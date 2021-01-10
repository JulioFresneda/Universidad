/*
Creado por: Jose Antonio Ruiz.
						Julio Antonio Fresneda.
						Adrian Pelaez.
						
Practica 4 ED : Iteradores
Universidad de Granada
*/

#ifndef __CONJUNTOIT_H
#define __CONJUNTOIT_H
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;


//! Clase conjunto
 /*! conjunto::conjunto, find, size,
 * Tipos conjunto::value_type, conjunto::size_type
 * Iteradores:iterator, impar_iterator, secure_iterator;
 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::value_type \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto. Es requisito que el tipo conjunto::value_type tenga definidos los operadores operator< y operator= .

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática.

 @todo Implementa esta clase siguiendo la especificación asociada
 */




template <typename T, class CMP>
class conjunto
{
public:
	typedef T value_type;
	typedef unsigned int size_type;

	//Clases de iteradores. Atributos y métodos definidos abajo.
	//@todo Implementa las clases de iteradores.
	class iterator;
	class impar_iterator;
	class secure_iterator;
	//Clases de iteradores constantes.
	//@todo Implementa las clases de iteradores constantes.
	class const_iterator;
	class const_impar_iterator;
	class const_secure_iterator;


	/** @brief constructor primitivo.
	*/
	conjunto( ){}


	/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	conjunto (const conjunto<T,CMP> & d);


	/** @brief busca una entrada en el conjunto
	@param[in] s: entrada  a buscar.
	@return Si existe una entrada en el conjunto con ese valor devuelve el iterador a su posicion, en caso contrario devuelve iterador al final de conjunto
	@post no modifica el conjunto.
	*/
	iterator  find (const value_type & s) ;
	const_iterator  find (const value_type & s) const;



	/** @brief cuenta cuantas entradas coinciden con los parámetros dados.
	@param[in] e entrada.
	@return Como el conjunto de mutaciones no puede tener entradas repetidas, devuelve 1 (si se encuentra la entrada) o 0 (si no se encuentra).
	@post no modifica el conjunto.
	*/

	size_type count (const value_type & e) const;



	/** @brief Inserta una entrada en el conjunto
	@param val entrada a insertar
	@return un par donde el segundo campo vale true si la entrada se ha podido insertar con éxito, esto es, no existe una mutación con igual valor en el conjunto. False en caso contrario.
    El primer campo del par devuelve un iterador al elemento insertado, o end() si no fue posible la insercion
   	@post Si e no esta en el conjunto, el size() sera incrementado en 1.
	*/
	pair<conjunto::iterator,bool> insert (const conjunto::value_type& val);


	/** @brief Borra una entrada en el conjunto .
	Busca la entrada y si la encuentra la borra.

	@param[in] val entrada a borrar.
	@param[in] position itarador que apunta a la  entrada que geremos borrar
	@return devuelve la posicion siguiente al elemento borrado (para la version con iterador) o el numero de elementos borrados
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	iterator  erase (iterator position);
	size_type erase (const value_type& val);


	/** @brief Borra todas las entradas del conjunto, dejandolo vacio.
	@post El conjunto se modifica, quedando vacio.
	*/
	void clear();

	/** @brief numero de entradas en el conjunto
	@post  No se modifica el conjunto.
	@return numero de entradas en el conjunto
	*/
	size_type size() const ;


	/** @brief Chequea si el conjunto esta vacio (size()==0)
	@post  No se modifica el conjunto.
	*/
  	bool empty() const;


	/** @brief operador de asignación
	@param[in] org conjunto a copiar.
	@return Crea y devuelve un conjunto duplicado exacto de org.
	*/
	conjunto & operator=( const conjunto & org);

	/** @brief begin del conjunto
	@return Devuelve un iterador (o iterador constante, respectivamente) al primer elemento del conjunto. Si no existe devuelve end
	*/
	iterator begin ();
	const_iterator cbegin () const;

	/** @brief end del conjunto
	@return Devuelve un iterador (o iterador constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
	*/
	iterator end ();
	const_iterator cend () const;


	/** @brief begin del conjunto
	@return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al primer elemento del conjunto. Si no existe devuelve end
	*/
	secure_iterator sbegin ();
	const_secure_iterator csbegin( ) const;

	/** @brief end del conjunto
	@return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
	*/
	secure_iterator send ();
	const_secure_iterator csend( ) const;

	/** @brief begin del conjunto
	@return Devuelve un iterador impar (o iterador impar constante, respectivamente) al primer elemento (de posición impar) del conjunto. Si no existe devuelve end
	*/
	impar_iterator ibegin();
   	const_impar_iterator cibegin( ) const;

