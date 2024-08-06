QT += core gui widgets serialport printsupport

TARGET = SerialPortExample
TEMPLATE = app

SOURCES += main.cpp \
           codeeditor.cpp \
           mainwindow.cpp \
           parserModel.cpp \
           serialmodel.cpp

HEADERS += mainwindow.h \
           codeeditor.h \
           parserModel.h \
           serialmodel.h

FORMS += mainwindow.ui
