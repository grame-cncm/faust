/**********************************************
* 			ROS User Interface
*
* This interface  creates default callbacks 
*	with default messages types
* It also returns parameters for specific ROS
*  callbacks, defined in the RosCallbacks class
*	thanks to the RosCI.h and ros-callbacks.cpp
* 	architecture files
**********************************************/
#ifndef FAUST_RosUI_H
#define FAUST_RosUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"

#include <algorithm>
#include <vector>

class RosUI : public UI
{
    
    public:
    
	RosUI(ros::NodeHandle nh, std::string nspace) : nh_(nh), queue_(10), count_(0), meta_(false), box_names_(0), zones_(0) 
	{
	   // Get the namespace's name for default topics
	   box_names_.push_back(nspace);
	};
	
	virtual ~RosUI() {}
	
	// String processing function for topics names
	std::string strProcess(std::string label)
    {
        int count = label.size();
        bool ok = false;
        int FORWARD_SLASH = 47;
        int TILDE = 126;
        int UNDERSCORE = 95;
        int SPACE = 32;
        int LEFT_BRACKET = 40;
        int RIGHT_BRACKET = 41;
        
        do
        {
            if ((label[0] < 65)  // before "A" in ASCII
                || (label[0] <= 96 && label[0] >= 91) // After "Z" and before "a" in ASCII
                || (label[0] > 122) // After "z" in ASCII
                && (label[0] != FORWARD_SLASH) // not "/"
                && (label[0] != TILDE) // not "~"
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

        for (int i=0; i < count; i++)
        {
            if ((label[i] <= 90 && label[i] >= 65) // A-Z
                    || (label[i] <= 122 && label[i] >= 97) // a-z
                    || (label[i] <= 57 && label[i] >= 47) // 0-9
                    || label[i] == UNDERSCORE 
               )
            {
            }
            else if (label[i] == SPACE) 
            {
                if(label[i-1] == UNDERSCORE)
                {
                    label.erase(i,1);
                    i=i-1;
                    count = label.size();
                }
                else
                    label[i] = '_';
            }

            else if(label[i] == LEFT_BRACKET) // in case of '('
            {
                if(label[i-1] == 95) 
                {
                    label.erase(i,1);
                    i=i-1;
                    count = label.size();
                }
                else		   
                    label[i] = '_';
            }
            else if (label[i] == RIGHT_BRACKET) // in case of ')'
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
	
	// -- default callbacks
	
	// Default Callbacks :
		// Buttons widgets use the std_msgs/Bool message type
		// Sliders and Numerical entries use the std_msgs/Float32 message type
	
	void buttonCallback(const std_msgs::BoolConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone = msg->data;
	}
	
	void cButtonCallback(const std_msgs::BoolConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone = msg->data;
	}
	
	void sliderCallback(const std_msgs::Float32ConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone = msg->data;
	}
	
	void numEntryCallback(const std_msgs::Float32ConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone = msg->data;
	}	
	
	// -- widget's layouts
		// Boxes names are stored in a vector so that the default topics names
		// fit to the graphic interface

	void openTabBox(const char* label)
	{
		std::string L = (std::string)label;
		if (L == "0x00") // no box name
		{
			L = "";
		}
	    
		box_names_.push_back(L);	    
	}
	
	void openHorizontalBox(const char* label)
	{
		std::string L = (std::string)label;
		if (L == "0x00") // no box name
		{
			L = "";
		}
	    
		box_names_.push_back(L);	    
	}
	
	void openVerticalBox(const char* label)
	{
		std::string L = (std::string)label;
		if (L == "0x00") // no box name
		{
			L = "";
		}
	    
		box_names_.push_back(L);	    
	}
	
	void closeBox()
	{
	    box_names_.pop_back();
	}

	// -- active widgets
    // Adding a widget is translated into subscribing to a topic
    // For each widget, we use default messages types
    // Buttons							: std_msgs/Bool
    // Sliders and Numerical Entries	: std_msgs/Float32

	void addButton(const char* label, FAUSTFLOAT* zone)
	{
	    // Gets the button name and processes it to fit to ROS naming conventions
	    std::string str = (std::string)label;
	    std::string my_string = strProcess(str);
	    
	    // Builds the topic name from boxes and button names
	    if (! box_names_.empty())
	    {
            std::string my_name = "";
		
			for (int i = 0; i<box_names_.size(); i++)
			{
			    if (box_names_[i] != "")
			    {
					my_name += "/" + strProcess(box_names_[i]); 
		    	}   
		    	else 
		    	{
					box_names_.erase(box_names_.begin()+i);
		    	}
			}
			
			my_string = my_name + "/" + my_string;
        }
	    else
	    {
	    	ROS_ERROR("RosUI.h - function addButton : No box name to use ! ");
	    	ROS_INFO("Button's callback will not be subscribed");
	    	return;
	    }
  		
  		// Subscription to buttons callback
	    ros::Subscriber* button_sub = new ros::Subscriber();
	    
	    *button_sub = nh_.subscribe<std_msgs::Bool>(my_string, queue_, 
	    boost::bind(&RosUI::buttonCallback, this, _1, zone));
	    
	    count_++;
	}
	void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
	    // Gets the check button name and processes it to fit to ROS naming conventions
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    // Builds the topic name from boxes and check button names
	    if (! box_names_.empty())
	    {
			std::string my_name = "";
		
			for (int i = 0; i<box_names_.size(); i++)
			{
			    if (box_names_[i] != "")
			    {
					my_name += "/" + strProcess(box_names_[i]); 
		    	}   
		    	else 
		    	{
					box_names_.erase(box_names_.begin()+i);
		    	}
			}
			
			my_string = my_name + "/" + my_string;
        }
	    else
	    {
	    	ROS_ERROR("RosUI.h - function addCheckButton : No box name to use ! ");
	    	ROS_INFO("Check button's callback will not be subscribed");
	    	return;
	    }
	    
	    // Subscription to check buttons callback
	    ros::Subscriber* c_button_sub = new ros::Subscriber();
	    
	    *c_button_sub = nh_.subscribe<std_msgs::Bool>(my_string, queue_, 
	    boost::bind(&RosUI::cButtonCallback, this, _1, zone));
	    
	    count_++;
	}
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	     // Gets the vertical slider name and processes it to fit to ROS naming conventions
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    // Builds the topic name from boxes and vertical slider names

	    if (! box_names_.empty())
	    {
			std::string my_name = "";
		
			for (int i = 0; i<box_names_.size(); i++)
			{
			    if (box_names_[i] != "")
			    {
					my_name += "/" + strProcess(box_names_[i]); 
			    }   
			    else 
			    {
					box_names_.erase(box_names_.begin()+i);
				}
			}
			
			my_string = my_name + "/" + my_string;
	    }
	    else
	    {
	    	ROS_ERROR("RosUI.h - function addVerticalSlider : No box name to use ! ");
	    	ROS_INFO("Vertical slider's callback will not be subscribed");
	    	return;
	    }
	    
	    // Subscription to sliders callback
	    ros::Subscriber* v_slider = new ros::Subscriber();
	    
	    *v_slider = nh_.subscribe<std_msgs::Float32>(my_string, queue_, 
	    boost::bind(&RosUI::sliderCallback, this, _1, zone));
	    
	    count_++;
	}
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    // Gets the horizontal slider name and processes it to fit to ROS naming conventions
	    std::string str = (std::string)label;
	    std::string my_string = strProcess(str);
	    
	    // Builds the topic name from boxes and horizontal slider names	    
	    if (!box_names_.empty())
	    {
			std::string my_name = "";
		
			for (int i = 0 ; i<box_names_.size() ; i++)
			{
			    if (box_names_[i] != "")
			    {
					my_name += "/" + strProcess(box_names_[i]); 
		    	}   
		    	else 
		    	{
					box_names_.erase(box_names_.begin()+i);
		    	}
			}
			
			my_string = my_name + "/" + my_string;
	    }
	    else
	    {
	    	ROS_ERROR("RosUI.h - function addVerticalSlider : No box name to use ! ");
	    	ROS_INFO("Vertical slider's callback will not be subscribed");
	    	return;
	    }
	    
	    // Subscription to sliders callback
	    ros::Subscriber* h_slider = new ros::Subscriber();
	    
	    *h_slider = nh_.subscribe<std_msgs::Float32>
	    (my_string, queue_, boost::bind(&RosUI::sliderCallback, this, _1, zone));
	    
	    count_++;
	}
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    // Gets the numerical entry name and processes it to fit to ROS naming conventions
	    std::string str = (std::string)label;
	    std::string my_string = strProcess(str);
	    
	    // Builds the topic name from boxes and numerical entry names
	    
	    if (! box_names_.empty())
	    {
			std::string my_name = "";
		
			for (int i = 0; i<box_names_.size(); i++)
			{
			    if (box_names_[i] != "")
		    	{
					my_name += "/" + strProcess(box_names_[i]); 
		    	}   
		    	else 
		    	{
					box_names_.erase(box_names_.begin()+i);
				}
			}
		
			my_string = my_name + "/" + my_string;
	    }
	    else
	    {
		    ROS_ERROR("RosUI.h - function addVerticalSlider : No box name to use ! ");
	    	ROS_INFO("Vertical slider's callback will not be subscribed");
	    	return;
	    }
	    
	    // Subscription to numerical entries callback
	    ros::Subscriber* num_entry = new ros::Subscriber();
	    *num_entry = nh_.subscribe<std_msgs::Float32>(my_string, queue_, 
	    boost::bind(&RosUI::numEntryCallback, this, _1, zone));
	    
		count_++;
 	}
	
	// -- passive widgets
    // Nothing to say - not used

	void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{}
	void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{}

	// -- metadata declarations

	void declare(FAUSTFLOAT* zone, const char* key, const char* val) 
	{
		if (key=="ros") // We do not care if key is not "ros" here
		{
			// Adds the Faust parameter's address (zone) to a zone vector
	    		// if a ros metadata has been declared
			zones_.push_back(zone);
		}
	}
    
    // Function returning the number of widgets added
	int getParamsCount()
	{
		return count_;
	}
	
	// Function saying if, yes or no, there is any ROS metadata declared
	bool isTrue()
    {
    	if (!zones_.empty())
    	{
    		return true; // yes
    	}
    	else
    	{
    		return false; // no
    	}
    }
	
	// Function returning the Faust parameters addresses (zones)
		// if these zones correspond to metadata declared topics
	std::vector<FAUSTFLOAT*> getZones()
	{
		return zones_;
	}
    
    private:
    
	ros::NodeHandle nh_;
	int queue_;
	int count_;
	bool meta_;
	
	std::vector<std::string> box_names_;
	std::vector<FAUSTFLOAT*> zones_;
};

#endif
