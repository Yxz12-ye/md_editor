#pragma once

#include <QObject>
#include <QSyntaxHighlighter>

enum highlightType{
    Title_1,
    Title_2,
    Title_3,
    Title_4,
    lineCodeBlock,
    codeBlock,
    Blod,
    Italic,
    Formula
};

class SyntaxHighlighter: public QSyntaxHighlighter
{
    Q_OBJECT
private:
    QHash<highlightType,QTextFormat> a;

public:
    SyntaxHighlighter(QTextDocument* parent);
    ~SyntaxHighlighter();

protected:
    // 处理文本, text是单行文本, 处理一整个输入时会调用多次
    void highlightBlock(const QString &text) override; 
};