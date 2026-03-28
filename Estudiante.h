#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include "Lista.h"

const int MAX_NOTAS=7;

struct Fecha{
    int dia;
    int mes;
    int anio;

    Fecha(int d=1, int m =2, int a =2000):dia(d),mes(m),anio(a){}

    //Edad en anios completos usa
    int calcularEdad() const {
        return 2026-anio;
    }

    std::string aTexto() const {
    return std::to_string(dia) + "/" +
           std::to_string(mes) + "/" +
           std::to_string(anio);
    }
};


// ─────────────────────────────────────────────
//  Clase Estudiante
// ─────────────────────────────────────────────
class Estudiante {
private:
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    Fecha       fechaNacimiento;
    Lista<double> notas;           // Lista enlazada de calificaciones
 
public:
    // Constructor principal
    Estudiante(const std::string& cedula,
               const std::string& nombres,
               const std::string& apellidos,
               const Fecha&       fechaNacimiento)
        : cedula(cedula),
          nombres(nombres),
          apellidos(apellidos),
          fechaNacimiento(fechaNacimiento)
    {}
 
    // ── Getters ───────────────────────────────
    std::string getCedula()    const { return cedula;    }
    std::string getNombres()   const { return nombres;   }
    std::string getApellidos() const { return apellidos; }
    Fecha       getFecha()     const { return fechaNacimiento; }
    int         getEdad()      const { return fechaNacimiento.calcularEdad(); }
 
    std::string getNombreCompleto() const {
        return nombres + " " + apellidos;
    }
 
    // ── Setters (para modificación de datos) ──
    void setCedula(const std::string& c)    { cedula    = c; }
    void setNombres(const std::string& n)   { nombres   = n; }
    void setApellidos(const std::string& a) { apellidos = a; }
    void setFecha(const Fecha& f)           { fechaNacimiento = f; }
 
    // ── Gestión de notas ──────────────────────
    Lista<double>& getNotas() { return notas; }
 
    bool notasLlenas() const {
        return notas.tamanio() >= MAX_NOTAS;
    }
 
    void agregarNota(double nota) {
        notas.insertarAlFinal(nota);
    }
 
    // Promedio de notas; retorna -1 si no hay notas registradas
    double calcularPromedio() const {
        if (notas.estaVacia()) return -1.0;
 
        double suma   = 0.0;
        Nodo<double>* actual = notas.inicio();
        while (actual != nullptr) {
            suma   += actual->dato;
            actual  = actual->siguiente;
        }
        return suma / notas.tamanio();
    }
};


#endif

