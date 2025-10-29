#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include "view/WelcomeView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu* fileMenu;
    QMenuBar* menuBar;
    QList<QAction*> actionList;
    WelcomeView* welcomeView;
    void initMenu();
public:
    MainWindow();
    ~MainWindow(){};
};
