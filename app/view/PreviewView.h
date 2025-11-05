#pragma once

#include <QObject>
#include "BaseView.h"

class PreviewView: public BaseView
{
    Q_OBJECT
private:
    /* data */
public:
    PreviewView(QWidget* parent = nullptr);
    ~PreviewView(){};
};
