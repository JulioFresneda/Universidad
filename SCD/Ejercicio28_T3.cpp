/*##################################################################################
+										   +
+		Julio A. Fresneda García  -  juliofgx17@gmail.com                  +
+										   +
###################################################################################*/


// Ejercicio 28 Tema 3


#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define maestro 6
#define peticion 99
#define respuesta 77
#define procesos_necesarios 3
#define finalizado 3333

using namespace std;

void Maestro(int rank, int size);
void Cliente(int rank, int size);

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;
   
   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   
   if( size!=7)
   {
      if( rank == 0) 
         cout<<"El numero de procesos debe ser 7" << endl << flush ;
      MPI_Finalize( ); 
      return 0; 
   }
   
   if( rank == 6 )
	Maestro(rank,size);
   else Cliente(rank,size); 
   
   MPI_Finalize( );
   return 0;
}  
// ---------------------------------------------------------------------



void Cliente(int rank, int size){
	MPI_Status status;
	int buf;
	int x = 1;
	while( true ){

		MPI_Send( &x, 1, MPI_INT, maestro, peticion, MPI_COMM_WORLD );			// Se envía una señal
		cout << "Señal enviada desde el cliente " << rank << endl << flush;		
		MPI_Recv( &buf, 1, MPI_INT, maestro, respuesta, MPI_COMM_WORLD, &status );	// Se ha recibido una señal, ya hay 3 clientes listos
		cout << "Proceso " << rank << " trabajando... " << endl << flush;
		sleep(3);
		MPI_Ssend( &x, 1, MPI_INT, maestro, finalizado, MPI_COMM_WORLD );		/* El cliente ha terminado de trabajar.
												   Se usa para que se muestren los mensajes en el 
												   orden correcto en pantalla */
	}
}



void Maestro(int rank, int size){
	MPI_Status status;
	int buf;
	int p = 0;
	int source[3];
	
	while( true ){
	
		MPI_Recv( &buf, 1, MPI_INT, MPI_ANY_SOURCE, peticion, MPI_COMM_WORLD, &status );	// Recibe mensaje (cliente listo).
		source[p] = status.MPI_SOURCE;								// Se guarda el origen del mensaje (rank).
		p+=buf;											// Equivale a p++
		

		if( p == procesos_necesarios ){								// Si ya hay 3 clientes listos
			p = 0;
			cout << endl << "Listo para empezar... " << endl << flush;
			sleep(2);
			for( int i=0; i<3; i++ ){
				MPI_Ssend( NULL, 0, MPI_INT, source[i], respuesta, MPI_COMM_WORLD );
													/* Envía un mensaje a los tres clientes que
													   llegaron primero, indicándoles que ya 
													   pueden empezar a trabajar. */
				
			}
			cout << "Reseteando valores " << endl << flush;					/* Espera a que los 3 clientes acaben de 
													   trabajar. Se usa para que no salgan los
													   mensajes en pantalla en orden incorrecto. */
			for( int i=0; i<3; i++){							
				MPI_Recv( &buf, 1, MPI_INT, MPI_ANY_SOURCE, finalizado, MPI_COMM_WORLD, &status );
				p+=buf;
			}
			
			p = 0;
		}

	}
}





























    
