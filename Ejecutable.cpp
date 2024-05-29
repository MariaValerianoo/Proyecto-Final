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

//Se crea una estructura para almacenar los datos de registro
struct Registro
{
    string usuario;
    string clave;
};

//Se crea un mapa para almacenar datos de registro
map<string, Registro> BaseDatos;

//Se crea la función para registrar un nuevo usuario
void registrarUsuario(){
    //Se crea un objeto de la estructura registro
    Registro usuarioNuevo;

    //Se le pide al usuario el dato para crear el usuario nuevo 
    cout << "Ingrese un nombre de usuario: " << endl;
    //Se ingresa la informacion recibida a la estructura mediante el objeto
    cin >> usuarioNuevo.usuario;
    
    //Se crea un ciclo, para poder siempre verificar que la clave contenga 8 digitos 
    do {
        //Se le pide al usuario ingresar la clave que tiene ciertas especifiaciones 
        cout << "Ingrese una clave (debe tener 8 caracteres entre letras y números): " << endl;
        //Se ingresa la informacion recibida a la estructura mediante el objeto 
        cin >> usuarioNuevo.clave;
        //Se crea una condicion para que la clave siempre cumpla las condiciones 
        if (usuarioNuevo.clave.length() != 8) {
            //Se muestra mensaje al usuario en caso dado de que no cumpla los requisitos
            cout << "La clave debe tener 8 caracteres. Intente nuevamente" << endl;
        }
      //Es la condicion que tiene en cuenta el ciclo para repetirse en caso dado de que no se cumpla  
    } while (usuarioNuevo.clave.length() != 8);

    //Se llama al mapa, y se le asignan los valores registrados por el usuario con el objeto de la estructura 
    BaseDatos[usuarioNuevo.usuario] = usuarioNuevo;
    //Se muestra un mensaje de exito al usuario
    cout << "Usuario registrado exitosamente!" << endl;
}

//Se crea la función para iniciar sesión
bool inicioSesion() {
    string usuario1;
    string clave1;

    //Se le pide al usuario ingresar el usuario que creo anteriormente 
    cout << "Ingrese su nombre de usuario: " << endl;
    //Se guarda la informacion ingresada en la variable creada
    cin >> usuario1;

    //Se le pide al usuario ingresar su clave anteriormente creada
    cout << "Ingrese su clave: " << endl;
    //Se guarda la informacion ingresada en la variable creada
    cin >> clave1;

    //Se crea una condicion que verifica que el usuario si este registrado en la base de datos
    if (BaseDatos.find(usuario1) != BaseDatos.end()) {
        //Se crea una condicion que verifica que la clave que se ingreso al iniciar sesion sea igual a la que se ingreso en el registro
        if (BaseDatos[usuario1].clave == clave1) {
            //Se le muestra un mensaje de exito al usuario
            cout << "Inicio de Sesion exitoso!" << endl;
            //Se le da la bienvenida al usuario 
            cout << "Bienvenido(a), " << usuario1 << endl;
            //El booleano retorna un valor verdadero para dar ingreso al sistema
            return true;
        } else {
            //En caso dado de que la verificacion de la clave sea incorrecta, se le muestra un mensaje al usuario
            cout << "Datos incorrectos. Por favor intente nuevamente" << endl;
            //El booleano retorna un valor falso para denegar el ingreso al sistema
            return false;
        }
    } else {
        //En caso dado de que la verificacion de si el usuario existe en la base de datos sea de resultado negativo, se muestra un mensaje al usuario
        cout << "El usuario no fue encontrado en la base de datos. Regístrese primero y luego intente de nuevo" << endl;
        //El booleano retorna un valor falso para denegar el ingreso al sistema
        return false;
    }
}

//Se crea una estructura para almacenar datos de una tarea
struct Tarea { 
    string nombre;
    string estado;
    string prioridad;
    string responsable;
    string fechaLimite;
    string resumen;
    string notas;
    map<string, int> reacciones;
    bool recurrente;
};

//Se crea una estructura para almacenar detalles del proyecto
struct DetallesProyecto {
    string fechaCreacion;
    string descripcion;
    string notas;
    map<string, int> reacciones;
};

