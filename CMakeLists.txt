cmake_minimum_required(VERSION 3.29)
project(Proyecto_1_MPointers)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_1_MPointers MPointerPack/main.cpp
        MPointerPack/MPointerGC.cpp
        MPointerPack/MPointerGC.h
        MPointerPack/MPLinkedList.cpp
        MPointerPack/MPLinkedList.h
        MPointerPack/MPointer.cpp
        MPointerPack/MPointer.h
        DLinkedList/SortAlgo.cpp
        DLinkedList/SortAlgo.h
        DLinkedList/Node.cpp
        DLinkedList/Node.h
        DLinkedList/LinkedList.cpp
        DLinkedList/LinkedList.h
        DLinkedList/mainLinkedList.cpp
)
