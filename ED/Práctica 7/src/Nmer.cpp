#include "../include/Nmer.h"
#include "../include/ktree.h"
#include <set>

#include <fstream>
using namespace std;



extern void recorrido_preorden(typename ktree<pair<char,int>,4>::const_node n, string s){
  if( !n.null() ){
    if( (*n).first != '-')
      s+=(*n).first;
    cout << "< " << s << " " << (*n).second << " >" << endl;

      for( int i=0; i<4; i++ ){
        if( !n.k_child(i).null() ){
          recorrido_preorden(n.k_child(i),s);
        }
      }

  }
}


Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));

}

Nmer::Nmer( const Nmer &a ){
  max_long = a.max_long;
  el_Nmer = a.el_Nmer;

}



bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;

 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = std::stoi(cadena);
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb);
    fe.close();
    return true;
 } // else
 fe.close();
 return false;
}

void Nmer::list_Nmer() const {
    // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
    string s = "";
    recorrido_preorden(el_Nmer.root(),s);
}


unsigned int Nmer::length() const {
   return max_long;
}

Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}


Nmer& Nmer::operator=( const Nmer a ){
  max_long = a.max_long;
  el_Nmer = a.el_Nmer;
  return *this;
}

void auxPrefix( const ktree<pair<char,int>,4>::node &emisor, ktree<pair<char,int>,4>::node &receptor, ktree<pair<char,int>,4> &nmer ){
  for( unsigned int i=0; i<4; i++ ){
    if( !emisor.k_child(i).null() ){
      pair<char,int> p = *(emisor.k_child(i));
      nmer.insert_k_child(receptor,i,p);
      ktree<pair<char,int>,4>::node naux = receptor.k_child(i);
      auxPrefix(emisor.k_child(i),naux,nmer);
    }
  }
}


Nmer Nmer::Prefix(string adn){
  Nmer aux;
  aux.sequenceADN(adn.size(),adn);
  ktree<pair<char,int>,4>::node naux = aux.el_Nmer.root();
  ktree<pair<char,int>,4>::node naux2 = el_Nmer.root();
  for( unsigned int i = 0; i<adn.size(); i++ ){
    for( unsigned int j=0; j<4; j++ ){
      if( !naux.k_child(i).null() && !naux2.k_child(i).null() ){
        naux = naux.k_child(i);
        naux2 = naux2.k_child(i);
      }
    }
  }
  auxPrefix(naux2,naux,aux.el_Nmer);
  return aux;
}


void Nmer::auxUnion( ktree<pair<char,int>,4>::node &uno, ktree<pair<char,int>,4>::node &dos, ktree<pair<char,int>,4>::node &uni, ktree<pair<char,int>,4> &nmer ){
  pair<char,int> p;
  ktree<pair<char,int>,4>::node naux, naux2;
  for( int i=0; i<4; i++ ){
    if( uno.k_child(i).null() && !(dos.k_child(i).null() ) ){
      p = *dos.k_child(i);
      nmer.insert_k_child(uni,i,p);
      naux = uno.k_child(i);
      naux2 = dos.k_child(i);
      auxUnion(naux,naux2,uni,nmer);
    }
    else if( !(uno.k_child(i).null()) && dos.k_child(i).null() ){
      p = *uno.k_child(i);
      nmer.insert_k_child(uni,i,p);
      naux = uno.k_child(i);
      naux2 = dos.k_child(i);
      auxUnion(naux,naux2,uni,nmer);
    }
    else if( !(uno.k_child(i).null()) && !(dos.k_child(i).null()) ){
      p = *uno.k_child(i);
      p.second += (*dos.k_child(i)).second;
      naux = uno.k_child(i);
      naux2 = dos.k_child(i);
      auxUnion(naux,naux2,uni,nmer);
    }
  }
}


Nmer Nmer::Union( const Nmer  reference ){
  Nmer aux;
  aux.el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
  return Union(aux);
}

