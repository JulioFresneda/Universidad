/* 9. Implementa una función list<T> mezclar(const list<T> &l1, const list<T> &l2)
que dadas dos listas ordenadas l1 y l2 devuelva una lista ordenada mezclando las dos listas. */

// Julio Fresneda

// Compilar usando -std=c++11


#include <iostream>
#include <list>
using namespace std;


template<typename T>
list<T> mezcla_ordenada( const list<T> &l1, const list<T> &l2 ){
  list<T> salida;
  typename list<T>::const_iterator pos1, pos2;

  pos1 = l1.cbegin();
  pos2 = l2.cbegin();

  while( pos1 != l1.cend() || pos2 != l2.cend() ){
    if( (*pos1 < *pos2) && (pos1 != l1.cend()) ){
      salida.push_back(*pos1);
      ++pos1;
    }
    else if( pos2 != l2.cend() ) {
      salida.push_back(*pos2);
      ++pos2;
    }

    if( pos2 == l2.cend() && pos1 != l1.cend() ){
      salida.push_back(*pos1);
      ++pos1;
    }


  }

  return salida;
}

int main(){

  list<int> lista1;
  lista1.push_back(1);
  lista1.push_back(2);
  lista1.push_back(2);
  lista1.push_back(3);
  lista1.push_back(4);

  list<int> lista2;
  lista2.push_back(0);
  lista2.push_back(3);
  lista2.push_back(3);
  lista2.push_back(4);
  lista2.push_back(5);
  lista2.push_back(6);

  list<int> salida = mezcla_ordenada(lista1,lista2);

  list<int>::iterator pos;

  cout << endl;
  for( pos = salida.begin(); pos != salida.end(); ++pos ){
    cout << *pos << " ";
  }
  cout << endl;

}
