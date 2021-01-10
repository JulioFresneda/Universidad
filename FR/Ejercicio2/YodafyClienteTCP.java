//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class YodafyClienteTCP {

	public static void main(String[] args) {


		// Nombre del host donde se ejecuta el servidor:
		String host="localhost";
		// Puerto en el que espera el servidor:
		int port=9009;

		// Socket para la conexión TCP
		Socket socketServicio=null;

		try {
			// Creamos un socket que se conecte a "host" y "port":
			socketServicio = new Socket( host, port );


			// Usamos PrintWriter
			PrintWriter outPrinter = new PrintWriter( socketServicio.getOutputStream(),true );
			String cadena = "Al monte del volcán debes ir sin demora";
			outPrinter.println( cadena );


			// Enviamos el array por el outputStream;
			BufferedReader inReader = new BufferedReader( new InputStreamReader( socketServicio.getInputStream() ) );
			String cadenaRecibida = inReader.readLine();


			// Mostremos la cadena de caracteres recibidos:
			System.out.println("Recibido: ");
			System.out.print( cadenaRecibida );

			// Una vez terminado el servicio, cerramos el socket (automáticamente se cierran
			// el inpuStream  y el outputStream)
			socketServicio.close();

			// Excepciones:
		} catch (UnknownHostException e) {
			System.err.println("Error: Nombre de host no encontrado.");
		} catch (IOException e) {
			System.err.println("Error de entrada/salida al abrir el socket.");
		}
	}
}
