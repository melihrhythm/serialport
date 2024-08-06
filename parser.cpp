#include "parserModel.h"
#include <QString>
#include <QStringList>
#include <QDebug>

parserModel::parserModel() : globalOperation("") {
}

void parserModel::parseData(const QString& data) {
    // Gelen veriyi virgüllerle ayır
    QStringList parsedData = data.split(',');

    // Verileri kontrol et
    if (parsedData.size() >= 3) {
        QString firstValue = parsedData.at(0);
        QString secondValue = parsedData.at(1);
        QString thirdValue = parsedData.at(2);
        QString fourthValue = parsedData.size() > 3 ? parsedData.at(3) : "";

        if (firstValue == "CMD" && secondValue == "OK") {
            // Üçüncü değeri global değişkene ata
            globalOperation = thirdValue;
            qDebug() << "Global Operation:" << globalOperation;

            // Dördüncü değeri kontrol et (kartın geri dönüşü)
            if (!fourthValue.isEmpty()) {
                // Kartın geri dönüşünü işleme
                qDebug() << "Card Response:" << fourthValue;
            }
        } else {
            qDebug() << "Geçersiz veri formatı!";
        }
    } else {
        qDebug() << "Yetersiz veri!";
    }
}
