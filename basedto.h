#ifndef BASEDTO_H
#define BASEDTO_H

#include <QString>
#include <QDebug>

class BaseDTO
{
public:
    BaseDTO();
    virtual ~BaseDTO();

    virtual void virtualMethod() = 0;
};

class TestDTO : public BaseDTO
{
public:
    int id;
    QString name;

    // BaseDTO interface
public:
    void virtualMethod() override;
};

#endif // BASEDTO_H
