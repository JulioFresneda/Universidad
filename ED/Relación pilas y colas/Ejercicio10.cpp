/*  10. Usando una pila y una cola, implementa una función que compruebe si un string es un palíndromo.  */

// Julio Fresneda

#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

bool esPalindromo( const string &s ){

  bool es = true;
  stack<char> pila;
  queue<char> cola;

  for( int i=0; i<s.size(); i++ ){
    pila.push(s[i]);
    cola.push(s[i]);
  }

  for( int i=0; i<s.size() && es; i++ ){
    if( pila.top() != cola.front() ) es = false;
    pila.pop();
    cola.pop();
  }

  return es;
}

int main(){

  string prueba = "hola";
  string prueba2 = "abcdedcba";

  if( esPalindromo(prueba2) && !esPalindromo(prueba) ) cout << endl << "Todo OK" << endl;
}
