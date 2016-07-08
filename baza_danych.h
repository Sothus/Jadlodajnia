#ifndef BAZA_DANYCH_H
#define BAZA_DANYCH_H

#include <QWidget>
#include <QString>
#include <QVector>

class DataBase
{
private:
   QStringList lista;

public:
    DataBase();
    QList< QStringList > model;
    ~DataBase();
};

#endif // BAZA_DANYCH_H
