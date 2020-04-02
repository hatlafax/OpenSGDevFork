// OpenSG Test Example: ambientocclusion
//
// This example uses the SSAOStage in order to generate
// an ambient occlusion texture image that is then used
// for ambient lighting in the light shader.
//

#ifdef OSG_BUILD_ACTIVE
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGChunkMaterial.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGGroup.h>
#include <OSGHDR2Stage.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGOrthographicCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGPolygonChunk.h>
#include <OSGSceneFileHandler.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderVariableOSG.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSolidBackground.h>
#include <OSGSSAOStage.h>
#include <OSGTransform.h>
#else
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGOrthographicCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGSSAOStage.h>
#include <OpenSG/OSGTransform.h>
#endif

bool useOrthoCamera      = false;
bool useCalcPosFromDepth = true;

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// The tonemapping stage
//
OSG::HDR2StageRefPtr hdr2Stage;

//
// The Screen Space Ambient Occlusion stage
//
OSG::SSAOStageRefPtr ssaoStage;

//
// The light fragment shader
//
OSG::ShaderProgramRefPtr fragShader;

bool useAmbientOcclusion = true;

//
// forward declarations...
//
std::string get_vp_program();
std::string get_fp_program();

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

void print_state();
void print_help();

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
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
    OSG::osgInit(argc,argv);

    print_help();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        OSG::NodeRefPtr hdr2Node = OSG::Node::create();
        OSG::NodeRefPtr ssaoNode = OSG::Node::create();
        OSG::NodeRefPtr scene    = OSG::Node::create();

        hdr2Stage = OSG::HDR2Stage::create();
        hdr2Stage->setActivate          (true);
        hdr2Stage->setToneMappingMode   (OSG::HDR2Stage::FILMIC_ACES_TONE_MAPPING);
        hdr2Stage->setAutoExposureMode  (OSG::HDR2Stage::AUTOMATIC);
        hdr2Stage->setAdjustLuminance   (false);
        hdr2Stage->setPerformBloom      (false);
        hdr2Stage->setForceBackground   (true);
        hdr2Stage->setCarryDepth        (true);
        hdr2Stage->setNumSamples        (4);

        hdr2Node->setCore(hdr2Stage);

        ssaoStage = OSG::SSAOStage::create();
        ssaoStage->setActivate(true);
        ssaoStage->setCalcPosFromDepth(useCalcPosFromDepth);
        ssaoNode->setCore(ssaoStage);

        scene->setCore(OSG::Group::create());

        hdr2Node->addChild(ssaoNode);
        ssaoNode->addChild(scene);


        OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
                                      fragShader = OSG::ShaderProgram::createFragmentShader();

        vertShader->setProgram(get_vp_program());
        fragShader->setProgram(get_fp_program());

        vertShader->addOSGVariable("OSGModelViewMatrix");
        vertShader->addOSGVariable("OSGProjectionMatrix");

        fragShader->addUniformVariable("uUseAO", useAmbientOcclusion);

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(prog_chunk);

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);

        OSG::NodeRefPtr materialNode = OSG::Node::create();
        materialNode->setCore(mgrp);

        //OSG::NodeRefPtr modelNode = OSG::SceneFileHandler::the()->read("Data/dinopet.3ds");
        //OSG::Real32 room_size = 10.f;
        //OSG::Vec3f  room_move(0.f, 0.f, 3.f);
        //OSG::Pnt3f  from(25.f/5.f, 10.f/5.f, 10.f/5.f);
        //OSG::Pnt3f  at(0.f, 0.f, 0.0f);
        //OSG::Vec3f  up(0,0,1);

        OSG::NodeRefPtr modelNode = OSG::SceneFileHandler::the()->read("Data/MyNanoSuit.obj");
        OSG::Real32 room_size = 50.f;
        OSG::Vec3f  room_move(0.f, 10.f, 24.0f);
        OSG::Pnt3f  from(25.f, 10.f, 10.f);
        OSG::Pnt3f  at(0.f, 0.f, 0.0f);
        OSG::Vec3f  up(0,0,1);

        //OSG::NodeRefPtr modelNode = OSG::SceneFileHandler::the()->read("Data/84mosque-ciro.3DS");
        //OSG::Real32 room_size = 2000.f;
        //OSG::Vec3f  room_move(0.f, 0.f, room_size / 2.f);
        //OSG::Pnt3f  from(1000.f,0,500.f);
        //OSG::Pnt3f  at(0,0,0);
        //OSG::Vec3f  up(0,0,1);

        OSG::MaterialChunkRefPtr matChunk = OSG::MaterialChunk::create();
        matChunk->setEmission(OSG::Color4f(0.f,0.f,0.f,1.f));
        matChunk->setAmbient(OSG::Color4f(0.21176f, 0.12941f, 0.05490f, 1.f));
        matChunk->setDiffuse(OSG::Color4f(0.71373f, 0.42745f, 0.18039f, 1.f));
        matChunk->setSpecular(OSG::Color4f(0.39216f, 0.27059f, 0.16863f, 1.f));
        matChunk->setShininess  (0.2f * 128.f);
        prog_state->addChunk(matChunk);
    
        OSG::ChunkMaterialRefPtr roomMat = OSG::ChunkMaterial::create();
        OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
        polygonChunk->setFrontMode(GL_FILL);
        polygonChunk->setCullFace(GL_FRONT);
        roomMat->addChunk(polygonChunk);

        OSG::NodeRefPtr     room    = OSG::Node::create();
        OSG::GeometryRefPtr roomGeo = OSG::makeBoxGeo(room_size, room_size, room_size, 1, 1, 1);
        roomGeo->setMaterial(roomMat);
        room->setCore(roomGeo);
        OSG::NodeRefPtr roomNode = OSG::Node::create();

        OSG::Matrix trafo;
        trafo.setTranslate(room_move);
        OSG::TransformRefPtr trafoCore = OSG::Transform::create();
        trafoCore->setMatrix(trafo);

        roomNode->setCore(trafoCore);
        roomNode->addChild(room);

        materialNode->addChild(roomNode);
        materialNode->addChild(modelNode);
        scene->addChild(materialNode);

        OSG::commitChanges();
    
        mgr->setRoot(hdr2Node);

        if (useOrthoCamera)
        {
            OSG::OrthographicCameraRefPtr orthoCamera = OSG::OrthographicCamera::create();
            mgr->setCamera(orthoCamera);
        }

        // show the whole scene
        mgr->showAll();
        mgr->getNavigator()->set(from, at, up);

        OSG::SolidBackgroundRefPtr background = OSG::SolidBackground::create();
        background->setColor(OSG::Color3f(0.5f,0.5f,0.5f));
        mgr->setBackground(background);

        OSG::commitChanges();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//