//Se crea una clase para gestionar proyectos
class Proyecto { 
//Se crean los atributos privados
private:
    //Se crea un mapa que almacena tanto la estructura que contiene los detalles del proyecto como un vector que alamacena la estructura que contiene los datos de una tarea
    map<string, pair<DetallesProyecto, vector<Tarea>>> proyectos;
//Se crean los atributos publicos
public:
    //Se crea una función para exportar datos
    void exportarDatos(string nombreArchivo, string formato = "csv"){
        //Se abe un archivo de salida con el nombre que proporciono el usuario
        ofstream archivoSalida(nombreArchivo);

        //Se verifica si se puedo abriri el archivo correctamente
        if (!archivoSalida.is_open()) {
            //En caso dado de que no, se le muestra un mensaje al usuario
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            //Se establece un return que en caso dado de que si se pueda abrir bien el archivo se salga de la condicion
            return;
        }

        //Se crea un condicional que verifica el formato especificado para exportar los datos
        if (formato == "csv"){
            //Se crea un ciclo y con un iteraor se recorre el mapa de proyectos
            for (auto &proyecto : proyectos) {
                //Se especifica que el archivo de salida, sera el nombre del proyecto, la fecha de creacion y la descripcion
                archivoSalida << proyecto.first << "," << proyecto.second.first.fechaCreacion << "," << proyecto.second.first.descripcion << endl;
                //Se crea un ciclo y con un iterador se recorre el mapa y dentro el vector que almacena la informacion de las tareas
                for (auto &tarea : proyecto.second.second) {
                    //Se especifica que informacion va a salir en el achivo, que vendrian siendo algunos detalles de la tarea
                    archivoSalida << tarea.nombre << "," << tarea.estado << "," << tarea.prioridad << "," << tarea.responsable << "," << tarea.fechaLimite << "," << tarea.resumen << endl;
                }
            }
        }
        else if (formato == "json") {
            //Se exporta el archivo en tipo json (implementacion simplificada)
            archivoSalida << "{" << endl;
            //Se crea un ciclo y con un iterador recorre el mapa de los proyectos
            for (auto &proyecto : proyectos) {
                //Se especifica lo que va a salir en el archivo, empezando por el nombre del proyecto
                archivoSalida << "  \"" << proyecto.first << "\": {" << endl;
                //Se especifica lo que va a salir en el archivo, como lo es la fecha de creacion
                archivoSalida << "    \"fechaCreacion\": \"" << proyecto.second.first.fechaCreacion << "\"," << endl;
                //Se especifica lo que va a salir en el archivo, como lo es la decripcion
                archivoSalida << "    \"descripcion\": \"" << proyecto.second.first.descripcion << "\"," << endl;
                //Se especifica lo que va a salir en el archivo, como lo es las tareas del proyecto
                archivoSalida << "    \"tareas\": [" << endl;
                //Se crea un ciclo y con un iterador se busca la informacion que almacena el vector tareas dentro del mapa
                for (auto &tarea : proyecto.second.second) {
                    //Se especifica la informacion que va a salir, en este caso son los datelles de la tarea
                    archivoSalida << "      {\"nombre\": \"" << tarea.nombre << "\", \"estado\": \"" << tarea.estado << "\", \"prioridad\": \"" << tarea.prioridad << "\", \"responsable\": \"" << tarea.responsable << "\", \"fechaLimite\": \"" << tarea.fechaLimite << "\", \"resumen\": \"" << tarea.resumen << "\"}," << endl;
                }
                //Se cierran los archivos
                archivoSalida << "    ]" << endl;
                archivoSalida << "  }," << endl;
            }
            archivoSalida << "}" << endl;
        }
        else {
            //Si el usuario no elige uno de los dos formatos de exportacion posible, el sistema muestra mensaje de error
            cout << "Formato no valido. Use 'csv' o 'json'." << endl;
        }

        //Se cierra el archivo 
        archivoSalida.close();
        //Sale un mensaje de exito confirmando que la exportacion que se acaba de realizar salio con exito
        cout << "Datos exportados exitosamente en formato " << formato << " al archivo " << nombreArchivo << endl;
    }

    //Se crea la función para importar datos
    void importarDatos(string nombreArchivo){
        //Se abre un archivo de entrada con el nombre que el usuario eligio 
        ifstream archivoEntrada(nombreArchivo);

        //Se verifica si se pudo abrir correctamente el archivo
        if (!archivoEntrada.is_open()) {
            //En caso de que no, se muestra un mensaje al usuario 
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            return;
        }

        
        //Se determina el formato del archivo basado en su extension
        string formato;
        //Se crea un condicion para verificar si es un archivo con extension csv
        if (nombreArchivo.find(".csv") != string::npos){
            //Se le asigna un nuevo valor a la variable creada
            formato = "csv";
          //Se verifica si el archivo no es de la extension de ese tipo y por lo contrario si es de este
        } else if (nombreArchivo.find(".json") != string::npos) {
            //Se le asigna un nuevo valor a la variable creada 
            formato = "json";
        } else {
            //En caso dado de que el archivo que se vaya a importar tengo otro tipo de extension, se muestra este mensaje al usuario
            cout << "Formato de archivo no reconocido. Use .csv o .json." << endl;
            //Se cierra el archivo 
            archivoEntrada.close();
            return;
        }
        
        //Se cargan los datos según el formato de importacon
        string linea;
        //Se crea un condicional que verifica si primero es un archivo con extension csv
        if (formato == "csv"){
            //Se importa desde el tipo de extension, en este caso csv
            while (getline(archivoEntrada, linea)) {
                stringstream ss(linea);
                string nombreProyecto, fechaCreacion, descripcionProyecto;
                //Se ingresan los datos importados en el sistema con un getline para incluir espacios y evitar saltos de linea
                getline(ss, nombreProyecto, ',');
                getline(ss, fechaCreacion, ',');
                getline(ss, descripcionProyecto, ',');

                //Se llama a la estucturam mediante un objeto y se le asignan los detalles del proyecto
                DetallesProyecto detalles = {fechaCreacion, descripcionProyecto};
                //Se llama al mapa mediante la clave y se le asignan los datos acerca de los datalles y los detalles de la tarea
                proyectos[nombreProyecto] = make_pair(detalles, vector<Tarea>());

                //Se crea un ciclo para que se verifique primero si las lineas ya estan vacias y la informacon ya esta cargada
                while (getline(archivoEntrada, linea)){
                    //Se crea un condicional para verificar si la linea a ingresar esta vacia
                    if (linea.empty())
                        //Se sale del ciclo 
                        break;
                    stringstream ssTarea(linea);
                    //Se declaran las variables a utilizar
                    string nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea;
                    //Se ingresa la informacion que contienen los detalles de la tarea separadas por , y en lineas diferentes
                    getline(ssTarea, nombreTarea, ',');
                    getline(ssTarea, estadoTarea, ',');
                    getline(ssTarea, prioridadTarea, ',');
                    getline(ssTarea, responsableTarea, ',');
                    getline(ssTarea, fechaLimiteTarea, ',');
                    getline(ssTarea, resumenTarea, ',');

                    //Se llama al mapa mediante la clave, y se agregan los detalles al vector tarea
                    proyectos[nombreProyecto].second.push_back({nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea});
                }
            }
        }

        //Se cierra el archivo
        archivoEntrada.close();
        //Se muestra un mensaje de satistaccion
        cout << "Datos importados exitosamente desde el archivo " << nombreArchivo << endl;
    }

