/* 	##############################################################################################################################################

						Práctica 6 - Julio A. Fresneda García - Estructura de Datos - Última versión: 26/13/16
						juliofresnedag@correo.ugr.es - juliofgx17@gmail.com - github.com/juliofg17

						No se ha usado material de otros compañeros para el desarrollo de esta práctica

		############################################################################################################################################  */

#include <iostream>
#include <set>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <queue>
#include "mutacion.h"
#include "enfermedad.h"


using namespace std;


typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

/**
 * @brief Functor para ordenar las mutaciones
 * @return Un bool
*/
struct ProbMutaciones{
	bool operator()( const mutacion &m1, const mutacion &m2 ){
		return ( (1-(m1.getCaf()).at(0)) >= (1-(m2.getCaf()).at(0) ));
	}
};

/**
 * @brief Clase clinvar
 * Clase para manejar las mutaciones y enfermedades de una base de datos
*/
class clinvar{
public:

	/**
	 * @brief Iterador sobre mutaciones en orden creciente de cromosoma/posicion
	*/
	class iterator {
		private:
				friend class clinvar;
				set<mutacion>::iterator it;
		public:
				const mutacion & operator*(){  //const - no se puede modificar la mutacion y alterar el orden del set
					return *it;
				}
				iterator operator++(int){
					++it;
					return *this;
				}
				iterator operator--(int){
					--it;
					return *this;
				}
				void operator+( int k ){
					for( int i=0; i<k; i++ )
						++it;
				}
				void operator-( int k ){
					for( int i=0; i<k; i++ )
						--it;
				}

				bool operator==( iterator it2 ){
					return (*it == *(it2.it));
				}

				bool operator==( set<mutacion>::iterator it2 ){
					return (*it == *it2);
				}

				bool operator!=( iterator it2 ){
					return !(*it == *(it2.it));
				}

				bool operator!=( set<mutacion>::iterator it2 ){
					return !(*it == *it2);
				}


				iterator& operator=( const iterator &it2 ){
					this->it = it2.it;
					return *this;
				}

				const iterator & operator+=( const int &k ){
					for( int i=0; i<k; i++ )
						++it;
					return *this;
				}

				const iterator & operator-=( const int &k ){
					for( int i=0; i<k; i++ )
						--it;
					return *this;
				}


	};

	/**
	 * @brief Iterador sobre enfermedades
	*/
	// Nos vale utilizar el iterador del map
	typedef map<IDenf, enfermedad>::iterator enfermedad_iterator;


	/**
	 * @brief Iterador sobre mutaciones considerando el orden creciente del ID del gen
	*/
	class gen_iterator {
		public:
			const mutacion & operator*(){
				return **itlist;
			}
			gen_iterator operator++(int){
				++itlist;
				if( itlist == itmap->second.end() ){
					++itmap;
					itlist = itmap->second.begin();
				}
				return *this;
			}
			gen_iterator operator--(int){
				if( itlist == itmap->second.begin() ){
					--itmap;
					itlist = itmap->second.end();
				}
				--itlist;
				return *this;
			}
			const gen_iterator & operator+( const int &k ){
				for( int i=0; i<k; i++ ){
					(*this)++;
				}
				return *this;
			}
			const gen_iterator & operator-( const int &k ){
				for( int i=0; i<k; i++ ){
					(*this)--;
				}
				return *this;
			}
			gen_iterator operator=( gen_iterator git ){
				this->itmap = git.itmap;
				this->itlist = git.itlist;
				return *this;
			}

			const gen_iterator & operator+=( int k ){
				for( int i=0; i<k; i++ ){
					(*this)++;
				}
				return *this;
			}
			const gen_iterator & operator-=( int k ){
				for( int i=0; i<k; i++ ){
					(*this)--;
				}
				return *this;
			}
			private:
			friend class clinvar;
			map<IDgen, list< set<mutacion>::iterator> >::iterator itmap;
			list<set<mutacion>::iterator>::iterator itlist;
			clinvar *ptrclinvar;
	};

