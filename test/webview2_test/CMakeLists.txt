# 最小化测试Qt6WebView
cmake_minimum_required(VERSION 3.16)
project(WebView2_test VERSION 0.1.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

find_package(unofficial-webview2 CONFIG REQUIRED)

add_executable(WebView2_test main.cpp MainWindow.cpp)

target_link_libraries(WebView2_test PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    unofficial::webview2::webview2
)
