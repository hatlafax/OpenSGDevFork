#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGBaseFunctions.h"
#include "OSGSpotLight.h"
#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGPerspectiveCamera.h"
#include "OSGGradientBackground.h"
#include "OSGSolidBackground.h"
#include "OSGRenderAction.h"
#include "OSGRenderAction.h"
#include "OSGImage.h"
#include "OSGSimpleMaterial.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTransform.h"
#include "OSGGroup.h"
#include "OSGTrackball.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"
#include "OSGVector.h"
#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"
#include "OSGNavigator.h"
#include "OSGShadowStage.h"
#include "OSGMatrixCamera.h"

OSG::SimpleSceneManagerRefPtr mgr;

OSG::GLUTWindowUnrecPtr gwin;
OSG::ShadowStageUnrecPtr svp;


OSG::NodeUnrecPtr rootNode;

OSG::PointLightUnrecPtr         _light1_core;
OSG::TransformUnrecPtr          _light1_trans;

OSG::SpotLightUnrecPtr          _light2_core;
OSG::TransformUnrecPtr          _light2_trans;

OSG::DirectionalLightUnrecPtr   _light3_core;
OSG::TransformUnrecPtr          _light3_trans;

OSG::TransformUnrecPtr _obj1_trans;
OSG::TransformUnrecPtr _dino1_trans, _dino2_trans, _dino3_trans, _dino4_trans;
OSG::TransformUnrecPtr _tree1_trans, _tree2_trans, _tree3_trans, _tree4_trans,
    _tree5_trans, _tree6_trans, _tree7_trans, _tree8_trans, _tree9_trans;

OSG::MatrixCameraUnrecPtr camera;
OSG::PerspectiveCameraUnrecPtr Pcamera;
OSG::NodeUnrecPtr cam_beacon;
OSG::TransformUnrecPtr cam_trans;
OSG::Vec3f camPos;
OSG::Vec3f camDir;

OSG::Navigator _navigator;
OSG::Int16 _lastx;
OSG::Int16 _lasty;
OSG::UInt16 _mousebuttons;

OSG::UInt32 frameCount;
OSG::Real32 fps = 0.0;
OSG::Real32 startTime2;

bool bAnim = false;

//FPS Counter
void startFpsCounter()
{
    startTime2 = OSG::getSystemTime();
}

void showFpsCounter()
{
    frameCount++;
    if(OSG::getSystemTime() - startTime2 >= 1.0)
    {
        printf("aktuelle FPS: %i\r", frameCount);
        frameCount = 0;
        startTime2 = OSG::getSystemTime();
    }
}



// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);
void print_help();
void print_state();

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    // OSG init
    OSG::osgInit(argc, argv);

    // GLUT init
    int                     winid = setupGLUT(&argc, argv);
    gwin = OSG::GLUTWindow::create();

    //Erstellen der ben�tigten Komponenten--------------------------------------

    rootNode = OSG::makeCoredNode<OSG::Group>();
    OSG::NodeUnrecPtr scene = OSG::makeCoredNode<OSG::Group>();

    // create lights

    // Point Light 1
    OSG::NodeUnrecPtr light1        = OSG::makeCoredNode<OSG::PointLight>(&_light1_core);
    OSG::NodeUnrecPtr light1_beacon = OSG::makeCoredNode<OSG::Transform >(&_light1_trans);
    _light1_trans->editMatrix().setTranslate(50.f, 50.f, 10.f);

    _light1_core->setAmbient(0.3f, 0.3f, 0.3f, 1.f);
    _light1_core->setDiffuse(0.8f, 0.8f, 0.8f, 1.f);
    _light1_core->setSpecular(0.0f, 0.0f, 0.0f, 1);
    _light1_core->setBeacon(light1_beacon);
    _light1_core->setOn(false);
    _light1_core->setShadowIntensity(0.8f);

    // Spot Light 2
    OSG::NodeUnrecPtr light2        = OSG::makeCoredNode<OSG::SpotLight>(&_light2_core);
    OSG::NodeUnrecPtr light2_beacon = OSG::makeCoredNode<OSG::Transform>(&_light2_trans);
    //_light2_trans->editMatrix().setTranslate(75.f, 0.f, 25.f);
    _light2_trans->editMatrix().setTranslate(250.f, -250.f, 300.f);
       
    _light2_core->setAmbient(0.3f, 0.3f, 0.3f, 1);
    _light2_core->setDiffuse(0.8f, 0.8f, 0.8f, 1);
    _light2_core->setSpecular(0.f, 0.f, 0.f, 1.f);
    _light2_core->setSpotCutOffDeg(40.0f);
    _light2_core->setSpotDirection(-0.85f, 0.85f,-1.f);
    _light2_core->setBeacon(light2_beacon);
    _light2_core->setShadowIntensity(0.7f);
    _light2_core->setOn(false);


    //Directional Light 3
    OSG::NodeUnrecPtr light3        = OSG::makeCoredNode<OSG::DirectionalLight>(&_light3_core);
    OSG::NodeUnrecPtr light3_beacon = OSG::makeCoredNode<OSG::Transform>(&_light3_trans);
    _light3_trans->editMatrix().setTranslate(0.f, 0.f, 0.f);
    _light3_core->setDirection(0.8f, 0.8f, 0.5f);
    _light3_core->setAmbient(0.15f, 0.15f, 0.15f, 1.f);
    _light3_core->setDiffuse(0.4f, 0.4f, 0.4f, 1.f);
    _light3_core->setSpecular(0.f, 0.f, 0.f, 1.f);
    _light3_core->setBeacon(light3_beacon);
    _light3_core->setShadowIntensity(0.7f);
    _light3_core->setOn(true);

    light1->addChild(light2);
    light2->addChild(light3);
    light3->addChild(scene);

    //Eigene Kamera erstellen
    Pcamera = OSG::PerspectiveCamera::create();
    cam_beacon = OSG::makeCoredNode<OSG::Transform>(&cam_trans);
    cam_trans->editMatrix().setTranslate(0.f, 0.f, 25.f);

    Pcamera->setBeacon(cam_beacon);
    Pcamera->setFov(OSG::osgDegree2Rad(60));
    Pcamera->setNear(1.0);
    Pcamera->setFar(1000);

    // create scene

    // bottom
    OSG::NodeUnrecPtr  plane = OSG::makePlane(300.0, 300.0, 256, 256);

    OSG::ImageUnrecPtr plane_img = OSG::Image::create();
    plane_img->read("Data/gras.jpg");

    OSG::TextureObjChunkUnrecPtr plane_tex_obj = OSG::TextureObjChunk::create();
    OSG::TextureEnvChunkUnrecPtr plane_tex_env = OSG::TextureEnvChunk::create();
    plane_tex_obj->setImage(plane_img);
    plane_tex_obj->setMinFilter(GL_LINEAR);
    plane_tex_obj->setMagFilter(GL_LINEAR);
    plane_tex_obj->setWrapS(GL_REPEAT);
    plane_tex_obj->setWrapT(GL_REPEAT);
    plane_tex_env->setEnvMode(GL_MODULATE);

    OSG::SimpleMaterialUnrecPtr       plane_mat = OSG::SimpleMaterial::create();
    plane_mat->setAmbient(OSG::Color3f(0.3f, 0.3f, 0.3f));
    plane_mat->setDiffuse(OSG::Color3f(1.0f, 1.0f, 1.0f));
    plane_mat->addChunk(plane_tex_obj);
    plane_mat->addChunk(plane_tex_env);

    OSG::Geometry* plane_geo = dynamic_cast<OSG::Geometry *>(plane->getCore());
    plane_geo->setMaterial(plane_mat);

    //load Tree Objects

    OSG::NodeUnrecPtr tree1_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree1_trans);
    OSG::NodeUnrecPtr tree2_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree2_trans);
    OSG::NodeUnrecPtr tree3_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree3_trans);
    OSG::NodeUnrecPtr tree4_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree4_trans);
    OSG::NodeUnrecPtr tree5_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree5_trans);
    OSG::NodeUnrecPtr tree6_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree6_trans);
    OSG::NodeUnrecPtr tree7_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree7_trans);
    OSG::NodeUnrecPtr tree8_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree8_trans);
    OSG::NodeUnrecPtr tree9_trans_node = OSG::makeCoredNode<OSG::Transform>(&_tree9_trans);

    _tree1_trans->editMatrix().setTranslate(-80.0, -80.0, 0.0);
    _tree1_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree2_trans->editMatrix().setTranslate(0.0, -80.0, 0.0);
    _tree2_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree3_trans->editMatrix().setTranslate(80.0, -80.0, 0.0);
    _tree3_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree4_trans->editMatrix().setTranslate(-80.0, 0.0, 0.0);
    _tree4_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree5_trans->editMatrix().setTranslate(0.0, 0.0, 0.0);
    _tree5_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree6_trans->editMatrix().setTranslate(80.0, 0.0, 0.0);
    _tree6_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree7_trans->editMatrix().setTranslate(-80.0, 80.0, 0.0);
    _tree7_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree8_trans->editMatrix().setTranslate(0.0, 80.0, 0.0);
    _tree8_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    _tree9_trans->editMatrix().setTranslate(80.0, 80.0, 0.0);
    _tree9_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    OSG::NodeUnrecPtr tree1 = OSG::SceneFileHandler::the()->read("Data/tree1.3ds");

