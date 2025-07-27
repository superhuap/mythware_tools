//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_message.h" resolved

#include "message.h"
#include "ui_message.h"


message::message(QWidget *parent) :
    QWidget(parent), ui(new Ui::message) {
    ui->setupUi(this);
}

message::~message() {
    delete ui;
}
