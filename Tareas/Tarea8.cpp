#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Estructura para almacenar la información de un usuario
struct Registro {
    string usuario; // Nombre de usuario
    string clave;   // Clave del usuario
};

// Base de datos simulada para almacenar los usuarios registrados
map<string, Registro> BaseDatos;

// Función para registrar un nuevo usuario
void registrarUsuario() {
    Registro usuarioNuevo;

    // Solicita al usuario que ingrese un nombre de usuario
    cout << "Ingrese un nombre de usuario: " << endl;
    cin >> usuarioNuevo.usuario;

    // Solicita al usuario que ingrese una clave de 8 caracteres
    do {
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y números): " << endl;
        cin >> usuarioNuevo.clave;
        if (usuarioNuevo.clave.length() != 8) {
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length() != 8);

    // Agrega el nuevo usuario a la base de datos
    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    cout << "Usuario registrado exitosamente!" << endl;
}

// Función para iniciar sesión de un usuario
void inicioSesion() {
    string usuario1;
    string clave1;

    // Solicita al usuario que ingrese su nombre de usuario y clave
    cout << "Ingrese su nombre de usuario: " << endl;
    cin >> usuario1;
    cout << "Ingrese su clave: " << endl;
    cin >> clave1;

    // Verifica si el usuario existe en la base de datos y si la clave es correcta
    if (BaseDatos.find(usuario1) != BaseDatos.end()) {
        if (BaseDatos[usuario1].clave == clave1) {
            cout << "Inicio de Sesion exitoso!" << endl;
            cout << "Bienvenido(a), " << usuario1 << endl;
        } else {
            cout << "Datos incorrectos. Por favor intente nuevamente" << endl;
        }
    } else {
        cout << "El usuario no fue encontrado en la base de datos. Regístrese primero y luego intente de nuevo" << endl;
    }
}

// Clase para manejar las tareas de un proyecto
class Tarea {
private:
    string nombreT;    // Nombre de la tarea
    string explicacion; // Explicación de la tarea
    string estado;      // Estado de la tarea

public:
    // Constructor de la clase Tarea
    Tarea(const string& _nombreT, const string& _explicacion, const string& _estado) {
        nombreT = _nombreT;
        explicacion = _explicacion;
        estado = _estado;
    }

    // Setter para el nombre de la tarea
    void setNombreT(const string _nombreT) {
        nombreT = _nombreT;
    }

    // Getter para el nombre de la tarea
    string getNombreT() const {
        return nombreT;
    }

    // Setter para la explicación de la tarea
    void setExplicacion(const string _explicacion) {
        explicacion = _explicacion;
    }

    // Getter para la explicación de la tarea
    string getExplicacion() const {
        return explicacion;
    }

    // Setter para el estado de la tarea
    void setEstado(const string& _estado) {
        estado = _estado;
    }

    // Getter para el estado de la tarea
    string getEstado() const {
        return estado;
    }
};

// Estructura para los detalles del proyecto
struct DetallesProyecto {
    string nombrePropietario; // Nombre del propietario del proyecto
    string estado;            // Estado del proyecto
};

// Clase para manejar proyectos, cada uno con múltiples tareas
class Proyecto {
private:
    // Mapa para almacenar proyectos con sus detalles y tareas
    map<string, pair<DetallesProyecto, vector<Tarea>>> proyectos;

public:
    // Función para crear un nuevo proyecto
    void crearProyecto() {
        string nombreProyecto;
        string nombrePropietario;
        string estado;

        // Solicita al usuario que ingrese los detalles del proyecto
        cout << "Ingrese el nombre de su proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        cout << "Ingrese el nombre del propietario: " << endl;
        getline(cin, nombrePropietario);

        cout << "Ingrese el estado del proyecto: " << endl;
        getline(cin, estado);

        // Agrega el nuevo proyecto al mapa de proyectos
        proyectos[nombreProyecto].first = { nombrePropietario, estado };
        proyectos[nombreProyecto].second = vector<Tarea>();

        cout << "Proyecto " << nombreProyecto << " ha sido creado exitosamente!" << endl;
        cout << "Propietario: " << nombrePropietario << endl;
        cout << "Estado: " << estado << endl;
    }

