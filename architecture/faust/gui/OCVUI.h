/************************************************
* 			OpenCV User Interface			  	*
*												*
* This architecture file allows the user to	  	*
*	use the OpenCV library in order to perform	*
*	image processing and use the result 		*
*	to control audio parameters.				*
*												*
* To use this mode, just add the option -ocv in *
* 	the command line. 							*
*												*
************************************************/
#ifndef _OCVUI_H
#define _OCVUI_H


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

// OpenCV includes
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// Basic includes
#include <iostream>
#include <ctype.h>

// std::thread
#include <pthread.h>

// OpenCV Main Loop Function Prototype

static void* ocvLoop(void*);

//********	OpenCV User Interface CLASS DEFINITION ********//
class OCVUI : public UI
{
    
    public :
    
    ////////////////////////////////////////////
	////									////
	////			STRUCTURES				////
	////									////
	////////////////////////////////////////////
	
	struct object
	{
		int color;
		float centerX;
		float centerY;
		float area;
		int radius;
	};
	
	struct metadata
	{
		FAUSTFLOAT* zone;
		int color;
		std::string param;
		bool used;
	};
	
	////////////////////////////////////////////
	////									////
	////			FUNCTIONS				////
	////									////
	////////////////////////////////////////////
	
	/**********************************************/
	/*******	UI Functions Redefinition	*******/
	/**********************************************/
		// Functions inherited from the UI class
	
    // Constructor
	OCVUI() : objects_storage_(0), parameters_storage_(0), height_(0), width_(0){};
	
	// Destructor
	~OCVUI() 
	{
	exit_=true;
	pthread_join(loop_, NULL);	
	};
	
	
	// -- WIDGETS LAYOUTS
	void openTabBox(const char* label){}
	void openHorizontalBox(const char* label){}
	void openVerticalBox(const char* label){}
	void closeBox(){}

