/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

// Definition of the standard size of the different elements

#define kKnobWidth 100
#define kKnobHeight 100

#define kVSliderWidth 80
#define kVSliderHeight 250

#define kHSliderWidth 350
#define kHSliderHeight 50

#define kButtonWidth 100
#define kButtonHeight 50

#define kCheckButtonWidth 60
#define kCheckButtonHeight 40

#define kMenuWidth 100
#define kMenuHeight 50

#define kRadioButtonWidth 100
#define kRadioButtonHeight 55

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kNumDisplayWidth 75
#define kNumDisplayHeight 50

#define kVBargraphWidth 60
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 50

#define kLedWidth 25
#define kLedHeight 25

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"
#include "faust/gui/ValueConverter.h"

/**
 * \brief       Custom LookAndFeel class.
 * \details     Define the appearance of all the JUCE widgets.
 */

struct CustomLookAndFeel : public LookAndFeel_V3
{
    void drawRoundThumb (Graphics& g, const float x, const float y,
                         const float diameter, const Colour& colour, float outlineThickness)
    {
        const Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;

        Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

        const DropShadow ds (Colours::black, 1, Point<int> (0, 0));
        ds.drawForPath (g, p);

        g.setColour (colour);
        g.fillPath (p);

        g.setColour (colour.brighter());
        g.strokePath (p, PathStrokeType (outlineThickness));
    }

    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();

        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            const float cornerSize = jmin (15.0f, jmin (width, height) * 0.45f);
            const float lineThickness = cornerSize * 0.1f;
            const float halfThickness = lineThickness * 0.5f;

            Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));

            const Colour outlineColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                        : TextButton::textColourOffId));

            g.setColour (baseColour);
            g.fillPath (outline);

            if (! button.getToggleState()) {
                g.setColour (outlineColour);
                g.strokePath (outline, PathStrokeType (lineThickness));
            }
        }
    }

    void drawTickBox (Graphics& g, Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        const float boxSize = w * 0.7f;

        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const Colour colour (component.findColour (TextButton::buttonColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));

        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked) {
            const Path tick (LookAndFeel_V2::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonOnColourId) : Colours::grey);

            const float scale = 9.0f;
            const AffineTransform trans (AffineTransform::scale (w / scale, h / scale)
                                         .translated (x - 2.5f, y + 1.0f));
            g.fillPath (tick, trans);
        }
    }

    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override
    {
        const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));

        if (style == Slider::LinearHorizontal || style == Slider::LinearVertical) {
            float kx, ky;

            if (style == Slider::LinearVertical) {
                kx = x + width * 0.5f;
                ky = sliderPos;
            } else {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }

            const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 2.0f,
                            knobColour, outlineThickness);
        } else {
            // Just call the base class for the demo
            LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        g.fillAll (slider.findColour (Slider::backgroundColourId));

        if (style == Slider::LinearBar || style == Slider::LinearBarVertical) {
            const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;

            Path p;

            if (style == Slider::LinearBarVertical)
                p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
            else
                p.addRectangle (fx, fy, sliderPos - fx, fh);


            Colour baseColour (slider.findColour (Slider::rotarySliderFillColourId)
                               .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                               .withMultipliedAlpha (0.8f));

            g.setColour (baseColour);
            g.fillPath (p);

            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        } else {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal()) {
            const float iy = y + height * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        } else {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillPath (off);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

//Background
        {
            g.setColour(Colours::lightgrey.withAlpha (isMouseOver ? 1.0f : 0.7f));
            Path intFilledArc;
            intFilledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.8);
            g.fillPath(intFilledArc);
        }

        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));

//Render knob value
        {
            Path pathArc;
            pathArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.8);
            g.fillPath(pathArc);

            Path cursor, cursorShadow;
            float rectWidth = radius*0.4;
            float rectHeight = rectWidth/2;
            float rectX = centreX + radius*0.9 - rectHeight/2;
            float rectY = centreY - rectWidth/2;

            cursor.addRectangle      (rectX,   rectY,   rectWidth,   rectHeight);
            cursorShadow.addRectangle(rectX-1, rectY-1, rectWidth+2, rectHeight+2);

            AffineTransform t = AffineTransform::translation(-rectWidth + 2, rectHeight/2);
            t = t.rotated((angle - float_Pi/2), centreX, centreY);

            cursor.applyTransform(t);
            cursorShadow.applyTransform(t);


            g.setColour(Colours::black);
            g.fillPath(cursor);

            g.setColour(Colours::black .withAlpha(0.15f));
            g.fillPath(cursorShadow);
        }
    }
};

/**
 * \brief   Different kind of slider available
 * \see     uiSlider
 */
enum SliderType {
    HSlider,    /*!< Horizontal Slider      */
    VSlider,    /*!< Vertical Slider        */
    NumEntry,   /*!< Numerical Entry Box    */
    Knob        /*!< Circular Slider        */
};

/**
 * \brief   Different kind of VU-meter available.
 */
enum VUMeterType {
    HVUMeter,   /*!< Horizontal VU-meter    */
    VVUMeter,   /*!< Vertical VU-meter      */
    Led,        /*!< LED VU-meter           */
    NumDisplay  /*!< Text Box VU_meter      */
};

/**
 * \brief   Intern class for all FAUST widgets.
 * \details Every active, passive or box widgets derive from this class.
 */
class uiBaseComponent: public Component
{
public:
    float fHRatio, fVRatio;
    int fTotalWidth, fTotalHeight; // Size with margins included (for a uiBox)
    int fDisplayRectHeight, fDisplayRectWidth;  // Size without margin, just the child dimensions
                                                // Sum on one dimension, max on the other
    String fName;
    
    /**
     * \brief   Constructor.
     * \details Initialize a uiBaseComponent with its name, and all its sizes.
     *
     * \param   totWidth    Minimal total width.
     * \param   totHeight   Minimal total Height.
     * \param   name        Name.
     */
    uiBaseComponent(int totWidth, int totHeight, String name) : fTotalWidth(totWidth), fTotalHeight(totHeight), fName(name) {
        fDisplayRectHeight = totHeight;
        fDisplayRectWidth  = totWidth;
    }
    
    /** Return the total height in pixels. */
    int getTotalHeight() {
        return fTotalHeight;
    }
    
    /** Return the total width in pixels. */
    int getTotalWidth() {
        return fTotalWidth;
    }
    
    /** Initialize both vertical and horizontal ratios. */
    virtual void setRatio() {
        setVRatio();
        setHRatio();
    }
    
    /** Return the horizontal ratio, between 0 and 1. */
    float getHRatio() {
        return fHRatio;
    }
    
    /** Return the vertical ratio, between 0 and 1. */
    float getVRatio() {
        return fVRatio;
    }
    
    /** Return the name. */
    String getName() {
        return fName;
    }
    
    /** Initialize the horizontal ratio. */
    void setHRatio() {
        // Avoid to set ratio for the "main box", which has no uiBaseComponent parent
        uiBaseComponent* tempParentBox = findParentComponentOfClass<uiBaseComponent>();
        if(tempParentBox != nullptr) {
            fHRatio = (float)fTotalWidth / (float)tempParentBox->fDisplayRectWidth;
        }
    }
    
    /** Initialize the vertical ratio. */
    void setVRatio() {
        // Avoid to set ratio for the "main box", which has no uiBaseComponent parent
        uiBaseComponent* tempParentBox = findParentComponentOfClass<uiBaseComponent>();
        if(tempParentBox != nullptr) {
            fVRatio = (float)fTotalHeight / (float)tempParentBox->fDisplayRectHeight;
        }
    }
    
    /**
     * \brief   Set the uiBaseComponent bounds.
     * \details Convert absolute bounds to relative bounds,
     *          used in JUCE Component mechanics.
     *
     * \param r The absolute bounds.
     *
     */
    void setBaseComponentSize(Rectangle<int> r) {
        setBounds(r.getX() - getParentComponent()->getX(),
                  r.getY() - getParentComponent()->getY(),
                  r.getWidth(),
                  r.getHeight());
    }
    
    /** Trigger on double click, write the debug output */
    void mouseDoubleClick(const MouseEvent &event) override {
        writeDebug();
    }

    /** Debug console output */
    virtual void writeDebug() = 0;
    /** Apply the LookAndFeel on the JUCE widget. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) = 0;
};

/**
 * \brief   Intern class for all FAUST active or passive widgets.
 * \details Every activ or passive widgets derive from this class.
 */
class uiComponent: public uiBaseComponent, public uiItem, public SettableTooltipClient
{
public:
    String fTooltipText;

