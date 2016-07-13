#include "mainwindow.h"
#include "chosenproductdelegate.h"
#include "startdialog.h"
#include <QApplication>

int main(int  argc, char *argv[])
{
    QApplication a(argc, argv);
    startDialog w;
    w.show();
    return a.exec();
}
