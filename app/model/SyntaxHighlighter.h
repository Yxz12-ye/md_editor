#pragma once

#include <QObject>
#include <QSyntaxHighlighter>

class SyntaxHighlighter: public QSyntaxHighlighter
{
    Q_OBJECT
private:
    

public:
    SyntaxHighlighter(QTextDocument* parent);
    ~SyntaxHighlighter();

protected:
    // 处理文本, text是单行文本, 处理一整个输入时会调用多次
    void highlightBlock(const QString &text) override; 
};