#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>
#include <string>
#include "Estudiante.h"
#include "Curso.h"

// ─────────────────────────────────────────────
//  Utilidades de entrada
// ─────────────────────────────────────────────

// Lee una cadena no vacía
std::string leerCadena(const std::string& etiqueta) {
    std::string valor;
    do {
        std::cout << etiqueta;
        std::getline(std::cin, valor);
        if (valor.empty())
            std::cout << "  El campo no puede estar vacio. Intente de nuevo.\n";
    } while (valor.empty());
    return valor;
}

// Lee un entero dentro de un rango usando una cadena intermedia
int leerEntero(const std::string& etiqueta, int minimo, int maximo) {
    while (true) {
        std::cout << etiqueta;
        std::string entrada;
        std::getline(std::cin, entrada);
        int valor = atoi(entrada.c_str());
        if (valor >= minimo && valor <= maximo)
            return valor;
        std::cout << "  Valor invalido. Ingrese un numero entre "
                  << minimo << " y " << maximo << ".\n";
    }
}

// Lee un número real en [0, 10] usando una cadena intermedia
double leerNota(const std::string& etiqueta) {
    while (true) {
        std::cout << etiqueta;
        std::string entrada;
        std::getline(std::cin, entrada);
        double valor = atof(entrada.c_str());
        if (valor >= 0.0 && valor <= 10.0)
            return valor;
        std::cout << "  Nota invalida. Debe estar entre 0.0 y 10.0.\n";
    }
}

// Lee una fecha válida
Fecha leerFecha(const std::string& etiqueta) {
    std::cout << etiqueta << "\n";
    int dia  = leerEntero("  Dia  (1-31):      ", 1, 31);
    int mes  = leerEntero("  Mes  (1-12):      ", 1, 12);
    int anio = leerEntero("  Anio (1900-2026): ", 1900, 2026);
    return Fecha(dia, mes, anio);
}

// Pregunta si/no y retorna true si el usuario elige 's'
bool preguntarSiNo(const std::string& mensaje) {
    std::string respuesta;
    do {
        std::cout << mensaje << " (s/n): ";
        std::getline(std::cin, respuesta);
    } while (respuesta != "s" && respuesta != "n" &&
             respuesta != "S" && respuesta != "N");
    return (respuesta == "s" || respuesta == "S");
}

// ─────────────────────────────────────────────
//  Utilidades de visualización
// ─────────────────────────────────────────────

void mostrarSeparador(char caracter = '-', int largo = 50) {
    std::cout << std::string(largo, caracter) << "\n";
}

// Muestra los datos básicos de un estudiante en una línea
void mostrarFilaEstudiante(int numero, const Estudiante* e) {
    std::cout << numero << ". "
              << e->getCedula()    << " | "
              << e->getNombres()   << " "
              << e->getApellidos() << " | "
              << e->getFecha().aTexto() << "\n";
}

// Lista todos los estudiantes del curso
void listarEstudiantes(const Curso& curso) {
    if (curso.estaVacio()) {
        std::cout << "\n  No hay estudiantes registrados.\n";
        return;
    }

    mostrarSeparador('=', 60);
    std::cout << "  No. | Cedula | Nombre completo | Nacimiento\n";
    mostrarSeparador('=', 60);

    Nodo<Estudiante*>* actual = curso.getEstudiantes().inicio();
    int numero = 1;
    while (actual != nullptr) {
        mostrarFilaEstudiante(numero++, actual->dato);
        actual = actual->siguiente;
    }
    mostrarSeparador('-', 60);
}

// Muestra el resumen de un estudiante (para opciones 2 y 3)
void mostrarResumenEstudiante(const Estudiante* e) {
    mostrarSeparador();
    std::cout << "  Nombre : " << e->getNombreCompleto() << "\n"
              << "  Cedula : " << e->getCedula()         << "\n"
              << "  Edad   : " << e->getEdad()           << " anios\n";
    mostrarSeparador();
}

// Lista las notas de un estudiante con su posición
void listarNotas(const Estudiante* e) {
    const Lista<double>& notas = const_cast<Estudiante*>(e)->getNotas();

    if (notas.estaVacia()) {
        std::cout << "  (Sin calificaciones registradas)\n";
        return;
    }

    std::cout << "  Calificaciones registradas:\n";
    Nodo<double>* actual = notas.inicio();
    int pos = 1;
    while (actual != nullptr) {
        std::cout << "    " << pos++ << ". " << actual->dato << "\n";
        actual = actual->siguiente;
    }
}

#endif // CONSOLA_H