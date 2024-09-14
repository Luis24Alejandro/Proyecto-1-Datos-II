#ifndef MPOINTERGC_H
#define MPOINTERGC_H
#include <mutex>
#include <thread>
#include "MPLinkedList.h"

class MPointerGC {
private:
    LinkedList list;              // Lista para rastrear punteros y sus referencias
    static MPointerGC* RECOLECTOR; // Instancia única del recolector de basura
    static std::mutex mutexx;     // Mutex para controlar el acceso concurrente
    int autoid = 0;               // Generador de IDs para punteros
    std::thread gcThread;         // Hilo que ejecuta la recolección de basura
    bool running = true;          // Controla la ejecución del hilo

    // Constructor y destructor privados para implementar el patrón Singleton
    MPointerGC();
    ~MPointerGC();

    // Ejecuta el ciclo de recolección de basura en un hilo separado
    void serchRef();

public:
    // Elimina la posibilidad de copiar o asignar la instancia Singleton
    MPointerGC(MPointerGC& other) = delete;  // Prohíbe la copia
    void operator=(const MPointerGC&) = delete;  // Prohíbe la asignación

    // Métodos accesibles públicamente
    static MPointerGC* GetInstance();    // Obtiene la instancia única del recolector
    int registerMPointer(void* address, DataType type);   // Registra un puntero nuevo y devuelve un ID
    void addRef(int id);                // Incrementa la referencia de un puntero
    bool deleteRef(int id);             // Disminuye la referencia y elimina el puntero si es necesario
    void debug();                       // Muestra el estado actual del recolector de basura

    // Detiene el hilo de recolección de basura
    void stop();
};

#include "MPointerGC.cpp"
#endif //MPOINTERGC_H
