#ifndef MPOINTER_H
#define MPOINTER_H
#include "MPointerGC.h"

using namespace std;

// Función para determinar el tipo de dato de T
template<typename T>
DataType getType() {
    if (std::is_same_v<T, int>) return DataType::INT;
    if (std::is_same_v<T, double>) return DataType::DOUBLE;
    if (std::is_same_v<T, float>) return DataType::FLOAT;
    return DataType::UNKNOWN;  // Tipo no reconocido
}

template <typename T>
class MPointer {
    // Instancia del recolector de basura
    MPointerGC* gC = MPointerGC::GetInstance();

private:
    bool hasValue = false;  // Indica si el puntero tiene un valor asignado
    int ID;  // Identificador único del puntero
    T* Mptr = nullptr;  // Puntero de tipo T

    // Constructor privado
    MPointer() {
        ID = gC->registerMPointer(Mptr, getType<T>());  // Registra el puntero en el recolector de basura
    }

public:
    // Constructor de copia
    MPointer(const MPointer & original) {
        Mptr = (original.Mptr);
        ID = (original.ID);  // Utiliza el mismo ID para añadir una referencia
        gC->addRef(ID);
    }

    // Destructor
    ~MPointer() {
        if (gC->deleteRef(ID)) {
            Mptr = nullptr;  // Elimina el puntero si no quedan referencias
        }
    }

    // Método estático para crear una nueva instancia de MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        return mp;
    }

    // Sobrecarga del operador * para acceder al valor apuntado
    T& operator*() {
        return *Mptr;
    }

    // Sobrecarga del operador & para obtener la dirección del puntero
    T operator&() {
        return *Mptr;
    }

    // Sobrecarga del operador = para asignar un valor del mismo tipo
    template <typename U>
    MPointer<T>& operator=(const U& valor) {
        hasValue = true;
        *Mptr = valor;  // Asigna el valor al puntero
        return *this;
    }

    // Sobrecarga del operador = para asignar un puntero
    MPointer<T>& operator=(T* ptr) {
        if (Mptr != ptr) {
            hasValue = true;
            if (Mptr) {
                bool noMoreRefs = gC->deleteRef(ID);
                deletePtr(noMoreRefs);  // Elimina el puntero si ya no hay referencias
            }
            Mptr = ptr;  // Actualiza el puntero
        }
        return *this;
    }

    // Sobrecarga del operador = para asignar otro MPointer
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            hasValue = true;
            Mptr = (other.Mptr);  // Copia el puntero
            gC->addRef(other.ID);
            bool noMoreRefs = gC->deleteRef(ID);
            deletePtr(noMoreRefs);  // Elimina el antiguo puntero si ya no hay referencias
            ID = other.ID;  // Actualiza el ID
        }
        return *this;
    }

    // Método para eliminar el puntero si es necesario
    void deletePtr(bool noMoreRefs) {
        if (noMoreRefs) {
            delete Mptr;
            Mptr = nullptr;
        }
    }

    // Verifica si el puntero tiene un valor asignado
    bool getHasValue() {
        return hasValue;
    }

    // Compara si dos MPointers apuntan a la misma dirección
    bool isSameAddress(const MPointer<T>& other) const {
        return this->Mptr == other.Mptr;
    }
};

#endif // MPOINTER_H
