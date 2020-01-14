cmake_minimum_required(VERSION 3.16.2)
project(pdq)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(pdq PDQ.cpp battle_check.cpp render.cpp misc.cpp)
