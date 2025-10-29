#include "CoreView.h"

CoreView::CoreView(QWidget *parent):ElaScrollArea(parent)
{
    pageContiner = new ElaTabWidget(this);
}

ElaTabWidget *CoreView::get()
{
    if(pageContiner) return pageContiner;
    else return nullptr;
}
