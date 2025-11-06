//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_setting.h" resolved

#include "setting.h"
#include "ui_setting.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QButtonGroup>
#include <ElaTheme.h>
#include <ElaScrollPageArea.h>
#include <ElaText.h>
#include <ElaComboBox.h>
#include <ElaPushButton.h>
#include <ElaRadioButton.h>
#include <ElaApplication.h>
#include <ElaSpinBox.h>
#include "../../util/SettingManager.h"
#include "DropableElaText.h"

setting::setting(QWidget *parent) :
    ElaScrollPage(parent), ui(new Ui::setting) {
    ui->setupUi(this);
    initSettings();
    createWidgets();
    configWidgets();
    loadSettings();
    setupLayout();
    setupConnections();
    addCentralWidget(centralWidget, centerLayout);
}

setting::~setting() {
    delete ui;
}


void setting::initSettings() {
    QSettings * settings = SettingsManager::instance() -> settings();
    if (settings->value("port").isNull()) {
        settings->setValue("port", "4705");
    }
    if (settings->value("run_mode").isNull()) {
        settings->setValue("run_mode", "cmd");
    }
    if (settings->value("theme").isNull()) {
        settings->setValue("theme", 0);
    }
    if (settings->value("mica_theme").isNull()) {
        settings->setValue("mica_theme", "Normal");
    }
    if (settings->value("message_bar_msec").isNull()){
        settings->setValue("message_bar_msec", 1500);
    }
}

void setting::createWidgets() {
    // 创建中央容器
    centralWidget = new QWidget(this);
    centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setWindowTitle(" ");

    // 模式选择
    portSwitchArea = new ElaScrollPageArea(this);
    portSwitchLayout = new QHBoxLayout(portSwitchArea);
    portSwitchText = new ElaText(QStringLiteral("接收端口"), portSwitchArea);
    portSpinBox = new ElaSpinBox(portSwitchArea);

    // 模式选择
    modeSwitchArea = new ElaScrollPageArea(this);
    modeSwitchLayout = new QHBoxLayout(modeSwitchArea);
    modeSwitchText = new ElaText(QStringLiteral("命令运行方式"), modeSwitchArea);
    modeComboBox = new ElaComboBox(modeSwitchArea);

    // IP 加载
    ipLoaderSwitchArea = new ElaScrollPageArea(this);
    ipLoaderSwitchLayout = new QHBoxLayout(ipLoaderSwitchArea);
    ipLoaderSwitchText = new ElaText(QStringLiteral("ip列表路径"), ipLoaderSwitchArea);
    ipLoaderSwitchPath = new DropableElaText(ipLoaderSwitchArea);
    ipLoaderPushButton = new ElaPushButton(ipLoaderSwitchArea);

    // 快捷消息加载
    msgLoaderSwitchArea = new ElaScrollPageArea(this);
    msgLoaderSwitchLayout = new QHBoxLayout(msgLoaderSwitchArea);
    msgLoaderSwitchText = new ElaText(QStringLiteral("快捷消息路径"), msgLoaderSwitchArea);
    msgLoaderSwitchPath = new DropableElaText(msgLoaderSwitchArea);
    msgLoaderPushButton = new ElaPushButton(msgLoaderSwitchArea);

    // 快捷命令加载
    cmdLoaderSwitchArea = new ElaScrollPageArea(this);
    cmdLoaderSwitchLayout = new QHBoxLayout(cmdLoaderSwitchArea);
    cmdLoaderSwitchText = new ElaText(QStringLiteral("快捷命令路径"), cmdLoaderSwitchArea);
    cmdLoaderSwitchPath = new DropableElaText(cmdLoaderSwitchArea);
    cmdLoaderPushButton = new ElaPushButton(cmdLoaderSwitchArea);

    // Mica 开关
    micaSwitchArea = new ElaScrollPageArea(this);
    micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    micaSwitchText = new ElaText(QStringLiteral("云母效果"), micaSwitchArea);
    micaButtonGroup = new QButtonGroup(this);
    normalButton = new ElaRadioButton("Normal", this);
    elamicaButton = new ElaRadioButton("ElaMica", this);
    #ifdef Q_OS_WIN
    micaButton = new ElaRadioButton("Mica", this);
    micaAltButton = new ElaRadioButton("MicaAlt", this);
    acrylicButton = new ElaRadioButton("Acrylic", this);
    dwmBlurButton = new ElaRadioButton("DWMBlur", this);
    #endif

    // 主题切换
    themeSwitchArea = new ElaScrollPageArea(this);
    themeSwitchLayout = new QHBoxLayout(themeSwitchArea);
    themeSwitchText = new ElaText(QStringLiteral("主题切换"), themeSwitchArea);
    themeComboBox = new ElaComboBox(themeSwitchArea);

    // 消息提示显示时间
    messageBarMsecSwitchArea = new ElaScrollPageArea(this);
    messageBarMsecSwitchLayout = new QHBoxLayout(messageBarMsecSwitchArea);
    messageBarMsecSwitchText = new ElaText(QStringLiteral("消息提示显示时间"), messageBarMsecSwitchArea);
    messageBarMsecSpinBox = new ElaSpinBox(messageBarMsecSwitchArea);
}

