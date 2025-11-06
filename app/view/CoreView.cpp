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
    startSize = size;
    pageContiner->resize(size);
    emit updateEditorSize(size);
}

void CoreView::addWelcomeTab()
{
    auto widget = new WelcomeView(this);
    addNewTab(widget, tr("Welcome"));
}

void CoreView::addNewEditorTab(mDocument doc)
{
    auto widget = new EditorView(this, doc);
    /**
     * @warning 这里感觉有点小问题, 但是现在想不起来
     */
    if (!doc.path.isEmpty())
    {
        addNewTab(widget, QUrl(doc.path).fileName());
    }
    else{
        addNewTab(widget, tr("*New File"));
    }
    connect(this, &CoreView::updateEditorSize, widget, &EditorView::updataSize);
    widget->updataSize(startSize);
}

mDocument CoreView::getCurrentDocument()
{
    auto p = pageContiner->currentWidget();
    EditorView* m = qobject_cast<EditorView*>(p);
    if(m){
        return m->m_document;
    }
    return mDocument();
}

void CoreView::newFile()
{
    addNewEditorTab(mDocument());
}

void CoreView::saveFile()
{
}

void CoreView::saveAs()
{
}