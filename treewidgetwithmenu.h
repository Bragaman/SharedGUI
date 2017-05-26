#ifndef TREEWIDGETWITHMENU_H
#define TREEWIDGETWITHMENU_H

#include <QTreeWidget>
#include <QWidgetAction>
#include <QMenu>
#include <QPushButton>

//TableWidgetWithMenu and TreeWidgetWithMenu are practically the same,
//despite base class, but I decided not to create common base for them, because
//both TableWidgetWithMenu and TreeWidgetWithMenu has to be inherrited from QTableWidget
//and QTreeWidget, respectively, and we would face the diamond inheritance problem.
class TreeWidgetWithMenu : public QTreeWidget
{
public:
    TreeWidgetWithMenu(QWidget *parent = 0);

protected:
    QWidgetAction *createActionWidget(const QString &name, const QString &objName);

    //choose actions according to selected rows of smthng like this
    virtual QList<QWidgetAction *> getPossibleTopActions();
    virtual QList<QWidgetAction *> getPossibleActions() = 0;

    //call in child constructor, create actions
    virtual void initActions() = 0;

    virtual QList<int> getSelectedTopIds();
    virtual QList<int> getSelectedIds() = 0;

    //call in child constructor, init headers and some view settings
    virtual void initView() = 0;

    bool hasMenuSections = false;

private slots:
    void showContextMenu(const QPoint &point);
};

#endif // TREEWIDGETWITHMENU_H
