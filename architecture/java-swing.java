/************************************************************************
    FAUST Architecture File
    Copyright (C) 2011 Kjetil Matheussen
    Copyright (C) 2013 Grame
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
    as published by the Free Software Foundation; either version 3 of 
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work 
    that contains this FAUST architecture section and distribute  
    that work under terms of your choice, so long as this FAUST 
    architecture section is not modified. 

 ************************************************************************
 ************************************************************************/

/***
    Duplex is supported.

    Example on how to use it:
    faust -lang java -a java-swing.java noise.dsp > mydsp.java && javac mydsp.java && java mydsp

    Audio playback info gathered from this thread:
    http://www.java-forums.org/awt-swing/2087-make-sound-play-java-application.html
 ***/

import javax.swing.*; 
import javax.swing.event.*; 
import javax.swing.text.*; 
import javax.swing.border.*; 
import javax.swing.colorchooser.*; 
import javax.swing.filechooser.*; 
import javax.accessibility.*; 
  
import java.awt.*; 
import java.awt.event.*; 
import java.beans.*; 
import java.util.*; 
import java.io.*; 
import java.applet.*; 
import java.net.*; 
import java.nio.Buffer.*;
import java.nio.FloatBuffer;
  
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JOptionPane;

import java.lang.Math;

import sun.audio.*;
import java.io.*;
import javax.sound.sampled.*;

class Sound {

    mydsp my_mydsp;

    final int nFrames = 1024;
    
    SourceDataLine sourceDataLine;
    TargetDataLine targetDataLine;

    AudioFormat getOutputAudioFormat()
    { 
        float sampleRate = my_mydsp.fSamplingFreq;
        int sampleSizeInBits = 16; 
        int channels = my_mydsp.getNumOutputs();
        boolean signed = true; 
        boolean bigEndian = true;  // Using 'false' here is falling on OSX...
        return new AudioFormat(sampleRate, 
                               sampleSizeInBits, 
                               channels, 
                               signed, 
                               bigEndian); 
    }
    
    AudioFormat getInputAudioFormat()
    { 
        float sampleRate = my_mydsp.fSamplingFreq;
        int sampleSizeInBits = 16; 
        int channels = my_mydsp.getNumInputs();
        boolean signed = true; 
        boolean bigEndian = true; // Using 'false' here is falling on OSX...
        return new AudioFormat(sampleRate, 
                               sampleSizeInBits, 
                               channels, 
                               signed, 
                               bigEndian); 
    }
  
    class PlayThread extends Thread { 
    
        float inverse_gain_float = 1.f / 32767.f;
        float inverse_gain_double = 1 / 32767;
        
        float[][] output_float_buffer = new float[my_mydsp.getNumOutputs()][nFrames];
        double[][] output_double_buffer = new double[my_mydsp.getNumOutputs()][nFrames];
        byte[] output_interleaved = new byte[my_mydsp.getNumOutputs() * nFrames * 2];
        java.nio.ShortBuffer output_wrapped = java.nio.ByteBuffer.wrap(output_interleaved).asShortBuffer();
        
        float[][] input_float_buffer = new float[my_mydsp.getNumInputs()][nFrames];
        double[][] input_double_buffer = new double[my_mydsp.getNumInputs()][nFrames];
        byte[] input_interleaved = new byte[my_mydsp.getNumInputs() * nFrames * 2];
        java.nio.ShortBuffer input_wrapped = java.nio.ByteBuffer.wrap(input_interleaved).asShortBuffer();
        
        public void process_float()
        {
            // Deinterleave and convert inputs
            int ipos = 0;
            for (int i = 0; i < nFrames; i++) {
                for(int ch = 0; ch < my_mydsp.getNumInputs(); ch++) {
                    input_float_buffer[ch][i] = (float)input_wrapped.get(ipos++) * inverse_gain_float;
                }
            }
            
            // Compute Faust effect
            my_mydsp.compute(nFrames, input_float_buffer, output_float_buffer);
            
            // Convert and interleave outputs
            ipos = 0;
            for (int i = 0; i < nFrames; i++){
                for(int ch = 0; ch < my_mydsp.getNumOutputs(); ch++) {
                    output_wrapped.put(ipos++, (short)(output_float_buffer[ch][i] * 32767.f));
                }
            }
        }
        