  /**
	 * @brief Método para cargar una base de datos desde un fichero externo al programa
	 * @param nombreDB Nombre del archivo a abrir
	*/
	void load (string nombreDB){
		ifstream fe;
		string cadena;

		cout << "Abrimos "<< nombreDB << endl;

		fe.open(nombreDB.c_str(), ifstream::in);

		if (fe.fail()){
			cerr << "Error al abrir el fichero " << nombreDB << endl;
		}
		else {

		 	//leo la cabecera del fichero (líneas que comienzan con #)
		 	do{
			 	getline(fe,cadena,'\n');
		 	}while (cadena.find("#")==0 && !fe.eof());

		 	//leo la tabla de mutaciones, una línea cada vez
		 	while ( !fe.eof() ){
				 	//cout << "leo:: "<< cadena << endl;

				 	// Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
				 	mutacion mut = mutacion(cadena);

				 	// Insertar mutación en el conjunto

					// Insertar en mutDB
				 	pair<set<mutacion>::iterator,bool> par = mutDB.insert(mut);

					// Insertar en IDm_map
					pair<IDmut,set<mutacion>::iterator> par2;
					par2.first = (par.first)->getID();
					par2.second = par.first;
					IDm_map.insert(par2);

					// Insertar en gen_map

					// Este for recorre todos los genes de la mutación
					for( int i=0; i < mut.getGenes().size(); i++ ){
						// Este iterador señala al elemento de gen_map cuyo IDgen coincide con el gen de mut del momento
						map<IDgen, list< set<mutacion>::iterator> >::iterator it = gen_map.find(mut.getGenes()[i]);
						// Si existe el gen en el gen_map
						if( it != gen_map.end() ){
							bool yaesta = false;
							//Este for comprueba si la mutación está ya en la lista
							for( list< set<mutacion>::iterator>::iterator l = (it->second).begin(); l != (it->second).end(); ++l ){
								if( **l == mut ) yaesta = true;
							}
							// Si no estaba, lo añade
							if( !yaesta ) (it->second).push_front(par.first);
						}
						// Si no existía el gen en gen_map
						else{
							// Creo una nueva lista donde añado el iterador de mut
							list< set<mutacion>::iterator> l;
							l.push_front(par.first);
							// Creo un nuevo par para añadir a gen_map con IDgen y la lista
							pair<IDgen, list< set<mutacion>::iterator> > p;
							p.first = mut.getGenes()[i];
							p.second = l;
							gen_map.insert(p);

						}
					}

					// Insertar en EnfDB

					// Este for recorre todas las enfermedades de mut
					for( int i=0; i<mut.getEnfermedades().size(); i++ ){

						// Añado a EnfDB las enfermedades de la mutación, junto a IDenf
						EnfDB.insert(pair<string,enfermedad>(mut.getEnfermedades()[i].getID(),mut.getEnfermedades()[i]));
					}

					// Insertar en IDenf_mmap
					for( int i=0; i<mut.getEnfermedades().size(); i++ ){
						// Insertamos por cada enfermedad de la mutación, un par con el IDenf y el iterador de mut
						IDenf_mmap.insert(pair<string,set<mutacion>::iterator>(mut.getEnfermedades()[i].getID(),par.first));
					}


				 	getline(fe,cadena,'\n');
		 	}
		 	fe.close();

	 	} // else
	 	fe.close();
	}	// Lee los datos de la base de datos clinvar

