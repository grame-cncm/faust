package com.ccrma.faust;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PointF;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.util.SparseArray;
import android.view.MotionEvent;
import android.view.ViewGroup;

import com.DspFaust.DspFaust;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MultiKeyboard extends ViewGroup {
    // GRAPHICAL ELEMENTS
    private ArrayList<ArrayList<Zone>> zones;
    private int viewWidth;
    private int viewHeight;
    private int zoneWidths[];
    private int zoneHeight;
    private int borderSize;
    private int zoneCenterXOffset[]; // necessary on android because sizes are ints
    private int zoneCenterYOffset;
    private Boolean UIon; // true when UI is built (used to secure the rounding thread when there's no UI on the screen)

    // TOUCH TRACKING
    private SparseArray<PointF> mActivePointers;
    private float currentContinuousKey; // key number of the current keyboard as a float
    private float currentKeyboardY; // y position of finger on key (corresponds to the "y" parameter in Faust)
    private int fingersOnKeyboardsCount[]; // number of fingers present on each keyboard (used to limit polyphony)
    private int previousTouchedKeyboards[]; // the last keyboard touched by a specific finger on the screen
    private int previousTouchedKeys[]; // the last key touched by a specific finger on the screen
    private int monoMode_previousActiveFinger[]; // last active finger in mono mode (in case touch needs to canceled)
    private int fingersOnScreenCount;

    // PITCH ROUNDING
    private float touchDiff[]; // distance between 2 distinct touch events
    private boolean rounding[]; // tell if the current pitch should be rounded
    private Smooth smooth[]; // integrators for rounding detection
    private int moveCount[]; // counts the number of movements outside the threshold for each touch
    private long roundingUpdateSpeed; // the speed at which the rounding thread is updated
    private float refPitch[];

    // FAUST
    private DspFaust dspFaust;
    private long voices[];

    // OTHER
    private Context context;
    private String currentPresetName;
    private String documentsDirectory;
    private SensorManager mSensorManager;

    // Public variables
    public Map<String,Object> keyboardParameters;
    public Map<String,Object> dspParameters;

    public MultiKeyboard(Context c, DspFaust dsp, String presetName) {
        super(c);

        context = c;
        dspFaust = dsp;
        currentPresetName = presetName;
        borderSize = 2; // this parameter should theoretically be updated in function of screen width
        setBackgroundColor(Color.BLACK);

        documentsDirectory = context.getFilesDir().toString();

        keyboardParameters = new HashMap<String,Object>();

        if(currentPresetName == null) {
            keyboardParameters.put("Number of Keyboards", 1);
            keyboardParameters.put("Max Fingers", 10);
            keyboardParameters.put("Max Keyboard Polyphony", 16);
            keyboardParameters.put("Mono Mode", 1);
            keyboardParameters.put("Rounding Mode", 0);
            keyboardParameters.put("Inter-Keyboard Slide", 1);
            keyboardParameters.put("Send Current Key", 1);
            keyboardParameters.put("Send Current Keyboard", 1);
            keyboardParameters.put("Send Fingers Count", 0);
            keyboardParameters.put("Send Sensors", 1);
            keyboardParameters.put("Rounding Update Speed", (float) 0.06);
            keyboardParameters.put("Rounding Smooth", (float) 0.9);
            keyboardParameters.put("Rounding Threshold", (float) 3.0);
            keyboardParameters.put("Rounding Cycles", 5);


            String JSONInterface = dspFaust.getJSONMeta();
            if (JSONInterface.contains("SmartKeyboard{")) {
                String JSONSmartKeyboard = JSONInterface.substring(JSONInterface.indexOf("SmartKeyboard{") + 14);
                JSONSmartKeyboard = JSONSmartKeyboard.substring(0, JSONSmartKeyboard.indexOf("}"));

                while (JSONSmartKeyboard.contains("'")) {
                    JSONSmartKeyboard = JSONSmartKeyboard.substring(JSONSmartKeyboard.indexOf("'") + 1);
                    String currentKey = JSONSmartKeyboard.substring(0, JSONSmartKeyboard.indexOf("'"));
                    JSONSmartKeyboard = JSONSmartKeyboard.substring(JSONSmartKeyboard.indexOf("'") + 1);
                    JSONSmartKeyboard = JSONSmartKeyboard.substring(JSONSmartKeyboard.indexOf("'") + 1);
                    String currentValue = JSONSmartKeyboard.substring(0, JSONSmartKeyboard.indexOf("'"));
                    JSONSmartKeyboard = JSONSmartKeyboard.substring(JSONSmartKeyboard.indexOf("'") + 1);

                    // this is soooooo dirty...
                    try {
                        keyboardParameters.put(currentKey, Integer.parseInt(currentValue));
                    } catch (RuntimeException e){
                        try{
                            keyboardParameters.put(currentKey, Float.parseFloat(currentValue));
                        } catch (RuntimeException ee){
                            keyboardParameters.put(currentKey, currentValue);
                        }
                    }
                }
            } else {
                Log.e("Faust MultiKeyboard", "No valid SmartKeyboard description in Faust code");
            }
            dspParameters = new HashMap<String,Object>(); // empty dictionary in that case
        }
        else {
            try {
                loadPreset();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }

        mActivePointers = new SparseArray<PointF>();
        mSensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);

        buildInterface();

        if((int)keyboardParameters.get("Rounding Mode") == 2){
            Thread t = new Thread(new PitchRounding());
            t.start();
        }
    }

    private void loadPreset() throws IOException, ClassNotFoundException {
        // loading keyboard parameters
        FileInputStream fileInputStreamKeyb = new FileInputStream(documentsDirectory.concat("/").concat(currentPresetName).concat("_keyb"));
        ObjectInputStream objectInputStreamKeyb = new ObjectInputStream(fileInputStreamKeyb);
        keyboardParameters = (Map<String,Object>) objectInputStreamKeyb.readObject();

        // loading DSP parameters
        FileInputStream fileInputStreamDsp = new FileInputStream(documentsDirectory.concat("/").concat(currentPresetName).concat("_dsp"));
        ObjectInputStream objectInputStreamDsp = new ObjectInputStream(fileInputStreamDsp);
        dspParameters = (Map<String,Object>) objectInputStreamDsp.readObject();
    }

    public void buildInterface(){
        UIon = true;

        if((int)keyboardParameters.get("Send Sensors") == 1){
            mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(
                    Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
        }

        // keyboard dependent default parameters
        for(int i=0; i<(int)keyboardParameters.get("Number of Keyboards") ; i++){
            if(keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Number of Keys", i), 13);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Lowest Key",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Lowest Key", i), (60 + i * 12) % 127);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Scale",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Scale", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Show Labels",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Show Labels", i), 1);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Static Mode",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Static Mode", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Piano Keyboard",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Piano Keyboard", i), 1);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Root Position",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Root Position", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Orientation",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Orientation", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send X",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send X", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Y",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Y", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Numbered X",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Numbered X", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Numbered Y",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Numbered Y", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Key X",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Key X", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Key Y",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Key Y", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Key Status",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Key Status", i), 0);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Freq",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Freq", i), 1);
            }
            if(keyboardParameters.get(String.format("Keyboard %d - Send Keyboard Freq",i)) == null) {
                keyboardParameters.put(String.format("Keyboard %d - Send Keyboard Freq", i), 0);
            }
        }

        touchDiff = new float[(int)keyboardParameters.get("Max Fingers")];
        moveCount = new int[(int)keyboardParameters.get("Max Fingers")];
        rounding = new boolean[(int)keyboardParameters.get("Max Fingers")];
        previousTouchedKeys = new int[(int)keyboardParameters.get("Max Fingers")];
        previousTouchedKeyboards = new int[(int)keyboardParameters.get("Max Fingers")];
        smooth = new Smooth[(int)keyboardParameters.get("Max Fingers")];
        voices = new long[(int)keyboardParameters.get("Max Fingers")];
        refPitch = new float[(int)keyboardParameters.get("Max Fingers")];

        for(int i=0; i<(int)keyboardParameters.get("Max Fingers"); i++){
            touchDiff[i] = 0;
            previousTouchedKeys[i] = -1;
            previousTouchedKeyboards[i] = -1;
            moveCount[i] = 0;
            smooth[i] = new Smooth();
            smooth[i].setSmooth((float)keyboardParameters.get("Rounding Smooth"));
            rounding[i] = true;
            voices[i] = -1;
            refPitch[i] = 0;
        }

        fingersOnScreenCount = 0;
        roundingUpdateSpeed = (long)((float)keyboardParameters.get("Rounding Update Speed")*1000);

        zoneWidths = new int[(int)keyboardParameters.get("Number of Keyboards")];
        zoneCenterXOffset = new int[(int)keyboardParameters.get("Number of Keyboards")];
        fingersOnKeyboardsCount = new int[(int)keyboardParameters.get("Number of Keyboards")];
        monoMode_previousActiveFinger = new int[(int)keyboardParameters.get("Number of Keyboards")];

        // initializing the different keyboards
        zones = new ArrayList<>();
        for(int i=0; i<(int)keyboardParameters.get("Number of Keyboards") ; i++) {
            zones.add(new ArrayList<Zone>());
            fingersOnKeyboardsCount[i] = 0;
            monoMode_previousActiveFinger[i] = 0;
            for(int j=0; j<(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i)); j++) {
                zones.get(i).add(new Zone(context));
                zones.get(i).get(j).setStaticMode((int)keyboardParameters.get(String.format("Keyboard %d - Static Mode", i)) == 1);
                zones.get(i).get(j).showLabels((int)keyboardParameters.get(String.format("Keyboard %d - Show Labels", i)) == 1);
                if (((int)keyboardParameters.get(String.format("Keyboard %d - Piano Keyboard", i)) == 1) &&
                        ((int) keyboardParameters.get(String.format("Keyboard %d - Scale", i)) < 1) ) {
                    if ((int)keyboardParameters.get(String.format("Keyboard %d - Orientation", i)) == 1) {
                        zones.get(i).get(j).setNote((int) applyScale((int) keyboardParameters
                                .get(String.format("Keyboard %d - Lowest Key", i)) + (int) keyboardParameters.get(String.format("Keyboard %d - Number of Keys", i)) - j - 1, i));
                    } else {
                        zones.get(i).get(j).setNote((int) applyScale(j + (int)
                                keyboardParameters.get
                                        (String.format("Keyboard %d - Lowest Key", i)), i));
                    }
                }
                if (keyboardParameters.get(String.format("Keyboard %d - Key %d - Label",i,j)) != null){
                    zones.get(i).get(j).setText((String) keyboardParameters.get(String.format("Keyboard %d - Key %d - Label",i,j)));
                }
                zones.get(i).get(j).drawBackground();
                addView(zones.get(i).get(j));
            }

        }
        // case where no pitch keyboard is on: we trigger the main voice on startup
        if((int)keyboardParameters.get("Max Keyboard Polyphony") == 0){
            voices[0] = dspFaust.newVoice();
        }

        ArrayList<String> dspKeys = new ArrayList<String>();
        // retrieve the existing parameter keys and order alphabetically
        for (String key : dspParameters.keySet()) {
            dspKeys.add(key);
        }
        for(int i=0; i<dspKeys.size(); i++){
            dspFaust.setParamValue(dspKeys.get(i).toString(),(float)dspParameters.get(dspKeys.get(i)));
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int pointerIndex = event.getActionIndex();
        int pointerId = event.getPointerId(pointerIndex);
        int maskedAction = event.getActionMasked();

        switch (maskedAction) {

            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN: {
                // We have a new pointer. Lets add it to the list of pointers
                PointF point = new PointF();
                point.x = event.getX(pointerIndex);
                point.y = event.getY(pointerIndex);
                mActivePointers.put(pointerId, point);
                touchDiff[pointerId] = 0;
                processTouchEvent(1,point,pointerId,event);
                break;
            }
            case MotionEvent.ACTION_MOVE: { // a pointer was moved
                for (int size = event.getPointerCount(), i = 0; i < size; i++) {
                    int localPointerId = event.getPointerId(i);
                    PointF point = mActivePointers.get(localPointerId);
                    if (point != null && ((point.x != event.getX(i)) || (point.y != event.getY(i)))) {
                        point.x = event.getX(i);
                        point.y = event.getY(i);
                        if(event.getHistorySize()>0){
                            touchDiff[localPointerId] = Math.abs(point.x - event.getHistoricalX(event.findPointerIndex(localPointerId),0));
                        }
                        else {
                            touchDiff[localPointerId] = 0;
                        }
                        processTouchEvent(2,point,localPointerId,event);
                    }
                }
                break;
            }
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
            case MotionEvent.ACTION_CANCEL: {
                PointF point = new PointF();
                point.x = event.getX(pointerIndex);
                point.y = event.getY(pointerIndex);
                mActivePointers.remove(pointerId);
                touchDiff[pointerId] = -10000;
                processTouchEvent(0,point,pointerId,event);
                break;
            }
        }
        invalidate();

        return true;
    }

    private void processTouchEvent(int eventType, PointF touchPoint, int fingerId, MotionEvent event){
        // we calculate the position of the touch on the keyboards matrix
        int currentKeyboard = Math.min((int)(touchPoint.y/zoneHeight),((int)keyboardParameters.get("Number of Keyboards")-1));
        // clipping the x/y positions to frme size, could potentially be improved
        currentContinuousKey = Math.min(Math.max(0f,touchPoint.x),(float)viewWidth)/(float)zoneWidths[currentKeyboard];
        currentKeyboardY = (Math.min(Math.max(0f,touchPoint.y),(float)viewHeight)/(float)zoneHeight)%1f;
        int currentKeyIdInRow = Math.min((int)currentContinuousKey,((int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",currentKeyboard))-1));
        fingersOnScreenCount = event.getPointerCount();

        // we make sure that the touch happened inside the keyboards matrix area
        if(currentKeyboard >= 0){
            // first we track fingers in the different keyboards (this is necessary to control the number of voices of polyphony of each keybaords)
            if(eventType == 0){ // if touch up
                fingersOnKeyboardsCount[currentKeyboard] = Math.max(0,fingersOnKeyboardsCount[currentKeyboard]-1);
            }
            else if(eventType == 1){ // if touch down
                fingersOnKeyboardsCount[currentKeyboard]++;
            }
            else if(eventType == 2 && currentKeyboard != previousTouchedKeyboards[fingerId]){ // if move
                // counting fingers on the keyboard...
                fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]] = Math.max(0,fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]]-1);
                fingersOnKeyboardsCount[currentKeyboard]++;
            }

            // default mode if poly keyboards
            if((int)keyboardParameters.get("Mono Mode") == 0 ||
                    (int)keyboardParameters.get("Max Keyboard Polyphony")>1 ||
                    (int)keyboardParameters.get("Max Keyboard Polyphony")==0){
                // if touch up
                if(eventType == 0){
                    sendKeyboardAction(0,currentKeyboard,currentKeyIdInRow,fingerId);
                }
                // if touch down
                else if(eventType == 1 && (fingersOnKeyboardsCount[currentKeyboard] <= (int)keyboardParameters.get("Max Keyboard Polyphony") ||
                        (int)keyboardParameters.get("Max Keyboard Polyphony") == 0)){
                    sendKeyboardAction(1,currentKeyboard,currentKeyIdInRow,fingerId);
                }
                // if move
                else if(eventType == 2){
                    // moved to another keyboard
                    if(currentKeyboard != previousTouchedKeyboards[fingerId]){
                        // cancel key in previous keyboard
                        sendKeyboardAction(0, previousTouchedKeyboards[fingerId], previousTouchedKeys[fingerId], fingerId);
                        // initiate new event only if there are keys available
                        if((fingersOnKeyboardsCount[currentKeyboard] <= (int)keyboardParameters.get("Max Keyboard Polyphony") ||
                                (int)keyboardParameters.get("Max Keyboard Polyphony") == 0) &&
                                (int)keyboardParameters.get("Inter-Keyboard Slide") == 1){
                            sendKeyboardAction(1, currentKeyboard, currentKeyIdInRow, fingerId);
                        }
                    }
                    // moved to another key within the same keyboard
                    else if(currentKeyIdInRow != previousTouchedKeys[fingerId] &&
                            zones.get(previousTouchedKeyboards[fingerId]).get(previousTouchedKeys[fingerId]).getStatus() == 1){
                        // cancel previous key
                        sendKeyboardAction(3, previousTouchedKeyboards[fingerId], previousTouchedKeys[fingerId], fingerId);
                        // inititate new event
                        sendKeyboardAction(4, currentKeyboard,currentKeyIdInRow, fingerId);
                    }
                    // move within the same key
                    else{
                        sendKeyboardAction(2, currentKeyboard, currentKeyIdInRow, fingerId);
                    }
                }
            }

            else if((int)keyboardParameters.get("Mono Mode") == 1){
                int currentKeyDown = -1;
                for(int i=0; i<(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",currentKeyboard)); i++){
                    if(zones.get(currentKeyboard).get(i).getStatus() == 1){
                        currentKeyDown = i;
                    }
                }

                // if touch up
                if(eventType == 0){
                    // cancel corresponding previous key (in case of fast move event)
                    if(previousTouchedKeyboards[fingerId] != currentKeyboard || previousTouchedKeys[fingerId] != currentKeyIdInRow){
                        sendKeyboardAction(0, previousTouchedKeyboards[fingerId], previousTouchedKeys[fingerId], fingerId);
                    }
                    // cancel corresponding key
                    sendKeyboardAction(0, currentKeyboard, currentKeyIdInRow, fingerId);
                    if(fingersOnKeyboardsCount[currentKeyboard]>0 && monoMode_previousActiveFinger[currentKeyboard] == fingerId){
                        float kb = currentKeyboard*zoneHeight;
                        for(int i=0; i<event.getPointerCount(); i++){
                            if(event.getY(i) >= kb &&
                                    event.getY(i) < zoneHeight+kb &&
                                    event.getY(i) != touchPoint.y &&
                                    i != monoMode_previousActiveFinger[currentKeyboard]){
                                currentContinuousKey = event.getX(i)/zoneWidths[currentKeyboard];
                                currentKeyIdInRow = Math.min((int)currentContinuousKey,(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",currentKeyboard))-1);
                                currentKeyboardY = (Math.min(Math.max(0f,event.getY(i)),(float)viewHeight)/(float)zoneHeight)%1f; // TODO: added on android only
                                sendKeyboardAction(1, currentKeyboard, currentKeyIdInRow, i);
                                monoMode_previousActiveFinger[currentKeyboard] = i;
                                break;
                            }
                        }
                    }
                    else{
                        currentKeyboard = -1;
                        currentKeyIdInRow = -1;
                    }
                }
                // if touch down
                else if(eventType == 1){
                    if(currentKeyDown>=0){
                        sendKeyboardAction(0, currentKeyboard, currentKeyDown, monoMode_previousActiveFinger[currentKeyboard]);
                    }
                    sendKeyboardAction(1, currentKeyboard, currentKeyIdInRow, fingerId);
                    monoMode_previousActiveFinger[currentKeyboard] = fingerId;
                }
                // if move
                else if(eventType == 2){
                    // moved to another keyboard
                    if(currentKeyboard != previousTouchedKeyboards[fingerId]){
                        // cancel key in previous keyboard
                        sendKeyboardAction(0, previousTouchedKeyboards[fingerId], previousTouchedKeys[fingerId], fingerId);

                        if((int)keyboardParameters.get("Inter-Keyboard Slide") == 1){
                            // new note if remaining finger in previous keyboard
                            if(previousTouchedKeyboards[fingerId] != -1 &&
                                    fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]]>0 &&
                                    previousTouchedKeys[fingerId] == previousTouchedKeys[monoMode_previousActiveFinger[previousTouchedKeyboards[fingerId]]]){
                                float kb = previousTouchedKeyboards[fingerId]*zoneHeight;
                                for(int i=0; i<event.getPointerCount(); i++){
                                    if(event.getY(i) >= kb &&
                                            event.getY(i) < zoneHeight+kb &&
                                            event.getY(i) != touchPoint.y &&
                                            i != monoMode_previousActiveFinger[previousTouchedKeyboards[fingerId]]){
                                        currentContinuousKey = event.getX(i)/zoneWidths[previousTouchedKeyboards[fingerId]];
                                        int localKeyIdInRow = Math.min((int)currentContinuousKey,(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",previousTouchedKeyboards[fingerId]))-1);
                                        currentKeyboardY = (Math.min(Math.max(0f,event.getY(i)),(float)viewHeight)/(float)zoneHeight)%1f; // TODO: added on android only
                                        sendKeyboardAction(1, previousTouchedKeyboards[fingerId], localKeyIdInRow, i);
                                        monoMode_previousActiveFinger[previousTouchedKeyboards[fingerId]] = i;
                                        break;
                                    }
                                }
                            }
                            if(currentKeyDown>=0){
                                sendKeyboardAction(0, currentKeyboard, currentKeyDown, monoMode_previousActiveFinger[currentKeyboard]);
                            }
                            sendKeyboardAction(1, currentKeyboard, currentKeyIdInRow, fingerId);
                            fingersOnKeyboardsCount[currentKeyboard]++; // TODO: added on android only...
                            monoMode_previousActiveFinger[currentKeyboard] = fingerId;
                        }
                    }
                    // moved to another key within the same keyboard
                    else if(currentKeyIdInRow != previousTouchedKeys[fingerId] &&
                            zones.get(previousTouchedKeyboards[fingerId]).get(previousTouchedKeys[fingerId]).getStatus() == 1){
                        if(fingersOnKeyboardsCount[currentKeyboard]>1 && monoMode_previousActiveFinger[currentKeyboard] != fingerId){
                            if(currentKeyDown>=0){
                                sendKeyboardAction(0, currentKeyboard, currentKeyDown, monoMode_previousActiveFinger[currentKeyboard]);
                            }
                            sendKeyboardAction(1, currentKeyboard, currentKeyIdInRow, fingerId);
                            monoMode_previousActiveFinger[currentKeyboard] = fingerId;
                        }
                        else{
                            // cancel previous key
                            sendKeyboardAction(3, previousTouchedKeyboards[fingerId], previousTouchedKeys[fingerId], fingerId);
                            // inititate new event
                            sendKeyboardAction(4, currentKeyboard, currentKeyIdInRow, fingerId);
                        }
                    }
                    // move within the same key
                    else{
                        sendKeyboardAction(2, currentKeyboard, currentKeyIdInRow, fingerId);
                    }
                }
            }

            // updating previous data for comparison
            previousTouchedKeyboards[fingerId] = currentKeyboard;
            previousTouchedKeys[fingerId] = currentKeyIdInRow;
        }
        // if touch is outside the keyboards matrix area
        else if(eventType == 2){
            zones.get(previousTouchedKeyboards[fingerId]).get(previousTouchedKeys[fingerId]).setStatus(0);
            fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]] = Math.max(0,fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]]-1);
        }
    }

    private void sendKeyboardAction(int eventType, int keyboardId, int keyId, int fingerId){
        // key up
        if(eventType == 0 || eventType == 3){
            // make sure that the corresponding key is active
            if(zones.get(keyboardId).get(keyId).getStatus() == 1){
                // check if another finger is present in the zone
                boolean otherFingerInKey = false;
                if((int)keyboardParameters.get("Mono Mode") == 0 || (int)keyboardParameters.get("Max Keyboard Polyphony")>1){
                    for(int i=0; i<(int)keyboardParameters.get("Max Fingers"); i++){
                        if(keyboardId == previousTouchedKeyboards[i] && keyId == previousTouchedKeys[i] && i != fingerId){
                            otherFingerInKey = true;
                            break;
                        };
                    }
                }
                // key physically up only if there are no more fingers in the zone
                if(!otherFingerInKey){
                    zones.get(keyboardId).get(keyId).setStatus(0);
                }
                if((int)keyboardParameters.get(String.format("Keyboard %d - Send Freq",keyboardId)) == 0){
                    sendSynthControlAction(keyboardId, keyId, fingerId, eventType, fingersOnKeyboardsCount[keyboardId]);
                }
                else {
                    sendPolySynthControlAction(eventType, keyboardId, keyId, fingerId, fingersOnKeyboardsCount[keyboardId]);
                }
            }
        }
        // key down
        else if(eventType == 1 || eventType == 4){
            zones.get(keyboardId).get(keyId).setStatus(1);
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Freq",keyboardId)) == 0){
                sendSynthControlAction(keyboardId, keyId, fingerId, eventType, fingersOnKeyboardsCount[keyboardId]);
            }
            else {
                sendPolySynthControlAction(eventType, keyboardId, keyId, fingerId, fingersOnKeyboardsCount[keyboardId]);
            }
        }
        // move within the same key
        else if(eventType == 2){
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Freq",keyboardId)) == 0){
                sendSynthControlAction(keyboardId, keyId, fingerId, eventType, fingersOnKeyboardsCount[keyboardId]);
            }
            else {
                sendPolySynthControlAction(eventType, keyboardId, keyId, fingerId, fingersOnKeyboardsCount[keyboardId]);
            }
        }
        if(eventType == 0 && fingersOnScreenCount == 1) resetKeyboard(); // TODO: this is kind of a terrible fix but it does the job for now
    }

    // This method is only used if keyboard mode is deactivated
    private void sendSynthControlAction(int keyboardId, int keyId, int fingerId, int eventType, int fingersOnKeyb){
        if((int)keyboardParameters.get("Send Current Keyboard") == 1)
            dspFaust.setParamValue("keyboard", keyboardId);
        if((int)keyboardParameters.get("Send Current Key") == 1)
            dspFaust.setParamValue("key", keyId);
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send X", keyboardId)) == 1)
            dspFaust.setParamValue("x", (currentContinuousKey % 1f));
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Y", keyboardId)) == 1)
            dspFaust.setParamValue("y", currentKeyboardY);
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Numbered X", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("x%d", fingerId), (currentContinuousKey % 1f));
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Numbered Y", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("y%d", fingerId), currentKeyboardY);
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key X", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("kb%dk%dx", keyboardId, keyId), (currentContinuousKey % 1f));
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key Y", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("kb%dk%dy", keyboardId, keyId), currentKeyboardY);
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key Status", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("kb%dk%dstatus", keyboardId, keyId), eventType);
        if((int)keyboardParameters.get("Send Fingers Count") == 1)
            dspFaust.setParamValue(String.format("kb%dfingers", keyboardId), fingersOnKeyb);
    }

    private void sendPolySynthControlAction(int eventType, int keyboardId, int keyId, int fingerId, int fingersOnKeyb){
        float pitch = 0; // the MIDI pitch of the note
        // delete (note off)
        if((eventType == 0 || (eventType == 3 &&
                (int)keyboardParameters.get("Rounding Mode") == 0)) && voices[fingerId] != -1){
            pitch = -1;
            refPitch[fingerId] = -1;
            dspFaust.setVoiceParamValue("gate", voices[fingerId], 0);
            if ((int) keyboardParameters.get("Max Keyboard Polyphony") > 0) {
                dspFaust.deleteVoice(voices[fingerId]);
                voices[fingerId] = -1;
            }
            else if(fingerId != 0){
                voices[fingerId] = -1;
            }
            smooth[fingerId].reset();
        }
        // new (note on)
        else if (eventType == 1 ||
                (eventType == 4 && (int)keyboardParameters.get("Rounding Mode") == 0)){
            if ((int) keyboardParameters.get("Max Keyboard Polyphony") > 0) {
                // allocating new voice to finger
                voices[fingerId] = dspFaust.newVoice();
            }
            else{
                voices[fingerId] = voices[0];
            }
            if (voices[fingerId] != -1) {
                dspFaust.setVoiceParamValue("bend", voices[fingerId], 1);
                dspFaust.setVoiceParamValue("gate", voices[fingerId], 1);
            } else {
                return;
            }

            // setting first pitch (always quantized)
            if((int)keyboardParameters.get("Rounding Mode") == 0 ||
                    ((int)keyboardParameters.get("Rounding Mode") == 2 &&
                            (int)keyboardParameters.get(String.format("Keyboard %d - Scale",keyboardId)) > 0)){
                // inverted keyboard
                if((int)keyboardParameters.get(String.format("Keyboard %d - Orientation",keyboardId)) == 1){
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+
                            (int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",keyboardId))-keyId-1, keyboardId);
                }
                // regular keyboard
                else{
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+keyId, keyboardId);
                }
            }
            else if((int)keyboardParameters.get("Rounding Mode") == 1 || (int)keyboardParameters.get("Rounding Mode") == 2){
                float pitchShiftCenter = 0;
                // -0.5 is here to center the pitch at the middle of the key
                if((int)keyboardParameters.get("Rounding Mode") == 1){
                    pitchShiftCenter = 0.5f;
                }
                // inverted keyboard
                if((int)keyboardParameters.get(String.format("Keyboard %d - Orientation",keyboardId)) == 1){
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+
                            (int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",keyboardId))-
                            currentContinuousKey-pitchShiftCenter, keyboardId);
                }
                // regular keyboard
                else{
                    pitch = applyScale(currentContinuousKey +
                            (int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))-
                            pitchShiftCenter, keyboardId);
                }
            }
            if(voices[fingerId] != -1){
                if((int)keyboardParameters.get("Rounding Mode") == 1){
                    refPitch[fingerId] = pitch;
                }
                else{
                    refPitch[fingerId] = (float)Math.floor(pitch);
                }
                dspFaust.setVoiceParamValue("freq", voices[fingerId], mtof(refPitch[fingerId]));
                if((int)keyboardParameters.get(String.format("Keyboard %d - Send Keyboard Freq",keyboardId)) == 1){
                    dspFaust.setVoiceParamValue(String.format("kb%dfreq", keyboardId), voices[fingerId], mtof(refPitch[fingerId]));
                }
            }
        }
        // update
        else if(eventType == 2 && ((int)keyboardParameters.get("Rounding Mode") == 1 || (int)keyboardParameters.get("Rounding Mode") == 2)){

            // Formating pitch
            if((int)keyboardParameters.get(String.format("Keyboard %d - Scale",keyboardId)) > 0 &&
                    rounding[fingerId] && (int)keyboardParameters.get("Rounding Mode") != 1){
                // inverted keyboard
                if((int)keyboardParameters.get(String.format("Keyboard %d - Orientation",keyboardId)) == 1){
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+
                            (int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",keyboardId))-keyId-1, keyboardId);
                }
                // regular keyboard
                else{
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+keyId, keyboardId);
                }
            }
            else {
                float pitchShiftCenter = 0;
                // -0.5 is here to center the pitch at the middle of the key
                if((int)keyboardParameters.get("Rounding Mode") == 1){
                    pitchShiftCenter = 0.5f;
                }
                // inverted keyboard
                if((int)keyboardParameters.get(String.format("Keyboard %d - Orientation",keyboardId)) == 1){
                    pitch = applyScale((int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))+
                            (int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",keyboardId))-currentContinuousKey-pitchShiftCenter, keyboardId);
                }
                // regular keyboard
                else{
                    pitch = applyScale(currentContinuousKey+(int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId))-pitchShiftCenter,keyboardId);
                }
            }

            // sending pitch to faust
            if(voices[fingerId] != -1 && pitch != -1){
                if((int)keyboardParameters.get("Rounding Mode") == 1){
                    dspFaust.setVoiceParamValue("bend", voices[fingerId], (float)Math.pow(2,(pitch-refPitch[fingerId])/12));
                    if((int)keyboardParameters.get(String.format("Keyboard %d - Send Keyboard Freq",keyboardId)) == 1){
                        dspFaust.setVoiceParamValue(String.format("kb%dbend", keyboardId), voices[fingerId], (float)Math.pow(2,(pitch-refPitch[fingerId])/12));
                    }
                }
                else if((int)keyboardParameters.get("Rounding Mode") == 2){
                    if(rounding[fingerId]){ // if rounding is activated, pitch is quantized to the nearest integer
                        dspFaust.setVoiceParamValue("bend", voices[fingerId], (float)Math.pow(2,(Math.floor(pitch)-refPitch[fingerId])/12));
                        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Keyboard Freq",keyboardId)) == 1){
                            dspFaust.setVoiceParamValue(String.format("kb%dbend", keyboardId), voices[fingerId], (float)Math.pow(2,(Math.floor(pitch)-refPitch[fingerId])/12));
                        }
                    }
                    else{
                        dspFaust.setVoiceParamValue("bend", voices[fingerId], (float)Math.pow(2,(pitch-0.5-refPitch[fingerId])/12));
                        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Keyboard Freq",keyboardId)) == 1){
                            dspFaust.setVoiceParamValue(String.format("kb%dbend", keyboardId), voices[fingerId], (float)Math.pow(2,(pitch-0.5-refPitch[fingerId])/12));
                        }
                    }
                }
            }
        }

        if(voices[fingerId] != -1){
            if((int)keyboardParameters.get("Send Current Keyboard") == 1)
                dspFaust.setVoiceParamValue("keyboard", voices[fingerId], keyboardId);
            if((int)keyboardParameters.get("Send Current Key") == 1)
                dspFaust.setVoiceParamValue("key",voices[fingerId], keyId);
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send X", keyboardId)) == 1)
                dspFaust.setVoiceParamValue("x", voices[fingerId], (currentContinuousKey % 1f));
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Y", keyboardId)) == 1)
                dspFaust.setVoiceParamValue("y", voices[fingerId], currentKeyboardY);
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Numbered X", keyboardId)) == 1)
                dspFaust.setVoiceParamValue(String.format("x%d", fingerId), voices[fingerId], (currentContinuousKey % 1f));
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Numbered Y", keyboardId)) == 1)
                dspFaust.setVoiceParamValue(String.format("y%d", fingerId), voices[fingerId], currentKeyboardY);
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key X", keyboardId)) == 1)
                dspFaust.setVoiceParamValue(String.format("kb%dk%dx", keyboardId, keyId), voices[fingerId], (currentContinuousKey % 1f));
            if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key Y", keyboardId)) == 1)
                dspFaust.setVoiceParamValue(String.format("kb%dk%dy", keyboardId, keyId), voices[fingerId], currentKeyboardY);
        }
        // TODO: there should be a better option that putting these guys outside of the previou condition
        if((int)keyboardParameters.get(String.format("Keyboard %d - Send Key Status", keyboardId)) == 1)
            dspFaust.setParamValue(String.format("kb%dk%dstatus", keyboardId, keyId), eventType);
        if((int)keyboardParameters.get("Send Fingers Count") == 1) {
            dspFaust.setParamValue(String.format("kb%dfingers", keyboardId), fingersOnKeyb);
        }
    }

    private float applyScale(float pitch, int keyboardId){
        int refPitch = (int)keyboardParameters.get(String.format("Keyboard %d - Lowest Key",keyboardId));
        int currentScale = (int)keyboardParameters.get(String.format("Keyboard %d - Scale",keyboardId)) - 1;
        float keyboardPitch = (pitch-refPitch); // float pitch on keyboard (from 0)
        float scaledPitch = 0; // the final scaled pitch

        int scalesCoeff[][] = {
                {1,1,1,1,1,1,1}, // chromatic
                {2,2,1,2,2,2,1}, // major
                {2,1,2,2,1,3,1} // harm minor
        };

        if(currentScale+1 > 0 && currentScale<4){
            int scaleAdd = 0;
            if(scalesCoeff[currentScale][(int)keyboardPitch%7] == 2){
                for(int i=0; i<(int)keyboardPitch; i++){
                    if(scalesCoeff[currentScale][i%7] == 1) scaleAdd--;
                    else if(scalesCoeff[currentScale][i%7] == 3) scaleAdd++;
                }
            }
            else if(scalesCoeff[currentScale][(int)keyboardPitch%7] == 1){
                for(int i=0; i<(int)keyboardPitch; i++){
                    if(scalesCoeff[currentScale][i%7] == 2) scaleAdd++;
                    else if(scalesCoeff[currentScale][i%7] == 3) scaleAdd+=2;
                }
            }
            else if(scalesCoeff[currentScale][(int)keyboardPitch%7] == 3){
                for(int i=0; i<(int)keyboardPitch; i++){
                    if(scalesCoeff[currentScale][i%7] == 2) scaleAdd--;
                    else if(scalesCoeff[currentScale][i%7] == 1) scaleAdd-=2;
                }
            }

            scaledPitch = refPitch+scaleAdd+
                    (keyboardPitch*scalesCoeff[currentScale][(int)keyboardPitch%7]);
        }
        else{
            scaledPitch = pitch;
        }
        return scaledPitch;
    }

    private float mtof(float note){
        return 440.0f * (float)Math.pow(2.0, (note-69.0)/12.0);
    }

    private void resetKeyboard(){
        if ((int) keyboardParameters.get("Max Keyboard Polyphony") > 0) dspFaust.allNotesOff();
        for(int i=0; i<(int)keyboardParameters.get("Number of Keyboards"); i++){
            fingersOnKeyboardsCount[i] = 0;
            for(int j=0;j<(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i));j++){
                zones.get(i).get(j).setStatus(0);
            }
        }
        for(int i=0; i<(int)keyboardParameters.get("Max Fingers"); i++){
            if ((int) keyboardParameters.get("Max Keyboard Polyphony") > 0) voices[i] = -1;
            previousTouchedKeys[i] = -1;
            previousTouchedKeyboards[i] = -1;
            moveCount[i] = 0;
        }
        fingersOnScreenCount = 0;
    }

    class PitchRounding implements Runnable{
        @Override
        public void run() {
            while(UIon){
                for(int i=0; i<(int)keyboardParameters.get("Max Fingers"); i++){
                    if(touchDiff[i] != -10000 && voices[i] != -1){
                        if(smooth[i].tick(touchDiff[i])>(float)keyboardParameters.get("Rounding Threshold") &&
                                moveCount[i]<(int)keyboardParameters.get("Rounding Cycles")){
                            rounding[i] = false;
                        }
                        else{
                            rounding[i] = true;
                            moveCount[i] = 0;
                        }

                        if(touchDiff[i]<1){
                            moveCount[i]++;
                        }
                    }
                }
                try {
                    Thread.sleep(roundingUpdateSpeed);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private final SensorEventListener mSensorListener = new SensorEventListener() {
        public void onSensorChanged(SensorEvent se) {
            if (se.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                // Update mapping at sensor rate, values are inverted to be coherent with iOS
                dspFaust.propagateAcc(0, -se.values[0]);
                dspFaust.propagateAcc(1, -se.values[1]);
                dspFaust.propagateAcc(2, -se.values[2]);
            }

            if (se.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
                // Update mapping at sensor rate
                dspFaust.propagateGyr(0, se.values[0]);
                dspFaust.propagateGyr(1, se.values[1]);
                dspFaust.propagateGyr(2, se.values[2]);
            }
        }
        public void onAccuracyChanged(Sensor sensor, int accuracy) {}
    };

    @Override
    protected void onLayout(boolean b, int left, int top, int right, int bottom) {
        viewWidth = right-left;
        viewHeight = bottom-top;
        zoneHeight = viewHeight/(int)keyboardParameters.get("Number of Keyboards");
        zoneCenterYOffset = (viewHeight-zoneHeight*(int)keyboardParameters.get("Number of Keyboards"))/2;
        for(int i=0; i<(int)keyboardParameters.get("Number of Keyboards") ; i++) {
            zoneWidths[i] = viewWidth/(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i));
            zoneCenterXOffset[i] = (viewWidth-zoneWidths[i]*(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i)))/2;
            for(int j=0; j<(int)keyboardParameters.get(String.format("Keyboard %d - Number of Keys",i)); j++) {
                int currentLeft = borderSize+zoneCenterXOffset[i]+zoneWidths[i]*j;
                int currentTop = borderSize+zoneCenterYOffset+zoneHeight*i;
                int currentRight = currentLeft+zoneWidths[i]-borderSize*2;
                int currentBottom = currentTop+zoneHeight-borderSize*2;
                zones.get(i).get(j).layout(currentLeft,currentTop,currentRight,currentBottom);
            }
        }
    }
}
