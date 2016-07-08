#include "productwindow.h"
#include "ui_productwindow.h"

ProductWindow::ProductWindow(QString &fileName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductWindow),
    baseProductsModel(new ProductsTableModel(fileName)),
    proxyModel(new QSortFilterProxyModel())
{
    ui->setupUi(this);
    proxyModel->setSourceModel(baseProductsModel);
    proxyModel->setFilterKeyColumn(0);
    ui->dataBaseTableView->setModel(proxyModel);
    ui->dataBaseTableView->setSortingEnabled(true);
    ui->dataBaseTableView->setDragEnabled(true);
    ui->dataBaseTableView->verticalHeader()->hide();
    ui->dataBaseTableView->resizeColumnsToContents();
    ui->dataBaseTableView->setColumnWidth(0, 150);
}

ProductWindow::~ProductWindow(){
    delete ui;
}

void ProductWindow::on_findProductLineEdit_textChanged(){
    proxyModel->setFilterRegExp(QRegExp(ui->findProductLineEdit->text(), Qt::CaseInsensitive, QRegExp::FixedString));
    ui->dataBaseTableView->reset();
}

