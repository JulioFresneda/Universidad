/*8. Implementa una función insertar(Q, pos, x) que inserte un elemento en una cola Q en la posición pos.
La cola debe quedar como estaba antes de insertar el elemento (salvo por el nuevo elemento)*/

// Julio Fresneda

#include<iostream>
#include<queue>
using namespace std;

template<typename T>
void insertar( queue<T> &Q, int pos, const T &x ){
  queue<T> aux;

  if( pos >= Q.size() )
    Q.push(x);
  else{

    for( int i=0; i<pos; i++ ){
      aux.push(Q.front());
      Q.pop();
    }

    aux.push(x);

    int tam = Q.size();
    for( int i=0; i<tam; i++ ){
      aux.push(Q.front());
      Q.pop();
    }
    Q = aux;
  }
}

int main(){

  queue<int> prueba;
  prueba.push(1);
  prueba.push(2);
  prueba.push(3);
  prueba.push(4);
  prueba.push(5);

  insertar(prueba,10,7);
  insertar(prueba,3,7);
  insertar(prueba,0,7);

  int tam = prueba.size();
  for( int i=0; i<tam; i++ ){
    cout << prueba.front() << endl;
    prueba.pop();
  }
}
