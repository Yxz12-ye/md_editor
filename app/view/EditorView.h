#pragma once

#include <ElaScrollArea.h>
#include <ElaPlainTextEdit.h>
#include "BaseView.h"
#include <QTextBlock>

class EditorView : public BaseView
{
private:
    ElaPlainTextEdit* editArea;
    QTextDocument* document;

    void initConnection();
public:
    EditorView(QWidget* parent = nullptr);
    ~EditorView(){};

    void updataSize(const QSize& size);
};

