#include "CoreView.h"

CoreView::CoreView(QWidget *parent):BaseView(parent)
{
    pageContiner = new ElaTabWidget(this);
}

ElaTabWidget *CoreView::get()
{
    if(pageContiner) return pageContiner;
    else return nullptr;
}
