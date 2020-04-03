// OpenSG Example: MultiLightShadowStage
//
// This examples shows the usage of the MultiLightShadowStage that works with the 
// MulitLightChunk class.
//

#include <boost/foreach.hpp>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new headers: 
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGGradientBackground.h>
#include <OSGSolidBackground.h>
#include <OSGRenderAction.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTrackball.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>
#include <OSGSceneFileHandler.h>
#include <OSGNavigator.h>
#include <OSGMatrixCamera.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGShaderVariableOSG.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>
#include <OSGSimpleShadowMapEngine.h>
#include <OSGShaderShadowMapEngine.h>
#include <OSGTrapezoidalShadowMapEngine.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 
#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTrackball.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGNavigator.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGSimpleShadowMapEngine.h>
#include <OpenSG/OSGShaderShadowMapEngine.h>
#include <OpenSG/OSGTrapezoidalShadowMapEngine.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#endif

OSG::SimpleSceneManagerRefPtr mgr;

OSG::GLUTWindowRefPtr gwin;

OSG::PointLightRefPtr       light1;
OSG::SpotLightRefPtr        light2;
OSG::DirectionalLightRefPtr light3;
OSG::DirectionalLightRefPtr light4;

OSG::NodeRefPtr light1Node;
OSG::NodeRefPtr light2Node;
OSG::NodeRefPtr light3Node;
OSG::NodeRefPtr light4Node;

OSG::ChunkMaterialRefPtr prog_state;
OSG::ShaderProgramChunkRefPtr prog_chunk;

OSG::NodeRefPtr materialNode;

OSG::TransformRefPtr  light1_trans;
OSG::TransformRefPtr  light2_trans;
OSG::TransformRefPtr  light3_trans;
OSG::TransformRefPtr  light4_trans;

OSG::TransformRefPtr obj1_trans;
OSG::TransformRefPtr dino1_trans, dino2_trans, dino3_trans, dino4_trans;
OSG::TransformRefPtr tree1_trans, tree2_trans, tree3_trans, tree4_trans, tree5_trans, tree6_trans, tree7_trans, tree8_trans, tree9_trans;

OSG::MatrixCameraRefPtr camera;
OSG::PerspectiveCameraRefPtr perspective_camera;
OSG::NodeRefPtr cam_beacon;
OSG::TransformRefPtr cam_trans;
OSG::Vec3f camPos;
OSG::Vec3f camDir;

OSG::Navigator navigator;
OSG::Int16     lastx;
OSG::Int16     lasty;
OSG::UInt16    mousebuttons;

OSG::UInt32 frameCount;
OSG::Real32 fps = 0.0;
OSG::Real32 startTime2;

bool bAnim = false;

std::string get_vp_program();
std::string get_fp_program();

const OSG::Int32 geom_tex_binding_pnt = 7;

/*----- create_and_exe_dot_file ---------------------------------------------*/

//#define CREATE_AND_EXE_DOT_FILE

#include <boost/filesystem.hpp>

#ifdef OSG_BUILD_ACTIVE
#include <OSGDotFileGeneratorGraphOp.h>
#else
#include <OpenSG/OSGDotFileGeneratorGraphOp.h>
#endif

const char* graphviz_dot_executale = "d:/_xxx/Utils/Graphviz/bin/dot.exe";
const char* graphviz_output_file   = "d:/out.dot";

