#ifndef SERIALMODEL_H
#define SERIALMODEL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QStringList>

/**
 * @brief Serial port ile iletişimi sağlayan sınıf.
 *
 * Bu sınıf, tekil (singleton) desenini kullanarak bir seri port
 * iletişim modeli sağlar. Seri port ile veri okuma, yazma ve
 * yapılandırma işlemlerini gerçekleştirir.
 */
class SerialModel : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief SerialModel sınıfının tekil örneğini döner.
     *
     * Bu fonksiyon, SerialModel sınıfının tekil (singleton) örneğini döner.
     *
     * @return SerialModel örneği
     */
    static SerialModel& getInstance()
    {
        static SerialModel instance;
        return instance;
    }

    /**
     * @brief Serial port nesnesini döner.
     *
     * Bu fonksiyon, seri port nesnesini döner.
     *
     * @return QSerialPort nesnesi
     */
    QSerialPort* getSerialPort() const { return serialPort; }

    /**
     * @brief Serial portu yapılandırır.
     *
     * Bu fonksiyon, seri portu verilen port adı ve baud hızı ile yapılandırır.
     *
     * @param portName Port adı
     * @param baudRate Baud hızı
     */
    void configureSerialPort(const QString &portName, qint32 baudRate);

    /**
     * @brief Serial portu açar.
     *
     * Bu fonksiyon, seri portu açar.
     */
    void openSerialPort();

    /**
     * @brief Serial portu kapatır.
     *
     * Bu fonksiyon, seri portu kapatır.
     */
    void closeSerialPort();

    /**
     * @brief Serial porttan veri okur.
     *
     * Bu fonksiyon, seri porttan veri okur.
     *
     * @return Okunan veri
     */
    QByteArray readData();

    /**
     * @brief Mevcut serial portları listeler.
     *
     * Bu fonksiyon, mevcut seri portları listeler ve bir QStringList olarak döner.
     *
     * @return Seri portların listesi
     */
    QStringList listSerialPorts();

    /**
     * @brief Serial porta veri yazar.
     *
     * Bu fonksiyon, seri porta verilen veriyi yazar.
     *
     * @param data Yazılacak veri
     */
    void writeData(const QString &data);

signals:
    /**
     * @brief Veri alındığında sinyal yayar.
     *
     * Bu sinyal, seri porttan veri alındığında yayılır.
     *
     * @param data Alınan veri
     */
    void dataReceived(const QByteArray &data);

private slots:
    /**
     * @brief Veri okunduğunda çağrılan slot.
     *
     * Bu slot, seri porttan veri okunduğunda çağrılır.
     */
    void handleReadyRead();

private:
    /**
     * @brief SerialModel sınıfının kurucusu.
     *
     * Bu fonksiyon, SerialModel sınıfının kurucusudur ve parent üst nesnesini alır.
     *
     * @param parent Üst nesne
     */
    explicit SerialModel(QObject *parent = nullptr);

    /**
     * @brief SerialModel sınıfının yıkıcısı.
     *
     * Bu fonksiyon, SerialModel sınıfının yıkıcısıdır.
     */
    ~SerialModel();

    /**
     * @brief Kopyalama yapılandırıcı ve atama operatörünü devre dışı bırak.
     *
     * Bu fonksiyonlar, SerialModel sınıfının kopyalanmasını ve atamasını devre dışı bırakır.
     */
    SerialModel(const SerialModel&) = delete;
    SerialModel& operator=(const SerialModel&) = delete;

    QSerialPort *serialPort; /**< QSerialPort nesnesi. */
};

#endif // SERIALMODEL_H
