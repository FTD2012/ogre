#include "AnotherSampleBrowser.h"

namespace OgreBites
{
AnotherSampleBrowser::AnotherSampleBrowser(bool nograb, int startSampleIndex)
    : SampleContext("OGRE Just Another Sample Browser"), mGrabInput(!nograb)
{

    mIsShuttingDown = false;
    mTrayMgr = 0;
    mLastViewCategory = 0;
    mLastViewTitle = 0;
    mLastSampleIndex = -1;
    mStartSampleIndex = startSampleIndex;
    mCategoryMenu = 0;
    mSampleMenu = 0;
    mSampleSlider = 0;
    mTitleLabel = 0;
    mDescBox = 0;
    mRendererMenu = 0;
    mCarouselPlace = 0.0f;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    mGestureView = 0;
#endif
}

// void AnotherSampleBrowser::loadStartUpSample() {

// }

// void AnotherSampleBrowser::runSampleByIndex(int idx) {

// }

// void AnotherSampleBrowser::runSample(Sample* s) {

// }

// bool AnotherSampleBrowser::frameRenderingQueued(const Ogre::FrameEvent &evt) {
//     return true;
// }

// void AnotherSampleBrowser::yesNoDialogClose(const Ogre::DisplayString &question, bool yesHit) {

// }

// void AnotherSampleBrowser::buttonHit(Button *b) {

// }

// void AnotherSampleBrowser::itemSelected(SelectMenu *menu) {

// }

// void AnotherSampleBrowser::sliderMoved(Slider *slider) {

// }

bool AnotherSampleBrowser::keyPressed(const KeyboardEvent &evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}

// bool AnotherSampleBrowser::mousePressed(const MouseButtonEvent &evt) {
//     return true;
// }

// bool AnotherSampleBrowser::touchPressed(const TouchFingerEvent &evt) {
//     return true;
// }

// bool AnotherSampleBrowser::mouseReleased(const MouseButtonEvent &evt) {
//     return true;
// }

// bool AnotherSampleBrowser::touchReleased(const TouchFingerEvent &evt) {
//     return true;
// }

// bool AnotherSampleBrowser::mouseMoved(const MouseMotionEvent& evt) {
//     return true;
// }

// bool AnotherSampleBrowser::touchMoved(const TouchFingerEvent& evt) {
//     return true;
// }

// bool AnotherSampleBrowser::mouseWheelRolled(const MouseWheelEvent& evt) {
//     return true;
// }

// void AnotherSampleBrowser::windowResized(Ogre::RenderWindow *rw) {

// }

void AnotherSampleBrowser::setup()
{
    ApplicationContext::setup();
    mWindow = getRenderWindow();
    addInputListener(this);
    if (mGrabInput)
        setWindowGrab();

    setupWidgets();
}

 NativeWindowPair AnotherSampleBrowser::createWindow(const Ogre::String &name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams) {
     NativeWindowPair res = ApplicationContext::createWindow(name, w, h, miscParams);
     return res;
 }

