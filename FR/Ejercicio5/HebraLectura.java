import java.net.Socket;

public class HebraLectura extends Thread{

	 SocketChat procesador;

	 HebraLectura(Socket socketConexion){
	 	procesador=new SocketChat(socketConexion);
	 }

	 public void run() {
		 procesador.Lectura();
	 }
}
