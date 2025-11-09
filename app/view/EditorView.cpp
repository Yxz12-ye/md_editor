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
    
    // 永远使用编辑区自带的文档，只复制内容
    document = editArea->document();
    
    if(doc.doc_ptr){
        // 只复制文本内容，不更换文档
        // 这里真没招了, setDocument会报错:QPlainTextEdit::setDocument: Document set does not support QPlainTextDocumentLayout
        QString content = doc.doc_ptr->toPlainText();
        editArea->setPlainText(content);
        
        // 更新 m_document 指向正确的文档
        m_document.doc_ptr = document;
        m_document.path = doc.path;

        delete doc.doc_ptr; // 释放传入的文档指针，防止内存泄漏
    }
    else{
        m_document.doc_ptr = document;
        m_document.path = doc.path;
    }
    
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
