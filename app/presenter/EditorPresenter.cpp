#include "EditorPresenter.h"

void EditorPresenter::initConnection()
{
    connect(m_coreView, &CoreView::editorChanged, this, &EditorPresenter::onEditorChanged);
}

EditorPresenter::EditorPresenter(QObject *parent, CoreView *coreView)
    : QObject(parent),
      m_coreView(coreView)
{
    documentModel = new DocumentModel(this);
}

void EditorPresenter::onEditorChanged(EditorView* new_editor)
{
    documentModel->updateDocument(new_editor->document);
}