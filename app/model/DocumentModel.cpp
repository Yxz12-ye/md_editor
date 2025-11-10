#include "DocumentModel.h"

DocumentModel::DocumentModel(QObject *parent) : QObject(parent)
{
    highlighter = new SyntaxHighlighter(nullptr);
    fileMgr = new FileManager(this);
    mdParser = new MarkdownParser();
}

void DocumentModel::updateDocument(mDocument doc)
{
    // 这里应该要断开先前的连接, 然后重新创建连接
    m_doc = doc;
    highlighter->setDocument(m_doc.doc_ptr);
}

void DocumentModel::onSave(mDocument& doc)
{
    fileMgr->saveFile(doc);
}

mDocument DocumentModel::onOpen()
{
    return fileMgr->openFile();
}

bool DocumentModel::isNull()
{
    return false;
}

void DocumentModel::requestNewEditor(QTextDocument *doc)
{
}

void DocumentModel::onTextUpdate(){
    
}