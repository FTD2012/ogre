#ifndef _TutorialApplication_H_
#define _TutorialApplication_H_

#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>

#include "Instance.h"

class TutorialApplication : public Instance
{
public:
  TutorialApplication();
  virtual ~TutorialApplication();

protected:
  virtual void setup() override;
  virtual void createFrameListener();
  virtual void shutdown() override;
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe) override;

private:
  void defineTerrain(long x, long y);
  void initBlendMaps(Ogre::Terrain* terrain);
  void configureTerrainDefaults(Ogre::Light* light);

  bool mTerrainsImported;
  Ogre::TerrainGroup* mTerrainGroup;
  Ogre::TerrainGlobalOptions* mTerrainGlobals;

  OgreBites::Label* mInfoLabel;

};

#endif // #ifndef __TutorialApplication_h_
