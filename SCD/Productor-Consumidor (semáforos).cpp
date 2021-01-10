Ejercicio productor-consumidor:
/*Se han usado dos variables estáticas, un vector de enteros llamado buffer, de tamaño 40, y un
entero llamado índice. También tres semáforos, uno que controla la producción, y otro que
controla la consumición. El tercero controla los mensajes en pantalla.
El semáforo que controla la consumición (puede_consumir) se ha inicializado a 0, por que si no
podría consumir antes de que el productor produjera siquiera. En cambio el semáforo
puede_producir se inicailiza con valor del tamaño del vector, para que sólo pare cuando dé una
vuelta al vector y alcance al consumidor, ya que el resultado sería incorrecto.
Para el correcto funcionamiento del programa, se han puesto los semáforos de la siguiente
forma:
sem_wait(&puede_producir) en la función productora, antes de insertar el dato en el
búffer, para que no inserte dato cuando no debe.
sem_post(&puede_consumir) en la función productora, después de insertar el dato en el
búffer, para que la función consumidora sepa que puede consumir en esa posición del
vector.
sem_wait(&puede_consumir) en la función consumidora, antes de consumir, esperando
la señal de la función productora para consumir.
sem_post(&puede_producir) en la función consumidora, después de consumir, para que
la función productora pueda producir sin miedo a acceder a una posición errónea del
vector.
El código del programa es el siguiente.*/
// *****************************************************************************
//
// Prácticas de SCD. Práctica 1.
// Plantilla de código para el ejercicio del productor-consumidor con
// buffer intermedio.
//
// *****************************************************************************
#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // necesario para {\ttbf usleep()}
#include <stdlib.h> // necesario para {\ttbf random()}, {\ttbf srandom()}
#include <time.h> // necesario para {\ttbf time()}
using namespace std ;// ---------------------------------------------------------------------
// constantes configurables:
static int buffer[40];
static int indice = 0;
const unsigned
num_items = 40 , // numero total de items que se producen o consumen
tam_vector = 10 ; // tamaño del vector, debe ser menor que el número de items
sem_t mutex, puede_producir, puede_consumir;
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
// ---------------------------------------------------------------------
// función que simula la producción de un dato
unsigned producir_dato()
{
static int contador = 0 ;
contador = contador + 1 ;
retraso_aleatorio( 0.1, 0.5 );
cout << "Productor : dato producido: " << contador << endl << flush ;
return contador ;
}
// ---------------------------------------------------------------------
// función que simula la consumición de un dato
void consumir_dato( int dato )
{
retraso_aleatorio( 0.1, 1.5 );
cout << "Consumidor:
dato consumido: " << dato << endl << flush ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del productor
void * funcion_productor( void * )
{
for( unsigned i = 0 ; i < num_items ; i++ )
{
int dato = producir_dato() ;
sem_wait(&puede_producir);sem_wait(&mutex);
// falta aquí: insertar "dato" en el vector o buffer
buffer[indice] = dato;
indice++;
cout << "Productor : dato insertado: " << dato << endl << flush ;
sem_post(&puede_consumir);
sem_post(&mutex);
}
return NULL ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del consumidor
void * funcion_consumidor( void * )
{
for( unsigned i = 0 ; i < num_items ; i++ )
{
int dato ;
// falta aquí: leer "dato" desde el vector intermedio
sem_wait(&puede_consumir);
sem_wait(&mutex);
dato = buffer[indice-1];
indice--;
cout << "Consumidor:
consumir_dato( dato ) ;
dato extraído : " << dato << endl << flush ;
sem_post(&mutex);
sem_post(&puede_producir);
}
return NULL ;
}
//----------------------------------------------------------------------
int main()
{
// falta: crear y poner en marcha las hebras, esperar que terminen
pthread_t consumidor, productor;
sem_init(&mutex,1,1);
sem_init(&puede_producir,0,tam_vector);
sem_init(&puede_consumir,0,0);
pthread_create(&consumidor,NULL,funcion_consumidor,NULL);
pthread_create(&productor,NULL,funcion_productor,NULL);
pthread_join(consumidor,NULL);
pthread_join(productor,NULL);
sem_destroy(&mutex);
sem_destroy(&puede_producir);
sem_destroy(&puede_consumir);
return 0 ;
}
