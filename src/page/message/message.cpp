//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_message.h" resolved

#include "message.h"


#include <QTextStream>
#include <QFile>
#include <QDebug>
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
}

void message::loadData() {
    ui->treeView->setModel(TreeModel::instance());
    loadMsgData();
}

void message::setupConnections() {
    connect(ui->pushButton_load, &ElaPushButton::clicked, this, &message::onReLoadDataButtonClicked);
    connect(ui->pushButton_selectAll, &ElaPushButton::clicked, this, &message::onSelectAllButtonClicked);
    connect(ui->pushButton_send, &ElaPushButton::clicked, this, &message::onSendButtonClicked);
}

void message::onReLoadDataButtonClicked() {
    TreeModel::instance()->reloadData();
    loadMsgData();
}


void message::onSelectAllButtonClicked() {
    TreeModel::instance()->selectAll();
}

void message::onSendButtonClicked() {
    TreeModel * tree_model = TreeModel::instance();
    ui->progressBar->setValue(0);
    for (int i = 0; i < tree_model->getCheckedItems().length(); ++i) {
        QString message = !ui->comboBox->currentText().isEmpty() ? ui->comboBox->currentText() : ui->plainTextEdit_msg->toPlainText();
        SendingManager::instance()->send("msg", message, tree_model->getCheckedItems().at(i)->getTitle());
        ui->progressBar->setValue(((i + 1) * 100.0f) / tree_model->getCheckedItems().length());
    }
    ElaMessageBar::success(ElaMessageBarType::TopRight, QStringLiteral("成功"), QStringLiteral("发送成功"), 2500);
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
