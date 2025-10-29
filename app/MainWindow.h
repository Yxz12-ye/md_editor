#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPlainTextEdit* editor;
public:
    MainWindow();
    ~MainWindow(){};
};
