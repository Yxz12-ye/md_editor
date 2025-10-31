#pragma once

#include <ElaWidget.h>
#include <ElaTabWidget.h>
#include <ElaScrollPage.h>
#include <ElaScrollArea.h>
#include "BaseView.h"

class CoreView : public BaseView
{
private:
    ElaTabWidget* pageContiner;
public:
    CoreView(QWidget* parent = nullptr);
    ~CoreView(){};

    void addNewTab(QWidget* widget, const QString& title); // 添加页面接口
    void updataSize(const QSize& size);
};