
#ifndef NODE_H
#define NODE_H
#include "../MPointerPack/MPointer.h"

template <typename T>
class Node {
private:
    T data;
    MPointer<Node> prev;
    MPointer<Node> next;

public:
    // Constructor
    Node(T valor) : data(valor), prev(MPointer<Node<T>>::New()), next(MPointer<Node<T>>::New()) {}

    // Métodos para obtener y establecer el dato
    T getData() const;
    void setData(T valor);

    // Métodos para obtener y establecer el nodo anterior
    MPointer<Node> getPrev() const;
    void setPrev(MPointer<Node> nodo);

    // Métodos para obtener y establecer el nodo siguiente
    MPointer<Node> getNext() const;
    void setNext(MPointer<Node> nodo);
};

#include "Node.cpp"

#endif //NODE_H
