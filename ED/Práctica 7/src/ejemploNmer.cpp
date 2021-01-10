#include <iostream>
#include <string>
#include "Nmer.cpp"
#include "../include/ktree.h"



using namespace std;

int main(){
  Nmer a;
  cout << "Secuencia: ACGTACCGTA" << endl;
  cout << "Lista: " << endl;
  a.sequenceADN(3,"ACGTACCGTAT");
  a.list_Nmer();

  cout << endl << endl << "Número de Nmers: " << a.size() << endl;
  cout << endl << "Nmers asociados al prefijo ACG" << endl;
  Nmer b = a.Prefix("ACG");
  b.list_Nmer();
  cout << endl << endl;

  cout << "¿Contiene la secuencia ACG? ";
  if( a.containsString("ACG")) cout << "Sí" << endl << endl;

  Nmer c;
  c.sequenceADN(3,"ACGTACCGT");
  cout << "¿Contiene el Nmer, un Nmer con la secuencia introducida ACGTACCGT? ";
  if( c.included(a) ) cout << "Sí" << endl << endl;

  cout << "Probando rareNmer, t = 1" << endl;
  set<pair<string,int>,OrdenCre > s;
  s = a.rareNmer(1);
  for( set<pair<string,int>,OrdenCre >::iterator it = s.begin(); it != s.end(); ++it ){
    cout << (*it).first << endl;
  }

  cout << "Probando commonNmer, t = 1" << endl;
  set<pair<string,int>,OrdenDecre > s2;
  s2 = a.commonNmer(1);
  for( set<pair<string,int>,OrdenDecre >::iterator it = s2.begin(); it != s2.end(); ++it ){
    cout << (*it).first << endl;
  }



  //No me ha dado tiempo a probar el resto de métodos... Pero están hechos.





}
