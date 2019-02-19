
#ifndef __Instance_H__
#define __Instance_H__

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreTrays.h"

class Instance : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{

public:
    explicit Instance();
    virtual ~Instance() override;
    virtual void setup() override;
    
    virtual void buttonHit(OgreBites::Button *button) override;

public:
    virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) override {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
    
public:
    OgreBites::TrayManager *mTrayMgr;
    bool isShowBackDrop;
    
};
#endif
