import java.io.*;
import com.grame.faust.Faust;
import com.grame.faust.llvm_dsp_factory;
import com.grame.faust.llvm_dsp;

class TestFaust
{
	static {
		try {
			String property = System.getProperty("java.library.path");
			System.out.println("java.library.path = " + property);
			System.loadLibrary("Faust"); 
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
		}
    }

    public static void main(String args[]) throws InterruptedException {
		System.out.println("Test libfaust");
        
        // noise generator
        String prog = "random = +(12345)~*(1103515245); noise = random/2147483647.0; process = noise * vslider(\"Volume\", 0.5, 0, 1, 0.01)<:_,_;";
   
        llvm_dsp_factory factory = Faust.createCDSPFactoryFromString("noise", prog, 0, null, "", "", 3);
        llvm_dsp dsp = Faust.createCDSPInstance(factory);
        
        System.out.println(Faust.getCName(factory));
        System.out.println(Faust.getCSHAKey(factory));
    
        System.out.println(Faust.getNumInputsCDSPInstance(dsp));
        System.out.println(Faust.getNumOutputsCDSPInstance(dsp));
    }
}