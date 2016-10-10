#ifndef TABLECONTAINERVIEW_H
#define TABLECONTAINERVIEW_H

#include <QVBoxLayout>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include "basedto.h"

class TableContainerView : public QTableWidget
{
    Q_OBJECT
public:
    TableContainerView(QWidget* parent = nullptr);
    virtual ~TableContainerView();

private:
    bool isSorted;

    virtual void privateOnAddObject(const BaseDTO &object) = 0;
    virtual void privateOnPatchObject(const BaseDTO &object ) = 0;
    virtual void privateOnRemoveObject(const BaseDTO &object ) = 0;

private slots:
    void showContextMenu(const QPoint &point);

public slots:

    // BaseContainerView interface
public:
    void onGotObjects(QList<BaseDTO *> listObjects);
    void onAddObject(const BaseDTO &object);
    void onPatchObject(const BaseDTO &object);
    void onRemoveObject(const BaseDTO &object);

signals:
    void openEditor(int id);
    void removeObject(int id);


    // BaseContainerView interface
protected:
    virtual QList<int> getSelectedIds() = 0;
    virtual void initView() = 0;
};

#endif // TABLECONTAINERVIEW_H
