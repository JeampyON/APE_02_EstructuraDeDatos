#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Curso.h"
#include "Consola.h"

// ─────────────────────────────────────────────
//  Opción 1 – Gestión de estudiantes
// ─────────────────────────────────────────────

void insertarEstudiante(Curso& curso) {
    if (curso.estaLleno()) {
        std::cout << "El curso ya esta lleno (" << MAX_ESTUDIANTES << " estudiantes).\n";
        return;
    }

    bool continuar = true;
    while (continuar && !curso.estaLleno()) {
        std::string cedula    = leerCadena("Cedula    : ");
        if (curso.buscar(cedula) != nullptr) {
            std::cout << "Ya existe un estudiante con esa cedula.\n";
        } else {
            std::string nombres   = leerCadena("Nombres   : ");
            std::string apellidos = leerCadena("Apellidos : ");
            Fecha fecha           = leerFecha("Fecha de nacimiento:");
            curso.agregar(new Estudiante(cedula, nombres, apellidos, fecha));
            std::cout << "Estudiante registrado.\n";
        }
        if (!curso.estaLleno())
            continuar = preguntarSiNo("Registrar otro estudiante?");
        else
            std::cout << "Se alcanzo el maximo de estudiantes.\n";
    }
}

void modificarEstudiante(Curso& curso) {
    if (curso.estaVacio()) {
        std::cout << "No hay estudiantes registrados.\n";
        return;
    }

    bool continuar = true;
    while (continuar) {
        listarEstudiantes(curso);
        int pos       = leerEntero("Numero a modificar: ", 1, curso.cantidad());
        Estudiante* e = curso.obtenerPorPosicion(pos);

        std::cout << "(Enter para conservar el valor actual)\n";

        std::string entrada;
        std::cout << "Nombres [" << e->getNombres() << "]: ";
        std::getline(std::cin, entrada);
        if (!entrada.empty()) e->setNombres(entrada);

        std::cout << "Apellidos [" << e->getApellidos() << "]: ";
        std::getline(std::cin, entrada);
        if (!entrada.empty()) e->setApellidos(entrada);

        std::cout << "Cedula [" << e->getCedula() << "]: ";
        std::getline(std::cin, entrada);
        if (!entrada.empty()) {
            if (curso.buscar(entrada) != nullptr && entrada != e->getCedula())
                std::cout << "Esa cedula ya pertenece a otro estudiante.\n";
            else
                e->setCedula(entrada);
        }

        if (preguntarSiNo("Modificar fecha de nacimiento?"))
            e->setFecha(leerFecha("Nueva fecha:"));

        std::cout << "Datos actualizados.\n";
        continuar = preguntarSiNo("Modificar otro estudiante?");
    }
}

void eliminarEstudiante(Curso& curso) {
    if (curso.estaVacio()) {
        std::cout << "No hay estudiantes registrados.\n";
        return;
    }

    bool continuar = true;
    while (continuar && !curso.estaVacio()) {
        listarEstudiantes(curso);
        int pos       = leerEntero("Numero a eliminar: ", 1, curso.cantidad());
        Estudiante* e = curso.obtenerPorPosicion(pos);

        std::cout << "Estudiante: " << e->getNombreCompleto() << "\n";
        if (preguntarSiNo("Confirma la eliminacion?")) {
            curso.eliminar(pos);
            std::cout << "Estudiante eliminado.\n";
        } else {
            std::cout << "Eliminacion cancelada.\n";
        }

        if (!curso.estaVacio())
            continuar = preguntarSiNo("Eliminar otro estudiante?");
    }
}

void menuEstudiantes(Curso& curso) {
    int opcion;
    do {
        std::cout << "\n=== ESTUDIANTES ===\n"
                  << "1. Listar\n"
                  << "2. Insertar\n"
                  << "3. Modificar\n"
                  << "4. Eliminar\n"
                  << "0. Volver\n";
        opcion = leerEntero("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: listarEstudiantes(curso);   break;
            case 2: insertarEstudiante(curso);  break;
            case 3: modificarEstudiante(curso); break;
            case 4: eliminarEstudiante(curso);  break;
        }
    } while (opcion != 0);
}

