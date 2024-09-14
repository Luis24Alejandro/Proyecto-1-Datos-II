#include "LinkedList.h"
#include <iostream>

// Constructor de la lista doblemente enlazada
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : length(0) {}

// Destructor de la lista doblemente enlazada
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    // Elimina todos los nodos de la lista
    while (head.getHasValue()) {
        MPointer<Node<T>> temp = head;  // Guarda el nodo actual
        Node<T> headNode = *head;
        head = headNode.getNext();  // Avanza al siguiente nodo
        temp.deletePtr(true);  // Elimina el nodo actual
    }
}

// Devuelve la longitud de la lista
template <typename T>
int DoubleLinkedList<T>::getLength() const {
    return length;
}

// Devuelve el nodo cabeza de la lista
template <typename T>
MPointer<Node<T>> DoubleLinkedList<T>::getHead() const {
    return head;
}

// Devuelve el nodo final de la lista
template <typename T>
MPointer<Node<T>> DoubleLinkedList<T>::getTail() const {
    return tail;
}

// Inserta un nuevo nodo al principio de la lista
template <typename T>
void DoubleLinkedList<T>::headAppend(T valor) {
    MPointer<Node<T>> nuevoNodo = MPointer<Node<T>>::New();
    nuevoNodo = new Node<T>(valor);  // Crea un nuevo nodo
    if (!head.getHasValue()) {
        head = tail = nuevoNodo;  // La lista está vacía, establece cabeza y cola al nuevo nodo
    } else {
        (*nuevoNodo).setNext(head);  // Inserta el nuevo nodo antes de la cabeza actual
        (*head).setPrev(nuevoNodo);  // Ajusta el puntero previo del nodo cabeza
        head = nuevoNodo;  // Actualiza la cabeza de la lista
    }
    length++;  // Incrementa la longitud de la lista
}

// Inserta un nuevo nodo al final de la lista
template <typename T>
void DoubleLinkedList<T>::append(T valor) {
    MPointer<Node<T>> nuevoNodo = MPointer<Node<T>>::New();
    nuevoNodo = new Node<T>(valor);  // Crea un nuevo nodo
    if (!tail.getHasValue()) {
        head = tail = nuevoNodo;  // La lista está vacía, establece cabeza y cola al nuevo nodo
    } else {
        (*tail).setNext(nuevoNodo);  // Inserta el nuevo nodo después de la cola actual
        (*nuevoNodo).setPrev(tail);  // Ajusta el puntero previo del nuevo nodo
        tail = nuevoNodo;  // Actualiza la cola de la lista
    }
    length++;  // Incrementa la longitud de la lista
}

// Elimina el nodo en la posición especificada
template <typename T>
void DoubleLinkedList<T>::deleteNode(int posicion) {
    if (posicion < 0 || posicion >= length) {
        std::cerr << "Posición inválida" << std::endl;
        return;
    }

    MPointer<Node<T>> actual = MPointer<Node<T>>::New();
    int indice;

    // Busca el nodo en la posición deseada
    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = (*actual).getNext();  // Avanza al siguiente nodo
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (*actual).getPrev();  // Retrocede al nodo previo
            indice--;
        }
    }

    if (actual.getHasValue()) {
        // Ajusta los punteros para eliminar el nodo actual
        if (actual.isSameAddress(head)) {
            head = (*head).getNext();  // Actualiza la cabeza de la lista
            if (head.getHasValue()) {
                (*head).setPrev(MPointer<Node<T>>::New());  // Ajusta el puntero previo del nuevo nodo cabeza
            }
        } else if (actual.isSameAddress(tail)) {
            tail = (*tail).getPrev();  // Actualiza la cola de la lista
            if (tail.getHasValue()) {
                (*tail).setNext(MPointer<Node<T>>::New());  // Ajusta el puntero siguiente del nuevo nodo cola
            }
        } else {
            MPointer<Node<T>> prevNode = (*actual).getPrev();
            (*prevNode).setNext((*actual).getNext());  // Ajusta el siguiente puntero del nodo previo
            MPointer<Node<T>> nextNode = (*actual).getNext();
            (*nextNode).setPrev((*actual).getPrev());  // Ajusta el puntero previo del nodo siguiente
        }

        length--;  // Decrementa la longitud de la lista
    } else {
        std::cerr << "Error al intentar eliminar en posición." << std::endl;
    }
}

// Reemplaza el valor en la posición especificada
template <typename T>
void DoubleLinkedList<T>::replace(int posicion, T nuevoValor) {
    if (posicion < 0 || posicion >= length) {
        std::cerr << "Posición inválida." << std::endl;
        return;
    }

    MPointer<Node<T>> actual = MPointer<Node<T>>::New();
    int indice;

    // Busca el nodo en la posición deseada
    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = (*actual).getNext();  // Avanza al siguiente nodo
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (*actual).getPrev();  // Retrocede al nodo previo
            indice--;
        }
    }

    if (actual.getHasValue()) {
        (*actual).setData(nuevoValor);  // Reemplaza el dato en el nodo actual
    } else {
        std::cerr << "Error al intentar reemplazar en posición." << std::endl;
    }
}

// Imprime todos los valores en la lista
template <typename T>
void DoubleLinkedList<T>::printList() {
    MPointer<Node<T>> actual = MPointer<Node<T>>::New();
    actual = head;
    while (!actual.isSameAddress((*tail).getNext())) {
        std::cout << (*actual).getData() << std::endl;  // Imprime el dato del nodo actual
        actual = (*actual).getNext();  // Avanza al siguiente nodo
    }
    std::cout << std::endl;
}
