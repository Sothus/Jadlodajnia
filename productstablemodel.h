#ifndef PRODUCTSTABLEMODEL_H
#define PRODUCTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QFlags>
#include <QModelIndex>
#include <QMimeData>
#include <QTextStream>

class ProductsTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    void createHeaders(QTextStream &stream);
    void createData(QTextStream &stream);
    QList<int> generateRows(QModelIndexList indexes) const; //wymaga uwagi (argumenty)
    QMimeData *throw2mime(QList<int> rows) const; // ta tez
public:
    ProductsTableModel();
    ProductsTableModel(QString filename);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    double getNumber(int row, int column) const;
    void addProduct(QStringList &product);
    void removeLastRow();
    void save2File(QString &fN);
protected:
    QVector<QVector <QString> > productBase;
    QStringList productBaseHeaders;
};

#endif // PRODUCTSTABLEMODEL_H
