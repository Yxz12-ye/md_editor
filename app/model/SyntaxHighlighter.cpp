#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *m_document)
    : QSyntaxHighlighter(m_document)
{
    // 初始化所有格式
    initFormats();
}

void SyntaxHighlighter::initFormats()
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
    a[lineCodeBlock].setFontFamily("Courier New");
    a[lineCodeBlock].setBackground(QBrush(QColor("#F5F5F5")));
    a[lineCodeBlock].setForeground(QBrush(QColor("#434CF4")));

    // 代码块格式
    a[codeBlock] = QTextCharFormat();
    a[codeBlock].setFontFamily("Courier New");
    a[codeBlock].setBackground(QBrush(QColor("#F5F5F5")));
    a[codeBlock].setForeground(QBrush(QColor("#434CF4")));

    // 加粗格式
    a[Bold] = QTextCharFormat();
    a[Bold].setFontWeight(QFont::Bold);
    a[Bold].setForeground(QBrush(QColor("#2C3E50")));

    // 斜体格式
    a[Italic] = QTextCharFormat();
    a[Italic].setFontItalic(true);
    a[Italic].setForeground(QBrush(QColor("#7F8C8D")));

    // 引用格式
    a[Cited] = QTextCharFormat();
    a[Cited].setForeground(QBrush(QColor("#6A9955")));
    a[Cited].setFontItalic(true);

    // 链接格式
    a[Link] = QTextCharFormat();
    a[Link].setForeground(QBrush(QColor("#3498DB")));
    a[Link].setUnderlineStyle(QTextCharFormat::SingleUnderline);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // 保存当前块状态
    int previousState = previousBlockState();
    
    // 处理代码块（多行状态）
    highlightCodeBlock(text, previousState);
    
    // 如果当前在代码块中，不处理其他语法
    if (currentBlockState() == CodeBlockState) {
        return;
    }
    
    // 处理标题
    highlightTitles(text);
    
    // 处理引用
    highlightCitation(text);
    
    // 处理行内元素（需要注意顺序）
    highlightLinks(text);
    highlightInlineCode(text);
    highlightBoldAndItalic(text);
}

void SyntaxHighlighter::highlightTitles(const QString &text)
{
    // 简单的基于行首字符来判断标题等级
    if (text.startsWith("# ")) {
        setFormat(0, text.length(), a[Title_1]);
    } else if (text.startsWith("## ")) {
        setFormat(0, text.length(), a[Title_2]);
    } else if (text.startsWith("### ")) {
        setFormat(0, text.length(), a[Title_3]);
    } else if (text.startsWith("#### ")) {
        setFormat(0, text.length(), a[Title_4]);
    }
}

void SyntaxHighlighter::highlightCitation(const QString &text)
{
    if (text.startsWith(">")) {
        setFormat(0, text.length(), a[Cited]);
    }
}

void SyntaxHighlighter::highlightInlineCode(const QString &text)
{
    // 行内代码使用反引号包裹，排除代码块的情况
    int start = 0;
    while ((start = text.indexOf('`', start)) != -1) {
        // 检查是否是代码块的开头（三个反引号）
        if (text.mid(start, 3) == "```") {
            start += 3;
            continue;
        }
        
        int end = text.indexOf('`', start + 1);
        if (end != -1) {
            setFormat(start, end - start + 1, a[lineCodeBlock]);
            start = end + 1;
        } else {
            break;
        }
    }
}

void SyntaxHighlighter::highlightBoldAndItalic(const QString &text)
{
    // 先处理加粗（**包裹），然后处理斜体（*包裹）
    // 这样可以避免加粗内部的*被误识别为斜体
    
    QList<QPair<int, int>> boldRanges;
    
    // 先找出所有加粗的范围
    int boldStart = 0;
    while ((boldStart = text.indexOf("**", boldStart)) != -1) {
        int boldEnd = text.indexOf("**", boldStart + 2);
        if (boldEnd != -1) {
            // 检查这不是在行内代码中
            if (!isInInlineCode(text, boldStart)) {
                boldRanges.append(qMakePair(boldStart, boldEnd + 2));
                setFormat(boldStart, boldEnd - boldStart + 2, a[Bold]);
            }
            boldStart = boldEnd + 2;
        } else {
            break;
        }
    }
    
    // 然后处理斜体，排除加粗范围内的内容
    int italicStart = 0;
    while ((italicStart = text.indexOf('*', italicStart)) != -1) {
        // 跳过加粗标记
        if (text.mid(italicStart, 2) == "**") {
            italicStart += 2;
            continue;
        }
        
        int italicEnd = text.indexOf('*', italicStart + 1);
        if (italicEnd != -1) {
            // 检查不在加粗范围内且不在行内代码中
            if (!isInBoldRange(italicStart, boldRanges) && !isInInlineCode(text, italicStart)) {
                setFormat(italicStart, italicEnd - italicStart + 1, a[Italic]);
            }
            italicStart = italicEnd + 1;
        } else {
            break;
        }
    }
}

void SyntaxHighlighter::highlightLinks(const QString &text)
{
    // 链接格式: [文本](URL)
    QRegularExpression linkRegex("\\[([^\\]]+)\\]\\(([^\\)]+)\\)");
    QRegularExpressionMatchIterator matches = linkRegex.globalMatch(text);
    
    while (matches.hasNext()) {
        QRegularExpressionMatch match = matches.next();
        int start = match.capturedStart();
        int length = match.capturedLength();
        
        // 检查不在代码块或行内代码中
        if (!isInInlineCode(text, start)) {
            setFormat(start, length, a[Link]);
        }
    }
}

void SyntaxHighlighter::highlightCodeBlock(const QString &text, int previousState)
{
    bool isCodeBlockStart = text.startsWith("```");
    bool isCodeBlockEnd = text.contains("```") && previousState == CodeBlockState;
    
    if (previousState == CodeBlockState) {
        // 当前在代码块中
        setFormat(0, text.length(), a[codeBlock]);
        
        if (isCodeBlockEnd) {
            // 代码块结束
            setCurrentBlockState(NormalState);
        } else {
            // 继续代码块
            setCurrentBlockState(CodeBlockState);
        }
    } else if (isCodeBlockStart) {
        // 代码块开始
        setFormat(0, text.length(), a[codeBlock]);
        setCurrentBlockState(CodeBlockState);
    } else {
        setCurrentBlockState(NormalState);
    }
}

bool SyntaxHighlighter::isInInlineCode(const QString &text, int pos)
{
    // 检查位置是否在行内代码中
    int backtickCount = 0;
    for (int i = 0; i < pos; ++i) {
        if (text[i] == '`') {
            backtickCount++;
        }
    }
    return (backtickCount % 2 == 1);
}

bool SyntaxHighlighter::isInBoldRange(int pos, const QList<QPair<int, int>> &boldRanges)
{
    for (const auto &range : boldRanges) {
        if (pos >= range.first && pos <= range.second) {
            return true;
        }
    }
    return false;
}