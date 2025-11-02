#pragma once

#include <ElaPlainTextEdit.h>


/**
 * @brief   用于实现带行显示的TextEdit
 *          这个就不用第三方库了...
 */
class CodePlainEditor: public ElaPlainTextEdit
{
private:
    /* data */
public:
    CodePlainEditor(/* args */);
    ~CodePlainEditor();
};