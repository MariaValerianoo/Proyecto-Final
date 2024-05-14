#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Definición de la estructura Tarea
struct Tarea
{
    string nombre;      // Nombre de la tarea
    string estado;      // Estado de la tarea (por ejemplo, pendiente, en progreso, completada)
    int prioridad;      // Prioridad de la tarea
    string responsable; // Quién es responsable de la tarea
    string fechaLimite; // Fecha límite de la tarea
    string resumen;     // Resumen de la tarea

    // Constructor para inicializar una tarea con valores predeterminados
    Tarea() : nombre(""), estado("pendiente"), prioridad(0), responsable(""), fechaLimite(""), resumen("") {}

    // Constructor para inicializar una tarea con valores específicos
    Tarea(string n, string s, int p, string r, string f, string re)
        : nombre(n), estado(s), prioridad(p), responsable(r), fechaLimite(f), resumen(re) {}
};

// Clase para gestionar las tareas
class GestorDeTareas
{
private:
    map<int, Tarea> tareas;         // Mapa para almacenar tareas por ID
    queue<Tarea> colaDeTareas;      // Cola para gestionar tareas por prioridad
    map<int, Tarea *> mapaDeTareas; // Mapa para mapear IDs a punteros de Tarea en la cola

public:
    // Función para agregar una nueva tarea
    void agregarTarea(int id, const Tarea &tarea)
    {
        tareas[id] = tarea;                       // Agrega la tarea al mapa de tareas
        colaDeTareas.push(tarea);                 // Agrega la tarea a la cola
        mapaDeTareas[id] = &colaDeTareas.front(); // Mapea el ID a un puntero al primer elemento de la cola
    }

    // Función para obtener una tarea por ID
    Tarea obtenerTarea(int id)
    {
        if (tareas.find(id) != tareas.end())
        {                      // Verifica si la tarea existe
            return tareas[id]; // Retorna la tarea si existe
        }
        return Tarea(); // Retorna una tarea vacía usando el constructor sin argumentos
    }

    // Función para actualizar la prioridad de una tarea
    void actualizarPrioridad(int id, int nuevaPrioridad)
    {
        if (tareas.find(id) != tareas.end())
        {                                          // Verifica si la tarea existe
            tareas[id].prioridad = nuevaPrioridad; // Actualiza la prioridad de la tarea
            colaDeTareas.pop();                    // Elimina el primer elemento de la cola
            tareas[id].prioridad = nuevaPrioridad; // Actualiza la prioridad de la tarea en el mapa
            colaDeTareas.push(tareas[id]);         // Agrega la tarea actualizada a la cola
        }
    }

    // Función para eliminar una tarea
    void eliminarTarea(int id)
    {
        if (tareas.find(id) != tareas.end())
        {                           // Verifica si la tarea existe
            tareas.erase(id);       // Elimina la tarea del mapa
            colaDeTareas.pop();     // Elimina el primer elemento de la cola
            mapaDeTareas.erase(id); // Elimina el mapeo del ID
        }
    }

    // Función para mostrar todas las tareas
    void mostrarTareas()
    {
        for (const auto &tarea : tareas)
        {                                                                                 // Itera sobre cada tarea en el mapa
            cout << "ID: " << tarea.first << ", Nombre: " << tarea.second.nombre << endl; // Imprime el ID y el nombre de la tarea
        }
    }

    // Función para guardar las tareas en un archivo
    // Función para guardar las tareas en un archivo
    void guardarTareas(const string &filename)
    {
        ofstream archivo(filename); // Abre el archivo para escritura
        if (!archivo.is_open())
        {
            cerr << "Error al abrir el archivo para escritura." << endl;
            return;
        }
        for (const auto &tarea : tareas)
        { // Itera sobre cada tarea en el mapa
            archivo << tarea.first << "," << tarea.second.nombre << "," << tarea.second.estado << ","
                    << tarea.second.prioridad << "," << tarea.second.responsable << ","
                    << tarea.second.fechaLimite << "," << tarea.second.resumen << "\n"; // Escribe la tarea en el archivo
        }
        archivo.close(); // Cierra el archivo
    }

