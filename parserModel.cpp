#include "parserMap.h"
#include <QDebug>
#include <QMap>

// Enum tanımı
enum Command {
    SM, RDI, SD, EAFA, EALA, TLT, UDE, RDT, UDT, RTLC, RBP, SMMV, RLST,
    SAT0, SAT1, SDST0, SDST1, RAS, RDS, SDST, RDST, DDT, EDT, RFLT,
    RLLT, RIST, SIST, RIS, IST, DILM, EILM, RE, InvalidCommand
};

// Komutları stringlerden enum değerlerine çeviren fonksiyon
Command getCommandFromString(const QString& command) {
    static const QMap<QString, Command> commandMap = {
        {"SM", SM}, {"RDI", RDI}, {"SD", SD}, {"EAFA", EAFA}, {"EALA", EALA},
        {"TLT", TLT}, {"UDE", UDE}, {"RDT", RDT}, {"UDT", UDT}, {"RTLC", RTLC},
        {"RBP", RBP}, {"SMMV", SMMV}, {"RLST", RLST}, {"SAT0", SAT0}, {"SAT1", SAT1},
        {"SDST0", SDST0}, {"SDST1", SDST1}, {"RAS", RAS}, {"RDS", RDS}, {"SDST", SDST},
        {"RDST", RDST}, {"DDT", DDT}, {"EDT", EDT}, {"RFLT", RFLT}, {"RLLT", RLLT},
        {"RIST", RIST}, {"SIST", SIST}, {"RIS", RIS}, {"IST", IST}, {"DILM", DILM},
        {"EILM", EILM}, {"RE", RE}
    };

    return commandMap.value(command, InvalidCommand);
}

// Constructor
ParserModel::ParserModel() : globalOperation("") {
}

// parseData fonksiyonunu tanımla
void ParserModel::parseData(const QString& data) {
    // Gelen veriyi virgüllerle ayır
    QStringList parsedData = data.split(',');

    // Verileri kontrol et
    if (parsedData.size() >= 3) {
        QString thirdValue = parsedData.at(2);

        if (parsedData[0] == "CMD" && parsedData[1] == "OK") {
            Command command = getCommandFromString(thirdValue);
            switch (command) {
            case SM:
                qDebug() << "SET MISSION:" << parsedData[3];
                break;
            case RDI:
                qDebug() << "READS DEVICE ID:" << parsedData[3];
                break;
            case SD:
                qDebug() << "SETS DEVICE ID:" << parsedData[3];
                break;
            case EAFA:
                qDebug() << "ERASES ALL FLASH AREA:" << parsedData[3];
                break;
            case EALA:
                qDebug() << "ERASES ALL LOG AREA:" << parsedData[3];
                break;
            case TLT:
                qDebug() << "TAKES LOG AND TRANSMIT:" << parsedData[3];
                break;
            case UDE:
                qDebug() << "UPDATES DEVICE EXPLANATION:" << parsedData[3];
                break;
            case RDT:
                qDebug() << "READS DEVICE TIME:" << parsedData[3];
                break;
            case UDT:
                qDebug() << "UPDATES DEVICE TIME:" << parsedData[3];
                break;
            case RTLC:
                qDebug() << "READS TOTAL LOG COUNT:" << parsedData[3];
                break;
            case RBP:
                qDebug() << "READS BATTERY PERCENTAGE:" << parsedData[3];
                break;
            case SMMV:
                qDebug() << "SETS MIN MAX VALUES:" << parsedData[3];
                break;
            case RLST:
                qDebug() << "READS LOG SLEEP TIME:" << parsedData[3];
                break;
            case SAT0:
            case SAT1:
                qDebug() << "SETS ALARM STATUS TO:" << parsedData[3];
                break;
            case SDST0:
            case SDST1:
                qDebug() << "SETS DATALOGGER STATUS:" << parsedData[3];
                break;
            case RAS:
                qDebug() << "READS ALARM STATUS:" << parsedData[3];
                break;
            case RDS:
                qDebug() << "READS DATALOGGER STATUS:" << parsedData[3];
                break;
            case SDST:
                qDebug() << "SETS DELAYED START TIME:" << parsedData[3];
                break;
            case RDST:
                qDebug() << "READS DELAYED START TIME:" << parsedData[3];
                break;
            case DDT:
                qDebug() << "DISABLES DELAYED TIME:" << parsedData[3];
                break;
            case EDT:
                qDebug() << "ENABLES DELAYED TIME:" << parsedData[3];
                break;
            case RFLT:
                qDebug() << "READS FIRST LOG TIME:" << parsedData[3];
                break;
            case RLLT:
                qDebug() << "READS LAST LOG TIME:" << parsedData[3];
                break;
            case RIST:
                qDebug() << "READS INTERMINATED STOP TIME:" << parsedData[3];
                break;
            case SIST:
                qDebug() << "SETS INTERMINATED STOP TIME:" << parsedData[3];
                break;
            case RIS:
                qDebug() << "READS INTERMINATED START TIME:" << parsedData[3];
                break;
            case IST:
                qDebug() << "SETS INTERMINATED START TIME:" << parsedData[3];
                break;
            case DILM:
                qDebug() << "DISABLING INTERMINATED LOG MODE:" << parsedData[3];
                break;
            case EILM:
                qDebug() << "ENABLING INTERMINATED LOG MODE:" << parsedData[3];
                break;
            case RE:
                qDebug() << "READS EXPLANATION:" << parsedData[3];
                break;
            case InvalidCommand:
            default:
                qDebug() << "Geçersiz komut!";
                break;
            }
        } else {
            qDebug() << "Geçersiz veri formatı!";
        }
    } else {
        qDebug() << "Yetersiz veri!";
    }
}
