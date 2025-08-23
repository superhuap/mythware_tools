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
class ElaScrollPageArea;
class ElaRadioButton;
class ElaSpinBox;
class ElaDoubleSpinBox;

QT_BEGIN_NAMESPACE
namespace Ui { class setting; }
QT_END_NAMESPACE

class setting : public ElaScrollPage {
Q_OBJECT

public:
    explicit setting(QWidget *parent);
    ~setting() override;

private slots:
    void onSpinBoxValueChanged(int value);
    void onComboBoxTextChanged(QString text);
    void onIpLoaderButtonClicked();
    void onMsgLoaderButtonClicked();
    void onCmdLoaderButtonClicked();
    void onMicaButtonClicked(QAbstractButton *button);
    void onThemeComboBoxChanged(int index);
    void onDoubleSpinBoxValueChanged(double value);

private:
    void initSettings();
    void createWidgets();
    void configWidgets();
    void loadSettings();
    void setupLayout();
    void setupConnections();

    Ui::setting *ui;

    QWidget *centralWidget;
    QVBoxLayout *centerLayout;

    // 端口选择
    ElaScrollPageArea *portSwitchArea;
    QHBoxLayout *portSwitchLayout;
    ElaText *portSwitchText;
    ElaSpinBox *portSpinBox;

    // 模式选择
    ElaScrollPageArea *modeSwitchArea;
    QHBoxLayout *modeSwitchLayout;
    ElaText *modeSwitchText;
    ElaComboBox *modeComboBox;

    // IP 加载
    ElaScrollPageArea *ipLoaderSwitchArea;
    QHBoxLayout *ipLoaderSwitchLayout;
    ElaText *ipLoaderSwitchText;
    ElaText *ipLoaderSwitchPath;
    ElaPushButton *ipLoaderPushButton;

    // 快捷消息加载
    ElaScrollPageArea *msgLoaderSwitchArea;
    QHBoxLayout *msgLoaderSwitchLayout;
    ElaText *msgLoaderSwitchText;
    ElaText *msgLoaderSwitchPath;
    ElaPushButton *msgLoaderPushButton;

    // 快捷命令加载
    ElaScrollPageArea *cmdLoaderSwitchArea;
    QHBoxLayout *cmdLoaderSwitchLayout;
    ElaText *cmdLoaderSwitchText;
    ElaText *cmdLoaderSwitchPath;
    ElaPushButton *cmdLoaderPushButton;

    // Mica
    ElaScrollPageArea *micaSwitchArea;
    QHBoxLayout *micaSwitchLayout;
    QButtonGroup *micaButtonGroup;
    ElaText *micaSwitchText;
    ElaRadioButton *normalButton;
    ElaRadioButton *elamicaButton;
    ElaRadioButton *micaButton;
    ElaRadioButton *micaAltButton;
    ElaRadioButton *acrylicButton;
    ElaRadioButton *dwmBlurButton;

    // 主题
    ElaScrollPageArea *themeSwitchArea;
    QHBoxLayout *themeSwitchLayout;
    ElaText *themeSwitchText;
    ElaComboBox *themeComboBox;

    // 消息提示显示时间
    ElaScrollPageArea *messageBarMsecSwitchArea;
    QHBoxLayout *messageBarMsecSwitchLayout;
    ElaText *messageBarMsecSwitchText;
    ElaDoubleSpinBox *messageBarMsecDoubleSpinBox;
};


#endif //SETTING_H
