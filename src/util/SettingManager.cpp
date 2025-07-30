//
// Created by superhuap on 2025/7/25.
//

#include "SettingManager.h"
#include <QSettings>

SettingsManager* SettingsManager::m_instance = nullptr;

SettingsManager* SettingsManager::instance()
{
    if (!m_instance) {
        m_instance = new SettingsManager();
    }
    return m_instance;
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings("superhuap", "mythware_tool")
{
}

void SettingsManager::setValue(const QString &key, const QVariant &value)
{
    m_settings.setValue(key, value);
}

QVariant SettingsManager::getValue(const QString &key, const QVariant &defaultValue) const
{
    return m_settings.value(key, defaultValue);
}

void SettingsManager::remove(const QString &key)
{
    m_settings.remove(key);
}

void SettingsManager::sync()
{
    m_settings.sync();
}