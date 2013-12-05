
#import "FaustAU_CustomView.h"

#include "FaustAU.h"


@implementation FaustAU_CustomView


// This listener responds to parameter changes, gestures, and property notifications
void eventListenerDispatcher (void *inRefCon, void *inObject, const AudioUnitEvent *inEvent, UInt64 inHostTime, Float32 inValue)
{
	FaustAU_CustomView *SELF = (FaustAU_CustomView *)inRefCon;
	[SELF priv_eventListener:inObject event: inEvent value: inValue];
}

void addParamListener (AUEventListenerRef listener, void* refCon, AudioUnitEvent *inEvent)
{
	inEvent->mEventType = kAudioUnitEvent_BeginParameterChangeGesture;
	verify_noerr ( AUEventListenerAddEventType(	listener, refCon, inEvent));
	
	inEvent->mEventType = kAudioUnitEvent_EndParameterChangeGesture;
	verify_noerr ( AUEventListenerAddEventType(	listener, refCon, inEvent));
	
	inEvent->mEventType = kAudioUnitEvent_ParameterValueChange;
	verify_noerr ( AUEventListenerAddEventType(	listener, refCon, inEvent));
}

- (void)priv_addListeners
{
    auUI* dspUI;
    
    if (mAU) {
		verify_noerr( AUEventListenerCreate(eventListenerDispatcher, self,
											CFRunLoopGetCurrent(), kCFRunLoopDefaultMode, 0.05, 0.05,
											&mAUEventListener));
		
        dspUI = [self dspUI];
        
		//add listeners
        AudioUnitEvent auEvent;
        for (int i = 0; i < dspUI->fUITable.size(); i++)
            if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
            {
                if (dynamic_cast<auButton*>(dspUI->fUITable[i])) {
                }
                else if (dynamic_cast<auToggleButton*>(dspUI->fUITable[i])) {
                }
                else if (dynamic_cast<auCheckButton*>(dspUI->fUITable[i])) {
                }
                else {
                    AudioUnitParameter parameter =
                    {
                        mAU,
                        i, //TODO 0 -> inParamID
                        kAudioUnitScope_Global,
                        0 // mElement
                    };
                    auEvent.mArgument.mParameter = parameter;
                    addParamListener (mAUEventListener, self, &auEvent);                }
            }
        
		//auEvent.mArgument.mParameter.mParameterID = kFilterParam_Resonance;
		//addParamListener (mAUEventListener, self, &auEvent);
		
		/* Add a listener for the changes in our custom property */
		/* The Audio unit will send a property change when the unit is intialized */
		auEvent.mEventType = kAudioUnitEvent_PropertyChange;
		auEvent.mArgument.mProperty.mAudioUnit = mAU;
		auEvent.mArgument.mProperty.mPropertyID = kAudioUnitCustomProperty_dspUI;
		auEvent.mArgument.mProperty.mScope = kAudioUnitScope_Global;
		auEvent.mArgument.mProperty.mElement = 0;
		verify_noerr (AUEventListenerAddEventType (mAUEventListener, self, &auEvent));
	}
	
}

- (void)priv_removeListeners
{
	if (mAUEventListener) verify_noerr (AUListenerDispose(mAUEventListener));
	mAUEventListener = NULL;
	mAU = NULL;
}

- (auUI*) dspUI
{
    auUI* dspUI;
    
    UInt32 dataSize = sizeof(auUI*);
    
    ComponentResult result = AudioUnitGetProperty(mAU,
                                                  (AudioUnitPropertyID)kAudioUnitCustomProperty_dspUI, //TODO
                                                  kAudioUnitScope_Global,
                                                  (AudioUnitElement)0, //inElement
                                                  (void*)&dspUI,
                                                  &dataSize);
    return dspUI;
}

- (NSButton*)addButton:(NSBox*) nsBox :(auButton*)fButton :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    int width = 100;
    int height = 35;
    
    FaustAU_Button* button = [[FaustAU_Button alloc] init :NSMakeRect(origin.x, origin.y, width, height) :fButton :controlId];
    
    button->delegate = self;
    
    [nsBox addSubview:button];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width)
            size.width = width;
    }
    else
    {
        origin.x += width;
        size.width += width;
        if (size.height < height)
            size.height = height;
    }
    
    return button;
    
}

