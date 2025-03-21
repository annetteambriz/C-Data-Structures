cmake_minimum_required(VERSION 3.30)
project(MyLinkedList C)

set(CMAKE_C_STANDARD 99)

add_executable(MyLinkedList LinkedListTester LinkedListTester.c SinglyLinkedList.c)
