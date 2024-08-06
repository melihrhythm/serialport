#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QFileDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QTimer>
#include <QIcon>  // QIcon sınıfını dahil ediyoruz

/**
 * @brief MainWindow yapıcı fonksiyonu
 * @param parent Üst widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialModel(SerialModel::getInstance())
{
    ui->setupUi(this);

    // Pencere başlığını ve simgesini ayarlıyoruz
    setWindowTitle("SerialPort-Beta"); // Yeni pencere başlığı
    setWindowIcon(QIcon("C:/Users/Umut Ceylan/Desktop/serialport.png")); // Yeni pencere simgesi, tam dosya yolu

    refreshSerialPorts();
    serialPort = serialModel.getSerialPort();

   /* if (!serialPort) {
        qDebug() << "Serial port nesnesi başlatılamadı!";
        return;
    }*/

    /* CodeEditor widget'ını oluştur ve frame içerisine yerleştir */
    codeEditor = new CodeEditor(this);
    QVBoxLayout *codeEditorLayout = new QVBoxLayout(ui->frame);
    codeEditorLayout->addWidget(codeEditor);
    ui->frame->setLayout(codeEditorLayout);

    /* Sinyal-slot bağlantıları */
    connect(ui->refreshPortsButton, &QPushButton::clicked, this, &MainWindow::refreshSerialPorts);
    connect(&serialModel, &SerialModel::dataReceived, this, &MainWindow::displayData);
    connect(ui->pushButton, &QPushButton::toggled, this, &MainWindow::on_pushButton_toggled);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::handleSendButton);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::clearTextEdit);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboBox_currentIndexChanged);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_lineEdit_returnPressed);
    connect(ui->ctrlZButton, &QPushButton::clicked, this, &MainWindow::handleCtrlZButton);

    /* Only Received CheckBox */
    onlyReceivedCheckBox = ui->onlyReceivedCheckBox;
    connect(onlyReceivedCheckBox, &QCheckBox::toggled, this, &MainWindow::handleOnlyReceivedModeChanged);

    /* Dosya formatı seçeneklerini ekle */
    ui->fileFormatComboBox->addItem("Save as .txt");
    ui->fileFormatComboBox->addItem("Save as .csv");

    /* Parity türlerini combo box'a ekle */
    ui->parityComboBox->addItem("No Parity", QSerialPort::NoParity);
    ui->parityComboBox->addItem("Even Parity", QSerialPort::EvenParity);
    ui->parityComboBox->addItem("Odd Parity", QSerialPort::OddParity);
    ui->parityComboBox->addItem("Mark Parity", QSerialPort::MarkParity);
    ui->parityComboBox->addItem("Space Parity", QSerialPort::SpaceParity);
    connect(ui->parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_parityComboBox_currentIndexChanged);

    /* Data bits seçeneklerini combo box'a ekleyin */
    ui->dataBitsComboBox->addItem("5", QSerialPort::Data5);
    ui->dataBitsComboBox->addItem("6", QSerialPort::Data6);
    ui->dataBitsComboBox->addItem("7", QSerialPort::Data7);
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);
    connect(ui->dataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_dataBitsComboBox_currentIndexChanged);

    /* Flow control seçeneklerini ekle */
    ui->flowControlComboBox->addItem("No Flow Control", QSerialPort::NoFlowControl);
    ui->flowControlComboBox->addItem("RTS/CTS", QSerialPort::HardwareControl);
    ui->flowControlComboBox->addItem("XON/XOFF", QSerialPort::SoftwareControl);
    connect(ui->flowControlComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_flowControlComboBox_currentIndexChanged);

    /* Stop bits seçeneklerini ekle */
    ui->stopBitsComboBox->addItem("1", QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->stopBitsComboBox->addItem("2", QSerialPort::TwoStop);
    connect(ui->stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_stopBitsComboBox_currentIndexChanged);

    /* Baud rate seçeneklerini combo box'a ekle */
    ui->baudRateComboBox->setEditable(true);
    ui->baudRateComboBox->addItem("9600", QSerialPort::Baud9600);
    ui->baudRateComboBox->addItem("19200", QSerialPort::Baud19200);
    ui->baudRateComboBox->addItem("38400", QSerialPort::Baud38400);
    ui->baudRateComboBox->addItem("57600", QSerialPort::Baud57600);
    ui->baudRateComboBox->addItem("115200", QSerialPort::Baud115200);
    connect(ui->baudRateComboBox, &QComboBox::editTextChanged, this, &MainWindow::on_baudRateComboBox_editTextChanged);
    connect(ui->baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_baudRateComboBox_currentIndexChanged);

    connect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(serialPort, &QSerialPort::readyRead, this, [=](){
        displayData(serialPort->readAll());
    });
}