    //Se crea una funcion que permite crear proyectos
    void crearProyecto() {
        string nombreProyecto;
        string nombreUsuario;
        string descripcionProyecto;

        //Se le pide al usuario ingresar el nombre del proyecto
        cout << "Ingrese el nombre del proyecto: " << endl;
        //Se limpia el buffer 
        cin.ignore();
        //Se guarda la informacion en la variable creada
        getline(cin,nombreProyecto);

        //Se le pide al usuario ingresar el nombre del creador del proyecto
        cout << "Ingrese el nombre del usuario que creo el proyecto: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se guarda la informacion en la variable creada
        getline(cin,nombreUsuario);

        //Se le pide al usuario ingresar una breve descripcion del proyecto
        cout << "Ingrese una breve descripcion del proyecto: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se guarda la informacion en la variable creada
        getline(cin, descripcionProyecto);

        //Se instancia la clase y se le asigna la fecha actual y la descripcion del proyecto ingresada por el usuario 
        DetallesProyecto detalles = {fechaActual(), descripcionProyecto};
        //Se llama al mapa creado, se utiliza la clave que viene siendo el nombre del proyecto y se le asigna los valores 
        proyectos[nombreProyecto] = make_pair(detalles, vector<Tarea>());

        //Se muestra un mensaje de exito al usuario 
        cout << "Proyecto creado exitosamente!" << endl;
    }

    //Se crea una funcion sin retorno que permite mostrar los proyectos
    void mostrarProyectos() {
        //Se crea una condicion que verifica si el mapa esta vacio o no
        if (proyectos.empty()) {
            //Si el mapa esta vacio muestra mensaje al usuario de que no hay proyectos creados 
            cout << "No hay proyectos creados." << endl;
            //Se crea un return que hace que se vuelva a verificar si hay o no proyectos y si hay siga se salga de la condicion
            return;
        }
        
        //Se imprimen los proyectos en una lista
        cout << "Lista de proyectos:" << endl;
        //Se crea un ciclo con un iterador que recorre proyectos y los imprime
        for (auto& proyecto : proyectos) {
            cout << " - " << proyecto.first << endl;
        }
    }

    //Se crea una funcion que le permite al usuario seleccionar el proyecto en el que quiere trabajar 
    void seleccionarProyecto(string nombreProyecto) {
        //Se crea una condicion que busca el nombre del proyecto seleccionado en el mapa que contiene los proyectos
        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            //Si la verificacion llega a dar resultados negativos, se muestra un mensaje en el que se le informa al usuario de esto 
            cout << "El proyecto " << nombreProyecto << " no existe." << endl;
            //Se crea un return donde si llega a encontrar el proyecto se salga de la condicion
            return;
        }
        
        //Se muestra un mensaje de que el proyecto se ha seleccionada
        cout << "Proyecto seleccionado: " << nombreProyecto << endl;

