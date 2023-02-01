cmake_minimum_required(VERSION 3.5)

project(OtusHomework_3_Allocator LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_3_Allocator main.cpp
    modules/simpleAllocator.h
    modules/utils.hpp
    modules/factorial.hpp
    modules/container.hpp)

install(TARGETS OtusHomework_3_Allocator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
