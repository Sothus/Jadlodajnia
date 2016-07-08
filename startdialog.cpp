#include "startdialog.h"
#include "ui_startdialog.h"
#include "mainwindow.h"
#include <QFileDialog>

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
    this->setSizeGripEnabled(0);
}

startDialog::~startDialog()
{
    delete ui;
}


void startDialog::on_customButton_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,"Otwórz...","/c:/","Pliki tekstowe (*.csv)");
    if(fileName.isEmpty())
        return;

    MainWindow* mainWind = new MainWindow();
    mainWind->show();
    connect(this, &startDialog::fileNameSignal, mainWind, &MainWindow::fileNameSlot);
    emit fileNameSignal(fileName);
    close();
}

void startDialog::on_defaultButton_clicked(){
    MainWindow* mainWind = new MainWindow();
    connect(this, &startDialog::fileNameSignal, mainWind, &MainWindow::fileNameSlot);
    emit fileNameSignal(":/baza1.csv");
    mainWind->show();
    close();
}
