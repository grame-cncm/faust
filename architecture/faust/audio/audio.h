
/******************************************************************************
*******************************************************************************

						An abstraction layer over audio layer

*******************************************************************************
*******************************************************************************/

#ifndef __audio__
#define __audio__
			
class dsp;

typedef void (* shutdown_callback)(const char* message, void* arg);

typedef void (* buffer_size_callback)(int frames, void* arg);

class audio {
    
 public:
			 audio() {}
	virtual ~audio() {}
	
	virtual bool init(const char* name, dsp*)               = 0;
	virtual bool start()                                    = 0;
	virtual void stop()                                     = 0;
    virtual void shutdown(shutdown_callback cb, void* arg)  {}
    
};
					
#endif
