#include "CodePlainEditor.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTextBlock>

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodePlainEditor* editor)
        : QWidget(editor)
        , m_editor(editor)
    {
    }

    QSize sizeHint() const override
    {
        return QSize(m_editor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        m_editor->lineNumberAreaPaintEvent(event);
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        m_editor->lineNumberAreaMousePressEvent(event);
        QWidget::mousePressEvent(event);
    }

private:
    CodePlainEditor* m_editor;
};

CodePlainEditor::CodePlainEditor(QWidget* parent)
    : ElaPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodePlainEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodePlainEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodePlainEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

CodePlainEditor::~CodePlainEditor() = default;

int CodePlainEditor::lineNumberAreaWidth() const
{
    int digits = 1;
    int maxBlockCount = qMax(1, blockCount());
    while (maxBlockCount >= 10) {
        maxBlockCount /= 10;
        ++digits;
    }

    const int numberWidth = fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return 12 + numberWidth;
}

void CodePlainEditor::updateLineNumberAreaWidth(int newBlockCount)
{
    Q_UNUSED(newBlockCount);
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodePlainEditor::updateLineNumberArea(const QRect& rect, int dy)
{
    if (dy != 0) {
        lineNumberArea->scroll(0, dy);
    } else {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}

void CodePlainEditor::resizeEvent(QResizeEvent* event)
{
    ElaPlainTextEdit::resizeEvent(event);

    const QRect contentRect = contentsRect();
    lineNumberArea->setGeometry(QRect(contentRect.left(), contentRect.top(), lineNumberAreaWidth(), contentRect.height()));
}

void CodePlainEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), palette().window().color().darker(104));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    const int currentBlockNumber = textCursor().blockNumber();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            const QString number = QString::number(blockNumber + 1);
            const int blockHeight = qRound(blockBoundingRect(block).height());
            const QColor numberColor = (blockNumber == currentBlockNumber)
                ? palette().highlight().color()
                : palette().color(QPalette::Disabled, QPalette::Text);
            painter.setPen(numberColor);
            painter.drawText(0, top, lineNumberArea->width() - 6, blockHeight, Qt::AlignRight | Qt::AlignVCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodePlainEditor::lineNumberAreaMousePressEvent(QMouseEvent* event)
{
    QTextBlock block = firstVisibleBlock();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->position().y()) {
        if (block.isVisible() && event->position().y() < bottom) {
            QTextCursor cursor(block);
            setTextCursor(cursor);
            setFocus();
            ensureCursorVisible();
            break;
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
    }
}

void CodePlainEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> selections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = palette().alternateBase().color();
        lineColor.setAlpha(80);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }

    setExtraSelections(selections);
    lineNumberArea->update();
}
