#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

//Creamos una estructura que almacena los datos que necesitamos para realizar el registro 
struct Registro{

    string usuario;
    string clave;
};

//Inicializamos el mapa con clave tipo string y valor sera la estructura que ya creamos
map <string, Registro> BaseDatos;

//Creamos una funcion que nos permite registrar un usuario al sistema
void registrarUsuario(){

    //Instanciamos la estructura creada, creando un objeto
    Registro usuarioNuevo;

    //Se muestra mensaje por consola que pide el usuario 
    cout << "Ingrese un nombre de usuario: " << endl;
    //Se almacena los datos ingresados en la estructura creada
    cin >> usuarioNuevo.usuario;

    //Se crea un condicional que siempre va a verificar que la clave sea de 8 digitos
    do {
        //Se muestra mensaje por consola teniendo en cuenta las especificaciones de la clave
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y numeros): " << endl;
        //Se almacena la informacion en la estructura
        cin >> usuarioNuevo.clave;
        //Verificamos la longitud de la clave 
        if (usuarioNuevo.clave.length() != 8){
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
    } while (usuarioNuevo.clave.length() != 8);

    //Guardamos la informacion en el mapa 
    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    //Se muestra un mensaje de satisfaccion 
    cout << "Usuario registrado exitosamente!" << endl;
}

//Se crea una funcion para el inisio de sesion
void inicioSesion(){

    //Se inicializan las variables necesarias
    string usuario1;
    string clave1;

    //Se le pide al usuario ingresar el nombre de usuario
    cout << "Ingrese su nombre de usuario: " << endl;
    //Se almacena en la variable creada
    cin >> usuario1;

    //Se le pide al usuario ingresar la clave
    cout << "Ingrese su clave: " << endl;
    //Se almacena la informacion en la variable creada
    cin >> clave1;

    //Creamos un condicional que verifica si el usuario esta almacenado en el mapa
    if (BaseDatos.find(usuario1) != BaseDatos.end()){
        //Se verifica que la clave asignada en el registro sea igual a la ingresada en el inicio de sesion
        if (BaseDatos[usuario1].clave == clave1){
            //Se muestran mensajes de exito al iniciar sesion
            cout << "Inicio de Sesion exitoso!" << endl;
            cout << "Bienvenido(a), " << usuario1 << endl;
        } else {
            //Si la clave no coincide muestra mensaje de error 
            cout << "Datos incorrectos. Por favor intente nuevamente" << endl;

        }
    } else {
        //Si el usuario no fue encontrado en el mapa, muestra mensaje para que el usuario se registre primero
        cout << "El usuario no fue encontrado en la base de datos. Registrese primero y luego intente de nuevo" << endl;
    }
}

//Se crea la clase tarea
class Tarea {

    //Se inicializan los atributos privados
    private:

    string nombreT;
    string explicacion;

    public:

    //Se crea el constructor de la clase, con datos constantes ya que indicamos que no los modificaremos 
    Tarea(const string& _nombreT, const string& _explicacion){

        //Se igualan las varibales constantes con los atributos
        nombreT = _nombreT;
        explicacion = _explicacion;
    }

    //Se crea el set de la primera variable
    void setNombreT(const string _nombreT){

        nombreT = _nombreT;
    }

    //Se crea el get de la primera variable
    string getNombreT() const {

        return nombreT;
    }

    //Se crea el set de la segunda variable
    void setExplicacion(const string _explicacion){

        explicacion = _explicacion;
    }

    //Se crea el get de la segunda variable
    string getExplicacion() const {

        return explicacion;
    }
};

//Creamos una estructura que almacena los datos que necesitamos 
struct DetallesProyecto {

    string nombrePropietario;
    string estado;

};

//Creamos la clase proyecto
class Proyecto {

    //Inicializamos los atributos privados
    private:

    //Se crea un mapa de clave string y de valor un pair que contiene la estructura anterior y el vector tarea
    map <string, pair<DetallesProyecto, vector<Tarea>>> proyectos;

    public:

    //Creamos el constructor vacio
    Proyecto () {

    }

    //Se crea la funcion para crear un proyecto
    void crearProyecto(){

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

    //Creamos la funcion que permite agregar una tarea a un proyecto
    void agregarTareaAProyecto(){

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

    //Se crea una funcion para buscar proyectos por nombre
    void buscarProyectoXNombre(){

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

//Opcion A si se usa un mapa para almacenar responsables con responsabilidad
//Se debe tener una clase con dos atributos privados y los metodos accesores

//Mostramos la lista de responsables ordenada por nombre
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


