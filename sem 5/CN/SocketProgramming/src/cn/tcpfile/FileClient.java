package cn.tcpfile;

import java.io.*;
import java.net.*;

public class FileClient {
    public static void main(String[] args) {
        try {
            // Connect to server (change IP if using another computer)
            Socket socket = new Socket("localhost", 5000);
            System.out.println("Connected to server.");

            // File to send (must exist in the same folder)
            File file = new File("test.txt");
            FileInputStream fis = new FileInputStream(file);
            OutputStream out = socket.getOutputStream();

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }

            System.out.println("File sent successfully.");

            fis.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
