#ifndef BASEDTO_H
#define BASEDTO_H

#include <QString>

class BaseDTO
{
public:
    BaseDTO();
    virtual ~BaseDTO();
};

class TestDTO : public BaseDTO
{
public:
    int id;
    QString name;
};

#endif // BASEDTO_H
