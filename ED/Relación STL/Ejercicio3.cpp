/*  3. Un método de encriptación basado en un código consiste en transformar cada letra del alfabeto por
otra. Implementa una función que encripte la cadena que se le pase y un map <
char, char > con el código y que devuelva la cadena encriptada.  */


// Julio Fresneda


#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

string encriptador( const string &codigo, const map<char,char> &mapa ){

  string encriptada = "";
  for( unsigned int i=0; i<codigo.length(); i++ ){
    encriptada +=mapa.find(codigo[i])->second;
  }

  return encriptada;
}


int main(){

  string palabra = "pove";
  map<char,char> mapa;
  mapa['p'] = 'q';
  mapa['o'] = 'p';
  mapa['v'] = 'w';
  mapa['e'] = 'f';

  string encriptada = encriptador(palabra,mapa);

  cout << endl << encriptada << endl;

}
