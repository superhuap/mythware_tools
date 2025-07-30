//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_command.h" resolved

#include "command.h"
#include "ui_command.h"
#include "../../model/TreeModel.h"

command::command(QWidget *parent) :
    QWidget(parent), ui(new Ui::command) {
    ui->setupUi(this);
    loadData();
}

command::~command() {
    delete ui;
}

void command::loadData() {
    ui->treeView->setModel(TreeModel::instance());
}
