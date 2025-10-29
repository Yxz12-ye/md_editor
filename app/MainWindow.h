#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include "view/WelcomeView.h"
#include <ElaWindow.h>
#include <ElaMenu.h>
#include <ElaMenuBar.h>

class MainWindow : public ElaWindow
{
    Q_OBJECT
private:
    ElaMenu* fileMenu;
    ElaMenuBar* menuBar;
    QList<QAction*> actionList;
    WelcomeView* welcomeView;
    void initMenu();
public:
    MainWindow();
    ~MainWindow(){};
};
