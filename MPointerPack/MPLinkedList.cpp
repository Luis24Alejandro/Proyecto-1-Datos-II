#include "MPLinkedList.h"

// Crea un nuevo nodo y lo agrega al final de la lista
void LinkedList::newMpointer(int id, void* address, DataType type) {
    Node* newNode = new Node(id, address, 1, nullptr, type);  // Inicializa el nodo con el conteo de referencias en 1
    if (head == nullptr) {
        head = newNode;  // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;  // Recorre la lista hasta el último nodo
        }
        current->next = newNode;  // Agrega el nuevo nodo al final de la lista
    }
}

// Incrementa el conteo de referencias de un nodo específico identificado por su ID
void LinkedList::addRef(int identifier) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == identifier) {
            current->refCount++;  // Aumenta el conteo de referencias del nodo encontrado
            return;
        }
        current = current->next;
    }
}

// Decrementa el conteo de referencias de un nodo específico identificado por su ID
int LinkedList::substractRef(int identifier) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == identifier) {
            current->refCount--;  // Disminuye el conteo de referencias del nodo encontrado
            return current->refCount;
        }
        current = current->next;
    }
    return -1;  // Retorna -1 si no se encuentra el nodo con el ID proporcionado
}

// Muestra la lista completa con los detalles de cada nodo para depuración
void LinkedList::print() {
    cout << "Inicio de la Lista" << endl;
    Node* current = head;
    while (current != nullptr) {
        // Imprime la información del nodo según su tipo de datos
        switch (current->type) {
            case DataType::INT: {
                int* intPtr = static_cast<int*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *intPtr
                     << endl;
                break;
            }
            case DataType::DOUBLE: {
                double* doublePtr = static_cast<double*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *doublePtr
                     << endl;
                break;
            }
            case DataType::FLOAT: {
                float* floatPtr = static_cast<float*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *floatPtr
                     << endl;
                break;
            }
            case DataType::UNKNOWN: {
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << endl;
                break;
            }
        }
        current = current->next;  // Avanza al siguiente nodo
    }
    cout << "Final de la Lista" << endl;
}

// Retorna el número total de nodos en la lista
int LinkedList::getSize() {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;  // Incrementa el contador por cada nodo
        current = current->next;  // Avanza al siguiente nodo
    }
    return count;
}

// Devuelve el ID del nodo en la posición especificada por el índice
int LinkedList::getIDAt(int index) {
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return current->id;  // Retorna el ID del nodo en el índice dado
        }
        count++;
        current = current->next;  // Avanza al siguiente nodo
    }
    return -1;  // Retorna -1 si el índice está fuera del rango
}

// Devuelve el conteo de referencias para el nodo con el ID especificado
int LinkedList::getRefCount(int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current->refCount;  // Retorna el conteo de referencias del nodo encontrado
        }
        current = current->next;  // Avanza al siguiente nodo
    }
    return -1;  // Retorna -1 si no se encuentra el nodo con el ID proporcionado
}

// Elimina el nodo con el ID especificado de la lista
void LinkedList::remove(int identifier) {
    Node* current = head;
    Node* previous = nullptr;

    // Busca el nodo a eliminar
    while (current != nullptr && current->id != identifier) {
        previous = current;
        current = current->next;
    }

    // Si no se encuentra el nodo, no se realiza ninguna acción
    if (current == nullptr) return;

    // Actualiza los punteros para excluir el nodo encontrado
    if (previous == nullptr) {  // Si el nodo a eliminar es la cabeza
        head = current->next;  // Mueve la cabeza al siguiente nodo
    } else {
        previous->next = current->next;  // Salta el nodo actual en la lista
    }

    delete current;  // Libera la memoria del nodo eliminado
}
