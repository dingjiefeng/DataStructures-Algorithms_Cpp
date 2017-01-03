cmake_minimum_required(VERSION 3.6)
project(03_SingleLinkedCircularList_DoubleLinkedList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SingleLinkedCircularList.h DoubleLinkedList.h)
add_executable(03_SingleLinkedCircularList_DoubleLinkedList ${SOURCE_FILES})