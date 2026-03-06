#pragma once

#include "CodePlainEditor.h"
#include "BaseView.h"
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

    int cursorLine() const;

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void mtextChanged(const QString& newText);
    void cursorLineChanged(int line);
};
