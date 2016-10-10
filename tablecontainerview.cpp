#include "tablecontainerview.h"
#include <QDebug>
TableContainerView::TableContainerView(QWidget *parent) :BaseContainerView(parent)
{
    layout = new QVBoxLayout();
    table = new QTableWidget();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    layout->addWidget(table);
    layout->setMargin(1);
    setLayout(layout);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table, &QTableWidget::customContextMenuRequested, this, &TableContainerView::showContextMenu);
}

TableContainerView::~TableContainerView()
{

}

QTableWidget *TableContainerView::getTable() const
{
    return table;
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
        connect(&actionRemove, &QAction::triggered, this, [ids, this](){
            foreach (int id, ids )
                emit removeObject(id);
        });
    }
    contextMenu.exec(getTable()->mapToGlobal(point));
}


void TableContainerView::onGotObjects(QList<BaseDTO> listObjects)
{
    foreach (auto object, listObjects)
        onAddObject(object);
}

void TableContainerView::onAddObject(const BaseDTO &object)
{
    table->setSortingEnabled(false);
    privateOnAddObject(object);
    table->setSortingEnabled(isSorted);
}

void TableContainerView::onPatchObject(const BaseDTO &object)
{
    table->setSortingEnabled(false);
    privateOnPatchObject(object);
    table->setSortingEnabled(isSorted);
}

void TableContainerView::onRemoveObject(const BaseDTO &object)
{
    table->setSortingEnabled(false);
    privateOnRemoveObject(object);
    table->setSortingEnabled(isSorted);
}
