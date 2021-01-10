/*2. Implementa un función para determinar si una expresión contenida en un string tiene una configura-
ción de paréntesis correcta. Debe tener un orden lineal.*/

// Julio Fresneda

#include <iostream>
#include <stack>
#include <string>
using namespace std;

//  La función no determina si la expresión es sintácticamente correcta, sólo si los paréntesis están puestos en el orden correcto.
//  Por ejemplo, (x+8()) la daría por correcta, aunque 8() no tenga sentido.

bool parentesisCorrectos(const stack<char> &pila){  //  Orden del string en la pila: Primer elemento de string en tope de pila
  bool correcto = true;

  int x = 0;
  int tam = pila.size();

  for( int i = 0; i < tam && correcto; i++ ){

    if( pila.top() == '(' ){
      x++;
    }

    if( pila.top() == ')' ){
      if( x == 0 )
        correcto = false;
      else x--;
    }
  }

  if( ( x == 0 ) && correcto ) return true;
  else return false;

}

int main(){
  stack<char> prueba;
  string p = "(5+3)+((4-2)-8+(33))";  // Función de prueba


  for( int i=0; i<p.size(); i++ ){
    prueba.push(p[p.size()-i-1]);
  }

  int tam = prueba.size();

  bool ok = ( parentesisCorrectos(prueba)  );
  if( ok ) cout << "ok";

}
