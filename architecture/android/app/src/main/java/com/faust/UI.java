package com.faust;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Point;
import android.view.Display;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.util.Log;

/*
 * REMARKS:
 * 	- All the UI elements with a size greater than 2 pixels vary
 * 	in function of the screen definition. The others are considered
 * 	to be neglectable. The size of the text is the only exception and
 * 	remains the same on every screen. Perhaps this should be changed?
 */

public class UI {
	/*
	 * Global Variables (accessible from outside the class).
	 */
	// string to store the full JSON description
	String JSONparameters = new String();
	// the values and parameters of the different UI elements saved and retrieved
	// every time a new activity is created
	ParametersInfo parametersInfo;
	/*
	 * Counters for the different UI element types with:
	 * parametersCounters[0]: hslider
	 * parametersCounters[1]: vslider
	 * parametersCounters[2]: knob
	 * parametersCounters[3]: nentry
	 * parametersCounters[4]: menu
	 * parametersCounters[5]: radio
	 * parametersCounters[7]: checkbox
	 * parametersCounters[8]: button
     * parametersCounters[9]: hbargraph
     * parametersCounters[10]: vbargraph
	 */
	int[] parametersCounters = {0,0,0,0,0,0,0,0,0,0};
	// global counter of the UI elements
	int parameterNumber = 0;
	// screen dimensions
	int screenSizeX, screenSizeY;
	// true if parameters were saved during a previous instance
	boolean isSavedParameters;
	// keyboard interface specified in the Faust code
	boolean hasKeyboard;
	// MultiParam interface specified in the Faust code
	boolean hasMulti;

	// public UI elements (accessible from outside the class)
	HorizontalScrollView horizontalScroll;
	HorizontalSlider[] hsliders;
	VerticalSlider[] vsliders;
	Knob[] knobs;
	Nentry[] nentries;
	Menu[] menus;
	Radio[] radios;
	Checkbox[] checkboxes;
	PushButton[] buttons;
	BarGraph[] bargraphs;

	ConfigWindow parametersWindow;

	SettingWindow settingWindow;

    private void updateAccGyr(final ParametersInfo parametersInfo, int index)
    {
        /*
         Log.d("FaustJava", "updateAccGyr :  " + index
         + " " + parametersInfo.accgyrType[index]
         + " " + parametersInfo.accgyrCurve[index]
         + " " + parametersInfo.accgyrMin[index]
         + " " + parametersInfo.accgyrCenter[index]
         + " " + parametersInfo.accgyrMax[index]);
         */

        if (parametersInfo.accgyrType[index] == 0) {
            FaustActivity.dspFaust.setAccConverter(index, -1, 0, 0, 0, 0); // -1 means no mapping
            FaustActivity.dspFaust.setGyrConverter(index, -1, 0, 0, 0, 0); // -1 means no mapping
        } else if (parametersInfo.accgyrType[index] <= 3) {
            FaustActivity.dspFaust.setAccConverter(index,
                                      parametersInfo.accgyrType[index] - 1,  // Java : from 0 to 3 (0 means no mapping), C : -1 to 2 (-1 means no mapping)
                                      parametersInfo.accgyrCurve[index],
                                      parametersInfo.accgyrMin[index],
                                      parametersInfo.accgyrCenter[index],
                                      parametersInfo.accgyrMax[index]);

        } else {
            FaustActivity.dspFaust.setGyrConverter(index,
                                      parametersInfo.accgyrType[index] - 4,  // Java : from 0 to 3 (0 means no mapping), C : -1 to 2 (-1 means no mapping)
                                      parametersInfo.accgyrCurve[index],
                                      parametersInfo.accgyrMin[index],
                                      parametersInfo.accgyrCenter[index],
                                      parametersInfo.accgyrMax[index]);
        }
    }

