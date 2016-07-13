#ifndef CHOSENPRODUCTMODEL_H
#define CHOSENPRODUCTMODEL_H

#include "productstablemodel.h"
#include <QFlags>

class ChosenProductsTableModel : public ProductsTableModel
{
    Q_OBJECT
private:


public:
    ChosenProductsTableModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    double getNutritionValue(int column, int row);
    double getColumnNutritionValue(int column);

};

#endif // CHOSENPRODUCTMODEL_H