        /*
        public void process_double()
        {
            // Deinterleave and convert inputs
            int ipos = 0;
            for (int i = 0; i < nFrames; i++) {
                for(int ch = 0; ch < my_mydsp.getNumInputs(); ch++) {
                    input_double_buffer[ch][i] = (double)input_wrapped.get(ipos++) * inverse_gain_double;
                }
            }
            
            // Compute Faust effect
            my_mydsp.compute(nFrames, input_double_buffer, output_double_buffer);
            
            // Convert and interleave outputs
            ipos = 0;
            for (int i = 0; i < nFrames; i++){
                for(int ch = 0; ch < my_mydsp.getNumOutputs(); ch++) {
                    output_wrapped.put(ipos++, (short)(output_double_buffer[ch][i] * 32767));
                }
            }
        }
        */

        public void run() 
        { 
            try { 
                while (true) {
                    
                    if (my_mydsp.getNumInputs() > 0) {
                        targetDataLine.read(input_interleaved, 0, nFrames * 2 * my_mydsp.getNumInputs());
                    }
                    
                    process_float();
                    
                    if (my_mydsp.getNumOutputs() > 0) {
                        sourceDataLine.write(output_interleaved, 0, nFrames * 2 * my_mydsp.getNumOutputs());
                    }
                }
            } catch (Exception e) { 
                System.out.println(e); 
                System.exit(0); 
            }
        }
    }
    
    Sound(mydsp my_mydsp) {
        this.my_mydsp = my_mydsp;

        try { 
        
            if (my_mydsp.getNumInputs() > 0) {
                AudioFormat audioInputFormat = getInputAudioFormat(); 
                DataLine.Info input_dataLineInfo = new DataLine.Info(TargetDataLine.class, audioInputFormat);
                targetDataLine = (TargetDataLine)AudioSystem.getLine(input_dataLineInfo); 
                targetDataLine.open(audioInputFormat); 
                targetDataLine.start(); 
            }
            
            if (my_mydsp.getNumOutputs() > 0) {
                AudioFormat audioOutputFormat = getOutputAudioFormat(); 
                DataLine.Info output_dataLineInfo = new DataLine.Info(SourceDataLine.class, audioOutputFormat);
                sourceDataLine = (SourceDataLine)AudioSystem.getLine(output_dataLineInfo); 
                sourceDataLine.open(audioOutputFormat); 
                sourceDataLine.start(); 
            }
             
            Thread playThread = new Thread(new PlayThread()); 
            playThread.start(); 
            
        } catch (Exception e) { 
            e.printStackTrace();
        }
    }
}

<<includeIntrinsic>>

class Meta {
    void declare(String name, String value) {}
}

interface FaustVarAccess {
    public String getId();
    public void set(float val);
    public float get();
}

class UI {
    JFrame jframe;
    JPanel jpanel;

    public static Dimension HGAP2 = new Dimension(2, 1);
    public static Dimension HGAP10 = new Dimension(10, 1);
    public static Dimension VGAP5 = new Dimension(1, 5);
    public static Dimension VGAP10 = new Dimension(1, 10);

    UI() {
        jframe = new JFrame("Test Frame"); 
        jpanel = new JPanel();
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.pack();
        jframe.setVisible(true);
        jframe.getContentPane().add(jpanel);
        //UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
    }

    public void declare(String id, String key, String value) {}

    // -- layout groups
    
    public void openTabBox(String label) {}
    public void openHorizontalBox(String label) {}
    public void openVerticalBox(String label) {}
    public void closeBox() {}

    // -- active widgets
    
    public void addButton(String label, final FaustVarAccess varAccess) {
        final JButton b = new JButton(label);

        b.addMouseListener(new MouseListener(){
                public void mouseClicked(MouseEvent e) {}
                public void mouseEntered(MouseEvent e)  {}
                public void mouseExited(MouseEvent e) {}
                public void mousePressed(MouseEvent e) {
                    varAccess.set(1);
                }
                public void mouseReleased(MouseEvent e) {
                    varAccess.set(0);
                }
            });

        jpanel.add(b);
        jpanel.add(Box.createRigidArea(HGAP10)); 
        jframe.pack();
    }
    public void addCheckButton(String label, FaustVarAccess varAccess)
    {
        System.out.println("TODO");
        addButton(label,varAccess);
    }

