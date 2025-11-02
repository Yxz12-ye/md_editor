#pragma once

#include <QObject>
#include <QFile>
#include <QUrl>
#include <QTextDocument>

class FileManager: public QObject
{
    Q_OBJECT
private:
    QUrl path;

public:
    FileManager(/* args */);
    ~FileManager();

    /**
     * @todo    这里的和之前的返回值最好要去更新, 
     *          需要包含QTextDocument*和QUrl两个东西, 用于区分文件是否已经在
     *          另存为同样也需要
     */
    QTextDocument* openFile();
    bool saveFile(QTextDocument* doc);
};
