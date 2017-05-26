#ifndef TABLEWIDGETWITHDEFAULTMENU_H
#define TABLEWIDGETWITHDEFAULTMENU_H

#include <QVBoxLayout>
#include <QTableWidget>
#include <QAction>
#include <QWidgetAction>
#include <QMenu>
#include <QHeaderView>

#include "tablewidgetwithmenu.h"


class BaseDTO;

class TableWidgetWithDefaultMenu : public TableWidgetWithMenu
{
    Q_OBJECT
public:
    TableWidgetWithDefaultMenu(QWidget* parent = nullptr);

    void onAddObject(const BaseDTO &object);
    void onPatchObject(const BaseDTO &object);
    void onRemoveObject(const BaseDTO &object);

    void deleteSelectedObjects();

signals:
    void openEditor(int id);
    void removeObject(int id);
    void removeObjects(const QList<int> ids);

protected:
    bool isSorted;

    virtual QString getUnitDescription(int id) = 0;

    virtual bool askToDelete(bool single, QList<int> ids) = 0;

    QString msgOnDeleteOne;
    QString msgOnDeleteMore;

    QString containedUnit;
    QString containedUnits;

    virtual QList<QWidgetAction *> getPossibleActions();

    virtual void initActions();

private:
    virtual void privateOnAddObject(const BaseDTO &object) = 0;
    virtual void privateOnPatchObject(const BaseDTO &object ) = 0;
    virtual void privateOnRemoveObject(const BaseDTO &object ) = 0;

    QWidgetAction *actionAdd = nullptr;
    QWidgetAction *actionPatch = nullptr;
    QWidgetAction *actionRemove = nullptr;
};

#endif // TABLEWIDGETWITHDEFAULTMENU_H
