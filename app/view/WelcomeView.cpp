#include "WelcomeView.h"

WelcomeView::WelcomeView(QWidget *parent):BaseView(parent)
{
    verticalContiner = new QVBoxLayout(this);
    welcomeMessage = new ElaText(tr("Welcome! Press the button to start!"));
    newFile_button = new ElaPushButton(tr("New File"));
    verticalContiner->addWidget(welcomeMessage);
    verticalContiner->addSpacing(20);
    verticalContiner->addWidget(newFile_button);
}
