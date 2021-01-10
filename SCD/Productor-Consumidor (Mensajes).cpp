#include <mpi.h>
#include <iostream>
#include <math.h>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"


#define Productor    0	// Sólo es una etiqueta, el productor puede ser desde el proceso 0 hasta el proceso 4
#define Buffer       5
#define Consumidor   2	// Sólo es una etiqueta, el consumidor puede ser desde el proceso 6 hasta el proceso 9

#define ITERS       20
#define TAM          5

#define NumProcesos 10
#define NumProductores 5
#define NumConsumidores 4

using namespace std;

// ---------------------------------------------------------------------

void productor( int rank )
{
   int value;  

   for ( unsigned int i=0; i < ITERS/NumProductores ; i++ )
   { 
      value = i ;
      cout << "Productor " << rank << " produce valor " << value << endl << flush ;
      
      // espera bloqueado durante un intervalo de tiempo aleatorio 
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
      
      // enviar 'value'
      MPI_Ssend( &value, 1, MPI_INT, Buffer, Productor, MPI_COMM_WORLD );
   }
}
// ---------------------------------------------------------------------

void buffer()
{
   int        value[TAM] , 
	      peticion , 
              pos  =  0,
              rama ;
              MPI_Status status ;
   
   for( unsigned int i=0 ; i < ITERS*2 ; i++ )
   {  
      if ( pos==0 )  rama = 0 ;      // el consumidor no puede consumir       
      else if (pos==TAM) rama = 1 ;  // el productor no puede producir
                    
      else               // ambas guardas son ciertas
      {
         // leer 'status' del siguiente mensaje (esperando si no hay)
         MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
         
         // calcular la rama en función del origen del mensaje
         if ( status.MPI_TAG == Productor ) 
            rama = 0 ; 
         else 
            rama = 1 ;
      }
      switch(rama)
      {
         case 0:
	    /* Recibe mensajes de cualquier proceso (MPI_ANY_SOURCE) con la etiqueta Productor. Así
		se esperará a que cualquiera de los productores produzca un ítem. */
            MPI_Recv( &value[pos], 1, MPI_INT, MPI_ANY_SOURCE, Productor, MPI_COMM_WORLD, &status ); 
            cout << "Buffer recibe " << value[pos] << " de Productor " << status.MPI_SOURCE << endl << flush;  
            pos++;
            break;
         case 1:
	    /* Espera mensajes de cualquier proceso (MPI_ANY_SOURCE) con la etiqueta Consumidor. Así
		se esperará a que cualquiera de los consumidores pida un ítem. */
            MPI_Recv( &peticion, 1, MPI_INT, MPI_ANY_SOURCE, Consumidor, MPI_COMM_WORLD, &status );
            MPI_Ssend( &value[pos-1], 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            cout << "Buffer envía " << value[pos-1] << " a Consumidor " << status.MPI_SOURCE << endl << flush;  
            pos--;
            break;
      }     
   }
}   
   
// ---------------------------------------------------------------------

void consumidor( int rank )
{
   int         value,
               peticion = 1;
   float       raiz ;
               MPI_Status  status ;
 
   for (unsigned int i=0; i<ITERS/NumConsumidores; i++)
   {
      MPI_Ssend( &peticion, 1, MPI_INT, Buffer, Consumidor, MPI_COMM_WORLD );       
      MPI_Recv ( &value, 1,    MPI_INT, Buffer, 0, MPI_COMM_WORLD, &status );
      cout << "Consumidor " << rank << " recibe valor " << value << " de Buffer " << endl << flush ;
      
      // espera bloqueado durante un intervalo de tiempo aleatorio 
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
      
      raiz = sqrt(value) ;
   }
}
// ---------------------------------------------------------------------

int main(int argc, char *argv[]) 
{
   int rank,size; 
   
   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   
   // inicializa la semilla aleatoria:
   srand ( time(NULL) );
   
   // comprobar el número de procesos con el que el programa 
   // ha sido puesto en marcha (debe ser 3)
   if ( size != NumProcesos ) 
   {
      cout<< "El numero de procesos debe ser " << NumProcesos << endl;
      return 0;
   } 
   
   // verificar el identificador de proceso (rank), y ejecutar la
   // operación apropiada a dicho identificador
   if ( rank < Buffer ) 
      productor(rank);
   else if ( rank == Buffer ) 
      buffer();
   else 
      consumidor(rank);
   
   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}

