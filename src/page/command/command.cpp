//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_command.h" resolved

#include "command.h"
#include "ui_command.h"
#include <QDomElement>
#include <QtConcurrent/QtConcurrent>
#include <ElaMessageBar.h>
#include <ElaContentDialog.h>
#include "../../item/TreeItem.h"
#include "../../model/TreeModel.h"
#include "../../util/XmlLoaderHelper.h"
#include "../../util/SettingManager.h"
#include "../../util/SendingHelper.h"

command::command(QWidget *parent) :
    QWidget(parent), ui(new Ui::command) {
    ui->setupUi(this);
    configWidgets();
    loadData();
    setupConnections();
}

command::~command() {
    delete ui;
}

void command::configWidgets() {
    ui->label->setTextPixelSize(15);
    dialog = new ElaContentDialog(this);
    dialog->setLeftButtonText(QStringLiteral("取消"));
    dialog->setMiddleButtonText(QStringLiteral("输入框"));
    dialog->setRightButtonText(QStringLiteral("快捷命令"));
    label = new ElaText(QStringLiteral("您想发送输入框还是快捷命令？"), dialog);
    label->setTextPixelSize(15);
    label->setAlignment(Qt::AlignCenter);
    dialog->setCentralWidget(label);
}

void command::loadData() {
    ui->treeView->setModel(TreeModel::instance());
    loadCmdData();
}

void command::loadCmdData() {
    // 清空现有内容
    ui->comboBox->clear();
    ui->comboBox->addItem("", "");  // 可选：空项，无数据

    // 使用通用函数加载并解析 XML
    ParsedXmlResult result = loadAndParseXML("cmd_loader_path", "cmd_list");
    if (!result.isValid) {
        return;
    }

    QDomElement root = result.doc.documentElement();
    int validCount = 0;

    // 遍历所有 <cmd> 节点
    for (QDomElement elem = root.firstChildElement("cmd");
         !elem.isNull();
         elem = elem.nextSiblingElement("cmd")) {

        QString name = elem.firstChildElement("name").text().trimmed();
        QString command = elem.firstChildElement("command").text().trimmed();

        // name 和 command 至少要有 command
        if (command.isEmpty()) {
            continue;  // 跳过无效项
        }

        if (name.isEmpty()) {
            name = QStringLiteral("未知命令");
        }

        // 添加到 ComboBox：显示 name，存储 command 作为数据
        ui->comboBox->addItem(name, command);
        validCount++;
    }

    // 显示结果提示
    if (validCount > 0) {
        ElaMessageBar::success(ElaMessageBarType::TopRight,
                               QStringLiteral("成功"),
                               QStringLiteral("加载了 %1 条命令").arg(validCount),
                               SettingsManager::instance()->getValue("message_bar_msec").toInt());
    } else {
        ElaMessageBar::warning(ElaMessageBarType::TopRight,
                               QStringLiteral("提示"),
                               QStringLiteral("XML中未找到有效命令"),
                               SettingsManager::instance()->getValue("message_bar_msec").toInt());
    }
}

void command::setupConnections() {
    connect(ui->pushButton_load, &ElaPushButton::clicked, this, &command::onReLoadDataButtonClicked);
    connect(ui->pushButton_selectAll, &ElaPushButton::clicked, this, &command::onSelectAllButtonClicked);
    connect(ui->pushButton_send, &ElaPushButton::clicked, this, &command::onSendButtonClicked);
    connect(dialog, &ElaContentDialog::leftButtonClicked, [this]() {
        dialog->close();
    });
    connect(dialog, &ElaContentDialog::middleButtonClicked, [this]() {
        send(ui->plainTextEdit_cmd->toPlainText());
        dialog->close();
    });
    connect(dialog, &ElaContentDialog::rightButtonClicked, [this]() {
        send(ui->comboBox->currentData().toString());
        dialog->close();
    });
}

void command::onReLoadDataButtonClicked() {
    TreeModel::instance()->reloadData();
    loadCmdData();
}

void command::onSelectAllButtonClicked() {
    TreeModel::instance()->selectAll();
}

void command::onSendButtonClicked() {
    ui->progressBar->setValue(0);
    if (!ui->plainTextEdit_cmd->toPlainText().isEmpty() && (ui->comboBox->currentText() != "")){
        dialog->show();
    } else {
        send(!ui->comboBox->currentText().isEmpty() ? ui->comboBox->currentData().toString() : ui->plainTextEdit_cmd->toPlainText());
    }
}

void command::send(QString cmd) {
    TreeModel *tree_model = TreeModel::instance();
    auto checkedItems = tree_model->getCheckedItems();

    if (checkedItems.isEmpty()) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight,QStringLiteral("提示"),QStringLiteral("没有选中的IP！"),SettingsManager::instance()->getValue("message_bar_msec").toInt());
        return;
    }

    if (cmd.isEmpty()) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight,QStringLiteral("提示"),QStringLiteral("请输入命令！"),SettingsManager::instance()->getValue("message_bar_msec").toInt());
        return;
    }

    if (cmd.length() >= 150){
        ElaMessageBar::warning(ElaMessageBarType::TopRight,QStringLiteral("提示"),QStringLiteral("命令过长！"),SettingsManager::instance()->getValue("message_bar_msec").toInt());
        return;
    }

    // 禁用控件
    ui->pushButton_send->setEnabled(false);
    ui->comboBox->setEnabled(false);
    if (ui->plainTextEdit_cmd->isEnabled()) {
        ui->plainTextEdit_cmd->setEnabled(false);
    }

    // 获取运行模式
    QString runMode = SettingsManager::instance()->getValue("run_mode").toString();
    QString sendType = (runMode == "powershell") ? "powershell" : "cmd";

    QtConcurrent::run([=, this]() {
        int total = checkedItems.length();
        int sent = 0;

        for (int j = 0; j < checkedItems.length(); ++j) {
            const QString& ip = checkedItems.at(j)->getIp();
            SendingHelper::instance()->send(sendType, cmd, ip);
            sent++;

            int progress = (sent * 100) / total;
            QMetaObject::invokeMethod(ui->progressBar, "setValue", Qt::QueuedConnection, Q_ARG(int, progress));
            QMetaObject::invokeMethod(ui->label_Progress, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::number(progress) + "%"));
        }

        // 发送完成提示
        QMetaObject::invokeMethod(this, [=, this]() {
            ElaMessageBar::success(ElaMessageBarType::TopRight,
                                   QStringLiteral("成功"),
                                   QStringLiteral("命令已发送"),
                                   SettingsManager::instance()->getValue("message_bar_msec").toInt());
            ui->pushButton_send->setEnabled(true);
            ui->comboBox->setEnabled(true);
            ui->plainTextEdit_cmd->setEnabled(true);
        }, Qt::QueuedConnection);
    });
}



