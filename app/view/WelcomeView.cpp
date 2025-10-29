#include "WelcomeView.h"

WelcomeView::WelcomeView(QWidget *parent):QWidget(parent)
{
    verticalContiner = new QVBoxLayout(this);
    welcomeMessage = new QLabel(tr("Welcome! Press the button to start!"));
    newFile_button = new QPushButton(tr("New File"));
    verticalContiner->addWidget(welcomeMessage);
    verticalContiner->addSpacing(20);
    verticalContiner->addWidget(newFile_button);
}
