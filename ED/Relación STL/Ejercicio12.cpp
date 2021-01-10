/*  12. Tenemos dos listas: l, que contiene n elementos y otra li que contiene una serie de posiciones de la
lista anterior (valores de la clase iterador). Construye una función a la que se le pasen esas dos listas
y devuelva otra que contenga los elementos de l indicados por las posiciones de la lista li.  */

// Julio Fresneda

//Compilar con -std=c++11

#include <iostream>
#include <list>
using namespace std;

template<typename T>
list<T> funcion12( const list<T> &l, const list<typename list<T>::iterator> &li ){
  list<T> salida;
  for( typename list<typename list<T>::iterator>::const_iterator pos = li.cbegin(); pos != li.cend(); ++pos ){
    salida.push_front(*pos);
  }

  return salida;
}


int main(){

  list<int> lista1;
  lista1.push_front(1);
  lista1.push_front(2);
  lista1.push_front(3);
  lista1.push_front(4);
  lista1.push_front(5);

  list<list<int>::iterator> lista_it;

  for( list<int>::iterator pos = lista1.begin(); pos != lista1.end(); ++pos ){
    if( pos != lista1.begin() && pos != --lista1.end() )
      lista_it.push_front(pos);
  }

  for( list<list<int>::iterator>::iterator pos = lista_it.begin(); pos != lista_it.end(); ++pos ){
    cout << **pos << " ";
  }

  cout << endl;





}
