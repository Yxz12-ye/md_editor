#include "DocumentModel.h"

DocumentModel::DocumentModel(QObject *parent) : QObject(parent)
{
}

void DocumentModel::updateDocument(QTextDocument *doc)
{
    // 这里应该要断开先前的连接, 然后重新创建连接
    m_doc = doc;
}
