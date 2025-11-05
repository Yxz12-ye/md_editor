#include "EditorView.h"

void EditorView::initConnection()
{
    connect(editArea, &ElaPlainTextEdit::textChanged, this, [=]{
        // 测试用, 实际连接位置可能不在这
    });
}

EditorView::EditorView(QWidget *parent, mDocument doc)
{
    splitter = new QSplitter(this);
    editArea = new ElaPlainTextEdit(this);
    preview = new PreviewView(this);
    if(doc.doc_ptr){
        editArea->setDocument(doc.doc_ptr);
        document = doc.doc_ptr;
    }
    else{
        document = editArea->document();
    }
    m_document = doc;
    initConnection();
}

void EditorView::updataSize(const QSize &size)
{
    QSize adjustedSize = size;
    adjustedSize.setHeight(adjustedSize.height() - 40);
    if (editArea){
        editArea->resize(adjustedSize);
    }
}
