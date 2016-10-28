#include "actionwidget.h"
#include "ui_actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent, const QString &label) :
    QToolButton(parent),
    ui(new Ui::ActionWidget)
{
    ui->setupUi(this);
    ui->label->setText(label);
}

ActionWidget::~ActionWidget()
{
    delete ui;
}

