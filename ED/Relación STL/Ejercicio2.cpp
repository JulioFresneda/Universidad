/*  2. Construye una función que dado el map del ejercicio anterior devuelva un multimap que nos permita
consultar las palabras que aparecen un número determinado de veces.  */


// Julio Fresneda


#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

multimap<string,int> multimapa( const map<string,int> &mapa ){ 

  multimap<string,int> m;

  map<string,int>::const_iterator pos = mapa.begin();
  for( pos = mapa.begin(); pos != mapa.end(); ++pos ){
    for( int i=0; i<pos->second; i++ ){
      m.insert(pair<string,int>(pos->first,1));
    }
  }

  return m;
}





// No es parte del ejercicio, sólo es para probarlo

map<string,int> palabras( const string &name ){
  map<string, int> res;
  string palabra = "";
  char aux;
  map<string, int>::iterator pos;

  ifstream fich;
  fich.open( name.c_str(), ifstream::in );

  int i = 0;

  while( !fich.eof() ){

    fich.get(aux);
    if( (aux > 47 && aux < 57) || (aux > 63 && aux < 91) || (aux > 96 && aux < 123) || (aux > 127 && aux < 166) || (aux > 224 && aux < 238) ){
      palabra = palabra + aux;
      i++;

    }
    else if( i != 0 ){

      if( res.count( palabra ) != 0 ){

        pos = res.find(palabra);
        pos->second = pos->second + 1;
      }
      else res[palabra] = 1;
      i = 0;
      palabra = "";
    }
  }
  fich.close();
  return res;

}


int main(){


  map<string,int> prueba = palabras("texto.txt");

  multimap<string,int> prueba_mm = multimapa(prueba);


  cout << "Numero de veces que está la palabra ''caracal'': ";
  cout << prueba_mm.count("caracal") << endl;

}
