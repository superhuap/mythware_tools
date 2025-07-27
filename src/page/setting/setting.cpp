//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_setting.h" resolved

#include "setting.h"
#include "ui_setting.h"
#include <ElaScrollPageArea.h>
#include <QHBoxLayout>
#include <ElaText.h>
#include <ElaComboBox.h>
#include <ElaPushButton.h>
#include <ElaToggleSwitch.h>


setting::setting(QWidget *parent) :
    QWidget(parent), ui(new Ui::setting) {
    ui->setupUi(this);
    createWidgets();
}

setting::~setting() {
    delete ui;
}

void setting::createWidgets() {
    // 创建中央容器
    centralWidget = new QWidget(this);
    centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setWindowTitle(" ");

    // 模式选择
    modeSwitchArea = new ElaScrollPageArea(this);
    modeSwitchLayout = new QHBoxLayout(modeSwitchArea);
    modeSwitchText = new ElaText("命令运行方式", modeSwitchArea);
    modeComboBox = new ElaComboBox(modeSwitchArea);

    // IP 加载
    ipLoaderSwitchArea = new ElaScrollPageArea(this);
    ipLoaderSwitchLayout = new QHBoxLayout(ipLoaderSwitchArea);
    ipLoaderSwitchText = new ElaText("ip列表路径", ipLoaderSwitchArea);
    ipLoaderSwitchPath = new ElaText("", ipLoaderSwitchArea);
    ipLoaderPushButton = new ElaPushButton(ipLoaderSwitchArea);

    // Mica 开关
    micaSwitchArea = new ElaScrollPageArea(this);
    micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    micaSwitchText = new ElaText("启用云母效果", micaSwitchArea);
    micaSwitchButton = new ElaToggleSwitch(micaSwitchArea);

    // 主题切换
    themeSwitchArea = new ElaScrollPageArea(this);
    themeSwitchLayout = new QHBoxLayout(themeSwitchArea);
    themeSwitchText = new ElaText("主题切换", themeSwitchArea);
    themeComboBox = new ElaComboBox(themeSwitchArea);
}

