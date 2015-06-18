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
        String prog = "random = +(12345)~*(1103515245); noise1 = random/2147483647.0; process = noise1 * vslider(\"Volume\", 0.5, 0, 1, 0.01)<:_,_;";
        
        //String argv = "-vec " + "-lv " + "1 ";
        
        String argv = "-vec " + "-lv " + "1 ";
        //String argv = "-vec " + "-lv " + "1 " + "-I " + "/Documents/faust-sf/embedded/faustjava/test_lib/";
        
        System.out.println(argv);
        
        llvm_dsp_factory factory = Faust.createCDSPFactoryFromStringAux("noise", prog, argv, "", 3);
        if (factory == null) {
            System.out.print(Faust.getCDSPLastError());
            return;
        }
         
        llvm_dsp dsp = Faust.createCDSPInstance(factory);
        
        System.out.println(Faust.getCName(factory));
        System.out.println(Faust.getCSHAKey(factory));
    
        System.out.println(Faust.getNumInputsCDSPInstance(dsp));
        System.out.println(Faust.getNumOutputsCDSPInstance(dsp));
    }
}