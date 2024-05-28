#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <windows.h>
using namespace std;

// Estructura para almacenar datos de registro
struct Registro {
    string usuario;
    string clave;
};

// Mapa para almacenar datos de registro
map<string, Registro> BaseDatos;

// Función para registrar un nuevo usuario
void registrarUsuario() {
    Registro usuarioNuevo;

    cout << "Ingrese un nombre de usuario: " << endl;
    cin >> usuarioNuevo.usuario;

    do {
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y números): " << endl;
        cin >> usuarioNuevo.clave;
        if (usuarioNuevo.clave.length() != 8) {
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length() != 8);

    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    cout << "Usuario registrado exitosamente!" << endl;
}

// Función para iniciar sesión
bool inicioSesion() {
    string usuario1;
    string clave1;

    cout << "Ingrese su nombre de usuario: " << endl;
    cin >> usuario1;

    cout << "Ingrese su clave: " << endl;
    cin >> clave1;

    if (BaseDatos.find(usuario1) != BaseDatos.end()) {
        if (BaseDatos[usuario1].clave == clave1) {
            cout << "Inicio de Sesion exitoso!" << endl;
            cout << "Bienvenido(a), " << usuario1 << endl;
            return true;
        } else {
            cout << "Datos incorrectos. Por favor intente nuevamente" << endl;
            return false;
        }
    } else {
        cout << "El usuario no fue encontrado en la base de datos. Regístrese primero y luego intente de nuevo" << endl;
        return false;
    }
}

// Estructura para almacenar datos de una tarea
struct Tarea {
    string nombre;
    string estado;
    string prioridad;
    string responsable;
    string fechaLimite;
    string resumen;
};

// Estructura para almacenar detalles del proyecto
struct DetallesProyecto {
    string fechaCreacion;
    string descripcion;
};

// Clase para gestionar proyectos
class Proyecto {
private:
    map<string, pair<DetallesProyecto, vector<Tarea>>> proyectos;

public:
    // Función para exportar datos
    void exportarDatos(string nombreArchivo, string formato = "csv") {
        ofstream archivoSalida(nombreArchivo);

        if (!archivoSalida.is_open()) {
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            return;
        }

        if (formato == "csv") {
            // Exportar en formato CSV
            for (auto& proyecto : proyectos) {
                archivoSalida << proyecto.first << "," << proyecto.second.first.fechaCreacion << "," << proyecto.second.first.descripcion << endl;
                for (auto& tarea : proyecto.second.second) {
                    archivoSalida << tarea.nombre << "," << tarea.estado << "," << tarea.prioridad << "," << tarea.responsable << "," << tarea.fechaLimite << "," << tarea.resumen << endl;
                }
            }
        } else if (formato == "json") {
            // Exportar en formato JSON (implementación simplificada)
            archivoSalida << "{" << endl;
            for (auto& proyecto : proyectos) {
                archivoSalida << "  \"" << proyecto.first << "\": {" << endl;
                archivoSalida << "    \"fechaCreacion\": \"" << proyecto.second.first.fechaCreacion << "\"," << endl;
                archivoSalida << "    \"descripcion\": \"" << proyecto.second.first.descripcion << "\"," << endl;
                archivoSalida << "    \"tareas\": [" << endl;
                for (auto& tarea : proyecto.second.second) {
                    archivoSalida << "      {\"nombre\": \"" << tarea.nombre << "\", \"estado\": \"" << tarea.estado << "\", \"prioridad\": \"" << tarea.prioridad << "\", \"responsable\": \"" << tarea.responsable << "\", \"fechaLimite\": \"" << tarea.fechaLimite << "\", \"resumen\": \"" << tarea.resumen << "\"}," << endl;
                }
                archivoSalida << "    ]" << endl;
                archivoSalida << "  }," << endl;
            }
            archivoSalida << "}" << endl;
        } else {
            cout << "Formato no válido. Use 'csv' o 'json'." << endl;
        }

        archivoSalida.close();
        cout << "Datos exportados exitosamente en formato " << formato << " al archivo " << nombreArchivo << endl;
    }

