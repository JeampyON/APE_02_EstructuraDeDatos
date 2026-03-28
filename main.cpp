#include <iostream>
#include "Curso.h"
#include "Consola.h"
#include "Menu.h"

int main() {
    Curso curso;
    int   opcion;

    do {
        std::cout << "\n=== GESTOR DE ESTUDIANTES ===\n"
                  << "1. Estudiantes\n"
                  << "2. Registro de calificaciones\n"
                  << "3. Promedio de notas de un estudiante\n"
                  << "4. Promedio de notas del curso\n"
                  << "0. Salir\n";
        opcion = leerEntero("Opcion: ", 0, 4);

        switch (opcion) {
            case 1: menuEstudiantes(curso);        break;
            case 2: menuCalificaciones(curso);     break;
            case 3: menuPromedioEstudiante(curso); break;
            case 4: menuPromedioCurso(curso);      break;
        }
    } while (opcion != 0);

    std::cout << "Hasta luego.\n";
    return 0;
}