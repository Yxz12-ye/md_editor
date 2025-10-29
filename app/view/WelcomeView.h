#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class WelcomeView : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* verticalContiner;
    QLabel* welcomeMessage;
    QPushButton* newFile_button;
public:
    WelcomeView(QWidget* parent = nullptr);
    ~WelcomeView(){};
};