    // Función para importar datos
    void importarDatos(string nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);

    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Determinar el formato del archivo
    string formato;
    if (nombreArchivo.find(".csv") != string::npos) {
        formato = "csv";
    } else if (nombreArchivo.find(".json") != string::npos) {
        formato = "json";
    } else {
        cout << "Formato de archivo no reconocido. Use .csv o .json." << endl;
        archivoEntrada.close();
        return;
    }

    // Cargar los datos según el formato
    string linea;
    if (formato == "csv") {
        // Importar desde CSV
        while (getline(archivoEntrada, linea)) {
            stringstream ss(linea);
            string nombreProyecto, fechaCreacion, descripcionProyecto;
            getline(ss, nombreProyecto, ',');
            getline(ss, fechaCreacion, ',');
            getline(ss, descripcionProyecto, ',');

            DetallesProyecto detalles = {fechaCreacion, descripcionProyecto};
            proyectos[nombreProyecto] = make_pair(detalles, vector<Tarea>());

            while (getline(archivoEntrada, linea)) {
                if (linea.empty()) break; // Fin de las tareas de este proyecto
                stringstream ssTarea(linea);
                string nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea;
                getline(ssTarea, nombreTarea, ',');
                getline(ssTarea, estadoTarea, ',');
                getline(ssTarea, prioridadTarea, ',');
                getline(ssTarea, responsableTarea, ',');
                getline(ssTarea, fechaLimiteTarea, ',');
                getline(ssTarea, resumenTarea, ',');

                proyectos[nombreProyecto].second.push_back({nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea});
            }
        }
    }

