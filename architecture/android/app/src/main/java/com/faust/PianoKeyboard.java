package com.faust;

import android.content.Context;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;

/*
 * This class implements a polyphonic continuous piano keyboard.
 */
public class PianoKeyboard extends ViewGroup {
    public PianoKey[] keys;
	
	// Config variables
	private int numberOfKeys = 16;
	public int baseNote = 72; // base MIDI note
	
	// local variables
	private int numberOfWhiteKeys = 0;
	private int[] keysType = {0,3,1,3,2,0,3,1,3,1,3,2};
	private int whiteKeysWidth = 0;
	private int blackKeysWidth = 0;
	private int blackKeysHeight = 0;
	
	// listener interface
	private OnKeyboardChangeListener mOnKeyboardChangeListener;
	public interface OnKeyboardChangeListener
    {
		/* when a key is pressed or released with:
		 * note: MIDI note number
		 * velocity: MIDI velocity
		 * status: true for down, false for up
		 */
	    void onKeyChanged(int note, int velocity, boolean status);
		/*
		 * when the finger position on the Y axis changed where:
		 * note: the MIDI pitch affected by this change
		 * y: the normalized Y position (0-1)
		 */
		void onYChanged(long refPitch, float y);
		/*
		 * replace refPitch by pitch (float, MIDI number)
		 */
		void onPitchBend(long refPitch, float pitch);
	}
	
	// set the the pitch of the lowest key as a MIDI number,
	// can be used for transposition, etc.
    public void setBaseNote(int n)
    {
        baseNote = n;
    }
	
    public PianoKeyboard(Context context, AttributeSet attrs)
    {
		super(context, attrs);
		TypedArray a = context.getTheme().obtainStyledAttributes(
				attrs,
				R.styleable.PianoKeyboard,
				0, 0);
		try {
			// if parameters are declared from XML 
			numberOfKeys = a.getInt(R.styleable.PianoKeyboard_keys, numberOfKeys);
			baseNote = a.getInt(R.styleable.PianoKeyboard_basenote, baseNote);
		} finally {
			a.recycle();
		}
		
		keys = new PianoKey[numberOfKeys];
		
		for(int i = 0; i < numberOfKeys; i++) {
			if (keysType[i%12] != 3){
				keys[i] = new PianoKey(context,keysType[i%12],i);
				addView(keys[i]);
				numberOfWhiteKeys++;
			}
		}
		for (int i = 0; i < numberOfKeys; i++){
			if (keysType[i%12] == 3) {
				keys[i] = new PianoKey(context,keysType[i%12],i);
				addView(keys[i]);
			}
		}
		
		setBackgroundColor(Color.BLACK);
	}
	
