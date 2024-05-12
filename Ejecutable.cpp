#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct Registro{

    string usuario;
    string clave;
};

map <string, Registro> BaseDatos;

void registrarUsuario(){

    Registro usuarioNuevo;

    cout << "Ingrese un nombre de usuario: " << endl;
    cin >> usuarioNuevo.usuario;

    do {
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y numeros): " << endl;
        cin >> usuarioNuevo.clave;
        if (usuarioNuevo.clave.length() != 8){
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length() != 8);

    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    cout << "Usuario registrado exitosamente!" << endl;
}

void inicioSesion(){

    string usuario1;
    string clave1;

    cout << "Ingrese su nombre de usuario: " << endl;
    cin >> usuario1;

    cout << "Ingrese su clave: " << endl;
    cin >> clave1;

    if (BaseDatos.find(usuario1) != BaseDatos.end()){
        if (BaseDatos[usuario1].clave == clave1){
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

    Tarea(const string& _nombreT, const string& _explicacion){

        nombreT = _nombreT;
        explicacion = _explicacion;
    }

    void setNombreT(string _nombreT){

        nombreT = _nombreT;
    }

    string getNombreT(){

        return nombreT;
    }

    void setExplicacion(string _explicacion){

        explicacion = _explicacion;
    }
};

class Proyecto {

    private:

    map <string, vector<Tarea>> proyectos;

    public:

    void crearProyecto(){

        string nombreProyecto;

        cout << "Ingrese el nombre de su proyecto: " << endl;
        cin >> nombreProyecto;

        proyectos[nombreProyecto] = vector<Tarea>();

        cout << "Proyecto " << nombreProyecto << "ha sido creado exitosamente!" << endl; 
    }

    void agregarTareaAProyecto(){

        string nombreProyecto;
        string nombreTarea;
        string explicacion;

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin >> nombreProyecto;

        auto it = proyectos.find(nombreProyecto);
        if (it == proyectos.end()) {

            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        cout << "Ingrese las tareas para el proyecto " << nombreProyecto << "(Ingrese 'fin' para salir)" << endl;
        while (true) {

            cout << "Ingrese el nombre de la tarea: " << endl;
            cin >> nombreTarea;

            if (nombreTarea == "fin")
                break;
            
            cout << "Ingrese la explicacion de la tarea: " << endl;
            cin.ignore();
            getline(cin, explicacion);
            Tarea tarea(nombreTarea, explicacion);
            it -> second.push_back(tarea);
            cout << "Tarea agregada al proyecto: " << nombreProyecto << endl;
        }
    }
};
