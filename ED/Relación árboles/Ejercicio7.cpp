/*  Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F
7. Construye una función que determine si un árbol binario es completo.*/

#include "bintree.h"
#include <iostream>
using namespace std;

template<typename T>
bool esCompleto( const bintree<T> &tree, const typename bintree<T>::node &node, bool &completo){

  if( node.left().null() ^ node.right().null() ){
    completo = false;
    return false;
  }
  else if( node.left().null() && node.right().null()) return true;
  else return (  !(esCompleto( tree, node.left(), completo ) ^ esCompleto( tree, node.right(), completo ))  && completo );
}


int main(){

  bool c = true;
  bintree<int> Arb(1);  // Árbol completo

  Arb.insert_left(Arb.root(), 1);
  Arb.insert_right(Arb.root(), 1);

  Arb.insert_left(Arb.root().left(), 1);
  Arb.insert_right(Arb.root().left(), 1);

  Arb.insert_left(Arb.root().right(), 1);
  Arb.insert_right(Arb.root().right(), 1);


  bintree<int> Arb2(1);  // Árbol incompleto

  Arb2.insert_left(Arb2.root(), 1);
  Arb2.insert_right(Arb2.root(), 1);

  Arb2.insert_left(Arb2.root().left(), 1);
  Arb2.insert_right(Arb2.root().left(), 1);


  Arb2.insert_right(Arb2.root().right(), 1);


  bintree<int> Arb3(1);  // Árbol incompleto

  Arb3.insert_left(Arb3.root(), 1);
  Arb3.insert_right(Arb3.root(), 1);

  Arb3.insert_left(Arb3.root().left(), 1);
  Arb3.insert_right(Arb3.root().left(), 1);


  cout << "Comprobación arbol uno: ";
  if( esCompleto(Arb,Arb.root(), c) ) cout << "OK" << endl << endl;

  cout << "Comprobación arbol dos: ";
  if( !esCompleto(Arb2,Arb2.root(), c) ) cout << "OK" << endl << endl;

  cout << "Comprobación arbol tres: ";
  if( !esCompleto(Arb3,Arb3.root(), c) ) cout << "OK" << endl << endl;
}
