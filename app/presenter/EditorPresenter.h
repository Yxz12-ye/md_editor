#pragma once

#include <QObject>
#include "view/CoreView.h"
#include "model/DocumentModel.h"
#include "model/tool.h"

class EditorPresenter: public QObject
{
    Q_OBJECT
private:
    CoreView* m_coreView;
    DocumentModel* documentModel;

    void initConnection();

public:
    EditorPresenter(QObject* parent = nullptr, CoreView* coreView = nullptr);
    ~EditorPresenter(){};

    void requestSave(QTextDocument* doc);
    void requestOpen();
    void onRequiredNewEditor(QTextDocument* doc);
    void requireSaveAs(QTextDocument* doc);
    void updateHighlight(int line);

private slots:
    void onEditorChanged(EditorView* new_editor);
};
