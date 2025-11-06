#include "EditorPresenter.h"

void EditorPresenter::initConnection()
{
    // 当活动的Editor改变时会发射该信号, 并传递改变后的EditorView
    connect(m_coreView, &CoreView::editorChanged, this, &EditorPresenter::onEditorChanged);
}

EditorPresenter::EditorPresenter(QObject *parent, CoreView *coreView)
    : QObject(parent),
      m_coreView(coreView)
{
    documentModel = new DocumentModel(this);
}

void EditorPresenter::requestSave()
{
    auto currentDocument = m_coreView->getCurrentDocument();
    if (currentDocument.doc_ptr){
        documentModel->onSave(currentDocument);
    }
}

void EditorPresenter::requestOpen()
{
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

void EditorPresenter::onEditorChanged(EditorView* new_editor)
{
    documentModel->updateDocument(new_editor->m_document);
}