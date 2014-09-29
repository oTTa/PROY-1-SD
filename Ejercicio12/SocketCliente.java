import java.net.*;
import java.io.*;
import java.util.Scanner;


public class SocketCliente
 {
     public static void main (String [] args)
     {
         if (args.length<2){
        	System.out.println("debes introducir un <IP,PUERTO>");
        	System.exit(0);
	  }
         new SocketCliente(args[0],Integer.parseInt(args[1]));
     }

     public SocketCliente(String ip, int puerto)
     {
         try
         {
	      //para medir tiempos
	      long time_start, time_end;
              //dato que se le va a pedir al servidor
	      String pedido;
	      String rta;
	      //para leer por pantalla
	      Scanner lector = new Scanner(System.in);
             /* Se crea el socket cliente */
             Socket socket = new Socket (ip,puerto);
             if (socket!=null)
	      System.out.println ("[SD2014]> conectado");
	     else{
	      System.out.println ("[SD2014]> no se pudo establer conexion con el servidor: "+ip+":"+puerto);
	      System.exit(0);
	      }
             /* Se obtiene un stream de lectura/escritura para tipos de datos simples */
             DataInputStream entrada = new DataInputStream (socket.getInputStream());
             DataOutputStream salida = new DataOutputStream (socket.getOutputStream());
             
             //intercambio de informacion
             boolean continuar=true;
             while (continuar){
	      //se le muestras las opciones al cliente y se le pide que eleja una
	      mostrarOpciones();
	      System.out.print("[SD2014]> ");
	      pedido=lector.nextLine();
	      if (pedido.equals("5")){
		  continuar=false;
		  salida.writeUTF(pedido);
	      }
	      else{
		//enviamos el pedido al servidor
		time_start = System.nanoTime();
		salida.writeUTF(pedido);
		rta=entrada.readUTF();
		time_end = System.nanoTime();
		//respues del servidor
		System.out.println ("[SD2014]> Respuesta: " + rta);
		System.out.println ("[SD2014]> Tiempo de respuesta: " + (time_end-time_start) + " ns");
		System.out.println ();
	      }
             }
             System.out.println ("[SD2014]> conexion terminada.");
         }
         catch (java.net.ConnectException a)
         {
	  System.out.println ("[SD2014]> Primero debes iniciar al servidor o verificar que los datos son correctos ");
         }
         catch (Exception e)
         {
             e.printStackTrace();
         }
         
     }
     
     private void mostrarOpciones (){
	System.out.println("[SD2014]> Elija una opcion para obtener los datos del servidor.");
	System.out.println("[SD2014]> - (1) hora del sistema - (2) fecha del sistema - (3) nombre de la maquina - (4) cantidad de usuarios logueados - (5) salir");
     }
}
