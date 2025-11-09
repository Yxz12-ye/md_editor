#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

enum highlightType {
    Title_1,
    Title_2,
    Title_3,
    Title_4,
    lineCodeBlock,
    codeBlock,
    Bold,
    Italic,
    Cited,
    Link
};

enum BlockState {
    NormalState = -1,
    CodeBlockState = 1
};

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    QTextCharFormat a[10]; // 根据highlightType的数量调整
    
    void initFormats();
    void highlightTitles(const QString &text);
    void highlightCitation(const QString &text);
    void highlightInlineCode(const QString &text);
    void highlightBoldAndItalic(const QString &text);
    void highlightLinks(const QString &text);
    void highlightCodeBlock(const QString &text, int previousState);
    
    bool isInInlineCode(const QString &text, int pos);
    bool isInBoldRange(int pos, const QList<QPair<int, int>> &boldRanges);
};