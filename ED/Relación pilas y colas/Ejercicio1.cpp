/*1. Construye una función a la que se se le pase una pila P de tipo T y dos elementos x,y de tipo T y que
modifique la pila de forma que todas las veces que aparezca x se substituya por y (quedando la pila en
el mismo estado en el que estaba anteriormente). Para este ejercicio no se podrán utilizar iteradores.*/


// Julio Fresneda

#include <iostream>
#include <stack>

using namespace std;

template<typename T>

void sustituir(stack<T> &pila, T x, T y){
  stack<T> temp;
  int tam = pila.size();


  for( int i=0; i<tam; i++ ){

    if( pila.top() == x ){

      temp.push(y);
      pila.pop();

    }
    else{

      temp.push(pila.top());
      pila.pop();

    }
  }

  for( int i=0; i<tam; i++){
    pila.push(temp.top());
    temp.pop();
  }

}

int main(){
  stack<int> pilaprueba;

  for(int i=0; i<10; i++){
    pilaprueba.push(i);
  }

  sustituir(pilaprueba,5,6);  // Sustituimos 5 por 6

  for(int i=0; i<10; i++){
    cout << pilaprueba.top() << endl;
    pilaprueba.pop();
  }
}
