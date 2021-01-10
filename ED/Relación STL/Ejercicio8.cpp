/* 8. Resuelve el problema anterior pero sobre una única lista pasada por referencia. */



// Julio Fresneda


#include <iostream>
#include <list>
using namespace std;

template<typename T>

void lista_inversa( list<T> &lista ){

  list<T> l;
  typename list<T>::iterator pos = lista.end();
  pos--;
  while( pos != lista.cbegin() ){
    l.push_back( *pos );
     --pos;
  }

  l.push_back( *pos );

  lista = l;
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

  lista_inversa(prueba);

  cout << endl;

  for( pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << *pos << " ";
  }
}
