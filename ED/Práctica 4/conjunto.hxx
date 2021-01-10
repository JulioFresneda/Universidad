///////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename CMP>
void conjunto<T,CMP>::getElem( conjunto::iterator pos ) const{
  if ( pos >= vm.begin() && pos < vm.end() ){
    int i = pos-vm.begin();
    cout << vm[i] << endl;
  }
}

template <typename T, typename CMP>
conjunto<T,CMP>::conjunto(){
  vector<T> a;
	this->vm = a;
  CMP cmp;
  this->comp = cmp;
}
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::find (const conjunto::value_type & s) const{
  conjunto::const_iterator it;

  for( it = vm.begin(); !it.end() ; ++it ){
    if( !comp(*it,s) && !comp(s,*it) ){
      return it;
    }
  }
  return it;
}
template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (conjunto::value_type& val){
  pair<conjunto<T,CMP>::iterator,bool > res;
  if ( vm.size() == 0 ){
		vm.push_back(val);
    res.first = vm.begin();
    res.second = true;
		return res;
	}
	if( comp(vm[vm.size()-1],val) ){
		vm.push_back(val);
    res.first = vm.end()-1;
    res.second = true;
		return res;
	}
	else{
	  for ( conjunto<T,CMP>::iterator it = vm.begin(); it != vm.end(); ++it ){
      if( !comp(*it,val) ){
        vm.insert(it,val);
        res.first = it;
        res.second = true;
        return res;
      }
    }
	}
}

template <typename T, typename CMP>
void conjunto<T,CMP>::clear (){
  vm.clear();
}

template <typename T, typename CMP>
conjunto<T,CMP> & conjunto<T,CMP>::operator=( const conjunto & org){
  if ( this != &org ){
    this->vm = org.vm;
  }
  return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const{
  return vm.begin();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const conjunto::value_type& val) const{
  conjunto::const_iterator it;
	for( it = vm.begin() ; it != vm.end(); ++it )
		if(!comp(*it,val))
      return it;
    else
      return vm.end();
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::cheq_rep( ) const{
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
///////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto & d){
    this->vm = d.vm;
    this->comp = d.comp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const conjunto::value_type & e) const{
    bool repe = false;
    for( int i=0; i<vm.size(); i++ ){
        if( !comp(vm[i],e) && !comp(e,vm[i]) )
            repe = true;
    }
    if (repe) return 1; else return 0;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::erase (const conjunto::iterator position){
    vm.erase(position);
    return ++position;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::size() const{
    return vm.size();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin (){
    conjunto::iterator it;
    if( vm.size() > 0 )
        it = vm.begin();
    else it = vm.end();
    return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const{
    return vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const conjunto::value_type& val){
    conjunto::const_iterator it;
    bool aqui = false;
    for( it = vm.begin(); it != vm.end() && !aqui; ++it ){
        if( comp(val,*it) ) aqui = true;
    }
    return it;
}

template <typename T, typename CMP>
ostream &  operator<< ( ostream & sal, const conjunto<T,CMP> & C){
  for ( int i = 0; i < C.size(); i++ ){
      sal << C.vm[i];
  }
  return sal;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::find (const conjunto::value_type & e){

    	typename conjunto::iterator it = vm.begin();
			while(it!=vm.end() && (comp(*it,e) || comp(e,*it))){
				it++;
			}
			return it;
}

template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (const conjunto::value_type& val){
    pair<conjunto::iterator,bool> salida;
    conjunto::iterator its = vm.begin();
    bool bs = false;

    if ( vm.size() == 0 ){
        vm.push_back(val);
        salida.first = vm.begin();
        salida.second = true;
        return salida;
    }
    if( vm[vm.size()-1] < val ){
        vm.push_back(val);
        salida.first = vm.end();
        salida.second = true;
        return salida;
    }
    if ( val < vm[0] ){
        vm.insert(vm.begin(),val);
        salida.first = vm.begin();
        salida.second = true;
        return salida;
    }
    else{
      while(!bs){
            if(!comp(*its,val) && !comp(val,*its)){
                salida.first = vm.end();
                salida.second = false;
                return salida;
            }

            else if(comp(*val,*its)){
                vm.insert(its, val);
                bs = true;
                salida.first = its;
                salida.second = bs;
                return salida;
            }
            its++;
        }
    }
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase (const conjunto::value_type& val){
	conjunto::size_type count = 0;
	for(int i = 0; i < vm.size(); i++){
		if(!comp(vm[i],val) && !comp(val,vm[i])){
			vm.erase(vm.begin()+i);
			count++;
		}
	}
	return count;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::empty() const{
	if(vm.size() == 0) return true;
	else return false;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end(){
	return vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const conjunto::value_type& val){

	    conjunto::iterator it;
	    bool esta = false;
	    for( it=vm.begin(); it!=vm.end() && !esta; ++it ){
	        if( !comp(*it,val) ){
	            esta = true;
					}
	    }
	    return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const conjunto::value_type& val) const{

	bool encontrado = false;
	conjunto::const_iterator it;
	for ( it = vm.begin(); it != vm.end() && !encontrado; ++it ){
		if ( !(comp(*it, val)) ){
			if( !comp(*it, val) && !comp(val, *it) )
				it++;
			encontrado = true;
		}
	}
	return it;
}

////////////////////////////////////////////////////////////////////////////////////