bool Nmer::containsString(const string adn) const{
  bool esta = true;
  ktree<pair<char,int>,4>::const_node naux = el_Nmer.root();
  for( unsigned int i=0; i<adn.size() && esta; i++ ){
      if( adn[i] == 'A' ){
        if( naux.k_child(0).null() )
          esta = false;
        else naux = naux.k_child(0);
      }
      if( adn[i] == 'G' ){
        if( naux.k_child(1).null() )
          esta = false;
        else naux = naux.k_child(1);
      }
      if( adn[i] == 'C' ){
        if( naux.k_child(2).null() )
          esta = false;
        else naux = naux.k_child(2);
      }
      if( adn[i] == 'T' ){
        if( naux.k_child(3).null() )
          esta = false;
        else naux = naux.k_child(3);
      }
  }
  return esta;
}


bool Nmer::includedAux( const ktree<pair<char,int>,4>::const_node naux, ktree<pair<char,int>,4>::const_node nauxr ){

  for( int i=0; i<4; i++ ){
    if( !naux.k_child(i).null() ){
      if( nauxr.k_child(i).null() )
        return false;
      else{
        return includedAux(naux.k_child(i),nauxr.k_child(i));
      }
    }
  }
  return true;
}

bool Nmer::included(const Nmer reference){
  ktree<pair<char,int>,4>::const_node nauxr = reference.el_Nmer.root();
  return includedAux(el_Nmer.root(),nauxr);
}



void Nmer::sequenceADN( unsigned int tama, const string & adn ){
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
  string subcadena = "";
  for( unsigned int i=0; i<=adn.size(); i++ ){
    for( unsigned int j=0; j<tama && j<adn.size()-i; j++ ){
      subcadena+=adn[j+i];
    }
    insertar_cadena(subcadena);
    subcadena = "";
  }
}


void Nmer::insertar_cadena( const string &cadena ){
  ktree<pair<char,int>,4>::node n_act = el_Nmer.root();
  for( unsigned int i=0; i<cadena.size(); i++ ){

    if( cadena[i] == 'A' ){
      if( n_act.k_child(0).null() ){
        el_Nmer.insert_k_child(n_act,0,pair<char,int>('A',1));
        (*(n_act.k_child(0))).second = 1;
      }
      else (*(n_act.k_child(0))).second++;
      n_act = n_act.k_child(0);
    }
    if( cadena[i] == 'G' ){
      if( n_act.k_child(1).null() ){
        el_Nmer.insert_k_child(n_act,1,pair<char,int>('G',1));
        (*(n_act.k_child(1))).second = 1;
      }
      else (*(n_act.k_child(1))).second++;
      n_act = n_act.k_child(1);
    }
    if( cadena[i] == 'C' ){
      if( n_act.k_child(2).null() ){
        el_Nmer.insert_k_child(n_act,2,pair<char,int>('C',1));
        (*(n_act.k_child(2))).second = 1;
      }
      else (*(n_act.k_child(2))).second++;
      n_act = n_act.k_child(2);
    }
    if( cadena[i] == 'T' ){
      if( n_act.k_child(3).null() ){
        el_Nmer.insert_k_child(n_act,3,pair<char,int>('T',1));
        (*(n_act.k_child(3))).second = 1;

      }
      else (*(n_act.k_child(3))).second++;
      n_act = n_act.k_child(3);
    }
  }

}

void Nmer::rareAux(const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenCre> &s, int t ){

  string saux = "";
  pair<char,int> p = *nodo;
  bool hoja = true;
  ktree<pair<char,int>,4>::node naux = nodo;
  int aux;

  for( int i=0; i<4; i++ ){
    if( !nodo.k_child(i).null() )
      hoja = false;

  }

  if( hoja && p.second <= t ){
    aux = p.second;
    while( naux != el_Nmer.root() ){
        saux.insert(saux.begin(),p.first);
        naux = naux.parent();
        p = *naux;
    }
    s.insert(pair<string,int>(saux,aux));
  }

  else{
    for( int i=0; i<4; i++ ){
      if( !(nodo.k_child(i).null() ))
        rareAux(nodo.k_child(i),saux,s,t);

    }
  }
}

set<pair<string,int>,OrdenCre>Nmer::rareNmer( int t ){
  set<pair<string,int>,OrdenCre> s;
  string str = "";

  rareAux(el_Nmer.root(),str,s,t);
  return s;

}