    // Función para cargar tareas desde un archivo
    void cargarTareas(const string &filename)
    {
        ifstream archivo(filename); // Abre el archivo para lectura
        if (!archivo.is_open())
        {
            cerr << "Error al abrir el archivo para lectura." << endl;
            return;
        }
        string linea;
        while (getline(archivo, linea))
        {
            cout << "Línea leída: " << linea << endl; // Imprime la línea leída del archivo
            stringstream ss(linea);                   // Convierte la línea en un stream
            int id;
            string nombre, estado, responsable, fechaLimite, resumen;
            char prioridad;
            ss >> id >> nombre >> estado >> prioridad >> responsable >> fechaLimite >> resumen; // Extrae los datos de la línea
            Tarea tarea(nombre, estado, prioridad - '0', responsable, fechaLimite, resumen);    // Crea una nueva tarea
            tareas[id] = tarea;                                                                 // Agrega la tarea al mapa
            colaDeTareas.push(tarea);                                                           // Agrega la tarea a la cola
            mapaDeTareas[id] = &colaDeTareas.front();                                           // Mapea el ID a un puntero al primer elemento de la cola
        }
        archivo.close(); // Cierra el archivo
    }
    // Función para cambiar el estado de una tarea
void cambiarEstado(int id, string nuevoEstado)
{
    // Verifica si la tarea con el ID proporcionado existe en el mapa de tareas
    if (tareas.find(id)!= tareas.end())
    {
        // Verifica si el nuevo estado es uno de los estados válidos ("pendiente", "en progreso", "completada")
        if ((nuevoEstado == "pendiente") || (nuevoEstado == "en progreso") || (nuevoEstado == "completada"))
        {
            // Cambia el estado de la tarea en el mapa de tareas
            tareas[id].estado = nuevoEstado;
            
            // Elimina la tarea actual de la cola de tareas para reflejar el cambio de estado
            colaDeTareas.pop();
            
            // Vuelve a agregar la tarea a la cola de tareas con el nuevo estado, lo que actualiza su posición en la cola
            // según su prioridad, ya que el estado puede afectar la prioridad de la tarea en la gestión de tareas
            colaDeTareas.push(tareas[id]);
        }
        else
        {
            // Si el nuevo estado no es válido, muestra un mensaje de error
            cerr << "Error: El estado ingresado no es válido o la tarea no existe." << endl;
        }
    }
    else
    {
        // Si la tarea con el ID proporcionado no existe, muestra un mensaje de error
        cerr << "Error: El estado ingresado no es válido o la tarea no existe." << endl;
    }
}
};

int main()
{
    GestorDeTareas gestor;          // Instancia del gestor de tareas
    string filename = "tareas.txt"; // Nombre del archivo donde se guardarán las tareas

    // Verifica si el archivo de tareas existe y carga las tareas desde él
    if (ifstream(filename))
    {
        gestor.cargarTareas(filename); // Carga las tareas desde el archivo
    }

    int opcion, id, prioridad;
    string nombre, estado, responsable, fechaLimite, resumen;
    string nuevoEstado; // Variable para almacenar el nuevo estado de la tarea

    // Bucle principal del programa
    while (true)
    {
        cout << "\n1. Agregar Tarea\n2. Actualizar Prioridad\n3. Eliminar Tarea\n4.Actulizar estado de tarea\n5. Mostrar Tareas \n6. Guardar Tareas\n7. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: // Agregar Tarea
            cout << "Ingrese el ID de la tarea: ";
            cin >> id;
            cout << "Ingrese el nombre de la tarea: ";
            cin >> nombre;
            cout << "Ingrese el estado de la tarea (pendiente, en-progreso, completada): ";
            cin >> estado;
            cout << "Ingrese la prioridad de la tarea (1-10): ";
            cin >> prioridad;
            cout << "Ingrese el responsable de la tarea: ";
            cin >> responsable;
            cout << "Ingrese la fecha límite de la tarea (AAAA-MM-DD): ";
            cin >> fechaLimite;
            cout << "Ingrese el resumen de la tarea: ";
            cin.ignore(); // Ignora el salto de línea del input anterior
            getline(cin, resumen);
            gestor.agregarTarea(id, Tarea(nombre, estado, prioridad, responsable, fechaLimite, resumen));
            break;
        case 2: // Actualizar Prioridad de Tarea
            cout << "Ingrese el ID de la tarea a actualizar: ";
            cin >> id;
            cout << "Ingrese la nueva prioridad de la tarea (1-10): ";
            cin >> prioridad;
            gestor.actualizarPrioridad(id, prioridad);
            break;
        case 3: // Eliminar Tarea
            cout << "Ingrese el ID de la tarea a eliminar: ";
            cin >> id;
            gestor.eliminarTarea(id);
            break;
        case 4: // Cambiar Estado
            cout << "Ingrese el ID de la tarea: ";
            cin >> id;
            cout << "Ingrese el nuevo estado de la tarea (pendiente, en progreso, completada): ";
            cin >> nuevoEstado;
            gestor.cambiarEstado(id, nuevoEstado);
            break;
        case 5: // Mostrar Tareas
            gestor.mostrarTareas();
            break;
        case 6: // Guardar Tareas
            cout << "Ingrese el nombre del archivo para guardar las tareas: ";
            cin >> filename;
            gestor.guardarTareas(filename);
            break;
        case 7:       // Salir
            return 0; // Termina el programa
        default:
            cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }
    }

    return 0;
}
