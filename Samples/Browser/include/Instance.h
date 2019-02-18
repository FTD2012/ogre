
#ifndef __Instance_H__
#define __Instance_H__

#include "Ogre.h"
#include "OgreApplicationContext.h"

class Instance : public OgreBites::ApplicationContext, public OgreBites::InputListener
{

  public:
    virtual void setup() override;

  public:
    virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
};
#endif
