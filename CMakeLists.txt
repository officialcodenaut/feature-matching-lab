cmake_minimum_required(VERSION 3.20)

project(feature_matching_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

add_executable(feature_matching_lab
    src/main.cpp
)

target_link_libraries(feature_matching_lab
    PRIVATE
        ${OpenCV_LIBS}
)

target_include_directories(feature_matching_lab
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)