    archivoEntrada.close();
    cout << "Datos importados exitosamente desde el archivo " << nombreArchivo << endl;
}
    void crearProyecto() {
        string nombreProyecto;
        string nombreUsuario;
        string descripcionProyecto;

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin >> nombreProyecto;

        cout << "Ingrese el nombre del usuario creador: " << endl;
        cin >> nombreUsuario;

        cout << "Ingrese una breve descripcion del proyecto: " << endl;
        cin.ignore();
        getline(cin, descripcionProyecto);

        DetallesProyecto detalles = {fechaActual(), descripcionProyecto};
        proyectos[nombreProyecto] = make_pair(detalles, vector<Tarea>());

        cout << "Proyecto creado exitosamente!" << endl;
    }

    void mostrarProyectos() {
        if (proyectos.empty()) {
            cout << "No hay proyectos creados." << endl;
            return;
        }

        cout << "Lista de proyectos:" << endl;
        for (auto& proyecto : proyectos) {
            cout << " - " << proyecto.first << endl;
        }
    }

    void seleccionarProyecto(string nombreProyecto) {
        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            cout << "El proyecto " << nombreProyecto << " no existe." << endl;
            return;
        }

        cout << "Proyecto seleccionado: " << nombreProyecto << endl;

        // Opciones del menú del proyecto seleccionado
        menuProyecto(nombreProyecto);
    }

    void eliminarProyecto(string nombreProyecto) {
        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            cout << "El proyecto " << nombreProyecto << " no existe." << endl;
            return;
        }

        proyectos.erase(nombreProyecto);
        cout << "Proyecto " << nombreProyecto << " eliminado exitosamente." << endl;
    }

    void agregarTarea(string nombreProyecto) {
        string nombreTarea;
        string estadoTarea;
        string prioridadTarea;
        string responsableTarea;
        string fechaLimiteTarea;
        string resumenTarea;

        cout << "Ingrese el nombre de la tarea: " << endl;
        cin >> nombreTarea;

        cout << "Ingrese el estado de la tarea (pendiente, progreso, completada): " << endl;
        cin >> estadoTarea;

        cout << "Ingrese la prioridad de la tarea (alta, media, baja): " << endl;
        cin >> prioridadTarea;

        cout << "Ingrese el responsable de la tarea: " << endl;
        cin >> responsableTarea;

        cout << "Ingrese la fecha límite de la tarea (formato dd/mm/aaaa): " << endl;
        cin >> fechaLimiteTarea;

        cout << "Ingrese un breve resumen de la tarea: " << endl;
        cin.ignore();
        getline(cin, resumenTarea);

        proyectos[nombreProyecto].second.push_back({nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea});
         // Mostrar mensaje de éxito con el estado de la tarea en color
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (estadoTarea == "pendiente") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        } else if (estadoTarea == "progreso") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); // Amarillo
        } else if (estadoTarea == "completada") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
        cout << "Tarea agregada exitosamente al proyecto " << nombreProyecto << " con estado: " << estadoTarea << endl;
        SetConsoleTextAttribute(hConsole, 7); // Restablecer el color
        
    }

    void mostrarTareas(string nombreProyecto) {
        if (proyectos[nombreProyecto].second.empty()) {
            cout << "No hay tareas en el proyecto " << nombreProyecto << endl;
            return;
        }

        cout << "Lista de tareas del proyecto " << nombreProyecto << ":" << endl;
        for (auto& tarea : proyectos[nombreProyecto].second) {
            cout << " - " << tarea.nombre << endl;
        }
    }

    void seleccionarTarea(string nombreProyecto, string nombreTarea) {
        auto& proyecto = proyectos[nombreProyecto];
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea& tarea) {
            return tarea.nombre == nombreTarea;
        });

        if (it == proyecto.second.end()) {
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        cout << "Tarea seleccionada: " << nombreTarea << endl;

        // Opciones del menú de la tarea seleccionada
        menuTarea(nombreProyecto, nombreTarea);
    }

    void editarTarea(string nombreProyecto, string nombreTarea) {
        auto& proyecto = proyectos[nombreProyecto];
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea& tarea) {
            return tarea.nombre == nombreTarea;
        });

        if (it == proyecto.second.end()) {
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        cout << "Información actual de la tarea:" << endl;
        cout << " - Nombre: " << it->nombre << endl;
        cout << " - Estado: " << it->estado << endl;
        cout << " - Prioridad: " << it->prioridad << endl;
        cout << " - Responsable: " << it->responsable << endl;
        cout << " - Fecha Límite: " << it->fechaLimite << endl;
        cout << " - Resumen: " << it->resumen << endl;

        string nuevoEstado, nuevaPrioridad, nuevoResponsable, nuevaFechaLimite, nuevoResumen;

        cout << "¿Desea modificar el estado? (si/no): " << endl;
        cin >> nuevoEstado;
        if (nuevoEstado == "si") {
            cout << "Ingrese el nuevo estado: " << endl;
            cin >> nuevoEstado;
        } else {
            nuevoEstado = it->estado;
        }

        cout << "¿Desea modificar la prioridad? (si/no): " << endl;
        cin >> nuevaPrioridad;
        if (nuevaPrioridad == "si") {
            cout << "Ingrese la nueva prioridad: " << endl;
            cin >> nuevaPrioridad;
        } else {
            nuevaPrioridad = it->prioridad;
        }

        cout << "¿Desea modificar el responsable? (si/no): " << endl;
        cin >> nuevoResponsable;
        if (nuevoResponsable == "si") {
            cout << "Ingrese el nuevo responsable: " << endl;
            cin >> nuevoResponsable;
        } else {
            nuevoResponsable = it->responsable;
        }

        cout << "¿Desea modificar la fecha límite? (si/no): " << endl;
        cin >> nuevaFechaLimite;
        if (nuevaFechaLimite == "si") {
            cout << "Ingrese la nueva fecha límite: " << endl;
            cin >> nuevaFechaLimite;
        } else {
            nuevaFechaLimite = it->fechaLimite;
        }

        cout << "¿Desea modificar el resumen? (si/no): " << endl;
        cin >> nuevoResumen;
        if (nuevoResumen == "si") {
            cout << "Ingrese el nuevo resumen: " << endl;
            cin.ignore();
            getline(cin, nuevoResumen);
        } else {
            nuevoResumen = it->resumen;
        }
        
        
        it->estado = nuevoEstado;
        it->prioridad = nuevaPrioridad;
        it->responsable = nuevoResponsable;
        it->fechaLimite = nuevaFechaLimite;
        it->resumen = nuevoResumen;

        // Mostrar mensaje de éxito con el nuevo estado de la tarea en color
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (nuevoEstado == "pendiente") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        } else if (nuevoEstado == "progreso") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); // Amarillo
        } else if (nuevoEstado == "completado") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
        cout << "Tarea modificada exitosamente! Nuevo estado: " << nuevoEstado << endl;
        SetConsoleTextAttribute(hConsole, 7); // Restablecer el color
    }

    void cambiarEstadoTarea(string nombreProyecto, string nombreTarea, string nuevoEstado) {
        auto& proyecto = proyectos[nombreProyecto];
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea& tarea) {
            return tarea.nombre == nombreTarea;
        });

        if (it == proyecto.second.end()) {
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        if (nuevoEstado != "pendiente" && nuevoEstado != "en progreso" && nuevoEstado != "completada") {
            cout << "Estado inválido. Ingrese: pendiente, en progreso o completada." << endl;
            return;
        }

        it->estado = nuevoEstado;
        cout << "El estado de la tarea " << nombreTarea << " se ha cambiado a " << nuevoEstado << endl;
    }

    void eliminarTarea(string nombreProyecto, string nombreTarea) {
        auto& proyecto = proyectos[nombreProyecto];
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea& tarea) {
            return tarea.nombre == nombreTarea;
        });

        if (it == proyecto.second.end()) {
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        proyecto.second.erase(it);
        cout << "La tarea " << nombreTarea << " se ha eliminado del proyecto " << nombreProyecto << endl;
    }

    void guardarProyectos(string nombreArchivo) {
        ofstream archivoSalida(nombreArchivo);

        if (!archivoSalida.is_open()) {
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            return;
        }

        for (auto& proyecto : proyectos) {
            archivoSalida << proyecto.first << endl;
            archivoSalida << proyecto.second.first.fechaCreacion << endl;
            archivoSalida << proyecto.second.first.descripcion << endl;

            for (auto& tarea : proyecto.second.second) {
                archivoSalida << tarea.nombre << endl;
                archivoSalida << tarea.estado << endl;
                archivoSalida << tarea.prioridad << endl;
                archivoSalida << tarea.responsable << endl;
                archivoSalida << tarea.fechaLimite << endl;
                archivoSalida << tarea.resumen << endl;
            }
        }

        archivoSalida.close();
        cout << "Proyectos guardados exitosamente en el archivo " << nombreArchivo << endl;
    }

    void cargarProyectos(string nombreArchivo) {
        ifstream archivoEntrada(nombreArchivo);

        if (!archivoEntrada.is_open()) {
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            return;
        }

        proyectos.clear();

        string nombreProyecto;
        string fechaCreacion;
        string descripcionProyecto;
        string nombreTarea;
        string estadoTarea;
        string prioridadTarea;
        string responsableTarea;
        string fechaLimiteTarea;
        string resumenTarea;

        while (getline(archivoEntrada, nombreProyecto)) {
            getline(archivoEntrada, fechaCreacion);
            getline(archivoEntrada, descripcionProyecto);

            DetallesProyecto detalles = {fechaCreacion, descripcionProyecto};
            proyectos[nombreProyecto] = make_pair(detalles, vector<Tarea>());

            while (getline(archivoEntrada, nombreTarea)) {
                getline(archivoEntrada, estadoTarea);
                getline(archivoEntrada, prioridadTarea);
                getline(archivoEntrada, responsableTarea);
                getline(archivoEntrada, fechaLimiteTarea);
                getline(archivoEntrada, resumenTarea);

                proyectos[nombreProyecto].second.push_back({nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea});
            }
        }

        archivoEntrada.close();
        cout << "Proyectos cargados exitosamente desde el archivo " << nombreArchivo << endl;
    }

