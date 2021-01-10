/*  15. Una forma eficiente de guardar secuencias de valores iguales consiste en guardar cada uno de los
valores seguido del número de veces que aparece en la secuencia. Por ejemplo,
<1,1,1,2,2,2,2,2,2,7,7,7,7,7,12,1,1,5,5>
< (1,3), (2,6), (7,5), (12,1), (1,2), (5,2) >
Implementa las funciones:
list<pair<T, int> > comprimir(const list<T> &l)+
list<T> descomprimir(const list<pair<T, int> > &lc)
que permitan convertir entre ambas representaciones.  */

// Julio Fresneda

#include <iostream>
#include <list>
using namespace std;

template<typename T>
list<pair<T,int> > comprimir( const list<T> &l ){
  list<pair<T,int> > salida;
  bool repitiendo = false;
  pair<T,int> aux;
  T t;

  for( typename list<T>::const_iterator pos = l.cbegin(); pos != l.cend(); ++pos ){

    if( pos != l.cbegin() ){
      if( t == *pos ) repitiendo = true;
      else repitiendo = false;
    }
    t = *pos;

    if( repitiendo ) salida.back().second++;
    else{
      aux.first = *pos;
      aux.second = 1;
      salida.push_back(aux);
    }
  }
  return salida;
}

template<typename T>
list<T> descomprimir( const list<pair<T,int> > &l ){
  list<T> salida;

  for( typename list<pair<T,int> >::const_iterator pos = l.cbegin(); pos != l.cend(); ++pos ){
    for( int i=0; i<pos->second; i++ ){
      salida.push_back(pos->first);
    }
  }

  return salida;
}

int main(){
  list<pair<int,int> > prueba;
  list<int> lista;

  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(2);
  lista.push_back(3);
  lista.push_back(3);
  lista.push_back(3);
  lista.push_back(1);
  lista.push_back(1);
  lista.push_back(0);


  for( list<int>::iterator pos = lista.begin(); pos != lista.end(); ++pos ){
    cout << *pos << " ";
  }

  prueba = comprimir(lista);
  cout << endl;

  for( list<pair<int,int> >::iterator pos = prueba.begin(); pos != prueba.end(); ++pos ){
    cout << pos->first << " (" << pos->second << " veces) ";
  }

  cout << endl;

  lista = descomprimir(prueba);
  for( list<int>::iterator pos = lista.begin(); pos != lista.end(); ++pos ){
    cout << *pos << " ";
  }
  cout << endl;


}
