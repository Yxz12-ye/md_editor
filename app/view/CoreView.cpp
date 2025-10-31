#include "CoreView.h"

CoreView::CoreView(QWidget *parent) : BaseView(parent)
{
    pageContiner = new ElaTabWidget(this);
}

void CoreView::addNewTab(QWidget *widget, const QString &title)
{
    pageContiner->addTab(widget, title);
}

void CoreView::updataSize(const QSize &size)
{
    pageContiner->resize(size);
}