private:
    string fechaActual() {
        time_t tiempo = time(NULL);
        tm* tiempoLocal = localtime(&tiempo);
        char buffer[80];
        strftime(buffer, 80, "%d/%m/%Y", tiempoLocal);
        return string(buffer);
    }

    void menuProyecto(string nombreProyecto) {
        while (true) {
            cout << "\nMenú del Proyecto " << nombreProyecto << ":" << endl;
            cout << "1. Seleccionar tarea" << endl;
            cout << "2. Agregar tarea" << endl;
            cout << "3. Eliminar proyecto" << endl;
            cout << "4. Editar detalles del proyecto" << endl;
            cout << "5. Guardar proyecto en archivo" << endl;
            cout << "6. Cargar proyecto desde archivo" << endl;
            cout << "0. Volver al menú principal" << endl;

            int opcion;
            cout << "Ingrese una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarTareas(nombreProyecto);
                    cout << "Ingrese el nombre de la tarea a seleccionar: ";
                    {
                        string nombreTarea;
                        cin >> nombreTarea;
                        seleccionarTarea(nombreProyecto, nombreTarea);
                    }
                    break;
                case 2:
                    agregarTarea(nombreProyecto);
                    break;
                case 3:
                    eliminarProyecto(nombreProyecto);
                    return; // Salir del menú del proyecto
                case 4:
                    // Editar detalles del proyecto (opcional, no implementado en este ejemplo)
                    break;
                case 5:
                    guardarProyectos(nombreProyecto + ".txt");
                    break;
                case 6:
                    cargarProyectos(nombreProyecto + ".txt");
                    break;
                case 0:
                    return; // Salir del menú del proyecto
                default:
                    cout << "Opción inválida. Intente nuevamente." << endl;
            }
        }
    }

    void menuTarea(string nombreProyecto, string nombreTarea) {
        while (true) {
            cout << "\nMenú de la Tarea " << nombreTarea << " (Proyecto: " << nombreProyecto << "):" << endl;
            cout << "1. Cambiar estado" << endl;
            cout << "2. Editar tarea" << endl;
            cout << "3. Eliminar tarea" << endl;
            cout << "0. Volver al menú del proyecto" << endl;

            int opcion;
            cout << "Ingrese una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    cout << "Ingrese el nuevo estado (pendiente, en progreso, completada): ";
                    {
                        string nuevoEstado;
                        cin >> nuevoEstado;
                        cambiarEstadoTarea(nombreProyecto, nombreTarea, nuevoEstado);
                    }
                    break;
                case 2:
                    editarTarea(nombreProyecto, nombreTarea);
                    break;
                case 3:
                    eliminarTarea(nombreProyecto, nombreTarea);
                    return; // Salir del menú de la tarea
                case 0:
                    return; // Salir del menú de la tarea
                default:
                    cout << "Opción inválida. Intente nuevamente." << endl;
            }
        }
    }