//    NodeUnrecPtr tree1 = makeSphere(2, 2.0);

    tree1_trans_node->addChild(tree1);
    tree2_trans_node->addChild(cloneTree(tree1));
    tree3_trans_node->addChild(cloneTree(tree1));
    tree4_trans_node->addChild(cloneTree(tree1));
    tree5_trans_node->addChild(cloneTree(tree1));
    tree6_trans_node->addChild(cloneTree(tree1));
    tree7_trans_node->addChild(cloneTree(tree1));
    tree8_trans_node->addChild(cloneTree(tree1));
    tree9_trans_node->addChild(cloneTree(tree1));

    OSG::NodeUnrecPtr trees = OSG::makeCoredNode<OSG::Group>();

    trees->addChild(tree1_trans_node);
    trees->addChild(tree2_trans_node);
    trees->addChild(tree3_trans_node);
    trees->addChild(tree4_trans_node);
    trees->addChild(tree5_trans_node);
    trees->addChild(tree6_trans_node);
    trees->addChild(tree7_trans_node);
    trees->addChild(tree8_trans_node);
    trees->addChild(tree9_trans_node);

    //Load a Quad as Pointlight
    OSG::GeometryUnrecPtr boxGeo = OSG::makeBoxGeo(15, 15, 15, 1, 1, 1);
    OSG::NodeUnrecPtr     boxNode = OSG::Node::create();
    boxNode->setCore(boxGeo);

    OSG::SimpleMaterialUnrecPtr box_mat = OSG::SimpleMaterial::create();
    box_mat->setAmbient(OSG::Color3f(0.95f, 1.0f, 0.2f));
    box_mat->setDiffuse(OSG::Color3f(0.95f, 1.0f, 0.2f));

    boxGeo->setMaterial(box_mat);

    OSG::NodeUnrecPtr lightBoxTransNode = OSG::makeCoredNode<OSG::Transform>(&_obj1_trans);

    lightBoxTransNode->addChild(boxNode);

    //load Dino Objects

    OSG::NodeUnrecPtr dino1_trans_node = OSG::makeCoredNode<OSG::Transform>(&_dino1_trans);
    OSG::NodeUnrecPtr dino2_trans_node = OSG::makeCoredNode<OSG::Transform>(&_dino2_trans);
    OSG::NodeUnrecPtr dino3_trans_node = OSG::makeCoredNode<OSG::Transform>(&_dino3_trans);
    OSG::NodeUnrecPtr dino4_trans_node = OSG::makeCoredNode<OSG::Transform>(&_dino4_trans);

    _dino1_trans->editMatrix().setTranslate(-20.0, -20.0, 10.0);
    _dino1_trans->editMatrix().setScale(OSG::Vec3f(5.0, 5.0, 5.0));

    _dino2_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino2_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

    _dino3_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino3_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

    _dino4_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino4_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

    OSG::NodeUnrecPtr dino1 = OSG::SceneFileHandler::the()->read("Data/dinopet.3ds");

    dino1_trans_node->addChild(dino1);
    dino2_trans_node->addChild(cloneTree(dino1));
    dino3_trans_node->addChild(cloneTree(dino1));
    dino4_trans_node->addChild(cloneTree(dino1));

    OSG::NodeUnrecPtr dinos = OSG::makeCoredNode<OSG::Group>();

    dinos->addChild(dino1_trans_node);
    dinos->addChild(dino2_trans_node);
    dinos->addChild(dino3_trans_node);
    dinos->addChild(dino4_trans_node);

    //load Stone Objects

    OSG::TransformUnrecPtr _stone_trans1, _stone_trans2, _stone_trans3, _stone_trans4, _stone_trans5, _stone_trans6, _stone_trans7, _stone_trans8, _stone_trans9;
    OSG::NodeUnrecPtr stone_trans_node1 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans1);
    OSG::NodeUnrecPtr stone_trans_node2 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans2);
    OSG::NodeUnrecPtr stone_trans_node3 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans3);
    OSG::NodeUnrecPtr stone_trans_node4 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans4);
    OSG::NodeUnrecPtr stone_trans_node5 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans5);
    OSG::NodeUnrecPtr stone_trans_node6 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans6);
    OSG::NodeUnrecPtr stone_trans_node7 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans7);
    OSG::NodeUnrecPtr stone_trans_node8 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans8);
    OSG::NodeUnrecPtr stone_trans_node9 = OSG::makeCoredNode<OSG::Transform>(&_stone_trans9);

    _stone_trans1->editMatrix().setTranslate(-70,-70, 0);
    _stone_trans2->editMatrix().setTranslate( 10,-70, 0);
    _stone_trans3->editMatrix().setTranslate( 90,-70, 0);
    _stone_trans4->editMatrix().setTranslate(-70, 10, 0);
    _stone_trans5->editMatrix().setTranslate( 10, 10, 0);
    _stone_trans6->editMatrix().setTranslate( 90, 10, 0);
    _stone_trans7->editMatrix().setTranslate(-70, 90, 0);
    _stone_trans8->editMatrix().setTranslate( 10, 90, 0);
    _stone_trans9->editMatrix().setTranslate( 90, 90, 0);

    OSG::NodeUnrecPtr stone1 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone2 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone3 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone4 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone5 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone6 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone7 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone8 = OSG::makeSphere(1, 7.0);
    OSG::NodeUnrecPtr stone9 = OSG::makeSphere(1, 7.0);

    OSG::ImageUnrecPtr plane_img2 = OSG::Image::create();
    plane_img2->read("Data/stone.jpg");

    OSG::TextureObjChunkUnrecPtr plane_tex2_obj = OSG::TextureObjChunk::create();
    OSG::TextureEnvChunkUnrecPtr plane_tex2_env = OSG::TextureEnvChunk::create();
    plane_tex2_obj->setImage(plane_img2);
    plane_tex2_obj->setMinFilter(GL_LINEAR);
    plane_tex2_obj->setMagFilter(GL_LINEAR);
    plane_tex2_obj->setWrapS(GL_REPEAT);
    plane_tex2_obj->setWrapT(GL_REPEAT);
    plane_tex2_env->setEnvMode(GL_MODULATE);

    OSG::SimpleMaterialUnrecPtr plane_mat2 = OSG::SimpleMaterial::create();
    plane_mat2->setAmbient(OSG::Color3f(0.3f, 0.3f, 0.3f));
    plane_mat2->setDiffuse(OSG::Color3f(1.0f, 1.0f, 1.0f));
    plane_mat2->addChunk(plane_tex2_obj);
    plane_mat2->addChunk(plane_tex2_env);

    dynamic_cast<OSG::Geometry*>(stone1->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone2->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone3->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone4->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone5->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone6->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone7->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone8->getCore())->setMaterial(plane_mat2);
    dynamic_cast<OSG::Geometry*>(stone9->getCore())->setMaterial(plane_mat2);

    stone_trans_node1->addChild(stone1);
    stone_trans_node2->addChild(stone2);
    stone_trans_node3->addChild(stone3);
    stone_trans_node4->addChild(stone4);
    stone_trans_node5->addChild(stone5);
    stone_trans_node6->addChild(stone6);
    stone_trans_node7->addChild(stone7);
    stone_trans_node8->addChild(stone8);
    stone_trans_node9->addChild(stone9);

    OSG::NodeUnrecPtr stones = OSG::makeCoredNode<OSG::Group>();

    stones->addChild(stone_trans_node1);
    stones->addChild(stone_trans_node2);
    stones->addChild(stone_trans_node3);
    stones->addChild(stone_trans_node4);
    stones->addChild(stone_trans_node5);
    stones->addChild(stone_trans_node6);
    stones->addChild(stone_trans_node7);
    stones->addChild(stone_trans_node8);
    stones->addChild(stone_trans_node9);

    scene->addChild(plane);
    scene->addChild(lightBoxTransNode);
    scene->addChild(trees);
    scene->addChild(stones);
    scene->addChild(dinos);

    svp = OSG::ShadowStage::create();

    //svp->setShadowMode(OSG::ShadowStage::NO_SHADOW);
    svp->setShadowMode(OSG::ShadowStage::STD_SHADOW_MAP);
    //svp->setShadowMode(OSG::ShadowStage::PCF_SHADOW_MAP);

    svp->setBlitZBuffer(true);

    OSG::GradientBackgroundUnrecPtr gbg = OSG::GradientBackground::create();
    OSG::SolidBackgroundUnrecPtr    sbg = OSG::SolidBackground::create();

    gbg->addLine(OSG::Color3f(0.7f, 0.7f, 0.8f), 0);
    gbg->addLine(OSG::Color3f(0.0f, 0.1f, 0.3f), 1);

    rootNode->setCore(svp);

    rootNode->addChild(light1);
    rootNode->addChild(light1_beacon);
    rootNode->addChild(light2_beacon);
    rootNode->addChild(light3_beacon);
    rootNode->addChild(cam_beacon);

    // Shadow viewport
