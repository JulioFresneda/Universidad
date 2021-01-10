/*  Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F
5. El recorrido en preordenorden de un determinado árbol binario es:
GEAIBMCLDFKJH
y en inorden
IABEGLDCFMKHJ
Resolver:
a) Dibuja el árbol binario.
b) Da el recorrido en postorden.
c) Diseña una función para dar el recorrido en postorden dados los recorridos en preorden e inorden
(sin construir el árbol) y escribir un programa para comprobar el resultado del apartado anterior.*/

#include "bintree.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;




/*       G
        / \________
       E           M
      /           / \
     A           C   K
    / \         / \   \
   I   B       L  F   J
               \     /
                D   H


Postorden: IBAELDFCKHJMG
*/


void f_postorden(char *preorden,char *inorden,char *postorden,int n)
{
  int sizeizq;

  if(n!=0){
    postorden[n-1]=preorden[0];
    sizeizq=strchr(inorden,preorden[0])-inorden;
    f_postorden(preorden+1,inorden,postorden,sizeizq);
    f_postorden(preorden+1+sizeizq,inorden+1+sizeizq,postorden+sizeizq,n-1-sizeizq);
  }
}

int main(){
  char preorden[14]="GEAIBMCLDFKJH";
  char inorden[14]="IABEGLDCFMKHJ";
  char postorden[14];

  f_postorden(preorden,inorden,postorden,13);

  cout << "Postorden: ";
  for( int i=0; i<13; i++ ){
    cout << postorden[i];
  }

}
