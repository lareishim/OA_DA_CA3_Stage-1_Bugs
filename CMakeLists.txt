cmake_minimum_required(VERSION 3.30)
project(OA_DA_CA3_Stage_1_Bugs)

set(CMAKE_CXX_STANDARD 20)

add_executable(OA_DA_CA3_Stage_1_Bugs
        main.cpp
        Crawler.cpp
        Board.cpp
        Hopper.cpp
        Bishop.cpp
        Bishop.h
        BugVisualizer.cpp
        BugVisualizer.h
)

# Headers are not needed here unless you're installing
# No need to include .h files in add_executable

# Set SFML location (update this path to your actual location if needed)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics network REQUIRED)

# Include headers
include_directories("C:/SFML-2.6.2/include")

# Link SFML to your executable
target_link_libraries(OA_DA_CA3_Stage_1_Bugs
        sfml-system sfml-window sfml-graphics sfml-network
)
