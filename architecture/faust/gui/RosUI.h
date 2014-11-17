#ifndef FAUST_RosUI_H
#define FAUST_RosUI_H


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"

#include <algorithm>
#include <vector>

class RosUI : public UI
{
    
    public :
    
	RosUI(ros::NodeHandle nh) : nh_(nh), queue_(10), count_(0), box_names_(0) 
	{
	    const std::string nh_name = nh_.getNamespace();
	    box_names_.push_back(nh_name);
	};
	
	//~RosUI() {}
	
	// String function for topics names
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
            if ((label[0]<65)  // before A in ASCII
                || (label[0]<=96 && label[0]>=91) // After Z and before a in ASCII
                || (label[0] > 122) // After z in ASCII
                && (label[0] != FORWARD_SLASH) // not /
                && (label[0] != TILDE) // not ~
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
                    || label[i]==UNDERSCORE 
               )
            {
            }
            else if (label[i]==SPACE) 
            {
                if(label[i-1]==UNDERSCORE)
                {
                    label.erase(i,1);
                    i=i-1;
                    count = label.size();
                }
                else
                    label[i]='_';
            }

            else if(label[i]== LEFT_BRACKET) // in case of '('
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
            else if (label[i]==RIGHT_BRACKET) // in case of ')'
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
	
	void buttonCallback(const std_msgs::BoolConstPtr& msg, FAUSTFLOAT* zone)
	{
	    
	    *zone=msg->data;
	    //ros::Duration(0.005).sleep();
	    //*zone=0;
	    
	}
	
	void cButtonCallback(const std_msgs::BoolConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->data;
	    
	}
	
	void sliderCallback(const std_msgs::Float32ConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->data;
	    
	}
	
	void numEntryCallback(const std_msgs::Float32ConstPtr& msg, FAUSTFLOAT* zone)
	{
	    *zone=msg->data;
	    
	}	
	
    	// -- widget's layouts

    	void openTabBox(const char* label)
    	{
	    std::string L = (std::string)label;
	    if(L == "0x00")
	    {
		L="";
	    }
	    
	    box_names_.push_back(L);
    	}
	void openHorizontalBox(const char* label)
	{
	    std::string L = (std::string)label;
	    if(L == "0x00")
	    {
		L="";
	    }
	    
	    box_names_.push_back(L);
	    
	}
	void openVerticalBox(const char* label)
	{
	    std::string L = (std::string)label;
	    if(L == "0x00")
	    {
		L="";
	    }
	    
	    box_names_.push_back(L);
	}
	void closeBox()
	{
	    box_names_.pop_back();
	}

	// -- active widgets

	void addButton(const char* label, FAUSTFLOAT* zone)
	{
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    if (! box_names_.empty())
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
	    std::cout<<"RosUI.h - function addButton - line 187 : No box name to use ! "<<std::endl;
	    std::cout<<"Finishing..."<<std::endl;
	    return;
	    }
  
	    ros::Subscriber* button_sub = new ros::Subscriber();
	    *button_sub = nh_.subscribe<std_msgs::Bool>(my_string, queue_, 
	    boost::bind(&RosUI::buttonCallback, this, _1, zone));
	    count_++;
	 	
	}
	void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    if (! box_names_.empty())
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
	    std::cout<<"RosUI.h - function addCheckButton - line 225 : No box name to use ! "<<std::endl;
	    std::cout<<"Finishing..."<<std::endl;
	    return;
	    }
	    
	    ros::Subscriber* c_button_sub = new ros::Subscriber();
	    *c_button_sub = nh_.subscribe<std_msgs::Bool>(my_string, queue_, 
	    boost::bind(&RosUI::cButtonCallback, this, _1, zone));
	    count_++;
	 
	 
	}
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);

	    if (! box_names_.empty())
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
	    std::cout<<"RosUI.h - function addVerticalSlider - line 263 : No box name to use ! "<<std::endl;
	    std::cout<<"Finishing..."<<std::endl;
	    return;
	    }
	    
	    
	    ros::Subscriber* v_slider = new ros::Subscriber();
	    *v_slider = nh_.subscribe<std_msgs::Float32>(my_string, queue_, 
	    boost::bind(&RosUI::sliderCallback, this, _1, zone));
	    count_++;
	 
	  
	}
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    if (! box_names_.empty())
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
	    std::cout<<"RosUI.h - function addHorizontalSlider - line 303 : No box name to use ! "<<std::endl;
	    std::cout<<"Finishing..."<<std::endl;
	    return;
	    }
	    
	    ros::Subscriber* h_slider = new ros::Subscriber();
	    
	    *h_slider = nh_.subscribe<std_msgs::Float32>
	    (my_string, queue_, boost::bind(&RosUI::sliderCallback, this, _1, zone));
	    count_++;
	
	  
	}
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
	    std::string str = (std::string)label;
	    
	    std::string my_string = strProcess(str);
	    
	    if (! box_names_.empty())
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
	    std::cout<<"RosUI.h - function addNumEntry - line 343 : No box name to use ! "<<std::endl;
	    std::cout<<"Finishing..."<<std::endl;
	    return;
	    }
	    ros::Subscriber* num_entry = new ros::Subscriber();
	    *num_entry = nh_.subscribe<std_msgs::Float32>(my_string, queue_, 
	    boost::bind(&RosUI::numEntryCallback, this, _1, zone));
	   count_++;
	 
	
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
    	    return count_;
    	}
    
    private :
    
	ros::NodeHandle nh_;
	int queue_;
	int count_;
	
	std::vector<std::string> box_names_;
		
};

#endif
