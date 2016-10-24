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
    horizontalHeader()->setSectionResizeMode(Columns::ID, QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(Columns::NAME, QHeaderView::Stretch);


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

QString TestTable::getUnitDescription(int id)
{
    return QString::number(id);
}

bool TestTable::askToDelete(bool single, QList<int> ids)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    QString msg = "Are you sure you want to delete ";
    if (single)
        msgBox.setText(msg.append("item with id = %1?").arg(getUnitDescription(ids.at(0))));

    else
        msgBox.setText(msg.append("selected items (%1)?").arg(getUnitDescription(ids.size())));

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    msgBox.setButtonText(QMessageBox::No, tr("No"));

    return (msgBox.exec() == QMessageBox::Yes);
}

