#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

#include <QMainWindow>
#include <productstablemodel.h>
#include <QSortFilterProxyModel>

namespace Ui {
class ProductWindow;
}

class ProductWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::ProductWindow *ui;
    ProductsTableModel *baseProductsModel;
    QSortFilterProxyModel *proxyModel;

public:
    explicit ProductWindow(QString& fileName, QWidget *parent = 0);
    ~ProductWindow();

private slots:
    void on_findProductLineEdit_textChanged();
};

#endif // PRODUCTWINDOW_H
