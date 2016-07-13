#include "chosenproducttablemodel.h"
#include <QDebug>
#include <QDataStream>

ChosenProductsTableModel::ChosenProductsTableModel(): ProductsTableModel()
{
    productBaseHeaders.append("Ilość");
    productBaseHeaders.append("Cena");
    productBaseHeaders.append("Waga");
}

Qt::ItemFlags ChosenProductsTableModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    else
        return Qt::ItemIsDropEnabled;
}

QVariant ChosenProductsTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(role == Qt::DisplayRole){
            return productBase[index.row()][index.column()];
    }
    return QVariant();
}

bool ChosenProductsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        productBase[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool ChosenProductsTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    if (action == Qt::IgnoreAction)
      return true;

    if (!data->hasFormat("text/csv"))
      return false;

    QByteArray encodedData = data->data("text/csv");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QVector<QVector<QString> > lines;
    QStringList temp;

    int i = 0;

    while (!stream.atEnd()){
      stream >> temp;
      qDebug() << temp;
      lines.append( QVector<QString>());
      for(int j = 0; j < temp.count(); j++)
          lines[i].append(temp.at(j));
      i++;
    }
    // wstawka dla kolumny ilosc, cena i waga - w przyszlosci wyeliminowac tego potworka
    for(int i = 0; i < lines.count(); i++){
        lines[i].append("0");
        lines[i].append("0");
        lines[i].append("0");
    }
    int rows = lines.count();
    ///////////////////////////////////
    insertRows(0, rows, QModelIndex());
    foreach(QVector<QString> line, lines) {
      productBase.append(line);
      row++;
    }
    return true;
}

double ChosenProductsTableModel::getNutritionValue(int column, int row)
{
    return productBase[column][row].toDouble() * productBase[14][row].toDouble();
}

double ChosenProductsTableModel::getColumnNutritionValue(int column)
{
    double result = 0;
    for(int i = 0; i < productBase.count(); i++)
        result += productBase[i][column].toDouble() * productBase[i][14].toDouble();

    return result;
}
