#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = 0);
    ~AddProductDialog();

private slots:

    void on_addButton_clicked();


private:
    Ui::AddProductDialog *ui;

signals:
    void addProductSignal(QStringList &product);
};

#endif // ADDPRODUCTDIALOG_H
