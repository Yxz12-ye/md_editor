#pragma once

#include <QObject>
#include "BaseView.h"

class PreviewView: public BaseView
{
private:
    /* data */
public:
    PreviewView(QWidget* parent = nullptr);
    ~PreviewView(){};
};