    /**
     * \brief   Constructor.
     * \details Initialize all uiItem, uiBaseComponent and the tooltip variables.
     *
     * \param   gui     Current FAUST GUI.
     * \param   zone    Zone of the widget.
     * \param   w       Width of the widget.
     * \param   h       Height of the widget.
     * \param   tooltip Tooltip text.
     * \param   name    Name of the widget.
     */
    uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h, String tooltip, String name): uiBaseComponent(w, h, name), uiItem(gui,zone), fTooltipText(tooltip) { }

    /** Write some debug informations in the console, such as bounds, parent box, etc. */
    virtual void writeDebug() override {
        std::cout<<std::endl<<"Bounds of Component : {"<<getBounds().toString()<<"}";
        std::cout<<", for parent : "<<findParentComponentOfClass<uiBaseComponent>()->fName<<", ";
        std::cout<<getParentComponent()->getBounds().toString()<<std::endl;
        std::cout<<"Ratios : "<<fHRatio<<" "<<fVRatio<<", Recommended Size : "<<fTotalWidth<<"x"<<fTotalHeight<<std::endl;
        std::cout<<"fDisplayRectHeight : "<<fDisplayRectHeight<<", fDisplayRectWidth : "<<fDisplayRectWidth<<std::endl;
    }
};

/** 
 * \brief   Intern class for all kind of sliders.
 * \see     SliderType
 */
class uiSlider: public uiComponent,
    private juce::Slider::Listener
{
private:
    Slider::SliderStyle fStyle;
    Label fLabel;
    ScopedPointer<ValueConverter> fConverter;
    int x, y, width, height;
    SliderType fType;
    Slider fSlider;

public:
    /**
     * \brief   Constructor.
     * \details Initialize all uiComponent variables, and Slider specific ones.
     *          Initialize juce::Slider parameters.
     *
     * \param   gui, zone, w, h, tooltip, name  uiComponent variables.
     * \param   min                             Minimum value of the slider.
     * \param   max                             Maximum value of the slider.
     * \param   cur                             Initial value of the slider.
     * \param   step                            Step of the slider.
     * \param   unit                            Unit of the slider value.
     * \param   scale                           Scale of the slider, exponential, logarithmic, or linear.
     * \param   type                            Type of slider (see SliderType).
     */
    uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT cur, FAUSTFLOAT step, String name, String unit, String tooltip, MetaDataUI::Scale scale, SliderType type) : uiComponent(gui, zone, w, h, tooltip, name), fType(type)
    {
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(min, max, min, max);
            fSlider.setSkewFactor(0.5); // Logarithmic slider
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(min, max, min, max);
            fSlider.setSkewFactor(2.0); // Exponential slider
        } else {
            fConverter = new LinearValueConverter(min, max, min, max);
        }

        // Set the JUCE widget initalization variables.
        switch(fType) {
        case HSlider:
            fStyle = Slider::SliderStyle::LinearHorizontal;
            break;
        case VSlider:
            fStyle = Slider::SliderStyle::LinearVertical;
            fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
            break;
        case NumEntry:
            fSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_AutoDirection);
            fStyle = Slider::SliderStyle::IncDecButtons;
            break;
        case Knob:
            fStyle = Slider::SliderStyle::Rotary;
            fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
            break;

        default:
            break;
        }
        addAndMakeVisible(fSlider);

        // Slider settings
        fSlider.setBounds(getBounds());
        fSlider.setRange(min, max, step);
        fSlider.setValue(fConverter->faust2ui(cur));
        fSlider.addListener(this);
        fSlider.setSliderStyle(fStyle);
        fSlider.setTextValueSuffix(unit);
        if(fTooltipText.isNotEmpty()) {
            fSlider.setTooltip(fTooltipText);
        }

        // Label settings, only happens for a horizontal of numerical entry slider
        // because the method attachToComponent only give the choice to place the
        // slider name on centered top, which is what we want. It's done manually
        // the paint method.
        if(fType == HSlider || fType == NumEntry) {
            fLabel.setText(fName, dontSendNotification);
            fLabel.attachToComponent(&fSlider, true);
            addAndMakeVisible (fLabel);
            if(fTooltipText.isNotEmpty()) {
                fLabel.setTooltip(fTooltipText);
            }
        }
    }

    /** Draw the name of a vertical or circular slider. */
    virtual void paint(Graphics& g) override {
        if(fType == VSlider || fType == Knob) {
            g.setColour (Colours::black);
            g.drawText(fName, getLocalBounds(), Justification::centredTop);
        }
    }

    /** Allow to control the slider when its value is changed, but not by the user. */
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        fSlider.setValue(fConverter->faust2ui(v));
    }

    /** JUCE callback for a slider value change, give the value to the FAUST module. */
    void sliderValueChanged(Slider* slider) override
    {
        float value = slider->getValue();
        std::cout<<fName<<" : "<<value<<std::endl;
        modifyZone(value);
    }

    /** Apply the LookAndFeel to the juce::Slider widget. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) override {
        fSlider.setLookAndFeel(laf);
    }

    /** 
     * Set the good coordinates and size for the juce::Slider object depending 
     * on its SliderType, whenever the layout size changes.
     */
    virtual void resized() override {
        if       (fType == HSlider) {
            x = getLocalBounds().getX() + 60;
            y = getLocalBounds().getY();
            width = getLocalBounds().getWidth()-60;
            height = getLocalBounds().getHeight();
        } else if(fType == NumEntry) {
            width = kNumEntryWidth;
            height = kNumEntryHeight;
            // x position is the top left corner horizontal position of the box
            // and not the top left of the NumEntry label, so we have to do that
            x = (getLocalBounds().getWidth()-width)/2 + (Font().getStringWidth(fName)+5)/2;
            y = (getLocalBounds().getHeight()-height)/2;
        } else if(fType == VSlider) {
            x = getLocalBounds().getX();
            y = getLocalBounds().getY()+12; // 12 pixels for the name
            height = getLocalBounds().getHeight()-12;
            width = getLocalBounds().getWidth();
        } else if(fType == Knob) {
            // The knob name needs to be displayed, 12 pixels
            height = jmin(getLocalBounds().getHeight()-12, kKnobHeight);
            width = height;
            x = (getLocalBounds().getWidth() - width)/2;
            // 12 pixels for the knob name still
            y = jmax((getLocalBounds().getHeight() - height)/2, 12);
        }
        fSlider.setBounds(x, y, width, height);
    }
};

/** Intern class for button */
class uiButton: public uiComponent,
    private juce::Button::Listener
{
private:
    int x, y, width, height;
    TextButton fButton;

public:
    /**
     * \brief   Constructor.
     * \details Initialize all uiComponent variables and juce::TextButton parameters.
     *
     * \param   gui, zone, w, h, tooltip, label     uiComponent variable.
     */
    uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) :  uiComponent(gui, zone, w, h, tooltip, label), width(w), height(h)
    {
        width = kButtonWidth;
        height = kButtonHeight;
        x = getLocalBounds().getX();
        y = (getLocalBounds().getHeight()-height)/2;

        fButton.setButtonText(label);
        fButton.setBounds(x, y, width, height);
        fButton.addListener(this);
        if(fTooltipText.isNotEmpty()) {
            fButton.setTooltip(fTooltipText);
        }

        addAndMakeVisible(fButton);
    }

    /** 
     * Has to be defined because its a pure virtual function of juce::Button::Listener, 
     * which uiButton derives from. Control of user actions is done in buttonStateChanged.
     * \see buttonStateChanged
     */
    void buttonClicked (Button* button) override
    {
    }

    /** Indicate to the FAUST module when the button is pressed and released. */
    void buttonStateChanged (Button* button) override
    {
        if(button->isDown()) {
            modifyZone(1.0);
        }
        else {
            modifyZone(0.0);
        }
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }

    /** Apply the LookAndFeel to the juce::TextButton widget. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) override {
        fButton.setLookAndFeel(laf);
    }

    /** Set the good coordinates and size to the juce::TextButton widget whenever the layout size changes. */
    virtual void resized() override
    {
        x = getLocalBounds().getX();
        width = getLocalBounds().getWidth();
        height = jmin(getLocalBounds().getHeight(), kButtonHeight);
        y = (getLocalBounds().getHeight()-height)/2;
        fButton.setBounds(x, y, width, height);
    }
};

