#ifndef LISTA_H
#define LISTA_H

#include <stdexcept>
 
// ─────────────────────────────────────────────
//  Nodo de la lista enlazada
// ─────────────────────────────────────────────
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
 
    explicit Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};
 
// ─────────────────────────────────────────────
//  Lista enlazada simple genérica
// ─────────────────────────────────────────────
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int      cantidad;
 
public:
    Lista() : cabeza(nullptr), cantidad(0) {}
 
    ~Lista() { limpiar(); }
 
    // Impide copias accidentales (cada lista gestiona su propia memoria)
    Lista(const Lista&)            = delete;
    Lista& operator=(const Lista&) = delete;
 
    // ── Consultas ─────────────────────────────
    bool estaVacia()  const { return cantidad == 0; }
    int  tamanio()    const { return cantidad; }
    Nodo<T>* inicio() const { return cabeza; }
 
    // Acceso por posición (base 1). Lanza excepción si está fuera de rango.
    T& obtener(int posicion) {
        validarPosicion(posicion);
        return nodoPorPosicion(posicion)->dato;
    }
 
    const T& obtener(int posicion) const {
        validarPosicion(posicion);
        return nodoPorPosicion(posicion)->dato;
    }
 
    // ── Inserción ─────────────────────────────
    void insertarAlFinal(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (estaVacia()) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cantidad++;
    }
 
    // ── Modificación ──────────────────────────
    void modificar(int posicion, const T& nuevoValor) {
        validarPosicion(posicion);
        nodoPorPosicion(posicion)->dato = nuevoValor;
    }
 
    // ── Eliminación ───────────────────────────
    void eliminar(int posicion) {
        validarPosicion(posicion);
 
        Nodo<T>* aEliminar;
 
        if (posicion == 1) {
            aEliminar = cabeza;
            cabeza    = cabeza->siguiente;
        } else {
            Nodo<T>* anterior = nodoPorPosicion(posicion - 1);
            aEliminar         = anterior->siguiente;
            anterior->siguiente = aEliminar->siguiente;
        }
 
        delete aEliminar;
        cantidad--;
    }
 
    void limpiar() {
        while (!estaVacia())
            eliminar(1);
    }
 
private:
    // Devuelve el nodo en la posición dada (base 1)
    Nodo<T>* nodoPorPosicion(int posicion) const {
        Nodo<T>* actual = cabeza;
        for (int i = 1; i < posicion; i++)
            actual = actual->siguiente;
        return actual;
    }
 
    void validarPosicion(int posicion) const {
        if (posicion < 1 || posicion > cantidad)
            throw std::out_of_range("Posicion fuera de rango en la lista.");
    }
};

#endif