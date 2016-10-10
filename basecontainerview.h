#ifndef BASECONTAINERVIEW_H
#define BASECONTAINERVIEW_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QMenu>
#include <QAction>

#include "basedto.h"
//Рассмотрим ситуацию только для таблиц и листов
class BaseContainerView : public QWidget
{
    Q_OBJECT
public:
    explicit BaseContainerView(QWidget *parent = 0);
    virtual ~BaseContainerView();
    virtual void initView() = 0;

    virtual void onGotObjects(QList<BaseDTO> listObjects ) = 0;
    virtual void onAddObject(const BaseDTO &object ) = 0;
    virtual void onPatchObject(const BaseDTO &object ) = 0;
    virtual void onRemoveObject(const BaseDTO &object ) = 0;

    bool getIsSorted() const;
    void setIsSorted(bool value);

signals:
    void sendGetRequest(const QString &queryStr);

protected:
    bool isSorted;

    virtual QList<int> getSelectedIds() = 0;

public slots:



};

#endif // BASECONTAINERVIEW_H
