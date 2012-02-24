#ifndef FAUST_CUI_H
#define FAUST_CUI_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * CUI : Faust User Interface for C generated code.
 ******************************************************************************/

/* -- layout groups */

typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

/* -- active widgets */

typedef void (* addButtonFun) (void* interface, const char* label, float* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, float* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);
typedef void (* addNumEntryFun) (void* interface, const char* label, float* zone, float init, float min, float max, float step);

/* -- passive display widgets */

typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, float* zone, float min, float max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, float* zone, float min, float max);

typedef void (* declareFun) (void* interface, float* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (const char* key, const char* value);

typedef struct {

    metaDeclareFun declare;

} MetaGlue;

#ifdef __cplusplus
}
#endif

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

#endif
