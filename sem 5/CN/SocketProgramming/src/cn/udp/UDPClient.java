package cn.udp;

//UDPClient.java
import java.net.*;

public class UDPClient {
 public static void main(String[] args) {
     try {
         DatagramSocket clientSocket = new DatagramSocket();
         InetAddress IPAddress = InetAddress.getByName("localhost");

         byte[] sendData = "Hello from UDP Client!".getBytes();
         byte[] receiveData = new byte[1024];

         DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
         clientSocket.send(sendPacket);

         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
         clientSocket.receive(receivePacket);

         String reply = new String(receivePacket.getData()).trim();
         System.out.println("Server says: " + reply);

         clientSocket.close();
     } catch (Exception e) {
         e.printStackTrace();
     }
 }
}
