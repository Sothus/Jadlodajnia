#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QStringListModel>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QTextTable>
#include <QDate>
#include <QTextTableFormat>
#include <QPrinter>
#include "productstablemodel.h"
#include "chosenproducttablemodel.h"
#include "chosenproductdelegate.h"
#include "basemanagerwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        chosenProductsModel(new ChosenProductsTableModel()),
        delegate(new ChosenProductDelegate())
{
    ui->setupUi(this);
    initializeComponents();
}

void MainWindow::initializeComponents(){
    setWindowTitle("Jadłospis");
    ui->chosenProductsTableView->setModel(chosenProductsModel);
    for(int i = 1; i <= 13; i++)
        ui->chosenProductsTableView->setColumnHidden(i, true);
    ui->chosenProductsTableView->verticalHeader()->hide();
    ui->chosenProductsTableView->setAcceptDrops(true);
    ui->chosenProductsTableView->setDropIndicatorShown(true);
    ui->chosenProductsTableView->setItemDelegate(delegate);
    ui->chosenProductsTableView->setColumnWidth(0,130);
    ui->chosenProductsTableView->setColumnWidth(1,20);
    ui->chosenProductsTableView->setColumnWidth(2,20);
}

bool MainWindow::wantExit()
{
    QMessageBox::StandardButton exit;
    exit = QMessageBox::warning(this, "Na pewno chcesz wyjść?","Aplikacja zostanie zamknięta\n", QMessageBox::Ok | QMessageBox::Cancel);
    if (exit == QMessageBox::Ok)
        return true;
    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(wantExit())
        exit(0);
    else
        event->ignore();
}

void MainWindow::on_countButton_clicked(){
    ui->caloriesEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(1)));
    ui->proteinEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(2)));
    ui->fatEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(3)));
    ui->carbohydratesEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(4)));
    ui->roughageEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(5)));
    ui->sodiumEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(6)));
    ui->potassiumEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(7)));
    ui->calciumEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(8)));
    ui->ironEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(9)));
    ui->magnessiumEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(01)));
    ui->vitAEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(11)));
    ui->vitEEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(12)));
    ui->vitCEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(13)));
    ui->sumPersonEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(15)));
    ui->perPersonEdit->setText(QString::number(chosenProductsModel->getColumnNutritionValue(15)/(ui->studentNumberEdit->text().toInt()+ui->teacherNumberEdit->text().toInt()+ui->otherNumberEdit->text().toInt())));
}

void MainWindow::on_deleteLastButton_clicked(){
    if(chosenProductsModel->rowCount()){
        chosenProductsModel->removeRow(chosenProductsModel->rowCount());
        ui->chosenProductsTableView->reset();
    }
}

