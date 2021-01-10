

/**
@brief Constructor por defecto de la clase mutacion donde inicializaremos todos los valores a nulo.
*/
mutacion::mutacion(){
  ID = "";
  chr = "";
  pos = 0;
  common = "";
}


mutacion::mutacion(const string & str){
  int i = 0 , j = 0;
  if(str[i] != '#'){
    string aux;
    int auxi;
    vector<string> elem;
    while(i < 5){
      aux.clear();
      while(str[j] != '\t'){
        aux.push_back(str[j]);
        j++;
      }
      elem.push_back(aux);
      i++;
      j++;
    }
    aux.clear();
    int k = 0, i = 0;
    k = str.find("GENEINFO");
    k += 9;
    vector<string> a;
    while(str[k] != ';' ){
      if(str[k] == '|' || str[k] == ','){
        a.push_back(aux);
        k++;
        aux.clear();
      }
      aux.push_back(str[k]);
      k++;
    }
    a.push_back(aux);
    setGenes(a);
    aux.clear();
    k = str.find("CAF");
    if( k != -1 ){

      string s;
      bool lee;
      k+=4;

      while(str[k] != ';'){

          s.push_back(str[k]);
          lee = false;

          if (str[k+1] == '|' || str[k+1] == ','){

              caf.push_back(strtof(s.c_str(), NULL));
              k+=2;
              lee = true;
          }
          else
              k++;

          if(str[k] == ';'){
              caf.push_back(strtof(s.c_str(), NULL));
          }

          if (lee)
          {
              s.clear();
          }
      }
    } else caf.push_back(1.0);

    k = str.find("COMMON");
    k += 7;
    aux.push_back(str[k]);
    if(aux == "1"){
      setCommon(true);
    }
    else{
      setCommon(false);
    }

    k = str.find("CLNSIG");
    k += 7;
    vector<int> c;
    while(str[k] != ';' ){
      if(str[k] == '|' || str[k] == ','){
        auxi = atoi(aux.c_str());
        c.push_back(auxi);
        k++;
        aux.clear();
      }
      aux.push_back(str[k]);
      k++;
    }
    auxi = atoi(aux.c_str());
    c.push_back(auxi);
    setClnsig(c);
    aux.clear();

    k = str.find("CLNDBN");
    k += 7;
    vector<enfermedad> d;
    vector<string> nombres;
    vector<string> ID;
    vector<string> databases;
    while(str[k] != ';' ){
      if(str[k] == '|' || str[k] == ','){
        nombres.push_back(aux);
        k++;
        aux.clear();
      }
      aux.push_back(str[k]);
      k++;
    }
    nombres.push_back(aux);
    aux.clear();

    k = str.find("CLNDSDBID");
    k += 10;
    while(str[k] != ';' ){
      if(str[k] == '|' || str[k] == ','){
        ID.push_back(aux);
        k++;
        aux.clear();
      }
      aux.push_back(str[k]);
      k++;
    }
    ID.push_back(aux);
    aux.clear();

    k = str.find("CLNDSDB");
    k += 8;
    while(str[k] != ';' ){
      if(str[k] == '|' || str[k] == ','){
        databases.push_back(aux);
        k++;
        aux.clear();
      }
      aux.push_back(str[k]);
      k++;
    }
    databases.push_back(aux);
    aux.clear();

    for( char i = 0; i < nombres.size(); i++){
      if(ID.size() == nombres.size()){
        enfermedad p(nombres[i], ID[i], databases[i]);
        d.push_back(p);
      }
      else{
        enfermedad p(nombres[i], ID[0], databases[0]);
        d.push_back(p);
      }
    }
    setEnfermedades(d);

    setChr(elem[0]);
    setPos(atoi(elem[1].c_str()));
    setID(elem[2]);
    vector<string> z;
    z.push_back(elem[3]);
    z.push_back(elem[4]);
    setRef_alt(z);
  }

}

