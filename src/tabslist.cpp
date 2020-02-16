#include "tabslist.h"
#include <QKeyEvent>

TabsList::TabsList(QWidget * parent) : QListWidget(parent)
{
    setVisible(false);
    setSizeAdjustPolicy(QListWidget::AdjustToContents);
    connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
}

void TabsList::onItemClicked(QListWidgetItem * item)
{
    QVariant itemData = item->data(Qt::UserRole);
    emit itemClicked(itemData.toInt());
}

void TabsList::keyPressEvent(QKeyEvent *e)
{
    int code = e->key();
    if (code == Qt::Key_Return) {
        QList<QListWidgetItem *> selected = selectedItems();
        if (selected.size() > 0) {
            onItemClicked(selected.at(0));
            return;
        }
    }
    QListWidget::keyPressEvent(e);
}

void TabsList::addItem(QString str, int index)
{
    QListWidgetItem * newItem = new QListWidgetItem;
    QVariant itemData(index);
    newItem->setData(Qt::UserRole, itemData);
    newItem->setText(str);
    newItem->setIcon(QIcon(":/icons/item.png"));
    newItem->setToolTip(str);
    insertItem(count(), newItem);
}
