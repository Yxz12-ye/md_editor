#pragma once

#include <QObject>
#include <QTextDocument>

class DocumentModel: public QObject
{
    Q_OBJECT
private:
    QTextDocument* m_doc;

public:
    DocumentModel(QObject* parent = nullptr);
    ~DocumentModel(){};

    void updateDocument(QTextDocument* doc);
    void onSave(QTextDocument* doc);
    QTextDocument* onOpen();
    bool isNull();
    void requestNewEditor(QTextDocument* doc);

private slots:
    void onTextUpdate();
};
