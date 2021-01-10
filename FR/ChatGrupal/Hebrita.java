/*
  Práctica de Fundamentos de Redes - Chat Grupal usando sockets

    Julio Antonio Fresneda García - 49215154F - juliofresnedag@correo.ugr.es
    Santiago Vidal Martínez - 77138012Z - sanviflo@correo.ugr.es

*/


import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

import java.net.Socket;


// Clase Hebrita
class Hebrita extends Thread
{
  private Socket socket;
  private String nick;

  private BufferedReader inReader;
  private PrintWriter outPrinter;

  // Constructor
  public Hebrita( Socket _socket )
  {
      socket = _socket;
  }


  public void run() {

    try
    {

        inReader = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );
        outPrinter = new PrintWriter( socket.getOutputStream(), true );


        while( true )
        {
          // Pedimos el nick
          outPrinter.println("enviarnick");

          // Leemos el nick que el cliente haya escrito
          nick = inReader.readLine();

          // Si el nick introducido no es nulo y no está en los antiguos nicks, se agrega y el nuevo cliente se conectará
          if( nick != null && !ServidorChatGrupal.nicks.contains( nick )) {
              ServidorChatGrupal.nicks.add( nick );
              break;
          }

          if( nick == null ) return;

        }

        // El nick está aceptado, enviamos confirmación
        outPrinter.println("nickok");

        // Añadimos el printwriter al array, para que pueda chatear
        ServidorChatGrupal.printWrites.add(outPrinter);

        while( true )
        {
          // Leemos el mensaje de un cliente
          String input = inReader.readLine();

          if( input == null ) return;

          // Enviamos el mensaje recibido de ese cliente a cada uno de los clientes (incluido el mismo que lo ha enviado)
          for (PrintWriter pw : ServidorChatGrupal.printWrites) {
              pw.println("mensaje " + nick + ": " + input);
          }

        }

    } catch (IOException e) {}


  }
}
