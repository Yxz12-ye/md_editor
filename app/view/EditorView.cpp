#include "EditorView.h"

void EditorView::initConnection()
{
    connect(editArea, &ElaPlainTextEdit::textChanged, this, [=]{
        // 测试用, 实际连接位置可能不在这
    });
}

EditorView::EditorView(QWidget *parent) : BaseView(parent)
{
    editArea = new ElaPlainTextEdit(this);
    document = editArea->document();
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
