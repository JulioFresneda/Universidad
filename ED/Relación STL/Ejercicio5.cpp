/*  5. Implementa una función que, dada una lista l de tipo T y un elemento x de tipo T, elimine el elemento
x de todas las posiciones en las que aparezca en l. Por ejemplo: si x = 1 y l = (2, 1, 1, 1, 1, 5, 3) el
resultado deberı́a ser (2, 5, 3)  */

// Julio Fresneda

#include <iostream>
#include <list>
using namespace std;

template <typename T>
void eliminar( list<T> &l , const T &t ){

  typename list<T>::iterator pos;
  for( pos = l.begin(); pos != l.end(); ++pos ){
    if( t == *pos ){
      pos = l.erase(pos);
      --pos;
    }
  }
}


int main(){

  list<int> lista;
  for( int i=1; i<4; ++i ) lista.push_back(i*10);
  for( int i=4; i<7; ++i ) lista.push_back(40);
  for( int i=7; i<10; ++i )lista.push_back(i*10);

  for ( list<int>::iterator it=lista.begin(); it!=lista.end(); ++it )
    cout << ' ' << *it;
  cout << '\n';

  eliminar(lista,40);

  for ( list<int>::iterator it=lista.begin(); it!=lista.end(); ++it )
    cout << ' ' << *it;
  cout << '\n';
}
