#include <ElaScrollArea.h>
#include <ElaPlainTextEdit.h>
#include "BaseView.h"

class EditorView : public BaseView
{
private:
    ElaPlainTextEdit* editArea;
public:
    EditorView(QWidget* parent = nullptr);
    ~EditorView(){};

    void updataSize(const QSize& size);
};

