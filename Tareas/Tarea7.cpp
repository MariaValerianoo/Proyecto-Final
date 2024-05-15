#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct Registro {
    string usuario;
    string clave;
};

map<string, Registro> BaseDatos;

void registrarUsuario() {
    Registro usuarioNuevo;

    cout << "Ingrese un nombre de usuario: " << endl;
    cin >> usuarioNuevo.usuario;

    do {
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y numeros): " << endl;
        cin >> usuarioNuevo.clave;
        if (usuarioNuevo.clave.length() != 8) {
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length() != 8);

    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    cout << "Usuario registrado exitosamente!" << endl;
}

void inicioSesion() {
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
        } else {
            cout << "Datos incorrectos. Por favor intente nuevamente" << endl;
        }
    } else {
        cout << "El usuario no fue encontrado en la base de datos. Registrese primero y luego intente de nuevo" << endl;
    }
}

class Tarea {
private:
    string nombreT;
    string explicacion;

public:
    Tarea(const string& _nombreT, const string& _explicacion) {
        nombreT = _nombreT;
        explicacion = _explicacion;
    }

    void setNombreT(const string _nombreT) {
        nombreT = _nombreT;
    }

    string getNombreT() const {
        return nombreT;
    }

    void setExplicacion(const string _explicacion) {
        explicacion = _explicacion;
    }

    string getExplicacion() const {
        return explicacion;
    }
};

struct DetallesProyecto {
    string nombrePropietario;
    string estado;
};

class Proyecto {
private:
    map<string, pair<DetallesProyecto, vector<Tarea>>> proyectos;

public:
    void crearProyecto() {
        string nombreProyecto;
        string nombrePropietario;
        string estado;

        cout << "Ingrese el nombre de su proyecto: " << endl;
        getline(cin, nombreProyecto);

        cout << "Ingrese el nombre del propietario: " << endl;
        getline(cin, nombrePropietario);

        cout << "Ingrese el estado del proyecto: " << endl;
        getline(cin, estado);

        proyectos[nombreProyecto].first = { nombrePropietario, estado };
        proyectos[nombreProyecto].second = vector<Tarea>();

        cout << "Proyecto " << nombreProyecto << " ha sido creado exitosamente!" << endl;
        cout << "Propietario: " << nombrePropietario << endl;
        cout << "Estado: " << estado << endl;
    }

    void agregarTareaAProyecto() {
        string nombreProyecto;
        string nombreTarea;
        string explicacion;

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        cout << "Ingrese las tareas para el proyecto " << nombreProyecto << "(Ingrese 'fin' para salir)" << endl;
        while (true) {
            cout << "Ingrese el nombre de la tarea: " << endl;
            getline(cin, nombreTarea);

            if (nombreTarea == "fin")
                break;

            cout << "Ingrese la explicacion de la tarea: " << endl;
            cin.ignore();
            getline(cin, explicacion);
            Tarea tarea(nombreTarea, explicacion);
            it->second.second.push_back(tarea);
            cout << "Tarea agregada al proyecto: " << nombreProyecto << endl;
        }
    }

    void buscarProyectoXNombre() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        string nombreBusqueda;

        cout << "Ingrese el nombre del proyecto del que desea ver las tareas: " << endl;
        cin.ignore();
        getline(cin, nombreBusqueda);

        auto it = proyectos.find(nombreBusqueda);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreBusqueda << " no encontrado" << endl;
            return;
        }

        cout << "Tareas del proyecto " << nombreBusqueda << ":" << endl;
        for (const auto& tarea : it->second.second) {
            cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
        }
    }

    void mostrarDetallesProyecto() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

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

    // Nueva función para visualizar tareas por proyecto
    void visualizarTareasPorProyecto() {
        if (proyectos.empty()) {
            cout << "No hay proyectos disponibles" << endl;
            return;
        }

        cout << "Ingrese el nombre del proyecto que desea visualizar: " << endl;
        cin.ignore();
        string nombreProyecto;
        getline(cin, nombreProyecto);

        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no encontrado" << endl;
            return;
        }

        cout << "Detalles del proyecto " << nombreProyecto << ":" << endl;
        cout << "Propietario: " << it->second.first.nombrePropietario << endl;
        cout << "Estado: " << it->second.first.estado << endl;
        cout << "Tareas asociadas:" << endl;
        for (const auto& tarea : it->second.second) {
            cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
        }
        cout << "-------------------------" << endl;
    }
};