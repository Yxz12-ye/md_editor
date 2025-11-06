#pragma once

#include <ElaWidget.h>
#include <ElaTabWidget.h>
#include <ElaScrollPage.h>
#include <ElaScrollArea.h>
#include "BaseView.h"
#include "view/EditorView.h"
#include "view/WelcomeView.h"
#include "model/tool.h"

class CoreView : public BaseView
{
    Q_OBJECT
private:
    ElaTabWidget* pageContiner;

    void initConnection();
public:
    CoreView(QWidget* parent = nullptr);
    ~CoreView(){};

    void addNewTab(QWidget* widget, const QString& title); // 添加页面接口
    void updataSize(const QSize& size);
    void addWelcomeTab();
    void addNewEditorTab(mDocument doc);
    mDocument getCurrentDocument();

signals:
    void editorChanged(EditorView* new_editor);

public slots:
    void newFile();
    void saveFile();
    void saveAs();
};