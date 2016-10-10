#include "testtable.h"
#include <QDebug>

TestTable::TestTable(QWidget *parent) : TableContainerView(parent)
{
    initView();
}

void TestTable::initView()
{
    setColumnCount(Columns::COUNT);

    setRowCount(0);

    setHorizontalHeaderLabels(QStringList()
                           << tr("id")
                           << tr("rule")
                           );


}
void TestTable::privateOnAddObject(const BaseDTO &object)
{
    const TestDTO &obj = dynamic_cast<const TestDTO &>(object);
    insertRow(0);
    setItem(0, Columns::ID, new QTableWidgetItem(QString::number(obj.id)));
    setItem(0, Columns::NAME, new QTableWidgetItem(obj.name));
}

void TestTable::privateOnPatchObject(const BaseDTO &object)
{
    auto obj = dynamic_cast<const TestDTO &>(object);
    auto items = findItems(QString::number(obj.id), Qt::MatchFixedString);
    int row = items.at(0)->row();
    item(row, Columns::NAME)->setText(obj.name);
}

void TestTable::privateOnRemoveObject(const BaseDTO &object)
{
    auto obj = dynamic_cast<const TestDTO &>(object);
    auto item = findItems(QString::number(obj.id), Qt::MatchFixedString);
    int row = item.at(0)->row();
    removeRow(row);
}

QList<int> TestTable::getSelectedIds()
{
    QList<int> result;
    auto items = selectedItems();
    foreach (auto item, items) {
        if (item->column() == Columns::ID) {
            result.append(item->text().toInt());
        }
    }

    return result;
}

