import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
public class YodafyServidorIterativo extends Thread{




	public static void main(String[] args) {

		// Puerto de escucha
		int port=9099;
		// array de bytes auxiliar para recibir o enviar datos.
		byte []buffer=new byte[256];
		// Número de bytes leídos
		int bytesLeidos=0;

		ServerSocket socketServidor;
		Socket socketServicio = null;



		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			socketServidor = new ServerSocket( port );



				// Aceptamos una nueva conexión con accept()
				socketServicio = socketServidor.accept();


				// Nueva hebra concurrente
				YodafyServidorIterativo concurrente = new YodafyServidorIterativo();
				concurrente.start();


				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServicio);
				procesador.procesa();




		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+port);
		}

	}

}