	/**
	 * @brief Método para insertar una mutación en el objeto de tipo clinvar
	 * @param x Objeto de tipo mutación
	*/
	void insert (const mutacion & x){
		// Insertar mutación en el conjunto

	  // Insertar en mutDB
		pair<set<mutacion>::iterator,bool> par;
		par = mutDB.insert(x);

		// Insertar en IDm_map
		pair<IDmut,set<mutacion>::iterator> par2;
		par2.first = (par.first)->getID();
		par2.second = par.first;
		IDm_map.insert(par2);

		// Insertar en gen_map

		// Este for recorre todos los genes de la mutación
		for( int i=0; i < x.getGenes().size(); i++ ){
			// Este iterador señala al elemento de gen_map cuyo IDgen coincide con el gen de mut del momento
			map<IDgen, list< set<mutacion>::iterator> >::iterator it = gen_map.find(x.getGenes()[i]);
			// Si existe el gen en el gen_map
			if( it != gen_map.end() ){
				bool yaesta = false;
				//Este for comprueba si la mutación está ya en la lista
				for( list< set<mutacion>::iterator>::iterator l = (it->second).begin(); l != (it->second).end(); ++l ){
					if( **l == x ) yaesta = true;
				}
				// Si no estaba, lo añade
				if( !yaesta ) (it->second).push_front(par.first);
			}
			// Si no existía el gen en gen_map
			else{
				// Creo una nueva lista donde añado el iterador de mut
				list< set<mutacion>::iterator> l;
				l.push_front(par.first);
				// Creo un nuevo par para añadir a gen_map con IDgen y la lista
				pair<IDgen, list< set<mutacion>::iterator> > p;
				p.first = x.getGenes()[i];
				p.second = l;
				gen_map.insert(p);

			}
		}

		// Insertar en EnfDB

		// Este for recorre todas las enfermedades de mut
		for( int i=0; i<x.getEnfermedades().size(); i++ ){

			// Añado a EnfDB las enfermedades de la mutación, junto a IDenf
			EnfDB.insert(pair<string,enfermedad>(x.getEnfermedades()[i].getID(),x.getEnfermedades()[i]));
		}

		// Insertar en IDenf_mmap
		for( int i=0; i<x.getEnfermedades().size(); i++ ){
			// Insertamos por cada enfermedad de la mutación, un par con el IDenf y el iterador de mut
			IDenf_mmap.insert(pair<string,set<mutacion>::iterator>(x.getEnfermedades()[i].getID(),par.first));
		}
	}

	/**
	 * @brief Método para borrar una mutación de la base de datos del objeto clinvar
	 * @param ID El ID de la mutación a borrar, de tipo string
	 * @return True si se borra la mutación, false en caso contrario
	*/
	bool erase (IDmut ID){
		bool borrado = true;
		// Si no está en IDm_map
		if( IDm_map.find(ID) == IDm_map.end() ) borrado = false;
		else{
			set<mutacion>::iterator mut = IDm_map.find(ID)->second;
			// Borramos la mutación de IDm_map
			IDm_map.erase(ID);

			// Borramos la mutación de gen_map
			map<IDgen, list< set<mutacion>::iterator> >::iterator it_gen_map;
			// Recorremos todos los genes de mut
			for( int i=0; i<mut->getGenes().size(); i++ ){

				// Encontramos el gen en el gen_map
				it_gen_map = gen_map.find(mut->getGenes()[i]);

				// Recorremos la lista de mutaciones asociadas al gen anterior
				bool b = false;
				for( list< set<mutacion>::iterator>::iterator it = it_gen_map->second.begin(); !b && it != it_gen_map->second.end(); ++it ){
					// Si encontramos la mutación en la lista, se borra

					if( **it == *mut ){

					  (it_gen_map->second).erase(it);
						b = true;
					}
				}

			}

			// Borramos la mutación de IDenf_mmap;
			pair<multimap<IDenf,set<mutacion>::iterator>::iterator,multimap<IDenf,set<mutacion>::iterator>::iterator> par4;
			// Recorremos las enfermedades de la mutación
			for( int i=0; i<mut->getEnfermedades().size(); i++ ){
				// Obtenemos los iteradores que señalan al principio y fin de la parte del mmap que contiene keys iguales al IDenf
				par4 = IDenf_mmap.equal_range(mut->getEnfermedades()[i].getID());
				// Se recorre el rango anterior descrito, y si algún elemento coincide con la mutación, se borra
				for( multimap<IDenf,set<mutacion>::iterator>::iterator it = par4.first; it != par4.second; ++it ){
					if( *(it->second) == *mut ) IDenf_mmap.erase(it);
				}
			}
		}

		return borrado;
	}

