#include "Instance.h"
#include "OgreVolumeChunk.h"

Instance::Instance(bool isGrabInput)
: isShowBackDrop(false)
, mGrabInput(isGrabInput)
{
    
}

Instance::~Instance() {
    delete mTrayMgr;
    mTrayMgr = nullptr;
}

void Instance::setup() {
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);
    
    // hide operator cursor
    if (mGrabInput) setWindowGrab();
    
    // get a pointer to the already created root
    Ogre::Root *root = getRoot();
    scnMgr = root->createSceneManager();
//    scnMgr->setDisplaySceneNodes(true);
    
    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    
    // ambient light
//    scnMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
//    scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    
    // camera
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 50, 140);
    
    // camera intrective
    mCameraMan = new OgreBites::CameraMan(camNode);
    
    // view port
    Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.1, 0.1, 0.1));
    cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    
//    // ninja entity
//    Ogre::Entity *ninjaEntity = scnMgr->createEntity("ninja.mesh");
//    ninjaEntity->setCastShadows(true);
//    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);
//
//    // plane
//    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
//    Ogre::MeshManager::getSingletonPtr()->createPlane("ground", Ogre::RGN_DEFAULT, plane, 500, 500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//    // ground1
//    Ogre::Entity *groundEntity = scnMgr->createEntity("ground");
//    groundEntity->setCastShadows(true);
//    groundEntity->setMaterialName("Examples/Rockwall");
//    Ogre::SceneNode *ground1Node = scnMgr->getRootSceneNode()->createChildSceneNode();
//    ground1Node->attachObject(groundEntity);
    
//     ground2
//    Ogre::Entity *groundEntity2 = scnMgr->createEntity("ground");
//    groundEntity2->setCastShadows(true);
//    groundEntity2->setMaterialName("Examples/Rockwall");
//    Ogre::SceneNode *ground2Node = scnMgr->getRootSceneNode()->createChildSceneNode();
//    ground2Node->setScale(0.1, 0.1, 0.1);
//    ground2Node->setPosition(0, 10, 0);
//    ground2Node->attachObject(groundEntity2);
    
    
    
//    // spot light
//    Ogre::Light *spotLight = scnMgr->createLight("SpotLight");
//    spotLight->setDiffuseColour(0, 0, 1.0);
//    spotLight->setSpecularColour(0, 0, 1.0);
//    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
//    Ogre::SceneNode *spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//    spotLight->setDirection(-1, -1, 0);
//    spotLight->setPosition(Ogre::Vector3(200, 200, 0));
//    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
//    spotLightNode->attachObject(spotLight);
    
//    // direction light
//    Ogre::Light *directionLight = scnMgr->createLight("DirectionLight");
//    directionLight->setType(Ogre::Light::LT_DIRECTIONAL);
//    directionLight->setDiffuseColour(0.4, 0, 0);
//    directionLight->setSpecularColour(0.4, 0, 0);
//    Ogre::SceneNode *directionLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//    directionLightNode->setDirection(0, -1, 1);
//    directionLightNode->attachObject(directionLight);
    
    
    //DemoManager.cpp
    Ogre::ManualObject* cube = scnMgr->createManualObject("cube");
    cube->begin("cubeMaterial");
    cube->position(-10, -10, -10);
    cube->colour(0.0, 0.0, 0.0);
    cube->position(10, -10, -10);
    cube->colour(1.0, 0.0, 0.0);
    cube->position(10, -10, 10);
    cube->colour(1.0, 0.0, 1.0);
    cube->position(-10, -10, 10);
    cube->colour(0.0, 0.0, 1.0);
    cube->position(-10, 10, -10);
    cube->colour(0.0, 1.0, 0.0);
    cube->position(10, 10, -10);
    cube->colour(1.0, 1.0, 0.0);
    cube->position(10, 10, 10);
    cube->colour(1.0, 1.0, 1.0);
    cube->position(-10, 10, 10);
    cube->colour(0.0, 1.0, 1.0);
    
    cube->triangle(0, 2, 1);
    cube->triangle(0, 2, 3);
    cube->triangle(3, 4, 0);
    cube->triangle(3, 7, 4);
    cube->triangle(4, 7, 6);
    cube->triangle(4, 6, 5);
    cube->triangle(5, 2, 1);
    cube->triangle(5, 6, 2);
    cube->triangle(0, 4, 1);
    cube->triangle(5, 1, 4);
    cube->triangle(3, 6, 7);
    cube->triangle(3, 2, 6);
    cube->end();
    
    Ogre::SceneNode *cubeNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    cubeNode->attachObject(cube);
    
    
    // add tray manager
    /// TODO: ljm >>> move new operate to constructor
//    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow(), this);
//    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
//    mTrayMgr->showLogo(OgreBites::TL_TOPRIGHT);
//    mTrayMgr->hideCursor();
//    addInputListener(mTrayMgr);
//    scnMgr->addRenderQueueListener(getOverlaySystem());
    



}

bool Instance::keyPressed(const OgreBites::KeyboardEvent& evt) {
    int key = evt.keysym.sym;
    
    if (key == 'h' || key == OgreBites::SDLK_F1)  {
        
    } else if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }
    
    mCameraMan->keyPressed(evt);
    return true;
}

bool Instance::keyReleased(const OgreBites::KeyboardEvent& evt) {
    int key = evt.keysym.sym;
    mCameraMan->keyReleased(evt);
    return true;
}

bool Instance::mouseMoved(const OgreBites::MouseMotionEvent& evt) {
    mCameraMan->mouseMoved(evt);
    return true;
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

bool Instance::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    OgreBites::ApplicationContext::frameRenderingQueued(evt);
    mCameraMan->frameRendered(evt);
    return true;
}