// ─────────────────────────────────────────────
//  Opción 2 – Registro de calificaciones
// ─────────────────────────────────────────────

void gestionarNotas(Estudiante* e) {
    mostrarResumenEstudiante(e);

    int opcion;
    do {
        listarNotas(e);
        Lista<double>& notas = e->getNotas();

        std::cout << "\nCalificaciones: " << notas.tamanio() << "/" << MAX_NOTAS << "\n"
                  << "1. Agregar\n"
                  << "2. Modificar\n"
                  << "3. Eliminar\n"
                  << "0. Volver\n";
        opcion = leerEntero("Opcion: ", 0, 3);

        switch (opcion) {
            case 1:
                if (e->notasLlenas()) {
                    std::cout << "Ya se ingresaron todas las calificaciones posibles.\n";
                } else {
                    bool continuar = true;
                    while (continuar && !e->notasLlenas()) {
                        e->agregarNota(leerNota("Nueva calificacion (0-10): "));
                        std::cout << "Calificacion agregada.\n";
                        if (e->notasLlenas())
                            std::cout << "Se alcanzaron todas las calificaciones posibles.\n";
                        else
                            continuar = preguntarSiNo("Agregar otra?");
                    }
                }
                break;

            case 2:
                if (notas.estaVacia()) {
                    std::cout << "No hay calificaciones para modificar.\n";
                } else {
                    int pos = leerEntero("Numero a modificar: ", 1, notas.tamanio());
                    notas.modificar(pos, leerNota("Nuevo valor (0-10): "));
                    std::cout << "Calificacion actualizada.\n";
                }
                break;

            case 3:
                if (notas.estaVacia()) {
                    std::cout << "No hay calificaciones para eliminar.\n";
                } else {
                    int pos = leerEntero("Numero a eliminar: ", 1, notas.tamanio());
                    notas.eliminar(pos);
                    std::cout << "Calificacion eliminada.\n";
                }
                break;
        }
    } while (opcion != 0);
}

void menuCalificaciones(Curso& curso) {
    bool continuar = true;
    while (continuar) {
        std::string cedula = leerCadena("Cedula del estudiante: ");
        Estudiante* e      = curso.buscar(cedula);

        if (e != nullptr) {
            gestionarNotas(e);
            continuar = false;
        } else {
            std::cout << "No se encontro un estudiante con cedula: " << cedula << "\n";
            continuar = preguntarSiNo("Ingresar otra cedula?");
        }
    }
}

// ─────────────────────────────────────────────
//  Opción 3 – Promedio de un estudiante
// ─────────────────────────────────────────────

void menuPromedioEstudiante(Curso& curso) {
    std::string cedula = leerCadena("Cedula del estudiante: ");
    Estudiante* e      = curso.buscar(cedula);

    if (e == nullptr) {
        std::cout << "No se encontro un estudiante con cedula: " << cedula << "\n";
        return;
    }

    mostrarResumenEstudiante(e);
    listarNotas(e);

    double promedio = e->calcularPromedio();
    if (promedio < 0.0)
        std::cout << "El estudiante no tiene calificaciones registradas.\n";
    else
        std::cout << "Promedio: " << promedio << "\n";
}

// ─────────────────────────────────────────────
//  Opción 4 – Promedio general del curso
// ─────────────────────────────────────────────

void menuPromedioCurso(Curso& curso) {
    if (!curso.algunoTieneNotas()) {
        std::cout << "No se han registrado calificaciones de estudiantes.\n";
        return;
    }
    std::cout << "Promedio general del curso: " << curso.calcularPromedioGeneral() << "\n";
}

#endif // MENU_H