void MainWindow::on_cleanButton_clicked(){
    if(chosenProductsModel->rowCount()){
        chosenProductsModel->removeRows(1,chosenProductsModel->rowCount());
        ui->chosenProductsTableView->reset();
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionDodaj_produkt_triggered(){
    productWindow->show();
}

void MainWindow::on_actionMenad_er_bazy_triggered(){
    baseManager->show();
}

void MainWindow::fileNameSlot(QString fN){
    fileName = fN;
    productWindow = new ProductWindow(fileName);
    baseManager = new BaseManagerWindow(fileName);
}

void MainWindow::on_actionZapisz_tabel_warto_ci_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz...", "/c:/", "Plik PDF (*.pdf)");
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fileName + ".pdf");



    QModelIndex* position = new QModelIndex();
    QModelIndex* position2 = new QModelIndex();
    QTextDocument *tablesPage = new QTextDocument();
    QTextCursor *cursor2 = new QTextCursor(tablesPage);

    cursor2->insertText("obiad nr " + ui->dinnerNumberEdit->text() + "\t" + QDate::currentDate().toString() + "\n");
    cursor2->insertText("osob\t" + QString::number(ui->studentNumberEdit->text().toInt()
                                                     + ui->teacherNumberEdit->text().toInt()
                                                     + ui->otherNumberEdit->text().toInt()) );

    QTextTable* tab = cursor2->insertTable(chosenProductsModel->rowCount() + 4, 17);
    tab->mergeCells(0,0,2,1);//2
    tab->mergeCells(0,1,2,1);//3
    tab->mergeCells(0,2,1,3);//A
    tab->mergeCells(0,5,1,3);//4
    tab->mergeCells(0,8,1,3);//5
    tab->mergeCells(0,11,1,3);//6
    tab->mergeCells(0,14,1,3);//7
    tab->mergeCells(chosenProductsModel->rowCount() + 2,0,2,1);//B
    tab->mergeCells(chosenProductsModel->rowCount() + 2,1,2,3);//14
    tab->mergeCells(chosenProductsModel->rowCount() + 2,5,2,2);//13
    tab->mergeCells(chosenProductsModel->rowCount() + 2,8,2,2);//12
    tab->mergeCells(chosenProductsModel->rowCount() + 2,11,2,2);//11
    tab->mergeCells(chosenProductsModel->rowCount() + 2,14,2,2);//10

    cursor2->insertText("Składniki:");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("waga w kg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("kcal");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("białko");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("tłuszcz");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("węglowodany");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("błonnik");
    cursor2->movePosition(QTextCursor::NextCell);

    for(int i = 0; i < 5; i++){
        cursor2->insertText("w 100g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w 1000g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w całym posiłku");
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < chosenProductsModel->rowCount(); i++){
        *position = ui->chosenProductsTableView->model()->index(i,0);
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,16); //trzeba dodać kolumnę kg!
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);

        for(int j = 0; j < 5; j++){
            *position = ui->chosenProductsTableView->model()->index(i, (j + 1));
            cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
            cursor2->movePosition(QTextCursor::NextCell);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position).toDouble() * 10));
            cursor2->movePosition(QTextCursor::NextCell);
            *position2 = ui->chosenProductsTableView->model()->index(i, 14);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position2).toDouble() * ui->chosenProductsTableView->model()->data(*position).toDouble()));
            cursor2->movePosition(QTextCursor::NextCell);
        }
    }

    cursor2->insertText("RAZEM NA OSOBĘ");
    cursor2->movePosition(QTextCursor::NextCell);

    for(int i = 0; i < 5; i++){
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+1)));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < 5; i++){
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+1)/(ui->studentNumberEdit->text().toInt()+ui->teacherNumberEdit->text().toInt()+ui->otherNumberEdit->text().toInt())));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    cursor2->movePosition(QTextCursor::NextBlock);
    cursor2->insertText("\n");
    tab = cursor2->insertTable(chosenProductsModel->rowCount() + 4, 17);

    tab->mergeCells(0,0,2,1);//1.1
    tab->mergeCells(0,1,2,1);//1.2
    tab->mergeCells(0,2,1,3);//1.3
    tab->mergeCells(0,5,1,3);//1.4
    tab->mergeCells(0,8,1,3);//1.5
    tab->mergeCells(0,11,1,3);//1.6
    tab->mergeCells(0,14,1,3);//1.7
    tab->mergeCells(chosenProductsModel->rowCount() + 2,0,2,1);//1.11
    tab->mergeCells(chosenProductsModel->rowCount() + 2,1,2,3);//1.12
    tab->mergeCells(chosenProductsModel->rowCount() + 2,5,2,2);//1.14
    tab->mergeCells(chosenProductsModel->rowCount() + 2,8,2,2);//1.15
    tab->mergeCells(chosenProductsModel->rowCount() + 2,11,2,2);//1.16
    tab->mergeCells(chosenProductsModel->rowCount() + 2,14,2,2);//1.17

    cursor2->insertText("Składniki:");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("waga w kg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Sód mg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Potas mg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Wapń mg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Żelazo mg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Magnez mg");
    cursor2->movePosition(QTextCursor::NextCell);

    for(int i = 0; i < 5; i++){
        cursor2->insertText("w 100g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w 1000g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w całym posiłku");
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < chosenProductsModel->rowCount(); i++){
        *position = ui->chosenProductsTableView->model()->index(i,0);
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,16); //trzeba dodać kolumnę kg!
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);

        for(int j = 0; j < 5; j++){
            *position = ui->chosenProductsTableView->model()->index(i, (j + 6));
            cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
            cursor2->movePosition(QTextCursor::NextCell);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position).toDouble() * 10));
            cursor2->movePosition(QTextCursor::NextCell);
            *position2 = ui->chosenProductsTableView->model()->index(i, 14);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position2).toDouble() * ui->chosenProductsTableView->model()->data(*position).toDouble()));
            cursor2->movePosition(QTextCursor::NextCell);
        }
    }

    cursor2->insertText("RAZEM NA OSOBĘ");
    cursor2->movePosition(QTextCursor::NextCell);

    for(int i = 0; i < 5; i++){
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+6)));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < 5; i++){
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+6)/(ui->studentNumberEdit->text().toInt()+ui->teacherNumberEdit->text().toInt()+ui->otherNumberEdit->text().toInt())));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    cursor2->movePosition(QTextCursor::NextBlock);
    cursor2->insertText("\n");
    tab = cursor2->insertTable(ui->chosenProductsTableView->model()->rowCount() + 4, 11);

    tab->mergeCells(0,0,2,1);//1.1
    tab->mergeCells(0,1,2,1);//1.2
    tab->mergeCells(0,2,1,3);//1.8
    tab->mergeCells(0,5,1,3);//1.9
    tab->mergeCells(0,8,1,3);//1.10
    tab->mergeCells(chosenProductsModel->rowCount() + 2,0,2,1);//1.11
    tab->mergeCells(chosenProductsModel->rowCount() + 2,1,2,3);//1.12
    tab->mergeCells(chosenProductsModel->rowCount() + 2,2,2,2);//1.18
    tab->mergeCells(chosenProductsModel->rowCount() + 2,5,2,2);//1.19
    tab->mergeCells(chosenProductsModel->rowCount() + 2,8,2,2);//1.20

    cursor2->insertText("Składniki:");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("waga w kg");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Witamina A");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Witamina E");
    cursor2->movePosition(QTextCursor::NextCell);
    cursor2->insertText("Witamina C");
    cursor2->movePosition(QTextCursor::NextCell);


    for(int i = 0; i < 3; i++){
        cursor2->insertText("w 100g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w 1000g");
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText("w całym posiłku");
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < chosenProductsModel->rowCount(); i++){
        *position = ui->chosenProductsTableView->model()->index(i,0);
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,16); //trzeba dodać kolumnę kg!
        cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor2->movePosition(QTextCursor::NextCell);

        for(int j = 0; j < 3; j++){
            *position = ui->chosenProductsTableView->model()->index(i, (j + 11));
            cursor2->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
            cursor2->movePosition(QTextCursor::NextCell);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position).toDouble() * 10));
            cursor2->movePosition(QTextCursor::NextCell);
            *position2 = ui->chosenProductsTableView->model()->index(i, 14);
            cursor2->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position2).toDouble() * ui->chosenProductsTableView->model()->data(*position).toDouble()));
            cursor2->movePosition(QTextCursor::NextCell);
        }
    }

    cursor2->insertText("RAZEM NA OSOBĘ");
    cursor2->movePosition(QTextCursor::NextCell);

    for(int i = 0; i < 3; i++){
        cursor2->movePosition(QTextCursor::NextCell);
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+11)));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    for(int i = 0; i < 3; i++){
        cursor2->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(i+11)/(ui->studentNumberEdit->text().toInt()+ui->teacherNumberEdit->text().toInt()+ui->otherNumberEdit->text().toInt())));
        cursor2->movePosition(QTextCursor::NextCell);
    }

    tablesPage->print(&printer);
}

