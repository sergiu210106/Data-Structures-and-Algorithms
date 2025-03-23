cmake_minimum_required(VERSION 3.30)
project(FixedCapBiMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(first_assignment/include)

add_executable(FixedCapBiMap
    first_assignment/include/ExtendedTest.h
    first_assignment/include/FixedCapBiMap.h
    first_assignment/include/FixedCapBiMapIterator.h
    first_assignment/include/ShortTest.h
    first_assignment/src/App.cpp
    first_assignment/src/ExtendedTest.cpp
    first_assignment/src/FixedCapBiMap.cpp
    first_assignment/src/FixedCapBiMapIterator.cpp
    first_assignment/src/ShortTest.cpp)
