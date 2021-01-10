/* 10. Implementa una función a la que se le pase una lista de enteros y un entero x de manera que cada vez
que aparezca en una posición ese valor, se inserte x-1 en la posición siguiente.  */

// Julio Fresneda

#include <iostream>
#include <list>
using namespace std;

void funcion10( list<int> &l, int x ){
  list<int>::iterator pos;
  for( pos = l.begin(); pos != --l.end(); ++pos ){
    if( *pos == x ){
      ++pos;
      *pos = x-1;
      --pos;
    }
  }

}

int main(){
  list<int> lista1;
  lista1.push_back(1);
  lista1.push_back(2);
  lista1.push_back(3);
  lista1.push_back(4);

  funcion10( lista1, 2 );

  list<int>::iterator pos;

  cout << endl;
  for( pos = lista1.begin(); pos != lista1.end(); ++pos ){
    cout << *pos << " ";
  }
  cout << endl;

  funcion10( lista1, 3 );
  funcion10( lista1, 1 );

  for( pos = lista1.begin(); pos != lista1.end(); ++pos ){
    cout << *pos << " ";
  }
  cout << endl;

}
