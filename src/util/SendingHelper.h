// SendingHelper.h
#pragma once

#include <QObject>

class SendingHelper : public QObject {
Q_OBJECT

public:
    static SendingHelper *instance();

    void send(const QString &type, QString content, const QString &ip);

private:
    explicit SendingHelper(QObject *parent = nullptr);

    static SendingHelper *m_instance;

    QByteArray formatToBytes(const QString &text) const;

    QByteArray packMessage(const QString &type, QString &content) const;

    static const std::array<QByteArray, 3> m_base;
};