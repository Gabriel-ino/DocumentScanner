cmake_minimum_required(VERSION 3.1)
project(scanner VERSION 1.0) 
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
    scanner
    main.cpp
    ImageProcesser.hpp
    ImageProcesser.cpp
)

target_link_libraries(scanner ${OpenCV_LIBS})