void create_and_exe_dot_file(OSG::Node* node)
{
#ifdef CREATE_AND_EXE_DOT_FILE
    using namespace OSG;

    namespace fs = ::boost::filesystem;

    fs::path dot_file(graphviz_output_file); dot_file.replace_extension(".dot");
    fs::path png_file(graphviz_output_file); png_file.replace_extension(".png");

    if (fs::exists(dot_file))
        fs::remove(dot_file);

    if (fs::exists(png_file))
        fs::remove(png_file);

    DotFileGeneratorGraphOpRefPtr go = DotFileGeneratorGraphOp::create();

    std::string param("filename=");
    go->setParams(param + dot_file.string());
    go->setParams("max_node_children=10 no_name_attachments=true no_ranks=true no_addresses=false");

    go->traverse(node);

    go = NULL;

    if (!fs::exists(dot_file))
        return;

    fs::path exe_file(graphviz_dot_executale);
    if (!fs::exists(exe_file))
        return;

    std::string cmd = exe_file.string();
    cmd += " -T png " + dot_file.string() + " -o " + png_file.string();

    system(cmd.c_str()) ;
#endif // CREATE_AND_EXE_DOT_FILE
}

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
    int winid = setupGLUT(&argc, argv);
    gwin = OSG::GLUTWindow::create();

    OSG::NodeUnrecPtr rootNode = OSG::makeNodeFor(OSG::Group::create());

    // Setup the scene
    OSG::NodeRefPtr light1_beacon = OSG::makeCoredNode<OSG::Transform>(&light1_trans);
    OSG::NodeRefPtr light2_beacon = OSG::makeCoredNode<OSG::Transform>(&light2_trans);
    OSG::NodeRefPtr light3_beacon = OSG::makeCoredNode<OSG::Transform>(&light3_trans);
    OSG::NodeRefPtr light4_beacon = OSG::makeCoredNode<OSG::Transform>(&light4_trans);

    light1 = OSG::PointLight::create();
    light1->setAmbient (0.3f, 0.3f, 0.3f, 1.f);
    light1->setDiffuse (0.8f, 0.8f, 0.8f, 1.f);
    light1->setSpecular(0.0f, 0.0f, 0.0f, 1.f);
    light1->setBeacon(light1_beacon);
    light1->setOn(false);
    light1->setShadowIntensity(0.8f);

    OSG::ShaderShadowMapEngineRefPtr ssme1 = OSG::ShaderShadowMapEngine::create();
    ssme1->setWidth (1024);
    ssme1->setHeight(1024);
    //ssme1->setOffsetBias(6.f);
    //ssme1->setOffsetFactor(4.f);
    ssme1->setEnabled(true);

    light1->setLightEngine(ssme1);


    light2 = OSG::SpotLight::create();
    light2->setSpotDirection(0.f, -7.f, -3.f);
    light2->setSpotCutOffDeg(45.0f);
    light2->setAmbient (0.3f, 0.3f, 0.3f, 1.f);
    light2->setDiffuse (0.8f, 0.8f, 0.8f, 1.f);
    light2->setSpecular(0.0f, 0.0f, 0.0f, 1.f);
    light2->setBeacon(light2_beacon);
    light2->setOn(true);
    light2->setShadowIntensity( 0.7f);

    OSG::ShaderShadowMapEngineRefPtr ssme2 = OSG::ShaderShadowMapEngine::create();
    ssme2->setWidth (1024);
    ssme2->setHeight(1024);
    //ssme2->setOffsetBias(6.f);
    //ssme2->setOffsetFactor(4.f);
    ssme2->setEnabled(true);

    light2->setLightEngine(ssme2);


    light3 = OSG::DirectionalLight::create();
    light3->setDirection(-OSG::Vec3f(0.8f, 0.8f, 0.5f)); //(*)
    light3->setAmbient (0.15f, 0.15f, 0.15f, 1.f);
    light3->setDiffuse (0.4f, 0.4f, 0.4f, 1.f);
    light3->setSpecular(0.0f, 0.0f, 0.0f, 1.f);
    light3->setBeacon(light3_beacon);
    light3->setOn(false);
    light3->setShadowIntensity( 0.7f);

    OSG::ShaderShadowMapEngineRefPtr ssme3 = OSG::ShaderShadowMapEngine::create();
    ssme3->setWidth (1024);
    ssme3->setHeight(1024);
    //ssme3->setOffsetBias(6.f);
    //ssme3->setOffsetFactor(4.f);
    ssme3->setEnabled(false);

    light3->setLightEngine(ssme3);

    light4 = OSG::DirectionalLight::create();
    light4->setDirection(OSG::Vec3f(-0.85f, 0.85f,-1.f));
    light4->setAmbient (0.3f, 0.3f, 0.3f, 1.f);
    light4->setDiffuse (0.8f, 0.8f, 0.8f, 1.f);
    light4->setSpecular(0.0f, 0.0f, 0.0f, 1.f);
    light4->setBeacon(light4_beacon);
    light4->setOn(false);
    light4->setShadowIntensity( 0.7f);

    light1_trans->editMatrix().setTranslate( 50.f,  50.f,  10.f);
    light2_trans->editMatrix().setTranslate(0.f, 7.f, 3.f);
    light3_trans->editMatrix().setTranslate(  0.f,   0.f,   0.f);
    light4_trans->editMatrix().setTranslate(  0.f,   0.f,   0.f);

    light1Node = OSG::makeNodeFor(light1);
    light2Node = OSG::makeNodeFor(light2);
    light3Node = OSG::makeNodeFor(light3);
    light4Node = OSG::makeNodeFor(light4);

      rootNode->addChild(light1Node);
    light1Node->addChild(light2Node);
    light2Node->addChild(light3Node);
    light3Node->addChild(light4Node);

    rootNode->addChild(light1_beacon);
    rootNode->addChild(light2_beacon);
    rootNode->addChild(light3_beacon);
    rootNode->addChild(light4_beacon);
    rootNode->addChild(cam_beacon);

    
    
    //
    // The shader program is globally added by an material chunk override group
    //
                                  prog_chunk = OSG::ShaderProgramChunk::create();
    OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
    OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

    vertShader->setProgram(get_vp_program());
    fragShader->setProgram(get_fp_program());

    fragShader->addOSGVariable("OSGLight0Active");
    fragShader->addOSGVariable("OSGLight1Active");
    fragShader->addOSGVariable("OSGLight2Active");
    fragShader->addOSGVariable("OSGLight3Active");
    fragShader->addOSGVariable("OSGLight4Active");
    fragShader->addOSGVariable("OSGLight5Active");
    fragShader->addOSGVariable("OSGLight6Active");
    fragShader->addOSGVariable("OSGLight7Active");

    prog_chunk->addShader(vertShader);
    prog_chunk->addShader(fragShader);

    OSG::ShaderProgramVariableChunkRefPtr no_tex_var_chunk = OSG::ShaderProgramVariableChunk::create();
    no_tex_var_chunk->addUniformVariable("uHasTexture", false);

    prog_state = OSG::ChunkMaterial::create();
    prog_state->addChunk(prog_chunk);
    prog_state->addChunk(no_tex_var_chunk);

    OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
    mgrp->setMaterial(prog_state);

    materialNode = OSG::makeNodeFor(mgrp);
    //materialNode = OSG::makeCoredNode<OSG::Group>();

    OSG::NodeUnrecPtr scene = OSG::makeCoredNode<OSG::Group>();

    //Eigene Kamera erstellen
    perspective_camera = OSG::PerspectiveCamera::create();
    cam_beacon = OSG::makeCoredNode<OSG::Transform>(&cam_trans);
    cam_trans->editMatrix().setTranslate(0.f, 0.f, 25.f);

    perspective_camera->setBeacon(cam_beacon);
    perspective_camera->setFov(OSG::osgDegree2Rad(60));
    perspective_camera->setNear(1.0);
    perspective_camera->setFar(1000);

    // create scene

    // bottom
    OSG::NodeUnrecPtr plane = OSG::makePlane(300.0, 300.0, 256, 256);

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

    OSG::ShaderProgramVariableChunkRefPtr plane_var_chunk = OSG::ShaderProgramVariableChunk::create();
    plane_var_chunk->addUniformVariable("uHasTexture", true);
    plane_var_chunk->addUniformVariable("uGeomTex", geom_tex_binding_pnt);

    OSG::SimpleMaterialUnrecPtr plane_mat = OSG::SimpleMaterial::create();
    plane_mat->setAmbient(OSG::Color3f(0.3f, 0.3f, 0.3f));
    plane_mat->setDiffuse(OSG::Color3f(1.0f, 1.0f, 1.0f));
    plane_mat->addChunk(plane_tex_obj, geom_tex_binding_pnt);
    plane_mat->addChunk(plane_tex_env, geom_tex_binding_pnt);
    plane_mat->addChunk(plane_var_chunk);

    OSG::Geometry* plane_geo = dynamic_cast<OSG::Geometry *>(plane->getCore());
    plane_geo->setMaterial(plane_mat);

    //load Tree Objects

    OSG::NodeUnrecPtr tree1_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree1_trans);
    OSG::NodeUnrecPtr tree2_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree2_trans);
    OSG::NodeUnrecPtr tree3_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree3_trans);
    OSG::NodeUnrecPtr tree4_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree4_trans);
    OSG::NodeUnrecPtr tree5_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree5_trans);
    OSG::NodeUnrecPtr tree6_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree6_trans);
    OSG::NodeUnrecPtr tree7_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree7_trans);
    OSG::NodeUnrecPtr tree8_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree8_trans);
    OSG::NodeUnrecPtr tree9_trans_node = OSG::makeCoredNode<OSG::Transform>(&tree9_trans);

    tree1_trans->editMatrix().setTranslate(-80.0, -80.0, 0.0);
    tree1_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree2_trans->editMatrix().setTranslate(0.0, -80.0, 0.0);
    tree2_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree3_trans->editMatrix().setTranslate(80.0, -80.0, 0.0);
    tree3_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree4_trans->editMatrix().setTranslate(-80.0, 0.0, 0.0);
    tree4_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree5_trans->editMatrix().setTranslate(0.0, 0.0, 0.0);
    tree5_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree6_trans->editMatrix().setTranslate(80.0, 0.0, 0.0);
    tree6_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree7_trans->editMatrix().setTranslate(-80.0, 80.0, 0.0);
    tree7_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree8_trans->editMatrix().setTranslate(0.0, 80.0, 0.0);
    tree8_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

    tree9_trans->editMatrix().setTranslate(80.0, 80.0, 0.0);
    tree9_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));

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

    OSG::NodeUnrecPtr lightBoxTransNode = OSG::makeCoredNode<OSG::Transform>(&obj1_trans);

    lightBoxTransNode->addChild(boxNode);

    //load Dino Objects

    OSG::NodeUnrecPtr dino1_trans_node = OSG::makeCoredNode<OSG::Transform>(&dino1_trans);
    OSG::NodeUnrecPtr dino2_trans_node = OSG::makeCoredNode<OSG::Transform>(&dino2_trans);
    OSG::NodeUnrecPtr dino3_trans_node = OSG::makeCoredNode<OSG::Transform>(&dino3_trans);
    OSG::NodeUnrecPtr dino4_trans_node = OSG::makeCoredNode<OSG::Transform>(&dino4_trans);

    dino1_trans->editMatrix().setTranslate(-20.0, -20.0, 10.0);
    dino1_trans->editMatrix().setScale(OSG::Vec3f(5.0, 5.0, 5.0));

    dino2_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    dino2_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

    dino3_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    dino3_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

    dino4_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    dino4_trans->editMatrix().setScale(OSG::Vec3f(3.0, 3.0, 3.0));

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

    OSG::TransformUnrecPtr stone_trans1, stone_trans2, stone_trans3, stone_trans4, stone_trans5, stone_trans6, stone_trans7, stone_trans8, stone_trans9;
    OSG::NodeUnrecPtr stone_trans_node1 = OSG::makeCoredNode<OSG::Transform>(&stone_trans1);
    OSG::NodeUnrecPtr stone_trans_node2 = OSG::makeCoredNode<OSG::Transform>(&stone_trans2);
    OSG::NodeUnrecPtr stone_trans_node3 = OSG::makeCoredNode<OSG::Transform>(&stone_trans3);
    OSG::NodeUnrecPtr stone_trans_node4 = OSG::makeCoredNode<OSG::Transform>(&stone_trans4);
    OSG::NodeUnrecPtr stone_trans_node5 = OSG::makeCoredNode<OSG::Transform>(&stone_trans5);
    OSG::NodeUnrecPtr stone_trans_node6 = OSG::makeCoredNode<OSG::Transform>(&stone_trans6);
    OSG::NodeUnrecPtr stone_trans_node7 = OSG::makeCoredNode<OSG::Transform>(&stone_trans7);
    OSG::NodeUnrecPtr stone_trans_node8 = OSG::makeCoredNode<OSG::Transform>(&stone_trans8);
    OSG::NodeUnrecPtr stone_trans_node9 = OSG::makeCoredNode<OSG::Transform>(&stone_trans9);

    stone_trans1->editMatrix().setTranslate(-70,-70, 0);
    stone_trans2->editMatrix().setTranslate( 10,-70, 0);
    stone_trans3->editMatrix().setTranslate( 90,-70, 0);
    stone_trans4->editMatrix().setTranslate(-70, 10, 0);
    stone_trans5->editMatrix().setTranslate( 10, 10, 0);
    stone_trans6->editMatrix().setTranslate( 90, 10, 0);
    stone_trans7->editMatrix().setTranslate(-70, 90, 0);
    stone_trans8->editMatrix().setTranslate( 10, 90, 0);
    stone_trans9->editMatrix().setTranslate( 90, 90, 0);

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

    OSG::ShaderProgramVariableChunkRefPtr plane_var2_chunk = OSG::ShaderProgramVariableChunk::create();
    plane_var2_chunk->addUniformVariable("uHasTexture", true);
    plane_var2_chunk->addUniformVariable("uGeomTex", geom_tex_binding_pnt);

    OSG::SimpleMaterialUnrecPtr plane_mat2 = OSG::SimpleMaterial::create();
    plane_mat2->setAmbient(OSG::Color3f(0.3f, 0.3f, 0.3f));
    plane_mat2->setDiffuse(OSG::Color3f(1.0f, 1.0f, 1.0f));
    plane_mat2->addChunk(plane_tex2_obj, geom_tex_binding_pnt);
    plane_mat2->addChunk(plane_tex2_env, geom_tex_binding_pnt);
    plane_mat2->addChunk(plane_var2_chunk);

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

    OSG::GradientBackgroundUnrecPtr gbg = OSG::GradientBackground::create();
    OSG::SolidBackgroundUnrecPtr    sbg = OSG::SolidBackground::create();

    gbg->addLine(OSG::Color3f(0.7f, 0.7f, 0.8f), 0);
    gbg->addLine(OSG::Color3f(0.0f, 0.1f, 0.3f), 1);

    light4Node->addChild(materialNode);

    materialNode->addChild(scene);

    gwin->setGlutId(winid);

    gwin->init();

    OSG::Vec3f min, max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds(min, max);

    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    mgr->setWindow(gwin);
    mgr->setCamera(perspective_camera);
    mgr->setRoot(rootNode);

    navigator.setMode(OSG::Navigator::TRACKBALL);
    navigator.setCameraTransformation(cam_beacon);

    OSG::Vec3f up(0,1,0);
    OSG::Pnt3f at(0,0,0);
    OSG::Pnt3f from(0.0f,-100.1f,20.0f);

    navigator.set(from, at, up);
    navigator.setMotionFactor(0.5f);

    // activate Framecounter
    startFpsCounter();

    // dynamic_cast<RenderAction *>(mgr->getAction())->setLocalLights(true);
    mgr->turnHeadlightOff();
    mgr->showAll();
    mgr->getCamera()->setNear(      1.0f);
    mgr->getCamera()->setFar (1000000.f );

    navigator.setViewport(gwin->getPort(0));

    print_help();
    print_state();

    create_and_exe_dot_file(mgr->getRoot());

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
        
        //    light2_trans->editMatrix().setTranslate(-100.0*sin(rota),-100.0*cos(rota), 250.0);
        
        //animate Trees
        OSG::Quaternion      q;
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rota));
        tree1_trans->editMatrix().setRotate(q);
        tree1_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        tree2_trans->editMatrix().setRotate(q);
        tree2_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        tree3_trans->editMatrix().setRotate(q);
        tree3_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        tree4_trans->editMatrix().setRotate(q);
        tree4_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        tree5_trans->editMatrix().setRotate(q);
        tree5_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        tree6_trans->editMatrix().setRotate(q);
        tree6_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotd));
        tree7_trans->editMatrix().setRotate(q);
        tree7_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        tree8_trans->editMatrix().setRotate(q);
        tree8_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        tree9_trans->editMatrix().setRotate(q);
        tree9_trans->editMatrix().setScale(OSG::Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        {
            OSG::Matrix  m;
            m.setIdentity();
            OSG::Vec3f   scale(0.15f,0.15f,0.15f);
            OSG::Vec3f   trans(-40.0 * sin(rotb),-40.0 * cos(rotb),
                          50.0 + 25.0 * sin(rotd));
            q.setValueAsAxisRad(0, 0, 1, -rotb);
            m.setTransform(trans, q, scale);
            obj1_trans->setMatrix(m);
        }
        
        
        // {
        //     light2_trans->editMatrix().setTranslate(-40.0 * sin(rotb), -40.0 *
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
            dino1_trans->setMatrix(m);
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
            dino2_trans->setMatrix(m);
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
            dino3_trans->setMatrix(m);
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
            dino4_trans->setMatrix(m);
        }
    }

    navigator.idle(mousebuttons, lastx, lasty);
    mgr->redraw();
}