void setting::configWidgets() {
    // port
    portSwitchText->setWordWrap(false);
    portSwitchText->setTextPixelSize(15);
    portSpinBox->setButtonMode(ElaSpinBoxType::Side);
    portSpinBox->setMinimum(0);
    portSpinBox->setMaximum(65535);

    // mode
    modeSwitchText->setWordWrap(false);
    modeSwitchText->setTextPixelSize(15);
    modeComboBox->addItem("cmd");
    modeComboBox->addItem("powershell");

    // ip loader
    ipLoaderSwitchText->setWordWrap(false);
    ipLoaderSwitchText->setTextPixelSize(15);
    ipLoaderSwitchPath->setTextPixelSize(10);
    ipLoaderSwitchPath->setWordWrap(false);
    ipLoaderSwitchPath->setMinimumWidth(100);
    ipLoaderSwitchPath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 扩展填充
    ipLoaderPushButton->setText(QStringLiteral("选择文件"));

    // msg loader
    msgLoaderSwitchText->setWordWrap(false);
    msgLoaderSwitchText->setTextPixelSize(15);
    msgLoaderSwitchPath->setTextPixelSize(10);
    msgLoaderSwitchPath->setWordWrap(false);
    msgLoaderSwitchPath->setMinimumWidth(100);
    msgLoaderSwitchPath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 扩展填充
    msgLoaderPushButton->setText(QStringLiteral("选择文件"));

    // cmd loader
    cmdLoaderSwitchText->setWordWrap(false);
    cmdLoaderSwitchText->setTextPixelSize(15);
    cmdLoaderSwitchPath->setTextPixelSize(10);
    cmdLoaderSwitchPath->setWordWrap(false);
    cmdLoaderSwitchPath->setMinimumWidth(100);
    cmdLoaderSwitchPath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 扩展填充
    cmdLoaderPushButton->setText(QStringLiteral("选择文件"));

    // mica
    micaSwitchText->setWordWrap(false);
    micaSwitchText->setTextPixelSize(15);
    micaButtonGroup->addButton(normalButton, 0);
    micaButtonGroup->addButton(elamicaButton, 1);
    #ifdef Q_OS_WIN
    micaButtonGroup->addButton(micaButton, 2);
    micaButtonGroup->addButton(micaAltButton, 3);
    micaButtonGroup->addButton(acrylicButton, 4);
    micaButtonGroup->addButton(dwmBlurButton, 5);
    #endif

    // theme
    themeSwitchText->setWordWrap(false);
    themeSwitchText->setTextPixelSize(15);
    themeComboBox->addItem(QStringLiteral("日间模式"));
    themeComboBox->addItem(QStringLiteral("夜间模式"));

    // message bar
    messageBarMsecSwitchText->setWordWrap(false);
    messageBarMsecSwitchText->setTextPixelSize(15);
    messageBarMsecSpinBox->setButtonMode(ElaSpinBoxType::Side);
    messageBarMsecSpinBox->setMinimum(100);
    messageBarMsecSpinBox->setMaximum(10000);
    messageBarMsecSpinBox->setSingleStep(100);
}

