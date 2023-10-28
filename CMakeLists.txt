cmake_minimum_required(VERSION 3.15)
project(oled_test)

file(GLOB_RECURSE U8G2_SRC "u8g2/*.*")
add_library(u8g2 STATIC ${U8G2_SRC})
include_directories(u8g2)

set(SRC main.cpp port_u8g2.cpp port_u8g2.h)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} u8g2)

