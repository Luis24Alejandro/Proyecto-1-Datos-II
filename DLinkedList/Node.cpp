#include "Node.h"


// Definiciones de las funciones miembro deben estar también en el .h

template <typename T>
T Node<T>::getData() const {
    return data;
}

template <typename T>
void Node<T>::setData(T valor) {
    data = valor;
}

template <typename T>
MPointer<Node<T>> Node<T>::getPrev() const {
    return prev;
}

template <typename T>
void Node<T>::setPrev(MPointer<Node<T>> nodo) {
    prev = nodo;
}

template <typename T>
MPointer<Node<T>> Node<T>::getNext() const {
    return next;
}

template <typename T>
void Node<T>::setNext(MPointer<Node<T>> nodo) {
    next = nodo;
}