	/**
	 * @brief Método que busca una mutación de la base de datos del objeto clinvar
	 * @param ID El ID de la mutación a buscar, de tipo string
	 * @return Iterador, el cual señala a la mutación correspondiente
	*/
	iterator find_Mut (IDmut ID){
		iterator ite;
		unordered_map<IDmut,set<mutacion>::iterator>::iterator it = IDm_map.find(ID);
		if( it == IDm_map.end() ) ite.it = mutDB.end();
		else ite.it = it->second;
		return ite;

	}

	/**
	 * @brief Método que busca una enfermedad de la base de datos del objeto clinvar
	 * @param ID El ID de la enfermedad a buscar, de tipo string
	 * @return Enfermedad_iterator, el cual señala a la enfermedad correspondiente
	*/
	enfermedad_iterator find_Enf(IDenf ID){
		return EnfDB.find(ID);
	}

	/**
	 * @brief Método que devuelve todas las enfermedades asociadas a una mutación
	 * @param mut Objeto de tipo mutación
	 * @return Contenedor tipo vector con las enfermedades
	*/
	vector<enfermedad> getEnfermedades(mutacion & mut){
			return mut.getEnfermedades();
	}

	/**
	 * @brief Método que encuentra todas las enfermedades cuyo nombre contiene una palabra clave
	 * @param keyword Palabra clave
	 * @return Contenedor de tipo lista con los ID de todas las enfermedades
	*/
	list<IDenf> getEnfermedades(string keyword){
		list<IDenf> l;
		for( enfermedad_iterator eit = EnfDB.begin(); eit != EnfDB.end(); ++eit ){
			if( (eit->second).nameContains(keyword) ) l.push_front(eit->first);
		}
		return l;
	}

	/**
	 * @brief Método que encuentra todas las mutaciones que pueden dar lugar a una enfermedad determinada
	 * @param ID ID de la enfermedad, de tipo string
	 * @return Contenedor de tipo set con todas las IDs de las mutaciones
	*/
	set<IDmut> getMutacionesEnf (IDenf ID){
		set<IDmut> s;
		pair<multimap<IDenf,set<mutacion>::iterator>::iterator,multimap<IDenf,set<mutacion>::iterator>::iterator> par = IDenf_mmap.equal_range(ID);
		for( multimap<IDenf,set<mutacion>::iterator>::iterator it = par.first; it != par.second; ++it ){
			s.insert((it->second)->getID());
		}
		return s;
	}

	/**
	 * @brief Método que ecuentra todas las mutaciones que tengan que ver con un gen determinado
	 * @param ID ID del gen, de tipo string
	 * @return Contenedor de tipo set con todas las IDs de las mutaciones
	*/
	set<IDmut> getMutacionesGen (IDgen ID){
		set<IDmut> s;
		map<IDgen, list< set<mutacion>::iterator> >::iterator git = gen_map.find(ID);
		for( list<set<mutacion>::iterator>::iterator it = (git->second).begin(); it != (git->second).end(); ++it ){
			s.insert((*it)->getID());
		}
		return s;
	}