- (NSButton*)addCheckButton:(NSBox*) nsBox :(auCheckButton*)fButton :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    int width = 100;
    int height = 35;
    
    NSRect frame = NSMakeRect(origin.x, origin.y, width, height);
    
    NSButton* button = [[NSButton alloc] initWithFrame:frame ];
    
    [button setTitle:[[NSString alloc] initWithCString:fButton->fLabel.c_str() encoding:NSUTF8StringEncoding]]; //TODO
    
    [button setButtonType:NSSwitchButton];
    [button setBezelStyle:NSRoundedBezelStyle];
    
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [button setIdentifier: identifier];
    
    [button setTarget:self];
    [button setAction:@selector(paramChanged:)];
    
    [nsBox addSubview:button];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width)
            size.width = width;
    }
    else
    {
        origin.x += width;
        size.width += width;
        if (size.height < height)
            size.height = height;
    }
    
    return button;
    
}


- (NSTextField*)addTextField:(NSBox*) nsBox :(const char*)label :(int)controlId :(NSPoint&) origin :(bool)isVerticalBox
{
    int width = 100;
    int height = 35;
    
    NSTextField* textField;
    
    textField = [[NSTextField alloc] initWithFrame:NSMakeRect(origin.x, origin.y - 10 , width, height)]; //TODO + 10
    
    [textField setBezeled:NO];
    [textField setDrawsBackground:NO];
    [textField setEditable:NO];
    [textField setSelectable:NO];
    [textField setIdentifier: @"200"]; //TODO
    [textField setStringValue:[[NSString alloc] initWithCString:label encoding:NSUTF8StringEncoding]]; //TODO
    
    [nsBox addSubview:textField];
    
    
    return textField;
    
}


- (FaustAU_Slider*)addSlider:(NSBox*) nsBox :(auSlider*)fSlider :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    
    NSTextField* labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
    [labelTextField setAlignment: NSRightTextAlignment];
    
    int width;
    int height;
    float value;
    
    if (fSlider->fIsVertical) {
        width = 15;
        height = 100;
    }
    else{
        width = 300;
        height = 35;
    }
    
    
    FaustAU_Slider* slider;
    slider = [[FaustAU_Slider alloc] initWithFrame:NSMakeRect(origin.x + 100, origin.y, width, height)];
    [slider setMinValue:fSlider->fMin];
    [slider setMaxValue:fSlider->fMax];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    [slider setDoubleValue:value];
    
    //TODO [slider setNumberOfTickMarks: (fSlider->fMax - fSlider->fMin) / fSlider->fStep];
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [slider setIdentifier: identifier];
    
    [slider setContinuous:YES];
    
    [slider setAction:@selector(paramChanged:)];
    [slider setTarget:self];
    
    [nsBox addSubview:slider];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    char valueString[100];
    sprintf(valueString, "%9.2f", value);
    
    NSPoint org;
    org.x = origin.x + 100 + width - 10; //TODO -15
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+100+100)
            size.width = width+100+100;
    }
    else
    {
        origin.x += width+100+100;
        size.width += width+100+100;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField; //TODO
    
    [slider setLabelTextField: labelTextField];
    [slider setValueTextField: valueTextField];
    
    return slider;
    
}


- (NSArray*)generateArrayFrom:(float)start to:(float)stop step:(float)step
{
    NSMutableArray *a = [[NSMutableArray alloc] init];
    float v = start;
    
    while (v <= stop)
    {
        [a addObject:@(v)];
        v += step;
        
    }
    return a;
}