void setting::loadSettings() {
    QSettings * settings = SettingsManager::instance() -> settings();

    portSpinBox->setValue(settings->value("port", portSpinBox->value()).toInt());
    modeComboBox->setCurrentText(settings->value("run_mode").toString());

    eTheme->setThemeMode(settings->value("theme").toInt() == 0 ? ElaThemeType::Light : ElaThemeType::Dark);
    themeComboBox->setCurrentText(settings->value("theme") == 0 ? QStringLiteral("日间模式") : QStringLiteral("夜间模式"));

    QString mica_code = settings->value("mica_theme").toString();
    if (mica_code == "Normal") {
        micaButtonGroup->button(0)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::Normal);
    } else if (mica_code == "ElaMica") {
        micaButtonGroup->button(1)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::ElaMica);
    }
    #ifdef Q_OS_WIN
    else if (mica_code == "Mica") {
        micaButtonGroup->button(2)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::Mica);
    } else if (mica_code == "MicaAlt") {
        micaButtonGroup->button(3)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::MicaAlt);
    } else if (mica_code == "Acrylic") {
        micaButtonGroup->button(4)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::Acrylic);
    } else if (mica_code == "DWMBlur") {
        micaButtonGroup->button(5)->setChecked(true);
        eApp->setWindowDisplayMode(ElaApplicationType::DWMBlur);
    }
    #endif

    ipLoaderSwitchPath->setText(settings->value("ip_loader_path").toString());
    msgLoaderSwitchPath->setText(settings->value("msg_loader_path").toString());
    cmdLoaderSwitchPath->setText(settings->value("cmd_loader_path").toString());

    messageBarMsecSpinBox->setValue(settings->value("message_bar_msec").toInt());
}

void setting::setupLayout() {
    // port
    portSwitchLayout->addWidget(portSwitchText);
    portSwitchLayout->addStretch();
    portSwitchLayout->addWidget(portSpinBox);

    // mode
    modeSwitchLayout->addWidget(modeSwitchText);
    modeSwitchLayout->addStretch();
    modeSwitchLayout->addWidget(modeComboBox);

    // ip loader
    ipLoaderSwitchLayout->addWidget(ipLoaderSwitchText);
    ipLoaderSwitchLayout->addWidget(ipLoaderSwitchPath, 1); // 添加拉伸因子
    ipLoaderSwitchLayout->addWidget(ipLoaderPushButton);

    // msg loader
    msgLoaderSwitchLayout->addWidget(msgLoaderSwitchText);
    msgLoaderSwitchLayout->addWidget(msgLoaderSwitchPath, 1); // 添加拉伸因子
    msgLoaderSwitchLayout->addWidget(msgLoaderPushButton);

    // cmd loader
    cmdLoaderSwitchLayout->addWidget(cmdLoaderSwitchText);
    cmdLoaderSwitchLayout->addWidget(cmdLoaderSwitchPath, 1); // 添加拉伸因子
    cmdLoaderSwitchLayout->addWidget(cmdLoaderPushButton);

    // mica
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(normalButton);
    micaSwitchLayout->addWidget(elamicaButton);
    #ifdef Q_OS_WIN
    micaSwitchLayout->addWidget(micaButton);
    micaSwitchLayout->addWidget(micaAltButton);
    micaSwitchLayout->addWidget(acrylicButton);
    micaSwitchLayout->addWidget(dwmBlurButton);
    #endif

    // theme
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(themeComboBox);

    // message bar
    messageBarMsecSwitchLayout->addWidget(messageBarMsecSwitchText);
    messageBarMsecSwitchLayout->addStretch();
    messageBarMsecSwitchLayout->addWidget(messageBarMsecSpinBox);

    // 主布局
    centerLayout->addWidget(portSwitchArea);
    centerLayout->addWidget(modeSwitchArea);
    centerLayout->addWidget(ipLoaderSwitchArea);
    centerLayout->addWidget(msgLoaderSwitchArea);
    centerLayout->addWidget(cmdLoaderSwitchArea);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addWidget(messageBarMsecSwitchArea);
    centerLayout->addStretch();
}

