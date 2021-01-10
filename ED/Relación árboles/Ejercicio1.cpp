/*  Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F
1. Escribe una función que determine cual es la hoja más profunda de un árbol binario. */

#include "bintree.h"
#include <iostream>
using namespace std;

template<typename T>
typename bintree<T>::node mas_profunda( const bintree<T> &b ){

  typename bintree<T>::const_level_iterator it;
  if( b.empty() ) return *it;
  else{
    it = b.begin_level();

    for( unsigned int i=0; i<b.size() -1; i++ ){
      ++it;
    }
    return *it;
  }

}

int main(){
  bintree<int> Arb(1);
  Arb.insert_left(Arb.root(), 1);
  Arb.insert_right(Arb.root(), 9);
  Arb.insert_left(Arb.root().left(), 6);
  Arb.insert_right(Arb.root().left(), 8);
  Arb.insert_right(Arb.root().left().right(), 4);
  Arb.insert_left(Arb.root().right(), 5);

  cout << "Si funciona, este programa debería escribir 4: " << *(mas_profunda(Arb));
}
