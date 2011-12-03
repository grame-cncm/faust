#ifndef FAUST_CUI_H
#define FAUST_CUI_H


/*******************************************************************************
 * CUI : Faust User Interface for C generated code.
 ******************************************************************************/

// -- layout groups

typedef void (* openFrameBoxFun) (void* interface, const char* label);
typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, float* zone);
typedef void (* addToggleButtonFun) (void* interface, const char* label, float* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, float* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);
typedef void (* addNumEntryFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);

// -- passive display widgets

typedef void (* addNumDisplayFun) (void* interface, const char* label, float* zone, int precision);
typedef void (* addTextDisplayFun) (void* interface, const char* label, float* zone, const char* names[], float min, float max);
typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, float* zone, float min, float max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, float* zone, float min, float max);

typedef void (* declareFun) (void* interface, float* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openFrameBoxFun openFrameBox;
    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addToggleButtonFun addToggleButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addNumDisplayFun addNumDisplay;
    addTextDisplayFun addTextDisplay;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (const char* key, const char* value);

typedef struct {

    metaDeclareFun declare;

} MetaGlue;

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

#endif
