#ifndef TABLECONTAINERVIEW_H
#define TABLECONTAINERVIEW_H

#include "basecontainerview.h"

#include <QVBoxLayout>
#include <QTableWidget>
#include <QAction>

class TableContainerView : public BaseContainerView
{
    Q_OBJECT
public:
    TableContainerView(QWidget* parent = nullptr);
    virtual ~TableContainerView();

    QTableWidget *getTable() const;

private:
    QVBoxLayout *layout;
    QTableWidget *table;

    virtual void privateOnAddObject(const BaseDTO &object) = 0;
    virtual void privateOnPatchObject(const BaseDTO &object ) = 0;
    virtual void privateOnRemoveObject(const BaseDTO &object ) = 0;


private slots:
    void showContextMenu(const QPoint &point);

public slots:



    // BaseContainerView interface
public:
    void onGotObjects(QList<BaseDTO> listObjects ) override;
    void onAddObject(const BaseDTO &object ) override;
    void onPatchObject(const BaseDTO &object ) override;
    void onRemoveObject(const BaseDTO &object ) override;

signals:
    void openEditor(int id);
    void removeObject(int id);

    // BaseContainerView interface
};

#endif // TABLECONTAINERVIEW_H
