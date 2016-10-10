#include "basecontainerview.h"

BaseContainerView::BaseContainerView(QWidget *parent) : QWidget(parent)
{

}

BaseContainerView::~BaseContainerView()
{

}

bool BaseContainerView::getIsSorted() const
{
    return isSorted;
}

void BaseContainerView::setIsSorted(bool value)
{
    isSorted = value;
}
