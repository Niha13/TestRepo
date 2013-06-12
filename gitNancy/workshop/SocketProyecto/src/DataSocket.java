import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.io.PrintWriter;
import java.io.*;

public class DataSocket
{
  private Socket socket;
  private InputStreamReader stream;
  private BufferedReader reader;
  private PrintWriter writer;
  private String str;
  private String msg;
  
  public DataSocket()
  {
    try
    {
      socket = new Socket("127.0.0.1", 3550);
      stream = new InputStreamReader(socket.getInputStream());
      reader = new BufferedReader(stream);
      writer = new PrintWriter(socket.getOutputStream(),true);
    }
    catch(IOException e)
    {
      System.out.println("ERROR: The connection can not be established it");
      e.printStackTrace();
    }
  }
  
  private void communicateWithTheServer()
  {
    try
    {
      msg = "bien";
      writer.println("2345");
      System.out.println("Indicaste a Socket(c) tu IP");
      str = reader.readLine();
      System.out.println("Recibiste del servidor: "+str);
      writer.close();
      reader.close();
      socket.close();
    }
    catch(IOException e)
    {
      System.out.println("ERROR: The connection can not be established it");
      e.printStackTrace();
    }
  }
  
  public static void main(String[] args)
  {
  
    DataSocket test = new DataSocket();
    test.communicateWithTheServer();
  }
}

