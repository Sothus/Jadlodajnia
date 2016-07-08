#include "chosenproductdelegate.h"
#include <QSpinBox>
#include <QLineEdit>

ChosenProductDelegate::ChosenProductDelegate(QObject *parent):
    QStyledItemDelegate(parent) {}

QWidget *ChosenProductDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    if(index.column() == 14 || index.column() == 15 || index.column() == 16){
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setDecimals(2);
        editor->setMaximum(1000);
        editor->setSingleStep(0.01);
        return editor;
    }
    else return 0;
}

void ChosenProductDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();

    QDoubleSpinBox *lineEdit = static_cast<QDoubleSpinBox*>(editor);
    lineEdit->setValue(value.toDouble());

}

void ChosenProductDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    double value = spinBox->value();

    model->setData(index, QString::number(value, 'g', 6), Qt::EditRole);
}

void ChosenProductDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}


