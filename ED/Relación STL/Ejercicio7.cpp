/*  7. Implementa una función que dada una lista l devuelva una lista que tenga los elementos de l pero en
orden inverso.  */

// Julio Fresneda

// Compilar con std=c++11
#include <iostream>
#include <list>
using namespace std;

template<typename T>

list<T> lista_inversa( const list<T> &lista ){

  list<T> l;
  typename list<T>::const_iterator pos = lista.cend();
  pos--;
  while( pos != lista.cbegin() ){
    l.push_back( *pos );
     --pos;
  }

  l.push_back( *pos );

  return l;
}


int main(){

  list<int> prueba;
  prueba.push_back(1);
  prueba.push_back(2);
  prueba.push_back(3);

  list<int>::iterator pos;
  for( pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << *pos << " ";
  }

  prueba = lista_inversa(prueba);

  cout << endl;

  for( pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << *pos << " ";
  }
}
