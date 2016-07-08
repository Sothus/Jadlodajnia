#include "addproductdialog.h"
#include "ui_addproductdialog.h"
#include <qdebug>

AddProductDialog::AddProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}


void AddProductDialog::on_addButton_clicked()
{
    QStringList product;
    product.append(ui->nameEdit->text());
    product.append(QString::number(ui->caloriesSpinBox->value()));
    product.append(QString::number(ui->proteinSpinBox->value()));
    product.append(QString::number(ui->fatSpinBox->value()));
    product.append(QString::number(ui->carbohydratesSpinBox->value()));
    product.append(QString::number(ui->rughageSpinBox->value()));
    product.append(QString::number(ui->sodiumSpinBox->value()));
    product.append(QString::number(ui->potassiumSpinBox->value()));
    product.append(QString::number(ui->calciumSpinBox->value()));
    product.append(QString::number(ui->ironSpinBox->value()));
    product.append(QString::number(ui->magnessiumSpinBox->value()));
    product.append(QString::number(ui->vitASpinBox->value()));
    product.append(QString::number(ui->vitESpinBox->value()));
    product.append(QString::number(ui->vitCSpinBox->value()));
    emit addProductSignal(product);
    qDebug() << product;
}

