#ifndef FAUST_RosUI_H
#define FAUST_RosUI_H


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "ros/ros.h"
#include "faust_msgs/ParamFaust.h"

#include <algorithm>

class RosUI : public UI
{
    
    public :
    
	RosUI(ros::NodeHandle nh) : m_nh(nh), m_queue(10), m_count(0) {};
	
	//~RosUI() {}
	
	// String function for topics names
	std::string str_process(std::string label)
    {
        int count = label.size();
        bool ok = false;
        
        do
        {
            if ((label[0]<65)  // before A in ASCII
                || (label[0]<=96 && label[0]>=91) // After Z and before a in ASCII
                || (label[0] > 122) // After z in ASCII
                && (label[0] != 47) // not /
                && (label[0] != 126) // not ~
              )
            {
                label.erase(0,1);
                count = label.size();
            }
            else if(count <= 1)
            {
                label = "/topic";
                count = label.size();
                ok=true;
            }
            else
            {
                ok=true;
            }
        }
        while (!ok);

        for (int i=0 ; i<count ; i++)
        {

            if ((label[i]<=90 && label[i]>=65) // A-Z
                    || (label[i]<=122 && label[i]>=97) // a-z
                    || (label[i]<=57 && label[i]>=47) // 0-9
                    || label[i]==95 // _
               )
            {
            }
            else if (label[i]==32) // in case of : ' ' (=space)
            {
                if(label[i-1]==95)
                {
                    label.erase(i,1);
                    i=i-1;
                    count = label.size();
                }
                else
                    label[i]='_';
            }

            else if(label[i]== 40) // in case of '('
            {
                if(label[i-1]==95) 
                {
                    label.erase(i,1);
                    i=i-1;
                    count = label.size();
                }
                else		   
                    label[i]='_';
            }
            else if (label[i]==41) // in case of ')'
            {
                label.erase(i,1);
                i=i-1;
                count = label.size();
            }
            else
            {
                label.erase(i, 1);
                i=i-1;
                count = label.size();
            }

        }
        return (label);
    }
	
	
	// -- callbacks
	
	void ButtonCallback(const faust_msgs::ParamFaustConstPtr& msg, FAUSTFLOAT* zone)
	{
	    // If msg-> value >=0, then the button is activated 
	    // and reset to 0 after 5 ms.
	    *zone=msg->value;
	    ros::Duration(0.005).sleep();
	    *zone=0;
	    
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
	    std::string String = (std::string)label;
	    
	    std::string myString = str_process(String);
	    
	    ros::Subscriber* _buttonSub = new ros::Subscriber();
	    *_buttonSub = m_nh.subscribe<faust_msgs::ParamFaust>(myString, m_queue, boost::bind(&RosUI::ButtonCallback, this, _1, zone));
	    m_count++;
	 	
	}
	void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
	    std::string String = (std::string)label;
	    
	    std::string myString = str_process(String);
	    
	    ros::Subscriber* _CButtonSub = new ros::Subscriber();
	    *_CButtonSub = m_nh.subscribe<faust_msgs::ParamFaust>(myString, m_queue, boost::bind(&RosUI::CButtonCallback, this, _1, zone));
	    m_count++;
	 
	 
	}
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string String = (std::string)label;
	    
	    std::string myString = str_process(String);
	    
	    ros::Subscriber* _vSlider = new ros::Subscriber();
	    *_vSlider = m_nh.subscribe<faust_msgs::ParamFaust>(myString, m_queue, boost::bind(&RosUI::SliderCallback, this, _1, zone));
	    m_count++;
	 
	  
	}
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string String = (std::string)label;
	    
	    std::string myString = str_process(String);
	    
	    ros::Subscriber*_hSlider = new ros::Subscriber();
	    *_hSlider = m_nh.subscribe<faust_msgs::ParamFaust>(myString, m_queue, boost::bind(&RosUI::SliderCallback, this, _1, zone));
	    m_count++;
	
	  
	}
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string String = (std::string)label;
	    
	    std::string myString = str_process(String);
	    
	    ros::Subscriber* _numEntry = new ros::Subscriber();
	    *_numEntry = m_nh.subscribe<faust_msgs::ParamFaust>(myString, m_queue, boost::bind(&RosUI::NEntryCallback, this, _1, zone));
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
