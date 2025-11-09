#include "MainWindow.h"

void MainWindow::initMenu()
{
    menuBar = new ElaMenuBar(this);
    fileMenu = new ElaMenu(tr("File"), this);

    auto newFile_action = new QAction(tr("New File"));
    auto openFile_action = new QAction(tr("Open File"));
    auto save_action = new QAction(tr("Save"));
    auto save_as_action = new QAction(tr("Save As"));

    actionList.append(newFile_action);
    actionList.append(openFile_action);
    actionList.append(save_action);
    actionList.append(save_as_action);

    fileMenu->addActions(actionList);
    menuBar->addMenu(fileMenu);
    this->setMenuBar(menuBar);
}

void MainWindow::initContent()
{
    page = new CoreView(this);
    editorPresenter = new EditorPresenter(this, page);

    this->setIsNavigationBarEnable(false);
    page->addWelcomeTab();
    page->addNewEditorTab(mDocument());// 临时
    page->setMinimumSize(this->size());
    page->updataSize(this->size());
    this->setCentralCustomWidget(page);
}

void MainWindow::initConnection()
{
    connect(actionList[0], &QAction::triggered, editorPresenter, &EditorPresenter::requestNew);
    connect(actionList[1], &QAction::triggered, editorPresenter, &EditorPresenter::requestOpen);
    connect(actionList[2], &QAction::triggered, editorPresenter, &EditorPresenter::requestSave);
    // connect(actionList[2], &QAction::triggered, editorPresenter, &EditorPresenter::requestSaveAs);
}

MainWindow::MainWindow() : ElaWindow(nullptr)
{
    initMenu();
    initContent();
    initConnection();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ElaWindow::resizeEvent(event);
    QSize adjustedSize = event->size();
    adjustedSize.setHeight(adjustedSize.height() - 75);
    if(page){
        page->resize(adjustedSize);  // 或者使用 resize()
        page->updataSize(adjustedSize);
    }
    return;
}
