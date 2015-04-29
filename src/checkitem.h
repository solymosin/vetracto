#ifndef CHECKITEM_H
#define CHECKITEM_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>

class checkItem : public QItemDelegate
{
    Q_OBJECT

public:
    checkItem(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor) const;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QStringList iLst;



};

#endif // CHECKITEM_H
