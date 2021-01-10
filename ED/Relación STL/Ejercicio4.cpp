/*  4. Implementa una función desencripta que haga el proceso inverso al del ejercicio anterior.  */


// Julio Fresneda


#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

string desencriptador( const string &codigo, const map<char,char> &mapa ){

  string desencriptada = "";
  map<char,char> mapd;
  map<char,char>::const_iterator pos;

  for( map<char,char>::const_iterator it = mapa.begin(); it != mapa.end(); ++it ){
    mapd[it->second] = it->first;
  }

  for( unsigned int i=0; i<codigo.length(); i++ ){
    desencriptada += mapd.find(codigo[i])->second;
  }
  return desencriptada;
}


// Lo dejamos para probar el código

string encriptador( const string &codigo, const map<char,char> &mapa ){

  string encriptada = "";
  for( unsigned int i=0; i<codigo.length(); i++ ){
    encriptada += mapa.find(codigo[i])->second;
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

  encriptada = desencriptador(encriptada, mapa);

  cout << endl << encriptada << endl;

}
