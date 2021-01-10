/*  19. Escribe un programa que permita leer de la entrada estándar una serie de coordenadas (como un par
de float) y que contabilice de forma eficiente el número de veces que aparece cada uno de los pares.  */

// Julio Fresneda


#include <iostream>
#include <set>
using namespace std;

multiset<pair<float, float> > coordenadas;

float a, b;
int x;

int main(){
  cout << "Pulse 1 para introducir coordenadas, otro número para salir." << endl;
  cin >> x;
  while( x == 1 ){
    cout << "Introduce coordenadas: ";
    cin >> a >> b;
    coordenadas.insert(pair<float,float>(a,b));
    cout  << "Coordenadas insertadas. Las coordenadas introducidas aparecen " << coordenadas.count(pair<float,float>(a,b)) << " veces." << endl;
    cout << "\nPulse 1 para introducir coordenadas, otro número para salir." << endl;
    cin >> x;
  }
}
