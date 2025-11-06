#pragma once

#include <QObject>
#include <QTextDocument>
#include "model/tool.h"
#include "model/FileManager.h"

class DocumentModel: public QObject
{
    Q_OBJECT
private:
    mDocument m_doc;
    FileManager* fileMgr;

public:
    DocumentModel(QObject* parent = nullptr);
    ~DocumentModel(){};

    void updateDocument(mDocument doc);
    void onSave(mDocument doc);
    QTextDocument* onOpen();
    bool isNull();
    void requestNewEditor(QTextDocument* doc);

private slots:
    void onTextUpdate();
};
