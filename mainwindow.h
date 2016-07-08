#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCloseEvent>
#include "productstablemodel.h"
#include "chosenproducttablemodel.h"
#include "chosenproductdelegate.h"
#include "productwindow.h"
#include "basemanagerwindow.h"
#include <QSortFilterProxyModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
     Ui::MainWindow *ui;

     ChosenProductsTableModel *chosenProductsModel;
     ChosenProductDelegate *delegate;
     ProductWindow *productWindow;
     BaseManagerWindow *baseManager;
     QString fileName;
     void initializeComponents();
     bool wantExit();

protected:
     void closeEvent(QCloseEvent *event);

public:
     explicit MainWindow(QWidget *parent = 0);
     ~MainWindow();

private slots:
    void on_countButton_clicked();
    void on_deleteLastButton_clicked();
    void on_cleanButton_clicked();
    void on_actionDodaj_produkt_triggered();
    void on_actionMenad_er_bazy_triggered();

    void on_actionZapisz_tabel_warto_ci_triggered();

    void on_actionZapisz_raport_triggered();

    void on_actionZapisz_triggered();

public slots:
    void fileNameSlot(QString fN);
};

#endif // MAINWINDOW_H
