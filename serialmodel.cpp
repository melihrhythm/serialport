#include "serialmodel.h"
#include <QDebug>

/**
 * @brief SerialModel sınıfının kurucusu.
 * @param parent Üst nesne
 */
SerialModel::SerialModel(QObject *parent)
    : QObject(parent), serialPort(new QSerialPort(this))
{
    /* QSerialPort nesnesinin readyRead sinyalini handleReadyRead slotuna bağlar. */
    connect(serialPort, &QSerialPort::readyRead, this, &SerialModel::handleReadyRead);
}

/**
 * @brief SerialModel sınıfının yıkıcısı.
 */
SerialModel::~SerialModel()
{
    /* Serial port açıksa kapatılır ve nesne serbest bırakılır. */
    if (serialPort->isOpen())
        serialPort->close();
    delete serialPort;
}

/**
 * @brief Serial portu yapılandırır.
 * @param portName Port adı
 * @param baudRate Baud hızı
 */
void SerialModel::configureSerialPort(const QString &portName, qint32 baudRate)
{
    if (!serialPort) {
        qDebug() << "Serial port nesnesi geçersiz!";
        return;
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
}

/**
 * @brief Serial portu açar.
 */
void SerialModel::openSerialPort()
{
    if (!serialPort) {
        qDebug() << "Serial port nesnesi geçersiz!";
        return;
    }

    if (!serialPort->isOpen()) {
        if (serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port başarıyla açıldı.";
        } else {
            qDebug() << "Serial port açılamadı: " << serialPort->errorString();
        }
    }
}

/**
 * @brief Serial portu kapatır.
 */
void SerialModel::closeSerialPort()
{
    if (!serialPort) {
        qDebug() << "Serial port nesnesi geçersiz!";
        return;
    }

    if (serialPort->isOpen()) {
        serialPort->close();
        qDebug() << "Serial port kapatıldı.";
    }
}

/**
 * @brief Serial porttan veri okur.
 * @return Okunan veri
 */
QByteArray SerialModel::readData()
{
    if (!serialPort) {
        qDebug() << "Serial port nesnesi geçersiz!";
        return QByteArray();
    }

    QByteArray data = serialPort->readAll();
    qDebug() << "Serial porttan okunan veri: " << data;
    return data;
}

/**
 * @brief Mevcut serial portları listeler.
 * @return Seri portların listesi
 */
QStringList SerialModel::listSerialPorts()
{
    QStringList portList;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        portList.append(info.portName());
    return portList;
}

/**
 * @brief Serial porta veri yazar.
 * @param data Yazılacak veri
 */
void SerialModel::writeData(const QString &data)
{
    if (!serialPort || !serialPort->isOpen()) {
        qDebug() << "Serial port nesnesi geçersiz veya açık değil!";
        return;
    }

    if (!data.isEmpty()) {
        serialPort->write(data.toUtf8());
        qDebug() << "Serial porta yazılan veri: " << data;
    }
}

/**
 * @brief Veri okunduğunda çağrılan slot.
 */
void SerialModel::handleReadyRead()
{
    if (!serialPort) {
        qDebug() << "Serial port nesnesi geçersiz!";
        return;
    }

    QByteArray data = readData();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    } else {
        qDebug() << "Serial porttan veri okunamadı.";
    }
}
