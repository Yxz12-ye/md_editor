cmake_minimum_required(VERSION 3.10.0)
project(cmark_test VERSION 0.1.0 LANGUAGES C CXX)

find_package(cmark-gfm CONFIG REQUIRED)

add_executable(cmark_test ./main.cpp)

target_link_libraries(cmark_test PRIVATE 
    libcmark-gfm 
)