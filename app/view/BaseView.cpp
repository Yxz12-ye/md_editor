#include "BaseView.h"
#include <ElaTheme.h>

BaseView::BaseView(QWidget* parent)
    : ElaScrollArea(parent) {
    connect(eTheme, &ElaTheme::themeModeChanged, this, [this, parent]() {
        if (!parent) {
            update();
        }
    });
}

BaseView::~BaseView() {}