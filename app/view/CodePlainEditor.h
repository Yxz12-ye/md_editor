#pragma once

#include <ElaPlainTextEdit.h>
#include <QRect>
#include <QWidget>

class QResizeEvent;
class QPaintEvent;
class QMouseEvent;
class LineNumberArea;

/**
 * @brief   用于实现带行显示的TextEdit
 */
class CodePlainEditor : public ElaPlainTextEdit
{
private:
    friend class LineNumberArea;

    QWidget* lineNumberArea;

    int lineNumberAreaWidth() const;
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect& rect, int dy);
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    void lineNumberAreaMousePressEvent(QMouseEvent* event);
    void highlightCurrentLine();

public:
    explicit CodePlainEditor(QWidget* parent = nullptr);
    ~CodePlainEditor() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
};
