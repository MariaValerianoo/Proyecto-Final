#include <iostream>
#include <map>
#include <string>
using namespace std;



class Responsable{
    private:
    // Crear una estructura para almacenar las tareas y sus responsables
    map<string, string> tareas_responsables;
    public:
    string tarea;
    string nom;
    Responsable(){
        // Agregar tareas y responsables

    cout<<"Primero dinos que tarea es: (Escribelo asi:Tarea1) \n";
    cin>>tarea;
    cout<<"Ahora dime el nombre de la persona a la que se lo vamos a asignar: \n";
    cin>>nom;
    tareas_responsables[tarea] = nom;

    }

    // Consultar el responsable de una tarea específica
    void consultarResponsable(const string& tarea) {
        if (tareas_responsables.find(tarea) != tareas_responsables.end()) {
            cout << "El responsable de " << tarea << " es " << tareas_responsables[tarea] << endl;
        } else {
            cout << "La tarea " << tarea << " no tiene un responsable asignado." << endl;
        }
    }
};

int main() {
    Responsable responsable;

    // Consultar el responsable de una tarea específica
    responsable.consultarResponsable("Tarea2");

    return 0;
}