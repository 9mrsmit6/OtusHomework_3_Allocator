cmake_minimum_required(VERSION 3.5)

project(OtusHomework_3_Allocator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_3_Allocator main.cpp modules/simpleAllocator.h modules/utils.hpp modules/factorial.hpp)

install(TARGETS OtusHomework_3_Allocator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
