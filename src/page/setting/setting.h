//
// Created by superhuap on 2025/7/27.
//

#ifndef SETTING_H
#define SETTING_H

#include <ElaScrollPage.h>

class QAbstractButton;
class QButtonGroup;
class ElaPushButton;
class QHBoxLayout;
class ElaComboBox;
class ElaText;
class QVBoxLayout;
class ElaToggleSwitch;
class ElaScrollPageArea;
class ElaRadioButton;

QT_BEGIN_NAMESPACE
namespace Ui { class setting; }
QT_END_NAMESPACE

class setting : public ElaScrollPage {
Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting() override;

private slots:
    void onComboBoxTextChanged(QString text);
    void onIpLoaderButtonClicked();
    void onMicaButtonClicked(QAbstractButton *button);
    void onThemeComboBoxChanged(int index);

private:
    void initSettings();
    void createWidgets();
    void configWidgets();
    void loadSettings();
    void setupLayout();
    void setupConnections();

    Ui::setting *ui;

    QWidget *centralWidget = nullptr;
    QVBoxLayout *centerLayout = nullptr;

    // 模式选择
    ElaScrollPageArea *modeSwitchArea = nullptr;
    QHBoxLayout *modeSwitchLayout = nullptr;
    ElaText *modeSwitchText = nullptr;
    ElaComboBox *modeComboBox = nullptr;

    // IP 加载
    ElaScrollPageArea *ipLoaderSwitchArea = nullptr;
    QHBoxLayout *ipLoaderSwitchLayout = nullptr;
    ElaText *ipLoaderSwitchText = nullptr;
    ElaText *ipLoaderSwitchPath = nullptr;
    ElaPushButton *ipLoaderPushButton = nullptr;

    // Mica
    ElaScrollPageArea *micaSwitchArea = nullptr;
    QHBoxLayout *micaSwitchLayout = nullptr;
    QButtonGroup *micaButtonGroup = nullptr;
    ElaText *micaSwitchText = nullptr;
    ElaRadioButton *normalButton = nullptr;
    ElaRadioButton *elamicaButton = nullptr;
    ElaRadioButton *micaButton = nullptr;
    ElaRadioButton *micaAltButton = nullptr;
    ElaRadioButton *acrylicButton = nullptr;
    ElaRadioButton *dwmBlurButton = nullptr;

    // 主题
    ElaScrollPageArea *themeSwitchArea = nullptr;
    QHBoxLayout *themeSwitchLayout = nullptr;
    ElaText *themeSwitchText = nullptr;
    ElaComboBox *themeComboBox = nullptr;
};


#endif //SETTING_H