/**
 * @brief MainWindow yıkıcı fonksiyonu
 */
MainWindow::~MainWindow()
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
    }
    delete ui;
}

/**
 * @brief Seri port listesini yenileme işlevi
 */
void MainWindow::refreshSerialPorts()
{
    ui->comboBox->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        ui->comboBox->addItem(port.portName());
        qDebug() << "Available port:" << port.portName();
    }
}

/**
 * @brief Bağlan/Diskonek butonunu işleme işlevi
 * @param checked Buton durumu
 */
void MainWindow::on_pushButton_toggled(bool checked)
{
    QString portName = ui->comboBox->currentText();

    if (checked) {
        // Eğer port zaten açık değilse, açmaya çalış
        if (!serialPort->isOpen()) {
            // Seri port ayarlarını yapılandır
            bool ok;
            int baudRate = ui->baudRateComboBox->currentText().toInt(&ok);
            if (!ok) {
                if (!onlyReceivedCheckBox->isChecked()) {
                    appendToCodeEditorWithTimestamp("Geçersiz baud rate!", false, true);
                }
                ui->pushButton->setChecked(false);
                return;
            }

            serialModel.configureSerialPort(portName, static_cast<QSerialPort::BaudRate>(baudRate));

            // Portu açmayı dene
            bool success = serialPort->open(QIODevice::ReadWrite);
            if (success) {
                ui->pushButton->setText("Disconnect");
                if (!onlyReceivedCheckBox->isChecked()) {
                    appendToCodeEditorWithTimestamp("Connected to " + portName, false, true);
                }
                updateUIForConnectionState(true); // UI'yi bağlantı durumu için güncelle
            } else {
                // Başarısız olursa, butonu geri al ve hata mesajı yaz
                if (!onlyReceivedCheckBox->isChecked()) {
                    appendToCodeEditorWithTimestamp("Failed to open port!", false, true);
                }
                qDebug() << "Failed to open port:" << serialPort->errorString();
                ui->pushButton->setChecked(false);
            }
        }
    } else {
        // Bağlantıyı kes
        if (serialPort->isOpen()) {
            serialPort->close();
            ui->pushButton->setText("Connect");
            if (!onlyReceivedCheckBox->isChecked()) {
                appendToCodeEditorWithTimestamp("Disconnected from " + portName, false, true);
            }
            updateUIForConnectionState(false); // UI'yi bağlantı durumu için güncelle
        }
    }
}

/**
 * @brief Veri gönderme butonunu işleme işlevi
 */
