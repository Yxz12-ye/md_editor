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
    splitter = new QSplitter(this);
    pageContiner = new ElaTabWidget(splitter);
    previewView = new PreviewView(splitter);
    splitter->addWidget(pageContiner);
    splitter->addWidget(previewView);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    pageContiner->setMinimumWidth(500);
    initConnection();
    initComplete = true;
}

void CoreView::addNewTab(QWidget *widget, const QString &title)
{
    pageContiner->addTab(widget, title);
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
    connect(widget, &EditorView::mtextChanged, this, [=](const QString& newText){
        qDebug()<<"Editor text changed, length:"<<newText.length();
        emit ctextChanged(newText);
    });
}

mDocument& CoreView::getCurrentDocument()
{
    auto p = pageContiner->currentWidget();
    EditorView* m = qobject_cast<EditorView*>(p);
    if(m){
        return m->m_document;
    }
    static mDocument emptyDoc;
    return emptyDoc;
}

void CoreView::updateCurrentTabName(const QString &name)
{
    int index = pageContiner->currentIndex();
    pageContiner->setTabText(index, name);
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