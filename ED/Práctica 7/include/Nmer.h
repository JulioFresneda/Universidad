
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <string>
#include <set>

using namespace std;


/** @brief Criterio de ordenación creciente según frecuencia
*/
class OrdenCre{
public:
  bool operator()(const pair<string,int> &p1, const pair<string,int> &p2){
    if( p1.second != p2.second )
      return p1.second <= p2.second;
    else return p1.first.size() <= p2.first.size();
  }
};

class OrdenDecre{
public:
  bool operator()(const pair<string,int> &p1, const pair<string,int> &p2){
    if( p1.second != p2.second )
      return p1.second >= p2.second;
    else return p1.first.size() >= p2.first.size();
  }
};

class Nmer {
public:
  typedef unsigned int size_type;

  /** @brief Constructor primitivo .
      Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
  Nmer();

  /** @brief Constructor de copia
  */
  Nmer( const Nmer &a );

  /** @brief obtiene los Nmers a partir de una secuencia ADN
   * @param tama tamaño de la secuencia ADN
   *
   * @param adn secuencia ADN
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   */
  void sequenceADN( unsigned int tama, const string & adn );

  /** @brief obtiene un set con las secuencias cuya frecuencia sea menor o igual a t no prefijo
   * @param frecuencia máxima
   *
   * @return set de pair<cadena,frecuencia>
   */
  set<pair<string,int>,OrdenCre> rareNmer( int t );

  /** @brief función auxiliar para rareNmer
   */
  void rareAux( const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenCre> &s, int t );

  /** @brief obtiene un set con las secuencias cuya frecuencia sea mayor que t no prefijo
   * @param t frecuencia máxima
   *
   * @return set de pair<cadena,frecuencia>
   */
  set<pair<string,int>,OrdenDecre> commonNmer( int t );
  
  /** @brief fución auxiliar para commonNmer
   */
  void commonAux( const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenDecre> &s, int t );


  /** @brief función que devuelve los Nmers de una determinada longitud
   * @param l longitud
   * @return set con los Nmers de la longitud indicada
   */
  set <pair<string,int>,OrdenCre>level( int l );

  /** @brief función auxiliar
   */
  void levelAux( const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenCre> &s, int level );

  /** @brief inserta cadena en ktree
   * @param cadena cadena a insertar
   *
   */
  void insertar_cadena( const string &cadena );

  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   * La cadena original viene descrita en el fichero serializado
   */
  bool loadSerialized(const string & nombre_fichero);


  /** @brief Imprime los Nmers
   * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
   */
  void list_Nmer() const;

  Nmer& operator=( const Nmer a );
  /** @brief Máxima longitud de los Nmers almacenados
   */
   unsigned int length()const;


  /** @brief Número de Nmers almacenados
   */
  size_type size() const;




  /** @brief Devuelve el Nmer (subárbol) asociado a un prefijo
   * @param adn prefijo
   * @return subárbol
   */
  Nmer Prefix(string adn);

 /** @brief aux de Union
  */
 void auxUnion( ktree<pair<char,int>,4>::node &uno, ktree<pair<char,int>,4>::node &dos, ktree<pair<char,int>,4>::node &uni, ktree<pair<char,int>,4> &nmer );

  /** @brief Se devuelve un Nmer donde para cada nodo se computa la suma de las frecuencias en *this y en referencia,
   * @param Nmer referencia
   * @return Nmer con la unión
   */
  Nmer Union( const Nmer reference );

  /** @brief Devuelve true si la cadena adn está representada en el árbol.
   * @param cadena a comprobar
   * @return true si está, false si no lo está
  */
  bool containsString(const string adn) const;

  /** @brief Devuelve true si cada nodo de *this está también representado en reference
   * @param referencia
   * @return booleano
   */
  bool included(const Nmer reference);

  /** @brief Función auxiliar de included
   */
  bool includedAux( const ktree<pair<char,int>,4>::const_node naux, ktree<pair<char,int>,4>::const_node nauxr );

  /** @brief función que calcula la distancia entre dos Nmer
   * @param Nmer
   * @return distancia
   */
  float Distance( const Nmer &otro );

  /** @brief función auxiliar de Distance
   */
  void auxDistance( const ktree<pair<char,int>,4 >::const_node &nodo, set<pair<string,int>,OrdenDecre> &s, string &saux );
private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
   public:
    pair<char,int> operator()( const string & cad) {
	    pair<char,int> salida;
	    salida.first = cad[0];
	    salida.second = std::stoi(cad.substr(1));
	    return salida;
    }
  };

   /** @brief Functor para convertir un pair<char,int> en un string
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second);
       return salida;
     }
  };


};



#endif
