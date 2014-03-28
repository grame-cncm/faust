#import "FaustAU_Button.h"

@implementation FaustAU_Button

- (FaustAU_Button*)init :(NSRect)frame :(auButton*)fButton :(int)controlId {
    
    [self initWithFrame:frame];
    
    buttonState = 1;
    
    [self setTitle:[[NSString alloc] initWithCString:fButton->fLabel.c_str() encoding:NSUTF8StringEncoding]]; //TODO
    
    [self setButtonType:NSMomentaryPushInButton];
    [self setBezelStyle:NSRoundedBezelStyle];
    
    NSString *identifier = [NSString stringWithFormat:@"%d",controlId]; 
    [self setIdentifier: identifier];
    
    return self;
}

- (void)mouseDown:(NSEvent *)theEvent
{
    [self setNeedsDisplay:YES];
    buttonState = 0;
    [self setNeedsDisplay:TRUE];
    [delegate buttonPushed: self];
    
}

- (void)drawRect:(NSRect)rect {
    if (buttonState)
    {
        [[NSColor lightGrayColor] set];
    }
    else
    {
        [[NSColor darkGrayColor] set];
    }
    
    NSRectFill(rect);
    [super drawRect: rect];
}

- (void)mouseUp:(NSEvent *)theEvent
{
    buttonState = 1;
    [delegate buttonPushed: self];
    [self setNeedsDisplay:TRUE];
}
@end