/** Intern class for checkButton */
class uiCheckButton: public uiComponent,
    private juce::Button::Listener
{
private:
    ToggleButton fCheckButton;

public:
    /**
     * \brief   Constructor.
     * \details Initialize all uiComponent variables and juce::ToggleButton parameters.
     *
     * \param   gui, zone, w, h, label, tooltip     uiComponent variables.
     */
    uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) : uiComponent(gui, zone, w, h, tooltip, label)
    {
        int x = getLocalBounds().getX();
        int y = (getLocalBounds().getHeight()-h)/2;
        
        if(fTooltipText.isNotEmpty()) {
            setTooltip(fTooltipText);
        }

        fCheckButton.setButtonText(label);
        fCheckButton.setBounds(x, y, w, h);
        fCheckButton.addListener(this);
        if(fTooltipText.isNotEmpty()) {
            fCheckButton.setTooltip(fTooltipText);
        }

        addAndMakeVisible(fCheckButton);
    }

    /** Indicate to the FAUST module when the button is toggled or not. */
    void buttonClicked(Button* button) override
    {
        std::cout<<fName<<" : "<<button->getToggleState()<<std::endl;
        modifyZone(button->getToggleState());
    }

    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }

    /** Apply the LookAndFeel to the juce::ToggleButton widget. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) override {
        fCheckButton.setLookAndFeel(laf);
    }

    /** Set the good coordinates and size to the juce::ToggleButton widget, whenever the layout size changes. */
    virtual void resized() override
    {
        fCheckButton.setBounds(getLocalBounds());
    }
};

/** Intern class for Menu */
class uiMenu: public uiComponent,
    private juce::ComboBox::Listener
{
private:
    ComboBox fComboBox;
    int nbItem;
    vector<double> fValues;

public:
    /**
     * \brief   Constructor.
     * \details Initialize the uiComponent and Menu specific variables, and the juce::ComboBox parameters.
     *          Menu is considered as a slider in the FAUST logic, with a step of one. The first item
     *          would be 0 on a slider, the second 1, etc. Each "slider value" is associated with a 
     *          string.
     *
     * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
     * \param   cur                                 Current "slider value" associated with the current item selected.
     * \param   low                                 Lowest value possible.
     * \param   hi                                  Highest value possible.
     * \param   mdescr                              Menu description. Contains the names of the items associated with their "value".
     */
    uiMenu(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, String tooltip, const char* mdescr) : uiComponent(gui, zone, w, h, tooltip, label)
    {
        //Init ComboBox parameters
        fComboBox.setEditableText(false);
        fComboBox.setJustificationType(Justification::centred);
        fComboBox.addListener(this);
        addAndMakeVisible(fComboBox);

        vector<string>  names;
        vector<double>  values;

        if (parseMenuList(mdescr, names, values)) {

            int     defaultitem = -1;
            double  mindelta = FLT_MAX;

            // Go through all the Menu's items.
            for (int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ( (v >= lo) && (v <= hi) ) {
                    // It is a valid value : add corresponding menu item
                    // +1 because index 0 is reserved for a non-defined item.
                    fComboBox.addItem(String(names[i].c_str()), v+1);
                    fValues.push_back(v);

                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultitem = fComboBox.getNumItems();
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultitem > -1) {
                fComboBox.setSelectedItemIndex(defaultitem);
            }
        }

        *fZone = cur;
    }

    /** Indicate to the FAUST module when the selected items is changed. */
    void comboBoxChanged (ComboBox* cb) override
    {
        std::cout<<fName<<" : "<<cb->getSelectedId() - 1<<std::endl;
        // -1 because of the +1 at the initialization
        modifyZone(cb->getSelectedId() - 1);
    }

    virtual void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;

        // search closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;

        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) {
            fComboBox.setSelectedItemIndex(defaultitem);
        }
    }

    /** Apply the LookAndFeel to the juce::ComboBox widget. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) override {
        fComboBox.setLookAndFeel(laf);
    }

    /** Set the good coordinates and size to the juce::ComboBox widget whenever the layout get reiszed */
    virtual void resized() override {
        fComboBox.setBounds(0, getLocalBounds().getY() + kMenuHeight/2, getWidth(), kMenuHeight/2);
    }

    /** Display the name of the Menu */
    virtual void paint(Graphics& g) override {
        g.setColour(Colours::black);
        g.drawText(fName, getLocalBounds().withHeight(getLocalBounds().getHeight()/2), Justification::centredTop);
    }
};

/** Intern class for RadioButton */
class uiRadioButton: public uiComponent,
    private juce::Button::Listener
{
private:
    int x, y, width, height;
    int nbButtons;
    bool isVertical;
    OwnedArray<ToggleButton> fButtons;
    vector<double> fValues;

public:
    /**
     * \brief   Constructor.
     * \details Initialize the uiComponent variables, and the RadioButton specific variables
     *          and parameters. Works in a similar way to the Menu, because it is a special
     *          kind of sliders in the faust logic. 
     * \see     uiMenu
     * 
     * \param   gui, zone, tooltip, label   uiComponent variables.
     * \param   w                           uiComponent variable and width of the RadioButton widget.
     * \param   h                           uiComponent variable and height of the RadioButton widget.
     * \param   cur                         Current "value" associated with the item selected.
     * \param   low                         Lowest "value" possible.
     * \param   hi                          Highest "value" possible.
     * \param   vert                        True if vertical, false if horizontal.
     * \param   names                       Contain the names of the different items.
     * \param   values                      Contain the "values" of the different items.
     * \param   radioGroupID                RadioButton being multiple CheckButton in JUCE, 
     *                                      we need an ID to know which are linked together.
     */
    uiRadioButton(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, bool vert, vector<string>& names, vector<double>& values, String tooltip, int radioGroupID) : uiComponent(gui, zone, w, h, tooltip, label), width(w), height(h), isVertical(vert)
    {
        x = getLocalBounds().getX();
        y = (getLocalBounds().getHeight()-kCheckButtonHeight)/2;

        {
            ToggleButton*   defaultbutton = 0;
            double          mindelta = FLT_MAX;

            nbButtons = names.size();
            for(int i = 0; i < nbButtons; i++) {
                double v = values[i];

                if ((v >= lo) && (v <= hi)) {

                    // It is a valid value included in slider's range
                    ToggleButton* tb = new ToggleButton(names[i]);
                    addAndMakeVisible(tb);
                    tb->setRadioGroupId (radioGroupID);
                    tb->addListener(this);
                    fValues.push_back(v);
                    fButtons.add(tb);

                    if(fTooltipText.isNotEmpty()) {
                        tb->setTooltip(fTooltipText);
                    }
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultbutton = tb;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultbutton) {
                defaultbutton->setToggleState (true, dontSendNotification);
            }
        }
    }

    /** Apply the LookAndFeel to all the CheckButtons widgets. */
    virtual void setCompLookAndFeel(LookAndFeel* laf) {
        for(int i = 0; i<nbButtons; i++)
            fButtons[i]->setLookAndFeel(laf);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;

        // select closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;

        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) {
            fButtons.operator[](defaultitem)->setToggleState (true, dontSendNotification);
        }
    }

    /** Handle the placement of each juce::ToggleButton everytime the layout size is changed. */
    virtual void resized() {
        isVertical ? height = (getLocalBounds().getHeight()-12) / nbButtons
                              : width = getLocalBounds().getWidth() / nbButtons;

        for(int i = 0; i < nbButtons; i++) {
            if(isVertical) {
                fButtons.operator[](i)->setBounds(0, i * height + 12, getLocalBounds().getWidth(), height);
            }
            else {
                // 12 pixels offset for the title
                fButtons.operator[](i)->setBounds(i * width, 12, width, getLocalBounds().getHeight()-12);
            }
        }
    }
    
    /** Display the RadioButton name */
    virtual void paint(Graphics& g) {
        g.setColour(Colours::black);
        g.drawText(fName, getLocalBounds().withHeight(12), Justification::centredTop);
    }

    /** Check which button is checked, and give its "value" to the FAUST module */
    void buttonClicked(Button* button)
    {
        ToggleButton* checkButton = dynamic_cast<ToggleButton*>(button);
        std::cout<<fName<<" : "<<fButtons.indexOf(checkButton)<<std::endl;

        modifyZone(fButtons.indexOf(checkButton));
    }
};

