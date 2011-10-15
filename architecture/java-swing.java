/************************************************************************
    FAUST Architecture File
	Copyright (C) 2011 Kjetil Matheussen
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
    This architechture file needs more work.

    Only playback is supported.

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
  
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JOptionPane;

import java.lang.Math;

import  sun.audio.*;
import  java.io.*;
import javax.sound.sampled.*;


public final class Main {

    public static void main(String... aArgs){
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel");
        }catch (Exception e) {
            System.out.println("Couldn't set lookandfeel");
        }

        UI ui = new UI();
        mydsp my_mydsp = new mydsp();
        my_mydsp.init(44100);
        my_mydsp.buildUserInterface(ui);
        Sound sound = new Sound(my_mydsp);
    }
  
}

class Sound{
    mydsp my_mydsp;

    final int nFrames = 1024;


    AudioFormat getAudioFormat(){ 
        float sampleRate = my_mydsp.fSamplingFreq;
        int sampleSizeInBits = 16; 
        int channels = my_mydsp.getNumOutputs();
        boolean signed = true; 
        boolean bigEndian = false; 
        return new AudioFormat(sampleRate, 
                               sampleSizeInBits, 
                               channels, 
                               signed, 
                               bigEndian); 
    }
  
    AudioInputStream audioInputStream;
    SourceDataLine sourceDataLine;

    class PlayThread extends Thread{ 
        void floatToBytes(float in, byte[] out){
            short s = (short)(in * 32767);
            out[0] = (byte) ( ( s >>> 0 ) & 0xff );
            out[1] = (byte) ( ( s >>> 8 ) & 0xff );        
        }
        
        byte[] s=new byte[2];
        void floatsToBytes(float[] in, byte[] out, int len){
            for(int i=0;i<len;i++){
                floatToBytes(in[i],s);
                out[i*2]   = s[0];
                out[i*2+1] = s[1];
            }
        }
        
        float[][] buf = new float[my_mydsp.getNumOutputs()][nFrames];
        byte[][] bytebuf = new byte[my_mydsp.getNumOutputs()][nFrames*2];
        byte[] interleaved = new byte[my_mydsp.getNumOutputs() * nFrames * 2];
        public byte[] read(){
            my_mydsp.compute(nFrames,null,buf);
            for(int ch=0;ch<my_mydsp.getNumOutputs();ch++){
                floatsToBytes(buf[ch],bytebuf[ch],nFrames);
            }
            int ipos=0;
            for(int i=0;i<nFrames;i++){
                for(int ch=0;ch<my_mydsp.getNumOutputs();ch++){
                    interleaved[ipos++] = bytebuf[ch][i*2];
                    interleaved[ipos++] = bytebuf[ch][i*2+1];
                }
            }
            return interleaved;
        }

        public void run(){ 
            try{ 
                while(true){
                    byte[] data=read();
                    sourceDataLine.write(data,0,nFrames*2*my_mydsp.getNumOutputs());
                }
            }catch (Exception e) { 
                System.out.println(e); 
                System.exit(0); 
            }
        }
    }
    
    Sound(mydsp my_mydsp){
        this.my_mydsp = my_mydsp;

        try{ 
            AudioFormat audioFormat = getAudioFormat(); 

            DataLine.Info dataLineInfo = new DataLine.Info(SourceDataLine.class, audioFormat);
            sourceDataLine = (SourceDataLine) AudioSystem.getLine(dataLineInfo); 
            sourceDataLine.open(audioFormat,nFrames); 
            sourceDataLine.start(); 
            
            Thread playThread = new Thread(new PlayThread()); 
            playThread.start(); 
        } catch (Exception e) { 
            e.printStackTrace();
        }
    }
}

<<includeIntrinsic>>


class Meta{
    void declare(String name, String value){
    }
}

interface FaustVarAccess{
    public String getId();
    public void set(float val);
    public float get();
}


class UI{
    JFrame jframe;
    JPanel jpanel;

    public static Dimension HGAP2 = new Dimension(2,1);
    public static Dimension HGAP10 = new Dimension(10,1);
    public static Dimension VGAP5 = new Dimension(1,5);
    public static Dimension VGAP10 = new Dimension(1,10);

    UI(){
        jframe = new JFrame("Test Frame"); 
        jpanel = new JPanel();
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.pack();
        jframe.setVisible(true);
        jframe.getContentPane().add(jpanel);
        //UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());

    }

    public void declare(String id, String key, String value){}

    // -- layout groups
    
    public void openFrameBox(String label){}   
    public void openTabBox(String label){}
    public void openHorizontalBox(String label){}
    public void openVerticalBox(String label){}

    // -- extra widget's layouts

    public void openDialogBox(String label, FaustVarAccess varAccess){}
    public void openEventBox(String label){}
    public void openHandleBox(String label){}
    public void openExpanderBox(String label, FaustVarAccess varAccess){}
    
    public void closeBox(){}
    public void adjustStack(int n){}

    // -- active widgets
    
    public void addButton(String label, final FaustVarAccess varAccess){
 	final JButton b = new JButton(label);

        b.addMouseListener(new MouseListener(){
                public void mouseClicked(MouseEvent e){}
                public void mouseEntered(MouseEvent e) {}
                public void mouseExited(MouseEvent e){}
                public void mousePressed(MouseEvent e){
                    varAccess.set(1);
                }
                public void mouseReleased(MouseEvent e){
                    varAccess.set(0);
                }
            });

 	jpanel.add(b);
 	jpanel.add(Box.createRigidArea(HGAP10)); 
        jframe.pack();
    }
    public void addToggleButton(String label, FaustVarAccess varAccess){
        System.out.println("TODO");
        addButton(label,varAccess);
    }
    public void addCheckButton(String label, FaustVarAccess varAccess){
        System.out.println("TODO");
        addButton(label,varAccess);
    }

    public void addVerticalSlider(String label, final FaustVarAccess varAccess, float init, float min, float max, float step){
        JLabel tf = new JLabel(label); 
        //ChangeListener listener = new SliderListener(tf,label);
        JPanel p = new JPanel(); 
 	p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS)); 
 	p.setBorder(new TitledBorder(label+"*1000"));
 	final JSlider s = new JSlider(JSlider.VERTICAL, (int)(min*1000), (int)(max*1000), (int)(init*1000));
        s.setPaintLabels(true);
 	s.getAccessibleContext().setAccessibleName(label);
 	s.getAccessibleContext().setAccessibleDescription(label);
 	s.addChangeListener(new ChangeListener(){
                public void stateChanged(ChangeEvent e){
                    //System.out.println(s.getValue()/1000.0);
                    varAccess.set(s.getValue()/1000.0f);
                }
            });
 	p.add(Box.createRigidArea(HGAP10)); 
 	p.add(s); 
 	p.add(Box.createRigidArea(HGAP10)); 
        jpanel.add(p);
        jframe.pack();
    }   
    public void addHorizontalSlider(String label, final FaustVarAccess varAccess, float init, float min, float max, float step){
        JLabel tf = new JLabel(label); 
        //ChangeListener listener = new SliderListener(tf,label);
        JPanel p = new JPanel(); 
 	p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS)); 
 	p.setBorder(new TitledBorder(label+"*1000"));
 	final JSlider s = new JSlider(JSlider.HORIZONTAL, (int)(min*1000), (int)(max*1000), (int)(init*1000));
        s.setPaintLabels(true);
 	s.getAccessibleContext().setAccessibleName(label);
 	s.getAccessibleContext().setAccessibleDescription(label);
 	s.addChangeListener(new ChangeListener(){
                public void stateChanged(ChangeEvent e){
                    JSlider slider = (JSlider)e.getSource(); 
                    //System.out.println(s.getValue()/1000.0);
                    varAccess.set(s.getValue()/1000.0f);
                }
            });

	p.add(Box.createRigidArea(VGAP5));
	p.add(s);
	p.add(Box.createRigidArea(VGAP5));
 	jpanel.setLayout(new BoxLayout(jpanel, BoxLayout.Y_AXIS)); 
	jpanel.add(p);
	jpanel.add(Box.createRigidArea(VGAP10));

        jframe.pack();
    }   
 
    public void addKnob(String label, FaustVarAccess varAccess, float init, float min, float max, float step){
        System.out.println("TODO");
        addHorizontalSlider(label,varAccess,init,min,max,step);
    }
    public void addNumEntry(String label, FaustVarAccess varAccess, float init, float min, float max, float step){
        System.out.println("TODO");
        addHorizontalSlider(label,varAccess,init,min,max,step);
    }
    
    // -- passive display widgets
    
    public void addNumDisplay(String label, FaustVarAccess varAccess, int precision){}
    public void addTextDisplay(String label, FaustVarAccess varAccess, String names[], float min, float max){}
    public void addHorizontalBargraph(String label, FaustVarAccess varAccess, float min, float max){}
    public void addVerticalBargraph(String label, FaustVarAccess varAccess, float min, float max){}

}

class dsp{
    public float fSamplingFreq;

    float powf(float a,float b){
        return (float)java.lang.Math.pow(a,b);
    }
    double pow(double a,float b){
        return java.lang.Math.pow(a,b);
    }
    int max(int a,int b){
        return java.lang.Math.max(a,b);
    }
    int min(int a,int b){
        return java.lang.Math.min(a,b);
    }
    float floorf(float a){
        return (float)java.lang.Math.floor(a);
    }
    double floor(double a){
        return java.lang.Math.floor(a);
    }
    float sinf(float a){
        return (float)java.lang.Math.sin(a);
    }
    double sin(double a){
        return java.lang.Math.sin(a);
    }
}


<<includeclass>>
