#ifndef SORTALGO_H
#define SORTALGO_H

#include "LinkedList.h"

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(MPointer<Node<T>> a, MPointer<Node<T>> b);

// Algoritmo de QuickSort
template <typename T>
MPointer<Node<T>> partition(MPointer<Node<T>> start, MPointer<Node<T>> end);

template <typename T>
void quickSortRec(MPointer<Node<T>> bajo, MPointer<Node<T>> alto);

template <typename T>
void quickSort(DoubleLinkedList<T>& lista);

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(DoubleLinkedList<T>& lista);

// Algoritmo de Insertion Sort
template <typename T>
void insertionSort(DoubleLinkedList<T>& lista);


#include "SortAlgo.cpp"
#endif //SORTALGO_H
