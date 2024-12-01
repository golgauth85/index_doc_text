cmake_minimum_required(VERSION 3.5.0)
project(tp7 VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tp7 FileHandling.cpp CWordStat.cpp main.cpp)