/** 
 * \brief   Intern class for VU-meter
 * \details There is no JUCE widgets for VU-meter, so its fully designed in this class.
 */
class uiVUMeter  : public uiComponent, public Timer
{
public:
    /**
     * \brief   Constructor.
     * \details Initialize the uiComponent variables and the VU-meter specific ones.
     *
     * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
     * \param   mini                                Minimal value of the VU-meter range.
     * \param   maxi                                Maximal value of the VU-meter range.
     * \param   unit                                Unit of the VU-meter (dB or not).
     * \param   style                               Type of the VU-meter (see VUMeterType).
     * \param   vert                                True if vertical, false if horizontal.
     */
    uiVUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, String unit, String tooltip, VUMeterType style, bool vert)
        : uiComponent(gui, zone, w, h, tooltip, label), fMin(mini), fMax(maxi), fStyle(style)
    {
        fLevel = 0;         // Initialization of the level
        startTimer (50);    // Launch a timer that trigger a callback every 50ms
        this->fUnit = unit;
        (unit == "dB") ? db = true : db = false;
        
        if(db) {
            // Conversion in dB of the range
            fScaleMin = dB2Scale(fMin);
            fScaleMax = dB2Scale(fMax);
        }
        
        isBargraphNameShown = (!(fName.startsWith("0x")) && fName.isNotEmpty());
        
        if(fTooltipText.isNotEmpty()) {
            setTooltip(fTooltipText);
        }
        
        // No text editor for LEDs
        if(fStyle != Led) {
            setupLabel();
        }
    }

    /** Method called by the timer every 50ms, to refresh the VU-meter if it needs to */
    void timerCallback() override
    {
        if (isShowing()) {
            if(fLevel == 0) {
                forceRepaint = true;    //Force painting at the initialisation
            }
            else {
                forceRepaint = false;
            }

            float lastLevel = fLevel;   //t-1
            setLevel(); //t
            
            // Following condition means that we're repainting our VUMeter only if
            // there's one or more changing pixels between last state and this one,
            // and if the curent level is included in the VUMeter range. It improves
            // performances a lot in IDLE. It's the same for the other style of VUMeter
            
            if(db) {
                if(fStyle == VVUMeter) {
                    if (((int)dB2y(lastLevel) != (int)dB2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == HVUMeter) {
                    if (((int)dB2x(lastLevel) != (int)dB2x(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == NumDisplay) {
                    if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == Led) {
                    if((dB2Scale(lastLevel) != dB2Scale(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                }

            } else {
                if(fStyle == VVUMeter) {
                    if (((int)lin2y(lastLevel) != (int)lin2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == HVUMeter) {
                    if ((std::abs(lastLevel-fLevel)>0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == Led) {
                    if ((std::abs(lastLevel-fLevel)>0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                } else if(fStyle == NumDisplay) {
                    if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                        repaint();
                    }
                }
            }
        } else {
            fLevel = 0;
        }
    }

    /** 
     * Has to be defined because its purely virtual in uiBaseComponent, 
     * but as its not a JUCE widget, there is no LookAndFeel submethod associated.
     */
    virtual void setCompLookAndFeel(LookAndFeel* laf) override { }

    /** 
     * Call the appropriate drawing method according to the VU-meter style 
     * \see drawLed
     * \see drawNumDisplay
     * \see drawVBargraph
     * \see drawHBargraph
     */
    void paint (Graphics& g) override
    {
        if     (fStyle == Led)       {
            drawLed       (g, kLedWidth,       kLedHeight,        fLevel);
        } else if(fStyle == NumDisplay) {
            drawNumDisplay(g, kNumDisplayWidth,  kNumDisplayHeight/2, fLevel);
        } else if(fStyle == VVUMeter)  {
            drawVBargraph (g, kVBargraphWidth/2, getHeight(),         fLevel, db);
        } else if(fStyle == HVUMeter)  {
            drawHBargraph (g, getWidth(),        kHBargraphHeight/2,  fLevel, db);
        }
    }

    /** Set the Label position whenever the layout size changes. */
    void resized() override {
        setLabelPos();
    }

    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }

private:
    float fLevel;               // Current level of the VU-meter.
    float fMin, fMax;           // Linear range of the VU-meter.
    float fScaleMin, fScaleMax; // Range in dB if needed.
    bool db;                    // True if it's a dB VU-meter, false otherwise.
    VUMeterType fStyle;
    String fUnit;
    Label fLabel;               // Name of the VU-meter.
    bool isBargraphNameShown;   // Is the VU-meter name displayable.
    bool forceRepaint;          // Only needed at the initialization.

    /** Give the right coordinates and size to the text of Label depending on the VU-meter style */
    void setLabelPos() {
        if     (fStyle == VVUMeter)   {
            // -22 on the height because of the text box.
            fLabel.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20);
        }
        else if(fStyle == HVUMeter)   {
            isBargraphNameShown ? fLabel.setBounds(63, (getHeight()-20)/2, 50, 20)
                                : fLabel.setBounds(3,  (getHeight()-20)/2, 50, 20);
        }
        else if(fStyle == NumDisplay) {
            fLabel.setBounds((getLocalBounds().getWidth()-kNumDisplayWidth)/2,
                            (getLocalBounds().getHeight()-kNumDisplayHeight/2)/2,
                            kNumDisplayWidth,
                            kNumDisplayHeight/2);
        }
    }

    /** Contain all the initialization need for our Label */
    void setupLabel() {
        setLabelPos();
        fLabel.setEditable(false, false, false);
        fLabel.setJustificationType(Justification::centred);
        fLabel.setText(String((int)*fZone) + fUnit, dontSendNotification);
        if(fTooltipText.isNotEmpty()) {
            fLabel.setTooltip(fTooltipText);
        }

        addAndMakeVisible(fLabel);
    }

    /** 
     * \brief   Generic method to draw an horizontal VU-meter.
     * \details Draw the background of the bargraph, and the TextBox box, without taking
     *          care of the actual level of the VU-meter
     * \see     drawHBargraphDB
     * \see     drawHBargraphLin
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   width   Width of the VU-meter widget.
     * \param   height  Height of the VU-meter widget.
     * \param   level   Current level that needs to be displayed.
     * \param   dB      True if it's a db level, false otherwise.
     */
    void drawHBargraph(Graphics& g, int width, int height, float level, bool dB) {
        float x;
        float y = (float)(getHeight()-height)/2;
        if(isBargraphNameShown) {
            x = 120;
            width -= x;

            // VUMeter Name
            g.setColour(Colours::black);
            g.drawText(fName, 0, y, 60, height, Justification::centredRight);
        } else {
            x = 60;
            width -= x;
        }

        // VUMeter Background
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);

        // Label Window
        g.setColour(Colours::darkgrey);
        g.fillRect((int)x-58, (getHeight()-22)/2, 52, 22);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect((int)x-57, (getHeight()-20)/2, 50, 20);

        // Call the appropriate drawing method for the level.
        dB ? drawHBargraphDB (g, y, height, level)
           : drawHBargraphLin(g, x, y, width, height, level);
    }

    /**
     * Method in charge of drawing the level of a horizontal dB VU-meter.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   y       y coordinate of the VU-meter.
     * \param   height  Height of the VU-meter.
     * \param   level   Current level of the VU-meter, in dB.
     */
    void drawHBargraphDB(Graphics& g, int y, int height, float level) {

        // Drawing Scale
        g.setFont(9.0f);
        g.setColour(Colours::white);
        for(int i = -10; i > fMin; i -= 10) {
            paintScale(g, i);
        }
        for(int i = -6; i < fMax; i += 3)  {
            paintScale(g, i);
        }

        int alpha = 200;
        
        // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
        // and so to start the new color rectangle at the end of the previous one.
        
        // Drawing from the minimal range to the current level, or -10dB.
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(dB2x(fMin), y+1.0f, jmin(dB2x(level)-dB2x(fMin), dB2x(-10)-dB2x(fMin)), (float) height-2);

        // Drawing from -10dB to the current level, or -6dB.
        if(dB2Scale(level) > dB2Scale(-10)) {
            g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-10), y+1.0f, jmin(dB2x(level)-dB2x(-10), dB2x(-6)-dB2x(-10)), (float) height-2);
        }
        // Drawing from -6dB to the current level, or -3dB.
        if(dB2Scale(level) > dB2Scale(-6)) {
            g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-6), y+1.0f, jmin(dB2x(level)-dB2x(-6), dB2x(-3)-dB2x(-6)), (float) height-2);
        }
        // Drawing from -3dB to the current level, or 0dB.
        if(dB2Scale(level) > dB2Scale(-3)) {
            g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-3), y+1.0f, jmin(dB2x(level)-dB2x(-3), dB2x(0)-dB2x(-3)), (float) height-2);
        }
        // Drawing from 0dB to the current level, or the max range.
        if(dB2Scale(level) > dB2Scale(0)) {
            g.setColour(Colour((uint8)240,  (uint8)0, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(0), y+1.0f, jmin(dB2x(level)-dB2x(0), dB2x(fMax)-dB2x(0)), (float) height-2);
        }
    }

    /**
     * Method in charge of drawing the level of a horizontal linear VU-meter.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   x       x coordinate of the VU-meter.
     * \param   y       y coordinate of the VU-meter.
     * \param   height  Height of the VU-meter.
     * \param   width   Width of the VU-meter.
     * \param   level   Current level of the VU-meter, in linear logic.
     */
    void drawHBargraphLin(Graphics& g, int x, int y, int width, int height, float level) {

        int alpha = 200;
        Colour c = juce::Colour((uint8)255, (uint8)165, (uint8)0, (uint8)alpha);
        
        // Drawing from the minimal range to the current level, or 20% of the VU-meter
        g.setColour(c.brighter());
        g.fillRect(x+1.0f, y+1.0f, jmin(level*(width-2), 0.2f*(width-2)), (float) height-2);
        // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter
        if(level > 0.2f) {
            g.setColour(c);
            g.fillRect(x+1.0f + 0.2f*(width-2), y+1.0f, jmin((level-0.2f) * (width-2), (0.9f-0.2f) * (width-2)), (float) height-2);
        }
        // Drawing from 90% of the VU-meter to the current level, or the maximal range of the VU-meter
        if(level > 0.9f) {
            g.setColour(c.darker());
            g.fillRect(x+1.0f + 0.9f*(width-2), y+1.0f, jmin((level-0.9f) * (width-2), (1.0f-0.9f) * (width-2)), (float) height-2);
        }
    }
    /**
     * \brief   Generic method to draw a vertical VU-meter.
     * \details Draw the background of the bargraph, and the TextBox box, without taking
     *          care of the actual level of the VU-meter
     * \see     drawHBargraphDB
     * \see     drawHBargraphLin
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   width   Width of the VU-meter widget.
     * \param   height  Height of the VU-meter widget.
     * \param   level   Current level that needs to be displayed.
     * \param   dB      True if it's a db level, false otherwise.
     */
    void drawVBargraph(Graphics& g, int width, int height, float level, bool dB) {
        float x = (float)(getLocalBounds().getWidth()-width)/2;
        float y;
        if(isBargraphNameShown) {
            y = (float) getLocalBounds().getHeight()-height+15;
            height -= 40;

            // VUMeter Name
            g.setColour(Colours::black);
            g.drawText(fName, getLocalBounds(), Justification::centredTop);
        } else {
            y = (float) getLocalBounds().getHeight()-height;
            height -= 25;
        }

        // VUMeter Background
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);

        // Label window
        g.setColour(Colours::darkgrey);
        g.fillRect(jmax((getWidth()-50)/2, 0), getHeight()-23, jmin(getWidth(), 50), 22);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect(jmax((getWidth()-48)/2, 1), getHeight()-22, jmin(getWidth()-2, 48), 20);

        dB ? drawVBargraphDB (g, x, width, level)
        : drawVBargraphLin(g, x, width, level);
    }

    /**
     * Method in charge of drawing the level of a vertical dB VU-meter.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   x       x coordinate of the VU-meter.
     * \param   width   Width of the VU-meter.
     * \param   level   Current level of the VU-meter, in dB.
     */
    void drawVBargraphDB(Graphics& g, int x, int width, float level) {

        // Drawing Scale
        g.setFont(9.0f);
        g.setColour(Colours::white);
        for(int i = -10; i > fMin; i -= 10) {
            paintScale(g, i);
        }
        for(int i = -6; i < fMax; i += 3)  {
            paintScale(g, i);
        }

        int alpha = 200;
        
        // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
        // and so to start the new color rectangle at the end of the previous one.
        
        // Drawing from the minimal range to the current level, or -10dB.
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-10)), (float) width-2, dB2y(fMin)-jmax(dB2y(level), dB2y(-10)));
        
        // Drawing from -10dB to the current level, or -6dB.
        if(dB2Scale(level) > dB2Scale(-10)) {
            g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-6)), (float) width-2, dB2y(-10)-jmax(dB2y(level), dB2y(-6)));
        }
        // Drawing from -6dB to the current level, or -3dB.
        if(dB2Scale(level) > dB2Scale(-6)) {
            g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-3)), (float) width-2, dB2y(-6)-jmax(dB2y(level), dB2y(-3)));
        }
        // Drawing from -3dB to the current level, or 0dB.
        if(dB2Scale(level) > dB2Scale(-3)) {
            g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(0)), (float) width-2, dB2y(-3)-jmax(dB2y(level), dB2y(0)));
        }
        // Drawing from 0dB to the current level, or the maximum range.
        if(dB2Scale(level) > dB2Scale(0)) {
            g.setColour(Colour((uint8)240,  (uint8)0, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(fMax)), (float) width-2, dB2y(0)-jmax(dB2y(level), dB2y(fMax)));
        }
    }

    /**
     * Method in charge of drawing the level of a vertical linear VU-meter.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   x       x coordinate of the VU-meter.
     * \param   width   Width of the VU-meter.
     * \param   level   Current level of the VU-meter, in linear logic.
     */
    void drawVBargraphLin(Graphics& g, int x, int width, float level) {

        int alpha = 200;
        Colour c = juce::Colour((uint8)255, (uint8)165, (uint8)0, (uint8)alpha);

        // Drawing from the minimal range to the current level, or 20% of the VU-meter.
        g.setColour(c.brighter());
        g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.2f)), (float) width-2, lin2y(fMin)-jmax(lin2y(level), lin2y(0.2f)));
        
        // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter.
        if(level > 0.2f) {
            g.setColour(c);
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.9f)), (float) width-2, lin2y(0.2f)-jmax(lin2y(level), lin2y(0.9f)));
        }
        
        // Drawing from 90% of the VU-meter to the current level, or the maximum range.
        if(level > 0.9f) {
            g.setColour(c.darker());
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(fMax)), (float) width-2, lin2y(0.9)-jmax(lin2y(level), lin2y(fMax)));
        }
    }

    /**
     * Method in charge of drawing the LED VU-meter, dB or not.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   width   Width of the LED.
     * \param   height  Height of the LED.
     * \param   level   Current level of the VU-meter, dB or not.
     */
    void drawLed(Graphics& g, int width, int height, float level) {
        float x = (float) (getLocalBounds().getWidth() - width)/2;
        float y = (float) (getLocalBounds().getHeight() - height)/2;
        g.setColour(Colours::black);
        g.fillEllipse(x, y, width, height);

        if(db) {
            int alpha = 200;
            
            // Adjust the color depending on the current level
            g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
            if(dB2Scale(level) > dB2Scale(-10)) {
                g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha));
            }
            if(dB2Scale(level) > dB2Scale(-6)) {
                g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha));
            }
            if(dB2Scale(level) > dB2Scale(-3)) {
                g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha));
            }
            if(dB2Scale(level) > dB2Scale(0))  {
                g.setColour(Colour((uint8)240, (uint8)0,   (uint8)20, (uint8)alpha));
            }

            g.fillEllipse(x+1, y+1, width-2, height-2);
        } else {
            // The alpha depend on the level, from 0 to 1
            g.setColour(Colours::red.withAlpha((float)level));
            g.fillEllipse(x+1, y+1, width-2, height-2);
        }
    }

    /**
     * Method in charge of drawing the Numerical Display VU-meter, dB or not.
     *
     * \param   g       JUCE graphics context, used to draw components or images.
     * \param   width   Width of the Numerical Display.
     * \param   height  Height of the Numerical Display.
     * \param   level   Current level of the VU-meter.
     */
    void drawNumDisplay(Graphics& g, int width, int height, float level) {
        // Centering it
        int x = (getLocalBounds().getWidth()-width)  / 2;
        int y = (getLocalBounds().getHeight()-height)/ 2;

        // Draw box.
        g.setColour(Colours::darkgrey);
        g.fillRect(x, y, width, height);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect(x+1, y+1, width-2, height-2);
    
        // Text is handled by the setLabelPos() function
    }
    
    float dB2Scale(float dB)
    {
        float fScale = 1.0;

        if      (dB < -60.0)
            fScale = (dB + 70.0) * 0.0025;
        else if (dB < -50.0)
            fScale = (dB + 60.0) * 0.005 + 0.025;
        else if (dB < -40.0)
            fScale = (dB + 50.0) * 0.0075 + 0.075;
        else if (dB < -30.0)
            fScale = (dB + 40.0) * 0.015 + 0.15;
        else if (dB < -20.0)
            fScale = (dB + 30.0) * 0.02 + 0.3;
        else if (dB < -0.001 || dB > 0.001)  /* if (dB < 0.0) */
            fScale = (dB + 20.0f) * 0.025 + 0.5;

        return fScale;
    }

    /** Convert a dB level to a y coordinate, for easier draw methods. */
    float dB2y(float dB)
    {
        FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
        FAUSTFLOAT s1 = fScaleMax;      // Maximum range.
        FAUSTFLOAT sx = dB2Scale(dB);   // Current level.

        int h;
        int treshold;   // Value depend if the name is displayed

        if(isBargraphNameShown) {
            h = getHeight()-42; // 15 pixels for the VU-Meter name,
                                // 25 for the textBox, 2 pixels margin.
            treshold = 16;      // 15 pixels for the VU-Meter name.
        } else {
            h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
            treshold = 1;       // 1 pixel margin.
        }

        return (h - h*(s0-sx)/(s0-s1)) + treshold;
    }

    /** Convert a linear level to a y coordinate, for easier draw methods. */
    float lin2y(float level) {
        int h;
        int treshold;

        if(isBargraphNameShown) {
            h = getHeight()-42; // 15 pixels for the VU-Meter name,
                                // 25 for the textBox, 2 pixels margin.
            treshold = 16;      // 15 pixels for the VU-Meter name.
        } else {
            h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
            treshold = 1;       // 1 pixel margin.
        }

        return h * (1 - level) + treshold;
    }

    /** Convert a dB level to a x coordinate, for easier draw methods. */
    float dB2x(float dB)
    {
        FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
        FAUSTFLOAT s1 = fScaleMax;      // Maximal range.
        FAUSTFLOAT sx = dB2Scale(dB);   // Current level.

        int w;
        int treshold;

        if(isBargraphNameShown) {
            w = getWidth()-122; // 60 pixels for the VU-Meter name,
                                // 60 for the TextBox, 2 pixels margin.
            treshold = 121;     // 60 pixels for the VU-Meter name,
                                // 60 for the TextBox, and 1 pixel margin.
        } else {
            w = getWidth()-62;  // 60 pixels for the TextBox, 2 pixels margin.
            treshold = 61;      // 60 pixels for the TextBox, 1 pixel margin.
        }

        return treshold + w - w*(s1-sx)/(s1-s0);
    }

    /** Write the different level included in the VU-Meter range. */
    void paintScale(Graphics& g, float num) {
        Rectangle<int> r;

        if(fStyle == VVUMeter) {
            r = Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2 + 1,  // Left side of the VU-Meter.
                               dB2y(num),                               // Vertically centred with 20 height.
                               (kVBargraphWidth/2)-2,                   // VU-Meter width with margin.
                               20);                                     // 20 height.
            g.drawText(String(num), r, Justification::centredRight, false);
        } else {
            r = Rectangle<int>(dB2x(num)-10,                            // Horizontally centred with 20 width.
                               (getHeight()-kHBargraphHeight/2)/2 +1,   // Top side of the VU-Meter.
                               20,                                      // 20 width.
                               (kHBargraphHeight/2)-2);                 // VU-Meter height with margin
            g.drawText(String(num), r, Justification::centredTop, false);
        }
    }

    /** Set the level, keep it in the range of the VU-Meter, and set the TextBox text. */
    void setLevel() {
        float rawLevel = *fZone;

        if(db) {
            fLevel = rawLevel;
            if     (fLevel > fMax) {
                fLevel = fMax;
            }
            else if(fLevel < fMin) {
                fLevel = fMin;
            }
        } else {
            fLevel = (rawLevel-fMin)/(fMax-fMin);
            if     (fLevel > 1)  {
                fLevel = 1;
            }
            else if(fLevel < 0)  {
                fLevel = 0;
            }
        }

        fLabel.setText(String((int)rawLevel)+fUnit, dontSendNotification);
    }
};

