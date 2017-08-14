
#include "FaustAU_CustomView.h"
#include "FaustAU.h"

@implementation FaustAU_CustomView

// This listener responds to parameter changes, gestures, and property notifications
void eventListenerDispatcher (void *inRefCon, void *inObject, const AudioUnitEvent *inEvent, UInt64 inHostTime, Float32 inValue)
{
	FaustAU_CustomView *SELF = (FaustAU_CustomView *)inRefCon;
	[SELF eventListener:inObject event: inEvent value: inValue];
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

- (void)addListeners
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
                        i,
                        kAudioUnitScope_Global,
                        0 // mElement
                    };
                    auEvent.mArgument.mParameter = parameter;
                    addParamListener (mAUEventListener, self, &auEvent);                }
            }
        
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

- (void)removeListeners
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
                                                  (AudioUnitPropertyID)kAudioUnitCustomProperty_dspUI,
                                                  kAudioUnitScope_Global,
                                                  (AudioUnitElement)0, //inElement
                                                  (void*)&dspUI,
                                                  &dataSize);
    return dspUI;
}

/*
 - (BOOL)isFlipped {
     return YES;
 }
*/

- (void)dealloc
{
     [self unsetTimer];
     [self removeListeners];
     [[NSNotificationCenter defaultCenter] removeObserver: self];
     [super dealloc];
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
    
    [button setTitle:[[NSString alloc] initWithCString:fButton->fLabel.c_str() encoding:NSUTF8StringEncoding]];
    
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
    
    textField = [[NSTextField alloc] initWithFrame:NSMakeRect(origin.x, origin.y + 2 , width, height)];
    
    [textField setBezeled:NO];
    [textField setDrawsBackground:NO];
    [textField setEditable:NO];
    [textField setSelectable:NO];
    [textField setIdentifier: @"200"]; //TODO
    [textField setStringValue:[[NSString alloc] initWithCString:label encoding:NSUTF8StringEncoding]];
    
    [nsBox addSubview:textField];
    
    return textField;
}

- (FaustAU_Slider*)addSlider:(NSBox*) nsBox :(auSlider*)fSlider :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    int labelWidth = 0;
    
    NSTextField* labelTextField = NULL;
    
    if (strcmp(fSlider->fLabel.c_str(), "")) {
        labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
        [labelTextField setAlignment: NSRightTextAlignment];
        labelWidth = 100;
    }
    
    int width;
    int height;
    float value;
    
    if (fSlider->fIsVertical) {
        width = 15;
        height = 100;
    } else {
        width = 300;
        height = 45;
    }
    
    FaustAU_Slider* slider;
    slider = [[FaustAU_Slider alloc] initWithFrame:NSMakeRect(origin.x + labelWidth, origin.y, width, height)];
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
    org.x = origin.x + labelWidth + width - 12;
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+labelWidth+100)
            size.width = width+labelWidth+100;
    }
    else
    {
        origin.x += width+labelWidth+100;
        size.width += width+labelWidth+100;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField;
    
    if (labelTextField)
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
    NSTextField* labelTextField;
    int labelWidth = 0;
    
    if (strcmp(fSlider->fLabel.c_str(), "")) {
        labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
        [labelTextField setAlignment: NSRightTextAlignment];
        labelWidth = 100;
    }
    
    labelTextField = [self addTextField :nsBox :fSlider->fLabel.c_str() :200 :origin :isVerticalBox];
    [labelTextField setAlignment: NSRightTextAlignment];
    
    int width = 50;
    int height = 50;
    float value;
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    int initAngle =  225.0 - 270.0 * (value - fSlider->fMin) / (fSlider->fMax - fSlider->fMin);
    
    FaustAU_Knob *knob = [[FaustAU_Knob alloc] initWithFrame:NSMakeRect(origin.x + labelWidth, origin.y, width, height)
                                                  withInsets:10
                                    withControlPointDiameter:2
                                       withControlPointColor:[NSColor darkGrayColor]
                                               withKnobColor:[NSColor whiteColor]
                                         withBackgroundColor:[NSColor clearColor]
                                            withCurrentAngle:initAngle];
    
    
    knob->control = controlId;
    knob->controlPoint->delegate = self;
    knob->controlPoint->data = [self generateArrayFrom:fSlider->fMin to:fSlider->fMax step:fSlider->fStep]; //TODO step
    
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [knob setIdentifier: identifier];
    
    [nsBox addSubview:knob];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    char valueString[100];
    sprintf(valueString, "%9.2f", value);
    
    NSPoint org;
    org.x = origin.x + labelWidth + 28;
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+labelWidth + 30)
            size.width = width+labelWidth + 30;
    }
    else
    {
        origin.x += width+labelWidth + 30;
        size.width += width + labelWidth + 30;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField;
    
    if (labelTextField)
        [knob setLabelTextField: labelTextField];
    
    [knob setValueTextField: valueTextField];
    return knob;
}

