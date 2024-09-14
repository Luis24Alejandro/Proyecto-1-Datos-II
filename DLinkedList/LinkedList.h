#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"

template <typename T>
class DoubleLinkedList {
private:
    MPointer<Node<T>> head= MPointer<Node<T>>::New();  // Puntero al primer nodo
    MPointer<Node<T>> tail= MPointer<Node<T>>::New(); // Puntero al último nodo
    int length;        // Longitud de la lista

public:
    // Constructor
    DoubleLinkedList();

    // Destructor
    ~DoubleLinkedList();

    // Obtiene la longitud de la lista
    int getLength() const;

    // Obtiene el nodo de la cabeza de la lista
    MPointer<Node<T>> getHead() const;

    // Obtiene el nodo de la cola de la lista
    MPointer<Node<T>>getTail() const;

    // Agrega un nuevo nodo al inicio de la lista
    void headAppend(T valor);

    // Agrega un nuevo nodo al final de la lista
    void append(T valor);

    // Elimina un nodo en la posición especificada
    void deleteNode(int posicion);

    // Reemplaza el valor de un nodo en la posición especificada
    void replace(int posicion, T nuevoValor);

    // Imprime la lista
    void printList();
};


#include "LinkedList.cpp"
#endif //LINKEDLIST_H
