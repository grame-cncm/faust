package com.faust;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Point;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.OvalShape;
import android.graphics.drawable.shapes.RectShape;
import android.util.AttributeSet;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.TextView;

/*
 * MultiParams is a two dimensional control interface where points
 * can be moved on the screen. It respects the Faust standards and 
 * can output values constrained between a certain range, etc.
 */
public class MultiParams extends ViewGroup{
	private Context c;
	private ShapeDrawable frame; // the frame around the interface
	private ParamPoint points[]; // the points
	private boolean odd; // true if the number of parameters is odd
	private int nPoints; // number of points
	private int nParams; // number of parameters
	private int colors[] = { // color map for the different points
		// we assume that the max number of parameters will be 24...
		Color.parseColor("#0099CC"), Color.parseColor("#33CC33"),
		Color.parseColor("#CC66FF"), Color.parseColor("#FFFF00"),
		Color.parseColor("#FF9900"), Color.parseColor("#CC0000"),
		Color.parseColor("#0099CC"), Color.parseColor("#33CC33"),
		Color.parseColor("#CC66FF"), Color.parseColor("#FFFF00"),
		Color.parseColor("#FF9900"), Color.parseColor("#CC0000")};
	private int poolWidth; // interface width
	private int poolHeight; // interface height
	private int maxLabelLength = 10; // max number of characters in
	// a parameter name
	
	// listener interface
	private OnMultiParamsChangeListener mOnMultiParamsListener;
	public interface OnMultiParamsChangeListener {
		// activated when one of the point moved on the screen
		void onParamChange(int paramID, float value);
	}
	
	public MultiParams(Context context, AttributeSet attrs){
		super(context, attrs);
		c = context;
		setBackgroundColor(Color.parseColor("#A0A0A0")); // frame color
		frame = new ShapeDrawable(new RectShape()); // new background
		frame.getPaint().setColor(Color.BLACK); // background color
	}
	
	public void setParams(String labels[], float min[], float max[], float current[]){
		nParams = labels.length;
		odd = false;
		if(nParams%2 != 0){ // if the number of parameters is odd
			nPoints = nParams/2 + 1;
			odd = true;
		}
		else nPoints = nParams/2;
		
		points = new ParamPoint[nPoints];
		int ii=0; // double counter
		// points are created
		for(int i=0; i<nPoints; i++){
			points[i] = new ParamPoint(c,i*2);	
			points[i].setColor(colors[i%colors.length]);
			
			points[i].setMinX(min[ii]);
			points[i].setMaxX(max[ii]);
			points[i].setCurrentValueX(current[ii]);
			
			if(labels[ii].length()<maxLabelLength) points[i].setLabelX(labels[ii]);
			else points[i].setLabelX(labels[ii].substring(0, maxLabelLength));
			
			if(odd && i == nPoints-1){
				points[i].setLabelY("");
				points[i].setMinY(0);
				points[i].setMaxY(1000);
				points[i].setCurrentValueY(0);
			}
			else{
				if(labels[ii+1].length()<maxLabelLength) points[i].setLabelY(labels[ii+1]);
				else points[i].setLabelY(labels[ii+1].substring(0, maxLabelLength));
				points[i].setMinY(min[ii+1]);
				points[i].setMaxY(max[ii+1]);
				points[i].setCurrentValueY(current[ii+1]);
			}
			addView(points[i]);
			ii+=2;
		}
	}
	
	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {
		super.onSizeChanged(w, h, oldw, oldh);
    
		float xpad = (float) (getPaddingLeft() + getPaddingRight());
		float ypad = (float) (getPaddingTop() + getPaddingBottom());
		
		int frameWidth = 2; // this enough to not be adjusted in function of the screen size
    
		poolWidth =  (int) (w - xpad);
		poolHeight = (int) (h - ypad);
		
		frame.setBounds(frameWidth, frameWidth, poolWidth-frameWidth, poolHeight-frameWidth);
		layout(0, 0, poolWidth, poolHeight);
		
		for(int i=0; i<nPoints; i++){
			points[i].updatePosition();
		}
	}

	@Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {
	}
	
