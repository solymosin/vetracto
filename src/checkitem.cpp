
#include <QtGui>
#include <QCheckBox>

#include "checkitem.h"

checkItem::checkItem(QObject *parent): QItemDelegate(parent)
{

}

void checkItem::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}


QWidget *checkItem::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QCheckBox *cBox = new QCheckBox(parent);
//    cBox->addItem("");
//    foreach(QString s, iLst){
//        cBox->addItem(s);
//    }
    return cBox;
}

void checkItem::setEditorData(QWidget *editor) const
{
//void fTypSel::setEditorData(QWidget *editor, const QModelIndex &index) const
//    int value = index.model()->data(index, Qt::EditRole).toInt();
//
//    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
//    spinBox->setValue(value);

    QCheckBox *cBox = static_cast<QCheckBox*>(editor);
    cBox->setChecked(false);
//    cBox->setCurrentIndex(0);
}

void checkItem::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *cBox = static_cast<QCheckBox*>(editor);
    model->setData(index, cBox->isChecked(), Qt::EditRole);
}


