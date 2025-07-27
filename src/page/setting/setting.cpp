//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_setting.h" resolved

#include "setting.h"
#include "ui_setting.h"


setting::setting(QWidget *parent) :
    QWidget(parent), ui(new Ui::setting) {
    ui->setupUi(this);
}

setting::~setting() {
    delete ui;
}
