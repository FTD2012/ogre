#include "Instance.h"
#include "OgreVolumeChunk.h"

Instance::Instance()
: isShowBackDrop(false)
{
    
}

Instance::~Instance() {
    delete mTrayMgr;
    mTrayMgr = nullptr;
}

void Instance::setup() {

   
}

void Instance::buttonHit(OgreBites::Button *button) {
    if (button->getName() == "MyButton") {
        Ogre::LogManager::getSingletonPtr()->logMessage("My Button Click!");
        if (isShowBackDrop) {
            mTrayMgr->hideBackdrop();
        } else {
            mTrayMgr->showBackdrop("SdkTrays/Shade");
        }
        isShowBackDrop = !isShowBackDrop;
    }
}
