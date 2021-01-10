/*3. Implementa un TDA cola usando como representación dos pilas.*/

// Julio Fresneda

#include <iostream>
#include <stack>

using namespace std;

template<typename T>

class Cola{
private:
  stack<T> almacen;
  stack<T> auxiliar;

public:

  Cola(){

  }

  Cola( const Cola &y ){
    almacen = y.almacen;
  }

  void push(T v){

    if( !almacen.empty() ){
      int tam_almacen = almacen.size();
      for( int i=0; i<tam_almacen; i++ ){
        auxiliar.push(almacen.top());
        almacen.pop();
      }

      almacen.push(v);

      int tam_auxiliar = auxiliar.size();
      for( int i=0; i<tam_auxiliar; i++ ){
        almacen.push(auxiliar.top());
        auxiliar.pop();
      }
    } else almacen.push(v);


  }

  T front(){
    return almacen.top();
  }

  T back(){
    int tam_almacen = almacen.size();
    for( int i=0; i<tam_almacen; i++ ){
      auxiliar.push(almacen.top());
      almacen.pop();
    }

    T back = auxiliar.top();

    int tam_auxiliar = auxiliar.size();
    for( int i=0; i<tam_auxiliar; i++ ){
      almacen.push(auxiliar.top());
      auxiliar.pop();
    }

    return back;
  }

  void pop(){
    almacen.pop();
  }

  bool empty(){
    return almacen.empty();
  }

  int size(){
    return almacen.size();
  }

  bool operator<( const Cola<T> &b ){
    if( almacen.size() < b.almacen.size() ) return true;
    else return false;
  }

  bool operator==( const Cola<T> &b ){
    if( almacen == b.almacen ) return true;
    else return false;
  }

  Cola& operator=(const Cola<T> &c){
    Cola<T> cola;
    cola.almacen = c.almacen;
    return cola;
  }

};


int main(){
  Cola<int> prueba;

  if( prueba.empty() ) cout << "metodo empty ok" << endl << flush;

  prueba.push(4);

  prueba.push(5);

  prueba.push(6);



  int tam = prueba.size();

  for( int i=0; i<tam; i++ ){   // Observamos que se cumple la metodología FIFO
    cout << prueba.front();
    prueba.pop();
  }

  Cola<int> prueba2 = prueba;

  if( prueba == prueba2 ) cout << endl << "operador == y = ok" << endl << flush;

  prueba2.push(5);

  if( prueba < prueba2 ) cout << endl << "operador < ok" << endl << flush;

}
