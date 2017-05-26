#include "tablewidgetwithdefaultmenu.h"
#include "QPushButton"

TableWidgetWithDefaultMenu::TableWidgetWithDefaultMenu(QWidget *parent) : TableWidgetWithMenu(parent)
{
    msgOnDeleteOne = tr("Are you sure you want to delete %1 %2?");
    msgOnDeleteMore = tr("Are you sure you want to delete selected %1 (%2)?");

    initActions();
}

void TableWidgetWithDefaultMenu::onAddObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnAddObject(object);
    setSortingEnabled(isSorted);
}

void TableWidgetWithDefaultMenu::onPatchObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnPatchObject(object);
    setSortingEnabled(isSorted);
}

void TableWidgetWithDefaultMenu::onRemoveObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnRemoveObject(object);
    setSortingEnabled(isSorted);
}

void TableWidgetWithDefaultMenu::deleteSelectedObjects()
{
    auto ids = getSelectedIds();
    if (ids.empty())
        return;

    bool single = ids.size() == 1;
    bool userAllowed = askToDelete(single, ids);
    if (single && userAllowed) {
        emit removeObject(ids.at(0));
    } else if (!single && userAllowed) {
        clearSelection();
        emit removeObjects(ids);
    }
}

QList<QWidgetAction *> TableWidgetWithDefaultMenu::getPossibleActions()
{
    QList<QWidgetAction *>possibleActions;
    possibleActions.append(actionAdd);

    auto listCurId = getSelectedIds();
    if (!listCurId.isEmpty()) {
        if (listCurId.size() == 1) {
            possibleActions.append(actionPatch);
        }

        possibleActions.append(actionRemove);
    }
    return possibleActions;
}

void TableWidgetWithDefaultMenu::initActions()
{
    actionAdd = createActionWidget(tr("Add"), "actionAdd");
    connect(actionAdd, &QAction::triggered, this, [=](){
        emit openEditor(-1);
    });

    actionPatch = createActionWidget(tr("Patch"), "actionPatch");
    connect(actionPatch, &QAction::triggered, this, [this](){
        emit openEditor(getSelectedIds().at(0));
    });

    actionRemove = createActionWidget(tr("Remove"), "actionRemove");
    connect(actionRemove, &QAction::triggered, this,
            &TableWidgetWithDefaultMenu::deleteSelectedObjects);
}
