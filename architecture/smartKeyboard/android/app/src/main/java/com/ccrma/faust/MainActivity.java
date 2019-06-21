package com.ccrma.faust;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.media.midi.MidiDevice;
import android.media.midi.MidiDeviceInfo;
import android.media.midi.MidiManager;
import android.media.midi.MidiOutputPort;
import android.media.midi.MidiReceiver;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
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

public class MainActivity extends AppCompatActivity
implements ActivityCompat.OnRequestPermissionsResultCallback {

    private DspFaust dspFaust;
    private Context context;
    private RelativeLayout mainLayout;

    // For audio input request permission
    private static final int AUDIO_ECHO_REQUEST = 0;
    private boolean permissionToRecordAccepted = false;

    private void createFaust(){
        if (dspFaust == null) {
            dspFaust = new DspFaust(Integer.valueOf(getResources().getString(R.string.sr)), Integer.valueOf(getResources().getString(R.string.bs)));
        }

        MultiKeyboard multiKeyboard = new MultiKeyboard(this, dspFaust, null);
        mainLayout.addView(multiKeyboard);

        if(Build.VERSION.SDK_INT >= 23) {
            // MIDI Support
            final FaustMidiReceiver midiReceiver = new FaustMidiReceiver();
            final MidiManager m = (MidiManager) context.getSystemService(Context.MIDI_SERVICE);
            if (m == null) {
                Log.e("", "could not open MIDI service");
                return;
            }
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

    
    // Record audio permission callback
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        
        if (AUDIO_ECHO_REQUEST != requestCode) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
            return;
        }
        
        if (grantResults.length != 1 ||
            grantResults[0] != PackageManager.PERMISSION_GRANTED) {
            finish();
        } else {
            // Permission was granted
            permissionToRecordAccepted = true;
            createFaust();
        }
    }
    
    // For audio input request permission
    private boolean isRecordPermissionGranted() {
        return (ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED);
    }
    
    private void requestRecordPermission() {
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.RECORD_AUDIO}, AUDIO_ECHO_REQUEST);
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = getApplicationContext();
        mainLayout = (RelativeLayout) findViewById(R.id.activity_main);
        
        if (Build.VERSION.SDK_INT >= 23 && !isRecordPermissionGranted()){
            requestRecordPermission();
        } else {
            permissionToRecordAccepted = true;
            createFaust();
        }

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
    }

    @Override
    protected void onPause(){
        super.onPause();
        if (permissionToRecordAccepted) {
            dspFaust.stop();
        }
    }

    @Override
    protected void onResume(){
        super.onResume();
        if (permissionToRecordAccepted) {
            if (!dspFaust.isRunning()) {
                dspFaust.start();
            }
        }
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        dspFaust = null;
    }

    class FaustMidiReceiver extends MidiReceiver {
        public void onSend(byte[] data, int offset,
                           int count, long timestamp) {
            // we only consider MIDI messages containing 3 bytes (see is just an example)
            if (permissionToRecordAccepted && (count%3 == 0)) {
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
