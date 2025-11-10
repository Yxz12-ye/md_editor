#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *document)
    : QSyntaxHighlighter(document)
{
    initFormats();
    
    // 初始化正则表达式
    m_linkRegex = QRegularExpression(R"(\[([^\]]+)\]\(([^\)]+)\))");
    m_linkRegex.optimize();
}

void SyntaxHighlighter::initFormats()
{
    // 一级标题
    QTextCharFormat title1Format;
    title1Format.setFontPointSize(24.0);
    title1Format.setFontWeight(QFont::Bold);
    title1Format.setForeground(QColor("#D94F8A"));
    m_formats[HighlightType::Title1] = title1Format;

    // 二级标题
    QTextCharFormat title2Format;
    title2Format.setFontPointSize(20.0);
    title2Format.setFontWeight(QFont::Bold);
    title2Format.setForeground(QColor("#D94F8A"));
    m_formats[HighlightType::Title2] = title2Format;

    // 三级标题
    QTextCharFormat title3Format;
    title3Format.setFontPointSize(18.0);
    title3Format.setFontWeight(QFont::Bold);
    title3Format.setForeground(QColor("#D94F8A"));
    m_formats[HighlightType::Title3] = title3Format;

    // 四级标题
    QTextCharFormat title4Format;
    title4Format.setFontPointSize(16.0);
    title4Format.setFontWeight(QFont::Bold);
    title4Format.setForeground(QColor("#D94F8A"));
    m_formats[HighlightType::Title4] = title4Format;

    // 行内代码
    QTextCharFormat inlineCodeFormat;
    inlineCodeFormat.setFontFamily("Courier New");
    inlineCodeFormat.setBackground(QColor("#F5F5F5"));
    inlineCodeFormat.setForeground(QColor("#434CF4"));
    m_formats[HighlightType::InlineCode] = inlineCodeFormat;

    // 代码块
    QTextCharFormat codeBlockFormat;
    codeBlockFormat.setFontFamily("Courier New");
    codeBlockFormat.setBackground(QColor("#F5F5F5"));
    codeBlockFormat.setForeground(QColor("#434CF4"));
    m_formats[HighlightType::CodeBlock] = codeBlockFormat;

    // 加粗
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    boldFormat.setForeground(QColor("#2C3E50"));
    m_formats[HighlightType::Bold] = boldFormat;

    // 斜体
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    italicFormat.setForeground(QColor("#7F8C8D"));
    m_formats[HighlightType::Italic] = italicFormat;

    // 引用
    QTextCharFormat quoteFormat;
    quoteFormat.setForeground(QColor("#6A9955"));
    quoteFormat.setFontItalic(true);
    m_formats[HighlightType::Quote] = quoteFormat;

    // 链接
    QTextCharFormat linkFormat;
    linkFormat.setForeground(QColor("#3498DB"));
    linkFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    m_formats[HighlightType::Link] = linkFormat;
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // if (text.isEmpty()) {
    //     setCurrentBlockState(static_cast<int>(BlockState::Normal));
    //     return;
    // }

    // 1. 首先处理代码块（优先级最高）
    highlightCodeBlock(text);
    
    // 如果在代码块中，不处理其他语法
    if (currentBlockState() == static_cast<int>(BlockState::InCodeBlock)) {
        return;
    }

    // 初始化占用信息
    HighlightInfo info;
    info.init(text.length());

    // 2. 处理标题（块级元素）
    highlightTitles(text, info);

    // 3. 处理引用（块级元素）
    highlightQuote(text, info);

    // 4. 处理行内代码（行内元素，优先级高）
    highlightInlineCode(text, info);

    // 5. 处理链接
    highlightLinks(text, info);

    // 6. 处理加粗和斜体（最后处理，优先级最低）
    highlightBoldAndItalic(text, info);
}

void SyntaxHighlighter::highlightCodeBlock(const QString &text)
{
    const QString codeBlockMarker = "```";
    BlockState prevState = static_cast<BlockState>(previousBlockState());
    
    bool startsWithMarker = text.startsWith(codeBlockMarker);
    
    if (prevState == BlockState::InCodeBlock) {
        // 当前在代码块中
        setFormat(0, text.length(), m_formats[HighlightType::CodeBlock]);
        
        // 只有当行首是 ``` 时才结束代码块
        if (startsWithMarker) {
            setCurrentBlockState(static_cast<int>(BlockState::Normal));
        } else {
            // 继续代码块状态（包括空行）
            setCurrentBlockState(static_cast<int>(BlockState::InCodeBlock));
        }
    } else if (startsWithMarker) {
        // 代码块开始
        setFormat(0, text.length(), m_formats[HighlightType::CodeBlock]);
        setCurrentBlockState(static_cast<int>(BlockState::InCodeBlock));
    } else {
        setCurrentBlockState(static_cast<int>(BlockState::Normal));
    }
}

