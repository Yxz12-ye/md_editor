#pragma once

#include <QObject>
#include <QFileDialog>
#include <QUrl>
#include <QTextDocument>
#include "tool.h"

class FileManager: public QObject
{
    Q_OBJECT
private:
    QUrl path;

public:
    FileManager(QObject* parent=nullptr);
    ~FileManager(){};

    /**
     * @todo    这里的和之前的返回值最好要去更新, 
     *          需要包含QTextDocument*和QUrl两个东西, 用于区分文件是否已经在
     *          另存为同样也需要
     */
    mDocument openFile();
    bool saveFile(mDocument doc);
};