- (FaustAU_Knob*)addKnob:(NSBox*) nsBox :(auSlider*)fSlider :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    
    NSTextField* labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
    [labelTextField setAlignment: NSRightTextAlignment];
    
    int width = 50;
    int height = 50;
    float value;
    
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    
    int initAngle =  225.0 - 270.0 * (value - fSlider->fMin) / (fSlider->fMax - fSlider->fMin);
    
    FaustAU_Knob *knob = [[FaustAU_Knob alloc] initWithFrame:NSMakeRect(origin.x + 100, origin.y, width, height)
                                                  withInsets:10
                                    withControlPointDiameter:2
                                       withControlPointColor:[NSColor lightGrayColor]
                                               withKnobColor:[NSColor whiteColor]
                                         withBackgroundColor:[NSColor clearColor]
                                            withCurrentAngle:initAngle];
    
    
    knob->control = controlId;
    
    knob->controlPoint->delegate = self; //TODO
    
    knob->controlPoint->data = [self generateArrayFrom:fSlider->fMin to:fSlider->fMax step:fSlider->fStep]; //TODOOOOO not step?
    
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [knob setIdentifier: identifier];
    
    [nsBox addSubview:knob];
    
    
    //Value
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    char valueString[100];
    sprintf(valueString, "%9.2f", value);
    
    
    //origin.x += 300; //TODO
    NSPoint org;
    org.x = origin.x + 150;
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+100+100)
            size.width = width+100+100;
    }
    else
    {
        origin.x += width+100+100;
        size.width += width+100+100;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField; //TODO
    
    [knob setLabelTextField: labelTextField];
    [knob setValueTextField: valueTextField];
    
    return knob;
    
}


- (FaustAU_Slider*)addBargraph:(NSBox*) nsBox :(auBargraph*)fSlider :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    
    NSTextField* labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
    [labelTextField setAlignment: NSRightTextAlignment];
    
    int width;
    int height;
    float value;
    
    if (fSlider->fIsVertical) {
        width = 35;
        height = 100;
    }
    else{
        width = 300;
        height = 35;
    }
    
    
    FaustAU_Slider* slider;
    slider = [[FaustAU_Slider alloc] initWithFrame:NSMakeRect(origin.x + 100, origin.y, width, height)];
    [slider setMinValue:fSlider->fMin];
    [slider setMaxValue:fSlider->fMax];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    [slider setDoubleValue:value];
    
    //TODO [slider setNumberOfTickMarks: (fSlider->fMax - fSlider->fMin) / fSlider->fStep];
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [slider setIdentifier: identifier];
    
    [slider setContinuous:YES];
    
    [slider setAction:@selector(paramChanged:)];
    [slider setTarget:self];
    
    [nsBox addSubview:slider];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    char valueString[100];
    sprintf(valueString, "%9.2f", value);
    
    NSPoint org;
    org.x = origin.x + 100 + width - 10; //TODO -15
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+100+100)
            size.width = width+100+100;
    }
    else
    {
        origin.x += width+100+100;
        size.width += width+100+100;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField; //TODO
    
    [slider setLabelTextField: labelTextField];
    [slider setValueTextField: valueTextField];
    
    return slider;
}

