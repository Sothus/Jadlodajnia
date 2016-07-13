#include "baza_danych.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>


DataBase::DataBase()
{
    QFile in(":/baza1.csv");

    if(!in.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Błąd odczytu pliku!";
    QString tempStr;
    QTextStream stream(&in);

    while(!stream.atEnd()){
        tempStr = stream.readLine();
        lista = tempStr.split(",");
        model.append(lista);
    }
    in.close();
}

DataBase::~DataBase(){
}