  /**
	 * @brief Método que devuelve las mutaciones que más probablemente se den, que estén relacionadas con enfermedades con una palabra clave
	 * @param k El número de mutaciones con probabilidad más alta
	 * @param keyword Palabra clave
	 * @return Contenedor de tipo set con las mutaciones más probables
	 * @see ProbMutaciones
	*/
	set<mutacion,ProbMutaciones> topKMutaciones (int k, string keyword){
		// Cola con prioridad. La usaremos para mantener en el top la mutación con mayor cof[0] de la cola.
		priority_queue<mutacion,vector<mutacion>,ProbMutaciones> cola;
		// Set de IDs. Lo usaremos para asegurarnos de no repetir mutaciones
		unordered_set<IDmut> IDs;

		// Lista de las enfermedades que contienen keyword
		list<IDenf> lista = this->getEnfermedades(keyword);

		// Recorremos las IDenf
		for( list<IDenf>::iterator itl = lista.begin(); itl != lista.end(); ++itl ){
			// Metemos las enfermedades asociadas al IDenf en un set
			set<IDmut> muts = this->getMutacionesEnf(*itl);
			// Recorremos las mutaciones asociadas a esa enfermedad
			for( set<IDmut>::iterator itm = muts.begin(); itm != muts.end(); ++itm ){
				// Si la mutación no está en IDs, lo inserta
				if( IDs.find(*itm) == IDs.end() ) IDs.insert(*itm);

			}
		}

		unordered_set<IDmut>::iterator itids = IDs.begin();
		// Metemos las k primeras mutaciones en la cola
		for( int i=0; i<k && itids != IDs.end(); i++ ){
			cola.push(*(this->find_Mut(*itids)));
			++itids;
		}



		while( itids != IDs.end() ){
			iterator it = find_Mut(*itids);
			if( ((cola.top().getCaf()).at(0)) > (*it).getCaf()[0]  ){

				cola.pop();
				cola.push(*(this->find_Mut(*itids)));
			}
			++itids;
		}

		set<mutacion,ProbMutaciones> salida;
		while( !cola.empty() ){
		  salida.insert(cola.top());
			cola.pop();

		}


		return salida;
	}

	/* Métodos relacionados con los iteradores */

  /**
	 * @brief Iterador de clinvar
	 * @return Iterator
  */
	iterator begin(){
		iterator ite;
		ite.it = mutDB.begin();
		return ite;
	}

	/**
	 * @brief iterador de clinvar
	 * @return iterator
  */
	iterator end(){
		iterator ite;
		ite.it = mutDB.end();
		return ite;
	}

	/**
	 * @brief Iterador de clinvar
	 * @return iterator
  */
	iterator lower_bound(string cromosoma, unsigned int posicion){
		mutacion m;
		m.setChr(cromosoma);
		m.setPos(posicion);
		bool encontrado = false;
		iterator it;
		for( it.it = mutDB.begin(); it != mutDB.end() && !encontrado; it++ ){
			if( !( m > *it ) ){
				encontrado = true;
				it--;
			}
		}
		return it;
	}

	/**
	 * @brief Iterador de clinvar
	 * @return iterator
  */
	iterator upper_bound(string cromosoma, unsigned int posicion){
		mutacion m;
		m.setChr(cromosoma);
		m.setPos(posicion);
		bool encontrado = false;
		iterator it;
		for( it.it = mutDB.begin(); it != mutDB.end() && !encontrado; it++ ){
			if( *it > m ){
				encontrado = true;
				it--;
			}
		}
		return it;
	}

	/**
	 * @brief Iterador de las enfermedades de clinvar
	 * @return enfermedad_iterator
  */
	enfermedad_iterator ebegin(){
		return EnfDB.begin();
	}

	/**
	 * @brief Iterador de las enfermedades de clinvar
	 * @return enfermedad_iterator
  */
	enfermedad_iterator eend(){
		return EnfDB.end();
	}

	/**
	 * @brief Iterador de los genes de clinvar
	 * @return gen_iterator
  */
	gen_iterator gbegin(){
		gen_iterator it;
		it.itmap = gen_map.begin();
		it.itlist = gen_map.begin()->second.begin();
		return it;
	}

	/**
	 * @brief Iterador de los genes de clinvar
	 * @return gen_iterator
  */
	gen_iterator gend(){
		map<IDgen, list< set<mutacion>::iterator> >::iterator git;
		git = --gen_map.end();
		gen_iterator it;
		it.itmap = git;
		it.itlist = git->second.end();
		it++;
		return it;
	}



private:

	set<mutacion> mutDB; //base de datos que contiene toda la información asociada a una mutacion
	unordered_map<IDmut,set<mutacion>::iterator> IDm_map; // Asocia IDmutacion con mutación
	map<IDgen, list< set<mutacion>::iterator> > gen_map; // Asocia genes con mutaciones
	map<IDenf,enfermedad> EnfDB; // Base de datos de enfermedades
	multimap<IDenf,set<mutacion>::iterator> IDenf_mmap; // Asocia enfermedad con mutaciones

};
