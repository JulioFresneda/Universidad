/*#################################################################################

	Julio Fresneda - juliofresnedag@correo.ugr.es - 49215154F

	Ejercicio: Barbería

##################################################################################*/


import monitor.*;
import java.util.Random;



// Clase Barbería, usando AbstractMonitor
class Barberia extends AbstractMonitor
{

	private Condition sala = makeCondition();
	private Condition silla = makeCondition();
	private Condition barbero = makeCondition();
	
	// Constructor
	public Barberia()
	{
		
	}

	// Método para avisar al barbero 
	public void cortarPelo()
	{
		enter();
		

		if( !barbero.isEmpty() )
			System.out.println("Cliente despierta al barbero.\n");
		barbero.signal();							
		
		sala.await();								// Esperando en la sala		
		System.out.println("Cliente se sienta en la silla.\n");										
		silla.await();								// Afeitándose en la silla...
		System.out.println("Fin afeitado del cliente. Sale de la barbería.\n\n");		
		
		leave();
	}

	// Método para que pase el siguiente cliente
	public void siguienteCliente()
	{
		enter();
		
		  if (sala.isEmpty() && silla.isEmpty()){			// Si la barbería está vacía, el barbero empieza a dormir
			System.out.println("Barbero durmiendo.\n");
			barbero.await();
		  }
		
		System.out.println("Barbero llama a cliente para cortarle la barba.\n");
		sala.signal();	// Llamando al cliente
			
		leave();
	}

	// Método para avisar al cliente de que ha sido pelado
	public void finCliente()
	{
		enter();

		silla.signal();	 // El cliente ya se ha afeitado
				
		leave();

	}
	
}

// Clase del cliente
class Cliente implements Runnable{

	public Thread thr;
	private Barberia barberia;
	public Cliente( Barberia b ){
		barberia = b;
		thr = new Thread( this, "Cliente");
	}
	
	public void run()
	{
	try{
		while( true ){
			barberia.cortarPelo();	// El cliente espera (si procede) y se corta el pelo
			gastarTiempo.dormir(2000);	// El cliente está fuera de la barbería un tiempo
		}
	}
	catch(Exception e)
	{
            System.err.println("Excepcion en clase cliente: " + e);
        }
	}
}



// Clase del barbero
class Barbero implements Runnable{

	public Thread thr;
	private Barberia barberia;
	public Barbero( Barberia b ){
		barberia = b;
		thr = new Thread( this, "Barbero");
	}
	
	public void run()
	{
	try{
		while( true )
		{	
			barberia.siguienteCliente();
			gastarTiempo.dormir(2500);	// El barbero está cortando el pelo
			barberia.finCliente();
		
		}
		
	}
	catch(Exception e)
        {
            System.err.println("Excepcion en clase barbero: " + e);
        }
	}
}



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
            System.err.println("sleep interumpido en 'gastarTiempo.dormir()'");
        }
    }
}

// Main

class Ejercicio{

	public static void main( String[] args )
	{
		int num_clientes = 5;
		if( args.length != 0 )
			num_clientes = Integer.parseInt(args[0]);
	
		Barberia barberia = new Barberia();
		Barbero barbero = new Barbero(barberia);
		Cliente[] clientes = new Cliente[num_clientes];
		
		for( int i=0; i<num_clientes; i++ ){		
			clientes[i] = new Cliente(barberia);
		}

		barbero.thr.start();
		for( int i=0; i<num_clientes; i++ ){
			clientes[i].thr.start();
		}
	}

}
		
	










		





































		

