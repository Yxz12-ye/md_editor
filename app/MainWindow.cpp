#include "MainWindow.h"

void MainWindow::initMenu()
{
    menuBar = new ElaMenuBar(this);
    fileMenu = new ElaMenu(tr("File"), this);
    auto newFile_action = new QAction(tr("New File"));
    actionList.append(newFile_action);
    fileMenu->addActions(actionList);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);
}

void MainWindow::initContent()
{
    page = new CoreView(this);
    welcomeView = new WelcomeView(page);
    this->setIsNavigationBarEnable(false);
    page->get()->addTab(welcomeView, tr("Welcome"));
    page->get()->setMinimumSize(this->size());
    page->setMinimumSize(this->size());
    this->setCentralCustomWidget(page);
}

MainWindow::MainWindow() : ElaWindow(this)
{
    initMenu();
    initContent();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    return;
}