 	/** @brief end del conjunto
	@return Devuelve un iterador impar (o iterador impar constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	*/
 	impar_iterator iend();
  const_impar_iterator ciend( ) const;


	/** @brief busca primer elemento por debajo ('antes', '<') de los parámetros dados.
	@param[in] val entrada.
	@return Devuelve un iterador al primer elemento que cumple que "elemento<e" es falso, esto es, el primer elemento que  es mayor o igual que val
	Si no existe devuelve end
	@post no modifica el conjunto.
	*/
	iterator lower_bound (const value_type& val);
	const_iterator lower_bound (const value_type& val) const;


	/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados.
	@param[in] val entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e", esto es, el primer elemento ESTRICTAMENTE mayor que val
	Si no existe devuelve end
	@post no modifica el conjunto.
	*/
  iterator upper_bound (const value_type& val);
	const_iterator upper_bound (const value_type& val) const;

	/** @brief Devuelve un elemento del conjunto dada una posicion
	@param i: posicion a mostrar
	@pre la posicion debe entar dentro del rango del conjunto
	@return El elemento correspondiente a la posicion indicada
	*/
	T getElemento(int i) const;

	class iterator{
		public:
			/**
			@brief Constructor por defecto
			*/
			iterator(){}
			/**
			@brief Constructor de copia
			@param x: iterador para copiar su contenido
			*/
			iterator(const iterator &  x){
				*this = x;
			}
			/**
			@brief Transforma secure_iterator en iterator
			@param x: secure_iterator a transformar en iterator
			*/
			iterator(const secure_iterator &  x){ // Transforma secure_iterator en iterator;
				*this = x;
			}
			//Devolver el objeto al que apunta

			/**
			@brief Devuelve el contenido al que apunta el iterador
			@return elemto del vector al que apunta el iterador
			*/
			const T & operator*(){
				return *it;
			}
			/**
			@brief Adelanta una posicion el iterador
			@return la referencia al propio iterador
			*/
			iterator & operator++(){
				++it;
				return *this;
			}

			/**
			@brief Adelanta el iterador i posiciones
			@param i: numero de posiciones a adelantar
			@return la referencia al propio iterador
			*/
			iterator operator++(int i){
				it+=i;
				return *this;
			}

			/**
			@brief Atrasa el iterador una posicion
			@return la referencia al propio iterador
			*/
			iterator & operator--(){
				--it;
				return *this;
			}

			/**
			@brief Atrasa el iterador i posiciones
			@param i: numero de posicones a atrasar el iterador
			@return la referencia al propio iterador
			*/
			iterator operator--(int i){
				it-=i;
				return *this;
			}

			/**
			@brief Compara si dos iteradores apuntan al mismo sitio
			@param x: iterador a comparar con el actual
			@return true si son iguales o false en caso contrario
			*/
			bool operator==(const iterator & x) const {
				return (elvector == x.elvector && it == x.it);
			}
			/**
			@brief Compara si dos iteradores no apuntan al mismo elemento
			@param x: iterador a comparar con el actual
			@return true si los iteradores son distintos, false en caso contrario
			*/
			bool operator!=(const iterator & x) const {
				return (elvector != x.elvector || it != x.it);
			}
			/**
			@brief Iguala dos iteradores
			@param x: iterador del que copiaremos la informacion
			@return la referencia al propio iterador
			*/
			iterator & operator=(const iterator & x){
				if( this != &x ){
					it = x.it;
					elvector = x.elvector;
				}
				return *this;
			}
		public:
			friend class conjunto<T,CMP>;
			typename vector<T>::iterator it;
			vector<T> *elvector;
		};

		class const_iterator{
			public:

				/**
				@brief Constructor por defecto
				*/
				const_iterator(){}
				/**
				@brief Constructor de copia
				@param x: iterador para copiar su contenido
				*/
				const_iterator(const const_iterator &  x){
					*this = x;
				}
				/**
				@brief Transforma secure_iterator en const_iterator
				@param x: secure_iterator a transformar en const_iterator
				*/
				const_iterator(const const_secure_iterator &  x){ // Transforma secure_iterator en iterator;
					*this = x;
				}
				//Devolver el objeto al que apunta

				/**
				@brief Devuelve el contenido al que apunta el iterador
				@return elemto del vector al que apunta el iterador
				*/
				const T & operator*(){
					return *it;
				}
				/**
				@brief Adelanta una posicion el iterador
				@return la referencia al propio iterador
				*/
				const_iterator & operator++(){
					++it;
					return this;
				}

