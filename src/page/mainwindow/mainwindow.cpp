//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../message/message.h"
#include "../command/command.h"
#include "../setting/setting.h"


mainwindow::mainwindow(QWidget *parent) :
    ElaWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    init();
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::init() {
    this->setUserInfoCardVisible(false);
    this->setWindowTitle("mythware_tools");

    this->addPageNode("发送消息", new message(this), ElaIconType::Message);
    this->addPageNode("发送命令", new command(this), ElaIconType::Computer);
    this->addFooterNode("设置", new setting(this), Setting_key, 0, ElaIconType::GearComplex);
}

