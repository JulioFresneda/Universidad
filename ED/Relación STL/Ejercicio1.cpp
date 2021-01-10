/*  1. Construye una función a la que se le pase el nombre de un fichero y devuelva un map que contenga
las palabras que aparecen y el número de veces que aparece cada una.  */


// Julio Fresneda


#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

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

  map<string,int>::iterator pos;

  for( pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << "Palabra: " << pos->first;
    string s = pos->first;
    int i = 20 - s.length();

    for( int j=0; j<i; j++ ){
      cout << " ";
    }

    cout << "Repeticiones: " << pos->second << endl;
  }
}
