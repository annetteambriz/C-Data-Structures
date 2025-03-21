cmake_minimum_required(VERSION 3.30)
project(DoubleLinkedList C)

set(CMAKE_C_STANDARD 99)

add_executable(DoubleLinkedList LinkedListTester LinkedListTester.c DoubleLinkedList.c)