/**
@brief Insertar valor al atributo ID
@param id: Valor del campo ID para insertarlo a la mutacion
*/
void mutacion::setID( const string &id ){
  this->ID = id;
}
/**
@brief Este metodo nos permitira darle valor al atriburo ref_alt de la mutacion
@param ref_alt: Vector de string que asignaremos al atributo
*/
void mutacion::setRef_alt (const vector < string > &ref_alt){
  this->ref_alt = ref_alt;
}
/**
@brief Este metodo nos permitira darle valor al atriburo caf de la mutacion
@param caf: Vector de float que asignaremos al atributo
*/
void mutacion::setCaf (const vector < float > &caf){
  this->caf = caf;
}
/**
@brief Nos devuelve el valor del ID
@return ID
*/
string mutacion::getID () const{
  return ID;
}
/**
@brief Nos devuelve el string del atriburo ref_alt
@return ref_alt
*/
const vector < string > & mutacion::getRef_alt () const{
  return ref_alt;
}
/**
@brief Devuelve el vector de float del atriburo caf
@return caf
*/
const vector < float > & mutacion::getCaf () const{
  return caf;
}
/**
@brief Operador para igualar dos mutaciones
@param m: mutacion de la que queremos copiar el contenido
@return *this
*/
mutacion & mutacion::operator= (const mutacion &m){
  if(this != &m){
    this->ID = m.ID;
    this->chr = m.chr;
    this->pos = m.pos;
    this->ref_alt = m.ref_alt;
    this->genes = m.genes;
    this->common = m.common;
    this->caf = m.caf;
    this->enfermedades = m.enfermedades;
    this->clnsig = m.clnsig;
  }
  return *this;
}
/**
@brief Operador que nos muestra por pantalla una mutacion mostrando todos sus campos.
@param os: Flujo de salida
@param m: Objeto de la clase mutacion de la que mostraremos su contenido
*/
ostream& operator<< ( ostream& os, const mutacion& m){
  os << "Mutacion: " << m.getID() << endl;
  os << "\tCromosoma: " << m.getChr() << endl;
  os << "\tPosicion: " << m.getPos() << endl;
  os << "\tBase: ";
  for(int i = 0;i<m.getRef_alt().size(); i++){
    os << m.getRef_alt()[i] << " -- ";
  }
  os << endl << "\tGenes: ";
  for(int i = 0;i<m.getGenes().size(); i++){
    os << m.getGenes()[i] << " -- ";
  }
  os << "\t¿Es comun?: " << m.getCommon() << endl;
  os << "\tFrecuencia: ";
  for(int i = 0;i<m.getCaf().size(); i++){
    os << m.getCaf()[i] << " -- ";
  }
  os << endl << "\tEnfermedades: ";
  for(int i = 0;i<m.getEnfermedades().size(); i++){
    os << m.getEnfermedades()[i] << " -- ";
  }
  os << endl << "\tRelevancia clinica: ";
  for(int i = 0;i<m.getClnsig().size(); i++){
    os << m.getClnsig()[i] << " -- ";
  }
  os << endl << endl;

  return os;
}
/**
@brief Metemos un valor al atributo pos.
@param pos: valor a introducir en el atributo
*/
void mutacion::setPos(const unsigned int & pos){
	this->pos = pos;
}
/**
@brief Permite meter el valor del atriburo common
@param common: booleano con el valor a introducir en el atributo
*/
void mutacion::setCommon (const bool & common){
	this->common = common;
}
/**
@brief Introducir el valor del atributo clnsig
@param clnsig: vector de enteros que vamos a asignarle al atributo
*/
void mutacion::setClnsig (const vector<int> & clnsig){
	this->clnsig = clnsig;
}
/**
@brief Nos devuelve el valor del atributo pos
@return pos
*/
unsigned int mutacion::getPos() const{
	return pos;
}
/**
@brief Devuelve el valor del atributoo common
@return common
*/
bool mutacion::getCommon () const{
	return common;
}
/**
@brief Devuelve el valor del atributo clnsig
@return clnsig
*/
const vector<int> & mutacion::getClnsig () const{
	return clnsig;
}

