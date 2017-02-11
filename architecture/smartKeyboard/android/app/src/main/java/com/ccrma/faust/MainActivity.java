package com.ccrma.faust;

import android.content.Context;
import android.media.midi.MidiDevice;
import android.media.midi.MidiDeviceInfo;
import android.media.midi.MidiManager;
import android.media.midi.MidiOutputPort;
import android.media.midi.MidiReceiver;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.DspFaust.DspFaust;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private DspFaust dspFaust;
    private Context context;
    private RelativeLayout mainLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        context = getApplicationContext();

        startFaustDsp();

        mainLayout = (RelativeLayout) findViewById(R.id.activity_main);

        MultiKeyboard multiKeyboard = new MultiKeyboard(this, dspFaust, null);
        mainLayout.addView(multiKeyboard);


        if(Build.VERSION.SDK_INT >= 23) {
            // MIDI Support
            final FaustMidiReceiver midiReceiver = new FaustMidiReceiver();
            final MidiManager m = (MidiManager) context.getSystemService(Context.MIDI_SERVICE);
            final MidiDeviceInfo[] infos = m.getDevices();

            // opening all the available ports and devices already connected
            for (int i = 0; i < infos.length; i++) {
                final int currentDevice = i;
                m.openDevice(infos[i], new MidiManager.OnDeviceOpenedListener() {
                    @Override
                    public void onDeviceOpened(MidiDevice device) {
                        if (device == null) {
                            Log.e("", "could not open device");
                        } else {
                            for (int j = 0; j < infos[currentDevice].getOutputPortCount(); j++) {
                                MidiOutputPort outputPort = device.openOutputPort(j);
                                outputPort.connect(midiReceiver);
                            }
                        }
                    }
                }, new Handler(Looper.getMainLooper()));
            }

            // adding any newly connected device
            m.registerDeviceCallback(new MidiManager.DeviceCallback() {
                public void onDeviceAdded(final MidiDeviceInfo info) {
                    m.openDevice(info, new MidiManager.OnDeviceOpenedListener() {
                        @Override
                        public void onDeviceOpened(MidiDevice device) {
                            if (device == null) {
                                Log.e("", "could not open device");
                            } else {
                                for (int j = 0; j < info.getOutputPortCount(); j++) {
                                    MidiOutputPort outputPort = device.openOutputPort(j);
                                    outputPort.connect(midiReceiver);
                                }
                            }
                        }
                    }, new Handler(Looper.getMainLooper()));
                }

                public void onDeviceRemoved(final MidiDeviceInfo info) {

                }

            }, new Handler(Looper.getMainLooper()));
        }
    }

    private void startFaustDsp(){
        if(dspFaust == null){
            dspFaust = new DspFaust(Integer.valueOf(getResources().getString(R.string.sr)), Integer.valueOf(getResources().getString(R.string.bs)));
            dspFaust.start();
        }
    }

    private void stopFaustDsp(){
        if(dspFaust != null){
            dspFaust.stop();
            dspFaust = null;
        }
    }

    @Override
    public void onPause(){
        super.onPause();
        dspFaust.stop();
    }

    @Override
    public void onResume(){
        super.onPause();
        dspFaust.start();
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        dspFaust.stop();
    }

    class FaustMidiReceiver extends MidiReceiver {
        public void onSend(byte[] data, int offset,
                           int count, long timestamp) {
            // we only consider MIDI messages containing 3 bytes (see is just an example)
            if(count%3 == 0) {
                int nMessages = count / 3; // in case the event contains several messages
                for (int i = 0; i < nMessages; i++) {
                    int type = (int) (data[offset + i*3] & 0xF0);
                    int channel = (int) (data[offset + i*3] & 0x0F);
                    int data1 = (int) data[offset + 1 + i*3];
                    int data2 = (int) data[offset + 2 + i*3];
                    dspFaust.propagateMidi(3, timestamp, type, channel, data1, data2);
                }
            }
        }
    }
}
