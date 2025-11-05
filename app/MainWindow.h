#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include "view/WelcomeView.h"
#include <ElaWindow.h>
#include <ElaMenu.h>
#include <ElaMenuBar.h>
#include <ElaTabWidget.h>
#include "view/CoreView.h"
#include "view/EditorView.h"
#include "presenter/EditorPresenter.h"
#include "model/tool.h"

class MainWindow : public ElaWindow
{
    Q_OBJECT
private:
    ElaMenu* fileMenu;
    ElaMenuBar* menuBar;
    QList<QAction*> actionList;
    WelcomeView* welcomeView;
    CoreView* page;
    EditorView* editorView;
    EditorPresenter* editorPresenter;

    void initMenu();
    void initContent();
    void initConnection();
public:
    MainWindow();
    ~MainWindow(){};

    void resizeEvent(QResizeEvent *event);
};