#ifdef SHADOW_CHECK
    svp->setBackground(gbg);
    svp->setRoot(rootNode);
    svp->setSize(0, 0, 1, 1);
#endif
    // svp->setOffFactor(4.0);
    // svp->setOffBias(8.0);
    // used to set global shadow intensity, ignores shadow intensity from light sources if != 0.0
    // svp->setGlobalShadowIntensity(0.8);
    svp->setMapSize(1024);
    // ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    // ShadowSmoothness also used to define the light size for PCSS_SHADOW_MAP
    svp->setShadowSmoothness(0.5);
    // add light sources here
    // svp->editMFLightNodes  ()->push_back(light1);
    // svp->editMFLightNodes  ()->push_back(light2);
    svp->editMFExcludeNodes()->push_back(lightBoxTransNode);  // light box should not generate a shadow!
    svp->setAutoSearchForLights(true);

    gwin->setGlutId(winid);
#ifdef SHADOW_CHECK
    gwin->addPort(svp);
#endif

    gwin->init();

    OSG::Vec3f min, max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds(min, max);

    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    mgr->setWindow(gwin);
    mgr->setCamera(Pcamera);
    mgr->setRoot(rootNode);

    _navigator.setMode(OSG::Navigator::TRACKBALL);

#ifdef SHADOW_CHECK
    _navigator.setViewport(svp);
