import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.lang.String;
import java.util.ArrayList;


public class Servidor {

	public static void main(String[] args) {


		int port=8989;
  	ArrayList<String> buffers = new ArrayList();
    ArrayList<String> users = new ArrayList();
		int bytesLeidos = 0;
    int numClientes = 0;

		ServerSocket serverSocket;

		try {

			serverSocket = new ServerSocket(port);

			Socket socketConexion = null;

      socketConexion = serverSocket.accept();
      BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
      users.add( inReader.readLine() );

			do {
				try {
				


          numClientes++;

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
