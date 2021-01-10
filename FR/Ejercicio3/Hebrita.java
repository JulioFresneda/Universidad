import java.net.Socket;

public class Hebrita extends Thread{
	 
	 ProcesadorYodafy procesador;

	 Hebrita(Socket socketConexion){
	 	procesador=new ProcesadorYodafy(socketConexion);
	 }
	
	 public void run() {
		 procesador.procesa();
	 }
}
