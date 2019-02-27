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
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);
    
    // get a pointer to the already created root
    Ogre::Root *root = getRoot();
    scnMgr = root->createSceneManager();
    scnMgr->setDisplaySceneNodes(true);
    
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
    cam->setAutoAspectRatio(true);
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
    
    // add a button to the top-left tray
    OgreBites::Button *btn = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Click Meeeeeeeeeeeeeee");
    
    // add a text box
    OgreBites::TextBox *textBox = mTrayMgr->createTextBox(OgreBites::TL_CENTER, "MyTextBox", "MyTextBoxxxxxxxxoxxxxxxxxxxxxxxxxxxxxxxxxxx", 200, 5);
    
    // add a label
    OgreBites::Label *label = mTrayMgr->createLabel(OgreBites::TL_TOP, "MyLabel", "MyLabel");
    
    OgreBites::Separator *separator = mTrayMgr->createSeparator(OgreBites::TL_CENTER, "My Separator", 2000);
    
    mTrayMgr->getCursorRay(cam);
    OgreBites::TrayManager::screenToScene(cam, Ogre::Vector2(320, 240));
    

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