    public void addVerticalSlider(String label, final FaustVarAccess varAccess, float init, float min, float max, float step)
    {
        JLabel tf = new JLabel(label); 
        //ChangeListener listener = new SliderListener(tf,label);
        JPanel p = new JPanel(); 
        p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS)); 
        final JSlider s;
        int factor = 1;
        
        if (java.lang.Math.abs(max - min) <= 0.1) {
            p.setBorder(new TitledBorder(label+"*1000"));
            factor = 1000;
        } else if (java.lang.Math.abs(max - min) <= 1) {
            p.setBorder(new TitledBorder(label+"*100"));
            factor = 100;
        } else if (java.lang.Math.abs(max - min) <= 10) {
            p.setBorder(new TitledBorder(label+"*10"));
            factor = 10;
        } else {
            p.setBorder(new TitledBorder(label));
        }
        
        s = new JSlider(JSlider.VERTICAL, (int)(min * factor), (int)(max * factor), (int)(init * factor));
        s.setMajorTickSpacing((int)((max - min) * factor / 4));
        s.setMinorTickSpacing((int)((max - min) * factor / 8));
        s.setPaintTicks(true);
        s.setPaintLabels(true);
        s.getAccessibleContext().setAccessibleName(label);
        s.getAccessibleContext().setAccessibleDescription(label);
        if (factor == 1000) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/1000.f);
                }
            });
        } else if (factor == 100) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/100.f);
                }
            });
        } else if (factor == 10) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/10.f);
                }
            });
        } else {
            s.addChangeListener(new ChangeListener() {
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue());
                }
            });
        }
     
        p.add(Box.createRigidArea(HGAP10)); 
        p.add(s); 
        p.add(Box.createRigidArea(HGAP10)); 
        jpanel.add(p);
        jframe.pack();
    }   
    public void addHorizontalSlider(String label, final FaustVarAccess varAccess, float init, float min, float max, float step)
    {
        JLabel tf = new JLabel(label); 
        //ChangeListener listener = new SliderListener(tf,label);
        JPanel p = new JPanel(); 
        p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS)); 
        p.setBorder(new TitledBorder(label));
        final JSlider s;
        int factor = 1;
        
        if (java.lang.Math.abs(max - min) <= 0.1) {
            p.setBorder(new TitledBorder(label+"*1000"));
            factor = 1000;
        } else if (java.lang.Math.abs(max - min) <= 1) {
            p.setBorder(new TitledBorder(label+"*100"));
            factor = 100;
        } else if (java.lang.Math.abs(max - min) <= 10) {
            p.setBorder(new TitledBorder(label+"*10"));
            factor = 10;
        } else {
            p.setBorder(new TitledBorder(label));
        }
     
        s = new JSlider(JSlider.HORIZONTAL, (int)(min * factor), (int)(max * factor), (int)(init * factor));
        s.setMajorTickSpacing((int)((max - min) * factor / 4));
        s.setMinorTickSpacing((int)((max - min) * factor / 8));
        s.setPaintTicks(true);
        s.setPaintLabels(true);
        s.getAccessibleContext().setAccessibleName(label);
        s.getAccessibleContext().setAccessibleDescription(label);
        if (factor == 1000) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/1000.f);
                }
            });
        } else if (factor == 100) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/100.f);
                }
            });
        } else if (factor == 10) {
            s.addChangeListener(new ChangeListener(){
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue()/10.f);
                }
            });
        } else {
            s.addChangeListener(new ChangeListener() {
                    public void stateChanged(ChangeEvent e) {
                    varAccess.set((float)s.getValue());
                }
            });
        }
        
        p.add(Box.createRigidArea(VGAP5));
        p.add(s);
        p.add(Box.createRigidArea(VGAP5));
        jpanel.setLayout(new BoxLayout(jpanel, BoxLayout.Y_AXIS)); 
        jpanel.add(p);
        jpanel.add(Box.createRigidArea(VGAP10));
        jframe.pack();
    }   
 
    public void addNumEntry(String label, FaustVarAccess varAccess, float init, float min, float max, float step)
    {
        System.out.println("TODO");
        addHorizontalSlider(label, varAccess, init, min, max, step);
    }
    
    // -- passive display widgets
    
    public void addHorizontalBargraph(String label, FaustVarAccess varAccess, float min, float max) 
    {
        System.out.println("TODO");
    }
    public void addVerticalBargraph(String label, FaustVarAccess varAccess, float min, float max)
    {
        System.out.println("TODO");
    }

}

class dsp {

    public int fSamplingFreq;
     
    public static void main(String... aArgs)
    {
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel");
        } catch (Exception e) {
            System.out.println("Couldn't set lookandfeel");
        }
        
        UI ui = new UI();
        mydsp my_mydsp = new mydsp();
        my_mydsp.init(44100);
        my_mydsp.buildUserInterface(ui);
        Sound sound = new Sound(my_mydsp);
    }
  
}

<<includeclass>>
