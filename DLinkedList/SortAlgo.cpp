#include "SortAlgo.h"


// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(MPointer<Node<T>> a, MPointer<Node<T>> b) {
    T temp = (*a).getData();
    (*a).setData((*b).getData());
    (*b).setData(temp);
}

// Algoritmo de QuickSort
template <typename T>
MPointer<Node<T>> partition(MPointer<Node<T>> start, MPointer<Node<T>> end) {
    T pivote = (*end).getData();
    MPointer<Node<T>> i = (*start).getPrev();

    for (MPointer<Node<T>> j = start; !j.isSameAddress(end); j = (*j).getNext()) {
        if ((*j).getData() <= pivote) {
            i = (!i.getHasValue()) ? start : (*i).getNext();
            swap(i, j);
        }
    }
    i = (!i.getHasValue()) ? start : (*i).getNext();
    swap(i, end);
    return i;
}


template <typename T>
void quickSortRec(MPointer<Node<T>> bajo, MPointer<Node<T>> alto) {
    if (!alto.getHasValue() && !bajo.isSameAddress(alto) && !bajo.isSameAddress((*alto).getNext())) {  // Corrección aquí
        MPointer<Node<T>> p = partition(bajo, alto);
        quickSortRec(bajo, (*p).getPrev());
        quickSortRec((*p).getNext(), alto);
    }
}

template <typename T>
void quickSort(DoubleLinkedList<T>& lista) {
    quickSortRec(lista.getHead(), lista.getTail());
}

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(DoubleLinkedList<T>& lista) {
    if (!lista.getHead()) return;

    bool swapped;
    MPointer<Node<T>> actual = MPointer<Node<T>>::New();

    do {
        swapped = false;
        actual = lista.getHead();

        while (actual->getNext() != nullptr) {
            if (actual->getData() > actual->getNext()->getData()) {
                std::swap(actual->getData(), actual->getNext()->getData());
                swapped = true;
            }
            actual = actual->getNext();
        }
    } while (swapped);
}

// Algoritmo de Insertion Sort
template <typename T>
void insertionSort(DoubleLinkedList<T>& lista) {
    if (!lista.getHead()) return;

    MPointer<Node<T>> actual = lista.getHead()->getNext();
    while (actual != nullptr) {
        T clave = actual->getData();
        MPointer<Node<T>> anterior = actual->getPrev();

        while (anterior != nullptr && anterior->getData() > clave) {
            anterior->getNext()->setData(anterior->getData());
            anterior = anterior->getPrev();
        }
        if (anterior == nullptr) {
            lista.getHead()->setData(clave);
        } else {
            anterior->getNext()->setData(clave);
        }

        actual = actual->getNext();
    }
}