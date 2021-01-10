/*13. Implementa una cola con prioridad que contenga strings y de la que salgan primero las cadenas de
caracteres que tengan más vocales y que en caso de igualdad salgan por orden alfabético.*/

// Julio Fresneda


#include <iostream>
#include <queue>

using namespace std;

class string_priority{
public:
  string s;

  string_priority(){}

  string_priority( const string &c ){
    s = c;
  }

  string mostrar(){
    return s;
  }

  bool operator<(const string_priority & a) const{
    int voc1, voc2;
    voc1 = voc2 = 0;

    for( int i=0; i<a.s.size(); i++ ){
      if( a.s[i] == 'a' || a.s[i] == 'e' || a.s[i] == 'i' || a.s[i] == 'o' || a.s[i] == 'u' )
        voc1++;
    }
    for( int i=0; i<s.size(); i++ ){
      if( s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' )
        voc2++;
    }

    if( voc1 != voc2 ) return ( voc2 < voc1 );
    else {
      int tam;
      bool menor = false;
      bool fuera = false;

      if( s.size() < a.s.size() ) tam = s.size();
      else tam = a.s.size();

      for( int i=0; i< tam && !fuera; i++ ){
        if( s[i] != a.s[i] ){
           menor = (s[i] > a.s[i]);
           fuera = true;
         }
      }
      return menor;

    }
  }



};

int main(){


  string_priority prueba2("aabcdef");
  string_priority prueba3("aabcdeb");
  string_priority prueba("holae");

  priority_queue<string_priority> cola;

  cola.push(prueba2);
  cola.push(prueba3);
  cola.push(prueba);

  string_priority x = cola.top();
  cout << x.mostrar() << endl;

}
