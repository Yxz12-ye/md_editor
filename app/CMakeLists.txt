cmake_minimum_required(VERSION 3.10.0)
project(app VERSION 0.1.0 LANGUAGES C CXX)

find_package(cmark-gfm CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(app ./main.cpp)

target_sources(app PRIVATE 
    ./MainWindow.cpp

)

target_include_directories(
    app
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(app PRIVATE libcmark-gfm Qt6::Core Qt6::Gui Qt6::Widgets)