#ifndef PARSERMAP_H
#define PARSERMAP_H
#include <QString>
#include <QStringList>
#include <QDebug>


class ParserModel {
public:
    ParserModel();
    void parseData(const QString& data);

private:
    QString processData(QStringList parsedData);
    QString globalOperation; // Global değişken
};
namespace send
{
constexpr const char* SET_MISSION = "WLC";
constexpr const char* READS_DEVICE_ID = "WLD0";
constexpr const char* SETS_DEVICE_ID = "WLD1";
constexpr const char* ERASES_ALL_FLASH_AREA = "WLE0";
constexpr const char* ERASES_ALL_LOG_AREA = "WLE1";
constexpr const char* TAKES_LOG_AND_TRANSMIT = "WLF";
constexpr const char* UPDATES_DEVICE_EXPLANATION = "WLG";
constexpr const char* READS_DEVICE_TIME = "WLH0";
constexpr const char* UPDATES_DEVICE_TIME = "WLH1";
constexpr const char* READS_TOTAL_LOG_COUNT = "WLI";
constexpr const char* READS_BATTERY_PERCENTAGE= "WLJ";
constexpr const char* SETS_MIN_MAX_VALUES = "WLK";
constexpr const char* READS_LOG_SLEEP_TIME = "WLM";
constexpr const char* SETS_ALARM_STATUS_TO_0 = "WLN0";
constexpr const char* SETS_ALARM_STATUS_TO_1 = "WLN1";
constexpr const char* SETS_DATALOGGER_STATUS_TO_0 = "WLP0";
constexpr const char* SETS_DATALOGGER_STATUS_TO_1 = "WLP1";
constexpr const char* READS_ALARM_STATUS = "WLO";
constexpr const char* READS_DATALOGGER_STATUS = "WLR";
constexpr const char* SETS_DELAYED_START_TIME = "WLS0";
constexpr const char* READS_DELAYED_START_TIME = "WLS1";
constexpr const char* DISABLES_DELAYED_TIME = "WLT0";
constexpr const char* ENABLES_DELAYED_TIME = "WLT1";
constexpr const char* READS_FIRST_LOG_TIME = "WLU0";
constexpr const char* READS_LAST_LOG_TIME = "WLU1";
//constexpr const char* DISABLING_START_AFTER_DISCONNECT = "WLV0";//
//constexpr const char* ENABLING_START_AFTER_DISCONNECT = "WLV1";//
constexpr const char* READS_INTERMINATED_STOP_TIME = "WLY0";
constexpr const char* SETS_INTERMINATED_STOP_TIME = "WLY1";
constexpr const char* READS_INTERMINATED_START_TIME = "WLZ0";
constexpr const char* SETS_INTERMINATED_START_TIME = "WLZ1";
constexpr const char* DISABLING_INTERMINATED_LOG_MODE = "WLX0";
constexpr const char* ENABLING_INTERMINATED_LOG_MODE = "WLX1";
constexpr const char* READS_EXPLANATION = "WLW";
}


namespace parse
{
constexpr const char* SM = "SWM";
constexpr const char* RDI = "IDR";
constexpr const char* SD = "IDW";
constexpr const char* EAFA = "FBE";
constexpr const char* EALA = "LBE";
constexpr const char* TLT = "TLG";
constexpr const char* UDE = "EXW";
constexpr const char* RDT = "DTR";
constexpr const char* UDT = "DTC";
constexpr const char* RTLC = "LGC";
constexpr const char* RBP = "BPS";
constexpr const char* SMMV = "MTF";
constexpr const char* RLST = "SLP";
constexpr const char* SAT0 = "ALS";
constexpr const char* SAT1 = "ALS";
constexpr const char* SDST0 = "DLS";
constexpr const char* SDST1 = "DLS";
constexpr const char* RAS = "ALS";
constexpr const char* RDS = "DLS";
constexpr const char* SDST = "DSD";
constexpr const char* RDST = "DSD";
constexpr const char* DDT = "DSS";
constexpr const char* EDT = "DSS";
constexpr const char* RFLT = "FDT";
constexpr const char* RLLT = "LDT";
//constexpr const char* DSAD = "WLV0";//
//constexpr const char* ESAD = "WLV1";//
constexpr const char* RIST = "ILS";
constexpr const char* SIST = "ILS";
constexpr const char* RIS = "ILT";
constexpr const char* IST = "ILT";
constexpr const char* DILM = "ITS";
constexpr const char* EILM = "ITS";
constexpr const char* RE = "EXR";

}




#endif // PARSERMAP_H