/**
 * \brief   Intern class for box widgets
 * \details That's the class where the whole layout is calculated.
 */
class uiBox : public uiBaseComponent
{
public:
    /**
     * \brief   Constructor.
     * \details Initialize uiBaseComponent variables and uiBox specific ones.
     *
     * \param   vert        True if it's a vertical box, false otherwise.
     * \param   boxName     Name of the uiBox.
     * \param   boxOrder    "Order" of the box, 0 being the box at the tree root, 
                            and the higher it is, the closer to the tree leaves.
     */
    uiBox(bool vert, String boxName, int boxOrder): uiBaseComponent(0, 0, boxName), fOrder(boxOrder), isVertical(vert)
    {
        isNameDisplayed = (!(fName.startsWith("0x")) && fName.isNotEmpty());
        
        // The ratios being calculated depending on the uiBaseComponent parent size, and
        // the order 0 box not having one, we initialize them here.
        if(fOrder == 0) {
            fHRatio = 1;
            fVRatio = 1;
        }
    }

    /** Call the setLookAndFeel method for all its child, by going through the uiBaseComponent tree */
    void setCompLookAndFeel(LookAndFeel* laf) override {
        for(int i = 0; i<getNumChildComponents(); i++) {
            dynamic_cast<uiBaseComponent*> (getChildComponent(i))->setCompLookAndFeel(laf);
        }
    }

