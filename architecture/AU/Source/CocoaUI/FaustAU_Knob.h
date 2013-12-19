//  Based on Paolo Boschini's FlatKnob.

#import <Cocoa/Cocoa.h>

static const int INSETS = 10;
static const int CONTROL_POINT_DIAMETER = 12;

@protocol FaustAU_KnobProtocol <NSObject>
- (void)knobUpdatedWithIndex:(int)index withValue:(double)value withObject:(id)knob;

@end

/**********************************************************************************/

@interface FaustAU_ControlPoint : NSView {
    float currentDraggedAngle;
    int currentAngle;
    int mouseDownPosition;
    float previousValue;
    int insets;
    int controlPointDiameter;
    NSColor *controlPointColor;
    
@public
    float value;
    
    NSArray *data;
    id <FaustAU_KnobProtocol> delegate;
}

- (id)initWithFrame:(NSRect)frame withInsets:(int)insets
    withControlPointDiameter:(int)controlPointDiameter
    withControlPointColor:(NSColor*)controlPointColor
    withCurrentAngle:(int)_currentAngle;


@end


/**********************************************************************************/


@interface FaustAU_FlatKnob : NSView {
    int insets;
    NSColor *backgroundColor;
    NSColor *knobColor;
@public
    int control;
    FaustAU_ControlPoint *controlPoint;
}

- (id)initWithFrame:(NSRect)frame
        withInsets:(int)insets
        withControlPointDiameter:(int)controlPointDiameter
        withControlPointColor:(NSColor*)controlPointColor
        withKnobColor:(NSColor*)knobColor
        withBackgroundColor:(NSColor*)backgroundColor
        withCurrentAngle:(int)currentAngle;
@end


/**********************************************************************************/


@interface FaustAU_Knob : FaustAU_FlatKnob
{
    NSTextField* _labelTextField;
    NSTextField* _valueTextField;
}

- (double)doubleValue;
- (void)setDoubleValue:(double)aDouble;

@property (nonatomic, strong) NSTextField* labelTextField;
@property (nonatomic, strong) NSTextField* valueTextField;


@end



