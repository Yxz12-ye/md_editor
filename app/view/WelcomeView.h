#pragma once

#include <QVBoxLayout>
#include <ElaWidget.h>
#include <QLabel>
#include <ElaPushButton.h>
#include <ElaScrollArea.h>
#include <ElaText.h>

class WelcomeView : public ElaScrollArea
{
    Q_OBJECT
private:
    QVBoxLayout* verticalContiner;
    ElaText* welcomeMessage;
    ElaPushButton* newFile_button;
public:
    WelcomeView(QWidget* parent = nullptr);
    ~WelcomeView(){};
};
