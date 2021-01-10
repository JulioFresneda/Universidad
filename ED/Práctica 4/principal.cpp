#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class comp_enf_crec{
public:
  bool operator() (const enfermedad &a, const enfermedad &b){
    return( !(a < b) );
  }
};



typedef conjunto<enfermedad,comp_enf_crec> conjuntoenf;



	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/
template <typename T, typename CMP>
bool load(conjunto<T,CMP> &  cm, const string & s) {
 ifstream fe;
 string cadena;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
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
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }

int main(int argc, char *argv[]){

    conjuntoenf conjuntoEnf;
    string query_str;

    enfermedad a, b, c;
    a.setName("sida");
    b.setName("sindrome de lo q sea");
    c.setName("tuputamadre");

    conjuntoEnf.insert(a);
    conjuntoEnf.insert(b);
    conjuntoEnf.insert(c);

    for( conjuntoenf::iterator it = conjuntoEnf.begin(); it != conjuntoEnf.end(); ++it ){
      conjuntoEnf.getElem(it);
    }

    //Cargar las mutaciones en vectorSNPs
  /*  load(conjuntoMutaciones, "clinvar_20160831.vcf");
    //Imprimir número de elementos almacenados en conjuntoMutaciones
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutaciones.size()<<endl << endl;

    //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
    mutacion m;
    m.setChr("2");
    m.setPos(1);
    a = conjuntoMutaciones.lower_bound(m) - conjuntoMutaciones.begin();
    cout << "Mutaciones asociadas a Chr 1: "<< a<< endl << endl;

    /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
  /*  cout << "¿Existe la mutación con ID rs147165522?" << endl;

     /**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
  /*   cout << "¿Existe la mutación en chr/pos 14/67769578?" << endl;
    m.setChr("12");
    m.setPos(2566465);
    conjuntomutdecr_id::iterator res = conjuntoMutaciones.find(m);
    if ( res < conjuntoMutaciones.end() ){
      conjuntoMutaciones.getElem(res);
    }
    else{
      cout << "No existe mutacion con chr/pos -- 14/67769578" << endl;
    }
    // /**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
    // cout << "¿Cómo podríamos calcular el número de mutaciones del cromosoma 3?" << endl;
    // a = conjuntoMutaciones.lower_bound("4", 1) - conjuntoMutaciones.lower_bound("3",1);
    // cout << "Mutaciones asociadas a Chr 3: "<< a<< endl << endl;
    // /**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

   return 0;
}