void Nmer::commonAux( const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenDecre> &s, int t ){
  string saux = "";
  pair<char,int> p = *nodo, p2 = *nodo;
  bool hoja = true;
  bool encontrada = false;
  ktree<pair<char,int>,4>::node naux = nodo;

  for( int i=0; i<4; i++ ){
    if( !nodo.k_child(i).null() )
      hoja = false;
  }
  if( hoja ){
    while( naux != el_Nmer.root() ){
      if(p.second > t){
         encontrada = true;
       }
      if( encontrada ){
        saux.insert(saux.begin(),p.first);
      }
      naux = naux.parent();
      p = *naux;
    }
    s.insert(pair<string,int>(saux,p2.second));
  }

  else{
    for( int i=0; i<4; i++ ){
      if( !(nodo.k_child(i).null() ))
        commonAux(nodo.k_child(i),saux,s,t);

    }
  }
}


set<pair<string,int>,OrdenDecre>Nmer::commonNmer(int t){
  set<pair<string,int>,OrdenDecre> s;
  string str = "";
  commonAux(el_Nmer.root(),str,s,t);
  return s;
}




void Nmer::levelAux( const ktree<pair<char,int>,4>::node &nodo, string &str, set<pair<string,int>,OrdenCre> &s, int level ){
  ktree<pair<char,int>,4>::node naux = nodo;
  if( level != 0 ){
    for( int i=0; i<4; i++ ){
      if( !nodo.k_child(i).null() ){
        naux = nodo.k_child(i);
        levelAux(naux,str,s,level-1);
      }
    }
  }
  else{
    pair<string,int> p;
    pair<char,int> paux;
    paux = *nodo;
    p.second = paux.second;
    while( naux != el_Nmer.root() ){
      str.insert(str.begin(),paux.first);
      naux = naux.parent();
    }
    p.first = str;
    s.insert(p);
  }
}

set<pair<string,int>,OrdenCre>Nmer::level( int l ){
  set<pair<string,int>,OrdenCre> s;
  string str = "";
  levelAux(el_Nmer.root(),str,s,l);
  return s;
}


void Nmer::auxDistance( const ktree<pair<char,int>,4 >::const_node &nodo, set<pair<string,int>,OrdenDecre> &s, string &saux ){
  pair<char,int> paux;
  for( int i=0; i<4; i++ ){

    if( !nodo.k_child(i).null() ){

      paux = *(nodo.k_child(i));
      saux+=paux.first;

      s.insert(pair<string,int>(saux,paux.second));
      auxDistance(nodo.k_child(i),s,saux);
    }
  }
}


float Nmer::Distance( const Nmer &otro ){
  set<pair<string,int>,OrdenDecre> set1;
  set<pair<string,int>,OrdenDecre> set2;
  string saux1 = "";
  string saux2 = "";

  ktree<pair<char,int>,4>::const_node nodo1 = el_Nmer.root();
  ktree<pair<char,int>,4>::const_node nodo2 = otro.el_Nmer.root();
  
  auxDistance(nodo1,set1,saux1);
  auxDistance(nodo2,set2,saux2);

  set<pair<string,int>,OrdenCre> setrank1;
  set<pair<string,int>,OrdenCre> setrank2;

  int i = 1;
  for( set<pair<string,int>,OrdenDecre>::iterator it = set1.begin(); it != set1.end(); ++it ){
    setrank1.insert(pair<string,int>((*it).first,i));
    i++;
  }
  i = 1;
  for( set<pair<string,int>,OrdenDecre>::iterator it = set2.begin(); it != set2.end(); ++it ){
    setrank2.insert(pair<string,int>((*it).first,i));
    i++;
  }

  int posX, posY;
  float dist = 0;
  float valor = 0;
  unsigned int max = setrank1.size();
  pair<string,int> paux;
  if( setrank2.size() > max ) max = setrank2.size();

  for( set<pair<string,int>,OrdenDecre>::iterator it = setrank1.begin(); it != setrank1.end(); ++it ){
    if( setrank2.find(*it) != setrank2.end() ){
      posX = it->second;
      paux = *(setrank2.find(*it));
      posY = paux.second;
      if( posX > posY ) valor = (posX-posY)/max;
      else valor = (posY-posX)/max;
    }
    dist+=valor;
  }
  return dist/setrank1.size();
}
