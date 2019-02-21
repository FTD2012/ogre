#ifndef _AnotherSampleBrowser_H_
#define _AnotherSampleBrowser_H_

#include "SampleContext.h"
#include "SamplePlugin.h"
#include "OgreTrays.h"
#include "OgreConfigFile.h"
#include "OgreTechnique.h"
#include "OgreArchiveManager.h"

#define ENABLE_SHADERS_CACHE 1

#ifdef OGRE_STATIC_LIB
#include "DefaultSamplesPlugin.h"
#   ifdef SAMPLES_INCLUDE_PLAYPEN
#   include "PlayPenTestPlugin.h"
#   endif
#endif

namespace OgreBites {
    class AnotherSampleBrowser;
}


namespace OgreBites {
    /*=============================================================================
       | The OGRE Sample Browser. Features a menu accessible from all samples,
       | dynamic configureation, resource reloading, node labeling, and more.
      =============================================================================*/
    class AnotherSampleBrowser : public SampleContext, public TrayListener {

    public:
        AnotherSampleBrowser(bool nograb = false, int startSampleIndex = -1);

    //     virtual void loadStartUpSample();
    //     virtual void runSampleByIndex(int idx);
    //     virtual void runSample(Sample* s);

    //     /*-----------------------------------------------------------------------------
    //       | Extends frameRenderingQueued to update tray manager and carousel(旋转木马).
    //       -----------------------------------------------------------------------------*/
    //     bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    //     /*-----------------------------------------------------------------------------
    //       | Handles confirmation dialog responses.
    //       -----------------------------------------------------------------------------*/
    //     virtual void yesNoDialogClose(const Ogre::DisplayString &question, bool yesHit);

    //     /*-----------------------------------------------------------------------------
    //       | Handles button widget events.
    //       -----------------------------------------------------------------------------*/
    //     virtual void buttonHit(Button *b);

    //     /*-----------------------------------------------------------------------------
    //       | Handles meun item selection changes.
    //       -----------------------------------------------------------------------------*/
    //     virtual void itemSelected(SelectMenu *menu);

    //     /*-----------------------------------------------------------------------------
    //       | Handles sample slider changes. 
    //       -----------------------------------------------------------------------------*/
    //     virtual void sliderMoved(Slider *slider);

        /*-----------------------------------------------------------------------------
          | Handles keypresses.
          -----------------------------------------------------------------------------*/
        virtual bool keyPressed(const KeyboardEvent &evt);

    //     /*-----------------------------------------------------------------------------
    //       | Extends pointerPressed to inject mouse press into tray manager, and to check
    //       | for thumbnail clicks, just because we can.
    //       -----------------------------------------------------------------------------*/
    //     virtual bool mousePressed(const MouseButtonEvent &evt);

    //     // convert and redirect
    //     virtual bool touchPressed(const TouchFingerEvent &evt);

    //     /*-----------------------------------------------------------------------------
    //       | Extends pointerReleased to inject mouse release into tray manager.
    //       -----------------------------------------------------------------------------*/
    //     virtual bool mouseReleased(const MouseButtonEvent &evt);

    //     // convert and redirect
    //     virtual bool touchReleased(const TouchFingerEvent &evt);

    //     /*-----------------------------------------------------------------------------
    //       | Extends pointerMoved to inject mouse position into tray manager, and checks
    //       | for mouse wheel movements to slide the carousel, because we can.
    //       -----------------------------------------------------------------------------*/
    //     virtual bool mouseMoved(const MouseMotionEvent& evt);

    //     // convert and redirect
    //     virtual bool touchMoved(const TouchFingerEvent& evt);

    //     /*-----------------------------------------------------------------------------
    //       | Mouse wheel scrolls the sample list.
    //       -----------------------------------------------------------------------------*/         
    //     virtual bool mouseWheelRolled(const MouseWheelEvent& evt);

    //     /*-----------------------------------------------------------------------------
    //       | Extends Resized to best fit meuns on screen. We basically move the
    //       | menu tray to the left for higher resolutions and move it to the center
    //       | for lower resolutions.
    //       -----------------------------------------------------------------------------*/
    //     virtual void windowResized(Ogre::RenderWindow *rw);

