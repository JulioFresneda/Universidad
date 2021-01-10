//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ProcesadorYodafy {


	private Socket socketServicio;

	private InputStream inputStream;
	private OutputStream outputStream;
	
	private Random random;
	
	public ProcesadorYodafy(Socket socketServicio)
	{
		this.socketServicio=socketServicio;
		random=new Random();
	}
	
	

	void procesa()
	{
		
		String datosRecibidos;
		
		
		try {
			PrintWriter outPrinter = new PrintWriter(socketServicio.getOutputStream(),true);
			BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));	



			datosRecibidos = inReader.readLine();

			String respuesta=yodaDo(datosRecibidos);
			outPrinter.println(respuesta);
			
			
			
		} catch (IOException e) {
			System.err.println("Error.");
		}

	}


	private String yodaDo(String peticion) {

		String[] s = peticion.split(" ");
		String resultado="";
		
		for(int i=0;i<s.length;i++){
			int j=random.nextInt(s.length);
			int k=random.nextInt(s.length);
			String tmp=s[j];
			
			s[j]=s[k];
			s[k]=tmp;
		}
		
		resultado=s[0];
		for(int i=1;i<s.length;i++){
		  resultado+=" "+s[i];
		}
		
		return resultado;
	}
}