void SyntaxHighlighter::highlightTitles(const QString &text, HighlightInfo &info)
{
    // 标题必须在行首
    if (text.isEmpty() || text[0] != '#') {
        return;
    }

    // 计算标题级别
    int level = 0;
    int pos = 0;
    while (pos < text.length() && text[pos] == '#' && level < 6) {
        ++level;
        ++pos;
    }

    // 标题后必须跟空格
    if (pos < text.length() && text[pos] == ' ') {
        HighlightType type;
        switch (level) {
            case 1: type = HighlightType::Title1; break;
            case 2: type = HighlightType::Title2; break;
            case 3: type = HighlightType::Title3; break;
            case 4: type = HighlightType::Title4; break;
            default: return;
        }
        
        applyFormat(0, text.length(), type, info);
    }
}

void SyntaxHighlighter::highlightQuote(const QString &text, HighlightInfo &info)
{
    if (text.startsWith('>') && !info.isOccupied(0, text.length())) {
        applyFormat(0, text.length(), HighlightType::Quote, info);
    }
}

void SyntaxHighlighter::highlightInlineCode(const QString &text, HighlightInfo &info)
{
    int pos = 0;
    const int length = text.length();
    
    while (pos < length) {
        // 查找反引号
        int start = text.indexOf('`', pos);
        if (start == -1) {
            break;
        }

        // 跳过代码块标记
        if (start + 2 < length && text[start + 1] == '`' && text[start + 2] == '`') {
            pos = start + 3;
            continue;
        }

        // 查找匹配的反引号
        int end = text.indexOf('`', start + 1);
        if (end == -1) {
            break;
        }

        // 检查是否已被占用
        int codeLength = end - start + 1;
        if (!info.isOccupied(start, codeLength)) {
            applyFormat(start, codeLength, HighlightType::InlineCode, info);
        }
        
        pos = end + 1;
    }
}

void SyntaxHighlighter::highlightLinks(const QString &text, HighlightInfo &info)
{
    QRegularExpressionMatchIterator it = m_linkRegex.globalMatch(text);
    
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int start = match.capturedStart();
        int length = match.capturedLength();
        
        if (!info.isOccupied(start, length)) {
            applyFormat(start, length, HighlightType::Link, info);
        }
    }
}

void SyntaxHighlighter::highlightBoldAndItalic(const QString &text, HighlightInfo &info)
{
    const int length = text.length();
    
    // 一次遍历处理所有加粗和斜体
    int pos = 0;
    
    while (pos < length) {
        if (text[pos] != '*') {
            ++pos;
            continue;
        }
        
        // 检查是否已被占用
        if (info.occupied[pos]) {
            ++pos;
            continue;
        }
        
        // 检查是否是加粗 (**)
        if (pos + 1 < length && text[pos + 1] == '*') {
            // 查找匹配的 **
            int end = pos + 2;
            while (end + 1 < length) {
                if (text[end] == '*' && text[end + 1] == '*') {
                    // 找到匹配的 **
                    if (!info.occupied[end] && !info.occupied[end + 1]) {
                        int boldLength = end - pos + 2;
                        applyFormat(pos, boldLength, HighlightType::Bold, info);
                        pos = end + 2;
                        break;
                    }
                }
                ++end;
            }
            if (end + 1 >= length) {
                pos += 2; // 没找到匹配，跳过
            }
        } else {
            // 处理斜体 (*)
            // 查找匹配的 *
            int end = pos + 1;
            while (end < length) {
                if (text[end] == '*') {
                    // 确保不是 ** 的一部分
                    bool isPart = false;
                    if (end + 1 < length && text[end + 1] == '*') {
                        isPart = true;
                    }
                    if (end > 0 && text[end - 1] == '*') {
                        isPart = true;
                    }
                    
                    if (!isPart && !info.occupied[end]) {
                        int italicLength = end - pos + 1;
                        applyFormat(pos, italicLength, HighlightType::Italic, info);
                        pos = end + 1;
                        break;
                    }
                }
                ++end;
            }
            if (end >= length) {
                ++pos; // 没找到匹配，继续
            }
        }
    }
}

void SyntaxHighlighter::applyFormat(int start, int length, HighlightType type, 
                                   HighlightInfo &info)
{
    setFormat(start, length, m_formats[type]);
    info.markOccupied(start, length);
}