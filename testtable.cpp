#include "testtable.h"
#include <QDebug>

TestTable::TestTable(QWidget *parent) : TableContainerView(parent)
{
    initView();
}

void TestTable::initView()
{
    getTable()->setColumnCount(Columns::COUNT);

    getTable()->setRowCount(0);

    getTable()->setHorizontalHeaderLabels(QStringList()
                           << tr("id")
                           << tr("rule")
                           );


}
void TestTable::privateOnAddObject(const BaseDTO &object)
{
    const TestDTO &obj = dynamic_cast<const TestDTO &>(object);
    getTable()->insertRow(0);
    getTable()->setItem(0, Columns::ID, new QTableWidgetItem(QString::number(obj.id)));
    getTable()->setItem(0, Columns::NAME, new QTableWidgetItem(obj.name));
}

void TestTable::privateOnPatchObject(const BaseDTO &object)
{
    auto obj = dynamic_cast<const TestDTO &>(object);
    auto item = getTable()->findItems(QString::number(obj.id), Qt::MatchFixedString);
    int row = item.at(0)->row();
    getTable()->item(row, Columns::NAME)->setText(obj.name);
}

void TestTable::privateOnRemoveObject(const BaseDTO &object)
{
    auto obj = dynamic_cast<const TestDTO &>(object);
    auto item = getTable()->findItems(QString::number(obj.id), Qt::MatchFixedString);
    int row = item.at(0)->row();
    getTable()->removeRow(row);
}

QList<int> TestTable::getSelectedIds()
{
    QList<int> result;
    auto items = getTable()->selectedItems();
    foreach (auto item, items) {
        if (item->column() == Columns::ID) {
            result.append(item->text().toInt());
        }
    }

    return result;
}
