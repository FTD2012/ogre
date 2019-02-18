#include "Instance.h"

void Instance::setup()
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root *root = getRoot();
    Ogre::SceneManager *scnMgr = root->createSceneManager();
    
    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    
    // set ambient light
    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    // add named light
    Ogre::Light *light = scnMgr->createLight("MainLight");
    Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    lightNode->setPosition(20, 80, 50);
    
    // add camera
    Ogre::Camera *cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    Ogre::SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);
    getRenderWindow()->addViewport(cam);
    
    // add first enity with default postion
    Ogre::Entity *ogreEntity = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode *ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
    ogreNode->attachObject(ogreEntity);
    
    // add second entity with prebuild position
    Ogre::Entity *ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode *ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 48, 0));
    ogreNode2->attachObject(ogreEntity2);
    
    // add third entity with scale
    Ogre::Entity *ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode *ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 104, 0));
    ogreNode3->setScale(2, 1.2, 1);
    ogreNode3->attachObject(ogreEntity3);
    
    // add forth entity with rotation
    Ogre::Entity *ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode *ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-84, 48, 0));
    ogreNode4->roll(Ogre::Degree(-90));
    ogreNode4->attachObject(ogreEntity4);
    
    camNode->setPosition(0, 47, 222);
    
}
