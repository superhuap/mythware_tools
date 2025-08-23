//
// Created by superhuap on 2025/8/23.
//

#include "xmlloaderhelper.h"
#include "SettingManager.h"
#include "elamessagebar.h"
#include <QFile>
#include <QIODevice>

ParsedXmlResult loadAndParseXML(const QString& settingKey, const QString& expectedRootTag)
{
    ParsedXmlResult result;

    // 获取文件路径
    QString filePath = SettingsManager::instance()->getValue(settingKey).toString();
    if (filePath.isEmpty()) {
        ElaMessageBar::error(ElaMessageBarType::TopRight,
                             QStringLiteral("错误"),
                             QStringLiteral("未设置文件路径: %1").arg(settingKey),
                             SettingsManager::instance()->getValue("message_bar_msec").toInt());
        return result;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ElaMessageBar::error(ElaMessageBarType::TopRight,
                             QStringLiteral("错误"),
                             QStringLiteral("无法打开文件：%1").arg(filePath),
                             SettingsManager::instance()->getValue("message_bar_msec").toInt());
        SettingsManager::instance()->remove(settingKey);
        return result;
    }

    QDomDocument doc;
    QString errorStr;
    int errorLine, errorCol;

    if (!doc.setContent(&file, &errorStr, &errorLine, &errorCol)) {
        file.close();
        ElaMessageBar::error(ElaMessageBarType::TopRight,
                             QStringLiteral("解析失败"),
                             QStringLiteral("XML格式错误，第%1行：\n%2")
                                     .arg(errorLine).arg(errorStr),
                             SettingsManager::instance()->getValue("message_bar_msec").toInt());
        SettingsManager::instance()->remove(settingKey);

        result.errorMessage = errorStr;
        result.errorLine = errorLine;
        result.errorCol = errorCol;
        return result;
    }
    file.close();

    // 检查根节点
    QDomElement root = doc.documentElement();
    if (root.tagName() != expectedRootTag) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight,
                               QStringLiteral("格式错误"),
                               QStringLiteral("XML根节点应为 <%1>").arg(expectedRootTag),
                               SettingsManager::instance()->getValue("message_bar_msec").toInt());
        return result;
    }

    result.doc = doc;
    result.rootTagName = expectedRootTag;
    result.isValid = true;
    return result;
}