	// -- ACTIVE WIDGETS
	void addButton(const char* label, FAUSTFLOAT* zone){}
	void addCheckButton(const char* label, FAUSTFLOAT* zone){}
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
	FAUSTFLOAT max, FAUSTFLOAT step){}
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step){}
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step){}
	
	// -- PASSIVE WIDGETS
	void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max){}
	void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max){}


	// -- METADATA DECLARATION
	
	
	//******** Parsing function	********//
		// This function analyses a string and stores
		// the different parameters in a metadata structure.
		
	bool parser(std::string string2parse, metadata *pmeta)
	{
	    int SPACE = 32; // Parameters separator
	    std::vector<std::string> parameters(0);
	    
	    //*** String analysis ***//
	    for (int i = 0 ; i < string2parse.size() ; i++)
	    {
	    	if (string2parse[i]==SPACE)
	    	{
	    	    std::string oneParameter= string2parse.substr(0,i);
	    	    parameters.push_back(oneParameter);
	    	    string2parse.erase(string2parse.begin(), string2parse.begin()+i+1);
	    	    i=0;
	    	}	
	    }
	    std::string lastParameter = string2parse;
	    parameters.push_back(lastParameter);
	    	    
	    //*** Store Parameters in a Metadata Structure ***//
	    
	    // Parameters count must be 2
	    if (parameters.size()==2)
	    {
	    	// Associate every color to a digit
	    		// red		= 1	;	green 	= 3	;	blue 	= 5	;
	    		// yellow	= 2	;	cyan	= 4	;	magenta = 6	.
	    		
	    	if (parameters[0]=="red")
	    	{
	    		pmeta->color = 1;
	    	}
	    	else if (parameters[0]=="yellow")
	    	{
	    		pmeta->color = 2;
	    	}
	    	else if (parameters[0]=="green")
	    	{
	    		pmeta->color = 3;
	    	}
	    	else if (parameters[0]=="cyan")
	    	{
	    		pmeta->color = 4;
	    	}
	    	else if (parameters[0]=="blue")
	    	{
	    		pmeta->color = 5;
	    	}
	    	else if (parameters[0]=="magenta")
	    	{
	    		pmeta->color = 6;
	    	}
	    	pmeta->param = parameters[1];
	    	pmeta->used = false;
	    	return true;
	    }
	    else
	    {
	    	std::cout<<"Wrong count of parameters. Please check if the OpenCV"
	    			 <<"metadata is correctly defined"<<std::endl;
	    	return false;
	    }
	}
	//******** Declare Function ********//
	// This function calls the parsing function if the declared key is "ocv"
		// and creates a new metadata structure.
	void declare(FAUSTFLOAT* zone, const char* key, const char* val) 
	{
		if (key=="ocv")
		{
			metadata newMeta;
			bool string_parsed = false;
						
			if (zone != 0)
			{
				newMeta.zone = zone;
			}
			string_parsed = parser(val, &newMeta);
			
			if (string_parsed)
			{
				parameters_storage_.push_back(newMeta);
			}
		}
	}
	
	/**************************************************/
    /*******	Image Processing Functions		*******/
    /**************************************************/
       
    //*** Contours processing ***//   
    	// This function approximates contours to rectangles,
    	// keeps the bigest one,
    	// and stores it as a new object.
    void contoursProcess(std::vector<std::vector<cv::Point> > contours, int color)
	{
		int tempArea=0;
		cv::Rect myRect;
		for (int j=0 ; j<contours.size() ; j++)								// for each contour
		{
			std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
			std::vector<cv::Rect> boundRect( contours.size() );
		
			if (contours[j].size()>40)										// Do not take care about small
																				// contours
			{
				approxPolyDP( cv::Mat(contours[j]), contours_poly[j], 3, true );// Approximate contours to 
																				// a polygone
				boundRect[j] = cv::boundingRect( cv::Mat(contours_poly[j]) );		// Bound a contour in a 
																				// rectangle
				if ((int)boundRect[j].area()>tempArea)	
				{
					tempArea=(int)boundRect[j].area();
					myRect = boundRect[j];
				}
			}	
		}
		if (tempArea != 0)
		{
			// Create a new object structure to store the object properties
			object newObject;
			newObject.color = color;
			newObject.centerX = myRect.x+myRect.width/2;
			newObject.centerY = myRect.y+myRect.height/2;
			newObject.area = 1.5*(float)tempArea/(width_*height_);
			newObject.radius= (int)MIN(myRect.width/2, myRect.height/2);
				
			// Put the new object in the objects storage.
			objects_storage_.push_back(newObject);
		}
	}
	//*** Morphological Opening (Erosion and Dilatation) ***//
		// Improve a mask shape
		// See OpenCV documentation for more informations :
		// http://docs.opencv.org/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
	
	void erodeAndDilate(cv::Mat image)
	{
		cv::Mat element;
		element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
		
		// Erase small alone pixels
			// http://docs.opencv.org/modules/imgproc/doc/filtering.html#dilate
		for (int i = 0; i<2 ; i++)
		{
			cv::erode(image, image, element);
		}
		
		// Enlarge blocks of pixels
			// http://docs.opencv.org/modules/imgproc/doc/filtering.html#erode
		for (int i = 0; i<10 ; i++)
		{
			cv::dilate(image, image, element);
		}
	}

	
	//*** Image Threshold ***//
		// This function creates a mask for every defined color
	void thresholdHsv(cv::Mat image)
	{
		// Mask matrices (red, yellow, green, cyan, blue and magenta)
		cv::Mat r_mask, y_mask, g_mask, c_mask, b_mask, m_mask;
	
		// Objects contours
		std::vector<std::vector<cv::Point> > r_contours, y_contours, g_contours, 
											 c_contours, b_contours, m_contours;
		std::vector<cv::Vec4i> hierarchy;
		
		// Get every pixel whose value is between _min and _max
			// and put it into a mask
		cv::inRange(image, red_min, red_max, r_mask);
		cv::inRange(image, yellow_min, yellow_max, y_mask);
		cv::inRange(image, green_min, green_max, g_mask);
		cv::inRange(image, cyan_min, cyan_max, c_mask);
		cv::inRange(image, blue_min, blue_max, b_mask);
		cv::inRange(image, magenta_min, magenta_max, m_mask);
		
		// Improve masks shapes
		erodeAndDilate(r_mask);
		erodeAndDilate(y_mask);
		erodeAndDilate(g_mask);
		erodeAndDilate(c_mask);
		erodeAndDilate(b_mask);
		erodeAndDilate(m_mask);
	
		// Get the shapes contours from masks
		cv::findContours(r_mask, r_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		cv::findContours(y_mask, y_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		cv::findContours(g_mask, g_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		cv::findContours(c_mask, c_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		cv::findContours(b_mask, b_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		cv::findContours(m_mask, m_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	
		// Process every contour. Note that color is taken in account.
		for (int i=1 ; i<=6 ; i++)
		{
			switch (i)
			{
			case 1:		// RED
				contoursProcess(r_contours, 1);
			
				break;
			
			case 2:		// YELLOW
				contoursProcess(y_contours, 2);
			
				break;
			
			case 3:		// GREEN
				contoursProcess(g_contours, 3);
			
				break;
			
			case 4:		// CYAN
				contoursProcess(c_contours, 4);
			
				break;
		
			case 5:		// BLUE
				contoursProcess(b_contours, 5);
			
				break;
			
			case 6:		// MAGENTA
				contoursProcess(m_contours, 6);
			
				break;
		
			default:	// You'll have to add a new color...
				break;
			}
		}
	
	}

	//*** Object Detection ***//
		// This function calls the previous image processing functions
		// and uses the objects and parameters storages to set the audio parameters
		// depending on the detected objects.
	void detectObjects(cv::Mat hsvImage, cv::Mat originalFrame)
	{	
		height_ = originalFrame.rows;
		width_ = originalFrame.cols;
		
		// Objects detection and storage 
		thresholdHsv(hsvImage);
		
		// Audio parameters setting
		for (int i=0 ; i<objects_storage_.size() ; i++)
		{
			for (int j=0 ; j<parameters_storage_.size() ; j++)
			{
				if(objects_storage_[i].color==parameters_storage_[j].color
					&& !parameters_storage_[j].used)
				{
					if (parameters_storage_[j].param=="color")
					{
						*parameters_storage_[j].zone=(float)objects_storage_[i].color;
					}
					else if (parameters_storage_[j].param=="x")
					{
						*parameters_storage_[j].zone=objects_storage_[i].centerX/width_;
					}
					else if (parameters_storage_[j].param=="y")
					{
						*parameters_storage_[j].zone=1-(objects_storage_[i].centerY/height_);
					}
					else if (parameters_storage_[j].param=="area")
					{
						*parameters_storage_[j].zone=(float)objects_storage_[i].area;
					}
					parameters_storage_[j].used=true;
				}
			}
			
			
			
			// Draw a circle around the object for each object in the objects storage.
				// Circle color depends on the object color, of course !
			cv::Scalar bgr_color;
			switch (objects_storage_[i].color)
			{
				case 1: // RED
					bgr_color = cv::Scalar (0,0,255); // red in BGR (not RGB)
				
					break;
					
				case 2: //YELLOW
					bgr_color = cv::Scalar (0, 255, 255); // yellow in BGR
					
					break;
				
				case 3: // GREEN
					bgr_color = cv::Scalar (0, 255, 0);
				
					break;
				case 4: // CYAN
					bgr_color = cv::Scalar (255, 255, 0);
					
					break;
				
				case 5: // BLUE
					bgr_color = cv::Scalar (255,0,0); // blue in BGR (not RGB)
		
					break;
				
				case 6: // MAGENTA
					bgr_color = cv::Scalar (255, 0, 255);
					
					break;
	
				default: // Add a color !
					break;
			}
			// draw circle around every detected object
			cv::circle(originalFrame, cv::Point(objects_storage_[i].centerX, objects_storage_[i].centerY),
					   objects_storage_[i].radius, bgr_color, 2, 8, 0);
		}
	}
	
	/*******************************************/
	/********	Other Usefull Functions	********/
	/*******************************************/
	
	// Empty Function
		// This function empties both objects and parameters storages
	void empty()
    {
    	while (objects_storage_.size()>0)
    	{
    		objects_storage_.pop_back();
    	}
		
		for(int l=0 ; l<parameters_storage_.size() ; l++)
		{
			parameters_storage_[l].used=false;
		}
	}
	
	bool exit()
	{
		return exit_;
	}
	
	void exitThread()
	{
		pthread_exit(NULL);
	}
	
	void run()
	{		
		exit_=false;
		int create_thread = 1;
	
		create_thread = pthread_create(&loop_, NULL, ocvLoop, (void *) this);
		
		if (create_thread)
		{
			std::cout<<"Could not create thread. Thread Creation failed."<< std::endl;
		}

	}
       	
    ////////////////////////////////////////////
	////									////
	////		  MEMBER VARIABLES  		////
	////									////
	////////////////////////////////////////////
	
    private :
    	
	// HSV min and max values variables
	// #1 : RED
	static cv::Scalar red_min;
	static cv::Scalar red_max;
	
	// #2 : YELLOW
	static cv::Scalar yellow_min;
	static cv::Scalar yellow_max;
	
	// #3 : GREEN
	static cv::Scalar green_min;
	static cv::Scalar green_max;
	
	// #4 : CYAN
	static cv::Scalar cyan_min;
	static cv::Scalar cyan_max;
	
	// #5 : BLUE
	static cv::Scalar blue_min;	
	static cv::Scalar blue_max;
	
	// #6 : MAGENTA
	static cv::Scalar magenta_min;
	static cv::Scalar magenta_max;

	// Objects Storage
		// Where all the objects are stored
	std::vector<object> objects_storage_;
	
	// Parameters Storage
		// Where all the "ocv" metadata parameters are stored
	std::vector<metadata> parameters_storage_;
	
	// Matrix height and width
	int height_, width_;
	
	// Loop thread;
	pthread_t loop_;
	
	// Thread EXIT variable
	bool exit_;
		
};

// HSV min and max values
	// Note that H is between 0 and 180 
	// in openCV
	
// #1 = RED
cv::Scalar OCVUI::red_min = cv::Scalar (0,200,55);
cv::Scalar OCVUI::red_max = cv::Scalar (1,255,255);

// #2 = YELLOW
cv::Scalar OCVUI::yellow_min = cv::Scalar (25, 200, 55);
cv::Scalar OCVUI::yellow_max = cv::Scalar (35, 255, 255);

// #3 = GREEN
cv::Scalar OCVUI::green_min = cv::Scalar (30,155,55);
cv::Scalar OCVUI::green_max = cv::Scalar (40,255,255);

// #4 = CYAN
cv::Scalar OCVUI::cyan_min = cv::Scalar (85,200,55);
cv::Scalar OCVUI::cyan_max = cv::Scalar (95,200,55);

// #5 = BLUE
cv::Scalar OCVUI::blue_min = cv::Scalar (115,155,55);
cv::Scalar OCVUI::blue_max = cv::Scalar (125,255,255);

// #6 = MAGENTA
cv::Scalar OCVUI::magenta_min = cv::Scalar (145,200,55);
cv::Scalar OCVUI::magenta_max = cv::Scalar (155,255,255);


// OpenCV Main Loop Function Implementation
	// This function is a loop that gets every frame from a camera
	// and calls the image processing functions.
	// This is the OCVUI.h main function.
void* ocvLoop(void* ocv_object)
{
	// The camera index allows to select the camera.
		// 0 stands for the default camera.
	int camIndex=2;
	//std::cout<<"camera index ?"<<std::endl;
	//std::cin>>camIndex;

	cv::Mat frame, hsv;
	OCVUI* ocv = (OCVUI*) ocv_object;
	cv::VideoCapture cap(camIndex);
	std::cout<<"Video Capture from camera n°"<<camIndex<<std::endl;
	
	if(!cap.isOpened())  // check if we succeeded to read frames
							// from camera
	{
		std::cout<<"Could not open camera n°"<<camIndex<<" !"<<std::endl;
		
	}
    	  
	cap.set(CV_CAP_PROP_FPS, 60); 	// Set frames rate
		
	cv::namedWindow( "Tracking", 1 );	// Create a window

	while(!ocv->exit())
   	{

   	    cap >> frame;							// Get frame from camera
   	    cv::cvtColor(frame, hsv, CV_BGR2HSV);		// Convert frame to HSV format 
   	    											// in order to use "inRange"
   	            														
		ocv->detectObjects(hsv, frame);				// Objects Detection function
	
   		/*** Show image ***/
   		cv::imshow("Tracking", frame);

   		ocv->empty();								// Empty the objects and parameters storages
     	
   		/*** break ***/
  		//if(cv::waitKey(27) >= 0) break;

   	}
   	
   	ocv->exitThread();

}

#endif
