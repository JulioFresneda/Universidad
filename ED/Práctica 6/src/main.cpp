#include "../include/clinvar.h"
#include <iostream>
#include <set>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>

int main(){
  clinvar prueba;
  prueba.load("./clinvar_20160831.vcf");

  // Probando iteradores
  clinvar::iterator it = prueba.begin();
  cout << *it << endl;
  it++;
  it+=5;
  it--;
  it-=5;
  cout << *it << endl;
  it = prueba.lower_bound("4",373858); // He puesto esa posición intencionadamente. Es una posición real
  cout << "lower_bound: " << endl << *it << endl;
  it++;
  if( *it == *(prueba.upper_bound("4",373858))){
    cout << "lower_bound y upper_bound funcionan correctamente." << endl << endl;
  }

  // Probando gen_iterators
  clinvar::gen_iterator git = prueba.gbegin();
  cout << *git << endl;
  git++;
  git+=5;
  git--;
  git-=5;
  cout << *git << endl;

  // Probando métodos
  list<IDenf> lista_enf = prueba.getEnfermedades("cancer");

  clinvar::enfermedad_iterator eit = prueba.find_Enf(*lista_enf.begin());

  set<IDmut> set_mut = prueba.getMutacionesEnf(*lista_enf.begin());

  IDmut mut = *(set_mut.begin());
  mutacion m = *(prueba.find_Mut(mut));
  cout << m << endl;
  vector<enfermedad> v_enf = prueba.getEnfermedades(m);

  prueba.erase(mut);
  if( prueba.end() == prueba.find_Mut(mut) )
    cout << endl << "Borrado correctamente." << endl;

  prueba.insert(m);
  if( prueba.end() != prueba.find_Mut(mut) )
    cout << endl << "Insertado correctamente." << endl;



  // Probando topKMutaciones

  cout << endl << endl << endl << "Probando topKMutaciones: " << endl;

  set<mutacion,ProbMutaciones> s = prueba.topKMutaciones(10,"cancer");
  for( set<mutacion,ProbMutaciones>::iterator it = s.begin(); it != s.end(); ++it ){
    cout << *it << endl << flush;
    cout << "Probabilidad: " << 1-it->getCaf()[0] << endl << flush;
  }








}