- (NSBox*)addBox:(NSBox*) nsParentBox :(auBox*)fThisBox :(NSPoint&) parentBoxOrigin :(NSSize&) parentBoxSize :(bool)isParentVerticalBox {
    
    //parent-this-child
    
    auUIObject* childUIObject;
    
    NSBox* nsThisBox = [[NSBox alloc] init];
    NSPoint thisBoxOrigin;
    NSSize thisBoxSize;
    
    thisBoxOrigin.x = thisBoxOrigin.y = 0;
    thisBoxSize.width = thisBoxSize.height = 0;
    
    [nsThisBox setTitle:[[NSString alloc] initWithCString:fThisBox->fLabel.c_str() encoding:NSUTF8StringEncoding]];
    
    //TODO remove these lines
    auUI* dspUI = [self dspUI];
    
    int controlId;
    NSView* childView = NULL;
    
    bool hasChildView = false;
    
    for (int i = fThisBox->children.size() - 1; i >= 0; i--) {
        childUIObject = fThisBox->children[i];
        for (int j = 0; j < dspUI->fUITable.size(); j++)
        {
            if (dspUI->fUITable[j] == childUIObject)
                controlId = j;
        }
        
        if (dynamic_cast<auBox*>(childUIObject)) {
            [self addBox :nsThisBox :(auBox*)childUIObject :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
        }
        else
        {
            if (dynamic_cast<auButton*>(childUIObject)) {
                childView = [self addButton :nsThisBox :(auButton*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
            }
            else if (dynamic_cast<auCheckButton*>(childUIObject)) {
                childView = [self addCheckButton :nsThisBox :(auCheckButton*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
            }
            
            else if (dynamic_cast<auSlider*>(childUIObject)) {
                if (dspUI->knobSet.count(childUIObject->fZone)) { //isKnob
                    childView = [self addKnob :nsThisBox :(auSlider*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
                }
                else {
                    childView = [self addSlider :nsThisBox :(auSlider*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
                }
            }
            else if (dynamic_cast<auBargraph*>(childUIObject)) {
                childView = [self addBargraph :nsThisBox :(auBargraph*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->isVertical];
            }
            
            hasChildView = true;
            
            if (childView)
                viewMap[controlId] = childView;
            
        }
    }
    
    /* if (hasChildView)
     {
     
     auButton showHideAUButton(fThisBox->fLabel.c_str(), NULL);
     
     NSButton* showHideButton = [self addButton :nsThisBox :&showHideAUButton :-100 :thisBoxOrigin :thisBoxSize :fThisBox->isVertical]; //TODO -100
     /*
     
     // NSButton* showHideBtton = [[NSButton alloc] initWithFrame:NSMakeRect(0 //*thisBoxOrigin.x//, frame.size.//height - 30,  35, 70 )];
     
     [showHideButton setTarget:self];
     [showHideButton setAction:@selector(showHide:)];
     
     [nsThisBox addSubview:showHideButton];
     showHideMap[showHideButton] = nsThisBox;
     }*/
    
    
    NSRect frame;
    frame.origin.x = parentBoxOrigin.x;
    frame.origin.y = parentBoxOrigin.y;
    frame.size.width  = thisBoxSize.width + 25; //TODO
    frame.size.height = thisBoxSize.height + 25; //TODO
    [nsThisBox setFrame:frame];
    
    [nsThisBox setNeedsDisplay:YES]; //TODO
    
    
    [nsParentBox addSubview:nsThisBox];
    
    if (isParentVerticalBox)
    {
        parentBoxOrigin.x = 0;
        parentBoxOrigin.y += thisBoxSize.height + 25;
        
        parentBoxSize.height += thisBoxSize.height + 25;
        if (parentBoxSize.width < thisBoxSize.width)
            parentBoxSize.width = thisBoxSize.width;
    }
    else
    {
        parentBoxOrigin.x += thisBoxSize.width + 25;
        if (parentBoxSize.height < thisBoxSize.height)
            parentBoxSize.height = thisBoxSize.height;
        parentBoxOrigin.y = 0;
    }
    
    return nsThisBox;
    
}

-(void)repaint
{
    auUI* dspUI = [self dspUI];
    
    //[self remove]
    
    NSPoint origin;
    origin.x = origin.y = 0;
    NSSize size;
    NSBox* nsBoundingBox = [[NSBox alloc] init];
    
    [nsBoundingBox setTitle:@"FaustAU CustomView"];
    
    [self addBox :nsBoundingBox :dspUI->boundingBox :origin :size :true];
    NSRect frame;
    frame.size.width  = size.width + 25; //TODO
    frame.size.height = size.height + 25; //TODO
    [nsBoundingBox setFrame:frame];
    [nsBoundingBox setNeedsDisplay:YES]; //TODO
    
    [self addSubview:nsBoundingBox];
    
    //TODO
    if (usesBargraphs)
    {
        
        int width = 80;
        int height = 15;
        
        NSRect monitorFrame = NSMakeRect(0, 0, width, height);
        
        NSButton* button = [[NSButton alloc] initWithFrame:monitorFrame ];
        
        [button setTitle:@"MON"]; //TODO
        [button setButtonType:NSSwitchButton];
        [button setBezelStyle:NSRoundedBezelStyle];
        [button setTarget:self];
        [button setAction:@selector(monitorPushed:)];
        [button setState:TRUE];
        [self addSubview:button];
    }
    
    [self setFrame:frame];
    [self setNeedsDisplay:YES]; //TODO
}

- (void)setAU:(AudioUnit)inAU {
	
    mAU = inAU;
    [self priv_addListeners];
    [self priv_synchronizeUIWithParameterValues];
    
    auUI* dspUI = [self dspUI];
    
    usesBargraphs = false;
    for (int i = 0; i < dspUI->fUITable.size(); i++)
    {
        if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
        {
            if (dynamic_cast<auBargraph*>(dspUI->fUITable[i]))
                usesBargraphs = true;
            break;
        }
    }
    
    if (usesBargraphs)
    {
        monitor = true;
        [self setTimer];
    }
    
    [self repaint];

    //TODO only if there is bargraph
    
}

-(void) setTimer
{
    if (!timer)
    {
        timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(redraw) userInfo:nil repeats:YES];
    }
}

-(void) unsetTimer
{
    if (timer)
    {
        [timer invalidate];
        timer = nil;
    }
}

- (void)redraw //TODO rename
{
    [self priv_synchronizeUIWithParameterValues];
    
    [self setNeedsDisplay:YES]; //TODO
}

// Called upon a knob update
- (void)knobUpdatedWithIndex:(int)index
                   withValue:(double)value
                  withObject:(id)object
{
    [ (FaustAU_Knob*)object setDoubleValue :value ];//TODO??????????
    
    
    int paramId = [[object identifier] intValue];
    
    ComponentResult result = AudioUnitSetParameter(mAU,
                                                   paramId, //AudioUnitParameterID
                                                   kAudioUnitScope_Global,
                                                   (AudioUnitElement)0, //inElement
                                                   value, //inValue
                                                   0); //inBufferOffsetInFrames
    
    NSString *myString = [NSString stringWithFormat:@"%9.2f", value];
    [paramValues[paramId] setStringValue: myString]; //TODO
    
	AudioUnitParameter parameter = {mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, object, &parameter, (Float32)value, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
    
    
    [object setNeedsDisplay:TRUE]; //TODO
}


- (void)showHide:(id)sender
{
   	
    int intValue = [sender intValue];
    
    if (intValue)
    {
        [sender setTitle: @"-"];
        [sender setIntValue: 1];
        
        NSBox* box = showHideMap[sender];
        
        [box setHidden:FALSE];
        [box setNeedsDisplay:YES];
    }
    else
    {
        [sender setTitle: @"+"];
        [sender setIntValue: 0];
        
        NSBox* box = showHideMap[sender];
        
        [box setHidden:TRUE];
        [box setNeedsDisplay:YES];
    }
    
    //[self repaint];
}


- (void)buttonPushed:(id)sender
{
    int state =  ((FaustAU_Button*)sender)->buttonState;
    int paramId = [[sender identifier] intValue];
    
    ComponentResult result = AudioUnitSetParameter(mAU,
                                                   paramId, //AudioUnitParameterID
                                                   kAudioUnitScope_Global,
                                                   (AudioUnitElement)0, //inElement
                                                   state, //inValue
                                                   0); //inBufferOffsetInFrames
    
    NSString *myString = [NSString stringWithFormat:@"%i", state];
    
	AudioUnitParameter parameter = {mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, sender, &parameter, (Float32)state, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
    
}

//TODO
- (void)viewDidHide
{
    [self unsetTimer];
}


- (void)monitorPushed:(id)sender
{
    monitor = [(NSButton*)sender state];
    
    if (monitor)
        [self setTimer];
    else
        [self unsetTimer];
}

- (void)paramChanged:(id)sender
{
   	
    float value =  [sender doubleValue]; //TODO
    int paramId = [[sender identifier] intValue];
    
    ComponentResult result = AudioUnitSetParameter(mAU,
                                                   paramId, //AudioUnitParameterID
                                                   kAudioUnitScope_Global,
                                                   (AudioUnitElement)0, //inElement
                                                   value, //inValue
                                                   0); //inBufferOffsetInFrames
    
    NSString *myString = [NSString stringWithFormat:@"%9.2f", value];
    [paramValues[paramId] setStringValue: myString]; //TODO
    
	AudioUnitParameter parameter = {mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, sender, &parameter, (Float32)value, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
    
    //if (dynamic_cast<auSlider*>(dspUI->fUITable[i])
    
    
    // [NSObject cancelPreviousPerformRequestsWithTarget: self
    //                                        selector: @selector(finishTrack) object: nil ];
    // [self performSelector: @selector(finishTrack) withObject: nil
    //        afterDelay: 0.0];
    
    
    //SEL sel = @selector( sliderDone: );
    //[NSObject cancelPreviousPerformRequestsWithTarget: self selector:
    // sel object: sender];
    //[self performSelector: sel withObject: sender afterDelay: 0.0];
    
}


- (void)priv_synchronizeUIWithParameterValues {
    auUI* dspUI = [self dspUI];
    
    NSView* subView = NULL;
    int paramId;
    Float32 value;
    
    
    for (int i = 0; i < dspUI->fUITable.size(); i++)
    {
        if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
        {
            
            subView = viewMap[i]; //TODO use these in other places
            //subView = getView(dspUI->, dspUI->fUITable, i);
            
            if (subView)
            {
                //TODOOOOOOOO remove first if?
                if (dynamic_cast<auSlider*>(dspUI->fUITable[i])
                    || (dynamic_cast<auBargraph*>(dspUI->fUITable[i]))
                    ) {
                    
                    value = *(dspUI->fUITable[i]->fZone);
                    //AudioUnitGetParameter(mAU, i, kAudioUnitScope_Global, 0, &value);//TODO
                    
                    //TODO
                    [subView setDoubleValue:value]; //TODO
                    //[(NSSlider*)subView setDoubleValue:k]; //TODO
                    
                }
            }
        }
    }
    
    //TODO[self updateCurve];
    
}



#pragma mark ____ LISTENER CALLBACK DISPATCHEE ____
// Handle kAudioUnitProperty_PresentPreset event

- (void)priv_eventListener:(void *) inObject event:(const AudioUnitEvent *)inEvent value:(Float32)inValue {
    
    /*    switch (inEvent->mEventType) {
     case kAudioUnitEvent_ParameterValueChange:
     
     
     //  [self priv_synchronizeUIWithParameterValues]; //TODO
     
     
     // Parameter Changes
     
     auUI* dspUI;
     
     UInt32 dataSize = sizeof(auUI*);
     
     ComponentResult result = AudioUnitGetProperty(mAU,
     (AudioUnitPropertyID)kAudioUnitCustomProperty_dspUI, //TODO
     kAudioUnitScope_Global,
     (AudioUnitElement)0, //inElement
     (void*)&dspUI,
     &dataSize);
     
     NSView* subView = NULL;
     int paramId;
     Float32 value;
     
     
     for (int i = 0; i < dspUI->fUITable.size(); i++)
     {
     if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
     {
     
     for (subView in self.subviews)
     {
     paramId = [[subView identifier] intValue];
     if (paramId == inEvent->mArgument.mParameter.mParameterID)
     break;
     }
     
     if (subView)
     {
     if (dynamic_cast<auSlider*>(dspUI->fUITable[i])
     || dynamic_cast<auHorizontalBargraph*>(dspUI->fUITable[i])
     || dynamic_cast<auVerticalBargraph*>(dspUI->fUITable[i])
     ) {
     
     value = *(dspUI->fUITable[i]->fZone);
     AudioUnitGetParameter(mAU, paramId, kAudioUnitScope_Global, 0, &value);
     
     [(NSSlider*)subView setDoubleValue:value]; //TODO
     }
     }
     }
     }
     
     }*/
    
    
    // get the curve data from the audio unit
    /*
     case kAudioUnitEvent_BeginParameterChangeGesture:			// Begin gesture
     [graphView handleBeginGesture];							// notify graph view to update visual state
     break;
     case kAudioUnitEvent_EndParameterChangeGesture:				// End gesture
     [graphView handleEndGesture];							// notify graph view to update visual state
     break;
     */
    
    /*
     
     case kAudioUnitEvent_PropertyChange:						// custom property changed
     if (inEvent->mArgument.mProperty.mPropertyID == kAudioUnitCustomProperty_FilterFrequencyResponse)
     [self updateCurve];
     break;
     */
}



/*
 - (BOOL)isFlipped
 {
 return YES;
 }*/

- (void)removeFromSuperview
{
    //  [self unsetTimer];
}


- (void)dealloc {
    /*
     [self unsetTimer];
     
     
     [self priv_removeListeners];
     
     [[NSNotificationCenter defaultCenter] removeObserver: self];
     
     
     [super dealloc];*/
    
}


@end
