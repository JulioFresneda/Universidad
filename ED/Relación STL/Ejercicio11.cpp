/*  11. Implementa una función bool contenida(const list<T> &l1, const list<T> &l2)
a la que se le pasen dos listas y compruebe si la lista l1 está contenida en l2 (si los elementos apa-
recen en la otra y en el mismo orden).  */

// Julio Fresneda

// Compilar con -std=c++11

#include <iostream>
#include <list>
using namespace std;

template<typename T>
bool contenida( const list<T> &l1, const list<T> &l2 ){
  typename list<T>::const_iterator pos_l1, pos_l2;
  bool contenida = false;

  if( l1.size() >= l2.size() ) {
    pos_l2 = l2.cbegin();

    for( pos_l1 = l1.cbegin(); pos_l1 != l1.cend() && pos_l2 != l2.cend(); ++pos_l1 ){

      if( *(l2.cbegin()) == *pos_l1 && !contenida ) contenida = true;
      if( contenida ){
        if( *pos_l2 != *pos_l1 ) {
          contenida = false;
          pos_l2 = l2.cbegin();
        }
        ++pos_l2;
      }
    }
    if( pos_l2 != l2.cend() ) contenida = false;
  }

  return contenida;
}


int main(){
  list<int> lista1;
  lista1.push_back(1);
  lista1.push_back(2);
  lista1.push_back(3);
  lista1.push_back(4);

  list<int> lista2;
  lista2.push_back(2);
  lista2.push_back(3);


  if( contenida(lista1,lista2) ) cout << "OK" << endl;
  cout << endl;

  lista2.push_back(4);

  if( contenida(lista1,lista2) ) cout << "OK" << endl;
  cout << endl;

  lista2.push_back(5);

  if( contenida(lista1,lista2) ) cout << "OK" << endl;
  cout << endl;











}
