import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ClientSocket 
{
	
	public void establishConnection()
	{
		try{
			Socket s = new Socket("127.0.0.1",1405);
			InputStreamReader stream = new InputStreamReader(s.getInputStream());
			BufferedReader reader = new BufferedReader(stream);
			String str = reader.readLine();
			System.out.print("Text received from server: "+str);
			reader.close();
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}
	
	public static void main (String args[]) throws Exception
	{	
		ClientSocket client = new ClientSocket();
		while (true)
		{
			new BufferedReader(new InputStreamReader(System.in)).read();
			client.establishConnection();
		}
	}
}
