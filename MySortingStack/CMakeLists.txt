cmake_minimum_required(VERSION 3.30)
project(MySortingStack C)

set(CMAKE_C_STANDARD 99)

add_executable(MySortingStack StackTester StackTester.c DoubleLinkedList.c Stack.c)