        /*-----------------------------------------------------------------------------
          | *Extends setup to create dummy scene and tray interface.
          -----------------------------------------------------------------------------*/
        virtual void setup();

     protected:
         /*-----------------------------------------------------------------------------
           | Overrides the default window title.
           -----------------------------------------------------------------------------*/
         virtual NativeWindowPair createWindow(const Ogre::String &name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams);

         /*-----------------------------------------------------------------------------
           | Initialises only the browser's resources and those most commonly used
           | by samples. This way, additional special content can be initialised by
           | the samples that use them, so startup time is unaffected.
           -----------------------------------------------------------------------------*/
         virtual void loadResources();

    //     /*-----------------------------------------------------------------------------
    //       | Loads sample plugins from a configuration file.
    //       -----------------------------------------------------------------------------*/
    //     virtual Sample* loadSamples();

    //     /*-----------------------------------------------------------------------------
    //       | Unloads any loaded sample plugins.
    //       -----------------------------------------------------------------------------*/
    //     virtual void unloadSamples();
    
         /*-----------------------------------------------------------------------------
           | Sets up main page for browsing samples.
           -----------------------------------------------------------------------------*/
         virtual void setupWidgets();
    
    //     /*-----------------------------------------------------------------------------
    //       | Populates home menus with loaded samples.
    //       -----------------------------------------------------------------------------*/
    //     virtual void populateSampleMenus();
    
    //     /*-----------------------------------------------------------------------------
    //       | Overrides to recover by last sample's index instead.
    //       -----------------------------------------------------------------------------*/
    //     virtual void recoverLastSample();

    //     /*-----------------------------------------------------------------------------
    //       | Extends reconfigure to save the view and the index of last sample run.
    //       -----------------------------------------------------------------------------*/
    //     virtual void reconfigure(const Ogre::String &renderer, Ogre::NameValuePairList &options);
    
    // public:
    //     /*-----------------------------------------------------------------------------
    //       | Extends shutdown to destroy dummy scene and tray interface.
    //       -----------------------------------------------------------------------------*/
    //     virtual void shutdown();
    
    // protected:
    //     /*-----------------------------------------------------------------------------
    //       | Extend to temporiarily hide a sample's overlays while in the pause menu.
    //       -----------------------------------------------------------------------------*/
    //     virtual void pauseCurrentSample();

    //     /*-----------------------------------------------------------------------------
    //       | Extend to unhide all of sample's temporarily hidden overlays.
    //       -----------------------------------------------------------------------------*/
    //     virtual void uppauseCurrentSample();

    //     /*-----------------------------------------------------------------------------
    //       | Get the name of the RTSS shader cache file.
    //       -----------------------------------------------------------------------------*/
    //     virtual Ogre::String getShaderCacheFileName();


        TrayManager* mTrayMgr;                      // SDK tray interface
        Ogre::StringVector mLoadedSamplePlugins;       // loaded sample plugins
        std::set<Ogre::String> mSampleCategories;      // sample categories
        SampleSet mLoadedSamples;                      // loaded samples
        SelectMenu* mCategoryMenu;                     // sample category select menu
        SelectMenu* mSampleMenu;                       // sample select menu
        Slider* mSampleSlider;                         // sample slider bar
        Label* mTitleLabel;                            // sample title label
        TextBox* mDescBox;                             // sample description box
        SelectMenu* mRendererMenu;                     // render system selection menu
        std::vector<Ogre::Overlay*> mHiddenOverlays;   // sample overlays hidden for pausing
        std::vector<Ogre::OverlayContainer*> mThumbs;  // sample thumbnails
        Ogre::Real mCarouselPlace;                     // current state of carousel
        int mLastViewTitle;                            // last sample title viewed
        int mLastViewCategory;                         // last sample category viewed
        int mLastSampleIndex;                          // index of last sample running
        int mStartSampleIndex;                         // directly starts the sample with the given index
    public:
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        SampleBrowserGestureView *mGestureView;
#endif
        bool mIsShuttingDown;
        bool mGrabInput;
    
    };




}






#endif //_AnotherSampleBrowser_H_
