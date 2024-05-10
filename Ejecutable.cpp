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
