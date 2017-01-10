/*
 *     Daytime.java
 *
 *     Usage: java Daytime ip_adrress port_number
 *
 *     Gets and displays the time of a remote server
 *
 *     ip_address: IP address for a remote server
 *     port_number: Port number
 *
 *     Copyright (C) 2006 Katsuhisa Maruyama (maru@cs.ritsumei.ac.jp)
 */

import java.net.Socket;
import java.io.InputStream;
import java.io.IOException;

public class Daytime {

    static final int MAX_BUF_SIZE = 256;

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("java Daytime ip_adrress port_number");
            System.exit(1);
        }
        Daytime daytime = new Daytime();
        daytime.getDaytime(args[0], Integer.parseInt(args[1]));
    }

    public void getDaytime(String host, int port) {
        InputStream is = null;

        try {
            byte[] buf = new byte[MAX_BUF_SIZE];
            Socket s = new Socket(host, port);
            is = s.getInputStream();

            int n = is.read(buf);
            System.out.write(buf, 0, n);

            is.close();

        } catch (IOException e) {
            System.err.println("error: " + e.getMessage());
            System.exit(1);
        }
    }
}
