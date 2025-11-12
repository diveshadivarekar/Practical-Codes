package cn.tcp;
import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) {
        try {
            ServerSocket server = new ServerSocket(8080);
            System.out.println("Server waiting for client...");
            Socket socket = server.accept();
            System.out.println("Client connected!");

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            String msg = in.readLine();
            System.out.println("Client says: " + msg);
            out.println("Hello from TCP Server!");

            socket.close();
            server.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
