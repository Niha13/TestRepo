import java.io.*;
import java.net.Socket;

public class SocketJa
{
	
	BufferedReader reader;
	BufferedReader readInput;
	
	public void establishConnection()
	{
		try{
			Socket s = new Socket("127.0.0.1",3550);
			InputStreamReader stream = new InputStreamReader(s.getInputStream());
			reader = new BufferedReader(stream);
			Thread t = new Thread(new IncomingMessageReader());
			t.start();
			OutputStream out = s.getOutputStream();
			String mensaje = "";
			readInput =  new BufferedReader(new InputStreamReader(System.in));
			while(!mensaje.equals("exit"))
			{
				mensaje = readInput.readLine()+"\n";
				out.write(mensaje.getBytes());
				out.flush();
			}
			System.exit(0);
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}
	
	public static void main (String args[]) throws Exception 
	{	
		SocketJa client = new SocketJa();
		while (true)
		{
			new BufferedReader(new InputStreamReader(System.in)).read();
			client.establishConnection();
		}
	}
	
	class IncomingMessageReader implements Runnable
	{
		public void run() 
		{
			String line = null;
			try {
					while((line = reader.readLine())!= null)
					{
					System.out.println("Incoming message : " + line);
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
	}
	
}