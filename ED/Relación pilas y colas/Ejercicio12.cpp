/*  12. Implementa una cola con prioridad que contenga strings y de la que salgan primero las cadenas de
caracteres más largas y que en caso de igualdad salgan por orden alfabético. */

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
    if( s.size() != a.s.size() ) return( s.size() < a.s.size() );
    else{
      bool menor = false;
      for( int i=0; i<s.size() && !menor; i++ ){
        if( s[i] > a.s[i] ) menor = true;
      }
      return menor;
    }
  }



};

int main(){

  string_priority prueba("eea");
  string_priority prueba2("eeo");
  string_priority prueba3("eee");

  priority_queue<string_priority> cola;

  cola.push(prueba);
  cola.push(prueba2);
  cola.push(prueba3);

  string_priority x = cola.top();
  cout << x.mostrar() << endl;

}
