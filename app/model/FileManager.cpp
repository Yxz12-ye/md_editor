#include "FileManager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{
}

/**
 * @todo 修复用户取消选择的报错, 似乎和没返回值有关
 */
mDocument FileManager::openFile()
{
    QString filePath = "";
    filePath = QFileDialog::getOpenFileName(nullptr,
                                            tr("Open File"), ".",
                                            tr("Markdown Files (*.md);;Text Files (*.txt);;All Files (*)"));
    static mDocument nullDoc;

    if (!filePath.isNull()&&!filePath.isEmpty())
    {
        QTextDocument *document = new QTextDocument();
        QFile file(filePath);
        
        bool OK = file.open((QIODevice::ReadOnly | QIODevice::Text));
        if (OK)
        {
            QTextStream in(&file);
            in.setEncoding(QStringConverter::Encoding::Utf8);
            QString content = in.readAll();
            document->setPlainText(content);
            file.close();

            mDocument m_doc;
            m_doc.path = filePath;
            m_doc.doc_ptr = document;
            return m_doc;
        }
        else
        {
            qDebug() << "Unable to open the file!";
            delete document;
            return nullDoc;
        }
    }
    return nullDoc;
}

bool FileManager::saveFile(mDocument& doc)
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
        qDebug() << "Saving to " << doc.path << " content: " << content;
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Encoding::Utf8);
        out << content;
        file.close();
        return true;
    }
    else{
        // save markdown file
        QString filePath = QFileDialog::getSaveFileName(nullptr,
                                                        tr("Save File"), ".",
                                                        tr("Markdown Files (*.md);;Text Files (*.txt);;All Files (*)"));
        if (!filePath.isEmpty())
        {
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug() << "Unable to create:" << doc.doc_ptr;
                return false;
            }
            doc.path = filePath;
            QString content = doc.doc_ptr->toPlainText();
            QTextStream out(&file);
            out.setEncoding(QStringConverter::Encoding::Utf8);
            out << content;
            file.close();
            return true;
        }
    }
    return false;
}
