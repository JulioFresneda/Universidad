/*9. Un tipo ventana es un tipo de dato que permite insertar un elemento, mover derecha, mover izquierda,
borrar elemento y que se implementa usando dos pilas. Implementa ese tipo de dato con las operacio-
nes comentadas.*/

// Julio Fresneda

#include<stack>
#include<iostream>
using namespace std;



template<typename T> class Ventana{
private:
  stack<T> pila_izq;
  stack<T> pila_dcha;
public:
  Ventana(){}

  Ventana( const Ventana &V ){pila_izq = V.pila_izq && pila_dcha = V.pila_dcha;}

  void push( const T &x ){
    pila_izq.push(x);
  }


  void erase(){
    pila_izq.pop();
  }

  void next(){
    pila_izq.push(pila_dcha.top());
    pila_dcha.pop();
  }

  void back(){
   pila_dcha.push(pila_izq.top());
   pila_izq.pop();
 }

 T mostrarTop(){
   return pila_izq.top();
 }

};

int main(){

  Ventana<int> v;
  v.push(1);
  v.push(2);
  v.push(3);


  v.back();
  cout << endl << v.mostrarTop() << endl << flush;

  v.next();

  cout << endl << v.mostrarTop() << endl << flush;

  v.erase();

  cout << endl << v.mostrarTop() << endl << flush;



}
