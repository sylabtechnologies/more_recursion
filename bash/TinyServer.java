/**
 ** to use: http://n.n.n.n/0 or file number
 * 
 * 1. https://github.com/patniemeyer/learningjava/tree/master/examples/ch13
 * 
 * 2. the executor/threadpool construct =
 * == that parallel (aka concurrent) thread exection, #N
 * 
 * 3. just like w/ neat.java = JUST LIST MAJOR PROCEDURAL STEPS AND OBJECTS
 * (like read line, separate into parts, implement an algo, whoa!)
 * 
 */
package tinyserver;

import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.*;
import java.util.concurrent.*;

public class TinyServer
{
    public static void main( String argv[] ) throws IOException {
        Executor executor = Executors.newFixedThreadPool(3);
        ServerSocket ss = new ServerSocket( 80 );
        while ( true )
            executor.execute( new TinyHttpConnection( ss.accept() ) );
    }
    
}

class TinyHttpConnection implements Runnable
{
    Socket client;
//     final static String MYDIR = "C:\\Users\\Dennis\\Desktop\\CSharp\\NETAcad";
    final static String MYDIR = "C:\\Users\\Dennis\\Desktop\\Hack!\\sync";
    private static File[] workDir;
    
    /// restrict! (or delete all refs)
    private final static String RESTRICTED2 = "10.0.0.194";
  
    TinyHttpConnection ( Socket client ) throws SocketException
    {
      this.client = client;
    }
    
    synchronized private void printFile(int code, OutputStream out) throws IOException
    {
        if (code != 0)
        {
            code = code - 1;
            
            File file = workDir[code];
            FileInputStream fis = new FileInputStream(MYDIR + "\\" + file.getName());
            byte [] data = new byte [ 64*1024 ];
            for(int read; (read = fis.read( data )) > -1; )
                out.write( data, 0, read );
            out.flush();
            out.close();
            return;
        }
        
        for(File f : workDir)
        {
            String name = f.getName();
            out.write(name.getBytes());
            out.write(32);
            
            String timeStamp = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss").format(new Date(f.lastModified()));
            out.write(timeStamp.getBytes());
            
            out.write(13);
            out.write(10);
        }
        
        out.flush();
    }
    
    @Override
    public void run()
    {
        try
        {
            String userIP = client.getInetAddress().getHostAddress();
            if (!userIP.equals(RESTRICTED2))
            {
                System.out.println("reject " + userIP);
                return;
            }
            
            workDir = new File(MYDIR).listFiles();
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream(), "8859_1"));
            OutputStream out = client.getOutputStream();
            PrintWriter pout = new PrintWriter(new OutputStreamWriter(out, "8859_1"), true);
            String[] request = in.readLine().split(" ");
            System.out.println( "Request: " + request[1]);

            if (request[1].equals("/0"))
            {
                printFile(0, out);
            }
            else
            {
                // System.out.println( "Request: " + request[1].substring(1));
                int i = Integer.parseInt(request[1].substring(1));

                if (i > 0 && i <= workDir.length) printFile(i, out);
            }

            out.close();
            client.close();
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
    }
    
}

