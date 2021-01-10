/*
  Práctica de Fundamentos de Redes - Chat Grupal usando sockets

    Julio Antonio Fresneda García - 49215154F - juliofresnedag@correo.ugr.es
    Santiago Vidal Martínez - 77138012Z - sanviflo@correo.ugr.es

*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import java.net.Socket;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.ImageIcon;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


// Clase del cliente
public class ClienteChatGrupal
{
    // Creamos la interfaz gráfica
    JFrame jframe = new JFrame("Chat Grupal");

    JTextField jtextField = new JTextField(45);
    JTextArea jtextArea = new JTextArea(10, 45);

    BufferedReader inReader;
    PrintWriter outPrinter;



    public ClienteChatGrupal()
    {
        // Lanzamos la interfaz gráfica
        jframe.getContentPane().add( new JLabel(new ImageIcon("./cabecera.png")), "North" );
        jframe.getContentPane().add( new JScrollPane( jtextArea ), "Center" );
        jframe.getContentPane().add( jtextField, "South" );
        jframe.pack();

        jtextArea.setEditable( false );

        // Este método capta lo que escribimos en la interfaz
        jtextField.addActionListener(
          new ActionListener()
          {
            public void actionPerformed( ActionEvent e )
            {
                outPrinter.println( jtextField.getText() );
                jtextField.setText("");
            }
          }
        );


    }



    // Ejecutamos la hebra
    private void run() throws IOException
    {

      // Captamos la ip a la que nos vamos a conectar, escrita desde la interfaz
      String ip = JOptionPane.showInputDialog( jframe, "Introduce IP del servidor a conectar:", "Introduciendo IP:", JOptionPane.QUESTION_MESSAGE);

      // Creamos un socketConexion, lo conectamos al puerto 8989 (puerto del servidor)
      Socket socketConexion = new Socket(ip, 8989);

      outPrinter = new PrintWriter( socketConexion.getOutputStream(), true );
      inReader = new BufferedReader( new InputStreamReader( socketConexion.getInputStream() ) );


      // Aqui recibimos en bucle información del servidor
      while( true )
      {

          String readLine = inReader.readLine();

          // Si el mensaje recibido empieza con "enviarnick", se lanza una ventana pidiendo el nick
          if( readLine.startsWith("enviarnick"))
          {
              outPrinter.println( JOptionPane.showInputDialog( jframe, "Escribe tu nick:", "Introduciendo nick:",  JOptionPane.PLAIN_MESSAGE) );
          }
          // Si el mensaje recibido empieza con "nickok", significa que el nick enviado es válido y podemos empezar a enviar mensajes
          else if( readLine.startsWith("nickok") )
          {
              jtextField.setEditable(true);
          }
          // Si el mensaje recibido desde el servidor (el que haya enviado otro cliente) empieza con "mensaje", el mensaje se carga en la interfaz para que lo podamos ver
          else if (readLine.startsWith("mensaje"))
          {
              jtextArea.append(readLine.substring(8) + "\n");
          }

      }
    }


    public static void main(String[] args) throws Exception
    {
      ClienteChatGrupal cliente = new ClienteChatGrupal();
      cliente.jframe.setVisible( true );
      cliente.run();
    }
}
