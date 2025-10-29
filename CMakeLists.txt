cmake_minimum_required(VERSION 3.10.0)
project(mdeditor VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)

if(CMAKE_USE_VCPKG)
    message("Use vcpkg as package manager")
    if(DEFINED ENV{VCPKG_ROOT})
        message("find vcpkg: $ENV{VCPKG_ROOT}")
        include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    else()
        error("unable to locate vcpkg, please set VCPKG_ROOT to ENV")
    endif()
endif()

add_subdirectory(./app)