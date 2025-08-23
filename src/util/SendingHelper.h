// SendingHelper.h
#pragma once

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <random>

class SettingsManager; // 假设已存在

class SendingHelper : public QObject
{
    Q_OBJECT

public:
    static SendingHelper* instance();

    void send(const QString& type, const QString& content, const QString& ip);

private:
    explicit SendingHelper(QObject* parent = nullptr);

    static SendingHelper* m_instance;

    // 将 QString 转换为 Little-Endian UTF-16 字节数组
    QByteArray formatToBytes(const QString& text) const;

    // 构建消息包
    QByteArray packMessage(const QString& type, const QString& content) const;

    // 预置报文模板 (msg, cmd, powershell)
    // 注意：这里只包含前三个，你可以根据需要添加更多
    static const std::array<QByteArray, 3> m_base;
};