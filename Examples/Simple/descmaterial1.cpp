// OpenSG Tutorial Example: descmaterial1.cpp
//
// Loading a model containing DescMaterials.
//
// This example shows the basic usage of the 'description' material DescMaterial
// and of the material manager DescMaterialManager.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGClusterShadingStage.h>
#include <OSGContainerCollection.h>
#include <OSGDescMaterialManager.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGGroup.h>
#include <OSGHDR2Stage.h>
#include <OSGMaterialDesc.h>
#include <OSGMultiLightGroup.h>
#include <OSGMultiLightShadowStage.h>
#include <OSGNameAttachment.h>
#include <OSGSceneFileHandler.h>
#include <OSGShaderProgram.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSolidBackground.h>
#include <OSGSSAOStage.h>
#include <OSGTransform.h>

#else
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGClusterShadingStage.h>
#include <OpenSG/OSGContainerCollection.h>
#include <OpenSG/OSGDescMaterialManager.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGMaterialDesc.h>
#include <OpenSG/OSGMultiLightGroup.h>
#include <OpenSG/OSGMultiLightShadowStage.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGSSAOStage.h>
#include <OpenSG/OSGTransform.h>
#endif

class find_node_helper
{
public:
    explicit find_node_helper(const char* name) : _str(name), _result(nullptr), _type(nullptr) {}
    explicit find_node_helper(const std::string& str) : _str(str), _result(nullptr), _type(nullptr) {}
    explicit find_node_helper(const OSG::FieldContainerType* type) : _str(), _result(nullptr), _type(type) {}

    OSG::Action::ResultE enter_name(OSG::Node* node)
    {
        using namespace OSG;
        if (getName(node) && strcmp(getName(node), _str.c_str()) == 0) 
        {
            _result = node;
            return Action::Quit;
        }
        return Action::Continue;
    }

    OSG::Action::ResultE enter_type(OSG::Node* node)
    {
        using namespace OSG;

        if (node->getCore()->getType() == *_type) {
            _result = node;
            return Action::Quit;
        }
        return Action::Continue;
    }

    OSG::Node* result() { return _result; }

private:
    OSG::Node*                      _result;
    std::string                     _str;
    const OSG::FieldContainerType*  _type;
};

OSG::Node* find_node(OSG::Node* node, const OSG::FieldContainerType& type)
{
    using namespace OSG;
    find_node_helper helper(&type);
    traverse(node, boost::bind(&find_node_helper::enter_type, &helper, _1));
    return helper.result();
}

OSG::NodeCore* find_core(OSG::Node* node, const OSG::FieldContainerType& type)
{
    using namespace OSG;

    NodeCore* result = nullptr;

    Node* found = find_node(node, type);

    if (found)
        result = found->getCore();

    return result;
}

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// MaterialManager
//
OSG::DescMaterialManagerRefPtr materialManager;

void initShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
    }
}

void updateShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
    }
}

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

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

    OSG::osgInit(argc,argv);
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

        OSG::NodeRefPtr scene(nullptr);

        if(argc < 2)
        {
            scene = OSG::SceneFileHandler::the()->read("Data/descmaterial1.osb");
        }
        else
        {
            scene = OSG::SceneFileHandler::the()->read(argv[1]);
        }

        if (scene)
        {
            OSG::ShaderProgramFunctor   initFunctor = boost::bind(::initShader,   _1);
            OSG::ShaderProgramFunctor updateFunctor = boost::bind(::updateShader, _1);
        
            // create the DescMaterialManager
            materialManager = OSG::DescMaterialManager::createDefault(initFunctor, "", updateFunctor, "");
            materialManager->setWindow(gwin);

            mgr->turnHeadlightOff();
       
            OSG::HDR2Stage*             hdr2Stage               = dynamic_cast<OSG::HDR2Stage            *>(find_core(scene, OSG::HDR2Stage             ::getClassType()));
            OSG::SSAOStage*             ssaoStage               = dynamic_cast<OSG::SSAOStage            *>(find_core(scene, OSG::SSAOStage             ::getClassType()));
            OSG::MultiLightGroup*       multiLightGroup         = dynamic_cast<OSG::MultiLightGroup      *>(find_core(scene, OSG::MultiLightGroup       ::getClassType()));
            OSG::MultiLightShadowStage* multiLightShadowStage   = dynamic_cast<OSG::MultiLightShadowStage*>(find_core(scene, OSG::MultiLightShadowStage ::getClassType()));
            OSG::ClusterShadingStage*   clusterShadingStage     = dynamic_cast<OSG::ClusterShadingStage  *>(find_core(scene, OSG::ClusterShadingStage   ::getClassType()));
        
            materialManager->setHDR2Stage(hdr2Stage);
            materialManager->setClusterShadingStage(clusterShadingStage);
            materialManager->setMultiLightShadowStage(multiLightShadowStage);
            materialManager->setSSAOStage(ssaoStage);
            materialManager->setMultiLightGroup(multiLightGroup);
            materialManager->setLightBindingPnt(1);

            //
            // DataSolid model specific:
            // =========================
            //  The root node might contain a ContainerCollection attachment with nodes carrying transform cores.
            //  Any node that has the "__CartesianNode__" name attachment is expected to follow the camera.
            //
            OSG::ContainerCollection* cc = dynamic_cast<OSG::ContainerCollection*>(scene->findAttachment(OSG::ContainerCollection::getClassType()));
            if(cc)
            {
                OSG::Node* cameraBeacon = mgr->getCamera()->getBeacon();
                if (cameraBeacon)
                {
                    OSG::Transform* camTrafo = dynamic_cast<OSG::Transform*>(cameraBeacon->getCore());
                    if (camTrafo)
                    {
                        OSG::UInt32 N = cc->getNContainers();
                        for (OSG::UInt32 idx = 0; idx < N; ++idx)
                        {
                            OSG::Node* node = dynamic_cast<OSG::Node*>(cc->getContainers(idx));
                            if (node && OSG::getName(node) && std::string("__CartesianNode__") == OSG::getName(node))
                            {
                                OSG::Transform* trafo = dynamic_cast<OSG::Transform*>(node->getCore());
                                if (trafo)
                                {
                                    node->setCore(camTrafo);
                                }
                            }
                        }
                    }
                }
            }

            OSG::commitChanges();

            mgr->setRoot(scene);
            mgr->showAll();

            OSG::commitChanges();
        }
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
    switch (k)
    {
        case 27:    
        {
            materialManager = nullptr;
            mgr = nullptr;

            OSG::osgExit();
            exit(0);
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
    glutInitWindowSize(1000, 800);
    
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

