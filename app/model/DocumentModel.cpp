#include "DocumentModel.h"

DocumentModel::DocumentModel(QObject *parent) : QObject(parent)
{
    fileMgr = new FileManager(this);
}

void DocumentModel::updateDocument(mDocument doc)
{
    // 这里应该要断开先前的连接, 然后重新创建连接
    m_doc = doc;
}

void DocumentModel::onSave(mDocument doc)
{
    fileMgr->saveFile(doc);
}
