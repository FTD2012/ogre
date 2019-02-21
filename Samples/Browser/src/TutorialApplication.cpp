
#include "TutorialApplication.h"

TutorialApplication::TutorialApplication()
  : mTerrainGroup(0),
    mTerrainGlobals(0),
    mInfoLabel(0)
{
}

TutorialApplication::~TutorialApplication()
{
}

void TutorialApplication::setup()
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);
    
    // get a pointer to the already created root
    Ogre::Root *root = getRoot();
    scnMgr = root->createSceneManager();
    
    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    
    // ambient light
    scnMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    
    // camera
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
//    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 50, 140);
    
    // view port
    Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    
    // ninja entity
    Ogre::Entity *ninjaEntity = scnMgr->createEntity("ninja.mesh");
    ninjaEntity->setCastShadows(true);
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);
    
    // add tray manager
    /// TODO: ljm >>> move new operate to constructor
    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow(), this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_TOPRIGHT);
    //    mTrayMgr->hideCursor();
    addInputListener(mTrayMgr);
    scnMgr->addRenderQueueListener(getOverlaySystem());

    ////
    cam->setPosition(Ogre::Vector3(1683, 50, 2116));
    cam->lookAt(Ogre::Vector3(1963, 50, 1660));
    cam->setNearClipDistance(.1);
    
    bool infiniteClip =
    mRoot->getRenderSystem()->getCapabilities()->hasCapability(
                                                               Ogre::RSC_INFINITE_FAR_PLANE);
    
    if (infiniteClip)
        cam->setFarClipDistance(0);
    else
        cam->setFarClipDistance(50000);
    
    scnMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    
    Ogre::Vector3 lightDir(.55, -.3, .75);
    lightDir.normalise();
    
    Ogre::Light* light = scnMgr->createLight("TestLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightDir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(.4, .4, .4));
    
//    // Fog
//    Ogre::ColourValue fadeColour(.9, .9, .9);
//    getRenderWindow()->getViewport(0)->setBackgroundColour(fadeColour);
//
//    scnMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.002);
//
//    // Terrain
    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
                                                scnMgr,
                                                Ogre::Terrain::ALIGN_X_Z,
                                                513, 12000.0);
    mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

    configureTerrainDefaults(light);

    for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);

    mTerrainGroup->loadAllTerrains(true);

    if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

        while (ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            initBlendMaps(t);
        }
    }

    mTerrainGroup->freeTemporaryResources();

    // Sky Techniques
    // scnMgr->setSkyBox(true, "Examples/SpaceSkyBox", 300, false);
//    scnMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    // Ogre::Plane plane;
    // plane.d = 1000;
    // plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;

    // scnMgr->setSkyPlane(
    //   true, plane, "Examples/SpaceSkyPlane", 1500, 40, true, 1.5, 150, 150);



}

void TutorialApplication::createFrameListener()
{
  mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TerrainInfo", "", 350);
}

void TutorialApplication::shutdown()
{
  OGRE_DELETE mTerrainGroup;
  OGRE_DELETE mTerrainGlobals;
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    Instance::frameRenderingQueued(fe);
    return true;
  bool ret = Instance::frameRenderingQueued(fe);

  if (mTerrainGroup->isDerivedDataUpdateInProgress())
  {
    mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
    mInfoLabel->show();

    if (mTerrainsImported)
      mInfoLabel->setCaption("Building terrain...");
    else
      mInfoLabel->setCaption("Updating textures...");
  }
  else
  {
    mTrayMgr->removeWidgetFromTray(mInfoLabel);
    mInfoLabel->hide();

    if (mTerrainsImported)
    {
      mTerrainGroup->saveAllTerrains(true);
      mTerrainsImported = false;
    }
  }

  return ret;
}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
  img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  if (flipX)
    img.flipAroundY();
  if (flipY)
    img.flipAroundX();

}

void TutorialApplication::defineTerrain(long x, long y)
{
  Ogre::String filename = mTerrainGroup->generateFilename(x, y);

  bool exists =
    Ogre::ResourceGroupManager::getSingleton().resourceExists(
      mTerrainGroup->getResourceGroup(),
      filename);

  if (exists)
    mTerrainGroup->defineTerrain(x, y);
  else
  {
    Ogre::Image img;
    getTerrainImage(x % 2 != 0, y % 2 != 0, img);
    mTerrainGroup->defineTerrain(x, y, &img);

    mTerrainsImported = true;
  }
}

void TutorialApplication::initBlendMaps(Ogre::Terrain* terrain)
{
  Ogre::Real minHeight0 = 70;
  Ogre::Real fadeDist0 = 40;
  Ogre::Real minHeight1 = 70;
  Ogre::Real fadeDist1 = 15;

  Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
  Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

  float* pBlend0 = blendMap0->getBlendPointer();
  float* pBlend1 = blendMap1->getBlendPointer();

  for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
  {
    for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
    {
      Ogre::Real tx, ty;

      blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
      Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
      Ogre::Real val = (height - minHeight0) / fadeDist0;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend0++ = val;

      val = (height - minHeight1) / fadeDist1;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend1++ = val;
    }
  }

  blendMap0->dirty();
  blendMap1->dirty();
  blendMap0->update();
  blendMap1->update();

}

void TutorialApplication::configureTerrainDefaults(Ogre::Light* light)
{
  mTerrainGlobals->setMaxPixelError(8);
  mTerrainGlobals->setCompositeMapDistance(3000);

  mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
  mTerrainGlobals->setCompositeMapAmbient(scnMgr->getAmbientLight());
  mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

  Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
  importData.terrainSize = 513;
  importData.worldSize = 12000.0;
  importData.inputScale = 600;
  importData.minBatchSize = 33;
  importData.maxBatchSize = 65;

  importData.layerList.resize(3);
  importData.layerList[0].worldSize = 100;
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_diffusespecular.dds");
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_normalheight.dds");
  importData.layerList[1].worldSize = 30;
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_diffusespecular.dds");
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_normalheight.dds");
  importData.layerList[2].worldSize = 200;
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_diffusespecular.dds");
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_normalheight.dds");

}
