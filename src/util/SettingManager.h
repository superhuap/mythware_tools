//
// Created by superhuap on 2025/7/25.
//

#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QSettings>
#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    static SettingsManager* instance();

    // 提供 QSettings 的访问方法
    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
    void remove(const QString &key);
    void sync();

    // 获取原始 QSettings 对象
    QSettings* settings() { return &m_settings; }

private:
    explicit SettingsManager(QObject *parent = nullptr);
    static SettingsManager *m_instance;
    QSettings m_settings;
};

#endif //SETTINGMANAGER_H
