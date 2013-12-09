//
//  FaustAU_Button.h
//  FaustAU
//
//  Created by Reza Payami on 11/29/13.
//
//

#import <Foundation/Foundation.h>

#include "FaustAU.h"

@protocol FaustAU_ButtonProtocol <NSObject>
- (void)buttonPushed:(id)sender;
@end


@interface FaustAU_Button : NSButton
{
@public
    bool buttonState;
    id <FaustAU_ButtonProtocol> delegate;
}

- (FaustAU_Button*)init :(NSRect) frame :(auButton*)fButton :(int)controlId;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
@end