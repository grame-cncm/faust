package com.faust;

import com.illposed.osc.OSCListener;
import com.illposed.osc.OSCPortIn;

import java.net.SocketException;

public class Osc{
    public static int port;
    private static OSCPortIn receiver;

    public static Boolean init(int inPort){
        Boolean success = true;
        port = inPort;
        try {
            receiver  = new OSCPortIn(port);
        } catch (SocketException e) {
            success = false;
            e.printStackTrace();
        }
        return success;
    }

    public static void addListener(String address, OSCListener listener){
        receiver.addListener(address, listener);
    }

    public static void startListening(){
        receiver.startListening();
    }

    public static void stopListening(){
        receiver.stopListening();
    }
}