				/**
				@brief Adelanta el iterador i posiciones
				@param i: numero de posiciones a adelantar
				@return la referencia al propio iterador
				*/
				const_iterator operator++(int i){
					it+=i;
					return *this;
				}

				/**
				@brief Atrasa el iterador una posicion
				@return la referencia al propio iterador
				*/
				const_iterator & operator--(){
					--it;
					return this;
				}

				/**
				@brief Atrasa el iterador i posiciones
				@param i: numero de posicones a atrasar el iterador
				@return la referencia al propio iterador
				*/
				const_iterator operator--(int i){
					it-=i;
					return *this;
				}

				/**
				@brief Compara si dos iteradores apuntan al mismo sitio
				@param x: iterador a comparar con el actual
				@return true si son iguales o false en caso contrario
				*/
				bool operator==(const const_iterator & x) const {
					return (elvector == x.elvector && it == x.it);
				}
				/**
				@brief Compara si dos iteradores no apuntan al mismo elemento
				@param x: iterador a comparar con el actual
				@return true si los iteradores son distintos, false en caso contrario
				*/
				bool operator!=(const const_iterator & x) const {
					return (elvector != x.elvector || it != x.it);
				}
				/**
				@brief Iguala dos iteradores
				@param x: iterador del que copiaremos la informacion
				@return la referencia al propio iterador
				*/
				const_iterator & operator=(const const_iterator & x){
					if( *this != &x ){
						it = x.it;
						elvector = x.elvector;
					}
					return this;
				}
			public:
				friend class conjunto<T,CMP>;
				typename vector<T>::const_iterator it;
				vector<T> *elvector;
			};

	class secure_iterator{
		public:
			/**
			@brief Constructor por defecto
			*/
			secure_iterator(){}

			/**
			@brief Constructor de copia
			@param x: iterador seguro para copiar su contenido
			*/
			secure_iterator(const secure_iterator &  x){
				*this = x;
			}

			/**
			@brief Devuelve el contenido al que apunta al iterador, de forma segura
			@return elemento del vector al que apunta el iterador, siempre y cuando el iterador apunte dentro del vector
			*/
			const T & operator*(){																			// Devuelve el contenido al que apunta it
				bool posicion_correcta = false;
				if( it > elvector->begin() && it < elvector->end() )
						posicion_correcta = true;
				assert(posicion_correcta);
				return *it;
			}

			/**
				@brief Adelanta una posicion el iterador, siempre que no se salga del vector
				@return la referencia al propio iterador
				*/
			secure_iterator & operator++(){															// Operador ++
				bool posicion_correcta = false;
				if( it < elvector.end() ){
					posicion_correcta = true;
				assert(posicion_correcta);
				++it;
				return this;
				}
			}

			/**
				@brief Adelanta el iterador i posiciones, siempre que no se salga del vector
				@param i: numero de posiciones a adelantar
				@return la referencia al propio iterador
				*/
			secure_iterator operator++(int i){													// Adelanta i posiciones it de forma segura
				bool posicion_correcta = false;;
				if( it + i < elvector->end() ){
					posicion_correcta = true;
				}
				assert(posicion_correcta);
				it += i;
				return *this;

			}

			/**
				@brief Atrasa el iterador una posicion, siempre que la posicion sea correcta
				@return la referencia al propio iterador
				*/
			secure_iterator & operator--(){															// Operador --
				bool posicion_correcta = false;
				if( it > elvector->begin() ){
						posicion_correcta = true;
				}
				assert(posicion_correcta);
				--it;
				return *this;
			}

			/**
				@brief Atrasa el iterador i posiciones, siempre que no se salga del vector
				@param i: numero de posicones a atrasar el iterador
				@return la referencia al propio iterador
				*/
			secure_iterator operator--(int i){													// Retrasa i posiciones it de forma segura
				bool posicion_correcta = false;
				if( it - i > elvector->begin() ){
					posicion_correcta = true;
				}
				assert(posicion_correcta);
				it -= i;
				return *this;
   		}

			/**
				@brief Compara si dos iteradores apuntan al mismo sitio
				@param x: iterador a comparar con el actual
				@return true si son iguales o false en caso contrario
				*/
			bool operator==(const secure_iterator & x) const {					// Operador ==
				return ( ( it == x.it ) && ( elvector == x.elvector ) ) ;
			}

