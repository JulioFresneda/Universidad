/*  Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F
9. Dos árboles binarios los definimos similares si son iguales en cuanto a su estructura, es decir, cada
nodo en un árbol tiene los mismos hijos y en el mismo lugar que el correspondiente en el otro árbol
(sin importar las etiquetas). Escribe una función que dados dos árboles binarios devuelva si son o no
similares.  */

#include "bintree.h"
#include <iostream>
using namespace std;


bool iguales( const bintree<int>::node &a, const bintree<int>::node &b ){
  if( a.null() && b.null() ) return true;

  if( a.left().null() && a.right().null() && b.left().null() && b.right().null() ){
    return true;
  }
  else if( a.left().null() != b.left().null() || a.right().null() != b.right().null() ){
    return false;
  }
  else return( iguales(a.left(),b.left()) && iguales(a.right(), b.right()) );

}


int main(){


  bintree<int> Arb(1);  // Árbol uno

  Arb.insert_left(Arb.root(), 1);
  Arb.insert_right(Arb.root(), 1);

  Arb.insert_left(Arb.root().left(), 1);
  Arb.insert_right(Arb.root().left(), 1);

  Arb.insert_left(Arb.root().right(), 1);
  Arb.insert_right(Arb.root().right(), 1);


  bintree<int> Arb2(1);  // Árbol dos

  Arb2.insert_left(Arb2.root(), 1);
  Arb2.insert_right(Arb2.root(), 1);

  Arb2.insert_left(Arb2.root().left(), 1);
  Arb2.insert_right(Arb2.root().left(), 1);


  Arb2.insert_right(Arb2.root().right(), 1);


  bintree<int> Arb3(1);  // Árbol tres

  Arb3.insert_left(Arb3.root(), 1);
  Arb3.insert_right(Arb3.root(), 1);

  Arb3.insert_left(Arb3.root().left(), 1);
  Arb3.insert_right(Arb3.root().left(), 1);

  // Comprobamos

  if( iguales(Arb.root(), Arb.root()) ) cout << "OK" << endl;
  if( iguales(Arb2.root(), Arb2.root()) ) cout << "OK" << endl;
  if( iguales(Arb3.root(), Arb3.root()) ) cout << "OK" << endl;

  if( !iguales(Arb.root(), Arb2.root()) ) cout << "OK" << endl;
  if( !iguales(Arb.root(), Arb3.root()) ) cout << "OK" << endl;
  if( !iguales(Arb2.root(), Arb3.root()) ) cout << "OK" << endl;

}
