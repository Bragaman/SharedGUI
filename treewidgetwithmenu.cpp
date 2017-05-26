#include "treewidgetwithmenu.h"

TreeWidgetWithMenu::TreeWidgetWithMenu(QWidget *parent) : QTreeWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeWidget::customContextMenuRequested,
            this, &TreeWidgetWithMenu::showContextMenu);
}

QWidgetAction *TreeWidgetWithMenu::createActionWidget(
        const QString &name, const QString &objName)
{
    QWidgetAction *actionWidget = new QWidgetAction(this);
    QPushButton *btnIcon = new QPushButton(name);
    btnIcon->setObjectName(objName);
    connect(btnIcon, &QPushButton::clicked, actionWidget, &QWidgetAction::trigger);
    actionWidget->setDefaultWidget(btnIcon);
    return actionWidget;
}

QList<QWidgetAction *> TreeWidgetWithMenu::getPossibleTopActions()
{
    return QList<QWidgetAction *>();
}

QList<int> TreeWidgetWithMenu::getSelectedTopIds()
{
    return QList<int>();
}

void TreeWidgetWithMenu::showContextMenu(const QPoint &point)
{
    QMenu menu(tr("Context menu"), this);
    QList<QWidgetAction *> actionsList = getPossibleActions();

    if (hasMenuSections) { //maybe should also check if it is not empty
        QList<QWidgetAction *> topActionsList = getPossibleTopActions();
        if (!topActionsList.empty()) {
            menu.addSection("");
            foreach (auto action, topActionsList) {
                connect(action, &QWidgetAction::triggered, &menu, &QMenu::hide);
                menu.addAction(action);
            }
            menu.addSection("");
        }
    }

    foreach (auto action, actionsList) {
        connect(action, &QWidgetAction::triggered, &menu, &QMenu::hide);
        menu.addAction(action);
    }

    menu.exec(QTreeWidget::mapToGlobal(point));
}