    /**
     * \brief   Main layout function.
     * \details Allow to place all uiBaseComponent child correctly according to their ratios
     *          and the current box size.
     *
     * \param   functionRect    Absolute raw bounds of the current box (with margins 
     *                          and space for the title).
     */
    void arrangeComponents(Rectangle<int> functionRect)
    {
        // Deleting space for the box name if it needs to be shown
        if(isNameDisplayed) {
            functionRect.removeFromTop(12);
        }
        
        // Putting the margins
        functionRect.reduce(2, 2);
        
        // Give child components an adapt size depending on its ratio and the current box size
        for(int i = 0; i<getNumChildComponents(); i++) {
            uiBaseComponent* tempComp = dynamic_cast<uiBaseComponent*>(getChildComponent(i));
            
            if(isVertical) {
                int heightToRemove = getSpaceToRemove(tempComp->getVRatio());
                // Remove the space needed from the functionRect, and translate it
                // to show the margins
                tempComp->setBaseComponentSize(functionRect.removeFromTop(heightToRemove).translated(0, 4*i));
            } else {
                int widthToRemove = getSpaceToRemove(tempComp->getHRatio());
                // Remove the space needed from the functionRect, and translate it
                // to show the margins
                tempComp->setBaseComponentSize(functionRect.removeFromLeft(widthToRemove).translated(4*i, 0));
            }
        }
    }

    /** uiBox caracteristics debug output */
    void writeDebug() override {
        std::cout<<std::endl<<fName<<" : "<<std::endl;
        std::cout<<"order : "<<fOrder<<", itemCount : "<<getNumChildComponents();
        if(fOrder > 0) {
            std::cout<<", parent : "<<findParentComponentOfClass<uiBaseComponent>()->fName<<std::endl;
        } else {
            std::cout<<"no parent, main box"<<std::endl;
        }
        std::cout<<"CompBounds : {"<<getBounds().toString()<<"}"<<std::endl;
        std::cout<<"Recommended size : "<<fTotalWidth<<"x"<<fTotalHeight<<std::endl;
        std::cout<<"Ratios : "<<fVRatio<<", "<<fHRatio<<std::endl;
        std::cout<<"fDisplayRectHeight : "<<fDisplayRectHeight<<", fDisplayRectWidth : "<<fDisplayRectWidth<<std::endl;
        std::cout<<"isVisible ? "<<isVisible()<<std::endl;
        std::cout<<"Childs : ";
        for(int j = 0; j<getNumChildComponents(); j++) {
            std::cout<<dynamic_cast<uiBaseComponent*>(getChildComponent(j))->fName<<", ";
        }
        std::cout<<std::endl;
    }

