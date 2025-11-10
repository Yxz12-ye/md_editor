#pragma once

#include <ElaWidget.h>
#include <ElaTabWidget.h>
#include <ElaScrollPage.h>
#include <ElaScrollArea.h>
#include <QSplitter>
#include "BaseView.h"
#include "view/EditorView.h"
#include "view/WelcomeView.h"
#include "model/tool.h"
#include "view/PreviewView.h"

class CoreView : public BaseView
{
    Q_OBJECT
private:
    ElaTabWidget* pageContiner;
    QSize startSize;
    PreviewView* previewView;

    void initConnection();
public:
    CoreView(QWidget* parent = nullptr);
    ~CoreView(){};

    QSplitter* splitter;
    bool initComplete = false;

    void addNewTab(QWidget* widget, const QString& title); // 添加页面接口
    void addWelcomeTab();
    void addNewEditorTab(mDocument doc);
    mDocument& getCurrentDocument();
    void updateCurrentTabName(const QString& name);

signals:
    void editorChanged(EditorView* new_editor);
    void updateEditorSize(const QSize& size);
    void ctextChanged(const QString& newText);

public slots:
    void newFile();
    void saveFile();
    void saveAs();
    void updatePreview(const std::string& html);
};