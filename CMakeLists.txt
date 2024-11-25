cmake_minimum_required(VERSION 3.23)
project(BWT)

set(CMAKE_CXX_STANDARD 17)

# 将源文件和头文件分组
set(SOURCES
    main.cpp
    sort.cpp
    C2B.cpp
    BWT.cpp
)

set(HEADERS
    general_heading.h
    sort.h
    C2B.h
    BWT.h
)

# 添加可执行文件
add_executable(BWT ${SOURCES} ${HEADERS})