/*  17. Implementa la función intercalar(vector<T> &v, vector<pair<int, T> > pos)
que inserta el segundo elemento de cada par de pos en v en los lugares indicados por el primer
elemento de cada par de pos */

// Julio Fresneda

#include <vector>
#include <iostream>
using namespace std;

template<typename T>
void intercalar( vector<T> &v, vector<pair<int, T> > pos ){
  typename vector<T>::iterator posv;
  for( typename vector<pair<int, T> >::iterator it = pos.begin(); it != pos.end(); ++it ){
    posv = v.begin();
    if( it->first < v.size() && it->first >= 0 )
      v.insert(posv+it->first,it->second);
    else if( it->first >= v.size() ) v.push_back(it->second);
  }
}

int main(){
  vector<int> prueba = {1,2,3,4};

  pair<int,int> x;
  x.first = 0;
  x.second = 9;

  pair<int,int> y;
  y.first = 2;
  y.second = 8;

  pair<int,int> z;
  z.first = 6;
  z.second = 7;

  vector<pair<int, int> > interc = {x,y,z};

  cout << endl;
  for( int i=0; i<4; i++ ){
    cout << prueba.at(i) << " ";
  }

  intercalar(prueba,interc);

  cout << endl;
  for( unsigned int i=0; i<prueba.size(); i++ ){
    cout << prueba.at(i) << " ";
  }
  cout << endl;

}
