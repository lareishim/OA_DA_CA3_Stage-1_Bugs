cmake_minimum_required(VERSION 3.30)
project(OA_DA_CA3_Stage_1_Bugs)

set(CMAKE_CXX_STANDARD 20)

add_executable(OA_DA_CA3_Stage_1_Bugs main.cpp
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
        Position.h)
