cmake_minimum_required(VERSION 3.30)
project(Queue C)

set(CMAKE_C_STANDARD 99)

add_executable(Queue DoubleLinkedList.c LinkedList.h UserData.h Queue.c Queue.h QueueTester.c)
