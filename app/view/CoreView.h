#pragma once

#include <ElaWidget.h>
#include <ElaTabWidget.h>
#include <ElaScrollPage.h>
#include <ElaScrollArea.h>

class CoreView : public ElaScrollArea
{
    Q_OBJECT
private:
    ElaTabWidget* pageContiner;
public:
    CoreView(QWidget* parent = nullptr);
    ~CoreView(){};

    ElaTabWidget* get();
};