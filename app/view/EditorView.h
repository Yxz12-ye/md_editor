#include <ElaScrollArea.h>
#include <ElaPlainTextEdit.h>
#include "BaseView.h"

class EditorView : public BaseView
{
private:
    ElaPlainTextEdit* editArea;
public:
    EditorView(/* args */){};
    ~EditorView(){};
};

