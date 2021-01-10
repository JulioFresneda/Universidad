/*  Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F
2. Escribe una función que acepte un valor de tipo node y un árbol general T y devuelva el nivel del
nodo en el árbol.*/

#include "bintree.h"
#include <iostream>
using namespace std;

// Se presupone que se pasan datos correctos
template<typename T>
int nivel( const typename bintree<T>::node &node, const bintree<T> &tree, int niv = 0 ){
  niv++;

  if( node.parent() != tree.root() ){
    niv = nivel(node.parent(),tree,niv);
  }

  return niv;
}




int main(){


  bintree<int> Arb(1);
  Arb.insert_left(Arb.root(), 1);
  Arb.insert_right(Arb.root(), 9);
  Arb.insert_left(Arb.root().left(), 6);
  Arb.insert_right(Arb.root().left(), 8);
  Arb.insert_right(Arb.root().left().right(), 4);
  Arb.insert_left(Arb.root().right(), 5);

  cout << "Si funciona, este programa debería escribir 3: " << nivel(Arb.root().left().right().right(),Arb);


}
