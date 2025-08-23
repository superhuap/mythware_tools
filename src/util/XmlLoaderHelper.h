//
// Created by superhuap on 2025/8/23.
//

#ifndef MYTHWARE_TOOLS_XMLLOADERHELPER_H
#define MYTHWARE_TOOLS_XMLLOADERHELPER_H


#include <QDomDocument>
#include <QString>
#include <QPair>

struct ParsedXmlResult {
    QDomDocument doc;
    QString rootTagName;
    bool isValid = false;
    QString errorMessage;
    int errorLine = -1;
    int errorCol = -1;
};

ParsedXmlResult loadAndParseXML(const QString& settingKey, const QString& expectedRootTag);


#endif //MYTHWARE_TOOLS_XMLLOADERHELPER_H
