#pragma once

#include <ElaScrollArea.h>
#include <ElaPlainTextEdit.h>
#include "BaseView.h"
#include <QTextBlock>
#include "PreviewView.h"
#include <QSplitter>
#include "model/tool.h"

class EditorView : public BaseView
{
    Q_OBJECT
private:
    QSplitter* splitter;
    ElaPlainTextEdit* editArea;
    PreviewView* preview;

    void initConnection();
    
public:
    EditorView(QWidget* parent = nullptr, mDocument doc = mDocument());
    ~EditorView(){};

    QTextDocument* document;
    mDocument m_document;

    void updataSize(const QSize& size);
    
};

