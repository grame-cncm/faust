package com.faust;

import com.faust.PianoKeyboard.PianoKey;
import com.faust.PianoKeyboard.OnKeyboardChangeListener;
import com.dsp_faust.dsp_faust;

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
                    keyboard.keys[note - keyboard.baseNote].voice = dsp_faust.keyOn(note,velocity);
                } else {
                    dsp_faust.keyOff(note);
                    keyboard.keys[note - keyboard.baseNote].voice = -1;
                }
            }
			
            @Override
            public void onPitchBend(int voice, float pitch) {
                dsp_faust.setVoiceParamValue("freq", voice, (float)(440.0 * Math.pow(2.0, (pitch-69.0)/12.0)));
            }
       
            @Override
            public void onYChanged(int voice, float y) {
                dsp_faust.setVoiceParamValue("gain", voice, y);
            }
        });
	}
	
	@Override
	public void onDestroy(){
    	super.onDestroy();
    }
}
