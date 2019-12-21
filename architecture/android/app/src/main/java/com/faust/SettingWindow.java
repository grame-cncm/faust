package com.faust;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Point;
import android.text.InputType;
import android.text.method.KeyListener;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

public class SettingWindow {

    PopupWindow mainWindow;
    LinearLayout mainWindowLayout, ipAddressLayout, inPortLayout, outPortLayout, xMitLayout, windowLayout, titleLayout;
    SelectBar xmitSelection;
    TextView closeButton,ipAddressValue, inPortValue, outPortValue, xMitValue, windowLabel;
    EditText ipAddress, inPort, outPort;
    Point size;

    public void buildWindow(Context c) {
        WindowManager wm = (WindowManager) c.getSystemService(Context.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        size = new Point();
        display.getSize(size);
        
        // the global elements are instantiated
        mainWindowLayout = new LinearLayout(c);

        ipAddressLayout = new LinearLayout(c);
        inPortLayout = new LinearLayout(c);
        outPortLayout = new LinearLayout(c);
        xMitLayout = new LinearLayout(c);
        mainWindow = new PopupWindow(c);

        closeButton = new TextView(c);
        ipAddressValue = new TextView(c);
        inPortValue = new TextView(c);
        outPortValue = new TextView(c);
        xMitValue = new TextView(c);

        ipAddress = new EditText(c);
        inPort = new EditText(c);
        outPort = new EditText(c);
        xmitSelection = new SelectBar(c);

        windowLayout = new LinearLayout(c);
        titleLayout = new LinearLayout(c);
        windowLabel = new TextView(c);

        ViewGroup.LayoutParams wrapped = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);

        windowLayout.setLayoutParams(wrapped);
        windowLayout.setOrientation(LinearLayout.VERTICAL);
        windowLayout.setPadding(10, 0, 10, 0); // TODO adjust in function of screen size

        titleLayout.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        titleLayout.setOrientation(LinearLayout.HORIZONTAL);

        closeButton.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        closeButton.setGravity(Gravity.RIGHT);
        closeButton.setTextSize(20);
        closeButton.setText("Set");

        windowLabel.setText("OSC (Restart required)");
        windowLabel.setTextSize(16.f);

        ipAddress.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        ipAddress.setInputType(InputType.TYPE_TEXT_VARIATION_URI);
        ipAddress.setTextColor(Color.GRAY);

        inPort.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        inPort.setInputType(InputType.TYPE_CLASS_NUMBER);
        inPort.setTextColor(Color.GRAY);

        outPort.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        outPort.setInputType(InputType.TYPE_CLASS_NUMBER);
        outPort.setTextColor(Color.GRAY);

        String[] items = {"OFF","All","Alias"};
        xmitSelection.setItems(items);

        ipAddressValue.setText("IP Address:  ");
        inPortValue.setText("In Port:  ");
        outPortValue.setText("Out Port:  ");
        xMitValue.setText("xMit Mode:  ");

        titleLayout.addView(windowLabel);
        titleLayout.addView(closeButton);

        windowLayout.addView(titleLayout);

        ipAddressLayout.addView(ipAddressValue);
        ipAddressLayout.addView(ipAddress);

        inPortLayout.addView(inPortValue);
        inPortLayout.addView(inPort);

        outPortLayout.addView(outPortValue);
        outPortLayout.addView(outPort);

        xMitLayout.addView(xMitValue);
        xmitSelection.addTo(xMitLayout);

        windowLayout.addView(ipAddressLayout);
        windowLayout.addView(inPortLayout);
        windowLayout.addView(outPortLayout);
        windowLayout.addView(xMitLayout);

        mainWindow.setContentView(windowLayout);
        mainWindow.setFocusable(true);
        mainWindow.update();
    }

    public void showWindow(final ParametersInfo parametersInfo) {

        mainWindow.showAtLocation(mainWindowLayout, Gravity.CENTER,0,0);
        mainWindow.update(0, 0, size.x*700/800, ViewGroup.LayoutParams.WRAP_CONTENT);

        titleLayout.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                configOSC(parametersInfo);
                mainWindow.dismiss();
            }
        });

        ipAddress.setText(parametersInfo.ipAddress);
        inPort.setText(String.valueOf(parametersInfo.inPort));
        outPort.setText(String.valueOf(parametersInfo.outPort));
        xmitSelection.selectTextItem(parametersInfo.xmit);

        for(int i=0; i<xmitSelection.length; i++){
            final int index = i;
            xmitSelection.parameterLabel[i].setOnClickListener(new View.OnClickListener(){
                public void onClick(View v){
                    xmitSelection.selectTextItem(index);
                    Log.d("FaustJava", "xmit : " + index);
                    parametersInfo.xmit= index;
                }
            });
        }

        closeButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v){
                configOSC(parametersInfo);
                mainWindow.dismiss();
            }
        });

    }

    void configOSC(final ParametersInfo parametersInfo) {

        Log.d("FaustJava", "ipAddress : " + ipAddress.getText().toString());
        parametersInfo.ipAddress= ipAddress.getText().toString();

        Log.d("FaustJava", "inPort : " + inPort.getText().toString());
        parametersInfo.inPort= Integer.parseInt(inPort.getText().toString());

        Log.d("FaustJava", "outPort : " + outPort.getText().toString());
        parametersInfo.outPort= Integer.parseInt(outPort.getText().toString());

        Log.d("FaustJava", "xmit : " + xmitSelection.id);
        parametersInfo.xmit= xmitSelection.id;

        FaustActivity.dspFaust.configureOSC(parametersInfo.xmit,parametersInfo.inPort,parametersInfo.outPort,5512,parametersInfo.ipAddress);
    }

    void initOSC(final ParametersInfo parametersInfo) {
        parametersInfo.ipAddress = "192.168.1.5";
        parametersInfo.inPort = 5510;
        parametersInfo.outPort = 5511;
        parametersInfo.xmit = 1;
        FaustActivity.dspFaust.configureOSC(1,5510,5511,5512,"192.168.1.5");
    }

}
