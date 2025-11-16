cmake_minimum_required(VERSION 3.5)

project(hatch_generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hatch_generator
    main.cpp
    hatch_generator.h
    hatch_generator.cpp
)