- (FaustAU_Bargraph*)addBargraph:(NSBox*) nsBox :(auBargraph*)fBargraph :(int)controlId :(NSPoint&) origin :(NSSize&) size :(bool)isVerticalBox
{
    NSTextField* labelTextField = NULL;
    int labelWidth = 0;
    
    if (strcmp(fBargraph->fLabel.c_str(), "")) {
        labelTextField = [self addTextField :nsBox :fBargraph->fLabel.c_str() :200 :origin :isVerticalBox];
        [labelTextField setAlignment: NSRightTextAlignment];
        labelWidth = 100;
    }
    
    int width;
    int height;
    float value;
    
    if (fBargraph->fIsVertical) {
        width = 35;
        height = 100;
    } else {
        width = 300;
        height = 55;
    }
    
    FaustAU_Bargraph* bargraph;
    bargraph = [[FaustAU_Bargraph alloc] initWithFrame:NSMakeRect(origin.x + labelWidth, origin.y, width, height)];
    [bargraph setMinValue:fBargraph->fMin];
    [bargraph setMaxValue:fBargraph->fMax];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    [bargraph setDoubleValue:value];
    
    //TODO [barGraph setNumberOfTickMarks: (fBargraph->fMax - fBargraph->fMin) / fBargraph->fStep];
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId];
    [bargraph setIdentifier: identifier];
    
    [bargraph setContinuous:YES];
    
    [bargraph setAction:@selector(paramChanged:)];
    [bargraph setTarget:self];
    
    [nsBox addSubview:bargraph];
    
    AudioUnitGetParameter(mAU, controlId, kAudioUnitScope_Global, 0, &value);
    char valueString[100];
    sprintf(valueString, "%9.2f", value);
    
    NSPoint org;
    org.x = origin.x + labelWidth + width - 12;
    org.y = origin.y;
    NSTextField* valueTextField = [self addTextField :nsBox :valueString :-1 :org :isVerticalBox];
    [valueTextField setAlignment: NSLeftTextAlignment];
    
    if (isVerticalBox)
    {
        origin.y += height;
        size.height += height;
        if (size.width < width+labelWidth+100)
            size.width = width+labelWidth+100;
    }
    else
    {
        origin.x += width+labelWidth+100;
        size.width += width+labelWidth+100;
        if (size.height < height)
            size.height = height;
    }
    
    paramValues[controlId] = valueTextField;
    
    if (labelTextField)
        [bargraph setLabelTextField: labelTextField];
    
    [bargraph setValueTextField: valueTextField];
    
    return bargraph;
}

