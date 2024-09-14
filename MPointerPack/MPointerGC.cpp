#include "MPointerGC.h"

#include <iostream>
#include <mutex>

// Inicializa el puntero estático del recolector y el mutex
MPointerGC* MPointerGC::RECOLECTOR{nullptr};
std::mutex MPointerGC::mutexx;

// Constructor: inicia el hilo del recolector de basura
MPointerGC::MPointerGC() {
    gcThread = std::thread(&MPointerGC::serchRef, this);  // Lanza el hilo que ejecutará la recolección de basura
}

// Destructor: limpia recursos y detiene el hilo de recolección
MPointerGC::~MPointerGC() {
    stop();  // Detiene la ejecución del hilo del recolector
    if (gcThread.joinable()) {
        gcThread.join();  // Asegura que el hilo finalice correctamente
    }
    debug();  // Imprime el estado final para depuración
}

// Obtiene la instancia única del recolector de basura
MPointerGC* MPointerGC::GetInstance() {
    std::lock_guard<std::mutex> lock(mutexx);  // Asegura acceso exclusivo para crear la instancia
    if (RECOLECTOR == nullptr) {
        RECOLECTOR = new MPointerGC();  // Crea la instancia si no existe
    }
    return RECOLECTOR;  // Devuelve la instancia
}

// Registra un nuevo puntero en el recolector y asigna un ID
int MPointerGC::registerMPointer(void* address, DataType type) {
    this->autoid++;  // Incrementa el contador de IDs
    int iD = this->autoid;  // Asigna el nuevo ID
    this->list.newMpointer(iD, address, type);  // Añade el puntero a la lista
    return iD;  // Devuelve el ID asignado
}

// Incrementa el contador de referencias para un puntero dado
void MPointerGC::addRef(int id) {
    list.addRef(id);  // Actualiza la referencia en la lista
}

// Disminuye el contador de referencias y verifica si el puntero puede ser eliminado
bool MPointerGC::deleteRef(int id) {
    int ref = list.substractRef(id);  // Actualiza el contador de referencias
    return (ref == 0);  // Retorna true si el puntero ya no tiene referencias
}

// Muestra el contenido actual de la lista de punteros para depuración
void MPointerGC::debug() {
    list.print();  // Imprime la lista para verificar el estado
}

// Detiene el hilo del recolector de basura
void MPointerGC::stop() {
    running = false;  // Marca el recolector como inactivo
}

// Ciclo principal del recolector de basura: busca y elimina punteros sin referencias
void MPointerGC::serchRef() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Pausa para evitar uso excesivo de CPU

        std::lock_guard<std::mutex> lock(mutexx);  // Protege el acceso concurrente a la lista

        // Recorre la lista para encontrar y eliminar punteros sin referencias
        for (int i = 0; i < list.getSize(); ++i) {  // Itera sobre los nodos en la lista
            int id = list.getIDAt(i);  // Obtiene el ID del nodo en la posición actual
            if (list.getRefCount(id) <= 0) {  // Verifica si el puntero no tiene referencias
                list.remove(id);  // Elimina el nodo sin referencias
                std::cout << "GC: El Nodo con ID " << id << " se ha eliminado." << std::endl;
            }
        }
    }
}
