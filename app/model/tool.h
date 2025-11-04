#pragma once

#include <QTextDocument>
#include <QUrl>

struct mDocument
{
    QTextDocument* doc_ptr;
    QUrl path;
    mDocument(){};
    mDocument(QTextDocument* doc, QUrl _path = QUrl()):doc_ptr(doc),path(_path){};
    bool isPathEmpty(){return path.isEmpty();}
};
