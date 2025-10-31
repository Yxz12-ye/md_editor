#pragma once

#include <QObject>
#include "view/CoreView.h"
#include "view/EditorView.h"
#include "view/PreviewView.h"
#include "view/WelcomeView.h"

class EditorPresenter: public QObject
{
    Q_OBJECT
private:
    CoreView* m_coreView;
    EditorView* m_editorView;
    PreviewView* m_previewView;
    WelcomeView* m_welcomeView;

public:
    EditorPresenter(QObject* parent = nullptr, CoreView* coreView = nullptr, EditorView* editorView = nullptr, PreviewView* previewView = nullptr, WelcomeView* welcomeView = nullptr);
    ~EditorPresenter(){};
};
