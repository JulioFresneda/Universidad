/*6. Dada una matriz que representa un laberinto, construye una función que determine si se puede llegar
desde la entrada hasta la salida. Esta matriz tendrá una ’E’ en la entrada, una ’S’ en la salida, un ’0’
en las casillas por las que se pueda pasar y un ’1’ en las que no. No se puede ir en diagonal.*/

// Julio Fresneda

#include<stack>
#include<iostream>
#include<vector>
#include <unistd.h>


using namespace std;


pair<int,int> resolverLaberinto( const vector<vector<char> > &v ){  // Si no encuentra salida, devuelve la posición de la entrada en la matriz
  stack<pair<int,int> > pila;

  vector<vector<bool> > pisada (v.size(),vector<bool>(v[0].size()));
  pair<int, int > pos;
  pair<int,int>resultado;
  pos.first = pos.second = 0;


  bool entrada = false;
  for( int i=0; i<v.size() && !entrada; i++ ){
    for( int j=0; j<v[i].size() && !entrada; j++ ){

      if( v[i][j] == 'E')
        entrada = true;
        pos.first = i;
        pos.second = j;
        pisada[i][j] = true;

    }
  }
  resultado.first = pos.first;
  resultado.second = pos.second;

  pila.push(pos);

  bool encontrado = false;
  bool sincamino = true;
  bool cambiodecasilla = false;

  while( !encontrado ){

    for( int i=pos.first-1; i<=pos.first+1 && !cambiodecasilla; i++ ){
      for( int j=pos.second-1; j<=pos.second+1 && !cambiodecasilla; j++ ){

        if( i >= 0 && j >= 0 && (i == pos.first || j == pos.second ) && !pisada[i][j] ){

          if( v[i][j] == '0' ){
            sincamino = false;
            pos.first = i;
            pos.second = j;
            pila.push(pos);
            pisada[i][j] = true;
            cambiodecasilla = true;
          }
          if( v[i][j] == 'S'){
            resultado.first = i;
            resultado.second = j;
            sincamino = false;
            encontrado = true;
            cambiodecasilla = true;
          }

        }
      }
    }
    cambiodecasilla = false;
    if( sincamino ){
      pila.pop();
      pos = pila.top();
      sincamino = false;
    }
    sincamino = true;


  }

  return resultado;

}


int main(){

  vector<vector<char> > prueba(5,vector<char>(5));
  prueba[0][0] = '1';
  prueba[0][1] = '0';
  prueba[0][2] = 'E';
  prueba[0][3] = '0';
  prueba[0][4] = '0';
  prueba[1][0] = '0';
  prueba[1][1] = '0';
  prueba[1][2] = '1';
  prueba[1][3] = '1';
  prueba[1][4] = '0';
  prueba[2][0] = '1';
  prueba[2][1] = '1';
  prueba[2][2] = '0';
  prueba[2][3] = '0';
  prueba[2][4] = '0';
  prueba[3][0] = '1';
  prueba[3][1] = '1';
  prueba[3][2] = '1';
  prueba[3][3] = '0';
  prueba[3][4] = '1';
  prueba[4][0] = 'S';
  prueba[4][1] = '0';
  prueba[4][2] = '0';
  prueba[4][3] = '0';
  prueba[4][4] = '1';


  pair<int,int> res = resolverLaberinto(prueba);
  cout << "Salida en: " << res.first << " " << res.second << endl;
}