	public void setOnMultiParamsChangeListener(OnMultiParamsChangeListener l){
		mOnMultiParamsListener = l;
	}
	
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		frame.draw(canvas);
	}
	
	/*
	 * A single point parameter controller
	 */
	class ParamPoint extends View{
		private ShapeDrawable point;
		private TextView labelX, labelY;
		private int ID;
		private int viewWidth;
		private int viewHeight;
		private String nameX;
		private String nameY;
		private float minX;
		private float minY;
		private float maxX;
		private float maxY;
		private float currentX;
		private float currentY;
		private float rangeX;
		private float rangeY;
		private int screenX; // X screen size
		private int screenY; // Y screen size
		private int defPointSize = 50; // default point size (for a 1900 screen)
		private int defZoneSize = 300; // default point+label width (for a 1900 screen) 
		private int scaledPointSize;
		private int scaledZoneSize;
		
		public ParamPoint(Context context, int id){
			super(context);
			
			ID = id;
			
			// getting the screen size to adapt the point size 
			WindowManager wm = (WindowManager) c.getSystemService(Context.WINDOW_SERVICE);
			Display display = wm.getDefaultDisplay();
			Point size = new Point();
			display.getSize(size);
			screenX = size.x;
			screenY= size.y;
			
			// the point...
			point = new ShapeDrawable(new OvalShape());
			
			// label for the X parameter
			labelX = new TextView(context);
			addView(labelX);
			
			// label for the Y parameter
			labelY = new TextView(context);
			addView(labelY);
			
			scaledZoneSize = defZoneSize*Math.max(screenX,screenY)/1900;
			scaledPointSize = defPointSize*Math.max(screenX,screenY)/1900;
			
			layout(0, 0, scaledZoneSize, scaledPointSize);
		}
		
		public void setLabelX(String pNameX){
			nameX = pNameX;
			labelX.setText(nameX);
		}
		
		public void setLabelY(String pNameY){
			nameY = pNameY;
			labelY.setText(nameY);
		}
		
		public void setMinX(float X){
			minX = X;
			computeRangeX();
		}
		
		public void setMinY(float Y){
			minY = Y;
			computeRangeY();
		}
		
		public void setMaxX(float X){
			maxX = X;
			computeRangeX();
		}
		
		public void setMaxY(float Y){
			maxY = Y;
			computeRangeY();
		}
		
		public void setCurrentValueX(float X){
			currentX = X;
		}
		
		public void setCurrentValueY(float Y){
			currentY = Y;
		}
		
		// update the position of the point in function of the global variables
		public void updatePosition(){
			offsetLeftAndRight((int) (currentX*(poolWidth-scaledPointSize)/rangeX));
			offsetTopAndBottom((int) (currentY*(poolHeight-scaledPointSize)/rangeY));
		}
		
		public void setColor(int color){
			labelX.setTextColor(color);
			labelY.setTextColor(color);
			point.getPaint().setColor(color);
		}
		
		private void computeRangeX(){
			rangeX = maxX - minX;
		}
		
		private void computeRangeY(){
			rangeY = maxY - minY;
		}
		
		// TODO nice feature to add: big point when touched...
		/*
		private void focus(boolean s){
			if(s){
				labelX.setVisibility(INVISIBLE);
				labelY.setVisibility(INVISIBLE);
				layout(0, 0, defZoneSize*Math.max(screenX,screenY)/1900, 
						defPointSize*3*Math.max(screenX,screenY)/1900);
			}
			else{
				labelX.setVisibility(VISIBLE);
				labelY.setVisibility(VISIBLE);
				layout(0, 0, defZoneSize*Math.max(screenX,screenY)/1900, 
						defPointSize*Math.max(screenX,screenY)/1900);
			}
		}
		*/
		
		@Override
		public boolean onTouchEvent(MotionEvent event) {
			int eventAction = event.getAction();
			int pointOffset = viewHeight/2; // so that the touch point is centered
			
			// moving the point within the pool on the X axis
			float positionX = getLeft()+event.getX();
			currentX = positionX*rangeX/(poolWidth-scaledPointSize) + minX;
			if(getX()+(event.getX()-pointOffset) < (poolWidth-viewHeight)) 
				offsetLeftAndRight((int)event.getX()-pointOffset);
			
			// moving the point within the pool on the Y axis
			float positionY = getTop()+event.getY();
			currentY = positionY*rangeY/(poolHeight-scaledPointSize) + minY;
			if(getY()+(event.getY()-pointOffset) > 0 && getY()+(event.getY()-pointOffset) < poolHeight-viewHeight) 
				offsetTopAndBottom((int)event.getY()-pointOffset);
			
			if (mOnMultiParamsListener != null) {
				mOnMultiParamsListener.onParamChange(ID, currentX);
				if(!odd) mOnMultiParamsListener.onParamChange(ID+1, currentY);
				else if(odd && ID != nPoints-1) mOnMultiParamsListener.onParamChange(ID+1, currentY);
			}
	
			return true;
		}
		
		@Override
		protected void onSizeChanged(int w, int h, int oldw, int oldh) {
			super.onSizeChanged(w, h, oldw, oldh);
			
			float xpad = (float) (getPaddingLeft() + getPaddingRight());
			float ypad = (float) (getPaddingTop() + getPaddingBottom());
        
			viewWidth =  (int) (w - xpad);
			viewHeight = (int) (h - ypad);
			
			// Default label offset to the point for a 1900px screen
			int defLabelXOffset = 4;
			int defLabelYXOffset = -15;
			int defLabelYYOffset = 25;
			
			point.setBounds(0, 0, viewHeight, viewHeight);
			labelX.layout(viewHeight+(defLabelXOffset*viewHeight/defPointSize), defLabelYXOffset*viewHeight/defPointSize, 
					(defZoneSize-defPointSize)*viewHeight/defPointSize, viewHeight);
			labelY.layout(viewHeight+(defLabelXOffset*viewHeight/defPointSize), defLabelYYOffset*viewHeight/defPointSize, 
					(defZoneSize-defPointSize)*viewHeight/defPointSize, viewHeight+(defLabelYYOffset*viewHeight/defPointSize));
		}
		
		@Override
		public void offsetLeftAndRight(int offset){
			super.offsetLeftAndRight(offset);
			labelX.offsetLeftAndRight(offset);
			labelY.offsetLeftAndRight(offset);
		}
		
		@Override
		public void offsetTopAndBottom(int offset){
			super.offsetTopAndBottom(offset);
			labelX.offsetTopAndBottom(offset);
			labelY.offsetTopAndBottom(offset);
		}
		
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);
			point.draw(canvas);
		}
	}
	
}
