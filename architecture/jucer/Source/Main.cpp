/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

MainContentComponent* createMainContentComponent();

//==============================================================================
class RectangleAudioAppApplication  : public JUCEApplication
{
public:
    //==============================================================================
    RectangleAudioAppApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
     */
    
    class myViewport : public Viewport
    {
    public:
        myViewport(String name, int w, int h, int rW, int rH): Viewport(name), minWidth(w), minHeight(h), recommendedWidth(rW), recommendedHeight(rH)
        {
            addAndMakeVisible(tooltipWindow);
        }
        
        virtual void resized() override {
            Viewport::resized();
            getBounds().getWidth() < minWidth ? ((minWidth < recommendedWidth) ? width = minWidth
                                                                               : width = recommendedWidth)
                                              : width = getBounds().getWidth();
            getBounds().getHeight() < minHeight ? ((minHeight < recommendedHeight) ? height = minHeight
                                                                                   : height = recommendedHeight)
                                                : height = getBounds().getHeight();
            
        #if JUCE_IOS || JUCE_ANDROID
            currentAreaChanged(width, height);
        #else
            getViewedComponent()->setBounds(Rectangle<int>(0, 0, width, height));
        #endif
        }
        
        void currentAreaChanged (int w, int h) {
            getViewedComponent()->setBounds(0, 0, jmax(getParentWidth(), w), jmax(getParentHeight(), h));
            setSize(getParentWidth(), getParentHeight());
        }
            
        private:
        int minWidth, minHeight;
        int recommendedWidth, recommendedHeight;
        int width, height;
        TooltipWindow tooltipWindow;
        int j = 0;
    };
    
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow (String name) : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            
            #if JUCE_IOS || JUCE_ANDROID
                setFullScreen(true);
            #endif
            
            MainContentComponent* fWindow = createMainContentComponent();
            int minWidth  = fWindow->getMinSize().getWidth();
            int minHeight = fWindow->getMinSize().getHeight();
            int recomWidth = fWindow->getRecommendedSize().getWidth();
            int recomHeight = fWindow->getRecommendedSize().getHeight();
            
            fViewport = new myViewport(name, minWidth, minHeight, recomWidth, recomHeight);
            fViewport->setViewedComponent(fWindow);
            fViewport->setSize(minWidth, minHeight);
            
            setContentOwned(fViewport, true);
            centreWithSize (getWidth(), getHeight());
            setResizable (true, false);
            setVisible(true);
        }
        
        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        ScopedPointer<myViewport> fViewport;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
    
private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (RectangleAudioAppApplication)