	/*
	 * Initialize parametersValues in function of the total
	 * number of parameters.
	 */
	public void initUI(ParametersInfo paramsInfo, SharedPreferences settings) {
		parametersWindow = new ConfigWindow();
		settingWindow = new SettingWindow();

		// get the JSON description from the native code
		JSONparameters = FaustActivity.dspFaust.getJSONUI();

		// get the total number of parameters
		int numberOfParameters = FaustActivity.dspFaust.getParamsCount();

		// get the number of each UI elements
		int numberOfVsliders = countStringOccurrences(JSONparameters,"vslider");
		int numberOfHsliders = countStringOccurrences(JSONparameters,"hslider");
		int numberOfKnobs = countStringOccurrences(JSONparameters,"knob");
		int numberOfNentries = countStringOccurrences(JSONparameters,"nentry");
		int numberOfMenus = countStringOccurrences(JSONparameters,"menu");
		int numberOfRadios = countStringOccurrences(JSONparameters,"radio");
		int numberOfCheckboxes = countStringOccurrences(JSONparameters,"checkbox");
		int numberOfButtons = countStringOccurrences(JSONparameters,"button");
		int numberOfBarGraphs = countStringOccurrences(JSONparameters,"hbargraph") +
				countStringOccurrences(JSONparameters,"vbargraph");

		// the instance of ParametersInfo from the class Faust is associated to parametersInfo
		parametersInfo = paramsInfo;

		// the addresses of each param in the tree are retrieved from the native code
		for(int i = 0; i < numberOfParameters; i++) {
			parametersInfo.address[i] = FaustActivity.dspFaust.getParamAddress(i);
		}

		// the saved parameters of each UI element are retrieved
		isSavedParameters = parametersInfo.loadParameters(settings);

		// UI elements are instantiated
		if (numberOfVsliders > 0) vsliders = new VerticalSlider[numberOfVsliders];
		if (numberOfHsliders > 0) hsliders = new HorizontalSlider[numberOfHsliders];
		if (numberOfKnobs > 0) knobs = new Knob[numberOfKnobs];
		if (numberOfNentries > 0) nentries = new Nentry[numberOfNentries];
		if (numberOfMenus > 0) menus = new Menu[numberOfMenus];
		if (numberOfRadios > 0) radios = new Radio[numberOfRadios];
		if (numberOfCheckboxes > 0) checkboxes = new Checkbox[numberOfCheckboxes];
		if (numberOfButtons > 0) buttons = new PushButton[numberOfButtons];
		if (numberOfBarGraphs > 0) bargraphs = new BarGraph[numberOfBarGraphs];
	}

	/*
	 * Extract the UI element of the JSON description
	 */
	public JSONArray getJSONui() {
        JSONArray uiArray = new JSONArray();
        try {
			JSONObject parametersObject = new JSONObject(JSONparameters);
			uiArray = parametersObject.getJSONArray("ui");
		} catch (Exception e) {
			e.printStackTrace();
		}
        return uiArray;
	}

	/*
	 * Build the UI in function of the JSON description by calling the
	 * first iteration of parseJSON().
	 */
	public void buildUI(Context c, LinearLayout mainGroup) {
		int groupLevel = 0;
		WindowManager wm = (WindowManager) c.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		screenSizeX = size.x;
		screenSizeY = size.y;
		parametersWindow.buildWindow(c);
		settingWindow.buildWindow(c);
		JSONArray uiArray = getJSONui();

		// TODO Dirty way to detect keyboard: could be improved
        if (uiArray.toString().contains("\"style\":\"keyboard\"")) {
            hasMulti = false;
            hasKeyboard = true;
        }
        else if (uiArray.toString().contains("\"style\":\"multi\"")) {
            hasMulti = true;
            hasKeyboard = false;
        }
        else if (uiArray.toString().contains("\"style\":\"multikeyboard\"")) {
            hasMulti = true;
            hasKeyboard = true;
        }
        else {
            hasMulti = false;
            hasKeyboard = false;
        }

		parseJSON(c,uiArray,mainGroup,groupLevel,0,Math.round(screenSizeX*(1+parametersInfo.zoom*0.1f)));
	}

	/*
	 * Returns the content of a specific "member" of a JSON "object" contained
	 * in the meta member
	 */
	public String parseJSONMetaData(JSONObject object, String member) {
		JSONArray currentArray = new JSONArray();
		JSONObject currentObject = new JSONObject();
		String value = new String();
		try {
			// gets the content of the meta member
			currentArray = object.getJSONArray("meta");
			// we parse the object
			int length = currentArray.length();
			for (int i = 0; i < length; i++) {
				currentObject = currentArray.getJSONObject(i);
				try {
					value = currentObject.getString(member);
				} catch (JSONException e) {}
			}
		} catch (JSONException e) {}
		// returns the content of the member or
		// null if it doesn't exist
		return value;
	}

