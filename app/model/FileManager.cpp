#include "FileManager.h"

FileManager::FileManager(QObject *parent):QObject(parent)
{

}

mDocument FileManager::openFile()
{
    QUrl fileName = QFileDialog::getOpenFileUrl(nullptr,
    tr("Open Image"), "C:\\", 
    tr("Image Files (*.png *.jpg *.bmp)"));
}
