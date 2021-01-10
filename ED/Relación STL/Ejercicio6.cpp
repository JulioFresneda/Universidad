/*  6. Implementa una función elimina_duplicados(list<T> &l) que elimine los elementos du-
plicados (sin ordenar previamente la lista).  */

// Julio Fresneda

#include <iostream>
#include <list>
using namespace std;

template <typename T>
void eliminar_dup( list<T> &l )
{
  for (typename list<T>::iterator p = l.begin();  p != l.end(); ++p) {
    typename list<T>::iterator q = p;
    ++q;
    while (q != l.end()) {
      if (*p == *q)
        q = l.erase(q);
      else
        ++q;
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

  eliminar_dup(lista);

  for ( list<int>::iterator it=lista.begin(); it!=lista.end(); ++it )
    cout << ' ' << *it;
  cout << '\n';

}
