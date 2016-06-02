package faustProcessing;

import java.io.*;
import processing.core.*;
import com.grame.faust.*;

public class FaustProcessing {
	PApplet parent;
	dsp	myDSP;

	// transfert depuis le code processing du chargement de la librairie
	static {
	  try {
		String property = System.getProperty("java.library.path");
		System.out.println("java.library.path = " + property);
		System.loadLibrary("FaustEngine");
	  } 
	  catch (UnsatisfiedLinkError e) {
		System.err.println("Native code library failed to load.\n" + e);
		System.exit(1);
	  }
	}

 //:/Users/yannorlarey/Documents/Processing/libraries/faustProcessing/library:/Users/yannorlarey/Documents/Processing/libraries/controlP5/library::/Applications/Processing.app/Contents/Java:/Applications/Processing.app/Contents/MacOS

	public FaustProcessing(PApplet parent, String name, String code) {
    	this.parent = parent;
    	parent.registerMethod("dispose", this);

		System.out.println("\nSalut Yann");
		// determination du path des librairies Faust
		String suffix = "faustProcessing/library";
		String path = System.getProperty("java.library.path");
		String subpath = path.substring(0,path.indexOf(suffix)+suffix.length());
		String faustpath = subpath.substring(subpath.lastIndexOf(":")+1,subpath.length());
		System.out.println("Faust path is : "+ faustpath);
		// creation automatique d'un processeur
		myDSP = FaustEngine.create2Dsp(name, code, "-I " + faustpath, "", 3);
		//myDSP = FaustEngine.create1(name, code);
		System.out.println("Faust created");
		if (myDSP != null) { 
			FaustEngine.init1Dsp(myDSP, name); 
			FaustEngine.startDsp(myDSP); 
		} else {
			System.out.println("Error "+ FaustEngine.getLastError());
		}
	}

	public void start() {
		if (myDSP != null) { FaustEngine.startDsp(myDSP); }
	}


	public void stop() {
		if (myDSP != null) { FaustEngine.stopDsp(myDSP); }
	}

  	public void dispose() {
    	// Anything in here will be called automatically when 
    	// the parent sketch shuts down. For instance, this might
    	// shut down a thread used by this library.
		System.out.println("Entering dispose()");
		if (myDSP != null) {
			FaustEngine.stopDsp(myDSP);
        	FaustEngine.destroyDsp(myDSP);
		}
		System.out.println("Exiting dispose()");
  	}

	// implementation of FaustEngine API
	
	public String getJSON() {
		if (myDSP != null) {
    		return FaustEngine.getJSONDsp(myDSP);
    	} else {
    		return "";
    	}
  	}

  	public int getParamsCount() {
  		if (myDSP != null) {
    		return FaustEngine.getParamsCountDsp(myDSP);
    	} else {
    		return 0;
    	}
  	}

  	public int getParamIndex(String name) {
  		if (myDSP != null) {
    		return FaustEngine.getParamIndexDsp(myDSP, name);
    	} else {
    		return 0;
    	}
  	}

  	public String getParamAddress(int p) {
  		if (myDSP != null) {
    		return FaustEngine.getParamAddressDsp(myDSP, p);
    	} else {
    		return "";
    	}
  	}

  	public String getParamUnit(int p) {
  		if (myDSP != null) {
    		return FaustEngine.getParamUnitDsp(myDSP, p);
    	} else {
    		return "";
    	}
  	}

  	public float getParamMin(int p) {
  		if (myDSP != null) {
    		return FaustEngine.getParamMinDsp(myDSP, p);
    	} else {
    		return 0f;
    	}
  	}

  	public float getParamMax(int p) {
   		if (myDSP != null) {
   			return FaustEngine.getParamMaxDsp(myDSP, p);
    	} else {
    		return 0f;
    	}
  	}

  	public float getParamStep(int p) {
  		if (myDSP != null) {
    		return FaustEngine.getParamStepDsp(myDSP, p);
    	} else {
    		return 0f;
    	}
  	}

  	public float getParamValue(int p) {
  		if (myDSP != null) {
    		return FaustEngine.getParamValueDsp(myDSP, p);
    	} else {
    		return 0f;
    	}
  	}

  	public void setParamValue(int p, float v) {
    	if (myDSP != null) {
    		FaustEngine.setParamValueDsp(myDSP, p, v);
    	}
  	}

  	public float getParamRatio(int p) {
    	if (myDSP != null) {
    		return FaustEngine.getParamRatioDsp(myDSP, p);
    	} else {
    		return 0f;
    	}
  	}

  	public void setParamRatio(int p, float v) {
  		if (myDSP != null) {
    		FaustEngine.setParamRatioDsp(myDSP, p, v);
    	}
  	}

  	public void propagateAccX(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateAccDsp(myDSP, 0, a);
    	}
  	}

  	public void propagateAccY(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateAccDsp(myDSP, 1, a);
    	}
  	}

  	public void propagateAccZ(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateAccDsp(myDSP, 2, a);
    	}
  	}
    
    public void propagateGyrX(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateGyrDsp(myDSP, 0, a);
    	}
  	}

  	public void propagateGyrY(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateGyrDsp(myDSP, 1, a);
    	}
  	}

  	public void propagateGyrZ(float a) {
  		if (myDSP != null) {
    		FaustEngine.propagateGyrDsp(myDSP, 2, a);
    	}
  	}
}
