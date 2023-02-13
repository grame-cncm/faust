/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#import <UIKit/UIKit.h>

@class FIFlipsideViewController;

@protocol FIFlipsideViewControllerDelegate

- (void)flipsideViewControllerDidFinish:(FIFlipsideViewController *)controller;

@end

//@interface FIFlipsideViewController : UIViewController <UIAlertViewDelegate,UITextFieldDelegate>
@interface FIFlipsideViewController : UIViewController <UIAlertViewDelegate>
{
    IBOutlet UISlider*              _sampleRateSlider;
    IBOutlet UILabel*               _sampleRateLabel;
    IBOutlet UISlider*              _bufferSizeSlider;
    IBOutlet UILabel*               _bufferSizeLabel;
    IBOutlet UISwitch*              _openWidgetPanelSwitch;
    
    int                             _sampleRate;
    int                             _bufferSize;
    BOOL                            _openWidgetPanel;
    
    IBOutlet UITextField*   _oscIPOutput;
    NSString*               _oscIPOutputText;
    
    int                          _oscTransmit;
    IBOutlet UISegmentedControl* _oscTransmitState;
    
    IBOutlet UITextField*  _oscInputPort;
    NSString*              _oscInputPortText;
    
    IBOutlet UITextField*  _oscOutputPort;
    NSString*              _oscOutputPortText;
}

@property (assign, nonatomic) IBOutlet id <FIFlipsideViewControllerDelegate> delegate;
@property (nonatomic, nonatomic) int sampleRate;
@property (nonatomic, nonatomic) int bufferSize;
@property (nonatomic, nonatomic) BOOL openWidgetPanel;
@property (nonatomic, nonatomic) int oscTransmit;

- (IBAction)done:(id)sender;
- (IBAction)sampleRateSliderMoved:(id)sender;
- (IBAction)bufferSizeSliderMoved:(id)sender;
- (IBAction)openWidgetPanelSwitchMoved:(id)sender;
- (IBAction)deleteAssignationsButtonClicked:(id)sender;

- (int)sampleRateToSliderValue:(int)sampleRate;
- (int)sliderValueToSampleRate:(int)sliderValue;
- (int)bufferSizeToSliderValue:(int)bufferSize;
- (int)sliderValueToBufferSize:(int)sliderValue;

- (void)disableAudioWidgets;
- (void)enableAudioWidgets;

@end
