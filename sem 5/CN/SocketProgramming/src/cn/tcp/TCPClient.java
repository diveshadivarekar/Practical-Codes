package cn.tcp;
import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 8080);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            out.println("Hello from TCP Client!");
            String msg = in.readLine();
            System.out.println("Server says: " + msg);

            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
