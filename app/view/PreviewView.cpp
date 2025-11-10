#include "PreviewView.h"

void PreviewView::initializeWebView2()
{
    //开始窗口webview2窗口
    CreateCoreWebView2EnvironmentWithOptions(
        nullptr,
        nullptr,
        nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment *env) -> HRESULT {
                return OnEnvironmentCompleted(result, env);
            }
            ).Get());
}

HRESULT PreviewView::OnEnvironmentCompleted(HRESULT result, ICoreWebView2Environment *env)
{
    env->CreateCoreWebView2Controller(
        reinterpret_cast<HWND>(this->winId()),
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Controller *controller) -> HRESULT {
                return OnControllerCompleted(result, controller);
            }).Get());

    return S_OK;
}

HRESULT PreviewView::OnControllerCompleted(HRESULT result, ICoreWebView2Controller *controller)
{
    if (controller == nullptr) {
        return S_FALSE;
    }

    //初始化webview2的依赖对象
    m_webViewController = controller;
    m_webViewController->get_CoreWebView2(&m_webView);


    //定义窗口
    qreal dpiScale = this->devicePixelRatioF(); // 支持DPI缩放
    RECT rect = {0, 0, static_cast<LONG>(this->width() * dpiScale), static_cast<LONG>(this->height() * dpiScale)};
    m_webViewController->put_Bounds(rect);


    //导航地址
    QString mUrlstring = "https://www.bilibili.com/";
    m_webView->Navigate(mUrlstring.toStdWString().c_str());


    //开始
    m_webView->add_NavigationStarting(
        Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
            [this](ICoreWebView2 *sender, ICoreWebView2NavigationStartingEventArgs *args) -> HRESULT {
                return OnNavigationStarting(sender, args);
            }).Get(), &m_navigationStartingToken);

    //完成
    m_webView->add_NavigationCompleted(
        Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
            [this](ICoreWebView2 *sender, ICoreWebView2NavigationCompletedEventArgs *args) -> HRESULT {
                return OnNavigationCompleted(sender, args);
            }).Get(), &m_navigationCompletedToken);

    // 禁止创建新窗口
    m_webView->add_NewWindowRequested(
        Microsoft::WRL::Callback<ICoreWebView2NewWindowRequestedEventHandler>(
            [this](ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args) -> HRESULT {
                return OnNewWindowRequested(sender, args);
            }).Get(), &m_NewWindowRequested);



    return S_OK;
}

HRESULT PreviewView::OnNavigationStarting(ICoreWebView2 *sender, ICoreWebView2NavigationStartingEventArgs *args)
{
    //开始加载
    return S_OK;
}

HRESULT PreviewView::OnNavigationCompleted(ICoreWebView2 *sender, ICoreWebView2NavigationCompletedEventArgs *args)
{
    //加载完成
    BOOL isSuccess;
    args->get_IsSuccess(&isSuccess);
    if (!isSuccess) {
        //加载失败

    }else{
        //加载成功

    }

    return S_OK;
}

HRESULT PreviewView::OnNewWindowRequested(ICoreWebView2 *sender, ICoreWebView2NewWindowRequestedEventArgs *args)
{
    //拦截创建新窗口，导航到新窗口
    wil::unique_cotaskmem_string uri;
    args->get_Uri(&uri);
    std::wstring newWindowUri(uri.get());
    m_webView->Navigate(newWindowUri.c_str());

    //禁止创建窗口
    args->put_Handled(TRUE);

    return S_OK;
}

PreviewView::PreviewView(QWidget *parent) : BaseView(parent)
{
    initializeWebView2();
}

void PreviewView::resizeEvent(QResizeEvent *event)
{
    //同步webview的大小
    if (m_webView) {
        //定义窗口
        qreal dpiScale = this->devicePixelRatioF(); // 支持DPI缩放
        RECT rect = {0, 0, static_cast<LONG>(this->width() * dpiScale), static_cast<LONG>(this->height() * dpiScale)};
        m_webViewController->put_Bounds(rect);
    }
    QWidget::resizeEvent(event);

}