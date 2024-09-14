#include <iostream>
#include <thread>
#include <chrono>
#include "MPointer.h"

/*
 * Clase MPointer
 *
 * MPointer<T> es una clase template que encapsula punteros de tipo T* y gestiona
 * su memoria automáticamente mediante una recolección de basura simple con MPointerGC.
 */

int main() {
    // Obtener la instancia del recolector de basura
    MPointerGC* garbagecollector = MPointerGC::GetInstance();

    // Prueba 1: Crear MPointer<int>, asignar y modificar valor
    MPointer<int> p1 = MPointer<int>::New();
    *p1 = 10;
    garbagecollector->debug();  // Estado inicial

    *p1 = 20;  // Modificar valor
    garbagecollector->debug();  // Verificar cambios

    // Prueba 2: Crear MPointer<int> y realizar copia
    MPointer<int> p2 = MPointer<int>::New();
    *p2 = 30;
    MPointer<int> p3 = p2;  // Copiar p2 a p3
    garbagecollector->debug();  // Verificar referencias

    // Prueba 3: Reasignar p3 y verificar el recolector
    p3 = p1;  // p3 ahora debe apuntar a la misma dirección que p1
    garbagecollector->debug();  // Verificar cambios en referencias

    // Prueba 4: Crear MPointer<double>, asignar y modificar valor
    MPointer<double> pD1 = MPointer<double>::New();
    *pD1 = 1.618;
    garbagecollector->debug();  // Estado inicial

    *pD1 = 2.718;  // Modificar valor
    garbagecollector->debug();  // Verificar cambios

    // Prueba 5: Crear y liberar múltiples punteros
    for (int i = 0; i < 5; ++i) {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = i * 10;
    }
    garbagecollector->debug();  // Verificar liberación de memoria

    // Prueba 6: Reasignar punteros de diferentes tipos y verificar comportamiento
    MPointer<int> p4 = MPointer<int>::New();
    MPointer<double> pD2 = MPointer<double>::New();
    *p4 = 40;
    *pD2 = 3.14;

    p4 = MPointer<int>::New();  // Crear nuevo puntero para p4
    *p4 = 50;
    garbagecollector->debug();  // Verificar estado después de reasignar p4

    // Prueba 7: Desreferenciar y modificar valores en bucles
    MPointer<int> p5 = MPointer<int>::New();
    for (int i = 1; i <= 3; ++i) {
        *p5 = i * 10;
        garbagecollector->debug();  // Verificar estado en cada iteración
    }
    garbagecollector->debug();  // Verificar estado final

    // Prueba 8: Crear punteros, asignar valores y verificar después de un retraso
    MPointer<int> p6 = MPointer<int>::New();
    *p6 = 60;
    MPointer<int> p7 = MPointer<int>::New();
    *p7 = 70;
    garbagecollector->debug();  // Estado inicial

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Esperar 2 segundos
    garbagecollector->debug();  // Verificar estado después del retraso

    return 0;
}