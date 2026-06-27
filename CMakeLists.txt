cmake_minimum_required(VERSION 3.20)

project(phonk
        VERSION 0.1.0
        LANGUAGES CXX
)

option(PHONK_ENABLE_WARNINGS "Enable compiler warnings" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

add_subdirectory(compiler)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()