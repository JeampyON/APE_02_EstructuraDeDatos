#ifndef CURSO_H
#define CURSO_H
 
#include "Lista.h"
#include "Estudiante.h"
#include <string>
 
const int MAX_ESTUDIANTES = 20;
 
// ─────────────────────────────────────────────
//  Gestiona la lista enlazada de estudiantes
// ─────────────────────────────────────────────
class Curso {
private:
    Lista<Estudiante*> estudiantes;   // Punteros para evitar copias costosas
 
public:
    ~Curso() {
        // Liberar memoria de cada Estudiante creado con new
        Nodo<Estudiante*>* actual = estudiantes.inicio();
        while (actual != nullptr) {
            delete actual->dato;
            actual = actual->siguiente;
        }
    }
 
    // ── Consultas ─────────────────────────────
    bool estaLleno()  const { return estudiantes.tamanio() >= MAX_ESTUDIANTES; }
    bool estaVacio()  const { return estudiantes.estaVacia(); }
    int  cantidad()   const { return estudiantes.tamanio(); }
 
    Lista<Estudiante*>&       getEstudiantes()       { return estudiantes; }
    const Lista<Estudiante*>& getEstudiantes() const { return estudiantes; }
 
    // Busca un estudiante por cédula; retorna puntero o nullptr si no existe
    Estudiante* buscar(const std::string& cedula) const {
        Nodo<Estudiante*>* actual = estudiantes.inicio();
        while (actual != nullptr) {
            if (actual->dato->getCedula() == cedula)
                return actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }
 
    // Acceso por posición autonumérica (base 1)
    Estudiante* obtenerPorPosicion(int posicion) const {
        return estudiantes.obtener(posicion);
    }
 
    // ── Inserción ─────────────────────────────
    // Retorna false si ya existe la cédula o el curso está lleno
    bool agregar(Estudiante* estudiante) {
        if (estaLleno())                           return false;
        if (buscar(estudiante->getCedula()) != nullptr) return false;
 
        estudiantes.insertarAlFinal(estudiante);
        return true;
    }
 
    // ── Eliminación ───────────────────────────
    // Elimina por posición autonumérica (base 1); libera la memoria del Estudiante
    bool eliminar(int posicion) {
        if (posicion < 1 || posicion > estudiantes.tamanio()) return false;
 
        Estudiante* ptr = estudiantes.obtener(posicion);
        estudiantes.eliminar(posicion);
        delete ptr;   // También elimina su lista de notas (destructor de Estudiante)
        return true;
    }
 
    // ── Estadísticas ──────────────────────────
    // Promedio general del curso (promedio de los promedios individuales).
    // Solo considera estudiantes que tienen al menos una nota.
    // Retorna -1 si ningún estudiante tiene notas.
    double calcularPromedioGeneral() const {
        double sumaPromedios = 0.0;
        int    conteo        = 0;
 
        Nodo<Estudiante*>* actual = estudiantes.inicio();
        while (actual != nullptr) {
            double promedio = actual->dato->calcularPromedio();
            if (promedio >= 0.0) {          // -1 indica sin notas
                sumaPromedios += promedio;
                conteo++;
            }
            actual = actual->siguiente;
        }
 
        return (conteo > 0) ? (sumaPromedios / conteo) : -1.0;
    }
 
    bool algunoTieneNotas() const {
        Nodo<Estudiante*>* actual = estudiantes.inicio();
        while (actual != nullptr) {
            if (!actual->dato->getNotas().estaVacia()) return true;
            actual = actual->siguiente;
        }
        return false;
    }
};
 
#endif // CURSO_H
 