#include "tablewidgetwithmenu.h"

TableWidgetWithMenu::TableWidgetWithMenu(QWidget *parent) : QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTableWidget::customContextMenuRequested,
            this, &TableWidgetWithMenu::showContextMenu);
}

void TableWidgetWithMenu::showContextMenu(const QPoint &point)
{
    QMenu menu(tr("Context menu"), this);
    auto actionsList = getPossibleActions();
    foreach (auto action, actionsList) {
        connect(action, &QWidgetAction::triggered, &menu, &QMenu::hide);
        menu.addAction(action);
    }
    menu.exec(QTableWidget::mapToGlobal(point));
}


QWidgetAction *TableWidgetWithMenu::createActionWidget(
        const QString &name, const QString &objName)
{
    QWidgetAction *actionWidget = new QWidgetAction(this);
    QPushButton *btnIcon = new QPushButton(name);
    btnIcon->setObjectName(objName);
    connect(btnIcon, &QPushButton::clicked, actionWidget, &QWidgetAction::trigger);
    actionWidget->setDefaultWidget(btnIcon);
    return actionWidget;
}
