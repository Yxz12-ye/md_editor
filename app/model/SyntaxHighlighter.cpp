#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *m_document)
    :QSyntaxHighlighter(m_document)
{
    // 一级标题格式
    a[Title_1] = QTextCharFormat();
    a[Title_1].setFontPointSize(24.0);
    a[Title_1].setFontWeight(QFont::Bold);
    a[Title_1].setForeground(QBrush(QColor("#D94F8A")));
    // 二级标题格式
    a[Title_2] = QTextCharFormat();
    a[Title_2].setFontPointSize(20.0);
    a[Title_2].setFontWeight(QFont::Bold);
    a[Title_2].setForeground(QBrush(QColor("#D94F8A")));
    // 三级标题格式
    a[Title_3] = QTextCharFormat();
    a[Title_3].setFontPointSize(18.0);
    a[Title_3].setFontWeight(QFont::Bold);
    a[Title_3].setForeground(QBrush(QColor("#D94F8A")));
    // 四级标题格式
    a[Title_4] = QTextCharFormat();
    a[Title_4].setFontPointSize(16.0);
    a[Title_4].setFontWeight(QFont::Bold);
    a[Title_4].setForeground(QBrush(QColor("#D94F8A")));
    // 行内代码格式
    a[lineCodeBlock] = QTextCharFormat();
    a[lineCodeBlock].setFontFamily("Courier");
    // a[lineCodeBlock].setFontPointSize(12);
    a[lineCodeBlock].setForeground(QBrush(QColor("#434CF4")));

    // 加粗格式
    a[Bold] = QTextCharFormat();
    a[Bold].setFontWeight(QFont::Bold);

    // 斜体格式
    a[Italic] = QTextCharFormat();
    a[Italic].setFontItalic(true);

    // 引用格式
    a[Cited] = QTextCharFormat();
    a[Cited].setForeground(QBrush(QColor("#6A9955")));
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // 简单的基于行首字符来判断标题等级
    if (text.startsWith("# ")){
        setFormat(0, text.length(), a[Title_1]);
    } else if (text.startsWith("## ")){
        setFormat(0, text.length(), a[Title_2]);
    } else if (text.startsWith("### ")){
        setFormat(0, text.length(), a[Title_3]);
    } else if (text.startsWith("#### ")){
        setFormat(0, text.length(), a[Title_4]);
    }
    // 行内代码使用反引号包裹
    int start = text.indexOf('`');
    while (start != -1) {
        int end = text.indexOf('`', start + 1);
        if (end != -1) {
            setFormat(start, end - start + 1, a[lineCodeBlock]);
            start = text.indexOf('`', end + 1);
        } else {
            break; // 没有找到匹配的结束反引号
        }
    }
    // 加粗使用**包裹
    start = text.indexOf("**");
    while (start != -1) {
        int end = text.indexOf("**", start + 2);
        if (end != -1) {
            setFormat(start, end - start + 2, a[Bold]);
            start = text.indexOf("**", end + 2);
        } else {
            break; // 没有找到匹配的结束**
        }
    }
    // 斜体使用*包裹
    start = text.indexOf("*");
    while (start != -1) {
        int end = text.indexOf("*", start + 1);
        if (end != -1) {
            setFormat(start, end - start + 1, a[Italic]);
            start = text.indexOf("*", end + 1);
        } else {
            break; // 没有找到匹配的结束*
        }
    }
    // 引用使用>开头
    if (text.startsWith(">")){
        setFormat(0, text.length(), a[Cited]);
    }
}
