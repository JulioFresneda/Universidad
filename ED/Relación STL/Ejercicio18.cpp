/*  18. Define una clase que permita guardar los datos de los pilotos de F1. Por ejemplo, nombre, apellido
(sólo uno), posición en la clasificación, nombre de la escuderı́a. Además debe permitir que se pueda
buscar a un piloto por su apellido. ¿Qué podríamos añadir a esa clase para que se pueda buscar
también por cualquiera de los restantes campos?.  */

// Julio Fresneda

#include <iostream>
#include <map>
using namespace std;

class pilotos{
private:
  struct datos{
    int posicion;
    string nombre;
    string escuderia;
  };

  map< string , datos > mapa_pilotos;

public:

  void guardar_datos( string nombre, string apellido, int posicion, string escuderia ){
    datos d;
    d.posicion = posicion;
    d.nombre = nombre;
    d.escuderia = escuderia;

    mapa_pilotos.insert(pair<string,datos>(apellido,d));
  }

  datos buscar( string apellido ){
    return mapa_pilotos.find(apellido)->second;
  }
};

int main(){

  pilotos prueba;
  prueba.guardar_datos("Julio","Fresneda",1,"Ferrari");
  prueba.guardar_datos("Pepe","García",2,"Mercedes");
  prueba.guardar_datos("Juan","López",5,"RedBull");

  cout << "El piloto García tiene lo siguientes datos:" << endl;
  cout << "Nombre: " << prueba.buscar("García").nombre << endl;
  cout << "Escudería: " << prueba.buscar("García").escuderia << endl;
  cout << "Posición: " << prueba.buscar("García").posicion << endl;

}
