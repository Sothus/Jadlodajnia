#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T21:59:16
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jadlospis_wid
TEMPLATE = app


SOURCES += src/addproductdialog.cpp \
    src/basemanagerwindow.cpp \
    src/baza_danych.cpp \
    src/chosenproductdelegate.cpp \
    src/chosenproducttablemodel.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/productstablemodel.cpp \
    src/productwindow.cpp \
    src/startdialog.cpp

HEADERS  += src/addproductdialog.h \
    src/basemanagerwindow.h \
    src/baza_danych.h \
    src/chosenproductdelegate.h \
    src/chosenproducttablemodel.h \
    src/mainwindow.h \
    src/nutritonaltypes.h \
    src/productstablemodel.h \
    src/productwindow.h \
    src/startdialog.h

FORMS    += src/addproductdialog.ui \
    src/basemanagerwindow.ui \
    src/mainwindow.ui \
    src/productwindow.ui \
    src/startdialog.ui

RC_FILE = res/ico.rc

RESOURCES += \
    res/res.qrc

DISTFILES += \
    LICENSE.md \
    README.md \
    res/icon.ico \
    res/baza1.csv \
    res/ico.rc
