#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = 0);
    ~startDialog();

private slots:


    void on_customButton_clicked();

    void on_defaultButton_clicked();

signals:
    void fileNameSignal(QString fN);

private:
    Ui::startDialog *ui;
};

#endif // STARTDIALOG_H
