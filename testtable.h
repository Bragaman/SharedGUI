#ifndef TESTTABLE_H
#define TESTTABLE_H

#include "tablecontainerview.h"
#include <QTableWidgetItem>
#include <QHeaderView>


class TestTable : public TableContainerView
{
    Q_OBJECT
public:
    TestTable(QWidget *parent = nullptr);
    enum Columns {ID, NAME, COUNT};

    // BaseContainerView interface
public:
    void initView() override;

    // TableContainerView interface
private:
    void privateOnAddObject(const BaseDTO &object) override;
    void privateOnPatchObject(const BaseDTO &object) override;
    void privateOnRemoveObject(const BaseDTO &object) override;

    // TableContainerView interface
protected:
    QList<int> getSelectedIds() override;
};

#endif // TESTTABLE_H
