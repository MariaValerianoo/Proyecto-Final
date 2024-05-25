#include <iostream>

using namespace std;


void agregarNotaAProyecto() {
    string nombreProyecto, titulo, descripcion;

    cout << "Ingrese el nombre del proyecto: " << endl;
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, nombreProyecto);

    // Validar si el proyecto existe
    if (proyectos.find(nombreProyecto) == proyectos.end()) {
        cout << "Proyecto " << nombreProyecto << " no existe" << endl;
        return;
    }

    cout << "Ingrese el título de la nota: " << endl;
    getline(cin, titulo);

    // Validar que el título no esté vacío
    if (titulo.empty()) {
        cout << "El título de la nota no puede estar vacío." << endl;
        return;
    }

    cout << "Ingrese la descripción de la nota (opcional): " << endl;
    getline(cin, descripcion);

    // Obtener el nombre del usuario actual (implementa según tu lógica)
    string autor = "usuario_actual"; // Reemplaza con el nombre real del usuario

    // Crear la nota y agregarla al proyecto
    Nota nuevaNota = {titulo, autor, descripcion};
    notasProyecto[nombreProyecto].push_back(nuevaNota);

    cout << "Nota agregada al proyecto: " << nombreProyecto << endl;
}