	@Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh)
    {
		super.onSizeChanged(w, h, oldw, oldh);
    
		float xpad = (float) (getPaddingLeft() + getPaddingRight());
		float ypad = (float) (getPaddingTop() + getPaddingBottom());
    
		int viewWidth =  (int) (w - xpad);
		int viewHeight = (int) (h - ypad);
		
		whiteKeysWidth = viewWidth/(numberOfWhiteKeys);
		blackKeysWidth = (int) (whiteKeysWidth*0.595f);
		blackKeysHeight = (int) (viewHeight*0.535f);
		
		int whiteKeysIndex = 0;
		int blackKeysIndex = 1;
		int whiteKeysOffset = 0;
		for (int i = 0; i < numberOfKeys; i++){
			if (keysType[i%12] == 3) {
				keys[i].layout(0, 0, blackKeysWidth, blackKeysHeight);
				keys[i].offsetLeftAndRight((int) (whiteKeysOffset+whiteKeysWidth*0.71f));
				blackKeysIndex++;
			} else {
				keys[i].layout(0, 0, whiteKeysWidth, viewHeight);
				whiteKeysOffset = whiteKeysWidth*whiteKeysIndex;
				keys[i].offsetLeftAndRight(whiteKeysOffset);
				whiteKeysIndex++;
			}		
		}
	}
	
    public void setOnKeyboardChangeListener(OnKeyboardChangeListener l)
    {
		mOnKeyboardChangeListener = l;
	}
	
	@Override
    protected void onLayout(boolean changed, int l, int t, int r, int b)
    {}
	
	/*
	 * Subclass implementing a single key and its listener
	 */
	class PianoKey extends ViewGroup {
        private PianoKeyElement keyUp, keyDown;
        private int ID = 0;         // key ID on the keyboard
        private int keyType = 0;    // key type (white left, center, right or black)
        public long voice;           // allocated voice for the played pitch

		public PianoKey(Context context, int type, int id)
        {
			super(context);
			ID = id;
			keyType = type;
			keyUp = new PianoKeyElement(context,keyType,0);
			keyDown = new PianoKeyElement(context,keyType,1);
			addView(keyUp);
			addView(keyDown);
			keyDown.setVisibility(INVISIBLE);
		}
		
        public void setKeyDown()
        {
            keyDown.setVisibility(VISIBLE);
        }

        public void setKeyUp()
        {
            keyDown.setVisibility(INVISIBLE);
        }
		
		@Override
		protected void onSizeChanged(int w, int h, int oldw, int oldh)
        {
			super.onSizeChanged(w, h, oldw, oldh);
			
			float xpad = (float) (getPaddingLeft() + getPaddingRight());
			float ypad = (float) (getPaddingTop() + getPaddingBottom());
	    
			int viewWidth =  (int) (w - xpad);
			int viewHeight = (int) (h - ypad);
			
			keyUp.layout(0, 0, viewWidth, viewHeight);
			keyDown.layout(0, 0, viewWidth, viewHeight);
		}
		
		@Override
		public boolean onTouchEvent(MotionEvent event)
        {
			int pitch = ID+baseNote;
			float gain = 0;
			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				setKeyDown();
				if (mOnKeyboardChangeListener != null) {
                    mOnKeyboardChangeListener.onKeyChanged(pitch, (int)gain*127, true);
				}
			}
			else if(event.getAction() == MotionEvent.ACTION_UP) {
                setKeyUp();
                if (mOnKeyboardChangeListener != null) {
                     mOnKeyboardChangeListener.onKeyChanged(pitch, 0, false);
                }
			}
			if (mOnKeyboardChangeListener != null) {
                if (keyType != 3) {
                    if (event.getX() > whiteKeysWidth || event.getX() < 0) {
                        if (voice != -1) {
                            mOnKeyboardChangeListener.onPitchBend(voice, pitch + (event.getX()/whiteKeysWidth));
                        }
                    } else {
                        if (voice != -1) {
                            mOnKeyboardChangeListener.onPitchBend(voice, pitch);
                        }
                    }
                }
                if (keyType == 3) {
                    if (event.getX() > blackKeysWidth || event.getX() < 0) {
                        if (voice != -1) {
                            mOnKeyboardChangeListener.onPitchBend(voice, pitch + (event.getX()/blackKeysWidth));
                        }
                    } else {
                        if (voice != -1) {
                            mOnKeyboardChangeListener.onPitchBend(voice, pitch);
                        }
                    }
                }
                if (event.getY() < blackKeysHeight) {
                    gain = event.getY()/blackKeysHeight;
                    if (voice != -1) {
                        mOnKeyboardChangeListener.onYChanged(voice, gain);
                    }
                } else {
                    gain = 1;
                    if (voice != -1) {
                        mOnKeyboardChangeListener.onYChanged(voice, gain);
                    }
                }
			}
			return true;
		}
		
		@Override
	    protected void onLayout(boolean changed, int l, int t, int r, int b)
        {}
	}
	
	/*
	 * Single piano key element, for example black key down or up
	 */
	class PianoKeyElement extends View {
		private Drawable keyElement;
	
		public PianoKeyElement(Context context, int type, int mode)
        {
			super(context);
			
			Resources res = context.getResources();
            if (type == 0) {
                if (mode == 1) {
                    keyElement = res.getDrawable(R.drawable.piano_key_left_down);
                } else {
                    keyElement = res.getDrawable(R.drawable.piano_key_left);
                }
            } else if(type == 1) {
                if (mode == 1) {
                    keyElement = res.getDrawable(R.drawable.piano_key_center_down);
                } else {
                    keyElement = res.getDrawable(R.drawable.piano_key_center);
                }
            } else if(type == 2) {
                if (mode == 1) {
                    keyElement = res.getDrawable(R.drawable.piano_key_right_down);
                } else {
                    keyElement = res.getDrawable(R.drawable.piano_key_right);
                }
            } else if(type == 3) {
                if (mode == 1) {
                    keyElement = res.getDrawable(R.drawable.piano_key_black_down);
                } else {
                    keyElement = res.getDrawable(R.drawable.piano_key_black);
                }
            } else {
                if (mode == 1) {
                    keyElement = res.getDrawable(R.drawable.piano_key_center_down);
                } else {
                    keyElement = res.getDrawable(R.drawable.piano_key_center);
                }
            }
		}
	
		@Override
		protected void onSizeChanged(int w, int h, int oldw, int oldh)
        {
			super.onSizeChanged(w, h, oldw, oldh);
			
			// commented to remove the black border around keys: kind of look
			// better like that but can be reactivated at any time... Plus 
			// this remove any potential dead zone.
			//setPadding(3,0,3,3);
			
			float xpad = (float) (getPaddingLeft() + getPaddingRight());
			float ypad = (float) (getPaddingTop() + getPaddingBottom());
        
			int ww =  (int) (w - xpad);
			int hh = (int) (h - ypad);

			keyElement.setBounds(0, 0, ww, hh);
		}
	
		protected void onDraw(Canvas canvas)
        {
			super.onDraw(canvas);
			keyElement.draw(canvas);
		}
	}
}
