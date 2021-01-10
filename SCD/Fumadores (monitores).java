/*#################################################################################

	Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F

	Ejercicio: Estanquero y fumadores

##################################################################################*/


import monitor.*;
import java.util.Random;



// Clase Estanco, usando AbstractMonitor
class Estanco extends AbstractMonitor
{

	private Condition sem_estanquero = makeCondition();
	private Condition[] sem_fumador = new Condition[3];
	private int aux;

	// Constructor
	public Estanco()
	{
		this.aux = -1;
		for( int i=0; i<3; i++ ){
			sem_fumador[i] = makeCondition();
		}
	}

	// Método para obtener ingrediente, usado por los fumadores
	public void obtenerIngrediente( int ing )
	{
		enter();

		if( ing != aux ){
			sem_fumador[ing].await();
		}

		System.out.println("Fumador " + ing + " ha cogido el ingrediente\n");

		aux = -1;
		sem_estanquero.signal();

		leave();
	}

	// Método para poner ingredente en la mesa, usado por el estanquero
	public void servirIngrediente( int ing )
	{
		enter();

		aux = ing;

		System.out.println("El estanquero ha puesto el ingrediente " + ing + " en la mesa.\n");
		
		sem_fumador[ing].signal();

		leave();
	}

	// Método para que el estanquero espere que el ingrediente puesto en la mesa haya sido recogido
	public void esperarMesaVacia()
	{
		enter();

		if( aux != -1 )	
			sem_estanquero.await();

		leave();

	}

}



// Clase Estanquero
class Estanquero implements Runnable{

	private Estanco estanco;
	public Thread thr;
	
	// Constructor
	public Estanquero( Estanco e )
	{
		estanco = e;
		thr = new Thread(this, "estanquero");

	}


	// Ejecución del estanquero
	public void run()
	{
	try{
		int ingrediente;
		while( true )
		{
			ingrediente = (int) (Math.random() * 3.0);
			estanco.servirIngrediente(ingrediente);
			estanco.esperarMesaVacia();
		
		}
		
	}
	catch(Exception e)
        {
            System.err.println("Excepcion en estanquero: " + e);
        }
	}
}


// Clase Fumador
class Fumador implements Runnable{

	private Estanco estanco;
	private int ingrediente;
	public 	Thread thr;
	
	// Constructor
	public Fumador( Estanco e, int ing )
	{
		estanco = e;
		ingrediente = ing;
		thr = new Thread( this, "fumador " + ing );
	}

	// Ejecución del fumador
	public void run()
	{
	try{
		while( true )
		{
			estanco.obtenerIngrediente( ingrediente );
			gastarTiempo.dormir(1000); // Fumando...
		}
	}
	catch(Exception e)
        {
            System.err.println("Excepcion en fumador: " + e);
        }
	}
}


// Clase auxiliar para hacer un sleep
class gastarTiempo
{
    static Random genAlea = new Random();
    static void dormir(int milisecsMax)
    {
        try
        {
            Thread.sleep(genAlea.nextInt(milisecsMax));
        }
        catch(InterruptedException e)
        {
            System.err.println("sleep interumpido en 'aux.dormir_max()'");
        }
    }
}


// Main

class Ejercicio{

	public static void main( String[] args )
	{

		Estanco estanco = new Estanco();
		Estanquero estanquero = new Estanquero( estanco );
		Fumador[] fumadores = new Fumador[3];
		fumadores[0] = new Fumador(estanco, 0);
		fumadores[1] = new Fumador(estanco, 1);
		fumadores[2] = new Fumador(estanco, 2);

		fumadores[0].thr.start();
		fumadores[1].thr.start();
		fumadores[2].thr.start();
		estanquero.thr.start();
		

	}

}
		
	










		





































		

