package com.faust;

import com.faust.PianoKeyboard.PianoKey;
import com.faust.PianoKeyboard.OnKeyboardChangeListener;

import android.app.Activity;
import android.os.Bundle;

/*
 * This activity implements a full screen keyboard that can control
 * the pitch and the velocity of a Faust synthesizer.
 */
public class PianoActivity extends Activity {
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.piano);
        
        // no need for a dynamic interface: the keyboard is instantiated from the XML layout 
        final PianoKeyboard keyboard = (PianoKeyboard) this.findViewById(R.id.PianoKeyboard);
        keyboard.setOnKeyboardChangeListener(new OnKeyboardChangeListener(){
            @Override
            public void onKeyChanged(int note, int velocity, boolean status) {
                if (status) {
                    keyboard.keys[note - keyboard.baseNote].voice = FaustActivity.dspFaust.keyOn(note,velocity);
                } else {
                    FaustActivity.dspFaust.keyOff(note);
                    keyboard.keys[note - keyboard.baseNote].voice = -1;
                }
            }
			
            @Override
            public void onPitchBend(long voice, float pitch) {
                FaustActivity.dspFaust.setVoiceParamValue("freq", voice, (float)(440.0 * Math.pow(2.0, (pitch-69.0)/12.0)));
            }
       
            @Override
            public void onYChanged(long voice, float y) {
                FaustActivity.dspFaust.setVoiceParamValue("gain", voice, y);
            }
        });
	}
	
	@Override
	public void onDestroy(){
    	super.onDestroy();
    }
}
