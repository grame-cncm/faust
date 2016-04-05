/**********************************************
* 			ROS Callbacks Interface
*
* This interface allows the user to use ROS 
* 	metadata
* It handles ROS metadata, and writes the 
*	callbacks directly in the .cpp file.
*
**********************************************/

#ifndef FAUST_RosCI_H
#define FAUST_RosCI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"

#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class RosCI : public UI
{
    
    public:
    
	RosCI(): count_(0), use_slider_values_(false), meta_(false)
	{};
	
	virtual ~RosCI() {}
	
	// String processing function
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
            if ((label[0]<65)  // before "A" in ASCII
                || (label[0] <= 96 && label[0] >= 91) // After "Z" and before "a" in ASCII
                || (label[0] > 122) // After "z" in ASCII
                && (label[0] != FORWARD_SLASH) // not "/"
                && (label[0] != TILDE) // not "~"
              )
            {
                label.erase(0,1);
                count = label.size();
            }
            else if(count < 1)
            {
                label = "/topic";
                count = label.size();
                ok = true;
            }
            else
            {
                ok = true;
            }
        }
        while (!ok);

        for (int i = 0; i < count; i++)
        {
            if ((label[i] <= 90 && label[i] >= 65)          // A-Z
                    || (label[i] <= 122 && label[i] >= 97)  // a-z
                    || (label[i] <= 57 && label[i] >= 47)   // 0-9
                    || label[i] == UNDERSCORE 
               )
            {
            }
            else if (label[i] == SPACE) 
            {
                if (label[i-1] == UNDERSCORE)
                {
                    label.erase(i,1);
                    i = i-1;
                    count = label.size();
                }
                else
                    label[i]='_';
            }

            else if(label[i]== LEFT_BRACKET) // in case of '('
            {
                if (label[i-1] == 95) 
                {
                    label.erase(i,1);
                    i = i-1;
                    count = label.size();
                }
                else		   
                    label[i]='_';
            }
            else if (label[i] == RIGHT_BRACKET) // in case of ')'
            {
                label.erase(i,1);
                i = i-1;
                count = label.size();
            }
            else
            {
                label.erase(i, 1);
                i = i-1;
                count = label.size();
            }

        }
        return (label);
    }
	
    // -- widget's layouts

	void openTabBox(const char* label)
	{}
	void openHorizontalBox(const char* label)
	{}
	void openVerticalBox(const char* label)
	{}
	void closeBox()
	{}

	// -- active widgets

	void addButton(const char* label, FAUSTFLOAT* zone)
	{}
	void addCheckButton(const char* label, FAUSTFLOAT* zone)
	{}
    
	void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
		*zone = init;
		if (meta_)
		{
			if (use_slider_values_)
			{
				callbacks_parameters_[count_-1].min_value = min;
				callbacks_parameters_[count_-1].max_value = max;
				use_slider_values_ = false;
			}
			callbacks_parameters_[count_-1].slider_min = min;
			callbacks_parameters_[count_-1].slider_max = max;
			meta_ = false;
		}
	}
    
	void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
		*zone = init;
		if (meta_)
		{
			if (use_slider_values_)
			{
				callbacks_parameters_[count_-1].min_value = min;
				callbacks_parameters_[count_-1].max_value = max;
				use_slider_values_ = false;
			}
			callbacks_parameters_[count_-1].slider_min = min;
			callbacks_parameters_[count_-1].slider_max = max;
			meta_ = false;
		}
	}
    
	void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, 
	FAUSTFLOAT max, FAUSTFLOAT step)
	{
		*zone=init;
		if (meta_)
		{
			if (use_slider_values_)
			{
				callbacks_parameters_[count_-1].min_value = min;
				callbacks_parameters_[count_-1].max_value = max;
				use_slider_values_ = false;
			}
			callbacks_parameters_[count_-1].slider_min = min;
			callbacks_parameters_[count_-1].slider_max = max;
			meta_ = false;
		}
	}
	
	// -- passive widgets

	void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{}
	void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
	{}

	// -- metadata declarations

	// Structure containing a callback parameters
	struct CallbackParams
	{
	    std::string topic_name;
	    std::string msg_type;
	    std::string msg_name;
	    std::string field_name;
	    FAUSTFLOAT min_value;
	    FAUSTFLOAT max_value;
	    FAUSTFLOAT slider_min;
	    FAUSTFLOAT slider_max;
	};
	
	// Callback writing the callbacks filekeyboard's arrows
		// num is the number of ROS declared metadata
		// param_vector is a callbacks parameters structure container 
		// name is the application name
	void callbacksWriter(int num, std::vector<RosCI::CallbackParams> param_vector, std::string name)
	{
		// Get file name
		name = name + ".cpp";
		const char* file_name = name.c_str();
		std::fstream file (file_name);
		
		if (!file.is_open())
		{
			std::cout<<"unable to open"<<file_name<<std::endl;
			return;
		}
		
		std::string line, test_line;
		bool search_RosUI = true;
		std::streampos begin = 0;
		std::streampos end=0;
		int block_size;
		char * memblock;
		
		test_line = "class RosUI : public UI";  // This is the line we look for
                                                // in the file so that we can
                                                // write callbacks before this line
		
		while( search_RosUI )
		{
			std::getline(file,line);
			if(line == test_line)
			{
				search_RosUI=false;
			}
			else 
			{
                // Get the searched line position
                begin += (std::streampos)line.size() +(std::streampos)1;	
			}		
		}
		// Get the end of file position
		file.seekp(0,std::ios::end);
		end = file.tellp();
		
		block_size = end-begin;
        memblock = new char[block_size];

		// puts the end of the file in a memory block
        // in order to overwrite without deleting information
		file.seekp(begin, std::ios::beg);
		file.read(memblock, block_size);
		file.seekp(begin,std::ios::beg);

		file <<"/*****************************"<<std::endl
			 <<"* Code generated automatically"<<std::endl
			 <<"* "<<std::endl
			 <<"* See the RosCI.h file"<<std::endl
			 <<"* \tCallbacksWriter function"<<std::endl
			 <<"* \tfor more informations"<<std::endl
			 <<"* "<<std::endl
			 <<"*****************************/\n"<<std::endl;
		
		// Include messages files if they are different
		bool include = true;
		for (int i = 0; i < num ; i++)
		{
			RosCI::CallbackParams parameters = param_vector[i];
			if (i != 0)
			{
				for (int j = 0; j < i; j++)
				{
					if (parameters.msg_type == param_vector[j].msg_type)
					{
						if (parameters.msg_name == param_vector[j].msg_name)
						{
							include = false;
						}
					}
				}
			}
				
			if (include)
			{
				file << "#include \""<< parameters.msg_type<<"/"
					 << parameters.msg_name<<".h\""<<std::endl;
			}
		}
			
		// New class
		file << "class RosCallbacks"<< std::endl
			 << "{" << std::endl
			 << "\tpublic : \n" << std::endl
			 << "\tRosCallbacks(ros::NodeHandle n) : nh_(n)"<<std::endl
			 << "\t{};\n"<<std::endl;
		
		// Ranging Function
		file << "\tfloat rangeAndConvert(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT slider_min, "<< std::endl
			 << "\t\tFAUSTFLOAT slider_max, float value)" << std::endl
			 << "\t{" << std::endl
			 << "\t\tif (value < min)" << std::endl
			 << "\t\t{" << std::endl
			 << "\t\t\tvalue = min;" << std::endl
			 << "\t\t}" << std::endl
			 << "\t\telse if (value > max)" << std::endl
			 << "\t\t{" << std::endl
			 << "\t\t\tvalue = max ;" << std::endl
			 << "\t\t}" << std::endl
			 << "\t\tfloat a = (slider_max - slider_min)/(max-min);" << std::endl
			 << "\t\tfloat b = (slider_max + slider_min - a*(max+min))/2;" << std::endl
			 << "\t\tvalue = a*value + b;\n" << std::endl
			 << "\t\treturn value;" << std::endl
			 << "\t}" << std::endl;
		
		// ROS specific callbacks
		for (int i = 0; i < num; i++)
		{
			RosCI::CallbackParams parameters = param_vector[i];
			file << "\tvoid callback"<<i<<"(const "<< parameters.msg_type<<"::"
				 << parameters.msg_name<<"ConstPtr& msg, FAUSTFLOAT* zone)"<<std::endl
				 << "\t{"<<std::endl
				 << "\t\t FAUSTFLOAT min"<<i<<" = "<<parameters.min_value<<";"<<std::endl
				 << "\t\t FAUSTFLOAT max"<<i<<" = "<<parameters.max_value<<";"<<std::endl
				 << "\t\t FAUSTFLOAT smin"<<i<<" = "<<parameters.slider_min<<";"<<std::endl
				 << "\t\t FAUSTFLOAT smax"<<i<<" = "<<parameters.slider_max<<";\n"<<std::endl
				 << "\t\t *zone =  rangeAndConvert(min"<<i<<", max"<<i<<", smin"<<i<<", smax"<<i
				 << ", (float) msg->"<<parameters.field_name<<");"<<std::endl
				 << "\t}\n"<<std::endl;
		}	
		
		// RosCallbacks class main function :
			// When called, it subscribes to all the predefined callbacks
		file << "\n\tvoid subscribe(std::vector<FAUSTFLOAT*> zones)\n"<<std::endl
			 << "\t{" <<std::endl;
		
		// Declaring subscribers and subscribing	 
		for (int i = 0; i < num; i++)
		{
			RosCI::CallbackParams parameters = param_vector[i];
			file << "\t\tros::Subscriber* my_sub"<<i<<" = new ros::Subscriber();"<<std::endl
				 << "\t\t*my_sub"<<i<<" = nh_.subscribe<"<<parameters.msg_type<<"::"<<parameters.msg_name
				 << ">(\"" <<parameters.topic_name
				 << "\", 1,"<<std::endl
				 << "\t\t\tboost::bind(&RosCallbacks::callback"<<i
				 << ", this, _1, zones["<<i<<"]));\n"<<std::endl;
		}
		
		file << "\t}\n"<<std::endl;
		
		// RosCallbacks class private parameter
		file << "\tprivate :\n"<<std::endl
			 << "\tros::NodeHandle nh_;"<<std::endl;
		
		file << "};\n" << std::endl;
		
		file << memblock;
		file.close();
	}
	
	// String parsing function, which detects every callback parameter
		// Separators must be spaces, and there must be 4 or 6 arguments
	void stringParser(std::string string2parse)
	{
	    int SPACE = 32;
	    
	    for (int i = 0; i < string2parse.size(); i++)
	    {
	    	if (string2parse[i] == SPACE)
	    	{
	    	    std::string param= string2parse.substr(0,i);
	    	    topic_params_.push_back(param);
	    	    string2parse.erase(string2parse.begin(), string2parse.begin()+i+1);
	    	    i = -1;
            }
	    }
	    
	    topic_params_.push_back(string2parse);
	}
	
	// Function declaring metadata
	void declare(FAUSTFLOAT* zone, const char* key, const char* val) 
	{
		if (key == "ros") // We do not care if key is not "ros" here
		{
			stringParser(val); // Parsing the string corresponding to a callback parameters
			CallbackParams params;
			if (topic_params_.size() == 4 
				||
				topic_params_.size() == 6)
			{
				// Storing the parameters in a structure...
				params.topic_name=strProcess(topic_params_[0]);
				params.msg_type=topic_params_[1];
				params.msg_name=topic_params_[2];
				params.field_name=topic_params_[3];
				
				if (topic_params_.size() == 6)
				{
					std::stringstream smin, smax;
					smin.str(topic_params_[4]);
					smin >> params.min_value;
					smax.str(topic_params_[5]);
					smax >> params.max_value;
				}
				else 
				{
					use_slider_values_ = true;
				}
					
				// ... and the structure in a vector 
				callbacks_parameters_.push_back(params);
				
				count_++;
				meta_ = true;
			}
			else
			{
				std::cout<<"Wrong number of parameters in ros metadata declaration !"<<std::endl;
				std::cout<<"It should look like : [ros:/my/topic/name msg_type msg_name"
						 <<" field_name]"<<std::endl;
				std::cout<<"Example : [ros:/topic/level std_msgs Float32 data]"<<std::endl;
			}
			
			do
			{
			    topic_params_.pop_back();
			}
			while ( !topic_params_.empty());
		}
	}
    
    // Function returning the number of metadata declared, 
    	//which means the number of callbacks to call
    int getParamsCount()
    {
        return count_;
    }
    
    // Function returning a vector containing ROS Callbacks parameters structures	
    std::vector<CallbackParams> getCallbacksParameters()
    {
        return callbacks_parameters_;
    }
    
    private:
    
	int count_;
	bool use_slider_values_;
	bool meta_;
	
	std::vector<std::string> topic_params_;
	std::vector<CallbackParams> callbacks_parameters_;
};

#endif