void setting::setupConnections() {
    connect(portSpinBox, QOverload<int>::of(&ElaSpinBox::valueChanged), this, &setting::onPortSpinBoxValueChanged);
    connect(modeComboBox, &ElaComboBox::currentTextChanged, this, &setting::onComboBoxTextChanged);
    connect(ipLoaderPushButton, &ElaPushButton::clicked, this, &setting::onIpLoaderButtonClicked);
    connect(msgLoaderPushButton, &ElaPushButton::clicked, this, &setting::onMsgLoaderButtonClicked);
    connect(cmdLoaderPushButton, &ElaPushButton::clicked, this, &setting::onCmdLoaderButtonClicked);
    connect(micaButtonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &setting::onMicaButtonClicked);
    connect(themeComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, &setting::onThemeComboBoxChanged);
    connect(messageBarMsecSpinBox, QOverload<int>::of(&ElaSpinBox::valueChanged), this, &setting::onSpinBoxValueChanged);
    
    // 连接文件拖拽信号
    connect(ipLoaderSwitchPath, &DropableElaText::fileDropped, this, &setting::onIpFileDropped);
    connect(msgLoaderSwitchPath, &DropableElaText::fileDropped, this, &setting::onMsgFileDropped);
    connect(cmdLoaderSwitchPath, &DropableElaText::fileDropped, this, &setting::onCmdFileDropped);
}

void setting::onPortSpinBoxValueChanged(int value) {
    SettingsManager::instance()->setValue("port", value);
}

void setting::onIpLoaderButtonClicked() {
    QString file_name = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), QDir::homePath(), QStringLiteral("文本文件 (*.xml)"));
    if (file_name == "") {
        return;
    }
    ipLoaderSwitchPath->setText(file_name);
    SettingsManager::instance()->setValue("ip_loader_path", file_name);
}

void setting::onMsgLoaderButtonClicked() {
    QString file_name = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), QDir::homePath(), QStringLiteral("文本文件 (*.xml)"));
    if (file_name == "") {
        return;
    }
    msgLoaderSwitchPath->setText(file_name);
    SettingsManager::instance()->setValue("msg_loader_path", file_name);
}

void setting::onCmdLoaderButtonClicked() {
    QString file_name = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), QDir::homePath(), QStringLiteral("文本文件 (*.xml)"));
    if (file_name == "") {
        return;
    }
    cmdLoaderSwitchPath->setText(file_name);
    SettingsManager::instance()->setValue("cmd_loader_path", file_name);
}


void setting::onMicaButtonClicked(QAbstractButton *button) {
    SettingsManager::instance() -> setValue("mica_theme", button->text());
    if (button->text() == "Normal") {
        eApp->setWindowDisplayMode(ElaApplicationType::Normal);
    } else if (button->text() == "ElaMica") {
        eApp->setWindowDisplayMode(ElaApplicationType::ElaMica);
    }
    #ifdef Q_OS_WIN
    else if (button->text() == "Mica") {
        eApp->setWindowDisplayMode(ElaApplicationType::Mica);
    } else if (button->text() == "MicaAlt") {
        eApp->setWindowDisplayMode(ElaApplicationType::MicaAlt);
    } else if (button->text() == "Acrylic") {
        eApp->setWindowDisplayMode(ElaApplicationType::Acrylic);
    } else if (button->text() == "DWMBlur") {
        eApp->setWindowDisplayMode(ElaApplicationType::DWMBlur);
    }
    #endif
}

void setting::onThemeComboBoxChanged(int index) {
    eTheme->setThemeMode(index == 0 ? ElaThemeType::Light : ElaThemeType::Dark);
    SettingsManager::instance() -> setValue("theme", index);
}

void setting::onComboBoxTextChanged(QString text) {
    SettingsManager::instance() -> setValue("run_mode", text);
}

void setting::onSpinBoxValueChanged(double value) {
    SettingsManager::instance() -> setValue("message_bar_msec", value);
}

void setting::onIpFileDropped(const QString& filePath) {
    ipLoaderSwitchPath->setText(filePath);
    SettingsManager::instance()->setValue("ip_loader_path", filePath);
}

void setting::onMsgFileDropped(const QString& filePath) {
    msgLoaderSwitchPath->setText(filePath);
    SettingsManager::instance()->setValue("msg_loader_path", filePath);
}

void setting::onCmdFileDropped(const QString& filePath) {
    cmdLoaderSwitchPath->setText(filePath);
    SettingsManager::instance()->setValue("cmd_loader_path", filePath);
}


