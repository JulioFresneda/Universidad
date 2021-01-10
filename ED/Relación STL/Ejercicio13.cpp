/*  14. Una variante del vector disperso es aquella en la que se puede definir cual es el valor nulo. Modifica
la clase anterior de forma que se pueda definir cual es el valor nulo al crear un objeto. Implementa
también cambiar_nulo(const T &n)  */

// Julio Fresneda

// Compilar con -std=c++11

#include <vector>
#include <list>
#include <iostream>
using namespace std;


template <typename T>
class vdisperso {
  public:
    vdisperso( const vector<T> &v ){
      int i=0;
      pair<int, T> x;
      for( typename vector<T>::const_iterator pos = v.cbegin(); pos != v.cend(); ++pos, i++ ){
        if( *pos != NULL ){
          x.first = i;
          x.second = *pos;
          coefs.push_back(x);
        }
        if( pos == --v.cend() ){
          x.first = i;
          x.second = NULL;
          coefs.push_back(x);
        }

      }
    }

    void asignar_coeficiente(int i, const T &x){
      bool insertado = false;
      for( typename list< pair<int, T> >::iterator pos = coefs.begin(); pos != coefs.end() && !insertado; ++pos ){
        if( *pos->first > i ){
          coefs.insert(pos,(i,x));
          insertado = true;
        }
      }

    }

    vector<T> convertir() const{
      vector<T> v;
      typename list<pair<int,T>>::const_iterator pos = coefs.begin();
      for( int i=0; i<=(coefs.back()).first; i++ ){
        if( i == pos->first ) {
         v.push_back(pos->second);
         ++pos;
       }
        else v.push_back(NULL);
      }
      return v;
    }

    void mostrar_lista(){
      for( typename list<pair<int,T>>::iterator pos = coefs.begin(); pos != coefs.end(); ++pos ){
        cout << pos->second << " (" << pos->first << ") ";
      }
    }

  private:
    list< pair<int, T> > coefs;
    int n;

};


int main(){
  vector<int> prueba;
  prueba.push_back(NULL);
  prueba.push_back(NULL);
  prueba.push_back(1);
  prueba.push_back(NULL);
  prueba.push_back(5);
  prueba.push_back(3);
  prueba.push_back(NULL);

  cout << endl;
  for( vector<int>::iterator pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << *pos <<" ";
  }

  vdisperso<int> pruebavd(prueba);

  cout << endl;
  pruebavd.mostrar_lista();

  prueba = pruebavd.convertir();

  cout << endl;
  for( vector<int>::iterator pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << *pos <<" ";
  }
  cout << endl;


}
