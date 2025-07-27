//
// Created by superhuap on 2025/7/27.
//

#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

class ElaPushButton;
class QHBoxLayout;
class ElaComboBox;
class ElaText;
class QVBoxLayout;
class ElaToggleSwitch;
class ElaScrollPageArea;

QT_BEGIN_NAMESPACE
namespace Ui { class setting; }
QT_END_NAMESPACE

class setting : public QWidget {
Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting() override;

private:
    void createWidgets();
    void configWidgets();
    void setupLayout();
    void setupConnection();

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
    ElaText *micaSwitchText = nullptr;
    ElaToggleSwitch *micaSwitchButton = nullptr;

    // 主题
    ElaScrollPageArea *themeSwitchArea = nullptr;
    QHBoxLayout *themeSwitchLayout = nullptr;
    ElaText *themeSwitchText = nullptr;
    ElaComboBox *themeComboBox = nullptr;
};


#endif //SETTING_H
