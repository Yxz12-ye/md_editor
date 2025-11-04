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

    void initConnection();

public:
    EditorPresenter(QObject* parent = nullptr, CoreView* coreView = nullptr);
    ~EditorPresenter(){};

    void requestSave(QTextDocument* doc);
    void onRequiredNewEditor(QTextDocument* doc);
    void requireSaveAs(QTextDocument* doc);
    void updateHighlight(int line);

private slots:
    void onEditorChanged(EditorView* new_editor);
};