#endif
    _navigator.setCameraTransformation(cam_beacon);


    OSG::Vec3f up(0,1,0);
    OSG::Pnt3f at(0,0,0);
    OSG::Pnt3f from(0.0f,-100.1f,20.0f);

    _navigator.set(from, at, up);

    _navigator.setMotionFactor(0.5f);

#ifdef SHADOW_CHECK
    svp->setCamera(Pcamera);
#endif

    // activate Framecounter
    startFpsCounter();

    // dynamic_cast<RenderAction *>(mgr->getAction())->setLocalLights(true);
    mgr->turnHeadlightOff();
    mgr->showAll();
    mgr->getCamera()->setNear(      1.0f);
    mgr->getCamera()->setFar (1000000.f );

    _navigator.setViewport(gwin->getPort(0));

    print_help();
    print_state();

    return 0;
}



int main(int argc, char **argv)
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

void Animate()
{
    //Show FPS
    //showFpsCounter();

    if(bAnim == true)
    {
        static OSG::Real64   t0 = OSG::getSystemTime();
        
        OSG::Real64          t = OSG::getSystemTime() - t0;
        
        OSG::Real32          rot0 = t * 0.25;
        if(rot0 > 360.0)
            rot0 -= 360.0;
        
        OSG::Real32          rota = t * 0.5;
        if(rota > 360.0)
            rota -= 360.0;
        
        OSG::Real32          rotb = t * 1.0;
        if(rotb > 360.0)
            rotb -= 360.0;
        
        OSG::Real32          rotc = t * 1.5;
        if(rotc > 360.0)
            rotc -= 360.0;
        
        OSG::Real32          rotd = t * 2.0;
        if(rotd > 360.0)
            rotd -= 360.0;
        
        //    _light2_trans->editMatrix().setTranslate(-100.0*sin(rota),-100.0*cos(rota), 250.0);
        
        //animate Trees
        OSG::Quaternion      q;
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rota));
        _tree1_trans->editMatrix().setRotate(q);
        _tree1_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree2_trans->editMatrix().setRotate(q);
        _tree2_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree3_trans->editMatrix().setRotate(q);
        _tree3_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree4_trans->editMatrix().setRotate(q);
        _tree4_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree5_trans->editMatrix().setRotate(q);
        _tree5_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree6_trans->editMatrix().setRotate(q);
        _tree6_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotd));
        _tree7_trans->editMatrix().setRotate(q);
        _tree7_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree8_trans->editMatrix().setRotate(q);
        _tree8_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree9_trans->editMatrix().setRotate(q);
        _tree9_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(0.15f,0.15f,0.15f);
            OSG::Vec3f   trans(-40.0 * sin(rotb),-40.0 * cos(rotb),
                          50.0 + 25.0 * sin(rotd));
            q.setValueAsAxisRad(0, 0, 1, -rotb);
            m.setTransform(trans, q, scale);
            _obj1_trans->setMatrix(m);
        }
        
        
        // {
        //     _light2_trans->editMatrix().setTranslate(-40.0 * sin(rotb), -40.0 *
        //                                              cos(rotb),
        //                                              50.0 + 25.0 * sin(rotd));
        // }
        
        //animate Dinos
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(5.0,5.0,5.0);
            OSG::Real32  ztrans1 = sin(2.0 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            OSG::Vec3f   trans(-96.0 * cos(rot0),-96.0 * sin(rot0),
                          10.0 + 8.0 * ztrans1);
            m.setScale(OSG::Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170);
            m.setTransform(trans, q, scale);
            _dino1_trans->setMatrix(m);
        }
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(3.0,3.0,3.0);
            OSG::Real32  ztrans1 = sin(2.5 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            OSG::Vec3f   trans(-96.0 * cos((rot0 - 0.5)),-96.0 * sin((rot0 - 0.5)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(OSG::Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 169.9);
            m.setTransform(trans, q, scale);
            _dino2_trans->setMatrix(m);
        }
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(3.0,3.0,3.0);
            OSG::Real32  ztrans1 = sin(3.0 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            OSG::Vec3f   trans(-96.0 * cos((rot0 - 0.8)),-96.0 * sin((rot0 - 0.8)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(OSG::Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
            m.setTransform(trans, q, scale);
            _dino3_trans->setMatrix(m);
        }
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(3.0,3.0,3.0);
            OSG::Real32  ztrans1 = sin(2.75 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            OSG::Vec3f   trans(-96.0 * cos((rot0 - 1.2)),-96.0 * sin((rot0 - 1.2)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(OSG::Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
            m.setTransform(trans, q, scale);
            _dino4_trans->setMatrix(m);
        }
    }

    _navigator.idle(_mousebuttons, _lastx, _lasty);
    mgr->redraw();
}

// redraw the window
void display(void)
{
    _navigator.updateCameraTransformation();
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if(state)
    {
        mgr->mouseButtonRelease(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonRelease(OSG::Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonRelease(OSG::Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonRelease(OSG::Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonRelease(OSG::Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonRelease(OSG::Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons &= ~(1 << button);
        _lastx = x;
        _lasty = y;
    }

    else
    {
        mgr->mouseButtonPress(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonPress(OSG::Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonPress(OSG::Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonPress(OSG::Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonPress(OSG::Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonPress(OSG::Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons |= 1 << button;
        _lastx = x;
        _lasty = y;
    }

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);

    if(_mousebuttons)
        _navigator.moveTo(x, y);
    _lastx = x;
    _lasty = y;

    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            {
                _navigator.setViewport(NULL);
                _navigator.setCameraTransformation(NULL);

                gwin         = NULL;
                svp          = NULL;

                rootNode      = NULL;
                _light1_core  = NULL;
                _light1_trans = NULL;

                _light2_core  = NULL;
                _light2_trans = NULL;

                _obj1_trans  = NULL;
                _dino1_trans = NULL;
                _dino2_trans = NULL;
                _dino3_trans = NULL;
                _dino4_trans = NULL;
                _tree1_trans = NULL;
                _tree2_trans = NULL;
                _tree3_trans = NULL;
                _tree4_trans = NULL;
                _tree5_trans = NULL;
                _tree6_trans = NULL;
                _tree7_trans = NULL;
                _tree8_trans = NULL;
                _tree9_trans = NULL;

                camera       = NULL;
                Pcamera      = NULL;
                cam_beacon   = NULL;
                cam_trans    = NULL;

                mgr          = NULL;

                OSG::osgExit();
                exit(0);
            }
            break;

        case '9':
           {
               _light1_core->setOn(!_light1_core->getOn());

               if(_light1_core->getOn() && _light2_core->getOn())
               {
                   _light1_core->setAmbient(0.15f, 0.15f, 0.15f, 1);
                   _light1_core->setDiffuse(0.4f, 0.4f, 0.4f, 1);

                   _light2_core->setAmbient(0.15f, 0.15f, 0.15f, 1);
                   _light2_core->setDiffuse(0.4f, 0.4f, 0.4f, 1);
               }
               else if(_light1_core->getOn())
               {
                   _light1_core->setAmbient(0.3f, 0.3f, 0.3f, 1);
                   _light1_core->setDiffuse(0.8f, 0.8f, 0.8f, 1);
               }

               std::cout << std::endl;
               std::cout << "'9'     Light 1 " << (_light1_core->getOn() ? "on " : "off") << ", type '" << _light1_core->getType().getName() << "'" << std::endl;
            }
           break;

        case '0':
            {
                _light2_core->setOn(!_light2_core->getOn());

                if(_light1_core->getOn() && _light2_core->getOn())
                {
                    _light1_core->setAmbient(0.15f, 0.15f, 0.15f, 1);
                    _light1_core->setDiffuse(0.4f, 0.4f, 0.4f, 1);

                    _light2_core->setAmbient(0.15f, 0.15f, 0.15f, 1);
                    _light2_core->setDiffuse(0.4f, 0.4f, 0.4f, 1);
                }
                else if(_light2_core->getOn())
                {
                    _light2_core->setAmbient(0.3f, 0.3f, 0.3f, 1);
                    _light2_core->setDiffuse(0.8f, 0.8f, 0.8f, 1);
                }

                std::cout << std::endl;
                std::cout << "'0'     Light 2 " << (_light2_core->getOn() ? "on " : "off") << ", type '" << _light2_core->getType().getName() << "'" << std::endl;
            }
            break;

        case 'w':
            {
                OSG::Real32  t = svp->getOffBias();

                svp->setOffBias((t + 0.2));
                std::cout << std::endl;
                std::cout << "'w'     Polygon-OffsetBias is  : " << svp->getOffBias  () << std::endl;
                break;
            }

        case 's':
            {
                OSG::Real32  t = svp->getOffBias();

                svp->setOffBias((t - 0.2));

                std::cout << std::endl;
                std::cout << "'s'     Polygon-OffsetBias is  : " << svp->getOffBias  () << std::endl;
                break;
            }

        case 'e':
            {
                OSG::Real32  t = svp->getOffFactor();

                svp->setOffFactor(++t);
                std::cout << std::endl;
                std::cout << "'e'     Polygon-OffsetFactor is: " << svp->getOffFactor() << std::endl;
                break;
            }

        case 'd':
            {
                OSG::Real32  t = svp->getOffFactor();

                svp->setOffFactor(--t);
                std::cout << std::endl;
                std::cout << "'d'     Polygon-OffsetFactor is: " << svp->getOffFactor() << std::endl;
                break;
            }
        case 'o':
            {
                bool    s = svp->getShadowOn();
                svp->setShadowOn(!s);
                std::cout << std::endl;
                std::cout << "'o'     Shadow stage on/off    : " << (svp->getShadowOn() ? "on" : "off") << std::endl;
                break;
            }
        case '1':
            {
                svp->setShadowMode(OSG::ShadowStage::NO_SHADOW);
                std::cout << std::endl;
                std::cout << "'1'     Shadow mode            : " << "NO_SHADOW" << std::endl;
                break;
            }

        case '2':
            {
                svp->setShadowMode(OSG::ShadowStage::STD_SHADOW_MAP);
                std::cout << std::endl;
                std::cout << "'2'     Shadow mode            : " << "STD_SHADOW_MAP" << std::endl;
                break;
            }

        case '3':
            {
                svp->setShadowMode(OSG::ShadowStage::PERSPECTIVE_SHADOW_MAP);
                std::cout << std::endl;
                std::cout << "'3'     Shadow mode            : " << "PERSPECTIVE_SHADOW_MAP" << std::endl;
                break;
            }

        case '4':
            {
                svp->setShadowMode(OSG::ShadowStage::DITHER_SHADOW_MAP);
                std::cout << std::endl;
                std::cout << "'4'     Shadow mode            : " << "DITHER_SHADOW_MAP" << std::endl;
                break;
            }

        case '5':
            {
                svp->setShadowMode(OSG::ShadowStage::PCF_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                std::cout << std::endl;
                std::cout << "'5'     Shadow mode            : " << "PCF_SHADOW_MAP" << std::endl;
                std::cout << "'5'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }

       case '6':
            {
                svp->setShadowMode(OSG::ShadowStage::PCF2_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                std::cout << std::endl;
                std::cout << "'6'     Shadow mode            : " << "PCF2_SHADOW_MAP" << std::endl;
                std::cout << "'6'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }

        case '7':
            {
                svp->setShadowMode(OSG::ShadowStage::PCSS_SHADOW_MAP);
                svp->setShadowSmoothness(1.0);
                std::cout << std::endl;
                std::cout << "'7'     Shadow mode            : " << "PCSS_SHADOW_MAP" << std::endl;
                std::cout << "'7'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }

        case '8':
            {
                svp->setShadowMode(OSG::ShadowStage::VARIANCE_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                std::cout << std::endl;
                std::cout << "'8'     Shadow mode            : " << "VARIANCE_SHADOW_MAP" << std::endl;
                std::cout << "'8'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }

        case 'y':
            {
                svp->setMapSize(512);
                std::cout << std::endl;
                std::cout << "'y'     Shadow map size is     : " << svp->getMapSize         () << std::endl;
                break;
            }

        case 'x':
            {
                svp->setMapSize(1024);
                std::cout << std::endl;
                std::cout << "'x'     Shadow map size is     : " << svp->getMapSize         () << std::endl;
                break;
            }

        case 'c':
            {
                svp->setMapSize(2048);
                std::cout << std::endl;
                std::cout << "'c'     Shadow map size is     : " << svp->getMapSize         () << std::endl;
                break;
            }

        case '+':
            {
                OSG::Real32  t = svp->getShadowSmoothness();

                svp->setShadowSmoothness(t + 0.1);
                std::cout << std::endl;
                std::cout << "'+'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }

        case '-':
            {
                OSG::Real32  t = svp->getShadowSmoothness();

                svp->setShadowSmoothness(t - 0.1);
                std::cout << std::endl;
                std::cout << "'-'     Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;
                break;
            }
        case 'a':
        {
            bAnim = !bAnim;
        }
        break;
        case 'b':
        {
            std::cout << std::endl;
            std::cout << "camera near value is           : " << mgr->getCamera()->getNear() << std::endl;
            std::cout << "camera far  value is           : " << mgr->getCamera()->getFar () << std::endl;
        }
        break;
        case '#':
        {
            print_state();
        }
        break;
        case 'h':
        {
            print_help();
        }
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Set WindowSize here
    glutInitWindowSize(640, 512);

    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}

void print_help()
{
    std::cout << std::endl;
    printf("NOTE: Real point lights only supported for shadow mode 1...6!\n");
    std::cout << std::endl;
    std::cout << "h  : print help" << std::endl;
    std::cout << "#  : print state" << std::endl;
    std::cout << "Esc: quit example" << std::endl;
    std::cout << "9  : toggle light source 1" << std::endl;
    std::cout << "0  : toggle light source 2" << std::endl;
    std::cout << "w  : increase bias" << std::endl;
    std::cout << "s  : decrease bias" << std::endl;
    std::cout << "e  : increase offset" << std::endl;
    std::cout << "d  : decrease offset" << std::endl;
    std::cout << "o  : toggle shadows globally" << std::endl;
    std::cout << "1  : shadow mode NO_SHADOW" << std::endl;
    std::cout << "2  : shadow mode STD_SHADOW_MAP" << std::endl;
    std::cout << "3  : shadow mode PERSPECTIVE_SHADOW_MAP" << std::endl;
    std::cout << "4  : shadow mode DITHER_SHADOW_MAP" << std::endl;
    std::cout << "5  : shadow mode PCF_SHADOW_MAP" << std::endl;
    std::cout << "6  : shadow mode PCF2_SHADOW_MAP" << std::endl;
    std::cout << "7  : shadow mode PCSS_SHADOW_MAP" << std::endl;
    std::cout << "8  : shadow mode VARIANCE_SHADOW_MAP" << std::endl;
    std::cout << "y  : shadow map size  512" << std::endl;
    std::cout << "x  : shadow map size 1024" << std::endl;
    std::cout << "c  : shadow map size 2048" << std::endl;
    std::cout << "+  : increase shadow smoothness" << std::endl;
    std::cout << "-  : decrease shadow smoothness" << std::endl;
    std::cout << "a  : toogle animation" << std::endl;
    std::cout << "b  : print camera Z" << std::endl;
    std::cout << std::endl;
}

void print_state()
{
    std::cout << std::endl;
    std::cout << "'9'     Light 1 " << (_light1_core->getOn() ? "on " : "off") << ", type '" << _light1_core->getType().getName() << "'" << std::endl;
    std::cout << "'0'     Light 2 " << (_light2_core->getOn() ? "on " : "off") << ", type '" << _light2_core->getType().getName() << "'" << std::endl;

    std::cout << "'w/s'   Polygon-OffsetBias is  : " << svp->getOffBias  () << std::endl;
    std::cout << "'e/d'   Polygon-OffsetFactor is: " << svp->getOffFactor() << std::endl;

    std::cout << "'o'     Shadow stage on/off    : " << (svp->getShadowOn() ? "on" : "off") << std::endl;

    switch (svp->getShadowMode()) 
    {
        case OSG::ShadowStage::NO_SHADOW:              std::cout << "'1-8'   Shadow mode            : " << "NO_SHADOW" << std::endl; break;
        case OSG::ShadowStage::STD_SHADOW_MAP:         std::cout << "'1-8'   Shadow mode            : " << "STD_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::PERSPECTIVE_SHADOW_MAP: std::cout << "'1-8'   Shadow mode            : " << "PERSPECTIVE_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::DITHER_SHADOW_MAP:      std::cout << "'1-8'   Shadow mode            : " << "DITHER_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::PCF_SHADOW_MAP:         std::cout << "'1-8'   Shadow mode            : " << "PCF_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::PCF2_SHADOW_MAP:        std::cout << "'1-8'   Shadow mode            : " << "PCF2_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::PCSS_SHADOW_MAP:        std::cout << "'1-8'   Shadow mode            : " << "PCSS_SHADOW_MAP" << std::endl; break;
        case OSG::ShadowStage::VARIANCE_SHADOW_MAP:    std::cout << "'1-8'   Shadow mode            : " << "VARIANCE_SHADOW_MAP" << std::endl; break;
    }

    std::cout << "'y/x/c' Shadow map size is     : " << svp->getMapSize         () << std::endl;
    std::cout << "'+/-'   Shadow smoothness is   : " << svp->getShadowSmoothness() << std::endl;

    std::cout << "camera near value is           : " << mgr->getCamera()->getNear() << std::endl;
    std::cout << "camera far  value is           : " << mgr->getCamera()->getFar () << std::endl;
}
