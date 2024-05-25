#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Responsable {
private:
    map<string, vector<string>> tareas_responsables;

public:
    void asignarResponsable(const string& tarea, const string& responsable) {
        tareas_responsables[tarea].push_back(responsable);
    }

    void consultarResponsable(const string& tarea) {
        auto it = tareas_responsables.find(tarea);
        if (it != tareas_responsables.end()) {
            cout << "Responsables de " << tarea << ": ";
            for (const auto& resp : it->second) {
                cout << resp << " ";
            }
            cout << endl;
        } else {
            cout << "La tarea " << tarea << " no tiene responsables asignados." << endl;
        }
    }
};

int main() {
    Responsable responsable;

    responsable.asignarResponsable("Tarea1", "Juan");
    responsable.asignarResponsable("Tarea1", "Ana");
    responsable.asignarResponsable("Tarea2", "Pedro");

    responsable.consultarResponsable("Tarea1");
    responsable.consultarResponsable("Tarea2");
    responsable.consultarResponsable("Tarea3"); 

    return 0;
}