    /** 
     * \brief   Return the dimension size for a child to be displayed in.
     * \details Depending on the horizontal or vertical aspect of the uiBox, 
     *          the horizontal or vertical child ratio is given as argument, 
     *          and a width or a height value is returned.
     *
     * \param   ratio   Horizontal or Vertical ratio of the child component, depending on the uiBox.
     */
    int getSpaceToRemove(float ratio) {
        if(isVertical) {
            // Checking if the name is displayed, to give to good amount space for child components
            // 12 pixels is the bix name, 4 pixel per child components for the margins
            if(isNameDisplayed) {
                return (float)(getBounds().getHeight() - 12 - 4*getNumChildComponents())*ratio;
            } else {
                return (float)(getBounds().getHeight() - 4*getNumChildComponents())*ratio;
            }
        } else {
            // Don't need to check for an horizontal box, as it height doesn't matter
            return (float)(getBounds().getWidth() - 4*getNumChildComponents())*ratio;
        }
    }

    /** Add a uiBox as child of the current uiBox in the tree */
    void addChildBox(uiBox* box) {
        addAndMakeVisible(box);
    }
    
    /** Add a uiComponent as child of the current uiBox in the tree */
    void addChildUiComponent(uiComponent* comp) {
        addAndMakeVisible(comp);
    }

    /**
     * \brief   Initialization of the DisplayRect and Total size.
     * \details Calculate the correct size for each box, depending on its child
     *          sizes.
     */
    void calculRecommendedSize() {
        // Display rectangle size is the sum of a dimension on a side, and the max of the other one
        // on the other side, depending on its orientation (horizontal/vertical).
        // Using child's totalSize, because the display rectangle size need to be as big as
        // all of its child components with their margins included.
        for(int j = 0; j<getNumChildComponents(); j++) {
            if(isVertical) {
                fDisplayRectHeight += (dynamic_cast<uiBaseComponent*>(getChildComponent(j))->getTotalHeight());
                fDisplayRectWidth   = jmax((int)fDisplayRectWidth, dynamic_cast<uiBaseComponent*>(getChildComponent(j))->getTotalWidth());
            } else {
                fDisplayRectWidth += (dynamic_cast<uiBaseComponent*>(getChildComponent(j))->getTotalWidth());
                fDisplayRectHeight = jmax((int)fDisplayRectHeight, dynamic_cast<uiBaseComponent*>(getChildComponent(j))->getTotalHeight());
            }
        }
        
        fTotalHeight = fDisplayRectHeight;
        fTotalWidth = fDisplayRectWidth;
        
        // Adding 4 pixels of margins per child component on a dimension, and just 4 on
        // the other one, depending on its orientation
        if(isVertical) {
            fTotalHeight += 4 * getNumChildComponents();
            fTotalWidth  += 4;
        } else {
            fTotalWidth  += 4 * getNumChildComponents();
            fTotalHeight += 4;
        }

        // Adding 12 pixels on its height to allow the name to be displayed
        if(isNameDisplayed) {
            fTotalHeight += 12;
        }
        Component::setSize(fTotalWidth, fTotalHeight);
    }

    /** Initiate the current box ratio, and its child's ones recursively. */
    void setRatio() override {
        uiBaseComponent::setRatio();
        
        // Going through the Component tree recursively
        for(int i = 0; i<getNumChildComponents(); i++) {
            dynamic_cast<uiBaseComponent*>(getChildComponent(i))->setRatio();
        }
    }

    /** 
     * Call the dynamic layout method arrangeComponents.
     * \see arrangeComponents
     */
    void resized() override {
        arrangeComponents(getBounds());
        // Debug option
        // writeDebug();
    }

    /** 
     * Fill the uiBox bounds with a grey color, different shades depending on its order.
     * Write the uiBox name if it needs to.
     */
    void paint(Graphics& g) override
    {
        // Fill the box background in gray shades
        g.setColour(Colours::black.withAlpha(0.2f));
        g.fillRect(getLocalBounds());

        // Display the name if it's needed
        if(isNameDisplayed) {
            g.setColour(Colours::black);
            g.drawText(fName, getLocalBounds().withHeight(12), Justification::centred);
        }
    }

    /** 
     * \brief   Destructor.
     * \details Delete all uiBox recusively, but not the uiComponent, 
     *          because it's handled by the uiItem FAUST objects.
     */
    ~uiBox() {
        // Deleting boxes, from leaves to root
        int numChild = getNumChildComponents();
        std::cout<<"order : "<<fOrder<<", numChilds : "<<numChild<<std::endl;
        for(int i = numChild-1; i>=0; i--) {
            delete dynamic_cast<uiBox*> (getChildComponent(i));
        }
    }

    int fOrder; // mainly for debug usage
    bool isNameDisplayed;
    bool isVertical;
};


/** Intern class for tab widget */
class uiTabs  : public TabbedComponent
{
public:
    /**
     * \brief   Constructor.
     * \details Initalize the juce::TabbedComponent tabs to be at top, and the uiTabs size at 0 
     */
    uiTabs()
        : TabbedComponent (TabbedButtonBar::TabsAtTop)
    {
        fTabTotalHeight = 0;
        fTabTotalWidth = 0;
    }

    /** 
     * Initialize all his child ratios (1 uiBox per tabs), the LookAndFeel
     * and the uiTabs size to fit the biggest of its child.
     */
    void init() {
        for(int i = 0; i < getNumTabs(); i++) {
            uiBaseComponent* tempComp = dynamic_cast<uiBaseComponent*>(getTabContentComponent(i));
            tempComp->setRatio();
            tempComp->setCompLookAndFeel(laf);
            
            // The TabbedComponent size should be as big as its bigger child's dimension, done here
            fTabTotalHeight = jmax(fTabTotalHeight, tempComp->fTotalHeight);
            fTabTotalWidth = jmax(fTabTotalWidth, tempComp->fTotalWidth);
        }
    }

    /** Add a uiBox as child of the uiTabs, and a new tab. */
    void addTabs(String label, Component* comp) {
        TabbedComponent::addTab(label, Colours::white, comp, true);
        for(int i = 0; i<getNumChildComponents(); i++) {
            uiBox* box = dynamic_cast<uiBox*>(getChildComponent(i));
            if(box !=0) {
                std::cout<<"childs : "<<box->fName<<", ";
            }
        }
        std::cout<<std::endl;
    }

    int fTabTotalWidth, fTabTotalHeight;
    ScopedPointer<LookAndFeel> laf = new CustomLookAndFeel();
};


/** Class in charge of doing the glue between FAUST and JUCE */
class JuceGUI: public GUI, public MetaDataUI, public Component
{
public:
    /**
     * \brief   Constructor.
     * \details Initialize the JuceGUI specific variables. 
     */
    JuceGUI()
    {
        order = 0;      // Keep track of the progress in the buildUserInterface.
        radioGroup = 0; // Just needed in case of radioButtons.
    }

    /** Return the size of the FAUST program */
    Rectangle<int> getSize() {
        if(!tabLayout) {
            return Rectangle<int>(0,
                                  0,
                                  dynamic_cast<uiBox*>(getChildComponent(0))->fTotalWidth,
                                  dynamic_cast<uiBox*>(getChildComponent(0))->fTotalHeight);
        } else {
            return Rectangle<int>(0,
                                  0,
                                  dynamic_cast<uiTabs*>(getChildComponent(0))->fTabTotalWidth,
                                  dynamic_cast<uiTabs*>(getChildComponent(0))->fTabTotalHeight+30); // 30 height for the TabBar.
        }
    }

    /** Initialize the uiTabs component to be visible. */
    virtual void openTabBox(const char* label) {
        tabLayout = true;
        addAndMakeVisible(tabs);
    }

    /** Add a new vertical box to the user interface. */
    virtual void openVerticalBox(const char* label) {
        if(order == 0) { // First box that we open (excepted tabBox)
            if(tabLayout) {
                tabName = String(label);
                label = nullptr; // label is the box name, shouldn't be displayed
                                 // both (tab name and box name)
            }
            currentBox = new uiBox(true, String(label), order); // Create a new box
            parentBox = nullptr; // Its parent is not another uiBox, so null
            if(!tabLayout) {
                // Doesn't need to be done if it's a tab layout, addTabs function is already
                // doing it
                addAndMakeVisible(currentBox);
            }
        } else { // Not the first box
            parentBox = currentBox; // parent box is now set properly
            currentBox = new uiBox(true, String(label), order); // Create a new box
            parentBox->addChildBox(currentBox);
        }

        order++; // Keep track of "order" of the box, 0 being the main box, 1 being the main box child, etc...
    }

