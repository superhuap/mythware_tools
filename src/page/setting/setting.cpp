//
// Created by superhuap on 2025/7/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_setting.h" resolved

#include "setting.h"
#include "ui_setting.h"
#include "../../util/SettingManager.h"
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
    if (settings->value("run_mode").isNull()) {
        settings->setValue("run_mode", "cmd");
    }
    if (settings->value("theme").isNull()) {
        settings->setValue("theme", 0);
    }
    if (settings->value("mica_theme").isNull()) {
        settings->setValue("mica_theme", "Normal");
    }
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
    modeSwitchText = new ElaText(QStringLiteral("命令运行方式"), modeSwitchArea);
    modeComboBox = new ElaComboBox(modeSwitchArea);

    // IP 加载
    ipLoaderSwitchArea = new ElaScrollPageArea(this);
    ipLoaderSwitchLayout = new QHBoxLayout(ipLoaderSwitchArea);
    ipLoaderSwitchText = new ElaText(QStringLiteral("ip列表路径"), ipLoaderSwitchArea);
    ipLoaderSwitchPath = new ElaText("", ipLoaderSwitchArea);
    ipLoaderPushButton = new ElaPushButton(ipLoaderSwitchArea);

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
}

void setting::configWidgets() {
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
    ipLoaderPushButton->setText(QStringLiteral("选择文件"));

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
}

void setting::loadSettings() {
    QSettings * settings = SettingsManager::instance() -> settings();

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
    #if Q_OS_WIN
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
}

void setting::setupLayout() {
    // mode
    modeSwitchLayout->addWidget(modeSwitchText);
    modeSwitchLayout->addStretch();
    modeSwitchLayout->addWidget(modeComboBox);

    // ip loader
    ipLoaderSwitchLayout->addWidget(ipLoaderSwitchText);
    ipLoaderSwitchLayout->addStretch();
    ipLoaderSwitchLayout->addWidget(ipLoaderSwitchPath);
    ipLoaderSwitchLayout->addStretch();
    ipLoaderSwitchLayout->addWidget(ipLoaderPushButton);

    // mica
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(normalButton);
    micaSwitchLayout->addWidget(elamicaButton);
    #if Q_OS_WIN
    micaSwitchLayout->addWidget(micaButton);
    micaSwitchLayout->addWidget(micaAltButton);
    micaSwitchLayout->addWidget(acrylicButton);
    micaSwitchLayout->addWidget(dwmBlurButton);
    #endif

    // theme
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(themeComboBox);

    // 主布局
    centerLayout->addWidget(modeSwitchArea);
    centerLayout->addWidget(ipLoaderSwitchArea);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addStretch();
}

void setting::setupConnections() {
    connect(modeComboBox, &ElaComboBox::currentTextChanged, this, &setting::onComboBoxTextChanged);
    connect(ipLoaderPushButton, &ElaPushButton::clicked, this, &setting::onIpLoaderButtonClicked);
    connect(micaButtonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &setting::onMicaButtonClicked);
    connect(themeComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, &setting::onThemeComboBoxChanged);
}

void setting::onIpLoaderButtonClicked() {
    QString file_name = QFileDialog::getOpenFileName(this, tr("打开文件"), QDir::homePath(), tr("文本文件 (*.txt)"));
    if (file_name == "") {
        return;
    }
    ipLoaderSwitchPath->setText(file_name);
    SettingsManager::instance()->setValue("ip_loader_path", file_name);
}

void setting::onMicaButtonClicked(QAbstractButton *button) {
    SettingsManager::instance() -> setValue("mica_theme", button->text());
    if (button->text() == "Normal") {
        eApp->setWindowDisplayMode(ElaApplicationType::Normal);
    } else if (button->text() == "ElaMica") {
        eApp->setWindowDisplayMode(ElaApplicationType::ElaMica);
    }
    #if Q_OS_WIN
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


