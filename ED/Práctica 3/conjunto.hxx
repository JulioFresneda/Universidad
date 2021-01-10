//Nos dice si el chr de x es menor que el chr de m
bool compare_chr(const mutacion & x, const mutacion & m){

	if(x.getChr() == m.getChr()) return false;

	else if(x.getChr() != "X" && x.getChr() != "Y" && x.getChr() != "MT"){

		if(m.getChr() == "X" || m.getChr() == "Y" || m.getChr() == "MT") return true; //Porque si x.chr < X, y m.chr >= X, this->chr < m.chr
		else{
			int a = atoi(x.getChr().c_str());
      int b = atoi(m.getChr().c_str());
			return(a < b);
		}
	}
	else{
    if(m.getChr() != "X" && m.getChr() != "Y" && m.getChr() != "MT") return false;

		if(x.getChr() == "X") return true;
		else if(x.getChr() == "Y"){
			if(m.getChr() == "X") return false;
			else return true;
		}
		else return false;
	}
}


bool compare_chr_pos(const string & x, int y , const string & z , int t){

	if(x == z) return false;

	else if(x != "X" && x != "Y" && x != "MT"){

		if(z == "X" || z == "Y" || z == "MT") return true; //Porque si x.chr < X, y m.chr >= X, this->chr < m.chr
		else{
			int a = atoi(x.c_str());
      int b = atoi(z.c_str());
			return(a < b);
		}
	}
	else{
    if(z != "X" && z != "Y" && z != "MT") return false;

		if(x == "X") return true;
		else if(x == "Y"){
			if(z == "X") return false;
			else return true;
		}
		else return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

conjunto::conjunto(){
  vector<mutacion> a;
	this->vm = a;
}

pair<conjunto::value_type,bool> conjunto::find (const string & ID) const{
  pair<conjunto::value_type,bool> resultado;
  bool encontrado = false;

  for( int i = 0; i < vm.size() && !encontrado; i++ ){
    if(vm[i].getID() == ID){
      resultado.first = vm[i];
      resultado.second = true;
      encontrado = true;
    }
  }
  if( !encontrado ){
    mutacion a;
    resultado.first = a;
    resultado.second = false;
  }
  return resultado;
}

conjunto::size_type conjunto::count (const string & ID) const{
  for( int i = 0; i < vm.size(); i++ ){
    if(vm[i].getID() == ID){
      return 1;
    }
  }
  return 0;
}

bool conjunto::erase(const string & chr, const unsigned int & pos){
  bool borrado = false;
  for ( int i = 0; i < vm.size() && !borrado; i++ ){
    if ( vm[i].getChr() == chr && vm[i].getPos() == pos ){
      vm.erase(vm.begin()+i);
      borrado = true;
    }
  }
  return borrado;
}

void conjunto::clear (){
  vm.clear();
}

conjunto & conjunto::operator=( const conjunto & org){
  if ( this != &org ){
    this->vm = org.vm;
  }
  return *this;
}

conjunto::const_iterator conjunto::upper_bound (const string & chr, const unsigned int & pos) const{
  bool encontrado = false;
  conjunto::const_iterator it;
  for (  it = vm.begin(); it != vm.end() && !encontrado; ++it ){
    if ( !(compare_chr_pos(it->getChr() , it->getPos() , chr , pos)) ){
      if( it->getChr() == chr && it->getPos() == pos )
        it++;
      encontrado = true;
    }
  }
  return it;
}

ostream &  operator << ( ostream & sal, const conjunto & C){
  for ( int i = 0; i < C.size(); i++ ){
      sal << C.vm[i];
  }
  return sal;
}

conjunto::iterator conjunto::begin (){
	return vm.begin();
}

conjunto::iterator conjunto::end (){
	return vm.end();
}

conjunto::const_iterator conjunto::cbegin () const{
	return vm.begin();
}

conjunto::const_iterator conjunto::cend () const{
	return vm.end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

conjunto<T>::conjunto (const conjunto & d){
    this->vm = d.vm;
    this->CMP = d.CMP;
}

pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
    pair<conjunto::value_type,bool> res;
    mutacion a;
    res.first = a;
    res.second = false;
    for( int i=0; i<vm.size() && res.second == false; i++ ){
        if( vm[i].getID() == e.getID() || ( vm[i].getChr() == e.getChr() && vm[i].getPos() == e.getPos() ) ){
            res.first = e;
            res.second = true;
        }
    }
    return res;
}


bool conjunto::erase(const string & ID){
    bool esta = false;
    for( int i=0; i<vm.size() && !esta; i++ ){
        if( vm[i].getID() == ID ){
            esta = true;
            vm.erase(vm.begin()+i);
				}
    }
    return esta;
}

conjunto::size_type conjunto::size() const{
    return vm.size();
}

conjunto::const_iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) const{

    conjunto::const_iterator it;
    bool esta = false;
    for( it=vm.begin(); it!=vm.end() && !esta; ++it ){
        if( !(compare_chr_pos(it->getChr(),it->getPos(),chr,pos) ) ){
            esta = true;
				}
    }
    return it;
}

conjunto::const_iterator conjunto::upper_bound (const conjunto::value_type & e) const{

    conjunto::const_iterator i;
    bool esta = false;
    for( i=vm.begin(); i!=vm.end() && !esta; ++i ){
        if( compare_chr_pos(e.getChr(),e.getPos(),i->getChr(),i->getPos()))
            esta = true;
    }
    return i;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool conjunto::cheq_rep( ) const{

	bool salida = true;

	for(int i = 0; i < vm.size(); i++){
		if(vm[i].getChr() < "1" || vm[i].getChr() > "22" || vm[i].getChr() != "X" || vm[i].getChr() != "Y" || vm[i].getChr() != "MT" )
			salida = false;
	}
	for(int i = 0; i < vm.size()-1; i++){
//		vm[i].chr == vm[i+1].chr, entonces: vm[i].pos <
//		vm[i+1].pos
		if(!(vm[i].getChr() == vm[i+1].getChr() && vm[i].getPos() < vm[i+1].getPos()))
			salida = false;

//si vm[i].chr != vm[i+1].chr, entonces vm[i].chr < vm[i+1].chr
		if(!(vm[i].getChr() != vm[i+1].getChr() && compare_chr(vm[i], vm[i+1]) ))
			salida = false;
	}
	return salida;
}

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{

	pair<conjunto::value_type,bool> s;

	for(int i = 0; i < vm.size(); i++){

		if(vm[i].getChr() == chr && vm[i].getPos() == pos){

			s.first = vm[i];
			s.second = true;

			return s;
		}
	}
  mutacion a;
	s.first = a;
	s.second = false;

	return s;

}

conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{

	for(int i = 0; i < vm.size(); i++){

		if(this->vm[i].getChr() == chr && this->vm[i].getPos() == pos){

			return 1;
		}
	}

	return 0;
}

bool conjunto::insert( const conjunto::value_type & e){
	if ( vm.size() == 0 ){
		vm.push_back(e);
		return true;
	}
	if( vm[vm.size()-1] < e ){
		vm.push_back(e);
		return true;
	}
	if ( e < vm[0] ){
		vm.insert(vm.begin(),e);
		return true;
	}
	else{
	  int Iarriba = vm.size()-1;
	  int Iabajo = 0;
	  int Icentro;
	  while (Iabajo <= Iarriba){
      Icentro = (Iarriba + Iabajo)/2;
      if (vm[Icentro] == e)
 				return false;
      else
 				if (e < vm[Icentro])
   				Iarriba=Icentro-1;
 				else
   				Iabajo=Icentro+1;
	  }
		vm.insert(vm.begin()+Icentro,e);
		return true;
	}
}

bool conjunto::erase(const conjunto::value_type & e){
	for (int i = 0; i < vm.size(); i++) {
		if (vm[i].getID() == e.getID()) {
			vm.erase(vm.begin()+i);
			return true;
		}
		else return false;
	}
}

bool conjunto::empty() const{
	if(vm.size() == 0) return true;
	else return false;
}

conjunto::const_iterator conjunto::lower_bound (const conjunto::value_type & e) const{

	conjunto::const_iterator it;
	for( it = vm.begin() ; it != vm.end(); ++it )
		if(!(*it < e)) return it;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
