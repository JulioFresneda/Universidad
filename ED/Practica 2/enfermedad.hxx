/** @brief fichero de implementacion de la clase enfermedad

*/

/**
@brief Este sera el constructor por defecto que inicializara el objeto con todos los elementos vacios.
@param name: Es el nombre de la enfermedad.
@param ID: Identificador de la enfermedad.
@param database: Base de datos que provee el ID
*/
enfermedad::enfermedad(){
  name = "";
  ID = "";
  database = "";
}

/**
@brief
@param name: Es el nombre de la enfermedad.
@param ID: Identificador de la enfermedad.
@param database: Base de datos que provee el ID
*/
void enfermedad::setID(const string& ID){
  this->ID = ID;
}
/**
@brief Este metodo nos devuelve el ID de la enfermedad
@return ID
*/
string enfermedad::getID() const{
  return ID;
}
/**
@brief Nos devuelve una cadena dandonos toda la informacion sobre la enfermedad
@return String concatenado con todos los atributos
*/
string enfermedad::toString() const{
  string resultado = "Nombre = " + name + "; ID = " + ID + "; database = " + database;
  return resultado;
}
/**
@brief Compara dos enfermedades y comprueba si una es menor a la otra comparando por orden alfabetico el nombre.
@param otra: enfermedad que pasamos por referencia para comparar con la enfermedad actual.
@return Devuelve true si la enfermedad actual es menor que la que viene como parametro y false si es mayor.
*/
bool enfermedad::operator<(const enfermedad& otra) const{
  bool menor = false;
  if(this->name < otra.name)
    menor = true;
  return menor;
}
/**
@brief Operador que muestra toda la informacion de la enfermedad
@param os: flujo para mostrar el resultado
@param e: enfermedad a mostrar
@return os, devuelve el flujo mostrando los atributos de la enfermedad
*/

 ostream& operator<< ( ostream& os, const enfermedad & e){
   os << e.toString();
   return os;
 }

 /**
@brief Aniadir nombre
@param name: String con el nombre
*/

void enfermedad::setName(const string &name){
    this->name = name;
    for( int i=0; i<name.length(); i++){
        this->name[i] = tolower(name[i]);
    }
}

/**
@brief Devuelve nombre
@return Nombre
*/

string enfermedad::getName(){
    return name;
}

/**
@brief Sobrecarga del operador !=
@param e: Objeto de clase enfermedad
@return Bool. True si los objetos comparados son distintos. False si no lo son.
*/

bool enfermedad::operator!=(const enfermedad & e) const{
    bool distintos = false;
    if( ID != e.ID )
        distintos = true;
    return distintos;
}

/**
@brief Sobrecarga del operador =
@param e: Objeto de clase enfermedad
@return El objeto pasado como parametro
*/

enfermedad& enfermedad::operator=(const enfermedad & e){
  if(*this!=e){
    this->name = e.name;
    this->ID = e.ID;
    this->database = e.database;
    return *this;
  }
  else{
    return *this;
  }
}

/**
@brief Constructor con parametros
@param name: String con el nombre
@param ID: String con el ID
@param database: String con el database
@pre name tiene que estar en letra minuscula


*/
enfermedad::enfermedad(const string & name, const string & ID, const string & database){

	setName(name);
	setID(ID);
	setDatabase(database);
}

/**
@brief Intoduce string en atributo database
@param database: string con el database
*/
void enfermedad::setDatabase(const string & database){
	this->database = database;
}

/**
@brief Devuelve el atributo database
@return database
*/
string enfermedad::getDatabase(){
	return database;
}

/**
@brief Operador == que nos dice si dos enfermedades son iguales o no
@param e: enfermedad a comparar
@return bool
*/
bool enfermedad::operator==(const enfermedad & e) const{

	if(this->ID == e.ID) return true;
	else return false;
}

/**
@brief Nos dice si una cadena de caracteres esta dentro del nombre d ela enfermedad
@param str: cadena de caracteres que se buscara en el nombre
@pre name tiene que estar en minuscula
@return bool
*/
bool enfermedad::nameContains(const string &str) const{

	string s = str;

	for(int i=0; i < str.size(); i++){
		s[i] = tolower(s[i]);
	}

	if(name.find(s) == string::npos) return false;
	else return true;



}
