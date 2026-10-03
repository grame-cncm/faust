#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>
#include <vector>
#include <utility>
#include <atomic>

// typedef std::vector<std::pair<std::string, std::string>> param_meta_items;
struct Parameter;
typedef std::vector<Parameter> ParameterList;

struct Parameter{
    
    std::atomic<float> value{0.0f};  // runtime value of the parameter

    std::string type;
    std::string label;
    std::string shortname;
    int index;
    float init;
    float pmin;
    float pmax;
    float step;
    // param_meta_items meta;

    struct UI
    {
        int id;
    }preview;

    // constructor
    Parameter();

    // delete copying
    Parameter(const Parameter &p) = delete;
    Parameter &operator=(const Parameter &p) = delete;

    // support move
    Parameter(Parameter&& p) noexcept;
    Parameter& operator=(Parameter&& p) noexcept;

};

#endif