void MainWindow::handleSendButton()
{
    if (serialPort && serialPort->isOpen()) {
        QString data = ui->lineEdit->text();

        if (!data.isEmpty()) {
            serialModel.writeData(data);
            logSentData(data);
            ui->lineEdit->clear();
            if (!onlyReceivedCheckBox->isChecked()) {
                appendToCodeEditorWithTimestamp("Sending: " + data, false, true);
            }

            // "WBL" verisi gönderildiğinde frame içeriğini temizle
            if (data == "WBL") {
                // Frame içindeki tüm widget'ları sil
                QList<QWidget*> widgets = ui->frame->findChildren<QWidget*>();
                for (QWidget* widget : widgets) {
                    widget->deleteLater();
                }
                // Ayrıca layout'u temizlemek için
                QLayout* layout = ui->frame->layout();
                if (layout) {
                    QLayoutItem* item;
                    while ((item = layout->takeAt(0)) != nullptr) {
                        QWidget* widget = item->widget();
                        if (widget) {
                            widget->deleteLater();
                        }
                        delete item;
                    }
                }
            }
        }
    } else {
        qDebug() << "Serial port is not open!";
    }
}
/**
 * @brief Mesajı zaman damgasıyla birlikte CodeEditor'a ekler
 * @param message Mesaj metni
 * @param isReceived Mesajın alınıp alınmadığını belirler
 * @param includeTimestamp Zaman damgası eklenip eklenmeyeceğini belirler
 */
void MainWindow::appendToCodeEditorWithTimestamp(const QString &message, bool isReceived, bool includeTimestamp)
{
    QString formattedMessage = message;

    if (includeTimestamp) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString timestamp = currentDateTime.toString("[yyyy-MM-dd hh:mm:ss] ");
        formattedMessage = timestamp + message;
    }

    codeEditor->appendPlainText(formattedMessage);
}

/**
 * @brief Gönderilen verileri günlüğe kaydeder
 * @param data Gönderilen veri
 */
void MainWindow::logSentData(const QString &data)
{
    sentDataLog += data + "\n";
}

/**
 * @brief Alınan verileri günlüğe kaydeder
 * @param data Alınan veri
 */
void MainWindow::logReceivedData(const QString &data)
{
    receivedDataLog += data + "\n";
}

/**
 * @brief Alınan veriyi ekranda gösterir
 * @param data Alınan veri
 */
void MainWindow::displayData(const QByteArray &data)
{
    QString message = QString(data);
    appendToCodeEditorWithTimestamp(message, true, false);
    logReceivedData(message);
    qDebug() << "Data displayed: " << message;
}

/**
 * @brief CodeEditor içeriğini temizler
 */
void MainWindow::clearTextEdit()
{
    codeEditor->clear();
}

/**
 * @brief ComboBox'taki seçim değiştiğinde yapılacak işlemler
 * @param index Seçim indeksi
 */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
        ui->pushButton->setText("Connect");
        if (!onlyReceivedCheckBox->isChecked()) {
            appendToCodeEditorWithTimestamp("Disconnected from " + ui->comboBox->itemText(index), false, true);
        }
    }
}

/**
 * @brief LineEdit'te enter tuşuna basıldığında veri gönderir
 */
void MainWindow::on_lineEdit_returnPressed()
{
    handleSendButton();
}

/**
 * @brief Verileri dosyaya kaydetme işlemi
 */
void MainWindow::saveData()
{
    QString selectedFormat = ui->fileFormatComboBox->currentText();
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", selectedFormat == "Save as .txt" ? "Text Files (*.txt)" : "CSV Files (*.csv)");
    if (fileName.isEmpty())
        return;

    if (selectedFormat == "Save as .txt") {
        saveCodeEditorToTxtFile(fileName);
    } else if (selectedFormat == "Save as .csv") {
        saveCodeEditorToCsvFile(fileName);
    }
}

/**
 * @brief CodeEditor içeriğini .txt dosyasına kaydeder
 * @param fileName Dosya adı
 */
void MainWindow::saveCodeEditorToTxtFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << codeEditor->toPlainText(); // CodeEditor içeriğini yaz
        file.close();
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for writing"));
    }
}

/**
 * @brief CodeEditor içeriğini .csv dosyasına kaydeder
 * @param fileName Dosya adı
 */
void MainWindow::saveCodeEditorToCsvFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QString text = codeEditor->toPlainText();
        out << text.replace("\n", ",\n"); // CodeEditor içeriğini CSV formatında yaz
        file.close();
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for writing"));
    }
}
/**
 * @brief Parity ayarını günceller
 * @param index Parity indeksi
 */
