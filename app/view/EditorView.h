#pragma once

#include <ElaScrollArea.h>
#include "CodePlainEditor.h"
#include "BaseView.h"
#include <QTextBlock>
#include "PreviewView.h"
#include <QSplitter>
#include "model/tool.h"

class EditorView : public BaseView
{
    Q_OBJECT
private:
    CodePlainEditor* editArea;

    void initConnection();
    
public:
    EditorView(QWidget* parent = nullptr, mDocument doc = mDocument());
    ~EditorView(){};

    QTextDocument* document;
    mDocument m_document;

protected:
    void resizeEvent(QResizeEvent* event) override;
    
signals:
    void mtextChanged(const QString& newText);
};

