#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QHash>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    // 高亮类型枚举
    enum class HighlightType {
        Title1,
        Title2,
        Title3,
        Title4,
        InlineCode,
        CodeBlock,
        Bold,
        Italic,
        Quote,
        Link
    };

    // 块状态枚举
    enum class BlockState {
        Normal = -1,
        InCodeBlock = 1
    };

    // 格式存储
    QHash<HighlightType, QTextCharFormat> m_formats;
    
    // 缓存的正则表达式
    QRegularExpression m_linkRegex;

    // 简单的范围标记数组，用于快速检查位置是否已被占用
    struct HighlightInfo {
        QVector<bool> occupied;  // 标记每个字符是否已被高亮
        
        void init(int length) {
            occupied.fill(false, length);
        }
        
        bool isOccupied(int pos, int length) const {
            for (int i = pos; i < pos + length && i < occupied.size(); ++i) {
                if (occupied[i]) return true;
            }
            return false;
        }
        
        void markOccupied(int pos, int length) {
            for (int i = pos; i < pos + length && i < occupied.size(); ++i) {
                occupied[i] = true;
            }
        }
    };

    // 初始化方法
    void initFormats();
    
    // 高亮处理方法
    void highlightCodeBlock(const QString &text);
    void highlightTitles(const QString &text, HighlightInfo &info);
    void highlightQuote(const QString &text, HighlightInfo &info);
    void highlightInlineCode(const QString &text, HighlightInfo &info);
    void highlightLinks(const QString &text, HighlightInfo &info);
    void highlightBoldAndItalic(const QString &text, HighlightInfo &info);
    
    // 辅助方法
    void applyFormat(int start, int length, HighlightType type, HighlightInfo &info);
};