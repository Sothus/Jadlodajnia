#include "basemanagerwindow.h"
#include "ui_basemanagerwindow.h"
#include "addproductdialog.h"
#include <QDebug>
#include <QFileDialog>

BaseManagerWindow::BaseManagerWindow(QString &filename, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::baseManagerWindow),
    basemodel(new ProductsTableModel(filename)),
    dialog(new AddProductDialog())
{
    fileName = filename;
    ui->setupUi(this);
    ui->baseProductTableView->setModel(basemodel);
    ui->baseProductTableView->verticalHeader()->hide();
    ui->baseProductTableView->resizeColumnsToContents();
}

BaseManagerWindow::~BaseManagerWindow(){
    delete ui;
}

void BaseManagerWindow::on_addProductButton_clicked(){
    connect(dialog, &AddProductDialog::addProductSignal, this, &BaseManagerWindow::addProductSlot);
    dialog->show();
}


void BaseManagerWindow::addProductSlot(QStringList product){
    basemodel->addProduct(product);
    ui->baseProductTableView->reset();
    ui->baseProductTableView->setModel(basemodel);
    qDebug() << "hop i slot";
}

void BaseManagerWindow::on_deleteProductButton_clicked(){
    basemodel->removeLastRow();
}

void BaseManagerWindow::on_saveButton_clicked(){
    basemodel->save2File(fileName);
}

void BaseManagerWindow::on_saveAsButton_clicked(){
    QString saveFileName = QFileDialog::getSaveFileName(this, "Zapisz jako...", "/c:/", "Pliki tekstowe (*.csv)");
    basemodel->save2File(saveFileName);
}