void MainWindow::on_actionZapisz_raport_triggered()
{
    qDebug() << ui->dinnerTextEdit->toPlainText();
    QString rawRecipe = ui->dinnerTextEdit->toPlainText();
    QStringList recipe = rawRecipe.split("\n");
    QTextDocument* doc = new QTextDocument();

    QTextCursor* cursor = new QTextCursor(doc);
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setBorderStyle(QTextTableFormat::BorderStyle_Solid);
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(0);


    cursor->insertTable(1,1,tableFormat);
    cursor->insertText("Raporty żywieniowy na dzień......." + QDate::currentDate().toString());
    cursor->movePosition(QTextCursor::NextBlock);
    cursor->insertText("\n\n");

    tableFormat.setBorderStyle(QTextTableFormat::BorderStyle_Outset);
    cursor->insertTable(recipe.count() + 2 ,1, tableFormat);
    cursor->insertText("JADŁOSPIS");
    cursor->movePosition(QTextCursor::NextCell);
    for(int i = 0; i < recipe.count(); i++){
        cursor->insertText(recipe[i]);
        cursor->movePosition(QTextCursor::NextCell);
    }
    cursor->movePosition(QTextCursor::NextBlock);


    cursor->movePosition(QTextCursor::NextBlock);
    cursor->insertText("\n\n");
    QTextTable* tab = cursor->insertTable(6,2,tableFormat);
    tab->mergeCells(0,0,1,2);
    cursor->insertText("Liczba osób korzystających z wyżywienia");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("OBIAD");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("uczniów");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(ui->studentNumberEdit->text());
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("nauczycieli");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(ui->teacherNumberEdit->text());
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("innych osób");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(ui->otherNumberEdit->text());
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("RAZEM");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(QString::number(ui->studentNumberEdit->text().toInt()
                                       + ui->teacherNumberEdit->text().toInt()
                                       + ui->otherNumberEdit->text().toInt()));
    cursor->movePosition(QTextCursor::NextBlock);
    cursor->insertText("\n\n");

    qDebug() << ui->chosenProductsTableView->model()->rowCount() + 1;
    tab = cursor->insertTable(ui->chosenProductsTableView->model()->rowCount() + 3, 6,tableFormat);
    tab->mergeCells(ui->chosenProductsTableView->model()->rowCount() + 2, 0, 1, 6);
    tab->mergeCells(ui->chosenProductsTableView->model()->rowCount() + 1, 0, 1, 5);

    cursor->insertText("Lp.");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("Nazwa produktu");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("jedn.miary");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("Ilość");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("cena");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("wartość");
    cursor->movePosition(QTextCursor::NextCell);

    QModelIndex* position = new QModelIndex();
    QModelIndex* position2 = new QModelIndex();

    for(int i = 0; i < ui->chosenProductsTableView->model()->rowCount(); i++){
        cursor->insertText(QString::number(i + 1) + ".");
        cursor->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,0);
        cursor->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,16);
        cursor->insertText("wartość");
        cursor->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,14);
        cursor->insertText(ui->chosenProductsTableView->model()->data(*position).toString());
        cursor->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,15);
        cursor->insertText(ui->chosenProductsTableView->model()->data(*position).toString() + " zł");
        cursor->movePosition(QTextCursor::NextCell);
        *position = ui->chosenProductsTableView->model()->index(i,14);
        *position2 = ui->chosenProductsTableView->model()->index(i,15);
        cursor->insertText(QString::number(ui->chosenProductsTableView->model()->data(*position).toDouble()
                           * ui->chosenProductsTableView->model()->data(*position2).toDouble()) + " zł");
        cursor->movePosition(QTextCursor::NextCell);
    }

    cursor->insertText("suma");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(15)) + " zł"); //cena
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("RAPORT ZAKOŃCZONO POZYCJĄ NR " + QString::number(ui->chosenProductsTableView->model()->rowCount()));
    cursor->movePosition(QTextCursor::NextBlock);

    cursor->insertTable(2,2,tableFormat);
    cursor->insertText("RAZEM");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(15)) + " zł");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText("Średni koszt dzienny na jedną osobę");
    cursor->movePosition(QTextCursor::NextCell);
    cursor->insertText(QString::number(chosenProductsModel->getColumnNutritionValue(15)/(ui->studentNumberEdit->text().toInt()+ui->teacherNumberEdit->text().toInt()+ui->otherNumberEdit->text().toInt())));

    cursor->movePosition(QTextCursor::NextBlock);
    cursor->insertText("\n\n");
    cursor->insertText("Magazyn wyda \t\tzapisano w kart.magaz\t\tProdukty otrzymałam:"
                       "\n\n\n\t\tpodpis intendenta\t\tpodpis kucharki");

    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz...", "/c:/", "Plik PDF (*.pdf)");
    QPrinter printer;
    printer.setOutputFileName(fileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc->print(&printer);
}

void MainWindow::on_actionZapisz_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Zapisz jako..."),tr("/c:/"),tr("Pliki tekstowe (*.csv)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream(&file);
    QString data2file;
    QModelIndex *index = new QModelIndex;


    for(int i = 0; i < chosenProductsModel->rowCount(); i++){
        for(int j = 0; j < chosenProductsModel->columnCount(); j++){
            *index = chosenProductsModel->index(i,j);
            data2file += chosenProductsModel->data(*index, Qt::DisplayRole).toString() + ",";
        }
        data2file += "\n";
    }
    stream << data2file;

    file.close();
    delete index;
}
