#include <iostream>
#include "SortAlgo.h"
#include "LinkedList.h"
#include "../MPointerPack/MPointer.h"



int main() {
    MPointerGC* garbagecollector = MPointerGC::GetInstance();
    DoubleLinkedList<int> lista;

    lista.headAppend(10);
    lista.headAppend(20);
    lista.append(30);
    lista.append(40);
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Espera para ver los mensajes de GC
    garbagecollector->debug();
    std::cout << "Lista: ";
    lista.printList();

    lista.replace(2, 25);
    std::cout << "Después de reemplazar en posición 2: ";
    lista.printList();
    garbagecollector->debug();

    lista.deleteNode(1);
    std::cout << "Después de eliminar en posición 1: ";
    lista.printList();
    garbagecollector->debug();

    lista.replace(1, 50);
    std::cout << "Después de reemplazar en posición 1: ";
    lista.printList();
    garbagecollector->debug();

    quickSort(lista);
    std::cout << "Lista después de QuickSort: ";
    lista.printList();
    garbagecollector->debug();

    std::this_thread::sleep_for(std::chrono::seconds(3)); // Espera para ver los mensajes de GC
    garbagecollector->debug();
    return 0;
}