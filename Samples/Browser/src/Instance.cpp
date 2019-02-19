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
    
    // ambient light
    scnMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    scnMgr->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    
    // camera
    Ogre::Camera *cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    
    // camera scene node
    Ogre::SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(200, 300, 400);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
    camNode->attachObject(cam);
    
    // view port
    Ogre::Viewport *vp = getRenderWindow()->addViewport(cam);
    cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    
    // ninja entity
    Ogre::Entity *ninjaEntity = scnMgr->createEntity("ninja.mesh");
    ninjaEntity->setCastShadows(true);
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);
    
    // create plane mesh manually
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingletonPtr()->createPlane("ground", Ogre::RGN_DEFAULT, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    
    // create ground entity with plane mesh
    Ogre::Entity *groundEntity = scnMgr->createEntity("ground");
    groundEntity->setMaterialName("Examples/Rockwall");
    groundEntity->setCastShadows(false);
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    
    // add spot light
    Ogre::Light *spotLight = scnMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    
    Ogre::SceneNode *spotNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotNode->setDirection(-1, -1, 0);
    spotNode->setPosition(Ogre::Vector3(200, 200, 0));
    spotNode->attachObject(spotLight);
    
    
    // add direction light
    Ogre::Light *directionLight = scnMgr->createLight("DirectionLight");
    directionLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionLight->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0));
    directionLight->setSpecularColour(Ogre::ColourValue(0.4, 0, 0));
    
    Ogre::SceneNode *directionNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionNode->setDirection(0, -1, 1);
    directionNode->attachObject(directionLight);
    
    // add point light
    Ogre::Light *pointLight = scnMgr->createLight("PointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setDiffuseColour(0.3, 0.3, 0.3);
    pointLight->setSpecularColour(0.3, 0.3, 0.3);
    
    Ogre::SceneNode *pointNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    pointNode->setPosition(Ogre::Vector3(0, 150, 250));
    pointNode->attachObject(pointLight);
    
    
    
    
    
}