			/**
				@brief Compara si dos iteradores no apuntan al mismo elemento
				@param x: iterador a comparar con el actual
				@return true si los iteradores son distintos, false en caso contrario
				*/
			bool operator!=(const secure_iterator & x) const {					// Operador !=
				return ( !( it == x.it ) && ( elvector == x.elvector ) ) ;
			}

			/**
			@brief Iguala dos iteradores
			@param x: iterador del que copiaremos la informacion
			@return la referencia al propio iterador
			*/
			secure_iterator & operator=(const secure_iterator & x){			// Operador de asignación =
				if( this != &x ){
					it = x.it;
					elvector = x.elvector;
				}
				return *this;
			}

		public:
			friend class conjunto<T,CMP>;
			typename vector<T>::iterator it;
			vector<T> *elvector;
		};

		class const_secure_iterator{
			public:

				/**
				@brief Constructor por defecto
				*/
				const_secure_iterator(){}

				/**
				@brief Constructor de copia
				@param x: iterador para copiar su contenido
				*/																			// Constructor por defecto
				const_secure_iterator(const const_secure_iterator &  x){								// Constructor de copia
					*this = x;
				}

				/**
				@brief Devuelve el contenido al que apunta el iterador, siempre que el iterador apunte dentro del vector
				@return elemto del vector al que apunta el iterador
				*/
				const T & operator*(){																			// Devuelve el contenido al que apunta it
					bool posicion_correcta = false;
					if( it > elvector->begin() && it < elvector->end() )
							posicion_correcta = true;
					assert(posicion_correcta);
					return *it;
				}

				/**
				@brief Adelanta una posicion el iterador, siempre que no se salga del vector
				@return la referencia al propio iterador
				*/
				secure_iterator & operator++(){															// Operador ++
					bool posicion_correcta = false;
					if( it < elvector->end() ){
						posicion_correcta = true;
					}
					assert(posicion_correcta);
					return this;
				}

				/**
				@brief Adelanta el iterador i posiciones, siempre que no se salga del vector
				@param i: numero de posiciones a adelantar
				@return la referencia al propio iterador
				*/
				const_secure_iterator operator++(int i){													// Adelanta i posiciones it de forma segura
					bool posicion_correcta = false;
					if( it + i < elvector->end() ){
						posicion_correcta = true;
					}
					assert(posicion_correcta);
					it+=i;
					return *this;

				}

				/**
				@brief Atrasa el iterador una posicion, siempre que la posicion sea correcta
				@return la referencia al propio iterador
				*/
				const_secure_iterator & operator--(){															// Operador --
					bool posicion_correcta = false;
					if( it > elvector->begin() ){
							posicion_correcta = true;
					}
					assert(posicion_correcta);
					--it;
					return this;
				}

				/**
				@brief Atrasa el iterador i posiciones, siempre que no se salga del vector
				@param i: numero de posicones a atrasar el iterador
				@return la referencia al propio iterador
				*/
				const_secure_iterator operator--(int i){													// Retrasa i posiciones it de forma segura
					bool posicion_correcta = false;
					if( it - i > elvector->begin() ){
						posicion_correcta = true;
					}
					assert(posicion_correcta);
					it-=i;
					return *this;
				}

				/**
				@brief Compara si dos iteradores apuntan al mismo sitio
				@param x: iterador a comparar con el actual
				@return true si son iguales o false en caso contrario
				*/
				bool operator==(const const_secure_iterator & x) const {					// Operador ==
					return ( ( it == x.it ) && ( elvector == x.elvector ) ) ;
				}

				/**
				@brief Compara si dos iteradores no apuntan al mismo elemento
				@param x: iterador a comparar con el actual
				@return true si los iteradores son distintos, false en caso contrario
				*/
				bool operator!=(const const_secure_iterator & x) const {					// Operador !=
					return ( !( it == x.it ) && ( elvector == x.elvector ) ) ;
				}

				/**
				@brief Iguala dos iteradores
				@param x: iterador del que copiaremos la informacion
				@return la referencia al propio iterador
				*/
				const_secure_iterator & operator=(const secure_iterator & x){			// Operador de asignación =
					if( *this != &x ){
						it = x.it;
						elvector = x.elvector;
					}
					return this;
				}

			public:
				friend class conjunto<T,CMP>;
				typename vector<T>::const_iterator it;
				vector<T> *elvector;
			};


	class impar_iterator{
		public:
			/**
			@brief Constructor por defecto
			*/
			impar_iterator(){}

			/**
			@brief Constructor de copia
			@param x: parametro para copiar su contenido
			*/
			impar_iterator(const impar_iterator &  x){
				*this = x;
			}

