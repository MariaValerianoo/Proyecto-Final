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
        if (usuarioNuevo.clave.length()!= 8){
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length()!= 8);

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

    if (BaseDatos.find(usuario1)!= BaseDatos.end()){
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

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para almacenar datos de usuarios
struct Registro {
    string usuario;
    string clave;
};

// Base de datos de usuarios (mapa)
map<string, Registro> BaseDatos;

// Estructura para almacenar detalles de una nota
struct Nota {
    string titulo;
    string autor;
    string descripcion;
};

// Estructura para almacenar detalles de un proyecto
struct DetallesProyecto {
    string nombrePropietario;
    string estado;
};

// Clase para representar una tarea
class Tarea {
private:
    string nombreT;
    string explicacion;

public:
    Tarea(const string& _nombreT, const string& _explicacion) : nombreT(_nombreT), explicacion(_explicacion) {}

    void setNombreT(const string& _nombreT) {
        nombreT = _nombreT;
    }

    string getNombreT() const {
        return nombreT;
    }

    void setExplicacion(const string& _explicacion) {
        explicacion = _explicacion;
    }

    string getExplicacion() const {
        return explicacion;
    }
};

// Clase para representar un proyecto (con notas)
class Proyecto {
private:
    map<string, pair<DetallesProyecto, vector<Tarea>>> proyectos;
    map<string, vector<Nota>> notasProyecto; // Mapa para notas por proyecto

public:
    void crearProyecto() {
        //Inicializamos las variables necesarias
        string nombreProyecto;
        string nombrePropietario;
        string estado;

        //Se muestra mensaje por consola para que se ingrese el nombre dle proyecto
        cout << "Ingrese el nombre de su proyecto: " << endl;
        //Se almacena en la variables creada con getline para prevenir errores del usuario
        getline(cin,nombreProyecto);

        //Se muestra mensaje por consola para que se ingrese el nombre del propietario
        cout << "Ingrese el nombre del propietario: " << endl;
        //Se almacena en la variables creada con getline para prevenir errores del usuario
        getline(cin,nombrePropietario);

        //Se muestra mensaje por consola para que se ingrese el estado del proyecto
        cout << "Ingrese el estado del proyecto: " << endl;
        //Se almacena en la variables creada con getline para prevenir errores del usuario
        getline(cin,estado);
        
        //Se guarda la informacion en la estructura para luego guardarla en el mapa
        proyectos[nombreProyecto].first = {nombrePropietario, estado};
        //Se guarda la informacion en el vector tarea
        proyectos[nombreProyecto].second = vector<Tarea>();

        //Se muestran mensajes de exito al usuario
        cout << "Proyecto " << nombreProyecto << " ha sido creado exitosamente!" << endl; 
        cout << "Propietario: " << nombrePropietario << endl;
        cout << "Estado: " << estado << endl;
    }
    

    void agregarTareaAProyecto() {
       //Inicializamos las variables que necesitamos
        string nombreProyecto;
        string nombreTarea;
        string explicacion;

        //Se pide al usuario ingresar el nombre del proyecto
        cout << "Ingrese el nombre del proyecto: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable con getline para prevenir errores
        getline(cin,nombreProyecto);

        //Creamos un iterador que busca el nombre dle proyecto en el mapa
        auto it = proyectos.find(nombreProyecto);
        //Si el iterador llega al final, se muestra mensaje de que el proyecto no fue encontrado 
        if (it == proyectos.end()) {

            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        //Si el proyecto se encuenta, se ingresan las tareas para ese proyecto
        cout << "Ingrese las tareas para el proyecto " << nombreProyecto << "(Ingrese 'fin' para salir)" << endl;
        while (true) {

            cout << "Ingrese el nombre de la tarea: " << endl;
            //Se almacena el nombre de la tarea
            getline(cin,nombreTarea);

            //Si el usuario decide salirse del ciclo, escribe fin y el sistema sigue 
            if (nombreTarea == "fin")
                break;
            
            //Se ingresan las explicaciones de las tareas
            cout << "Ingrese la explicacion de la tarea: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la informacion
            getline(cin, explicacion);
            //Se crea un objeto de la clase tarea que almacena la informacion que el usuario acaba de ingresar
            Tarea tarea(nombreTarea, explicacion);
            //Se almacenan en el vector 
            it -> second.second.push_back(tarea);
            //Se muestra mensaje de exito
            cout << "Tarea agregada al proyecto: " << nombreProyecto << endl;
        }
    }

    void buscarProyectoXNombre() {
         //Se verifica que el mapa no este vacio
        if (proyectos.empty()){
            cout << "No hay proyectos disponibles" << endl;
            return;
        }
        
        //Inicializamos la variable
        string nombreBusqueda;

        //Se le pide al usuario ingresar el nombre del proyecto que va a buscar
        cout << "Ingrese el nombre del proyecto del que desea ver las tareas: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable
        getline(cin,nombreBusqueda);

        //Creamos un iterador que busca en el mapa el nombre que busca el usuario
        auto it = proyectos.find(nombreBusqueda);
        //Si se llega al find del mapa y no se encontro, se muestra mensaje de error
        if (it == proyectos.end()){
            cout << "Proyecto " << nombreBusqueda << " no encontrado" << endl;
            return;
        }

        //Si se encuentra el proyecto, se imprimen las tareas que tiene asociadas
        cout << "Tareas del proyecto " << nombreBusqueda << ":" << endl;
        for (Tarea& tarea : it -> second.second){
            //Traemos los metodos accesores de la clase tarea que creamos previamente y que almacena la informacion necesaria 
            cout << "Nombre: " << tarea.getNombreT() << ", Explicacion: " << tarea.getExplicacion() << endl;
        }
    }
    };
    void mostrarResponsables(){

    cout << "Lista de responsables ordenada por nombre: " << endl;
    for (const auto& par: responsables) {
        cout << par.first << ": " << par.second << endl;
    }

}

//Opcion B si se usa un vector 
//Se debe tener una clase con dos atributos privados y los metodos accesores

//Se crea una funcion de comparacion para ordenar los responsables por nombre
bool compararXNombre (const Responsable& a, const Responsable& b){

    return a.getNombre() < b.getNombre();
}

//Ordenamos el vector por nombre de responsables
sort(responsables.begin(), responsables.end(), compararXNombre);

//Mostramos la lista de responsables ordenada por nombre 
void mostrarResponsables(){

    cout << "Lista de responsables ordenada por nombre: " << endl;
    for (const auto& responsable : responsables){
        cout << responsable.getNombre() << ": " << responsable.getResponsabilidad() << endl;

    }
}

    void agregarNotaAProyecto() {
        string nombreProyecto, titulo, descripcion;

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        cout << "Ingrese el título de la nota: " << endl;
        getline(cin, titulo);

        if (titulo.empty()) {
            cout << "El título de la nota no puede estar vacío." << endl;
            return;
        }

        cout << "Ingrese la descripción de la nota (opcional): " << endl;
        getline(cin, descripcion);

        // Obtiene el nombre del usuario actual (implementa según tu lógica)
        string autor = "usuario_actual"; // Reemplaza con el nombre real

        Nota nuevaNota = {titulo, autor, descripcion};
        notasProyecto[nombreProyecto].push_back(nuevaNota);
        cout << "Nota agregada al proyecto: " << nombreProyecto << endl;
    }

    string nombreProyecto, titulo;
        int indiceNota = -1; // Inicializamos a -1 para indicar que no se ha encontrado

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        vector<Nota>& notas = notasProyecto[nombreProyecto];

        if (notas.empty()) {
            cout << "El proyecto no tiene notas." << endl;
            return;
        }

        cout << "Ingrese el título de la nota a editar: " << endl;
        getline(cin, titulo);

        // Buscamos la nota por título
        for (int i = 0; i < notas.size(); i++) {
            if (notas[i].titulo == titulo) {
                indiceNota = i;
                break;
            }
        }

        if (indiceNota != -1) { // Si encontramos la nota
            cout << "Ingrese el nuevo título de la nota: " << endl;
            getline(cin, notas[indiceNota].titulo);

            cout << "Ingrese la nueva descripción de la nota: " << endl;
            getline(cin, notas[indiceNota].descripcion);

            cout << "Nota editada exitosamente." << endl;
        } else {
            cout << "No se encontró una nota con ese título." << endl;
        }
    }

    // Función para eliminar una nota de un proyecto
    void eliminarNotaDeProyecto() {
        string nombreProyecto, titulo;

        cout << "Ingrese el nombre del proyecto: " << endl;
        cin.ignore();
        getline(cin, nombreProyecto);

        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            cout << "Proyecto " << nombreProyecto << " no existe" << endl;
            return;
        }

        vector<Nota>& notas = notasProyecto[nombreProyecto];

        if (notas.empty()) {
            cout << "El proyecto no tiene notas." << endl;
            return;
        }

        cout << "Ingrese el título de la nota a eliminar: " << endl;
        getline(cin, titulo);

        // Usamos un iterador para encontrar y eliminar la nota
        auto it = find_if(notas.begin(), notas.end(), [&titulo](const Nota& nota) {
            return nota.titulo == titulo;
        });

        if (it != notas.end()) {
            notas.erase(it);
            cout << "Nota eliminada exitosamente." << endl;
        } else {
            cout << "No se encontró una nota con ese título." << endl;
        }
    }