 void AnotherSampleBrowser::loadResources() {
     Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
     mTrayMgr = new TrayManager("BrowserControls", getRenderWindow(), this);
//     mTrayMgr->showBackdrop("SdkTrays/Bands");
//     mTrayMgr->getTrayContainer(TL_NONE)->hide();

#if ENABLE_SHADERS_CACHE == 1
     enableShaderCache();
#endif
     // Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

     createDummyScene();
     getRoot()->getSceneManager("DummyScene")->setDisplaySceneNodes(true);

//     mTrayMgr->showLoadingBar(1, 0);
//     Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//     mTrayMgr->hideLoadingBar();
 }

// Sample* AnotherSampleBrowser::loadSamples() {

// }

// void AnotherSampleBrowser::unloadSamples() {

// }

void AnotherSampleBrowser::setupWidgets()
{
    mTrayMgr->destroyAllWidgets();

    // create main navigation tray
    mTrayMgr->showLogo(TL_RIGHT);
    mTrayMgr->hideCursor();
    
//    mTrayMgr->createSeparator(TL_RIGHT, "LogoSep");
//    mTrayMgr->createButton(TL_RIGHT, "StartStop", "Start Sample", 120);
//
//#if OGRE_PLATFORM != OGRE_PLATFORM_WINRT
//    mTrayMgr->createButton(TL_RIGHT, "UnloadReload", mLoadedSamples.empty() ? "Reload Samples" : "Unload Samples");
//    mTrayMgr->createButton(TL_RIGHT, "Configure", "Configure");
//#endif // OGRE_PLATFORM_WINRT
//    mTrayMgr->createButton(TL_RIGHT, "Quit", "Quit");
//
//    // create sample viewing controls
//    mTitleLabel = mTrayMgr->createLabel(TL_LEFT, "SampleTitle", "");
//#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
//    mDescBox = mTrayMgr->createTextBox(TL_LEFT, "SampleInfo", "Sample Info", 120, 100);
//    mCategoryMenu = mTrayMgr->createThickSelectMenu(TL_LEFT, "CategoryMenu", "Select Category", 120, 10);
//    mSampleMenu = mTrayMgr->createThickSelectMenu(TL_LEFT, "SampleMenu", "Select Sample", 120, 10);
//    mSampleSlider = mTrayMgr->createThickSlider(TL_LEFT, "SampleSlider", "Slide Samples", 120, 42, 0, 0, 0);
//#else
//    mDescBox = mTrayMgr->createTextBox(TL_LEFT, "SampleInfo", "Sample Info", 250, 208);
//    mCategoryMenu = mTrayMgr->createThickSelectMenu(TL_LEFT, "CategoryMenu", "Select Category", 250, 10);
//    mSampleMenu = mTrayMgr->createThickSelectMenu(TL_LEFT, "SampleMenu", "Select Sample", 250, 10);
//    mSampleSlider = mTrayMgr->createThickSlider(TL_LEFT, "SampleSlider", "Slide Samples", 250, 80, 0, 0, 0);
//#endif
//    /* Sliders do not notify their listeners on creation, so we manually call the callback here
//     to format the slider value correctly. */
//    sliderMoved(mSampleSlider);
//
//    // create configuration screen button tray
//    mTrayMgr->createButton(TL_NONE, "Apply", "Apply Changes");
//    mTrayMgr->createButton(TL_NONE, "Back", "Go Back");
//
//    // create configuration screen label and renderer menu
//    mTrayMgr->createLabel(TL_NONE, "ConfigLabel", "Configuration");
//#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID) || (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
//    mRendererMenu = mTrayMgr->createLongSelectMenu(TL_NONE, "RendererMenu", "Render System", 216, 115, 10);
//#else
//    mRendererMenu = mTrayMgr->createLongSelectMenu(TL_NONE, "RendererMenu", "Render System", 450, 240, 10);
//#endif
//    mTrayMgr->createSeparator(TL_NONE, "ConfigSeparator");
//
//    // populate render system names
//    Ogre::StringVector rsNames;
//    Ogre::RenderSystemList rsList = mRoot->getAvailableRenderers();
//    for (unsigned int i = 0; i < rsList.size(); i++)
//    {
//        rsNames.push_back(rsList[i]->getName());
//    }
//    mRendererMenu->setItems(rsNames);

    // populateSampleMenus();
}

// void AnotherSampleBrowser::populateSampleMenus() {

// }

// void AnotherSampleBrowser::recoverLastSample() {

// }

// void AnotherSampleBrowser::reconfigure(const Ogre::String &renderer, Ogre::NameValuePairList &options) {

// }

// void AnotherSampleBrowser::shutdown() {

// }

// void AnotherSampleBrowser::pauseCurrentSample() {

// }

// void AnotherSampleBrowser::uppauseCurrentSample() {

// }

// Ogre::String AnotherSampleBrowser::getShaderCacheFileName() {

// }

} // namespace OgreBites