			/**
			@brief Operador que devuelve el contenido del objeto apuntado por it
			@return elemento apuntado por it
			*/
			const T & operator*(){
				return *it;
			}

			/**
			@brief operator que aumenta la posicion del iterador hasta la sieguiente posicion impar
			@return impar_iterator que apunta a la siquiente posicion calculada
			*/
			impar_iterator & operator++(){
				it+=2;
				return *this;
			}

			/**
			@brief operador que aumenta la posicion del it un numero i, si i es par
			@param i: posiciones que debe avanzar el it
			@return impar_iterator que apunta a la siguiente posicion calculada
			*/
			impar_iterator operator++(int i){
				if(i%2 == 0)
					it+=i;
				return *this;
			}

			/**
			@brief nos dice si dos impar_iterator son iguales
			@param x: impar_iterator con el que se compara
			@return true si son iguales, false en caso contrario
			*/
			bool operator==(const impar_iterator & x) const{
				return ( ( it == x.it ) && ( elvector == x.elvector ) ) ;
			}

			/**
			@brief nos dice si dos impar_iterator son diferentes
			@param x: impar_iterator con el que se compara
			@return true si son diferentes, false enm caso contrario
			*/
			bool operator!=(const impar_iterator & x) const{
				return ( ( it != x.it ) || ( elvector != x.elvector ) ) ;
			}

			/**
			@brief operador que asigna un iterador a otro
			@param x: impar_iterator que va a ser asignado
			@return impar_iterator con los valores del parametro
			*/
			impar_iterator & operator=(const impar_iterator & x){
				if(*this != x){
					it = x.it;
					elvector = x.elvector;
				}
				return *this;

			}
		public:
			friend class conjunto<T,CMP>;
			typename vector<T>::iterator it;
			vector<T> *elvector;
		};


		class const_impar_iterator{
			public:
				/**
				@brief Constructor por defecto
				*/
				const_impar_iterator(){}

				/**
				@brief Constructor de copia
				@param x: parametro para copiar su contenido
				*/
				const_impar_iterator(const const_impar_iterator &  x){
					*this = x;
				}

				/**
				@brief Operador que devuelve el contenido del objeto apuntado por it
				@return elemento apuntado por it
				*/
				const T & operator*(){
					return *it;
				}

				/**
				@brief operator que aumenta la posicion del iterador hasta la sieguiente posicion impar
				@return const_impar_iterator a la siguiente posición calculada
				*/
				const_impar_iterator & operator++(){
					it+=2;
					return this;
				}

				/**
				@brief operador que aumenta la posicion del it un numero i, si i es par
				@param i: posiciones que debe avanzar el it
				@return const_impar_iterator a la siguiente posicion calculada
				*/
				const_impar_iterator operator++(int i){
					if(i%2 == 0)
						it+=i;
					return *this;
				}

				/**
				@brief nos dice si dos const_impar_iterator son iguales
				@param x: const_impar_iterator con el que se compara
				@return true si son iguales, false en caso contrario
				*/
				bool operator==(const const_impar_iterator & x) const{
					return ( ( it == x.it ) && ( elvector == x.elvector ) ) ;
				}

				/**
				@brief nos dice si dos const_impar_iterator son diferentes
				@param x: const_impar_iterator con el que se compara
				@return true si son diferentes, false en caso contrario
				*/
				bool operator!=(const const_impar_iterator & x) const{
					return ( ( it != x.it ) || ( elvector != x.elvector ) ) ;
				}

				/**
				@brief operador que asigna un iterador a otro
				@param x: const_impar_iterator que va a ser asignado
				@return const_impar_iterator con los valores del parametro
				*/
				const_impar_iterator & operator=(const const_impar_iterator & x){
					if(*this != x){
						it = x.it;
						elvector = x.elvector;
					}
					return this;

				}
			public:
				friend class conjunto<T,CMP>;
				typename vector<T>::const_iterator it;
				vector<T> *elvector;
			};

private:
	friend class impar_iterator;
	friend class secure_iterator;
	friend class iterator;
	vector<value_type> vm; // vector que almacena los elementos del conjunto
	CMP comp; // criterio para guiar la ordenacion



	/** @brief Chequea el Invariante de la representacion
	    @return true si el invariante es correcto, falso en caso contrario
	*/
	bool cheq_rep( ) const;

};

/** @brief imprime todas las entradas del conjunto
@post No se modifica el conjunto.
Implementar tambien esta funcion
	*/
	template<typename T,typename CMP>
	ostream& operator<< ( ostream &sal, const conjunto<T,CMP> &con);

#include "conjunto.hxx"

#endif
