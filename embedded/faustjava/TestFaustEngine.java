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
        dsp DSP1 = FaustEngine.create2Dsp("noise", prog1, argv, "", 3);
        
        if (DSP1 == null) {
            System.out.print(FaustEngine.getLastError());
            return;
        }
        
        System.out.println(FaustEngine.getJSONDsp(DSP1));
          
        FaustEngine.init1Dsp(DSP1, "Test");
        FaustEngine.startDsp(DSP1);
        
        System.out.println("DSP1 inputs " + FaustEngine.getNumInputsDsp(DSP1));
        System.out.println("DSP1 outputs " + FaustEngine.getNumOutputsDsp(DSP1));
        
        System.out.println("getParamsCount : " + FaustEngine.getParamsCountDsp(DSP1));
     
        //String prog2  = "import(\"music.lib\"); db2linear1(x) = pow(10.0, x/20.0); smooth(c) = *(1-c) : +~*(c); vol = hslider(\"volume [unit:dB]\", 0, -96, 0, 0.1) : db2linear : smooth(0.999); freq = hslider(\"freq [unit:Hz]\", 1000, 20, 24000, 1); process = vgroup(\"Oscillator\", osc(freq) * vol);";
        
        //prog2 = prog1;
         
        String prog2 = "process = _,_;";

        // oscillator
        //dsp DSP2 = FaustEngine.create1("osc", prog2);

        System.out.println(argv);
        dsp DSP2 = FaustEngine.create2Dsp("osc", prog2, argv, "", 3);

System.out.println(DSP2);
        
        //System.out.println(FaustEngine.getJSON(DSP2));
          
        FaustEngine.init1Dsp(DSP2, "Test2");
        FaustEngine.startDsp(DSP2);
        
        System.out.println("DSP2 inputs " + FaustEngine.getNumInputsDsp(DSP2));
        System.out.println("DSP2 outputs " + FaustEngine.getNumOutputsDsp(DSP2));
        
       // System.out.println("getParamsCount : " + FaustEngine.getParamsCount(DSP2));
       
        System.out.println("getNumPhysicalInputs " + FaustEngine.getNumInputsDsp(null));
        System.out.println("getNumPhysicalOutputs " + FaustEngine.getNumOutputsDsp(null));
        
        FaustEngine.connectDsp(DSP1, null, 0, 0);
        FaustEngine.connectDsp(DSP1, null, 1, 1);
        
        FaustEngine.connectDsp(DSP1, DSP2, 0, 0);
        FaustEngine.connectDsp(DSP1, DSP2, 1, 1);
        
        FaustEngine.connectDsp(DSP2, null, 0, 0);
        FaustEngine.connectDsp(DSP2, null, 1, 1);
        
        FaustEngine.connectDsp(null, DSP2, 0, 0);
        FaustEngine.connectDsp(null, DSP2, 1, 1);
        
	Thread.sleep(1000);
        /////
        
        System.out.println(FaustEngine.isConnectedDsp(DSP1, null, 0, 0));
        System.out.println(FaustEngine.isConnectedDsp(DSP1, null, 1, 1));
        
        System.out.println(FaustEngine.isConnectedDsp(DSP1, DSP2, 0, 0));
        System.out.println(FaustEngine.isConnectedDsp(DSP1, DSP2, 1, 1));
        
        System.out.println(FaustEngine.isConnectedDsp(DSP2, null, 0, 0));
        System.out.println(FaustEngine.isConnectedDsp(DSP2, null, 1, 1));
        
        System.out.println(FaustEngine.isConnectedDsp(null, DSP2, 0, 0));
        System.out.println(FaustEngine.isConnectedDsp(null, DSP2, 1, 1)); 
        
        
        /////
        
        /*
        FaustEngine.disconnectDsp(DSP1, null, 0, 0);
        FaustEngine.disconnectDsp(DSP1, null, 1, 1);
        
        FaustEngine.disconnectDsp(DSP1, DSP2, 0, 0);
        FaustEngine.disconnectDsp(DSP1, DSP2, 1, 1);
        
        FaustEngine.disconnectDsp(DSP2, null, 0, 0);
        FaustEngine.disconnectDsp(DSP2, null, 1, 1);
        
        FaustEngine.disconnectDsp(null, DSP2, 0, 0);
        FaustEngine.disconnectDsp(null, DSP2, 1, 1);
        */
    
        Thread.sleep(1000*100);
        
        FaustEngine.stopDsp(DSP1);
        FaustEngine.stopDsp(DSP2);
        
        FaustEngine.destroyDsp(DSP1);
        FaustEngine.destroyDsp(DSP2);
    }
}