#pragma once

/**
 * @ref https://learn.microsoft.com/zh-cn/microsoft-edge/webview2/get-started/win32
 *      https://www.bilibili.com/opus/1064585366091071490
 */

#include <QMainWindow>
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
#include <QSize>
#include <QResizeEvent>

class MainWindow: public QMainWindow
{
    Q_OBJECT
private :
    void initializeWebView2();

    HRESULT OnEnvironmentCompleted(HRESULT result, ICoreWebView2Environment *env);

    HRESULT OnControllerCompleted(HRESULT result, ICoreWebView2Controller *controller);

    HRESULT OnNavigationStarting(ICoreWebView2 *sender, ICoreWebView2NavigationStartingEventArgs *args);

    HRESULT OnNavigationCompleted(ICoreWebView2 *sender, ICoreWebView2NavigationCompletedEventArgs *args);

    //拦截窗口事件
    HRESULT OnNewWindowRequested(ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args);

private:
    wil::com_ptr<ICoreWebView2Controller> m_webViewController;//控制器
    wil::com_ptr<ICoreWebView2> m_webView;//webview2

    EventRegistrationToken m_navigationStartingToken;
    EventRegistrationToken m_navigationCompletedToken;
    EventRegistrationToken m_NewWindowRequested;

public:
    MainWindow(/* args */);
    ~MainWindow(){};

protected:
    void resizeEvent(QResizeEvent *event) override;
};

