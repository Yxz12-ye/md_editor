#pragma once

#include <QTextDocument>
#include <QUrl>

struct mDocument
{
    QTextDocument* doc_ptr;
    QString path;
    mDocument(){};
    mDocument(QTextDocument* doc, QString _path = ""):doc_ptr(doc),path(_path){};
};
