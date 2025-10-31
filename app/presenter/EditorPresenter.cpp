#include "EditorPresenter.h"
    
EditorPresenter::EditorPresenter(QObject *parent, CoreView *coreView, EditorView *editorView, PreviewView *previewView, WelcomeView *welcomeView)
    : QObject(parent),
      m_coreView(coreView),
      m_editorView(editorView),
      m_previewView(previewView),
      m_welcomeView(welcomeView)
{
}
