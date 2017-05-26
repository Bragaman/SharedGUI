#ifndef TABLEWIDGETWITHMENU_H
#define TABLEWIDGETWITHMENU_H

#include <QTableWidget>
#include <QWidgetAction>
#include <QMenu>
#include <QPushButton>

class TableWidgetWithMenu : public QTableWidget
{
public:
    TableWidgetWithMenu(QWidget *parent = 0);

protected:
    QWidgetAction *createActionWidget(const QString &name, const QString &objName);

    //choose actions according to selected rows of smthng like this
    virtual QList<QWidgetAction *> getPossibleActions() = 0;

    //call in child constructor, create actions
    virtual void initActions() = 0;

    virtual QList<int> getSelectedIds() = 0;

    //call in child constructor, init headers and some view settings
    virtual void initView() = 0;

private slots:
    void showContextMenu(const QPoint &point);
};

#endif // TABLEWIDGETWITHMENU_H