        //Se llama a la funcion menú del proyecto seleccionado
        menuProyecto(nombreProyecto);
    }

    //Se crea una funcion sin retorno que le permite al usuario eliminar un proyecto 
    void eliminarProyecto(string nombreProyecto) {
        //Se crea una condicion que verifica si el proyecto a eliminar existe y esta previamente creado
        if (proyectos.find(nombreProyecto) == proyectos.end()) {
            //Si el proyecto llega a no estar creado, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe." << endl;
            //Se crea un return en caso de que si el proyecto es encontrado se salga de la condicion y siga
            return;
        }
        
        //Se llama al mapa y se elimina el proyecto seleccionado
        proyectos.erase(nombreProyecto);
        //Se muestra un mensaje al usuario de que el proyecto se ha eliminado exitosamente
        cout << "Proyecto " << nombreProyecto << " eliminado exitosamente." << endl;
    }

    //Se crea una funcion sin retorno que le permite al usuario agregar tareas a los proyectos 
    void agregarTarea(string nombreProyecto){
        string nombreTarea;
        string estadoTarea;
        string prioridadTarea;
        string responsableTarea;
        string fechaLimiteTarea;
        string resumenTarea;

        //Se le pide al usuario ingresar el nombre de la tarea
        cout << "Ingrese el nombre de la tarea: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin,nombreTarea);

        //Se le pide al usuario ingresar el estado de la tarea
        cout << "Ingrese el estado de la tarea (pendiente, en progreso, completada): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin,estadoTarea);

        //Se le pide al usuario que ingrese que tipo de prioridad tiene esa tarea
        cout << "Ingrese la prioridad de la tarea (alta, media, baja): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin,prioridadTarea);

       //Se le pide al usuario que ingrese quien es el responsable de la tarea
        cout << "Ingrese el responsable de la tarea: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin,responsableTarea);
        
        //Se le pide al usuario ingresar la fecha limie que tiene esa tarea para ser realizada
        cout << "Ingrese la fecha límite de la tarea (formato dd/mm/aaaa): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin,fechaLimiteTarea);

        //Se le pide al usuario que ingrese un breve resumen de la tarea
        cout << "Ingrese un breve resumen de la tarea: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin, resumenTarea);

        //Se llama al mapa mediante la clave que es el nombre del proyecto y se agregan en la segunda posicionq que seria el vector de tareas, los datos ingresados
        proyectos[nombreProyecto].second.push_back({nombreTarea, estadoTarea, prioridadTarea, responsableTarea, fechaLimiteTarea, resumenTarea});
        //Se ingresan los colores al sistem para diferenciar el estado de la tarea
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (estadoTarea == "pendiente") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Rojo
        } else if (estadoTarea == "progreso") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); // Amarillo
        } else if (estadoTarea == "completada") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Verde
        }
        //Se le muestra al usuario un mensaje de exito
        cout << "Tarea agregada exitosamente al proyecto " << nombreProyecto << " con estado: " << estadoTarea << endl;
        SetConsoleTextAttribute(hConsole, 7); //Restablece el color
    }

    //Se crea la funcion sin retorno para mostrar las tareas
    void mostrarTareas(string nombreProyecto){
        //Se crea una condicion que verifica si hay tareas para ese proyecto en especifico
        if (proyectos[nombreProyecto].second.empty()) {
            //Si no hay tareas, se muestra un mensaje al usuario 
            cout << "No hay tareas en el proyecto " << nombreProyecto << endl;
            //Se crea un return que en caso de que sea verdadero se sale de la condicion 
            return;
        }

        //Se imprimen las tareas que estan relacionadas al proyecto
        cout << "Lista de tareas del proyecto " << nombreProyecto << ":" << endl;
        //Se crea un ciclo con un iterador que basado en el nombre del proyecto busca las tareas que hay asociadas
        for (auto& tarea : proyectos[nombreProyecto].second) {
            cout << " - " << tarea.nombre << endl;
        }
    }

    //Se crea una funcion sin retorno que le permite al usuario seleccionar una tarea
    void seleccionarTarea(string nombreProyecto, string nombreTarea){

        //Se crea una condicion que verifica si el proyecto existe 
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << "no existe" << endl;
            //Se crea un return que en caso de que sea verdadero se sale de la condicion 
            return;
        }
        
        //Se crea una referencia al vector de tareas del proyecto especificado p
        auto& proyecto = proyectos[nombreProyecto];
        //Se busca la tarea  dentro del vector de tareas
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea& tarea){
            //Se compara el nombre de la tarea con el nombre de la tarea que el usuario esta buscando
            return tarea.nombre == nombreTarea;
        });

        //Se crea una condicion para confirmar que la tarea no se encuentra en el vector de tareas
        if (it == proyecto.second.end()) {
            //Se le muestra un mensaje al usuario 
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        //Se muestra un mensaje de cual ha sido la tarea selecciona
        cout << "Tarea seleccionada: " << nombreTarea << endl;

        //Se instancia la funcion del menu de opciones de la tarea seleccionada
        menuTarea(nombreProyecto, nombreTarea);
    }

    //Se crea una funcion sin retorno que permite editar una tarea
    void editarTarea(string nombreProyecto, string nombreTarea){
        //Se obtiene una referencia al proyecto dentro del mapa usando el nombre del proyecto
        auto &proyecto = proyectos[nombreProyecto];
        //Se busca la tarea dentro de la lista de tareas del proyecto
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea &tarea){ 
            //Se compara el nombre de la tarea actual con el nombre de la tarea registrado previamente
            return tarea.nombre == nombreTarea; 
        });

        //Se verifica si la tarea se encuentra en el proyecto
        if (it == proyecto.second.end()){
            //Se muestra un mensaje en caso dado de que no exista la tarea
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            //Se sale de la funcion
            return;
        }

        //Se imprime la informacion que se tiene de la tarea
        cout << "Informacion actual de la tarea:" << endl;
        //Se muestra el nombre registrado y se llama con un puntero para que acceda a la informacion 
        cout << " - Nombre: " << it->nombre << endl;
        //Se muestra el estado registrado y se llama con un puntero para que acceda a la informacion 
        cout << " - Estado: " << it->estado << endl;
        //Se muestra la prioridad registrada y se llama con un puntero para que acceda a la informacion 
        cout << " - Prioridad: " << it->prioridad << endl;
        //Se muestra el nombre del responsable registrado y se llama con un puntero para que acceda a la informacion 
        cout << " - Responsable: " << it->responsable << endl;
        //Se muestra la fecha limite registrada y se llama con un puntero para que acceda a la informacion 
        cout << " - Fecha Limite: " << it->fechaLimite << endl;
        ////Se muestra el resumen registrado y se llama con un puntero para que acceda a la informacion 
        cout << " - Resumen: " << it->resumen << endl;

        //Se declaran las variables necesarias
        string nuevoEstado, nuevaPrioridad, nuevoResponsable, nuevaFechaLimite, nuevoResumen;

        //Se le pregunta al usuario si desea modificar el estado de la tarea
        cout << "¿Desea modificar el estado? (si/no): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin, nuevoEstado);
        //Se crea una condicion para verificar la respuesta del usuario
        if (nuevoEstado == "si"){
            //En caso de que sea si, le permite ingresar un nuevo estado
            cout << "Ingrese el nuevo estado: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la informacion en la variable
            getline(cin, nuevoEstado);
        } else {
            //Si la respuesta del usuario es no, se mantiene la informacion que ya se habia ingresado
            nuevoEstado = it->estado;
        }

        //Se le pregunta al usuario si desea modificar la prioridad
        cout << "¿Desea modificar la prioridad? (si/no): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin, nuevaPrioridad);
        //Si la respuesta del usuario fue positiva
        if (nuevaPrioridad == "si") {
            //Se le pide al usuario ingresar la nueva prioridad
            cout << "Ingrese la nueva prioridad: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la nueva informacion
            getline(cin, nuevaPrioridad);
        } else {
            //En caso dado de que la respuesta del usuario sea negativa, se mantiene la informacion que ya se tenia
            nuevaPrioridad = it->prioridad;
        }

        //Se le pregunta al usuario si desea modificar el responsable de la tarea
        cout << "¿Desea modificar el responsable? (si/no): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable creada
        getline(cin, nuevoResponsable);
        //Se crea una condicion para verificar la respuesta del usuario
        if (nuevoResponsable == "si"){
            //En caso dado de que la respuesta sea si, se le pide al usuario ingresar el nuevo responsabble
            cout << "Ingrese el nuevo responsable: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la informacion en la variable creada
            getline(cin, nuevoResponsable);
        } else {
            //En caso dado de que la respuesta sea negativa, se mantiene la informacion que se tenia
            nuevoResponsable = it->responsable;
        }

        //Se le preggunta al usuario si desea cambiar la fecha limite de la tarea
        cout << "¿Desea modificar la fecha límite? (si/no): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena en la nueva variable creada
        getline(cin, nuevaFechaLimite);
        //Se crea una condicion que verifica la respuesta del usuario
        if (nuevaFechaLimite == "si"){
            //En caso dado de que la respuesta fuera positiva, se le pregunta al usuario por la nueva fecha
            cout << "Ingrese la nueva fecha límite: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la nueva informacion en la variable creada
            getline(cin, nuevaFechaLimite);
        } else {
            //Si la respuesta del usuario fue negativa, se mantiene la informacion que se tenia previamente
            nuevaFechaLimite = it->fechaLimite;
        }

        //Se le pregunta al usuario si desea modificar el resumen
        cout << "¿Desea modificar el resumen? (si/no): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la respuesta en la variable que fue creada
        getline(cin, nuevoResumen);
        //Se crea una condicion que verifica la respuesta del usuario
        if (nuevoResumen == "si"){
            //En caso dado de que la respuesta sea positiva, se le pide al usuario ingresar el nuevo resumen
            cout << "Ingrese el nuevo resumen: " << endl;
            //Se limpia el buffer
            cin.ignore();
            //Se almacena la informacion en la variable que ya creamos
            getline(cin, nuevoResumen);
        } else {
            //En caso dado de que la respuesta sea negativa, se mantiene la respuesta anterior
            nuevoResumen = it->resumen;
        }

        //Se apunta a la variable y se le asigna el valor nuevo en caso de que se haya cambiado la informacion
        //Si la informacion no cambio, se mantiene el valor que se tiene en el sistema
        it->estado = nuevoEstado;
        it->prioridad = nuevaPrioridad;
        it->responsable = nuevoResponsable;
        it->fechaLimite = nuevaFechaLimite;
        it->resumen = nuevoResumen;

        //Se muestra mensaje de éxito con el nuevo estado de la tarea en color
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (nuevoEstado == "pendiente") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Rojo
        } else if (nuevoEstado == "progreso") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); // Amarillo
        } else if (nuevoEstado == "completado") {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Verde
        }
        //Se muestra un mensaje de exito con el cambio de estado
        cout << "Tarea modificada exitosamente! Nuevo estado: " << nuevoEstado << endl;
        SetConsoleTextAttribute(hConsole, 7); //Restablece el color
    }

    //Se crea una funcion sin retorno que nos permite eliminar una tarea
    void eliminarTarea(string nombreProyecto, string nombreTarea){
        //Se obtiene una referencia al proyecto dentro del mapa usando el nombre del proyecto
        auto &proyecto = proyectos[nombreProyecto];
        //Se busca la tarea dentro de la lista de tareas de proyecto
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea &tarea){
            //Se compara el nombre de la tarea actual con el que ya se habia registrado previamente
            return tarea.nombre == nombreTarea; 
        });

        //Se crea una condicion para verificar si la tarea definitivamente no esta en el proyecto 
        if (it == proyecto.second.end()){
            //Se le muestra un mensaje al usuario indicando que la tarea no existe
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            //Se sale de la funcion 
            return;
        }

        //Se usa la opcion de eliminar un elemento de un mapa y se ubica la posicion
        proyecto.second.erase(it);
        //Se le muestra un mensaje al usuario de que la tarea se elimino con exito 
        cout << "La tarea " << nombreTarea << " se ha eliminado del proyecto " << nombreProyecto << endl;
    }

    //Se crea una funcion que le permite al usuario agregar notas a los proyectos
    void agregarNotaAProyecto(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se inicializa la variable
        string nota;
        //Se le pide al usuario ingresar la nota que quiere agregar al proyecto
        cout << "Ingrese la nota para el proyecto: " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion en la variable que creamos previamente
        getline(cin, nota);

        //Se llama al mapa con la clave que es el nombre del proyecto y se agrega la nota
        proyectos[nombreProyecto].first.notas = nota;
        //Se muestra un mensaje de exito al usuario
        cout << "Nota agregada al proyecto" << nombreProyecto << endl;
    }

    //Se crea una funcion que le permite al usuario agregar notas a las tareas
    void agregarNotaATarea(string nombreProyecto, string nombreTarea){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se obtiene una referencia al vector de tareas del proyecto que fue especificado
        auto &tareas = proyectos[nombreProyecto].second;
        //Se crea un ciclo y se itera sobre cada tarea que existe en el vecto de tareas
        for (auto &tarea : tareas){
            //Se crea una condicion que verifica si el nombre de la tarea actuak coincide con el nombre de la tarea creado previamente
            if (tarea.nombre = nombreTarea){
                //Se declara una variable
                string nota;
                //Se le pide al usuario ingresar la nota que va a agregar a la tarea
                cout << "Ingrese la nota para la tarea " << nombreTarea << ": " << endl;
                //Se limpia el buffer
                cin.ignore():
                //Se almacena la informacion en la variable creada
                getline(cin, nota);

                //Se agrega la nota ingresada a las notas de la tarea
                tarea.notas = nota;
                //Se nuestra un mensaje de exito al usuario
                cout << "Nota agregada a la tarea " << nombreTarea << endl;
                //Se sale del ciclo y de la funcion 
                return;
            }
        }

        //Si no se encuentra la tarea especificada, se muestra un mensaje al usuario 
        cout << "Tarea " << nombreTarea << " no encontrada en el proyecto" << nombreProyecto << endl;
    }

    //Se crea una funcion que permite agregar reacciones a las notas de un proyecto
    void agregarReaccionANotaDeProyecto(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se declara la variable
        string reaccion;
        //Se le pide al usuario que ingrese la reaccion que desea agregar
        cout << "Ingrese la reaccion para la nota del proyectro (ejemplo: Me gusta): " << endl;
        //Se limpia el buffer
        cin.ignore();
        //Se almacena la informacion obtenida en la variable
        getline(cin, reaccion);

        //Se accede a la primera parte del pair del mapa proyectos
        proyectos[nombreProyecto].first
        //Se incrementa el contador de la reaccion especificada en el mapa de reacciones
        proyectos[nombreProyecto].first.reacciones[reaccion]++;
        //Se muestra un mensaje de exito al usuario
        cout << "Reaccion '" << reaccion < "' agregada a la nota del proyecto " << nombreProyecto << endl;
        
    }

    //Se crea una funcion que le permite al usuario agregar reacciones a notas de tareas
    void agregarReaccionANotaDeTarea(string nombreProyecto, string nombreTarea){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se obtiene una referencia al vector de tareas del proyecto que fue especificado
        auto &tareas = proyectos[nombreProyecto].second;
        //Se crea un ciclo y se itera sobre cada tarea que existe en el vecto de tareas
        for (auto &tarea : tareas){
            //Se crea una condicion que verifica si el nombre de la tarea actuak coincide con el nombre de la tarea creado previamente
            if (tarea.nombre = nombreTarea){
                //Se declara una variable
                string reaccion;
                //Se le pide al usuario ingresar la reaccion que quiere agregar
                cout << "Ingrese la reaccion para la nota de la tarea " << nombreTarea << "(ejemplo: Me gusta): " << endl;
                //Se limpia el buffer
                cin.ignore();
                //Se almacena la informacion obtenida en la variable creada
                getline(cin, reaccion);

                //Se accede al contador de las reacciones con la reaccion especificada por el usuario
                tarea.reacciones[reaccion]++;
                //Se muestra un mensaje de exito al usuario
                cout << "Reaccion '" << reaccion << "' agregada a la nota de la tarea " << nombreTarea << endl;
                return;
            }
        }
        //Se muestra un mensaje al usuario en caso de que la tarea no se encuentre creada
        cout << "Tarea " << nombreTarea << " no encontrada en el proyecto " << nombreProyecto << endl;
    }

    void mostrarReaccionesDeNotaDeProyecto(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se accede a las reacciones que estan almacenadas en el mapa
        const auto& reaccioes = proyectos[nombreProyecto].first.reacciones;

        //Se crea una condicion que verifica si reacciones no esta vacio
        if (reacciones.empty()){
            //Si esta vacio, muestra mensaje al usuario
            cout << "No hay reacciones para el proyecto " << nombreProyecto << endl;
            return;
        }

        //Si no estaba vacio, muestra las reacciones a las notas del proyecto
        cout << "Reacciones del proyecto " << nombreProyecto << ":" << endl;
        for (const auto& reaccion : reacciones){
            cout << " - " << reaccion.first << ": " << reaccion.second << endl;
        }
        
    }

    void mostrarReaccionesANotaDeTarea(string nombreProyecto, string nombreTarea){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        auto& tareas = proyectos[nombreProyecto].second;
        auto tareaIt = find_if(tareas.begin(), tareas.end(), [&nombreTarea](const Tarea% tarea){
            return tarea.nombre == nombreTarea;
        });

        if (tareaIt = tareas.end()){
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        const auto& reacciones = tareaIt -> reacciones;

        //Se crea una condicion que verifica si reacciones no esta vacio
        if (reacciones.empty()){
            //Si esta vacio, muestra mensaje al usuario
            cout << "No hay reacciones para la tarea " << nombreTarea << endl;
            return;
        }

        //Si no estaba vacio, muestra las reacciones a las notas de una tarea
        cout << "Reacciones de la tarea " << nombreTarea << ":" << endl;
        for (const auto& reaccion : reacciones) {
            cout << " - " << reaccion.first << ": " << reaccion.second << endl;
        }
    }

//Se establecen los atributos privados
private:
    //Se crea una funcion de tipo string, que genera la fecha actual
    string fechaActual() {
        //Se obtiene el tiempo actual del sistema como objeto de la variable
        time_t tiempo = time(NULL);
        //Se convierte el tiempo a tiempo local 
        tm *tiempoLocal = localtime(&tiempo);
        //Se declara un buffer de caracteres para almacenar la fecha formateada
        char buffer[80];
        //Se almacena en el formato dd/mm/yyyy
        strftime(buffer, 80, "%d/%m/%Y", tiempoLocal);
        //Retorna el contido del buffer como un string
        return string(buffer);
    }

    //Se crea una funcion que contiene el menu de proyectos
    void menuProyecto(string nombreProyecto){
        //Se crea una condicion para que siempre que se ingrese a donde se instancio el menu, muestre el menu
        while (true) {
            //Se hacen las especificacions de cada una de las opciones que tiene el usuario y puede realizar
            cout << " Menu del Proyecto " << nombreProyecto << ":" << endl;
            cout << "1. Seleccionar tarea" << endl; //Puede seleccionar una tarea para abrir el menu de tareas
            cout << "2. Agregar tarea" << endl; // Puede agregar una tarea al proyecto
            cout << "3. Mostrar notas del proyecto" << endl; // Muestra las notas que tiene el proyecto
            cout << "4. Agregar nota al proyecto" << endl; // Agrega la nota al proyecto
            cout << "5. Agregar reaccion a nota del proyeto" << endl; // Agrega una reaccion a una nota 
            cout << "6. Mostrar reacciones a nota del proyecto" << endl; //Muestra las reacciones que tienen las notas del proyecto
            cout << "7. Eliminar proyecto" << endl; // Puede eliminar un proyecto
            cout << "0. Volver al menu principal" << endl; // Opcion para volver al menu principal

            //Se declara la variable
            int opcion;
            //Se le pide al usuario ingresar la opcion deseada
            cout << "Ingrese una opción: ";
            //Se lee y guarda la informacion en la variable
            cin >> opcion;

            //Se crea un switch para crear los posibles casos
            switch (opcion){
            //Si el usuario elige la opcion 1 
            case 1:
                //Se llama a la funcion que muestra las tareas de un proyecto
                mostrarTareas(nombreProyecto);
                //Se le pide al usuario ingresar el nombre de la tarea que quiere seleccionar
                cout << "Ingrese el nombre de la tarea a seleccionar: ";{
                    //Se declara la variable
                    string nombreTarea;
                    //Se limpia el buffer
                    cin.ignore();
                    //Se almacena la informacion obtenida
                    getline(cin, nombreTarea);
                    //Se llama a la funcion que permite seleccionar una tarea
                    seleccionarTarea(nombreProyecto, nombreTarea);
                }
                break;
            //Si el usuario selecciona la opcion 2
            case 2:
                //Se llama la funcion que le permite agregar una tarea al proyecto deseado
                agregarTarea(nombreProyecto);
                break;
            //Si el usuario selecciona la opcion 3
            case 3:
                //Se llama la funcion que le permite mostrar las notas que tiene el proyecto
                mostrarNotasProyecto(nombreProyecto); 
                break;
            //Si el usuario selecciona la opcion 4
            case 4:
                //Se llama la funcion que le permite agregar notas a un proyecto
                agregarNotaAProyecto(nombreProyecto);
                break;
            //Si el usuario selecciona la opcion 5
            case 5:
                //Se llama a la funcion que le permite agregar una reaccion a una nota
                agregarReaccionANotaDeProyecto(nombreProyecto);
                break;
            //Si el usuario selecciona la opcion 6
            case 6:
                //Se llama a la funcion que muestra las reacciones 
                mostrarReaccionesDeNotaDeProyecto(nombreProyecto);
                break;
            //Si el usuario selecciona la opcion 7
            case 7:
                //Se llama la funcion que le permite eliminar un proyecto
                eliminarProyecto(nombreProyecto);
                return; //Salir del menú del proyecto
            //Si el usuario selecciona la opcion 0 
            case o:
                return; //Salir del menú del proyecto
            default:
                cout << "Opción invalida. Intente nuevamente." << endl;
            }
        }
    }

    // Función para mostrar las notas asociadas a un proyecto
    void mostrarNotasProyecto(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //se le muestra al usuario las notas que tiene el proyecto
        cout << "Notas del proyecto " << nombreProyecto << ":" << endl;
        //Se accede al mapa de proyectos mediante la clave que es el nombre del proyecto y se accede a las notas
        cout << proyectos[nombreProyecto].first.notas << endl;
    }

    // Función para mostrar las notas asociadas a todas las tareas de un proyecto
    void mostrarNotasTarea(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Se le muestra al usuario las tareas del proyecto
        cout << "Lista de tareas del proyecto " << nombreProyecto << ":" << endl;
        //Se crea un ciclo que itera sobre el mapa de proyectos y busca las notas
        for (auto &tarea : proyectos[nombreProyecto].second){
            cout << " - " << tarea.nombre << ": " << tarea.notas << endl;
        }
    }

    //Se crea el menu de tarea
    void menuTarea(string nombreProyecto, string nombreTarea){
        while (true)
        {
            cout << "\nMenú de la Tarea " << nombreTarea << " (Proyecto: " << nombreProyecto << "):" << endl;
            cout << "1. Editar tarea" << endl; //Puede editar todos los detalles de una tarea
            cout << "2. Agregar nota a una tarea" << endl; //Agrega notas a una tarea
            cout << "3. Eliminar tarea" << endl; //Elimina una tarea
            cout << "4. Mostrar notas de una tarea" << endl; // Muestra las notas que tiene una tarea
            cout << "5. Agregar reaccion a nota de una tarea" << endl; //Agrega reacciones a una nota de una tarea
            cout << "6. Mostrar reacciones de una nota de tarea" << endl; // Muestra las reacciones que se agregaron
            cout << "0. Volver al menu del proyecto" << endl; //Se devuelve al menu principal

            int opcion;
            cout << "Ingrese una opcion: ";
            cin >> opcion;

            switch (opcion){
            //Si el usuario selecciona la opcion 1
            case 1:
                //Se llama la funcion que permite editar una tarea
                editarTarea(nombreProyecto, nombreTarea);
                break;
            //Si el usuario selecciona la opcion 2
            case 2:
                //Se llama a la funcion que permite agregar notas a tareas
                agregarNotaATarea(nombreProyecto, nombreTarea);
                break;
            //Si el usuario selecciona la opcion 3
            case 3:
                //Se llama a la funcion que permite eliminar una tarea
                eliminarTarea(nombreProyecto, nombreTarea);
                return;
            //Si el usuario selecciona la opcion 4
            case 4:
                //Se llama a la funcion que permite mostrar las notas que tiene una tarea
                mostrarNotasTarea(nombreProyecto); 
                break;
            //Si el usuario seleccion la opcion 5
            case 5:
                //Se llama la funcion que permite agregar reacciones a las notas de una tarea
                agregarReaccionANotaDeTarea(nombreProyecto, nombreTarea);
                break;
            //Si el usuario selecciona la opcion 6
            case 6:
                //Se llama la funcion que permite mostrar reacciones de las notas de una tarea
                mostrarReaccionesANotaDeTarea(nombreProyecto, nombreTarea);
                break;
            //Si el usuario selecciona la opcion 0
            case 0:
                return; // Salir del menú de la tarea
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
            }
        }
    }

    //Se crea una funcion que permite mostrar las notas de una tarea
    void mostrarNotasTarea(string nombreProyecto, string nombreTarea){
        //Se obtiene una referencia al proyecto usando el nombre del proyecto
        auto &proyecto = proyectos[nombreProyecto];
        //Se busca la tarea dentro del proyecto usando el nombre del proyecto
        auto it = find_if(proyecto.second.begin(), proyecto.second.end(), [&nombreTarea](const Tarea &tarea){
            return tarea.nombre == nombreTarea; 
        });

        //Si la tarea no se encuentra, se muestra un mensaje y se retorna
        if (it == proyecto.second.end()){
            cout << "La tarea " << nombreTarea << " no existe en el proyecto " << nombreProyecto << endl;
            return;
        }

        //Si se encuentra la tarea se muestran sus notas
        cout << "Notas de la tarea " << nombreTarea << ":" << endl;
        cout << it -> notas << endl;
    }

    //Se crea una funcion que permite mostrar las notas de un proyecto
    void mostrarNotasProyecto(string nombreProyecto){
        //Se crea una condicion que verifica si el proyecto que el usuario eligio existe
        if (proyectos.find(nombreProyecto) == proyectos.end()){
            //En caso dado de que el proyecto no exista, se le muestra un mensaje al usuario
            cout << "El proyecto " << nombreProyecto << " no existe" << endl;
            //Se sale de condicion
            return;
        }

        //Si el proyecto existe se muestran sus notas
        cout << "Notas del proyecto " << nombreProyecto << ":" << endl;
        cout << proyectos[nombreProyecto].first.notas << endl;
    }

//Se establecen los atributos publicos
public:
    //Se crea el menu principal
    void menuPrincipal(){
        while (true){
            cout << " Menu Principal:" << endl;
            cout << "1. Crear proyecto" << endl; //Deja crear un proyecto
            cout << "2. Mostrar proyectos" << endl; //Muestra los proyectos creados
            cout << "3. Seleccionar proyecto" << endl; //Deja seleccionar un proyecto
            cout << "4. Exportar datos" << endl; //Exporta los datos
            cout << "5. Importar datos" << endl; //Importa los datos
            cout << "0. Salir" << endl; //Se sale del programa

            int opcion;
            cout << "Ingrese una opcion: ";
            cin >> opcion;

            switch (opcion){
            //Si el usuario selecciona la opcion 1
            case 1:
                //Se llama a funcion que permite crear proyectos
                crearProyecto();
                break;
            //Si el usuario selecciona la opcion 2
            case 2:
                //Se llama la opcion que muestra los proyectos
                mostrarProyectos();
                break;
            //Si el usuario selecciona la opcion 3
            case 3:
                //Se le pide al usuario ingresar el nombre del proyecto que va a seleccionar
                cout << "Ingrese el nombre del proyecto a seleccionar: ";{
                    string nombreProyecto;
                    cin >> nombreProyecto;
                    //Se llama la funcion que le permite eso
                    seleccionarProyecto(nombreProyecto);
                }
                break;
            //Si el usuario selecciona la opcion 4
            case 4:
            {    
                //Se declaran variables
                string nombreArchivo, formato;
                //Se le pide al usuario ingresar el nombre del archivo a exportar
                cout << "Ingrese el nombre del archivo para exportar: ";
                //Se almacena la informacion
                cin >> nombreArchivo;

                //Se le pide ingresar el tipo de formato
                cout << "Ingrese el formato (csv o json, csv por defecto): ";
                //Se almacena la informacion obtenida
                cin >> formato;

                //Se llama la funcion que permite la exportacion
                exportarDatos(nombreArchivo, formato);
                break;
            }
            //Si el usuario selecciona la ocpion 5
            case 5:
            {    
                //Se declaran variables
                string nombreArchivo;
                //Se le pide al usuario ingresar el nombre del archivo a importar
                cout << "Ingrese el nombre del archivo para importar: ";
                //Se almacena la informacion
                cin >> nombreArchivo;

                // Verificar si el archivo existe antes de importar
                if (!filesystem::exists(nombreArchivo)){
                    cout << "El archivo " << nombreArchivo << " no existe." << endl;
                }
                else{
                    //Se llama la funcion que permite importar 
                    importarDatos(nombreArchivo);
                }
                break;
            }
            //Si el usuario decide salirse 
            case 0:
                cout << "Saliendo del programa..." << endl;
                return;
            default:
                cout << "Opción invalida. Intente nuevamente." << endl;
            }
        }
    }
};

int main()
{
    int opcion;

    while (true){
        cout << "Menu de Inicio:" << endl;
        cout << "1. Registrar usuario" << endl; // Permite al usuario registrarse
        cout << "2. Iniciar sesión" << endl; //Permite al usuario iniciar sesion
        cout << "0. Salir" << endl; //Permite al usuario salirse del sistema

        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion){
        //Si el usuario selecciona la opcion 1
        case 1:
            //Se llama la funcion que el permite registrarse
            registrarUsuario();
            break;
        //Si el usuario selecciona la opcion 2
        case 2:
        {   
            //Se llama la funcion que permite iniciar sesion con una condicion que tiene que cumplirarse para entrar al sistema
            if (inicioSesion()){
                //Se crea un objeto de la clase
                Proyecto proyecto;
                //Se llama al menu principal
                proyecto.menuPrincipal();
            }
            break;
        }
        //Si el usuario selecciona la opcion de salrise
        case 0:
            cout << "Saliendo del programa..." << endl;
            return 0;
        default:
            cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
            break;
        }
    }

    return 0;
}
