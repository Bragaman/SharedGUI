#include "tablecontainerview.h"
#include "QPushButton"

TableContainerView::TableContainerView(QWidget *parent) : QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTableWidget::customContextMenuRequested,
            this, &TableContainerView::showContextMenu);

    msgOnDeleteOne = tr("Are you sure you want to delete %1 %2?");
    msgOnDeleteMore = tr("Are you sure you want to delete selected %1 (%2)?");

    menu = nullptr;
}

TableContainerView::~TableContainerView()
{
}

QWidgetAction * TableContainerView::createActionWidget(const QString &name, const QString &objName)
{
    QWidgetAction *actionWidget = new QWidgetAction(this);
//    actionWidget->setObjectName(objName);
    QPushButton *btnIcon = new QPushButton(name);
    btnIcon->setObjectName(objName);
    connect(btnIcon, &QPushButton::clicked, actionWidget, &QWidgetAction::trigger);
    actionWidget->setDefaultWidget(btnIcon);
    return actionWidget;
}

void TableContainerView::showContextMenu(const QPoint &point)
{
    auto listCurId = getSelectedIds();
    menu = new QMenu(tr("Context menu"), this);
//    menu->setObjectName("contextMenu");
    auto actionAdd = createActionWidget(tr("Add"), "actionAdd");
    connect(actionAdd, &QAction::triggered, this, [=](){
        emit openEditor(-1);
        menu->close();
    });
    menu->addAction(actionAdd);

    if (!listCurId.isEmpty()) {
        if (listCurId.size() == 1) {
            auto actionPatch = createActionWidget(tr("Patch"), "actionPatch");
            connect(actionPatch, &QAction::triggered, this, [this, listCurId](){
                emit openEditor(listCurId.at(0));
                menu->close();

            });
            menu->addAction(actionPatch);
        }

        auto actionRemove = createActionWidget(tr("Remove"), "actionRemove");
        connect(actionRemove, &QAction::triggered, this, &TableContainerView::deleteSelectedObjects);
        menu->addAction(actionRemove);
    }

    menu->exec(mapToGlobal(point));
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
    bool single = ids.size() == 1;
    bool userAllowed = askToDelete(single, ids);
    if (single && userAllowed) {
        emit removeObject(ids.at(0));
    } else if (!single && userAllowed) {
        clearSelection();
        emit removeObjects(ids);
    }
    if (menu)
        menu->close();
}

