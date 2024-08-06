#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

#include "serialmodel.h"
#include "codeeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Ana pencere sınıfı.
 *
 * Bu sınıf, seri port iletişimi ve veri görüntüleme için ana arayüzü sağlar.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Yapıcı fonksiyon.
     *
     * @param parent Üst widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Yıkıcı fonksiyon.
     */
    ~MainWindow();

public slots:
    void refreshSerialPorts();   /**< Seri port listesini yeniler. */
    void saveData();             /**< Verileri kaydeder. */
    void handleOnlyReceivedModeChanged(bool checked); /**< Only Received modunun durumunu değiştirir. */

private slots:
    void handleSendButton();     /**< Veri gönderme butonunu işler. */
    void displayData(const QByteArray &data); /**< Alınan veriyi ekranda gösterir. */
    void clearTextEdit();        /**< CodeEditor içeriğini temizler. */
    void on_comboBox_currentIndexChanged(int index); /**< ComboBox'taki seçim değiştiğinde işlemler. */
    void on_lineEdit_returnPressed(); /**< LineEdit'te enter tuşuna basıldığında veri gönderir. */
    void on_parityComboBox_currentIndexChanged(int index); /**< Parity ayarını günceller. */
    void on_dataBitsComboBox_currentIndexChanged(int index); /**< Data bits ayarını günceller. */
    void on_stopBitsComboBox_currentIndexChanged(int index); /**< Stop bits ayarını günceller. */
    void on_flowControlComboBox_currentIndexChanged(int index); /**< Flow control ayarını günceller. */
    void handleCtrlZButton();    /**< Ctrl+Z butonunu işler. */
    void handleError(QSerialPort::SerialPortError error); /**< Hata durumunu işler. */
    void onSerialPortDisconnected(); /**< Seri port bağlantısı kesildiğinde işlemler. */
    void on_pushButton_toggled(bool checked); /**< Bağlan/Diskonek butonunu işler. */
    void on_baudRateComboBox_editTextChanged(const QString &text); /**< Baud rate combo box'taki yazı değiştiğinde işlemler. */
    void on_baudRateComboBox_currentIndexChanged(int index); /**< Baud rate combo box'taki seçim değiştiğinde işlemler. */

private:
    Ui::MainWindow *ui;                    /**< Kullanıcı arayüzü. */
    SerialModel &serialModel;              /**< Seri model nesnesi. */
    QSerialPort *serialPort;               /**< Seri port nesnesi. */
    CodeEditor *codeEditor;                /**< Kod düzenleyici widget'ı. */
    QCheckBox *onlyReceivedCheckBox;      /**< Yalnızca alınan verilerin görüntülenmesini sağlayan checkbox. */

    void listSerialPorts();                /**< Seri portları listeler. */
    void appendToCodeEditorWithTimestamp(const QString &message, bool isReceived = false, bool includeTimestamp = true); /**< Mesajı zaman damgasıyla birlikte CodeEditor'a ekler. */
    void logSentData(const QString &data); /**< Gönderilen verileri günlüğe kaydeder. */
    void logReceivedData(const QString &data); /**< Alınan verileri günlüğe kaydeder. */
    void saveCodeEditorToTxtFile(const QString &fileName); /**< Verileri .txt dosyasına kaydeder. */
    void saveCodeEditorToCsvFile(const QString &fileName); /**< Verileri .csv dosyasına kaydeder. */
    void disablePortSettings();           /**< Port ayarlarını devre dışı bırakır. */
    void enablePortSettings();            /**< Port ayarlarını etkinleştirir. */
    void updateUIForConnectionState(bool connected); /**< UI'yi bağlantı durumu için günceller. */
    void updateSerialSettings();          /**< Seri port ayarlarını günceller ve terminalde görüntüler. */

    QString sentDataLog;       /**< Gönderilen veri günlüğü. */
    QString receivedDataLog;   /**< Alınan veri günlüğü. */
};

#endif // MAINWINDOW_H
