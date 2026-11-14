cmake_minimum_required(VERSION 3.10)
project(EnvironmentTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

add_executable(EnvironmentTest main.cpp)