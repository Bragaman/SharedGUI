#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class ActionWidget;
}

class ActionWidget : public QToolButton
{
    Q_OBJECT

public:
    explicit ActionWidget(QWidget *parent = 0, const QString &label = "");
    ~ActionWidget();

private:
    Ui::ActionWidget *ui;
};

#endif // ACTIONWIDGET_H
