import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
public class YodafyServidorUDP {

	public static void main(String[] args) {

		int puerto=9000;
		InetAddress direccion;

		byte[] bufer = new byte[256];

		DatagramPacket paquete=null;
		DatagramPacket paqueteEnvio=null;
		DatagramSocket socketServidor=null;

		try {
			socketServidor = new DatagramSocket(puerto);
			
			do{
				paquete = new DatagramPacket(bufer, bufer.length);
				socketServidor.receive(paquete);			

				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServidor,paquete);
				paqueteEnvio=procesador.procesa();				
				socketServidor.send(paqueteEnvio);
				

			}while(true);

		}catch (UnknownHostException e) {
			System.err.println("Error.");
		} catch (IOException e) {
			System.err.println("Error.");
		}
		socketServidor.close();

	}

}


