//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_message.h" resolved

#include "message.h"

#include "ElaMessageBar.h"
#include "ui_message.h"
#include "../../model/TreeModel.h"
#include "../../item/TreeItem.h"

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
}

void message::loadData() {
    ui->treeView->setModel(TreeModel::instance());
}

void message::setupConnections() {
    connect(ui->pushButton_load, &ElaPushButton::clicked, this, &message::onLoadDataButtonClicked);
    connect(ui->pushButton_selectAll, &ElaPushButton::clicked, this, &message::onSelectAllButtonClicked);
}

void message::onLoadDataButtonClicked() {
    TreeModel::instance()->reloadData();
    ElaMessageBar::success(ElaMessageBarType::TopRight, "成功", "加载完成", 2500);
}


void message::onSelectAllButtonClicked() {
    TreeModel::instance()->selectAll();
}