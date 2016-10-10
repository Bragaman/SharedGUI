#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    iter = 0;
    connect(ui->widget, &TestTable::openEditor, this, [this](int id) {
        if (id == -1)
            addObj();
        else
            patchObj(id);
    });
    connect(ui->widget, &TestTable::removeObject, this, &Widget::removeObj);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addObj()
{
    TestDTO dto;
    iter++;
    dto.id = iter;
    dto.name  = QString::number(iter);
    ui->widget->onAddObject(dto);

}

void Widget::patchObj(int id)
{
    TestDTO dto;
    dto.id = id;
    dto.name  = "Graaaaaaaaaa";
    ui->widget->onPatchObject(dto);
}

void Widget::removeObj(int id)
{
    TestDTO dto;
    dto.id = id;
    dto.name  = "(((((";
    ui->widget->onRemoveObject(dto);
}
