
/******************************************************************************
*******************************************************************************

						An abstraction layer over audio layer

*******************************************************************************
*******************************************************************************/

#ifndef __audio__
#define __audio__
			
class dsp;
class audio {
 public:
			 audio() {}
	virtual ~audio() {}
	
	virtual bool init(const char* name, dsp*)	= 0;
	virtual bool start()						= 0;
	virtual void stop()							= 0;
};
					
#endif