- (NSBox*)addBox:(NSBox*) nsParentBox :(auBox*)fThisBox :(NSPoint&) parentBoxOrigin :(NSSize&) parentBoxSize :(bool)isParentVerticalBox {
    
    auUIObject* childUIObject;
    
    NSBox* nsThisBox = [[NSBox alloc] init];
    NSPoint thisBoxOrigin;
    NSSize thisBoxSize;
    
    thisBoxOrigin.x = thisBoxOrigin.y = 0;
    thisBoxSize.width = thisBoxSize.height = 0;
    
    [nsThisBox setTitle:[[NSString alloc] initWithCString:fThisBox->fLabel.c_str() encoding:NSUTF8StringEncoding]];
    
    auUI* dspUI = [self dspUI];
    
    int controlId;
    NSView* childView = NULL;
    
    bool hasChildView = false;
    
      for (int i = 0; i < fThisBox->fChildren.size(); i++) {
        if (fThisBox->fIsVertical)
            childUIObject = fThisBox->fChildren[fThisBox->fChildren.size() - i - 1]; //not isFlipped
        else
            childUIObject = fThisBox->fChildren[i];

        for (int j = 0; j < dspUI->fUITable.size(); j++)
        {
            if (dspUI->fUITable[j] == childUIObject)
                controlId = j;
        }
        
        if (dynamic_cast<auBox*>(childUIObject)) {
            [self addBox :nsThisBox :(auBox*)childUIObject :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
        }
        else
        {
            if (dynamic_cast<auButton*>(childUIObject)) {
                childView = [self addButton :nsThisBox :(auButton*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
            }
            else if (dynamic_cast<auCheckButton*>(childUIObject)) {
                childView = [self addCheckButton :nsThisBox :(auCheckButton*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
            }
            
            else if (dynamic_cast<auSlider*>(childUIObject)) {
                if (dspUI->isKnob(childUIObject->fZone)) { //isKnob
                    childView = [self addKnob :nsThisBox :(auSlider*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
                }
                else {
                    childView = [self addSlider :nsThisBox :(auSlider*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
                }
                 
            }
            else if (dynamic_cast<auBargraph*>(childUIObject)) {
                childView = [self addBargraph :nsThisBox :(auBargraph*)childUIObject :controlId :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical];
            }
            
            hasChildView = true;
            
            if (childView)
                viewMap[controlId] = childView;
        }
    }
    
    /* if (hasChildView)
     {
     
     auButton showHideAUButton(fThisBox->fLabel.c_str(), NULL);
     
     NSButton* showHideButton = [self addButton :nsThisBox :&showHideAUButton :-100 :thisBoxOrigin :thisBoxSize :fThisBox->fIsVertical]; //TODO -100
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
    frame.size.width  = thisBoxSize.width + 25;
    frame.size.height = thisBoxSize.height + 25;
    [nsThisBox setFrame:frame];
    
    [nsThisBox setNeedsDisplay:YES];
    
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
        parentBoxSize.width += thisBoxSize.width + 25;

        if (parentBoxSize.height < thisBoxSize.height)
            parentBoxSize.height = thisBoxSize.height;
        parentBoxOrigin.y = 0;
    }
    
    return nsThisBox;
}

-(void)repaint
{
    auUI* dspUI = [self dspUI];
    NSRect frame;
    
    NSPoint origin;
    origin.x = origin.y = 0;
    
    NSSize size;
    size.width = size.height = 0;
    
    NSBox* nsCustomViewBox = [[NSBox alloc] init];
    [nsCustomViewBox setTitle:@"FaustAU CustomView"];
    [self addBox :nsCustomViewBox :dspUI->boundingBox :origin :size :true];
    
    frame.origin.x  = 0;
    frame.origin.y = 0;
    frame.size.width  = size.width + 25;
    frame.size.height = size.height + 25;
    [nsCustomViewBox setFrame:frame];
    [nsCustomViewBox setNeedsDisplay:YES];
    [self addSubview:nsCustomViewBox];
    
    //xml button
    NSButton* button;
    NSRect monitorFrame = NSMakeRect(size.width - 32, 6, 55, 24);
    button = [[NSButton alloc] initWithFrame:monitorFrame ];
    [button setTitle:@"XML"];
    [button setButtonType:NSMomentaryPushInButton];
    [button setBezelStyle:NSRoundedBezelStyle];
    [button setTarget:self];
    [button setAction:@selector(xmlButtonPushed:)];
    [button setState:TRUE];
    [self addSubview:button];
    
    if (usesBargraphs)
    {
        NSRect monitorFrame = NSMakeRect(10, 10, 60, 15);
        button = [[NSButton alloc] initWithFrame:monitorFrame ];
        [button setTitle:@"MON"];
        [button setButtonType:NSSwitchButton];
        [button setBezelStyle:NSRoundedBezelStyle];
        [button setTarget:self];
        [button setAction:@selector(monitorButtonPushed:)];
        [button setState:TRUE];
        [self addSubview:button];
    }
    
    [self setFrame:frame];
    [self setNeedsDisplay:YES];
}

- (void)setAU:(AudioUnit)inAU
{
	if (mAU)
		[self removeListeners];
    
    mAU = inAU;
    [self addListeners];
    [self synchronizeUIWithParameterValues];
    
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
}

-(void)setTimer
{
    if (!timer)
    {
        timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(update) userInfo:nil repeats:YES];
    }
}

-(void)unsetTimer
{
    if (timer)
    {
        [timer invalidate];
        timer = nil;
    }
}

- (void)update
{
    [self synchronizeUIWithParameterValues];
    [self setNeedsDisplay:YES];
}

// Called upon a knob update
- (void)knobUpdatedWithIndex:(int)index
                   withValue:(double)value
                  withObject:(id)object
{
    [ (FaustAU_Knob*)object setDoubleValue :value ];
    int paramId = [[object identifier] intValue];
    ComponentResult result = AudioUnitSetParameter(mAU,
                                                   paramId, //AudioUnitParameterID
                                                   kAudioUnitScope_Global,
                                                   (AudioUnitElement)0, //inElement
                                                   value, //inValue
                                                   0); //inBufferOffsetInFrames
    
    NSString *string = [NSString stringWithFormat:@"%9.2f", value];
    [paramValues[paramId] setStringValue: string];
    
	AudioUnitParameter parameter = {mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, object, &parameter, (Float32)value, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
    
    [object setNeedsDisplay:TRUE];
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
 	AudioUnitParameter parameter = {mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, sender, &parameter, (Float32)state, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
}

- (void)xmlButtonPushed:(id)sender
{
    NSData *data;
    NSString* dataString;
    NSString *oldString, *newString;
    
    auUI* dspUI = [self dspUI];
    NSFileManager *filemgr = [NSFileManager defaultManager];
    
    NSString* path = [NSHomeDirectory() stringByAppendingString: @"/Library/Audio/Plug-Ins/Components/_FILENAME_.component/Contents/Resources/au-output.xml"];
    
    NSSavePanel *savePanel = [NSSavePanel savePanel];
    NSString *outputFileName = NULL;
    int result = [savePanel runModal];
    
    if (result == NSOKButton){
        outputFileName = [[savePanel URL] path];
    }
    
    data = [filemgr contentsAtPath: path ];
    
    dataString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    
    for (int i = 0; i < dspUI->fUITable.size(); i++)
    {
        if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
        {
            oldString = [NSString stringWithFormat:@"id=\"%i\"", i + 1];
            newString = [NSString stringWithFormat:@"id=\"%i\" value=\"%f\"", i + 1, *dspUI->fUITable[i]->fZone];
            
            dataString = [dataString stringByReplacingOccurrencesOfString: oldString withString:newString];
        }
    }
    
    data = [dataString dataUsingEncoding:NSUTF8StringEncoding];
    [filemgr createFileAtPath: outputFileName contents: data attributes: nil];
}

- (void)monitorButtonPushed:(id)sender
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
    
    NSString *string = [NSString stringWithFormat:@"%9.2f", value];
    [paramValues[paramId] setStringValue: string];
    
	AudioUnitParameter parameter = { mAU,
        paramId, //paramId
        kAudioUnitScope_Global,
        0 }; //mElement
	
	NSAssert(	AUParameterSet(mAUEventListener, sender, &parameter, (Float32)value, 0) == noErr,
             @"[FaustAU_CustomView paramChanged:] AUParameterSet()");
}

- (void)synchronizeUIWithParameterValues
{
    auUI* dspUI = [self dspUI];
    
    NSView* subView = NULL;
    int paramId;
    Float32 value;
    
    for (int i = 0; i < dspUI->fUITable.size(); i++)
    {
        if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
        {
            subView = viewMap[i]; //TODO can be used for other cases
            
            if (subView)
            {
                if (dynamic_cast<auBargraph*>(dspUI->fUITable[i])) {
                    value = *(dspUI->fUITable[i]->fZone);
                    [subView setDoubleValue:value];
                }
            }
        }
    }
}

- (void)eventListener:(void *) inObject event:(const AudioUnitEvent *)inEvent value:(Float32)inValue
{}

@end