    /** Add a new horizontal box to the user interface. */
    virtual void openHorizontalBox(const char* label) {
        if(order == 0) { // First box that we open (excepted tabBox)
            if(tabLayout) {
                tabName = String(label);
                label = nullptr; // label is the box name, shouldn't be displayed
                                 // both (tab name and box name)
            }
            currentBox = new uiBox(false, String(label), order); // Create a new box
            parentBox = nullptr; // Its parent is not another uiBox, so null
            if(!tabLayout) {
                // Doesn't need to be done if it's a tab layout, addTabs function is already
                // doing it
                addAndMakeVisible(currentBox);
            }
        } else { // Not the first box
            parentBox = currentBox; // parent box is now set properly
            currentBox = new uiBox(false, String(label), order); // Create a new box
            parentBox->addChildBox(currentBox);
        }

        order++; // Keep track of "order" of the box, 0 being the main box, 1 being the main box child, etc...
    }

    /** Close the current box. */
    virtual void closeBox() {
        order--; // Decrementing to keep track of where we are in the buildUserInterface
        if(order > -1) { // Avoid to calculate that two times in case of a tabLayout
            currentBox->calculRecommendedSize();
        }

        if(dynamic_cast<uiBox*>(currentBox->getParentComponent()) != 0) { // Not doing that for the main box
            // Going backward in the tree, to the previous branch
            currentBox = parentBox;
            parentBox = currentBox->findParentComponentOfClass<uiBox>(); // Return comp parent of type 'uiBox'
        }

        if(tabLayout && order == 0) { // Closing a tab
            std::cout<<"Adding Box "<<tabName<<" to tab list"<<std::endl;
            tabs.addTabs(tabName, currentBox); // Adding the current main box to a new tab
            tabName.clear();
        } else if(tabLayout && order == -1) { // End of buildUserInterface
            std::cout<<"Init tab"<<std::endl;
            init(); // So our user interface. need to be initiated
        } else if(!tabLayout && order == 0) { // End of buildUserInterface
            init(); // So our user interface. need to be initiated
        }
    }

    /** Add an horizontal slider to the user interface. */
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if(isKnob(zone)) {
            addKnob(label, zone, init, min, max, step);
        } else if(isRadio(zone)) {
            addRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str(), false);
        } else if(isMenu(zone)) {
            addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str());
        } else {
            currentBox->addChildUiComponent(new uiSlider(this, zone, kHSliderWidth, kHSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), HSlider));
        }
    }
    
    /** Add a vertical slider to the user interface. */
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        if(isKnob(zone)) {
            addKnob(label, zone, init, min, max, step);
        } else if(isRadio(zone)) {
            addRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str(), true);
        } else if(isMenu(zone)) {
            addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str());
        } else {
            currentBox->addChildUiComponent(new uiSlider(this, zone, kVSliderWidth, kVSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), VSlider));

        }
    }
    
    /** Add a menu to the user interface. */
    void addMenu(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr) {
        currentBox->addChildUiComponent(new uiMenu(this, zone, String(label), kMenuWidth, kMenuHeight, init, min, max, String(fTooltip[zone]), mdescr));
    }
    
    /** Add a radio buttons to the user interface. */
    void addRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr, bool vert) {
        vector<string> names;
        vector<double> values;
        parseMenuList(mdescr, names, values); // Set names and values vectors
        int nbButtons = names.size();
        radioGroup++; // This is the variable that set the radio buttons to be radio buttons,
                      // and not just n checkButtons.
        int checkButtonWidth = 0;

        for(int i = 0; i < nbButtons; i++) {
            // Checking the maximum of horizontal space needed to display the radio buttons
            checkButtonWidth = jmax(Font().getStringWidth(String(names[i])) + 15, checkButtonWidth);
        }
        
        if(vert) {
            currentBox->addChildUiComponent(new uiRadioButton(this, zone, String(label), kCheckButtonWidth, nbButtons * (kRadioButtonHeight - 25) + 25, init, min, max, true, names, values, String(fTooltip[zone]), radioGroup));
        } else {
            currentBox->addChildUiComponent(new uiRadioButton(this, zone, String(label), kCheckButtonWidth, kRadioButtonHeight, init, min, max, false, names, values, String(fTooltip[zone]), radioGroup));
        }
    }
    
    /** Add a ciruclar slider to the user interface. */
    void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        currentBox->addChildUiComponent(new uiSlider(this, zone, kKnobWidth, kKnobHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), Knob));
    }
    
    /** Add a button to the user interface. */
    virtual void addButton(const char* label, FAUSTFLOAT* zone) {
        currentBox->addChildUiComponent(new uiButton(this, zone, kButtonWidth, kButtonHeight, String(label), String(fTooltip[zone])));
    }
    
    /** Add a check button to the user interface. */
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {
        // CheckButtonWidth is his text size, plus the check box size
        int checkButtonWidth = Font().getStringWidth(String(label)) + 15;
        currentBox->addChildUiComponent(new uiCheckButton(this, zone, checkButtonWidth, kCheckButtonHeight, String(label), String(fTooltip[zone])));
    }
    
    /** Add a numerical entry to the user interface. */
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        // 5 pixels margin between the slider and his name
        int newWidth = int(ceil(Font().getStringWidth(String(label)) + kNumEntryWidth)) + 5;
        currentBox->addChildUiComponent(new uiSlider(this, zone, newWidth, kNumEntryHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]), getScale(zone), NumEntry));

    }
    
    /** Add an horizontal bargraph to the user interface. */
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        if(isLed(zone)) {
            addLed(String(label), zone, min, max);
        } else if(isNumerical(zone)) {
            addNumericalDisplay(String(label), zone, min, max);
        } else {
            currentBox->addChildUiComponent(new uiVUMeter (this, zone, kHBargraphWidth, kHBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), HVUMeter, false));
        }
    }
    
    /** Add a vertical bargraph to the user interface. */
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        if(isLed(zone)) {
            addLed(String(label), zone, min, max);
        } else if(isNumerical(zone)) {
            addNumericalDisplay(String(label), zone, min, max);
        } else {
            currentBox->addChildUiComponent(new uiVUMeter (this, zone, kVBargraphWidth, kVBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), VVUMeter, true));
        }
    }
    
    /** Add a LED to the user interface. */
    void addLed (String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
        currentBox->addChildUiComponent(new uiVUMeter (this, zone, kLedWidth, kLedHeight, label, min, max, String(fUnit[zone]), String(fTooltip[zone]), Led, false));
    }
    
    /** Add a numerical display to the user interface. */
    void addNumericalDisplay(String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
        currentBox->addChildUiComponent(new uiVUMeter (this, zone, kNumDisplayWidth, kNumDisplayHeight, label, min, max, String(fUnit[zone]), String(fTooltip[zone]), NumDisplay, false));
    }
    
    /** Declare a metadata. */
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
        MetaDataUI::declare(zone, key, value);
    }

    /** Initialize the user interface, once buildUserINterface is done. */
    void init() {
        if(tabLayout) {
            tabs.init();
        } else {
            uiBaseComponent* tempComp = dynamic_cast<uiBox*> (getChildComponent(0)); // This is our main box
            tempComp->setRatio();
            tempComp->setBaseComponentSize(getLocalBounds());
            tempComp->setCompLookAndFeel(laf);
        }
    }

    /** Resize its child to match the new bounds */
    void resized() {
        if(tabLayout) {
            tabs.setBounds(getLocalBounds());
        } else {
            dynamic_cast<uiBox*> (getChildComponent(0))->setBaseComponentSize(getLocalBounds());
        }
    }

    /** 
     * \brief   Destructor.
     * \details Delete temporary box used in buildUserInterface logic 
     */
    ~JuceGUI() {
        delete currentBox;
        delete parentBox;
    }

    int order;          // Keep track of the progress in the buildUserInterface method.
    int radioGroup;     // In case of radio buttons.
    uiBox* currentBox;  // Current box used in buildUserInterface logic.
    uiBox* parentBox;   // Parent of the current box in the builduser interface logic.
    bool tabLayout = false;
    uiTabs tabs;        
    String tabName;
    ScopedPointer<LookAndFeel> laf = new CustomLookAndFeel();
};
