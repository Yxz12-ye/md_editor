#include "EditorPresenter.h"

void EditorPresenter::initConnection()
{
    connect(m_coreView, &CoreView::editorChanged, this, &EditorPresenter::onEditorChanged);
}

EditorPresenter::EditorPresenter(QObject *parent, CoreView *coreView)
    : QObject(parent),
      m_coreView(coreView)
{
}

void EditorPresenter::onEditorChanged(EditorView* new_editor){
    // 更新Model的工作内容
}