// redraw the window
void display(void)
{
    navigator.updateCameraTransformation();

    if (light1 != NULL)
    {
        OSG::ShaderShadowMapEngine* ssme = dynamic_cast<OSG::ShaderShadowMapEngine*>(light1->getLightEngine());
        if (ssme)
        {
            OSG::Int32 shadowTexUnit = ssme->getForceTextureUnit() > 0 ? ssme->getForceTextureUnit() : 7;

            OSG::ShaderProgram* shadowFP = ssme->getShadowFragmentProgram();
            if(shadowFP != NULL && prog_chunk->getMFFragmentShader()->findIndex(shadowFP) == -1)
            {
                prog_chunk->addShader(shadowFP);
            }

            if (ssme->getShadowTexChunk() != NULL)
            {
                if(ssme->getEnabled() == true)
                {
                    prog_state->addChunk(ssme->getShadowTexChunk(), shadowTexUnit);
                }
                else
                {
                    prog_state->subChunk(ssme->getShadowTexChunk(), shadowTexUnit);
                }
            }
        }
    }

    if (light2 != NULL)
    {
        OSG::ShaderShadowMapEngine* ssme = dynamic_cast<OSG::ShaderShadowMapEngine*>(light2->getLightEngine());
        if (ssme)
        {
            OSG::Int32 shadowTexUnit = ssme->getForceTextureUnit() > 0 ? ssme->getForceTextureUnit() : 7;

            OSG::ShaderProgram* shadowFP = ssme->getShadowFragmentProgram();
            if(shadowFP != NULL && prog_chunk->getMFFragmentShader()->findIndex(shadowFP) == -1)
            {
                prog_chunk->addShader(shadowFP);
            }

            if (ssme->getShadowTexChunk() != NULL)
            {
                if(ssme->getEnabled() == true)
                {
                    prog_state->addChunk(ssme->getShadowTexChunk(), shadowTexUnit);
                }
                else
                {
                    prog_state->subChunk(ssme->getShadowTexChunk(), shadowTexUnit);
                }
            }
        }
    }

    OSG::commitChanges();

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
                navigator.buttonRelease(OSG::Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                navigator.buttonRelease(OSG::Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                navigator.buttonRelease(OSG::Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                navigator.buttonRelease(OSG::Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                navigator.buttonRelease(OSG::Navigator::DOWN_MOUSE, x, y);
                break;
        }
        mousebuttons &= ~(1 << button);
        lastx = x;
        lasty = y;
    }

    else
    {
        mgr->mouseButtonPress(button, x, y);
        switch(button)
        {
            case 0:
                navigator.buttonPress(OSG::Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                navigator.buttonPress(OSG::Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                navigator.buttonPress(OSG::Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                navigator.buttonPress(OSG::Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                navigator.buttonPress(OSG::Navigator::DOWN_MOUSE, x, y);
                break;
        }
        mousebuttons |= 1 << button;
        lastx = x;
        lasty = y;
    }

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);

    if(mousebuttons)
        navigator.moveTo(x, y);
    lastx = x;
    lasty = y;

    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            {
                navigator.setViewport(NULL);
                navigator.setCameraTransformation(NULL);

                gwin                = NULL;

                prog_state          = NULL;
                prog_chunk          = NULL;

                materialNode        = NULL;

                light1Node          = NULL;
                light2Node          = NULL;
                light3Node          = NULL;
                light4Node          = NULL;

                light1              = NULL;
                light2              = NULL;
                light3              = NULL;
                light4              = NULL;

                light1_trans        = NULL;
                light2_trans        = NULL;
                light3_trans        = NULL;
                light4_trans        = NULL;

                obj1_trans          = NULL;
                dino1_trans         = NULL;
                dino2_trans         = NULL;
                dino3_trans         = NULL;
                dino4_trans         = NULL;
                tree1_trans         = NULL;
                tree2_trans         = NULL;
                tree3_trans         = NULL;
                tree4_trans         = NULL;
                tree5_trans         = NULL;
                tree6_trans         = NULL;
                tree7_trans         = NULL;
                tree8_trans         = NULL;
                tree9_trans         = NULL;

                camera              = NULL;
                perspective_camera  = NULL;
                cam_beacon          = NULL;
                cam_trans           = NULL;

                mgr                 = NULL;

                OSG::osgExit();
                exit(0);
            }
            break;

        case '9':
           {
               light1->setOn(!light1->getOn());

               if(light1->getOn() && light2->getOn())
               {
                   light1->setAmbient(0.15f, 0.15f, 0.15f, 1);
                   light1->setDiffuse(0.4f, 0.4f, 0.4f, 1);

                   light2->setAmbient(0.15f, 0.15f, 0.15f, 1);
                   light2->setDiffuse(0.4f, 0.4f, 0.4f, 1);
               }
               else if(light1->getOn())
               {
                   light1->setAmbient(0.3f, 0.3f, 0.3f, 1);
                   light1->setDiffuse(0.8f, 0.8f, 0.8f, 1);
               }

               std::cout << std::endl;
               std::cout << "'9'     Light 1 " << (light1->getOn() ? "on " : "off") << ", type '" << light1->getType().getName() << "'" << std::endl;
               std::cout << "        Light 2 " << (light2->getOn() ? "on " : "off") << ", type '" << light2->getType().getName() << "'" << std::endl;

                OSG::commitChanges();
           }
           break;

        case '0':
            {
                light2->setOn(!light2->getOn());

                if(light1->getOn() && light2->getOn())
                {
                    light1->setAmbient(0.15f, 0.15f, 0.15f, 1);
                    light1->setDiffuse(0.4f, 0.4f, 0.4f, 1);

                    light2->setAmbient(0.15f, 0.15f, 0.15f, 1);
                    light2->setDiffuse(0.4f, 0.4f, 0.4f, 1);
                }
                else if(light2->getOn())
                {
                    light2->setAmbient(0.3f, 0.3f, 0.3f, 1);
                    light2->setDiffuse(0.8f, 0.8f, 0.8f, 1);
                }

                std::cout << std::endl;
                std::cout << "'0'     Light 1 " << (light1->getOn() ? "on " : "off") << ", type '" << light1->getType().getName() << "'" << std::endl;
                std::cout << "        Light 2 " << (light2->getOn() ? "on " : "off") << ", type '" << light2->getType().getName() << "'" << std::endl;

                OSG::commitChanges();
            }
            break;

        case 'w':
            {
                //OSG::Real32  t = shadowStage->getOffBias();

                //shadowStage->setOffBias((t + 0.2));
                //std::cout << std::endl;
                //std::cout << "'w'     Polygon-OffsetBias is  : " << shadowStage->getOffBias  () << std::endl;
                break;
            }

        case 's':
            {
                //OSG::Real32  t = shadowStage->getOffBias();
                
                //shadowStage->setOffBias((t - 0.2));
                //
                //std::cout << std::endl;
                //std::cout << "'s'     Polygon-OffsetBias is  : " << shadowStage->getOffBias  () << std::endl;
                break;
            }

        case 'e':
            {
                //OSG::Real32  t = shadowStage->getOffFactor();

                //shadowStage->setOffFactor(++t);
                //std::cout << std::endl;
                //std::cout << "'e'     Polygon-OffsetFactor is: " << shadowStage->getOffFactor() << std::endl;
                break;
            }

        case 'd':
            {
                //OSG::Real32  t = shadowStage->getOffFactor();

                //shadowStage->setOffFactor(--t);
                //std::cout << std::endl;
                //std::cout << "'d'     Polygon-OffsetFactor is: " << shadowStage->getOffFactor() << std::endl;
                break;
            }
        case 'o':
            {
                //bool    s = shadowStage->getShadowOn();
                //shadowStage->setShadowOn(!s);
                //std::cout << std::endl;
                //std::cout << "'o'     Shadow stage on/off    : " << (shadowStage->getShadowOn() ? "on" : "off") << std::endl;
                break;
            }
        case '1':
            {
                //shadowStage->setShadowMode(OSG::ShadowStage::NO_SHADOW);
                //std::cout << std::endl;
                //std::cout << "'1'     Shadow mode            : " << "NO_SHADOW" << std::endl;
                break;
            }

        case '2':
            {
                //shadowStage->setShadowMode(OSG::MultiLightShadowStage::SIMPLE_SHADOW_MAP);
                //std::cout << std::endl;
                //std::cout << "'2'     Shadow mode            : " << "SIMPLE_SHADOW_MAP" << std::endl;
                break;
            }

        case 'y':
            {
                //shadowStage->setMapSize(512);
                //std::cout << std::endl;
                //std::cout << "'y'     Shadow map size is     : " << shadowStage->getMapSize         () << std::endl;
                break;
            }

        case 'x':
            {
                //shadowStage->setMapSize(1024);
                //std::cout << std::endl;
                //std::cout << "'x'     Shadow map size is     : " << shadowStage->getMapSize         () << std::endl;
                break;
            }

        case 'c':
            {
                //shadowStage->setMapSize(2048);
                //std::cout << std::endl;
                //std::cout << "'c'     Shadow map size is     : " << shadowStage->getMapSize         () << std::endl;
                break;
            }

        case '+':
            {
                //OSG::Real32  t = shadowStage->getShadowSmoothness();

                //shadowStage->setShadowSmoothness(t + 0.1);
                //std::cout << std::endl;
                //std::cout << "'+'     Shadow smoothness is   : " << shadowStage->getShadowSmoothness() << std::endl;
                break;
            }

        case '-':
            {
                //OSG::Real32  t = shadowStage->getShadowSmoothness();

                //shadowStage->setShadowSmoothness(t - 0.1);
                //std::cout << std::endl;
                //std::cout << "'-'     Shadow smoothness is   : " << shadowStage->getShadowSmoothness() << std::endl;
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
    std::cout << "2  : shadow mode SIMPLE_SHADOW_MAP" << std::endl;
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

    std::cout << "camera near value is           : " << mgr->getCamera()->getNear() << std::endl;
    std::cout << "camera far  value is           : " << mgr->getCamera()->getFar () << std::endl;
}

// ============================================================================
//
// Part: The shader programs
//
// ============================================================================

//
// vertex shader program.
//
std::string get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 420 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
    << endl << "smooth out vec3 vNormalES;      // eye space normal"
    << endl << "smooth out vec3 vPositionES;    // eye space position"
    << endl << "smooth out vec3 vNormalWS;       // world space normal"
    << endl << "smooth out vec3 vPositionWS;     // world space position"
    << endl << ""
    << endl << "out vec2 vGeomTexCoord;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // multiply the object space vertex position with the modelview matrix "
    << endl << "    // to get the eye space vertex position"
    << endl << "    //"
    << endl << "    vPositionES = (gl_ModelViewMatrix * gl_Vertex).xyz;"
    << endl << ""
    << endl << "    //"
    << endl << "    // multiply the object space normal with the normal matrix (transpose of the inverse "
    << endl << "    // model view matrix) to get the eye space normal"
    << endl << "    //"
    << endl << "    vNormalES = gl_NormalMatrix * gl_Normal;"
    << endl << ""
    << endl << "    //"
    << endl << "    // multiply the combiend modelview projection matrix with the object space vertex"
    << endl << "    // position to get the clip space position"
    << endl << "    //"
    << endl << "    gl_Position = ftransform();"
    << endl << ""
    << endl << "    vGeomTexCoord = gl_MultiTexCoord0.st;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 440 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
    << endl << "smooth in vec3 vNormalES;       // eye space normal"
    << endl << "smooth in vec3 vPositionES;     // eye space position"
    << endl << "smooth in vec3 vNormalWS;       // world space normal"
    << endl << "smooth in vec3 vPositionWS;     // world space position"
    << endl << ""
    << endl << "in vec2 vGeomTexCoord;"
    << endl << ""
    << endl << "uniform sampler2D uGeomTex;"
    << endl << "uniform bool uHasTexture;"
    << endl << ""
    << endl << "const int POINT_LIGHT       = 1;"
    << endl << "const int DIRECTIONAL_LIGHT = 2;"
    << endl << "const int SPOT_LIGHT        = 3;"
    << endl << ""
    << endl << "uniform bool OSGLight0Active;"
    << endl << "uniform bool OSGLight1Active;"
    << endl << "uniform bool OSGLight2Active;"
    << endl << "uniform bool OSGLight3Active;"
    << endl << "uniform bool OSGLight4Active;"
    << endl << "uniform bool OSGLight5Active;"
    << endl << "uniform bool OSGLight6Active;"
    << endl << "uniform bool OSGLight7Active;"
    << endl << ""
    << endl << "struct Light"
    << endl << "{"
    << endl << "    vec3  position;"
    << endl << "    vec3  direction;"
    << endl << "    vec3  ambientIntensity;"
    << endl << "    vec3  diffuseIntensity;"
    << endl << "    vec3  specularIntensity;"
    << endl << "    float constantAttenuation;"
    << endl << "    float linearAttenuation;"
    << endl << "    float quadraticAttenuation;"
    << endl << "    float cosSpotlightAngle;"
    << endl << "    float spotlightExponent;"
    << endl << "    int   type;"
    << endl << "    bool  enabled;"
    << endl << "};"
    << endl << ""
    << endl << "struct Material"
    << endl << "{"
    << endl << "    vec3 ambient;"
    << endl << "    vec3 diffuse;"
    << endl << "    vec3 specular;"
    << endl << "    vec3 emissive;"
    << endl << ""
    << endl << "    float opacity;"
    << endl << "    float shininess;"
    << endl << "};"
    << endl << ""
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based on its"
    << endl << "// constant, linear and quadratic attenuation factors"
    << endl << "// and the distance d of the light to the current point."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in const float c,"
    << endl << "    in const float l,"
    << endl << "    in const float q,"
    << endl << "    in const float d)"
    << endl << "{"
    << endl << "    return 1.0 / (c + l*d + q*d*d);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      cutoff   :  cosine of the spot cutoff angle"
    << endl << "//      exponent :  the spot exponent"
    << endl << "//      l        :  normalized direction between fragment and light position"
    << endl << "//      s        :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in const float cutoff,"
    << endl << "    in const float exponent,"
    << endl << "    in const vec3 l,"
    << endl << "    in const vec3 s)"
    << endl << "{"
    << endl << "    float attenuation = 0.0;"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    if (l_dot_s >= cutoff)"
    << endl << "        attenuation = pow(l_dot_s, exponent);"
    << endl << "    return attenuation;"
    << endl << "}"
    << endl << ""

    << endl << "vec4 OSG_SSME_FP_calcShadow(in vec4 ecFragPos);"

    << endl << "//"
    << endl << "// directional light contribution"
    << endl << "//"
    << endl << "vec3 directionalLight("
    << endl << "    in Light    light,"
    << endl << "    in Material material, // the fragment material"
    << endl << "    in vec3     n,        // vertex normal in eye space"
    << endl << "    in vec3     v)        // view direction in eye space"
    << endl << "{"
    << endl << "    if (!light.enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the light direction in eye space"
    << endl << "    //"
    << endl << "    vec4 direction = vec4(light.direction, 0.0);"
    << endl << "    vec3 l = -direction.xyz;"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << ""
    << endl << "    float m = material.shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    float shadow = shadowAttenuationDirectionalLight(vPositionWS, vNormalWS, light);"
    << endl << ""
    << endl << "    return material.emissive"
    << endl << "     +          light. ambientIntensity * material.ambient"
    << endl << "     + shadow * light. diffuseIntensity * material.diffuse  * n_dot_l"
    << endl << "     + shadow * light.specularIntensity * material.specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// point light contribution"
    << endl << "//"
    << endl << "vec3 pointLight("
    << endl << "    in Light    light,"
    << endl << "    in Material material, // the fragment material"
    << endl << "    in vec3     n,        // vertex normal in eye space"
    << endl << "    in vec3     v,        // view direction in eye space"
    << endl << "    in vec3     p)        // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!light.enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec4 position = vec4(light.position, 1.0);"
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm direction from surf to light"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << ""
    << endl << "    float m = material.shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    float attenuation = calcAttenuation("
    << endl << "                            light. constantAttenuation,"
    << endl << "                            light.   linearAttenuation,"
    << endl << "                            light.quadraticAttenuation,"
    << endl << "                            d);"
    << endl << ""
    << endl << "    float shadow = shadowAttenuationPointLight(vPositionWS, vNormalWS, light);"
    << endl << ""
    << endl << "    return material.emissive"
    << endl << "     +          attenuation * light. ambientIntensity * material.ambient"
    << endl << "     + shadow * attenuation * light. diffuseIntensity * material.diffuse  * n_dot_l"
    << endl << "     + shadow * attenuation * light.specularIntensity * material.specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// spot light contribution"
    << endl << "//"
    << endl << "vec3 spotLight("
    << endl << "    in Light    light,"
    << endl << "    in Material material, // the fragment material"
    << endl << "    in vec3     n,        // vertex normal in eye space"
    << endl << "    in vec3     v,        // view direction in eye space"
    << endl << "    in vec3     p)        // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!light.enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec4 position = vec4(light.position, 1.0);"
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm dir from surface to light"
    << endl << "    "
    << endl << "    vec4 direction = vec4(light.direction, 0.0);"
    << endl << "    vec3 s = direction.xyz;"
    << endl << "    s = normalize(s);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << ""
    << endl << "    float m = material.shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    float attenuation = calcAttenuation("
    << endl << "                            light. constantAttenuation,"
    << endl << "                            light.   linearAttenuation,"
    << endl << "                            light.quadraticAttenuation,"
    << endl << "                            d);"
    << endl << ""
    << endl << "    attenuation *= spotAttenuation(light.cosSpotlightAngle, light.spotlightExponent, l, s);"
    << endl << ""
    << endl << "    float shadow = shadowAttenuationSpotLight(vPositionWS, vNormalWS, light);"
    << endl << ""
    << endl << "    return material.emissive"
    << endl << "     +          attenuation * light. ambientIntensity * material.ambient"
    << endl << "     + shadow * attenuation * light. diffuseIntensity * material.diffuse  * n_dot_l"
    << endl << "     + shadow * attenuation * light.specularIntensity * material.specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "Material getMaterial()"
    << endl << "{"
    << endl << "    Material material;"
    << endl << "    if (gl_FrontFacing)"
    << endl << "    {"
    << endl << "        material.ambient   = gl_FrontMaterial.ambient.rgb;"
    << endl << "        material.diffuse   = gl_FrontMaterial.diffuse.rgb;"
    << endl << "        material.specular  = gl_FrontMaterial.specular.rgb;"
    << endl << "        material.emissive  = gl_FrontMaterial.emission.rgb;"
    << endl << "        material.opacity   = gl_FrontMaterial.diffuse.a;"
    << endl << "        material.shininess = gl_FrontMaterial.shininess;"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        material.ambient   = gl_BackMaterial.ambient.rgb;"
    << endl << "        material.diffuse   = gl_BackMaterial.diffuse.rgb;"
    << endl << "        material.specular  = gl_BackMaterial.specular.rgb;"
    << endl << "        material.emissive  = gl_BackMaterial.emission.rgb;"
    << endl << "        material.opacity   = gl_BackMaterial.diffuse.a;"
    << endl << "        material.shininess = gl_BackMaterial.shininess;"
    << endl << "    }"
    << endl << "    return material;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    const int num_lights = 8;"
    << endl << "    Light lights[num_lights];"
    << endl << ""
    << endl << "    for (int i = 0; i < num_lights; ++i)"
    << endl << "    {"
    << endl << "        lights[i].enabled = false;"
    << endl << "        lights[i].type    = 0;"
    << endl << "    }"
    << endl << ""
    << endl << "    if(OSGLight0Active) lights[0].enabled = true;"
    << endl << "    if(OSGLight1Active) lights[1].enabled = true;"
    << endl << "    if(OSGLight2Active) lights[2].enabled = true;"
    << endl << "    if(OSGLight3Active) lights[3].enabled = true;"
    << endl << "    if(OSGLight4Active) lights[4].enabled = true;"
    << endl << "    if(OSGLight5Active) lights[5].enabled = true;"
    << endl << "    if(OSGLight6Active) lights[6].enabled = true;"
    << endl << "    if(OSGLight7Active) lights[7].enabled = true;"
    << endl << ""
    << endl << "    for (int i = 0; i < num_lights; ++i)"
    << endl << "    {"
    << endl << "        if (lights[i].enabled == true)"
    << endl << "        {"
    << endl << "            lights[i].ambientIntensity     = gl_LightSource[i].ambient.rgb;"
    << endl << "            lights[i].diffuseIntensity     = gl_LightSource[i].diffuse.rgb;"
    << endl << "            lights[i].specularIntensity    = gl_LightSource[i].specular.rgb;"
    << endl << "            lights[i].constantAttenuation  = gl_LightSource[i].constantAttenuation;"
    << endl << "            lights[i].linearAttenuation    = gl_LightSource[i].linearAttenuation;"
    << endl << "            lights[i].quadraticAttenuation = gl_LightSource[i].quadraticAttenuation;"
    << endl << "            lights[i].cosSpotlightAngle    = gl_LightSource[i].spotCosCutoff;"
    << endl << "            lights[i].spotlightExponent    = gl_LightSource[i].spotExponent;"
    << endl << "            if (gl_LightSource[i].position.w == 0.0)"
    << endl << "            {"
    << endl << "                lights[i].type             = DIRECTIONAL_LIGHT;"
    << endl << "                lights[i].position         = vec3(0,0,0);"
    << endl << "                lights[i].direction        = vec3(gl_LightSource[i].position);"
    << endl << "            }"
    << endl << "            else if (gl_LightSource[i].spotCutoff == 180.0)"
    << endl << "            {"
    << endl << "                lights[i].type             = POINT_LIGHT;"
    << endl << "                lights[i].position         = vec3(gl_LightSource[i].position);"
    << endl << "                lights[i].direction        = vec3(0,0,0);"
    << endl << "            }"
    << endl << "            else"
    << endl << "            {"
    << endl << "                lights[i].type             = SPOT_LIGHT;"
    << endl << "                lights[i].position         = vec3(gl_LightSource[i].position);"
    << endl << "                lights[i].direction        = vec3(gl_LightSource[i].spotDirection);"
    << endl << "            }"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    //"
    << endl << "    // normalize the eye space normal"
    << endl << "    //"
    << endl << "    int frontCond = -(1 - int(gl_FrontFacing)*2);"
    << endl << "    vec3 N = frontCond * normalize(vNormalES);"
    << endl << ""
    << endl << "    Material material = getMaterial();"
    << endl << ""
    << endl << "    //"
    << endl << "    // get the view vector and normalize it"
    << endl << "    //"
    << endl << "    vec3 V = normalize(cCameraPositionES - vPositionES);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Integrate over all lights: Any unused light does not contribute and each light"
    << endl << "    // contribute either from the directional light, the point light or the spot light."
    << endl << "    //"
    << endl << "    vec3 color = vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    for (int i = 0; i < num_lights; ++i)"
    << endl << "    {"
    << endl << "        switch (lights[i].type)"
    << endl << "        {"
    << endl << "            case       POINT_LIGHT: color +=       pointLight(lights[i], material, N, V, vPositionES); break;"
    << endl << "            case DIRECTIONAL_LIGHT: color += directionalLight(lights[i], material, N, V);              break;"
    << endl << "            case        SPOT_LIGHT: color +=        spotLight(lights[i], material, N, V, vPositionES); break;"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    vec3 factor = vec3(1.0);"
    << endl << "    if (uHasTexture)"
    << endl << "        factor = texture2D(uGeomTex, vGeomTexCoord).xyz;"
    << endl << ""
    << endl << "    color = factor * color;"
    << endl << ""
    << endl << "    vFragColor = vec4(color, material.opacity);"
    << endl << ""
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
