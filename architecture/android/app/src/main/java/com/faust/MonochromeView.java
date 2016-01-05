package com.faust;

import android.content.Context;
import android.graphics.Canvas;
import android.util.Log;
import android.view.View;

/**
 * Created by yannorlarey on 16/11/15.
 */
public class MonochromeView extends View
{
    private int fRed = 0;
    private int fGreen = 0;
    private int fBlue = 0;

    public MonochromeView(Context context){
        super(context);
        // specific stuff here
    }

    private int acc2byte(double r) {
        int c = (int) (255 * Math.abs(r));
        if (c > 255) {
            return 255;
        } else {
            return c;
        }
    }

    public void setRed(double r) {
        int c = acc2byte(r);
        if (c != fRed) {
            fRed = c;
            invalidate();
        }
    }

    public void setGreen(double r) {
        int c = acc2byte(r);
        if (c != fGreen) {
            fGreen = c;
            invalidate();
        }
    }

    public void setBlue(double r) {
        int c = acc2byte(r);
        if (c != fBlue) {
            fBlue = c;
            invalidate();
        }
    }

    public void setColor(int c) {
        fRed    = 255 & (c >> 16);
        fGreen  = 255 & (c >> 8);
        fBlue   = 255 & (c >> 0);
        invalidate();
    }

    protected void onDraw (Canvas canvas) {
        //Log.d("FaustJava", "MonochromeView.onDraw() "+ "width:" +getWidth()+ " height:"+ getHeight());
        canvas.drawRGB(fRed, fGreen, fBlue);
    }
}
