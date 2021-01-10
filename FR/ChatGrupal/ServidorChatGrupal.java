/*
  Práctica de Fundamentos de Redes - Chat Grupal usando sockets

    Julio Antonio Fresneda García - 49215154F - juliofresnedag@correo.ugr.es
    Santiago Vidal Martínez - 77138012Z - sanviflo@correo.ugr.es

*/


import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import java.util.ArrayList;

// Clase servidor
public class ServidorChatGrupal
{

    // Aqui se almacenarán los nicks y printwrites de cada cliente
    static ArrayList<String> nicks = new ArrayList<String>();
    static ArrayList<PrintWriter> printWrites = new ArrayList<PrintWriter>();

    private static final int PUERTO = 8989;

    public static void main(String[] args) throws Exception
    {
      // Servidor lanzado
      System.out.println("Servidor OK");

      // Creamos el ServerSocket
      ServerSocket socketServicio = new ServerSocket( PUERTO );

      try
      {
          while( true )
          {
            // Aceptamos la conexión de un nuevo cliente
            new Hebrita( socketServicio.accept() ).start();
          }
      } catch( IOException e ){}

    }

}