	/*
	 * Parse a JSON array and build the UI elements in function of the content
	 * PARAMETERS:
	 * 	c: context (this)
	 * 	uiArray: the JSON array to analyze
	 * 	currentGroup: the current group
	 * 	currentGroupLevel: the ID of the current group
	 * 	currentGroupType: 0 for vertical, 1 for horizontal
	 * 	currentViewWidth: the current group width
	 */
	public void parseJSON(Context c, JSONArray uiArray, LinearLayout currentGroup,
                        int currentGroupLevel, int currentGroupType, int currentViewWidth)
    {
		int nItemsTopLevel = uiArray.length(), groupDivisions;
		JSONObject currentObject = new JSONObject();
		JSONArray currentArray = new JSONArray();
		if (currentGroupType == 0) groupDivisions = 1;
		else groupDivisions = nItemsTopLevel;
		int localPadding = 10*screenSizeX/800;
		int localScreenWidth = (currentViewWidth-localPadding*2)/groupDivisions;
		int localBackgroundColor = currentGroupLevel*15;

		try {
			for (int i = 0; i < nItemsTopLevel; i++) {
				boolean paramVisible = true;
				currentObject = uiArray.getJSONObject(i);
				String metaDataStyle = parseJSONMetaData(currentObject, "style");
                String metaDataHidden = parseJSONMetaData(currentObject, "hidden");
				String metaDataMulti = parseJSONMetaData(currentObject, "multi");

				if (!isSavedParameters) {

                    // New accgyrerometer MetaData
					String metaDataAcc = parseJSONMetaData(currentObject, "acc");
                	if (!metaDataAcc.equals("")) {
          				float[] accParams = {0,0,0,0,0};
						for(int j = 0; j < 4; j++) {
							accParams[j] = Float.valueOf(metaDataAcc.substring(0, metaDataAcc.indexOf(" ")));
							metaDataAcc = metaDataAcc.substring(metaDataAcc.indexOf(" ")+1);
						}
						accParams[4] = Float.valueOf(metaDataAcc);
                        parametersInfo.accgyrType[parameterNumber] = (int) accParams[0] + 1;  // Java : from 1 to 3
						parametersInfo.accgyrCurve[parameterNumber] = (int) accParams[1];
						parametersInfo.accgyrMin[parameterNumber] = accParams[2];
						parametersInfo.accgyrCenter[parameterNumber] = accParams[3];
						parametersInfo.accgyrMax[parameterNumber] = accParams[4];
                    }

                    // New gyroscope MetaData
                    String metaDataGyr = parseJSONMetaData(currentObject, "gyr");
                    if (!metaDataGyr.equals("")) {
                        float[] gyrParams = {0,0,0,0,0};
                        for(int j = 0; j < 4; j++) {
                            gyrParams[j] = Float.valueOf(metaDataGyr.substring(0, metaDataGyr.indexOf(" ")));
                            metaDataGyr = metaDataGyr.substring(metaDataGyr.indexOf(" ")+1);
                        }
                        gyrParams[4] = Float.valueOf(metaDataGyr);
                        parametersInfo.accgyrType[parameterNumber] = (int) gyrParams[0] + 4;  // Java : from 4 to 6
                        parametersInfo.accgyrCurve[parameterNumber] = (int) gyrParams[1];
                        parametersInfo.accgyrMin[parameterNumber] = gyrParams[2];
                        parametersInfo.accgyrCenter[parameterNumber] = gyrParams[3];
                        parametersInfo.accgyrMax[parameterNumber] = gyrParams[4];
                    }
                }

				// Skipping freq, gain and gate if a keyboard interface was specified
				if (hasKeyboard && (currentObject.getString("label").equals("freq") ||
                    currentObject.getString("label").equals("gain") ||
                    currentObject.getString("label").equals("gate"))) {
					paramVisible = false;
				}

                if (metaDataHidden.equals("1")) {
                    paramVisible = false;
                }
                // tgroup handled like vgroup
                if (currentObject.getString("type").equals("tgroup") || currentObject.getString("type").equals("vgroup")) {
					currentArray = currentObject.getJSONArray("items");
					vgroup(c,currentArray,currentGroup,currentObject.getString("label"),
							currentGroupLevel,groupDivisions,currentViewWidth);
				}
            	else if (currentObject.getString("type").equals("hgroup")) {
					currentArray = currentObject.getJSONArray("items");
					hgroup(c,currentArray,currentGroup,currentObject.getString("label"),
							currentGroupLevel,groupDivisions,currentViewWidth);
				}
				else if (currentObject.getString("type").equals("vslider")
                         || currentObject.getString("type").equals("hslider")
                         || currentObject.getString("type").equals("nentry")) {

					if (!isSavedParameters) {
						if (isNumeric(metaDataMulti)) {
							parametersInfo.order[parameterNumber] = Integer.valueOf(metaDataMulti);
							parametersInfo.nMultiParams++;
						}
						else parametersInfo.order[parameterNumber] = -1;
						parametersInfo.label[parameterNumber] = currentObject.getString("label");
						parametersInfo.min[parameterNumber] = Float.parseFloat(currentObject.getString("min"));
						parametersInfo.max[parameterNumber] = Float.parseFloat(currentObject.getString("max"));
						parametersInfo.step[parameterNumber] = Float.parseFloat(currentObject.getString("step"));
             		}

					if (metaDataStyle.equals("knob")) {
						knob(c, currentGroup, currentObject.getString("address"),
								currentObject.getString("label"),
								Float.parseFloat(currentObject.getString("init")),
								Float.parseFloat(currentObject.getString("min")),
								Float.parseFloat(currentObject.getString("max")),
								Float.parseFloat(currentObject.getString("step")),
								localScreenWidth,localBackgroundColor,localPadding,paramVisible);
					}
                    else if (metaDataStyle.contains("menu")) {
						menu(c,currentGroup,currentObject.getString("address"),
								currentObject.getString("label"),
								localScreenWidth,localBackgroundColor,metaDataStyle,paramVisible);
					}
                    else if (metaDataStyle.contains("radio")) {
						radio(c,currentGroup,currentObject.getString("address"),
								currentObject.getString("label"),
                              localScreenWidth,localBackgroundColor,metaDataStyle,(currentObject.getString("type").equals("vslider")?0:1),paramVisible);
					}
                    else if (currentObject.getString("type").equals("vslider")) {
						vslider(c,currentGroup,currentObject.getString("address"),
								currentObject.getString("label"),
								Float.parseFloat(currentObject.getString("init")),
								Float.parseFloat(currentObject.getString("min")),
								Float.parseFloat(currentObject.getString("max")),
								Float.parseFloat(currentObject.getString("step")),
								localScreenWidth,localBackgroundColor,paramVisible);
                    }
					else if (currentObject.getString("type").equals("hslider")) {
                        hslider(c, currentGroup, currentObject.getString("address"),
                                currentObject.getString("label"),
                                Float.parseFloat(currentObject.getString("init")),
                                Float.parseFloat(currentObject.getString("min")),
                                Float.parseFloat(currentObject.getString("max")),
                                Float.parseFloat(currentObject.getString("step")),
                                localScreenWidth,localBackgroundColor,localPadding,paramVisible);
                    }
                    else if (currentObject.getString("type").equals("nentry")) {
                        nentry(c,currentGroup,currentObject.getString("address"),
                               currentObject.getString("label"),
                               Float.parseFloat(currentObject.getString("init")),
                               Float.parseFloat(currentObject.getString("min")),
                               Float.parseFloat(currentObject.getString("max")),
                               Float.parseFloat(currentObject.getString("step")),
                               localScreenWidth,localBackgroundColor,paramVisible);
                    }
					parameterNumber++;
				}
                else if (currentObject.getString("type").equals("button")) {
					button(c,currentGroup,currentObject.getString("address"),
							currentObject.getString("label"),
							localScreenWidth,localBackgroundColor,paramVisible);
					parameterNumber++;
				}
				else if (currentObject.getString("type").equals("checkbox")) {
					checkbox(c,currentGroup,currentObject.getString("address"),
							currentObject.getString("label"),
							localScreenWidth,localBackgroundColor,paramVisible);
					parameterNumber++;
				}
				else if (currentObject.getString("type").equals("hbargraph")) {
					hbargraph(c, currentGroup, currentObject.getString("address"),
							currentObject.getString("label"),
							Float.parseFloat(currentObject.getString("min")),
							Float.parseFloat(currentObject.getString("max")),
							localScreenWidth,localBackgroundColor,paramVisible);
					parameterNumber++;
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void updateUIstate() {
		for (int i = 0; i < 10; i++) {
			parametersCounters[i] = 0;
		}
		for (int i = 0; i < parameterNumber; i++) {
			if (parametersInfo.parameterType[i] == 0) {       //0: hslider
				hsliders[parametersCounters[0]].setValue(FaustActivity.dspFaust.getParamValue(hsliders[parametersCounters[0]].address));
				parametersCounters[0]++;
			}
			else if (parametersInfo.parameterType[i] == 1) {  //1: vslider
				vsliders[parametersCounters[1]].setValue(FaustActivity.dspFaust.getParamValue(vsliders[parametersCounters[1]].address));
				parametersCounters[1]++;
			}
			else if (parametersInfo.parameterType[i] == 2) {  //2 : knob
				knobs[parametersCounters[2]].setValue(FaustActivity.dspFaust.getParamValue(knobs[parametersCounters[2]].address));
				parametersCounters[2]++;
			}
			else if (parametersInfo.parameterType[i] == 3) {  //3 : nentry
				nentries[parametersCounters[3]].setValue(FaustActivity.dspFaust.getParamValue(nentries[parametersCounters[3]].address));
				parametersCounters[3]++;
			}
			else if (parametersInfo.parameterType[i] == 9) {  //9 : hbargraph
				bargraphs[parametersCounters[9]].setValue(FaustActivity.dspFaust.getParamValue(bargraphs[parametersCounters[9]].address));
				parametersCounters[9]++;
			}
		}
		// Other parameters are ignored because they are not continuous
	}

	public void reloadUIstate() {
		for (int i = 0; i < 10; i++) {
			parametersCounters[i] = 0;
		}
		for (int i = 0; i < parameterNumber; i++) {
			if (parametersInfo.parameterType[i] == 0) {       //0: hslider
				FaustActivity.dspFaust.setParamValue(hsliders[parametersCounters[0]].address, parametersInfo.values[i]);
				hsliders[parametersCounters[0]].setValue(FaustActivity.dspFaust.getParamValue(hsliders[parametersCounters[0]].address));
				parametersCounters[0]++;
			}
			else if (parametersInfo.parameterType[i] == 1) {  //1: vslider
				FaustActivity.dspFaust.setParamValue(vsliders[parametersCounters[1]].address, parametersInfo.values[i]);
				vsliders[parametersCounters[1]].setValue(FaustActivity.dspFaust.getParamValue(vsliders[parametersCounters[1]].address));
				parametersCounters[1]++;
			}
			else if (parametersInfo.parameterType[i] == 2) {  //2 : knob
				FaustActivity.dspFaust.setParamValue(knobs[parametersCounters[2]].address, parametersInfo.values[i]);
				knobs[parametersCounters[2]].setValue(FaustActivity.dspFaust.getParamValue(knobs[parametersCounters[2]].address));
                parametersCounters[2]++;
			}
			else if (parametersInfo.parameterType[i] == 3) {  //3 : nentry
				FaustActivity.dspFaust.setParamValue(nentries[parametersCounters[3]].address, parametersInfo.values[i]);
				nentries[parametersCounters[3]].setValue(FaustActivity.dspFaust.getParamValue(nentries[parametersCounters[3]].address));
				parametersCounters[3]++;
			}
			else if (parametersInfo.parameterType[i] == 9) {  //9 : hbargraph
				FaustActivity.dspFaust.setParamValue(bargraphs[parametersCounters[9]].address, parametersInfo.values[i]);
				bargraphs[parametersCounters[9]].setValue(FaustActivity.dspFaust.getParamValue(bargraphs[parametersCounters[9]].address));
                parametersCounters[9]++;
            }
		}
		// Other parameters are ignored because they are not continuous
	}
	
	public void initUIstate() {
		for (int i = 0; i < 10; i++) {
			parametersCounters[i] = 0;
		}
		for (int i = 0; i < parameterNumber; i++) {
			if (parametersInfo.parameterType[i] == 0) {       //0: hslider
				hsliders[parametersCounters[0]].setValue(FaustActivity.dspFaust.getParamInit(hsliders[parametersCounters[0]].address));
				parametersCounters[0]++;
			}
			else if (parametersInfo.parameterType[i] == 1) {  //1: vslider
				vsliders[parametersCounters[1]].setValue(FaustActivity.dspFaust.getParamInit(vsliders[parametersCounters[1]].address));
				parametersCounters[1]++;
			}
			else if (parametersInfo.parameterType[i] == 2) {  //2 : knob
				knobs[parametersCounters[2]].setValue(FaustActivity.dspFaust.getParamInit(knobs[parametersCounters[2]].address));
				parametersCounters[2]++;
			}
			else if (parametersInfo.parameterType[i] == 3) {  //3 : nentry
				nentries[parametersCounters[3]].setValue(FaustActivity.dspFaust.getParamInit(nentries[parametersCounters[3]].address));
				parametersCounters[3]++;
			}
			else if (parametersInfo.parameterType[i] == 9) {  //9 : hbargraph
				bargraphs[parametersCounters[9]].setValue(FaustActivity.dspFaust.getParamInit(bargraphs[parametersCounters[9]].address));
				parametersCounters[9]++;

			}
		}
		// Other parameters are ignored because they are not continuous
	}

	public void hbargraph(Context c, LinearLayout currentGroup, final String address, final String label,
			final float min, final float max, int localScreenWidth, int localBackgroundColor, boolean visibility) {
		bargraphs[parametersCounters[9]] = new BarGraph(c, address,parameterNumber, null, android.R.attr.progressBarStyleHorizontal, localScreenWidth, localBackgroundColor, visibility);
		bargraphs[parametersCounters[9]].id = parameterNumber;
		bargraphs[parametersCounters[9]].min = min;
		bargraphs[parametersCounters[9]].max = max;
        bargraphs[parametersCounters[9]].addTo(currentGroup);

        parametersInfo.parameterType[parameterNumber] = 9;
        parametersInfo.localId[parameterNumber] = parametersCounters[9];
        parametersCounters[9]++;
	}

	/*
	 * Creates a drop down menu and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 *  label: the name of the menu
	 *  localScreenWidth: width of the view
	 *  localBackgroundColor: background color of the view
	 *  currentGroupLevel: the "depth" of the parameter in the UI
	 *  parameters: string containing the parameters of the menu extracted
	 *  	from the JSON description
	 */
	//TODO: init?
	public void menu(Context c, LinearLayout currentGroup, final String address, final String label,
			int localScreenWidth, int localBackgroundColor, String parameters, boolean visibility) {

		String parsedParameters = parameters.substring(parameters.indexOf("{") + 1,
				parameters.indexOf("}"));
		menus[parametersCounters[4]] = new Menu(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, parsedParameters, visibility);
		menus[parametersCounters[4]].setLabel(label);
		int init = 0;
		if (isSavedParameters) init = (int) parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		menus[parametersCounters[4]].setSelection(init);
        menus[parametersCounters[4]].linkTo(parametersInfo);
	    menus[parametersCounters[4]].addTo(currentGroup);

        //FaustActivity.dspFaust.setParamValue(address, init);
	    parametersInfo.parameterType[parameterNumber] = 4;
	    parametersInfo.localId[parameterNumber] = parametersCounters[4];
	    parametersCounters[4]++;
	}

	/*
	 * Creates a radio buttons menu and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 *  label: the name of the menu
	 *  localScreenWidth: width of the view
	 *  localBackgroundColor: background color of the view
	 *  currentGroupLevel: the "depth" of the parameter in the UI
	 *  parameters: string containing the parameters of the menu extracted
	 *  	from the JSON description
	 *  orientation: 0 for vertical, 1 for horizontal
	 */
	//TODO: init?
	public void radio(Context c, LinearLayout currentGroup, final String address, final String label,
			int localScreenWidth, int localBackgroundColor, String parameters, int orientation, boolean visibility) {

		String parsedParameters = parameters.substring(parameters.indexOf("{") + 1, parameters.indexOf("}"));
    	int init = 0;
		if (isSavedParameters) init = (int)parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		radios[parametersCounters[5]] = new Radio(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, parsedParameters, orientation, init, visibility);
		radios[parametersCounters[5]].setLabel(label);
        radios[parametersCounters[5]].linkTo(parametersInfo);
	    radios[parametersCounters[5]].addTo(currentGroup);

        //FaustActivity.dspFaust.setParamValue(address, init);
	    parametersInfo.parameterType[parameterNumber] = 5;
	    parametersInfo.localId[parameterNumber] = parametersCounters[5];
	    parametersCounters[5]++;
	}

	/*
	 * Creates a horizontal slider and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  init: the default item of the menu
	 *  min: the minimum value
	 *  max: the maximum value
	 *  step: the slider step
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 *  localPadding: the padding of the view
	 */
	public void hslider(Context c, LinearLayout currentGroup, final String address, final String label, float init,
			final float min, final float max, final float step, int localScreenWidth, int localBackgroundColor,
			int localPadding, boolean visibility) {

        // the slider
		hsliders[parametersCounters[0]] = new HorizontalSlider(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, localPadding, visibility);
		hsliders[parametersCounters[0]].setParams(label, min, max, step);
    	if (isSavedParameters) init = parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		hsliders[parametersCounters[0]].setValue(init);
	    hsliders[parametersCounters[0]].linkTo(parametersInfo, parametersWindow, horizontalScroll);
	    hsliders[parametersCounters[0]].addTo(currentGroup);

        // Accelerometer mappings restored before so that we are sure they are allocated on C side before restoring the actual values...
        updateAccGyr(parametersInfo, parameterNumber);
        
        //FaustActivity.dspFaust.setParamValue(address, init);
        parametersInfo.parameterType[parameterNumber] = 0;
	    parametersInfo.localId[parameterNumber] = parametersCounters[0];
	    parametersCounters[0]++;
	}

	/*
	 * Creates a vertical slider and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  init: the default item of the menu
	 *  min: the minimum value
	 *  max: the maximum value
	 *  step: the slider step
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 */
	public void vslider(Context c, LinearLayout currentGroup, final String address, final String label, float init,
			final float min, final float max, final float step, int localScreenWidth, int localBackgroundColor,
			boolean visibility) {

		// the slider
		vsliders[parametersCounters[1]] = new VerticalSlider(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, visibility);
        vsliders[parametersCounters[1]].setParams(label, min, max, step);
    	if (isSavedParameters) init = parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		vsliders[parametersCounters[1]].setValue(init);
	    vsliders[parametersCounters[1]].linkTo(parametersInfo, parametersWindow, horizontalScroll);
	    vsliders[parametersCounters[1]].addTo(currentGroup);

        // Accelerometer mappings restored before so that we are sure they are allocated on C side before restoring the actual values...
        updateAccGyr(parametersInfo, parameterNumber);
    
        //FaustActivity.dspFaust.setParamValue(address, init);
        parametersInfo.parameterType[parameterNumber] = 1;
	    parametersInfo.localId[parameterNumber] = parametersCounters[1];
	    parametersCounters[1]++;
	}

	/*
	 * Creates a knob and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  init: the default item of the menu
	 *  min: the minimum value
	 *  max: the maximum value
	 *  step: the slider step
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 *  localPadding: the padding of the view
	 */
	public void knob(Context c, LinearLayout currentGroup, final String address, final String label, float init,
			final float min, final float max, final float step, int localScreenWidth, int localBackgroundColor,
			int localPadding, boolean visibility) {

		knobs[parametersCounters[2]] = new Knob(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, localPadding, visibility);
		knobs[parametersCounters[2]].setParams(label, min, max, step);
        if (isSavedParameters) init = parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		knobs[parametersCounters[2]].setValue(init);
	    knobs[parametersCounters[2]].linkTo(parametersInfo, parametersWindow, horizontalScroll);
	    knobs[parametersCounters[2]].addTo(currentGroup);

        // Accelerometer mappings restored before so that we are sure they are allocated on C side before restoring the actual values...
        updateAccGyr(parametersInfo, parameterNumber);
        
        //FaustActivity.dspFaust.setParamValue(address, init);
	    parametersInfo.parameterType[parameterNumber] = 2;
	    parametersInfo.localId[parameterNumber] = parametersCounters[2];
	    parametersCounters[2]++;
	}

	/*
	 * Creates a nentry and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  init: the default item of the menu
	 *  min: the minimum value
	 *  max: the maximum value
	 *  step: the slider step
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 */
	public void nentry(Context c, LinearLayout currentGroup, final String address, final String label, float init,
			final float min, final float max, final float step, int localScreenWidth, int localBackgroundColor,
			boolean visibility) {

		nentries[parametersCounters[3]] = new Nentry(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, visibility);
		nentries[parametersCounters[3]].setParams(label, min, max, step);
		if (isSavedParameters) init = parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		nentries[parametersCounters[3]].setValue(init);
        nentries[parametersCounters[3]].linkTo(parametersInfo, parametersWindow);
	    nentries[parametersCounters[3]].addTo(currentGroup);

        // Accelerometer mappings restored before so that we are sure they are allocated on C side before restoring the actual values...
        updateAccGyr(parametersInfo, parameterNumber);
        
        //FaustActivity.dspFaust.setParamValue(address, init);
	    parametersInfo.parameterType[parameterNumber] = 3;
	    parametersInfo.localId[parameterNumber] = parametersCounters[3];
	    parametersCounters[3]++;
	}

	/*
	 * Creates a button and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 */
	public void button(Context c, LinearLayout currentGroup, final String address, final String label,
			int localScreenWidth, int localBackgroundColor, boolean visibility) {

		buttons[parametersCounters[6]] = new PushButton(c,address,parameterNumber,
				localScreenWidth, localBackgroundColor, label);
	    buttons[parametersCounters[6]].linkTo(parametersInfo);
	    if (visibility) buttons[parametersCounters[6]].addTo(currentGroup);
	    parametersInfo.parameterType[parameterNumber] = 6;
	    parametersInfo.localId[parameterNumber] = parametersCounters[6];
	    parametersCounters[6]++;
	}

	/*
	 * Creates a button and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 * 	currentGroup: the group to add the menu
	 * 	address: the parameter address
	 *  label: the name of the menu
	 *  localScreenWidth: the width of the view
	 *  localBackgroundColor: the background color of the view
	 */
	public void checkbox(Context c, LinearLayout currentGroup, final String address, final String label,
			int localScreenWidth, int localBackgroundColor, boolean visibility) {

        int height = Math.round(screenSizeY*0.1f);
		checkboxes[parametersCounters[7]] = new Checkbox(c,address,parameterNumber,
				localScreenWidth, height, localBackgroundColor, label);
		float init = 0.0f; //default value for the checkbox
		if (isSavedParameters) init = parametersInfo.values[parameterNumber];
		else parametersInfo.values[parameterNumber] = init;
		checkboxes[parametersCounters[7]].setStatus(init);
	    checkboxes[parametersCounters[7]].linkTo(parametersInfo);
	    if (visibility) checkboxes[parametersCounters[7]].addTo(currentGroup);
        
        //FaustActivity.dspFaust.setParamValue(address, init);
	    parametersInfo.parameterType[parameterNumber] = 7;
	    parametersInfo.localId[parameterNumber] = parametersCounters[7];
	    parametersCounters[7]++;
	}

	/*
	 * Creates a vertical group and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 *  currentArray: current JSON array containing the items of the group
	 * 	currentGroup: the group to add the menu
	 *  label: the name of the menu
	 *  currentGroupLevel: current group's depth
	 *  nItemsUpperLevel: number of items in the upper group
	 *  upperViewWidth: width of the upper group
	 */
	public void vgroup(Context c, JSONArray currentArray, LinearLayout currentGroup, String label,
			int currentGroupLevel, int nItemsUpperLevel, int upperViewWidth) {
		// frame to create some padding around the view
		LinearLayout frame = new LinearLayout(c);
		// the local group
		LinearLayout localGroup = new LinearLayout(c);

		// for the local groups background color
		int localGroupLevel = currentGroupLevel+1;
		// padding is adjusted in function of the screen definition
		int padding = 10*screenSizeX/800;
		int currentViewPadding = padding;
		if (currentGroupLevel == 0) currentViewPadding = 0;
		int localViewWidth  = (upperViewWidth-currentViewPadding*2)/nItemsUpperLevel;

		// frame to create some padding around the view
		// the layout's width is "hard coded"
		frame.setLayoutParams(new ViewGroup.LayoutParams(
				localViewWidth, ViewGroup.LayoutParams.WRAP_CONTENT));
		frame.setOrientation(LinearLayout.VERTICAL);
		frame.setBackgroundColor(Color.rgb(currentGroupLevel*15,
				currentGroupLevel*15, currentGroupLevel*15));
		frame.setPadding(2,2,2,2);

		localGroup.setOrientation(LinearLayout.VERTICAL);
		localGroup.setBackgroundColor(Color.rgb(localGroupLevel*15,localGroupLevel*15,localGroupLevel*15));
		localGroup.setPadding(padding,padding,padding,padding);

		if (!label.contains("0x00")) {
			TextView textLabel = new TextView(c);
			textLabel.setText(label);
			textLabel.setTextSize(22.f);
			localGroup.addView(textLabel);
		}

		frame.addView(localGroup);
		currentGroup.addView(frame);

		// we iterate the group's items
		parseJSON(c,currentArray,localGroup,localGroupLevel,0,localViewWidth);
	}

	/*
	 * Creates a horizontal group and adds it to currentGroup.
	 * PARAMETERS:
	 * 	c: the context (this)
	 *  currentArray: current JSON array containing the items of the group
	 * 	currentGroup: the group to add the menu
	 *  label: the name of the menu
	 *  currentGroupLevel: current group's depth
	 *  nItemsUpperLevel: number of items in the upper group
	 *  upperViewWidth: width of the upper group
	 */
	public void hgroup(Context c, JSONArray currentArray, LinearLayout currentGroup, String label,
			int currentGroupLevel, int nItemsUpperLevel, int upperViewWidth) {
		// frame to create some padding around the view
		LinearLayout frame = new LinearLayout(c);
		// the local group
		LinearLayout localGroup = new LinearLayout(c);
		// the local vertical group (required to have the group name above the content of the group)
		LinearLayout localVerticalGroup = new LinearLayout(c);

		// for the local groups background color
		int localGroupLevel = currentGroupLevel+1;
		// padding is adjusted in function of the screen definition
		int padding = 10*screenSizeX/800;
		int currentViewPadding = padding;
		if (currentGroupLevel == 0) currentViewPadding = 0;
		int localViewWidth = (upperViewWidth-currentViewPadding*2)/nItemsUpperLevel;

		localGroup.setOrientation(LinearLayout.HORIZONTAL);

		// frame to create some padding around the view
		// the layout's width is "hard coded"
		frame.setLayoutParams(new ViewGroup.LayoutParams(
				localViewWidth, ViewGroup.LayoutParams.WRAP_CONTENT));
		frame.setOrientation(LinearLayout.VERTICAL);
		frame.setBackgroundColor(Color.rgb(currentGroupLevel*15,
				currentGroupLevel*15, currentGroupLevel*15));
		frame.setPadding(2,2,2,2);

		localVerticalGroup.setOrientation(LinearLayout.VERTICAL);
		localVerticalGroup.setBackgroundColor(Color.rgb(localGroupLevel*15,localGroupLevel*15,localGroupLevel*15));
		localVerticalGroup.setPadding(padding,padding,padding,padding);

		if (!label.contains("0x00")) {
			TextView textLabel = new TextView(c);
			textLabel.setText(label);
			textLabel.setTextSize(22.f);
			localVerticalGroup.addView(textLabel);
		}

		localVerticalGroup.addView(localGroup);
		frame.addView(localVerticalGroup);
		currentGroup.addView(frame);

		// we iterate the group's items
		parseJSON(c,currentArray,localGroup,localGroupLevel,1,localViewWidth);
	}

	/*
	 * Count the number of pattern in input
	 */
	private int countStringOccurrences(String input, String pattern) {
		int lastIndex = 0, count = 0;
		while (lastIndex != -1) {
			lastIndex = input.indexOf(pattern,lastIndex);
			if (lastIndex != -1) {
				count ++;
				lastIndex += pattern.length();
			}
		}
		return count;
	}

	/*
	 * Check if a string is numeric
	 */
	private static boolean isNumeric(String str)
	{
        try {
            double d = Double.parseDouble(str);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
	}
}