void MainWindow::on_parityComboBox_currentIndexChanged(int index)
{
    QSerialPort::Parity parity;

    switch (index) {
    case 0:
        parity = QSerialPort::NoParity;
        break;
    case 1:
        parity = QSerialPort::EvenParity;
        break;
    case 2:
        parity = QSerialPort::OddParity;
        break;
    case 3:
        parity = QSerialPort::MarkParity;
        break;
    case 4:
        parity = QSerialPort::SpaceParity;
        break;
    default:
        return;
    }

    serialPort->setParity(parity);
    updateSerialSettings();
}

/**
 * @brief Data bits ayarını günceller
 * @param index Data bits indeksi
 */
void MainWindow::on_dataBitsComboBox_currentIndexChanged(int index)
{
    QSerialPort::DataBits dataBits;

    switch (index) {
    case 0:
        dataBits = QSerialPort::Data5;
        break;
    case 1:
        dataBits = QSerialPort::Data6;
        break;
    case 2:
        dataBits = QSerialPort::Data7;
        break;
    case 3:
        dataBits = QSerialPort::Data8;
        break;
    default:
        return;
    }

    serialPort->setDataBits(dataBits);
    updateSerialSettings();
}

/**
 * @brief Stop bits ayarını günceller
 * @param index Stop bits indeksi
 */
void MainWindow::on_stopBitsComboBox_currentIndexChanged(int index)
{
    QSerialPort::StopBits stopBits;

    switch (index) {
    case 0:
        stopBits = QSerialPort::OneStop;
        break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop;
        break;
    case 2:
        stopBits = QSerialPort::TwoStop;
        break;
    default:
        return;
    }

    serialPort->setStopBits(stopBits);
    updateSerialSettings();
}

/**
 * @brief Flow control ayarını günceller
 * @param index Flow control indeksi
 */
void MainWindow::on_flowControlComboBox_currentIndexChanged(int index)
{
    QSerialPort::FlowControl flowControl;

    switch (index) {
    case 0:
        flowControl = QSerialPort::NoFlowControl;
        break;
    case 1:
        flowControl = QSerialPort::HardwareControl;
        break;
    case 2:
        flowControl = QSerialPort::SoftwareControl;
        break;
    default:
        return;
    }

    serialPort->setFlowControl(flowControl);
    updateSerialSettings();
}

/**
 * @brief Ctrl+Z butonunu işleme işlevi
 */
void MainWindow::handleCtrlZButton()
{
    if (!serialPort || !serialPort->isOpen()) {
        qDebug() << "Serial port nesnesi geçersiz veya açık değil!";
        return;
    }

    QByteArray ctrlZ;
    ctrlZ.append(0x1A); /* ASCII for Ctrl+Z */
    serialPort->write(ctrlZ);
    if (!onlyReceivedCheckBox->isChecked()) {
        appendToCodeEditorWithTimestamp("Sent Ctrl+Z to signal end of operation", false, true);
    }
    qDebug() << "Sent Ctrl+Z to serial port.";
}

/**
 * @brief Only Received modunun durumunu değiştirir
 * @param checked Checkbox durumu
 */
void MainWindow::handleOnlyReceivedModeChanged(bool checked)
{
    codeEditor->clear();
    if (!checked) {
        appendToCodeEditorWithTimestamp("Only Received mode disabled", false, true);
    }
}

/**
 * @brief Hata durumunu işleme işlevi
 * @param error Seri port hatası
 */
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        // Hata mesajı göster
        QMessageBox::critical(this, tr("Critical Error"), serialPort->errorString());
        // Bağlantıyı kesmeden önce biraz gecikme ekleyelim
        QTimer::singleShot(1000, this, &MainWindow::onSerialPortDisconnected);
    } else {
        qDebug() << "Serial port error:" << error;
    }
}

/**
 * @brief UI'yi bağlantı durumu için günceller
 * @param connected Bağlantı durumu
 */
