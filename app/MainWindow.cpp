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
    editorPresenter = new EditorPresenter(this, page);
    welcomeView = new WelcomeView(page);
    // 临时放在这里测试
    editorView = new EditorView(page);

    this->setIsNavigationBarEnable(false);
    page->addNewTab(welcomeView, tr("Welcome"));
    page->addNewTab(editorView, tr("*New File"));
    page->setMinimumSize(this->size());
    page->updataSize(this->size());
    this->setCentralCustomWidget(page);
}

void MainWindow::initConnection()
{

}

MainWindow::MainWindow() : ElaWindow(nullptr)
{
    initMenu();
    initContent();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ElaWindow::resizeEvent(event);
    QSize adjustedSize = event->size();
    adjustedSize.setHeight(adjustedSize.height() - 75);
    if(page){
        page->resize(adjustedSize);  // 或者使用 resize()
        page->updataSize(adjustedSize);
        editorView->updataSize(adjustedSize);
    }
    return;
}
