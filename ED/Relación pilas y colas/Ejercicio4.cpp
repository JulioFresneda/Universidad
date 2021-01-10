/*4. Implementa el TDA pila usando dos colas. ¿Qué orden de eficiencia tienen las operaciones push y
pop?*/

// Julio Fresneda

#include <iostream>
#include <queue>

using namespace std;

template<typename T>

class Pila{
private:
  queue<T> almacen;
  queue<T> auxiliar;

public:

  Pila(){}

  Pila( const Pila &y ){
    almacen = y.almacen;
  }

  bool operator<( const Pila<T> &b ){
    if( almacen.size() < b.almacen.size() ) return true;
    else return false;
  }

  bool operator==( const Pila<T> &b ){
    if( almacen == b.almacen ) return true;
    else return false;
  }

  Pila& operator=(const Pila<T> &c){
    Pila<T> pila;
    pila.almacen = c.almacen;
    return pila;
  }

  void push(T v){
    almacen.push(v);
  }

  void pop(){
    int tam_almacen = almacen.size();

    for( int i=0; i<tam_almacen-1; i++ ){
      auxiliar.push(almacen.front());
      almacen.pop();
    }

    almacen = auxiliar;

    int tam_auxiliar = auxiliar.size();
    for( int i=0; i<tam_auxiliar; i++ ){
      auxiliar.pop();
    }
  }

  T top(){
    return almacen.back();
  }

  bool empty(){
    return almacen.empty();
  }

  int size(){
    return almacen.size();
  }
};

int main(){

  Pila<int> prueba;

  cout << "Probando métodos: " << endl;

  if( prueba.empty() ) cout << "Empty ok" << endl << flush;

  prueba.push(1);
  prueba.push(2);
  prueba.push(3);
  prueba.push(4);

  int tam = prueba.size();
  cout << "Tamaño = " << tam << endl << flush;
  cout << "Top = " << prueba.top() << endl << flush;

  cout << "Mostrando pila: ";
  for( int i=0; i<tam; i++ ){
    cout << prueba.top();
    prueba.pop();
  }



}
