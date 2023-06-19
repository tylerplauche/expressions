cmake_minimum_required(VERSION 3.20)
project(expressions)

set(CMAKE_CXX_STANDARD 14)

add_executable(expressions main.cpp ExpressionManager.h ExpressionManagerInterface.h)
