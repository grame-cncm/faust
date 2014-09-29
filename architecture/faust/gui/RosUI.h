#ifndef FAUST_RosUI_H
#define FAUST_RosUI_H


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "ros/ros.h"
#include "faust_msgs/ParamFaust.h"

class RosUI : public UI
{
    
    public :
    
	RosUI(ros::NodeHandle nh) : m_nh(nh), m_queue(10), m_count(0) {};
	
	//~RosUI() {}
	
	
	// -- callbacks
	
	void ButtonCallback(const faust_msgs::ParamFaustConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->value;
	    
	}
	
	void CButtonCallback(const faust_msgs::ParamFaustConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->value;
	    
	}
	
	void SliderCallback(const faust_msgs::ParamFaustConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->value;
	    
	}
	
	void NEntryCallback(const faust_msgs::ParamFaustConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->value;
	    
	}	
	
    	// -- widget's layouts

    	void openTabBox(const char* label)
    	{
    	}
	void openHorizontalBox(const char* label)
	{
	}
	void openVerticalBox(const char* label)
	{
	}
	void closeBox()
	{
	}

	// -- active widgets

	void addButton(const char* label, FAUSTFLOAT* zone)
	{
	    ros::Subscriber* _buttonSub = new ros::Subscriber();
	    *_buttonSub = m_nh.subscribe<faust_msgs::ParamFaust>((std::string)label, m_queue, boost::bind(&RosUI::ButtonCallback, this, _1, zone));
	    m_count++;
	 	
	}
	void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
	    ros::Subscriber* _CButtonSub = new ros::Subscriber();
	    *_CButtonSub = m_nh.subscribe<faust_msgs::ParamFaust>((std::string)label, m_queue, boost::bind(&RosUI::CButtonCallback, this, _1, zone));
	    m_count++;
	 
	 
	}
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    ros::Subscriber* _vSlider = new ros::Subscriber();
	    *_vSlider = m_nh.subscribe<faust_msgs::ParamFaust>((std::string)label, m_queue, boost::bind(&RosUI::SliderCallback, this, _1, zone));
	    m_count++;
	 
	  
	}
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    ros::Subscriber*_hSlider = new ros::Subscriber();
	    *_hSlider = m_nh.subscribe<faust_msgs::ParamFaust>((std::string)label, m_queue, boost::bind(&RosUI::SliderCallback, this, _1, zone));
	    m_count++;
	
	  
	}
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    ros::Subscriber* _numEntry = new ros::Subscriber();
	    *_numEntry = m_nh.subscribe<faust_msgs::ParamFaust>((std::string)label, m_queue, boost::bind(&RosUI::NEntryCallback, this, _1, zone));
	   m_count++;
	 
	
	}
	
	// -- passive widgets

	void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{
	}
	void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{
	}

	// -- metadata declarations

	void declare(FAUSTFLOAT* zone, const char* key, const char* val) 
	{
	}
    
    	int getParamsCount()
    	{
    	    return m_count;
    	}
    
    private :
    
	ros::NodeHandle m_nh;
	int m_queue;
	int m_count;
		
};

#endif