    // Función para agregar tareas a un proyecto existente
    void agregarTareaAProyecto() {
        string nombreProyecto;
        string nombreTarea;
        string explicacion;
        string estado; // Atributo agregado para poder establecer el estado de una tarea

        // Solicita al usuario que ingrese el nombre del proyecto
        cout << "Ingrese el nombre del proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        // Busca el proyecto en el mapa de proyectos
        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        // Solicita al usuario que ingrese las tareas para el proyecto
        cout << "Ingrese las tareas para el proyecto " << nombreProyecto << "(Ingrese 'fin' para salir)" << endl;
        while (true) {
            cout << "Ingrese el nombre de la tarea: " << endl;
            getline(cin, nombreTarea);

            if (nombreTarea == "fin")
                break;

            cout << "Ingrese la explicacion de la tarea: " << endl;
            getline(cin, explicacion);

            cout << "Ingrese el estado de la tarea: " << endl;
            getline(cin, estado);

            Tarea tarea(nombreTarea, explicacion, estado);
            it->second.second.push_back(tarea);
            cout << "Tarea agregada al proyecto: " << nombreProyecto << endl;
        }
    }

    // Función para buscar un proyecto por su nombre y mostrar sus tareas
    void buscarProyectoXNombre() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        string nombreBusqueda;

        // Solicita al usuario que ingrese el nombre del proyecto a buscar
        cout << "Ingrese el nombre del proyecto del que desea ver las tareas: " << endl;
        cin.ignore();
        getline(cin, nombreBusqueda);

        // Busca el proyecto en el mapa de proyectos
        auto it = proyectos.find(nombreBusqueda);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreBusqueda << " no encontrado" << endl;
            return;
        }

        // Muestra las tareas del proyecto encontrado
        cout << "Tareas del proyecto " << nombreBusqueda << ":" << endl;
        for (const auto& tarea : it->second.second) {
            cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
        }
    }

    // Función para mostrar los detalles de todos los proyectos
    void mostrarDetallesProyecto() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        // Muestra los detalles de cada proyecto
        cout << "Detalles de los proyectos:" << endl;
        for (const auto& proyecto : proyectos) {
            cout << "Nombre del proyecto: " << proyecto.first << endl;
            cout << "Propietario: " << proyecto.second.first.nombrePropietario << endl;
            cout << "Estado: " << proyecto.second.first.estado << endl;
            cout << "Tareas asociadas:" << endl;
            for (const auto& tarea : proyecto.second.second) {
                cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
            }
            cout << "-------------------------" << endl;
        }
    }

    // Función para visualizar las tareas de un proyecto específico
    void visualizarTareasPorProyecto() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        // Solicita al usuario que ingrese el nombre del proyecto a visualizar
        cout << "Ingrese el nombre del proyecto que desea visualizar: " << endl;
        cin.ignore();
        string nombreProyecto;
        getline(cin, nombreProyecto);

        // Busca el proyecto en el mapa de proyectos
        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no encontrado" << endl;
            return;
        }

        // Muestra los detalles y las tareas del proyecto encontrado
        cout << "Detalles del proyecto " << nombreProyecto << ":" << endl;
        cout << "Propietario: " << it->second.first.nombrePropietario << endl;
        cout << "Estado: " << it->second.first.estado << endl;
        cout << "Tareas asociadas:" << endl;
        for (const auto& tarea : it->second.second) {
            cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
        }
        cout << "-------------------------" << endl;
    }

    // Función para visualizar los estados de las tareas de un proyecto específico
    void visualizarEstadosDeTareas() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        // Solicita al usuario que ingrese el nombre del proyecto para ver los estados de las tareas
        cout << "Ingrese el nombre del proyecto para ver los estados de las tareas: " << endl;
        cin.ignore();
        string nombreProyecto;
        getline(cin, nombreProyecto);

        // Busca el proyecto en el mapa de proyectos
        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no encontrado" << endl;
            return;
        }

        // Muestra los estados de las tareas del proyecto encontrado
        cout << "Estados de las tareas del proyecto " << nombreProyecto << ":" << endl;
        for (const auto& tarea : it->second.second) {
            cout << "Nombre: " << tarea.getNombreT() << ", Estado: " << tarea.getEstado() << endl;
        }
        cout << "-------------------------" << endl;
    }
};




