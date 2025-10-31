#include "EditorView.h"

EditorView::EditorView(QWidget *parent): BaseView(parent)
{
    editArea = new ElaPlainTextEdit(this);
}

void EditorView::updataSize(const QSize &size)
{
    QSize adjustedSize = size;
    adjustedSize.setHeight(adjustedSize.height() - 40);
    if (editArea){
        editArea->resize(adjustedSize);
    }
}
