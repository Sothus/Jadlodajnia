#ifndef BASEMANAGERWINDOW_H
#define BASEMANAGERWINDOW_H

#include <QMainWindow>
#include "productstablemodel.h"
#include "addproductdialog.h"

namespace Ui {
class baseManagerWindow;
}

class BaseManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseManagerWindow(QString &filename,QWidget *parent = 0);
    ~BaseManagerWindow();

private slots:
    void on_addProductButton_clicked();

    void on_deleteProductButton_clicked();

    void on_saveButton_clicked();

    void on_saveAsButton_clicked();

public slots:
    void addProductSlot(QStringList product);

private:
    Ui::baseManagerWindow *ui;
    ProductsTableModel *basemodel;
    AddProductDialog *dialog;
    QString fileName;

};

#endif // BASEMANAGERWINDOW_H