void MainWindow::updateUIForConnectionState(bool connected)
{
    ui->comboBox->setEnabled(!connected); // Port seçimi devre dışı bırak
    ui->parityComboBox->setEnabled(!connected); // Parity ayarı devre dışı bırak
    ui->dataBitsComboBox->setEnabled(!connected); // Data bits ayarı devre dışı bırak
    ui->stopBitsComboBox->setEnabled(!connected); // Stop bits ayarı devre dışı bırak
    ui->flowControlComboBox->setEnabled(!connected); // Flow control ayarı devre dışı bırak
    ui->refreshPortsButton->setEnabled(!connected); // Refresh button devre dışı bırak

    ui->baudRateComboBox->setEnabled(!connected); // Baud rate combo box devre dışı bırak

    ui->lineEdit->setEnabled(connected); // Line edit durumu bağlantıya göre ayarla
    ui->pushButton_2->setEnabled(connected); // Send button durumu bağlantıya göre ayarla
    ui->pushButton_3->setEnabled(connected); // Clear button durumu bağlantıya göre ayarla
    ui->saveButton->setEnabled(connected); // Save button durumu bağlantıya göre ayarla
    ui->ctrlZButton->setEnabled(connected); // Ctrl+Z button durumu bağlantıya göre ayarla
    ui->onlyReceivedCheckBox->setEnabled(connected); // Only Received checkbox durumu bağlantıya göre ayarla
}

/**
 * @brief Port ayarlarını devre dışı bırakır
 */
void MainWindow::disablePortSettings()
{
    ui->parityComboBox->setEnabled(false);
    ui->dataBitsComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->flowControlComboBox->setEnabled(false);
}

/**
 * @brief Port ayarlarını etkinleştirir
 */
void MainWindow::enablePortSettings()
{
    ui->parityComboBox->setEnabled(true);
    ui->dataBitsComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->flowControlComboBox->setEnabled(true);
}

/**
 * @brief Seri port bağlantısı kesildiğinde yapılacak işlemler
 */
void MainWindow::onSerialPortDisconnected()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    ui->pushButton->setText("Connect");
    updateUIForConnectionState(false);
    enablePortSettings(); // Bağlantı kesildiğinde ayarları tekrar etkinleştir
    codeEditor->clear();
    if (!onlyReceivedCheckBox->isChecked()) {
        appendToCodeEditorWithTimestamp("Port disconnected. Application reset.", false, true);
    }
}

/**
 * @brief Baud rate combo box'taki yazı değiştiğinde yapılacak işlemler
 * @param text Yazı metni
 */
void MainWindow::on_baudRateComboBox_editTextChanged(const QString &text)
{
    bool ok;
    int baudRate = text.toInt(&ok);
    if (!ok) {
        qDebug() << "Geçersiz baud rate:" << text;
        return;
    }
    serialPort->setBaudRate(baudRate);
    updateSerialSettings();
}

/**
 * @brief Baud rate combo box'taki seçim değiştiğinde yapılacak işlemler
 * @param index Seçim indeksi
 */
void MainWindow::on_baudRateComboBox_currentIndexChanged(int index)
{
    bool ok;
    int baudRate = ui->baudRateComboBox->itemData(index).toInt(&ok);
    if (!ok) {
        qDebug() << "Geçersiz baud rate:" << index;
        return;
    }
    serialPort->setBaudRate(baudRate);
    updateSerialSettings();
}

/**
 * @brief Seri port ayarlarını günceller ve terminalde görüntüler
 */
void MainWindow::updateSerialSettings()
{
    qDebug() << "Serial port settings updated:";
    qDebug() << "Parity:" << serialPort->parity();
    qDebug() << "Data bits:" << serialPort->dataBits();
    qDebug() << "Stop bits:" << serialPort->stopBits();
    qDebug() << "Flow control:" << serialPort->flowControl();
    qDebug() << "Baud rate:" << serialPort->baudRate();
}

