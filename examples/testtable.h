#ifndef TESTTABLE_H
#define TESTTABLE_H

#include <tablewidgetwithdefaultmenu.h>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include "basedto.h"


class TestTable : public TableWidgetWithDefaultMenu
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

    QString getUnitDescription(int id);
    bool askToDelete(bool single, QList<int> ids);
};

#endif // TESTTABLE_H