public:
    void menuPrincipal() {
        while (true) {
            cout << "\nMenú Principal:" << endl;
            cout << "1. Crear proyecto" << endl;
            cout << "2. Mostrar proyectos" << endl;
            cout << "3. Seleccionar proyecto" << endl;
            cout << "4. Exportar datos" << endl;
            cout << "5. Importar datos" << endl;
            cout << "0. Salir" << endl;

            int opcion;
            cout << "Ingrese una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    crearProyecto();
                    break;
                case 2:
                    mostrarProyectos();
                    break;
                case 3:
                    cout << "Ingrese el nombre del proyecto a seleccionar: ";
                    {
                        string nombreProyecto;
                        cin >> nombreProyecto;
                        seleccionarProyecto(nombreProyecto);
                    }
                    break;
                case 4: { 
                    string nombreArchivo, formato;
                    cout << "Ingrese el nombre del archivo para exportar: ";
                    cin >> nombreArchivo;

                    cout << "Ingrese el formato (csv o json, csv por defecto): ";
                    cin >> formato;

                    exportarDatos(nombreArchivo, formato);
                    break;
                }

                case 5: { 
                    string nombreArchivo;
                    cout << "Ingrese el nombre del archivo para importar: ";
                    cin >> nombreArchivo;
                    
                    // Verificar si el archivo existe antes de importar
                    if (!filesystem::exists(nombreArchivo)) {
                        cout << "El archivo " << nombreArchivo << " no existe." << endl;
                    } else {
                        importarDatos(nombreArchivo);
                    }
                    break;
                }
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    return;
                default:
                    cout << "Opción inválida. Intente nuevamente." << endl;
            }
        }
    }
};

int main() {
    int opcion;

    while (true) {
        cout << "Menú de Inicio:" << endl;
        cout << "1. Registrar usuario" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "0. Salir" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarUsuario();
                break;
            case 2: {
                if (inicioSesion()) {
                    Proyecto proyecto;
                    proyecto.menuPrincipal();
                }
                break;
            }
            case 0:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    }

  return 0;
}



