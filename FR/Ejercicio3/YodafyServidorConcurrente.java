import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
public class YodafyServidorConcurrente {

	public static void main(String[] args) {
	

		int port=8989;
		byte []buffer=new byte[256];
		int bytesLeidos=0;

		ServerSocket serverSocket;
		
		try {
			
			serverSocket= new ServerSocket(port);

			Socket socketConexion = null;

			do {
				try {
				 	socketConexion = serverSocket.accept();
				} catch (IOException e) {
				 	System.out.println("Error.");
				}
				new Hebrita(socketConexion).start();
				
				
			} while (true);
			
		} catch (IOException e) {
			System.err.println("Error.");
		}

	}

}


