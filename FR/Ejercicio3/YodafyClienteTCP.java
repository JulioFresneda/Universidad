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
		
		String buferEnvio;
		String buferRecepcion;
		
		String host="localhost";

		int port=8989;
		
		Socket socketServicio=null;
		
		try {
		
			socketServicio=new Socket (host,port);
		
			PrintWriter outPrinter = new PrintWriter(socketServicio.getOutputStream(),true);
			BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));	
					

			buferEnvio="Al monte del volcan debes ir sin demora";
			outPrinter.println(buferEnvio);
	
			buferRecepcion = inReader.readLine();


			System.out.println("Recibido: ");
			System.out.println(buferRecepcion);


			socketServicio.close();
			

		} catch (UnknownHostException e) {
			System.err.println("Error.");
		} catch (IOException e) {
			System.err.println("Error.");
		}
	}
}
