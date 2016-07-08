#include "productstablemodel.h"
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QModelIndex>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QTextStream>


ProductsTableModel::ProductsTableModel(){
    productBaseHeaders << "Produkt" << "Kcal" << "Białko" << "Tłuszcz" << "Węglowodany" << "Błonnik"
          << "Sód" << "Potas" << "Wapń" << "Żelazo" << "Magnez" << "Witamina A" << "Witamina E" << "Witamina C";
}


ProductsTableModel::ProductsTableModel(QString filename){
    QFile in(filename);

    in.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&in);

    createHeaders(stream);
    createData(stream);
    in.close();
}

void ProductsTableModel::createHeaders(QTextStream &stream){
    QString temp;

    temp = stream.readLine();
    productBaseHeaders = temp.split(",");
}

void ProductsTableModel::createData(QTextStream &stream){
    QString temp;
    QStringList list;
    int i = 0;

    while(!stream.atEnd()){
        temp = stream.readLine();
        list = temp.split(",");
        productBase.append(QVector<QString>());
        for(int j = 0; j < list.count(); j++)
            productBase[i].append(list.at(j));
        i++;
    }
}

int ProductsTableModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return productBase.count();
}

int ProductsTableModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return productBaseHeaders.count();
}

QVariant ProductsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            return productBaseHeaders[section];
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant ProductsTableModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QVariant();
    if(role == Qt::DisplayRole){
            return productBase[index.row()][index.column()];
    }
    return QVariant();
}

Qt::ItemFlags ProductsTableModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else
        return QAbstractItemModel::flags(index);
}

QStringList ProductsTableModel::mimeTypes() const
{
  QStringList types;
  types << "text/csv";
  return types;
}

QMimeData *ProductsTableModel::mimeData(const QModelIndexList &indexes) const{    
    return throw2mime(generateRows(indexes));
}

QList<int> ProductsTableModel::generateRows(QModelIndexList indexes) const{
    QList<int> rows;
    foreach (QModelIndex index, indexes)
      if (index.isValid())
        if (!rows.contains(index.row()))
          rows += index.row();
    return rows;
}

QMimeData *ProductsTableModel::throw2mime(QList<int> rows)const{
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    QMimeData* data = new QMimeData;
    foreach(int row, rows)
        stream << productBase[row];
    data->setData("text/csv", encodedData);
    return data;
}



bool ProductsTableModel::insertRows(int row, int count,
                    const QModelIndex & parent){
  Q_UNUSED(parent);
  beginInsertRows(QModelIndex(),row , row + count - 1);
  endInsertRows();
  return true;
}

bool ProductsTableModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(),row - 1, row - 1);
    productBase.removeLast();
    endRemoveRows();
    return true;
}

bool ProductsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(),row - 1, row + count - 2);
    productBase.erase(productBase.begin(),productBase.end());
    endRemoveRows();
    return true;
}

double ProductsTableModel::getNumber(int row, int column) const{
    QString temp = productBase[row][column];
    double result = temp.toDouble();
    return result;
}

void ProductsTableModel::addProduct(QStringList &product)
{
    qDebug() << "i jestesmy w addProduct" ;
    insertRow(productBase.count()-1);
    productBase.append(QVector<QString>());
    for(int i = 0; i < product.length(); i++)
        productBase.last().append(product[i]);
    qDebug() << productBase.last();
}

void ProductsTableModel::removeLastRow()
{
    if(productBase.count() > 0)
        removeRow(productBase.count());
}

void ProductsTableModel::save2File(QString &fN)
{
    QString fileName = fN;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream(&file);
    QString data2file;
    QModelIndex *index = new QModelIndex;

    for(int i = 0; i < productBaseHeaders.count(); i++)
        data2file += productBaseHeaders[i] + ",";

    data2file += "\n";

    for(int i = 0; i < productBase.count(); i++){
        for(int j = 0; j < productBase[0].count(); j++){
            data2file += productBase[i][j] + ",";
        }
        data2file += "\n";
    }
    stream << data2file;

    file.close();
    delete index;
}
