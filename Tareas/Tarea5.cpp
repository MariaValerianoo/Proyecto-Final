#include <iostream>     
#include <map>          
#include <string>       
#include <vector>       
using namespace std;

// Definición de la clase Responsable
class Responsable {
private:
    // Mapa que asocia cada tarea con una lista de responsables
    map<string, vector<string>> tareas_responsables;

public:
    // Método para asignar un responsable a una tarea
    void asignarResponsable(const string& tarea, const string& responsable) {
        // Agrega el responsable a la lista de responsables de la tarea especificada
        tareas_responsables[tarea].push_back(responsable);
    }

    // Método para consultar los responsables de una tarea específica
    void consultarResponsable(const string& tarea) {
        // Busca la tarea en el mapa
        auto it = tareas_responsables.find(tarea);
        if (it != tareas_responsables.end()) { // Si la tarea se encuentra en el mapa
            cout << "Responsables de " << tarea << ": ";
            // Imprime todos los responsables asociados a la tarea
            for (const auto& resp : it->second) {
                cout << resp << " ";
            }
            cout << endl;
        } else { // Si la tarea no se encuentra en el mapa
            cout << "La tarea " << tarea << " no tiene responsables asignados." << endl;
        }
    }
};