/**
@brief Constructor a partir de otro objeto de clase mutacion
@param m: Objeto clase mutacion
*/

mutacion::mutacion(const mutacion& m){
	this->ID = m.ID;
  this->chr = m.chr;
  this->pos = m.pos;
  this->ref_alt = m.ref_alt;
  this->common = m.common;
  this->genes = m.genes;
  this->caf = m.caf;
  this->enfermedades = m.enfermedades;
  this->clnsig = m.clnsig;

}

/**
@brief Aniadir chr
@param chr: string
*/

void mutacion::setChr(const string & chr){
	this->chr = chr;
}

/**
@brief Aniadir genes
@param genes: vector de strings
*/

void mutacion::setGenes (const vector<string> & genes){
		this->genes = genes;
}

/**
@brief Aniadir enfermedades
@param enfermedades: vector de objetos de clase enfermedad
*/

void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades){
		this->enfermedades = enfermedades;
}

/**
@brief Obtener chr
@return chr
*/

string mutacion::getChr( ) const{
	return chr;
}

/**
@brief Obtener genes
@return vector de genes (strings)
*/

const vector<string> & mutacion::getGenes () const{
	return genes;
}

/**
@brief Obtener enfermedades
@return vector de objetos de clase enfermedad
*/

const vector<enfermedad> & mutacion::getEnfermedades () const{
	return enfermedades;
}

/**
@brief Sobrecarga del operador ==
@param m: Objeto clase mutacion
@return bool
*/

bool mutacion::operator==(const mutacion & m) const{
	if (this == &m ){
    return true;
  }
	if( (this->ID == m.ID) || (this->chr == m.chr && this->pos == m.pos) ){
		return true;
	}
  return false;
}

/**
@brief Compara dos mutaciones para ver cual de ellas es menor a la otra.
@param m: mutacion a comparar con la mutacion propia
@return bool
*/

bool mutacion::operator<(const mutacion & m) const{

	if(this->chr == m.getChr()) return (this->pos < m.getPos());

	else if(this->chr != "X" && this->chr != "Y" && this->chr != "MT"){

		if(m.getChr() == "X" || m.getChr() == "Y" || m.getChr() == "MT") return true; //Porque si this->chr < X, y m.chr >= X, this->chr < m.chr
		else{
      int a = atoi(this->chr.c_str());
      int b = atoi(m.getChr().c_str());
      return(a < b);
    }
	}
	else{
    if(m.getChr() != "X" && m.getChr() != "Y" && m.getChr() != "MT") return false;

		if(this->chr == "X") return true;
		else if(this->chr == "Y"){
			if(m.getChr() == "X") return false;
			else return true;
		}
		else return false;
	}

}
/**
@brief Compara dos mutaciones para ver cual de ellas es mayor a la otra.
@param m: mutacion a comparar con la mutacion propia
@return bool
*/
bool mutacion::operator>(const mutacion & m) const{

	if(this->chr == m.getChr()) return (this->pos > m.getPos());

	else if(this->chr != "X" && this->chr != "Y" && this->chr != "MT"){

		if(m.getChr() == "X" || m.getChr() == "Y" || m.getChr() == "MT") return false; //Porque si this->chr < X, y m.chr >= X, this->chr < m.chr
		else{
      int a = atoi(this->chr.c_str());
      int b = atoi(m.getChr().c_str());
      return(a > b);
    }
	}
	else{
    if(m.getChr() != "X" && m.getChr() != "Y" && m.getChr() != "MT") return true;

		if(this->chr == "X") return false;
		else if(this->chr == "Y"){
			if(m.getChr() == "X") return true;
			else return false;
		}
		else return true;
	}

}
/**
@brief Compara dos mutaciones para ver cual de ellas es mayor a la otra.
@param m: mutacion a comparar con la mutacion propia
@return bool
*/
