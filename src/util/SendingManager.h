//
// Created by superhuap on 2025/7/31.
//

#ifndef SENDINGMANAGER_H
#define SENDINGMANAGER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QUdpSocket>

class SendingManager : public QObject
{
    Q_OBJECT

public:
    static SendingManager *instance();

    // 统一对外接口
    void send(const QString &type,
              const QString &content,
              const QString &ip);

private:
    explicit SendingManager(QObject *parent = nullptr);
    static SendingManager *m_instance;

    QByteArray packMessage(const QString &type, const QString &content) const;
    QByteArray formatToBytes(const QString &text) const;

    // 预置的 5 套报文模板（只用到下标 0/1/4）
    static const std::array<QByteArray, 5> m_base;
};

#endif // SENDINGMANAGER_H