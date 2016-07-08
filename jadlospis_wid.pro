#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T21:59:16
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jadlospis_wid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productstablemodel.cpp \
    chosenproductdelegate.cpp \
    chosenproducttablemodel.cpp \
    productwindow.cpp \
    basemanagerwindow.cpp \
    addproductdialog.cpp \
    startdialog.cpp

HEADERS  += mainwindow.h \
    productstablemodel.h \
    chosenproductdelegate.h \
    chosenproducttablemodel.h \
    productwindow.h \
    basemanagerwindow.h \
    addproductdialog.h \
    startdialog.h

FORMS    += mainwindow.ui \
    productwindow.ui \
    basemanagerwindow.ui \
    addproductdialog.ui \
    startdialog.ui

RC_FILE = ico.rc

RESOURCES += \
    res.qrc
