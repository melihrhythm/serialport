/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QTextEdit *textEdit;
    QPushButton *refreshPortsButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QComboBox *fileFormatComboBox;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(160, 30, 531, 421));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        refreshPortsButton = new QPushButton(layoutWidget);
        refreshPortsButton->setObjectName("refreshPortsButton");

        verticalLayout->addWidget(refreshPortsButton);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(350, 460, 131, 81));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        fileFormatComboBox = new QComboBox(widget);
        fileFormatComboBox->setObjectName("fileFormatComboBox");

        verticalLayout_2->addWidget(fileFormatComboBox);

        saveButton = new QPushButton(widget);
        saveButton->setObjectName("saveButton");

        verticalLayout_2->addWidget(saveButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        refreshPortsButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "data", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
