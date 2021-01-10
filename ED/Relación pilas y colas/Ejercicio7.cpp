/*7. Implementa una función insertar(P, pos, x) que inserte un elemento en una pila P en la posición pos.
La pila debe quedar como estaba antes de insertar el elemento (salvo por el nuevo elemento)*/

// Julio Fresneda

#include <iostream>
#include <stack>

using namespace std;

template<typename T>

void insertar( stack<T> &p, int pos, const T &x ){
  int tam;
  stack<T> aux;
  if( pos >= p.size() )
    p.push(x);
  else{
    tam = p.size();

    for( int i=0; i<tam-pos; i++ ){
      aux.push(p.top());
      p.pop();
    }
    p.push(x);

    tam = aux.size();
    for(int i=0; i<tam; i++ ){
      p.push(aux.top());
      aux.pop();
    }
  }
}

int main(){
  stack<int> prueba;
  prueba.push(1);
  prueba.push(2);
  prueba.push(3);
  prueba.push(4);
  prueba.push(5);

  insertar(prueba,0,9);
  insertar(prueba,4,9);
  insertar(prueba,100,9);

  cout << endl << endl << "Stack después de insertar: " << endl;
  int tam = prueba.size();

  for( int i=0; i<tam; i++ ){
    cout << prueba.top() << endl;
    prueba.pop();
  }
}
