/*  20. En un servicio de urgencias de un hospital quieren tener la posibilidad de poder gestionar el orden
en que los pacientes se irán atendiendo. Para ello, de cada paciente se guarda nombre, apellidos,
dni, gravedad. Al mismo tiempo se quiere poder acceder por dni. Construye una clase adecuada e
implementa las operaciones de inserción y borrado.  */

// Julio Fresneda

#include<map>
#include<list>
#include<iostream>
#include<string>
using namespace std;

struct datos{
  int gravedad;
  string nombre;
  string primer_apellido;
  string segundo_apellido;
};

class Pacientes{
private:

map<string,datos> mapa_pacientes;
list< map<string,datos>::iterator > lista;

public:

  void guardar_datos( int gravedad, string nombre, string ap, string segap, string _dni ){
    datos d;
    string dni;
    d.nombre = nombre;
    d.gravedad = gravedad;    // A menor número, más grave
    d.primer_apellido = ap;
    d.segundo_apellido = segap;
    dni = _dni;

    pair<string,datos> par;
    par.first = dni;
    par.second = d;

    pair<map<string,datos>::iterator , bool> parit;

    parit = mapa_pacientes.insert(par);
    map<string,datos>::iterator ite = parit.first;
    datos dat = ite->second;


    list< map<string,datos>::iterator >::iterator it = lista.begin();
    bool ok = false;
    while( it != lista.end() && !ok ){
      if( (*it)->second.gravedad > dat.gravedad )
        ++it;
      else ok = true;
    }
    lista.insert(it,ite);

  }

  void mostrar_paciente(const string &dni ){
     datos d = mapa_pacientes.find(dni)->second;
     cout << "Nombre completo: " << d.nombre << " " << d.primer_apellido << " " << d.segundo_apellido << endl;
     cout << "Gravedad: " << d.gravedad << endl;
  }

  void atender_mas_grave(){
    cout << "Los pacientes mas graves son: " << endl;
    list<map<string,datos>::iterator >::iterator end = lista.end();
    --end;
    int x = (*end)->second.gravedad;

    list<map<string,datos>::iterator >::iterator it = lista.end();
    --it;
    bool ok = false;
    while( (*it)->second.gravedad == x && !ok){
      cout << endl;
      mostrar_paciente((*it)->first);
      if( it == lista.begin() ) ok = true;
      else --it;

    }
  }
};

int main(){

  Pacientes pac;
  pac.guardar_datos(3,"Julio","Fresneda","García","49215154F");
  pac.guardar_datos(2,"Pepe","G","G","43443");
  pac.guardar_datos(1,"AA","S","SS","112");
  pac.guardar_datos(2,"e","w","e","33");

  pac.mostrar_paciente("49215154F");
  pac.atender_mas_grave();
}
