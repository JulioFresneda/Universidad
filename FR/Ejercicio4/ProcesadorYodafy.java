//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Random;
import java.net.UnknownHostException;


public class ProcesadorYodafy {


	InetAddress direccion;

	private DatagramSocket socketServicio;	
	private DatagramPacket paquete;
	private DatagramPacket paqueteEnvio;

	private Random random;
	
	byte[] bufer = new byte[256];

	public ProcesadorYodafy(DatagramSocket socketServicio,DatagramPacket paquete) {
		
		this.socketServicio=socketServicio;
		this.paquete=paquete;
		random=new Random();
	}
	
	
	DatagramPacket procesa()
	{
		
		String datosRecibidos;
		
		
		try {
			direccion = InetAddress.getByName("localhost");

			datosRecibidos = new String(paquete.getData());
			String respuesta=yodaDo(datosRecibidos);

			System.out.println(respuesta);
			paqueteEnvio = new DatagramPacket(respuesta.getBytes(), respuesta.getBytes().length, direccion, paquete.getPort());

			
		}catch (UnknownHostException e) {
			System.err.println("Error.");
		}
		return paqueteEnvio;

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
