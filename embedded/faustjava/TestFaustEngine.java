import java.io.*;
import com.grame.faust.FaustEngine;
import com.grame.faust.dsp;

class TestFaustEngine
{
	static {
		try {
			String property = System.getProperty("java.library.path");
			System.out.println("java.library.path = " + property);
            System.loadLibrary("FaustEngine"); 
		} catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
		}
    }

    public static void main(String args[]) throws InterruptedException {
		System.out.println("Start Faust Engine");
        
        // noise generator
        String prog1 = "random = +(12345)~*(1103515245); noise = random/2147483647.0; process = noise * vslider(\"Volume\", 0.5, 0, 1, 0.01)<:_,_;";

   
        //dsp DSP1 = FaustEngine.create1("noise", prog1);
       
        String argv = "-vec " + "-lv " + "1 " + "-I " + "C:\\Users\\Sarah\\faudiostream-code\\architecture";
        System.out.println(argv);
        dsp DSP1 = FaustEngine.create2("noise", prog1, argv, "", 3);
        
        if (DSP1 == null) {
            System.out.print(FaustEngine.getLastError());
            return;
        }
        
        System.out.println(FaustEngine.getJSON(DSP1));
          
        FaustEngine.init1(DSP1, "Test");
        FaustEngine.start(DSP1);
        
        System.out.println("DSP1 inputs " + FaustEngine.getNumInputs(DSP1));
        System.out.println("DSP1 outputs " + FaustEngine.getNumOutputs(DSP1));
        
        System.out.println("getParamsCount : " + FaustEngine.getParamsCount(DSP1));
     
        //String prog2  = "import(\"music.lib\"); db2linear1(x) = pow(10.0, x/20.0); smooth(c) = *(1-c) : +~*(c); vol = hslider(\"volume [unit:dB]\", 0, -96, 0, 0.1) : db2linear : smooth(0.999); freq = hslider(\"freq [unit:Hz]\", 1000, 20, 24000, 1); process = vgroup(\"Oscillator\", osc(freq) * vol);";
        
        //prog2 = prog1;
         
        String prog2 = "process = _,_;";

        // oscillator
        //dsp DSP2 = FaustEngine.create1("osc", prog2);

        System.out.println(argv);
        dsp DSP2 = FaustEngine.create2("osc", prog2, argv, "", 3);

System.out.println(DSP2);
        
        //System.out.println(FaustEngine.getJSON(DSP2));
          
        FaustEngine.init1(DSP2, "Test2");
        FaustEngine.start(DSP2);
        
        System.out.println("DSP2 inputs " + FaustEngine.getNumInputs(DSP2));
        System.out.println("DSP2 outputs " + FaustEngine.getNumOutputs(DSP2));
        
       // System.out.println("getParamsCount : " + FaustEngine.getParamsCount(DSP2));
       
        System.out.println("getNumPhysicalInputs " + FaustEngine.getNumPhysicalInputs());
        System.out.println("getNumPhysicalOutputs " + FaustEngine.getNumPhysicalOutputs());
        
        FaustEngine.connect(DSP1, null, 0, 0);
        FaustEngine.connect(DSP1, null, 1, 1);
        
        FaustEngine.connect(DSP1, DSP2, 0, 0);
        FaustEngine.connect(DSP1, DSP2, 1, 1);
        
        FaustEngine.connect(DSP2, null, 0, 0);
        FaustEngine.connect(DSP2, null, 1, 1);
        
        FaustEngine.connect(null, DSP2, 0, 0);
        FaustEngine.connect(null, DSP2, 1, 1);
        
        /////
        
        System.out.println(FaustEngine.isConnected(DSP1, null, 0, 0));
        System.out.println(FaustEngine.isConnected(DSP1, null, 1, 1));
        
        System.out.println(FaustEngine.isConnected(DSP1, DSP2, 0, 0));
        System.out.println(FaustEngine.isConnected(DSP1, DSP2, 1, 1));
        
        System.out.println(FaustEngine.isConnected(DSP2, null, 0, 0));
        System.out.println(FaustEngine.isConnected(DSP2, null, 1, 1));
        
        System.out.println(FaustEngine.isConnected(null, DSP2, 0, 0));
        System.out.println(FaustEngine.isConnected(null, DSP2, 1, 1)); 
        
        
        /////
        
        /*
        FaustEngine.disconnect(DSP1, null, 0, 0);
        FaustEngine.disconnect(DSP1, null, 1, 1);
        
        FaustEngine.disconnect(DSP1, DSP2, 0, 0);
        FaustEngine.disconnect(DSP1, DSP2, 1, 1);
        
        FaustEngine.disconnect(DSP2, null, 0, 0);
        FaustEngine.disconnect(DSP2, null, 1, 1);
        
        FaustEngine.disconnect(null, DSP2, 0, 0);
        FaustEngine.disconnect(null, DSP2, 1, 1);
        */
    
        Thread.sleep(1000*100);
        
        FaustEngine.stop(DSP1);
        FaustEngine.stop(DSP2);
        
        FaustEngine.destroy(DSP1);
        FaustEngine.destroy(DSP2);
    }
}