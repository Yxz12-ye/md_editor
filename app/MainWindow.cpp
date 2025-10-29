#include "MainWindow.h"

void MainWindow::initMenu()
{
    menuBar = new ElaMenuBar(this);
    fileMenu = new ElaMenu(tr("File"),this);
    auto newFile_action = new QAction(tr("New File"));
    actionList.append(newFile_action);
    fileMenu->addActions(actionList);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);
}

MainWindow::MainWindow()
{
    initMenu();
    welcomeView = new WelcomeView(nullptr);
    this->setCentralCustomWidget(welcomeView);
    this->setIsNavigationBarEnable(false);
}