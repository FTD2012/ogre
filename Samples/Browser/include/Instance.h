
#ifndef __Instance_H__
#define __Instance_H__

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreTrays.h"
#include "OgreCameraMan.h"

class Instance : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{ 

public:
    explicit Instance(bool isGrabInput = true);
    virtual ~Instance() override;
    virtual void setup() override;
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    virtual bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
    virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
    virtual void buttonHit(OgreBites::Button *button) override;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    
public:
    OgreBites::CameraMan *mCameraMan;
    Ogre::SceneManager *scnMgr;
    OgreBites::TrayManager *mTrayMgr;
    bool isShowBackDrop;
    
    
    bool mGrabInput;
    
};
#endif
