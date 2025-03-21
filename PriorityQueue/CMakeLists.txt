cmake_minimum_required(VERSION 3.30)
project(PriorityQueue C)

set(CMAKE_C_STANDARD 99)

add_executable(PriorityQueue LinkedList.h DoubleLinkedList.c PriorityQueue.c PriorityQueue.h PriorityQueueDemo.c UserData.h)
