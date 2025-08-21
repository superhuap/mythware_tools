//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_message.h" resolved

#include "message.h"


#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include "ElaContentDialog.h"
#include "ElaMessageBar.h"
#include "ui_message.h"
#include "../../model/TreeModel.h"
#include "../../item/TreeItem.h"
#include "../../util/SettingManager.h"
#include "../../util/SendingManager.h"

message::message(QWidget *parent) :
    QWidget(parent), ui(new Ui::message) {
    ui->setupUi(this);
    configWidgets();
    loadData();
    setupConnections();
}

message::~message() {
    delete ui;
}

void message::configWidgets() {
    ui->label->setTextPixelSize(15);
    ui->label_2->setTextPixelSize(15);
    ui->spinBox->setButtonMode(ElaSpinBoxType::Side);
    dialog = new ElaContentDialog(this);
    dialog->setLeftButtonText(QStringLiteral("取消"));
    dialog->setMiddleButtonText(QStringLiteral("输入框"));
    dialog->setRightButtonText(QStringLiteral("快捷消息"));
    label = new ElaText(QStringLiteral("您想发送输入框还是快捷消息？"), dialog);
    label->setTextPixelSize(15);
    label->setAlignment(Qt::AlignCenter);
    dialog->setCentralWidget(label);
}

void message::loadData() {
    ui->treeView->setModel(TreeModel::instance());
    loadMsgData();
}

void message::setupConnections() {
    connect(ui->pushButton_load, &ElaPushButton::clicked, this, &message::onReLoadDataButtonClicked);
    connect(ui->pushButton_selectAll, &ElaPushButton::clicked, this, &message::onSelectAllButtonClicked);
    connect(ui->pushButton_send, &ElaPushButton::clicked, this, &message::onSendButtonClicked);
    connect(dialog, &ElaContentDialog::leftButtonClicked, [this]() {
        dialog->close();
    });
    connect(dialog, &ElaContentDialog::middleButtonClicked, [this]() {
        send(ui->plainTextEdit_msg->toPlainText());
        dialog->close();
    });
    connect(dialog, &ElaContentDialog::rightButtonClicked, [this]() {
        send(ui->comboBox->currentText());
        dialog->close();
    });
}

void message::onReLoadDataButtonClicked() {
    TreeModel::instance()->reloadData();
    loadMsgData();
}


void message::onSelectAllButtonClicked() {
    TreeModel::instance()->selectAll();
}

void message::onSendButtonClicked() {
    ui->progressBar->setValue(0);
    if (!ui->plainTextEdit_msg->toPlainText().isEmpty() && (ui->comboBox->currentText() != "")){
        dialog->show();
    } else {
        send(!ui->comboBox->currentText().isEmpty() ? ui->comboBox->currentText() : ui->plainTextEdit_msg->toPlainText());
    }
}

void message::send(QString msg){
    TreeModel * tree_model = TreeModel::instance();
    auto checkedItems = tree_model->getCheckedItems();
    int spinCount = ui->spinBox->value();

    if (checkedItems.isEmpty()) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight, QStringLiteral("提示"), QStringLiteral("没有选中的IP！"), 2500);
        return;
    }

    ui->pushButton_send->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->plainTextEdit_msg->setEnabled(false);
    ui->comboBox->setEnabled(false);

    QtConcurrent::run([=]() {
        int total = checkedItems.length() * spinCount;
        int sent = 0;

        for (int i = 1; i <= spinCount; ++i) {
            for (int j = 0; j < checkedItems.length(); ++j) {
                SendingManager::instance()->send("msg", msg, checkedItems.at(j)->getTitle());
                sent++;

                int progress = (sent * 100) / total;
                QMetaObject::invokeMethod(ui->progressBar, "setValue", Qt::QueuedConnection,Q_ARG(int, progress));
            }
        }

        QMetaObject::invokeMethod(this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::TopRight, QStringLiteral("成功"), QStringLiteral("发送成功"), 2500);
        }, Qt::QueuedConnection);
        ui->pushButton_send->setEnabled(true);
        ui->spinBox->setEnabled(true);
        ui->plainTextEdit_msg->setEnabled(true);
        ui->comboBox->setEnabled(true);
    });
}

void message::loadMsgData() {
    ui->comboBox->addItem("");
    ui->comboBox->clear();
    QFile file(SettingsManager::instance()->getValue("msg_loader_path").toString());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    int messageCount = 0;
    ui->comboBox->addItem("");
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }
        messageCount++;
        ui->comboBox->addItem(line);
    }
    file.close();
    ElaMessageBar::success(ElaMessageBarType::TopRight, QStringLiteral("成功"), QStringLiteral("加载了%1条消息").arg(messageCount), 2500);
}
