#include "FileManager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{
}

mDocument FileManager::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Open Image"), ".",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    if (!filePath.isEmpty())
    {
        QTextDocument *document = new QTextDocument();
        QFile file(filePath);
        bool OK = file.open((QIODevice::ReadOnly | QIODevice::Text));
        if (OK)
        {
            QTextStream stream(&file);
            stream.setEncoding(QStringConverter::Encoding::Utf8);
            document->setPlainText(stream.readAll());
            file.close();
            return mDocument(document, filePath);
        }
        else
        {
            qDebug() << "Unable to open the file!";
            delete document;
            return mDocument();
        }
    }
}

bool FileManager::saveFile(mDocument doc)
{

    if (!doc.path.isEmpty() && QUrl(doc.path).isValid())
    {
        QFile file(doc.path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Unable to create:" << doc.doc_ptr;
            return false;
        }
        QString content = doc.doc_ptr->toPlainText();
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Encoding::Utf8);
        out << content;
        file.close();
        return true;
    }
    return false;
}
