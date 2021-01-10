#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define CogerTenedor 22 // Números cualquiera
#define SoltarTenedor 33 
#define sentarse 12
#define levantarse 11
#define camarero 10



using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);
void Camarero( int id, int nprocesos);

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;
   
   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   
   if( size!=11)
   {
      if( rank == 0) 
         cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( ); 
      return 0; 
   }
   
   if( rank == 10 )
	Camarero(rank,size);
   else if ((rank%2) == 0)  
      Filosofo(rank,size); // Los pares son Filosofos 
   else 
      Tenedor(rank,size);  // Los impares son Tenedores 
   
   MPI_Finalize( );
   return 0;
}  
// ---------------------------------------------------------------------



void Filosofo( int id, int nprocesos )	
{
   int izq = (id+1) % (nprocesos-1);
   int der = ((id+nprocesos)-2) % (nprocesos-1);   
   MPI_Status status;
   
   while(1)
   {

      // Pide sentarse
      cout << "Filosofo " << id << " solicita sentarse. " << endl << flush;
      MPI_Send( NULL, 0, MPI_INT, camarero, sentarse, MPI_COMM_WORLD );

      // Espera respuesta de que puede sentarse
      MPI_Recv( NULL, 0, MPI_INT, camarero, sentarse, MPI_COMM_WORLD, &status );
    

      // Solicita tenedor izquierdo
      cout << "Filosofo "<<id<< " solicita tenedor izq ..." << izq << endl << flush;      	
      MPI_Ssend(NULL,0,MPI_INT,izq,CogerTenedor,MPI_COMM_WORLD);
      	
      // Solicita tenedor derecho
      cout <<"Filosofo "<<id<< " coge tenedor der ..." << der << endl << flush;  
      MPI_Ssend(NULL,0,MPI_INT,der,CogerTenedor,MPI_COMM_WORLD);      
	  
      cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo
      
      


      // Suelta el tenedor izquierdo
      cout <<"Filosofo "<<id<< " suelta tenedor izq ..." << izq << endl << flush;
      MPI_Ssend(NULL, 0, MPI_INT, izq, SoltarTenedor, MPI_COMM_WORLD);
      
      // Suelta el tenedor derecho
      cout <<"Filosofo "<<id<< " suelta tenedor der ..." << der << endl << flush;      
      MPI_Ssend(NULL, 0, MPI_INT, der, SoltarTenedor, MPI_COMM_WORLD);

     

      // Se levanta
      MPI_Ssend( NULL, 0, MPI_INT, camarero, levantarse, MPI_COMM_WORLD );
      cout << "Filosofo " << id << " se levanta. " << endl << flush;
      


      // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;
      
      // espera bloqueado durante un intervalo de tiempo aleatorio 
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  int buf; 
  MPI_Status status; 
  int Filo;
  
  while( true )
  {
    // Espera un peticion desde cualquier filosofo vecino ...
    MPI_Recv( &buf, 1, MPI_INT, MPI_ANY_SOURCE, CogerTenedor, MPI_COMM_WORLD, &status ); 
    
    
    // Recibe la peticion del filosofo ...
    Filo = status.MPI_SOURCE;    
    cout << "Ten. " << id << " recibe petic. de " << Filo << endl << flush;
    
    // Espera a que el filosofo suelte el tenedor...
    MPI_Recv( &Filo, 1, MPI_INT, Filo, SoltarTenedor, MPI_COMM_WORLD, &status );
    cout << "Ten. " << id << " recibe liberac. de " << Filo << endl << flush; 
  }
}
// ---------------------------------------------------------------------

void Camarero(int id, int nprocesos)
{
  int buf, nfilos = 0;
  MPI_Status status;
  
  while( true )
  {
	if( nfilos < 4 )
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	else MPI_Probe(MPI_ANY_SOURCE, levantarse, MPI_COMM_WORLD, &status);

	if( status.MPI_TAG == sentarse ){
		nfilos++;
		buf = status.MPI_SOURCE;
		MPI_Recv( NULL, 0, MPI_INT, buf, sentarse, MPI_COMM_WORLD, &status );

		MPI_Send( NULL, 0, MPI_INT, buf, sentarse, MPI_COMM_WORLD );

		cout << "Filósofo " << buf << " se sienta. Hay " << nfilos << " sentados en la mesa." << endl << flush;
	}
	if( status.MPI_TAG == levantarse ){
		buf=status.MPI_SOURCE;
		nfilos--;
		MPI_Recv( NULL, 0, MPI_INT, buf, levantarse, MPI_COMM_WORLD, &status );
		cout << "Filósofo " << buf << " se levanta. Hay " << nfilos << " sentados en la mesa." << endl << flush;
	}
  }
}

    
