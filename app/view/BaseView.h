#pragma once

#include <ElaScrollArea.h>

class BaseView : public ElaScrollArea {
    Q_OBJECT
public:
    explicit BaseView(QWidget* parent = nullptr);
    ~BaseView();
};