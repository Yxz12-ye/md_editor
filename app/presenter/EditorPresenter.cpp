#include "EditorPresenter.h"

void EditorPresenter::initConnection()
{
    // 当活动的Editor改变时会发射该信号, 并传递改变后的EditorView
    connect(m_coreView, &CoreView::editorChanged, this, &EditorPresenter::onEditorChanged);
    connect(m_coreView, &CoreView::ctextChanged, this, &EditorPresenter::onCtextChanged);
}

EditorPresenter::EditorPresenter(QObject *parent, CoreView *coreView)
    : QObject(parent),
      m_coreView(coreView)
{
    documentModel = new DocumentModel(this);
    initConnection();
}

void EditorPresenter::requestSave()
{
    mDocument& currentDocument = m_coreView->getCurrentDocument();
    QString prevFileName = currentDocument.path;
    if (currentDocument.doc_ptr){
        documentModel->onSave(currentDocument);
    }
    if (prevFileName != currentDocument.path){
        m_coreView->updateCurrentTabName(QUrl(currentDocument.path).fileName());
    }
}

void EditorPresenter::requestOpen()
{
    qDebug()<<"Open File required";
    mDocument openedDoc = documentModel->onOpen();
    if (openedDoc.doc_ptr){
        m_coreView->addNewEditorTab(openedDoc);
    }
}

void EditorPresenter::requestNew()
{
    qDebug()<<"New File required";
    m_coreView->addNewEditorTab(mDocument());
}

void EditorPresenter::onRequiredNewEditor(QTextDocument *doc)
{
}

void EditorPresenter::requestSaveAs(QTextDocument *doc)
{
}

void EditorPresenter::updateHighlight(int line)
{
}

void EditorPresenter::onCtextChanged(const QString &newText)
{
    std::string& html = documentModel->requestParser(newText);
    m_coreView->updatePreview(html);
}

void EditorPresenter::onEditorChanged(EditorView* new_editor)
{
    documentModel->updateDocument(new_editor->m_document);
}