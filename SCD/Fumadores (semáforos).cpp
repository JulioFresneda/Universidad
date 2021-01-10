/*Ejercicio fumadores:
Se han usado cinco semáforos, tres para los fumadores, uno para el estanquero y otro para los
mensajes.
Los semáforos para los fumadores sirven para decidir cuándo un fumador puede coger
ingrediente y avisar al fumador cuando el estanquero deja el ingrediente en la mesa.
El semáforo de estanquero sirve para que el fumador le avise de que ya ha cogido el ingrediente
y puede poner otro en la mesa, y para bloquear al propio estanquero para no poner dos
ingredientes en la mesa a la vez.
El semáforo mutex sirve para que los mensajes salgan en pantalla correctamente.
El código fuente es el siguiente:
*/
// *****************************************************************************
//
// Prácticas de SCD. Práctica 1.
// Plantilla de código para el ejercicio de los fumadores
//
// *****************************************************************************
#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> // incluye "time(....)"
#include <unistd.h> // incluye "usleep(...)"
#include <stdlib.h> // incluye "rand(...)" y "srand"
using namespace std ;
sem_t sfumar[3], sestanquero, mutex;
// ---------------------------------------------------------------------
// introduce un retraso aleatorio de duración comprendida entre
// 'smin' y 'smax' (dados en segundos)
void retraso_aleatorio( const float smin, const float smax )
{
static bool primera = true ;
if ( primera )
// si es la primera vez:
{ srand(time(NULL)); // inicializar la semilla del generador
primera = false ; // no repetir la inicialización
}
// calcular un número de segundos aleatorio, entre {\ttbf smin} y {\ttbf smax}
const float tsec = smin+(smax-smin)*((float)random()/(float)RAND_MAX);
// dormir la hebra (los segundos se pasan a microsegundos, multiplicándos por 1 millón)
usleep( (useconds_t) (tsec*1000000.0) );
}
// ----------------------------------------------------------------------------
// función que simula la acción de fumar, como un retardo aleatorio de la hebra.
// recibe como parámetro el numero de fumador
// el tiempo que tarda en fumar está entre dos y ocho décimas de segundo.void * fumar( void * n )
{
while(true){
unsigned long num_fumador = (unsigned long) n ;
sem_wait(&sfumar[num_fumador]);
sem_post(&sestanquero);
sem_wait(&mutex);
cout << "Fumador número " << num_fumador << ": coge ingrediente y comienza a fumar." << endl << flush ;
}
retraso_aleatorio( 0.2, 5 );
cout << "Fumador número " << num_fumador << ": termina de fumar." << endl << flush ;
sem_post(&mutex);
}
// ----------------------------------------------------------------------------
// falta: resto de funciones
void * estanquero(void *)
{
while(true){
sem_wait(&sestanquero);
sem_wait(&mutex);
unsigned int ingrediente = (rand() % 3U);
cout << "Aquí dejo el ingrediente " << ingrediente << endl << flush;
sem_post(&mutex);
sem_post(&sfumar[ingrediente]);
}
}
// ----------------------------------------------------------------------------
int main()
{
srand( time(NULL) ); // inicializa semilla aleatoria para selección aleatoria de fumador
pthread_t hebra_e, hebra_f1, hebra_f2, hebra_f3;
sem_init(&mutex,0,1);
sem_init(&sestanquero,0,1);
sem_init(&sfumar[0],0,0);
sem_init(&sfumar[1],0,0);
sem_init(&sfumar[2],0,0);
pthread_create(&hebra_e,NULL,estanquero,NULL);
pthread_create(&hebra_f1,NULL,fumar,(void *)0);
pthread_create(&hebra_f2,NULL,fumar,(void *)1);
pthread_create(&hebra_f3,NULL,fumar,(void *)2);
pthread_join(hebra_e,NULL);
pthread_join(hebra_f1,NULL);
pthread_join(hebra_f2,NULL);
pthread_join(hebra_f3,NULL);
sem_destroy(&mutex);sem_destroy(&sestanquero);
sem_destroy(&sfumar[0]);
sem_destroy(&sfumar[1]);
sem_destroy(&sfumar[2]);
return 0 ;
}
