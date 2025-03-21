cmake_minimum_required(VERSION 3.30)
project(MyStack C)

set(CMAKE_C_STANDARD 99)

add_executable(MyStack StackTester StackTester.c DoubleLinkedList.c Stack.c)
