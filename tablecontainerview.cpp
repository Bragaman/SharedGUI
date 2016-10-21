#include "tablecontainerview.h"

TableContainerView::TableContainerView(QWidget *parent) : QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTableWidget::customContextMenuRequested,
            this, &TableContainerView::showContextMenu);

    msgOnDeleteOne = tr("Are you sure you want to delete %1 %2?");
    msgOnDeleteMore = tr("Are you sure you want to delete selected %1 (%2)?");
}

TableContainerView::~TableContainerView()
{
}

void TableContainerView::showContextMenu(const QPoint &point)
{
    auto ids = getSelectedIds();
    QMenu contextMenu(tr("Context menu"), this);

    QAction actionAdd("add", this);
    contextMenu.addAction(&actionAdd);
    connect(&actionAdd, &QAction::triggered, this, [=](){
        emit openEditor(-1);
    });

    QAction actionPatch("patch", this);
    if (ids.size() == 1) {
        contextMenu.addAction(&actionPatch);
        connect(&actionPatch, &QAction::triggered, this, [ids, this](){
            emit openEditor(ids.at(0));
        });
    }

    QAction actionRemove("remove", this);
    if (!ids.isEmpty()) {
        contextMenu.addAction(&actionRemove);
        connect(&actionRemove, &QAction::triggered, this, &TableContainerView::deleteSelectedObjects);
    }
    contextMenu.exec(mapToGlobal(point));
}

void TableContainerView::onAddObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnAddObject(object);
    setSortingEnabled(isSorted);
}

void TableContainerView::onPatchObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnPatchObject(object);
    setSortingEnabled(isSorted);
}

void TableContainerView::onRemoveObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnRemoveObject(object);
    setSortingEnabled(isSorted);
}

void TableContainerView::deleteSelectedObjects()
{
    auto ids = getSelectedIds();
    if (ids.size() == 1) {
        if (WarningsHandler::showInfoBoxYesNo(msgOnDeleteOne.arg(containedUnit).arg(getUnitDescription(ids.at(0)))))
            emit removeObject(ids.at(0));
    } else {
            if (WarningsHandler::showInfoBoxYesNo(msgOnDeleteMore.arg(containedUnits).arg(ids.count()))) {
                clearSelection();
                emit removeObjects(ids);
            }
    }
}

