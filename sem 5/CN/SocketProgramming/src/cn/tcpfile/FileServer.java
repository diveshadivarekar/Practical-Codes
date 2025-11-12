package cn.tcpfile;

import java.io.*;
import java.net.*;

public class FileServer {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(5000);
            System.out.println("Server waiting for file...");

            Socket socket = serverSocket.accept();
            System.out.println("Client connected!");

            // Input stream to receive file
            InputStream in = socket.getInputStream();
            FileOutputStream fos = new FileOutputStream("received_file.txt");
            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            
            System.out.println("Saving file to: " + new File("received_file.txt").getAbsolutePath());
            System.out.println("File received successfully and saved as received_file.txt");

            fos.close();
            socket.close();
            serverSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
