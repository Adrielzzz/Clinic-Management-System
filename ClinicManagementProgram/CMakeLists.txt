cmake_minimum_required(VERSION 3.5)

project(ClinicManagementProgram LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ClinicManagementProgram main.cpp)

install(TARGETS ClinicManagementProgram
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