// redraw the window
//
void display(void)
{
    mgr->redraw();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            mgr          = NULL;
            ssaoStage    = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;

        case 'a':
        {
            useAmbientOcclusion = !useAmbientOcclusion;
            fragShader->updateUniformVariable("uUseAO", useAmbientOcclusion);

            print_state();

            glutPostRedisplay();
        }
        break;

        case 'b':
        {
            OSG::Real32 bias = ssaoStage->getBias();
            if (bias < 1.f)
                bias += 0.001f;

            ssaoStage->setBias(bias);

            print_state();

            glutPostRedisplay();
        }
        break;

        case 'B':
        {
            OSG::Real32 bias = ssaoStage->getBias();
            if (bias >= 0.001f)
                bias -= 0.001f;

            ssaoStage->setBias(bias);

            print_state();

            glutPostRedisplay();
        }
        break;

        case 'r':
        {
            OSG::Real32 radius = ssaoStage->getRadius();
            if (radius < 10.f)
                radius += 0.1f;

            ssaoStage->setRadius(radius);

            print_state();

            glutPostRedisplay();
        }
        break;

        case 'R':
        {
            OSG::Real32 radius = ssaoStage->getRadius();
            if (radius >= 0.1f)
                radius -= 0.1f;

            ssaoStage->setRadius(radius);

            print_state();

            glutPostRedisplay();
        }
        break;

        case 'h':
        {
            print_help();
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

void print_state()
{
    OSG::Real32 bias   = ssaoStage->getBias();
    OSG::Real32 radius = ssaoStage->getRadius();

    std::cout << "useAmbientOcclusion = " << useAmbientOcclusion << std::endl;
    std::cout << "ssao bias           = " << bias << std::endl;
    std::cout << "ssao sample radius  = " << radius << std::endl;
}

void print_help()
{
    std::cout << "Esc : quit example" << std::endl;
    std::cout << "a   : toogle ambient occlusion on/off" << std::endl;
    std::cout << "b   : increase bias" << std::endl;
    std::cout << "B   : decrease bias" << std::endl;
    std::cout << "r   : increase sample radius" << std::endl;
    std::cout << "R   : decrease sample radius" << std::endl;
    std::cout << "h   : print this help" << std::endl;
}

//
// vertex shader program.
//
std::string get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "layout (location = 0) in vec4 aVertex;"
    << endl << "layout (location = 2) in vec3 aNormal;"
    << endl << ""
    << endl << "uniform mat4  OSGModelViewMatrix;"
    << endl << "uniform mat4  OSGProjectionMatrix;"
    << endl << ""
    << endl << "out vec3 vNormalES;"
    << endl << "out vec3 vPositionES;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    vec4 fragPosES = OSGModelViewMatrix * aVertex;"
    << endl << ""
    << endl << "    vPositionES = fragPosES.xyz;"
    << endl << "    vNormalES   = gl_NormalMatrix * aNormal;"
    //<< endl << "    vNormalES   = transpose(inverse(mat3x3(OSGModelViewMatrix))) * aNormal;"
    << endl << ""
    << endl << "    gl_Position = OSGProjectionMatrix * fragPosES;"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "#version 420 compatibility"
    << endl << ""
    << endl << "in vec3 vNormalES;"
    << endl << "in vec3 vPositionES;"
    << endl << ""
    << endl << "uniform bool uUseAO;"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "layout(binding = " << ssaoStage->getAmbientOcclusionTexUnit()   << ") uniform sampler2DRect uAmbientOcclusionMap;"
    << endl << ""
    << endl << "float getMaterialAmbientOcclusion()"
    << endl << "{"
    << endl << "    vec2 uv = gl_FragCoord.xy;"
    << endl << "    return texture2DRect(uAmbientOcclusionMap, uv).r;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Very simple directional light"
    << endl << "//"
    << endl << "struct Light"
    << endl << "{"
    << endl << "    vec3  color;"
    << endl << "    float intensity;"
    << endl << "    vec3  direction;"
    << endl << "};"
    << endl << ""
    << endl << "struct Material"
    << endl << "{"
    << endl << "    vec3  ambient;"
    << endl << "    vec3  diffuse;"
    << endl << "    vec3  specular;"
    << endl << "    vec3  emissive;"
    << endl << "    float shininess;"
    << endl << "    float opacity;"
    << endl << "};"
    << endl << ""
    << endl << "Material material;"
    << endl << ""
    << endl << "void InitializeMaterial()"
    << endl << "{"
    << endl << "    material.ambient   = gl_FrontMaterial.ambient.rgb;"
    << endl << "    material.diffuse   = gl_FrontMaterial.diffuse.rgb;"
    << endl << "    material.specular  = gl_FrontMaterial.specular.rgb;"
    << endl << "    material.emissive  = gl_FrontMaterial.emission.rgb;"
    << endl << "    material.shininess = gl_FrontMaterial.shininess;"
    << endl << "    material.opacity   = gl_FrontMaterial.diffuse.a;"
    << endl << "}"
    << endl << ""
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "void BlinnPhongShading(in vec3 N, in vec3 L, in vec3 V, out vec3 Ce, out vec3 Ca, out vec3 Cd, out vec3 Cs)"
    << endl << "{"
    << endl << "    vec3 H = normalize(L+V);"
    << endl << ""
    << endl << "    float NdotL = max(0.0, dot(N, L));"
    << endl << "    float NdotH = max(0.0, dot(N, H));"
    << endl << ""
    << endl << "    float S = material.shininess;"
    << endl << "    //"
    << endl << "    // calculate specular reflection only if"
    << endl << "    // the surface is oriented to the light source"
    << endl << "    //"
    << endl << "    float pf = (NdotL == 0.0 ? 0.0 : pow(NdotH, S));"
    << endl << ""
    << endl << "    Ce = material.emissive;"
    << endl << "    Ca = material.ambient;"
    << endl << "    Cd = material.diffuse  * NdotL;"
    << endl << "    Cs = material.specular * NdotL * pf;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // initialize light with arbitrary default."
    << endl << "    //"
    << endl << "    Light light;"
    << endl << "    light.color     = vec3(1,1,1);"
    << endl << "    light.intensity = 1.0;"
    << endl << "    light.direction = normalize( vPositionES - cCameraPositionES );"
    << endl << ""
    << endl << "    InitializeMaterial();"
    << endl << ""
    << endl << "    //"
    << endl << "    // normalize the eye space normal"
    << endl << "    //"
    << endl << "    vec3 N = normalize(vNormalES);"
    << endl << "    if (!gl_FrontFacing)"
    << endl << "        N = -N;"
    << endl << ""
    << endl << "    //"
    << endl << "    // get the view vector and normalize it."
    << endl << "    //"
    << endl << "    vec3 V = normalize(cCameraPositionES - vPositionES);"
    << endl << ""
    << endl << "    vec4 direction = vec4(light.direction, 0.0);"
    << endl << "    vec3 L = -direction.xyz;"
    << endl << ""
    << endl << "    vec3 Ce, Ca, Cd, Cs;"
    << endl << "    BlinnPhongShading(N, L, V, Ce, Ca, Cd, Cs);"
    << endl << ""
    << endl << "    vec3 I = light.intensity * light.color;"
    << endl << ""
    << endl << "    float ao = uUseAO ? getMaterialAmbientOcclusion() : 1.0;"
    << endl << ""
    //<< endl << "    vec3 color = vec3(ao, ao, ao);"
    << endl << "    vec3 color = Ce + ao*(Ca + Cd + Cs)*I;"
    << endl << ""
    << endl << "    vFragColor = vec4(color, material.opacity);"
    << endl << "}"
    << endl << ""
    ;

    return ost.str();
}
