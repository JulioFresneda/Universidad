/*5. Se llama expresión en postfijo a una expresión matemática en la que cada operación aparece con sus
dos operandos seguidos por el operador. Por ejemplo: 2 3 + 5 * Escribe un programa que evalue una
expresión en postfijo.
abˆc*d/e+ donde a = 5, b = 3, c = d = 2, e = 9
abcde+*+ donde a = 12, b = 4, c = 7, d = 5, e = 2
ab+cd*+e* donde a = 2, b = 6, c = 3, d = 5, e = 9*/


// Julio Fresneda

#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

int resuelvePostfijo( const string &exp, int valores[5] ){  // Se asume que se introduce correctamente la expresión
  stack<int> pila;
  int i1, i2, i3, resultado;


  for( int i=0; i<exp.size(); i++ ){

   switch( exp[i] ){

    case '+':

      i1 = pila.top();
      pila.pop();

      i2 = pila.top();
      pila.pop();

      i3 = i1 + i2;

      pila.push(i3);
      break;

    case '-':

      i1 = pila.top();
      pila.pop();

      i2 = pila.top() ;
      pila.pop();

      i3 = i2 - i1;

      pila.push(i3);
      break;

    case '/':

      i1 = pila.top();
      pila.pop();

      i2 = pila.top();
      pila.pop();

      i3 = i2 / i1;

      pila.push(i3);
      break;

    case '*':

      i1 = pila.top();
      pila.pop();

      i2 = pila.top();
      pila.pop();

      i3 = i2 * i1;

      pila.push(i3);
      break;

    case '^':

      i1 = pila.top();
      pila.pop();

      i2 = pila.top();
      pila.pop();

      i3 = 1;
      for(int j=0; j<i1; j++){
        i3 = i3*i2;
      }

      pila.push(i3);
      break;

    default:

      i1 = exp[i]-'a';
      pila.push(valores[i1]);
      break;

    }


  }

  resultado = pila.top();
  return resultado;



}



int main(){

  int var[5];
  var[0] = 5;
  var[1] = 3;
  var[2] = 2;
  var[3] = 2;
  var[4] = 9;

  string prueba1 = "ab^c*d/e+";
  int res = resuelvePostfijo(prueba1,var);

  cout << res << endl;

  int var2[5];
  var[0] = 12;
  var[1] = 4;
  var[2] = 7;
  var[3] = 5;
  var[4] = 2;

  string prueba2 = "abcde+*+";  // Falta un operador para que la expresión sea correcta
  int res2 = resuelvePostfijo(prueba2,var);

  cout << res2 << endl;

  int var3[5];
  var3[0] = 2;
  var3[1] = 6;
  var3[2] = 3;
  var3[3] = 5;
  var3[4] = 9;

  string prueba3 = "ab+cd*+e*";
  int res3 = resuelvePostfijo(prueba3,var3);

  cout << res3 << endl;
}
