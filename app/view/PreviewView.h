#pragma once

#include <QObject>
#include "BaseView.h"
#include <QMainWindow>
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
#include <QSize>
#include <QResizeEvent>
#include <Windows.h>

class PreviewView: public BaseView
{
    Q_OBJECT
private:
    void initializeWebView2();

    HRESULT OnEnvironmentCompleted(HRESULT result, ICoreWebView2Environment *env);

    HRESULT OnControllerCompleted(HRESULT result, ICoreWebView2Controller *controller);

    HRESULT OnNavigationStarting(ICoreWebView2 *sender, ICoreWebView2NavigationStartingEventArgs *args);

    HRESULT OnNavigationCompleted(ICoreWebView2 *sender, ICoreWebView2NavigationCompletedEventArgs *args);

    //拦截窗口事件
    HRESULT OnNewWindowRequested(ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args);

    wil::com_ptr<ICoreWebView2Controller> m_webViewController;//控制器
    wil::com_ptr<ICoreWebView2> m_webView;//webview2

    EventRegistrationToken m_navigationStartingToken;
    EventRegistrationToken m_navigationCompletedToken;
    EventRegistrationToken m_NewWindowRequested;

public:
    PreviewView(QWidget* parent = nullptr);
    ~PreviewView(){};

    void updateContent(const std::string& html);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
