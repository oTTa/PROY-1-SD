
import java.net.*;
import java.io.*;
import java.util.Calendar;
import java.util.GregorianCalendar;
public class SocketServidor
{    
    public static void main (String [] args)
    {
	  if (args.length==0){
        	System.out.println("debes introducir un puerto para la comunicación.");
        	System.exit(0);
	  }
        // Se instancia la clase principal para que haga todo lo que tiene que
        // hacer el ejemplo
        
        new SocketServidor(args[0]);
    }
    

    public SocketServidor(String puerto)
    {
        try
        {
            // Se crea un socket servidor atendiendo a un determinado puerto.
        
            ServerSocket socket = new ServerSocket (Integer.parseInt(puerto));
            
            // Se acepata una conexi�n con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            System.out.println ("Esperando cliente");
            Socket cliente = socket.accept();
            System.out.println ("Conectado con cliente de " + cliente.getInetAddress());

            /* Se obtiene un stream de lectura/escritura para tipos de datos simples */
             DataInputStream entrada = new DataInputStream (cliente.getInputStream());
             DataOutputStream salida = new DataOutputStream (cliente.getOutputStream());
            
            // setSoLinger() a true hace que el cierre del socket espere a que
            // el cliente lea los datos, hasta un máximo de 10 segundos de espera.
            // Si no ponemos esto, el socket se cierra inmediatamente y si el 
            // cliente no ha tenido tiempo de leerlos, los datos se pierden.
            cliente.setSoLinger (true, 10);
            
            boolean continuar=true;
            String pedido;
            while (continuar){
	      pedido = entrada.readUTF();
	      switch (pedido){
	      case "1": {salida.writeUTF(obtenerHora());break;}
	      case "2": {salida.writeUTF(obtenerFecha());break;}
	      case "3": {salida.writeUTF(obtenerNombreMaquina());break;}
	      case "4": {salida.writeUTF(obtenerCantUsuariosLogueados());break;}
	      case "5": {continuar=false;break;}
	      default : {salida.writeUTF("opcion invalida");break;}
              }
            }
             
         
            // Se cierra el socket con el cliente.
            cliente.close();
            
            // Se cierra el socket encargado de aceptar clientes. 
            socket.close();
            System.out.println ("Finalizo la conexión");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
    
    private String obtenerHora(){
		Calendar calendario = new GregorianCalendar();
		return(calendario.get(Calendar.HOUR_OF_DAY) + ":" + calendario.get(Calendar.MINUTE) + ":" + calendario.get(Calendar.SECOND));
    }
    
    private String obtenerFecha(){
           Calendar calendario = new GregorianCalendar();
	   return(calendario.get(Calendar.DAY_OF_MONTH) + "/" + calendario.get(Calendar.MONTH) + "/" + calendario.get(Calendar.YEAR));
    }
    
    private String obtenerNombreMaquina(){
      String hostname = "Unknown";
      try{
	hostname=InetAddress.getLocalHost().getHostName();
      }
      catch (UnknownHostException ex)
      {
	System.out.println("Problema al obtener el hostname");
      }
      return hostname;
    }
    
    private String obtenerCantUsuariosLogueados(){
    int lNumeroLineas = 0;
    try {
            Process p = Runtime.getRuntime().exec("who");
            p.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line=reader.readLine();

            while (line != null) {    
                lNumeroLineas++;
                line = reader.readLine();
            }

        }
        catch(IOException e1) {e1.printStackTrace();}
        catch(InterruptedException e2) {e2.printStackTrace();}

     return (""+lNumeroLineas);
    }
    
}

