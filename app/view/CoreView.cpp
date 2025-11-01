#include "CoreView.h"

void CoreView::initConnection()
{
    connect(pageContiner, &ElaTabWidget::currentChanged, this, [=](int index){
        qDebug()<<"page "<<index<<" clicked";
        auto p = pageContiner->currentWidget();
        EditorView* m = qobject_cast<EditorView*>(p);
        if(m){
            emit editorChanged(m);
        }
    });
}

CoreView::CoreView(QWidget *parent) : BaseView(parent)
{
    pageContiner = new ElaTabWidget(this);
    initConnection();
}

void CoreView::addNewTab(QWidget *widget, const QString &title)
{
    pageContiner->addTab(widget, title);
}

void CoreView::updataSize(const QSize &size)
{
    pageContiner->resize(size);
}
