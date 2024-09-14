#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

// Enumeración para el tipo de datos
enum class DataType {
    INT,
    DOUBLE,
    FLOAT,
    UNKNOWN
};

// Estructura de Nodo
struct Node {
    int id;
    void* address;
    int refCount;
    Node* next;
    DataType type;

    // Constructor del Nodo
    Node(int id = 0, void* address = nullptr, int refCount = 0, Node* next = nullptr, DataType type = DataType::INT)
        : id(id), address(address), refCount(refCount), next(next), type(type) {}
};

// Clase Lista Enlazada
class LinkedList {
private:
    Node* head;  // Puntero al primer nodo de la lista
    int size;    // Número de nodos en la lista

public:
    // Constructor de la lista
    LinkedList() : head(nullptr), size(0) {}

    // Destructor de la lista
    ~LinkedList() {
        clear();  // Asegurarse de que todos los nodos sean liberados
    }

    // Añadir un nuevo nodo a la lista
    void newMpointer(int id, void* address, DataType type);

    // Aumentar el conteo de referencias para un nodo
    void addRef(int identifier);

    // Disminuir el conteo de referencias para un nodo y eliminar si es necesario
    int substractRef(int identifier);

    // Eliminar un nodo con un ID dado
    void remove(int identifier);

    // Imprimir todos los nodos en la lista
    void print();

    // Obtener el número de nodos en la lista
    int getSize();

    // Obtener el ID del nodo en el índice dado
    int getIDAt(int index);

    // Obtener el conteo de referencias para un nodo con un ID dado
    int getRefCount(int id);

private:
    // Liberar todos los nodos en la lista
    void clear();
};

#include "MPLinkedList.cpp"

#endif // LINKEDLIST_H