// all needed include files
#ifdef OSG_BUILD_ACTIVE
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

//additional headder files
#include <OSGSceneFileHandler.h>
#include <OSGDistanceLOD.h>
#include <OSGSwitch.h>
#include <OSGNameAttachment.h>
#include <OSGComponentTransform.h>
#else
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional headder files
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDistanceLOD.h>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGComponentTransform.h>
#endif

OSG::SimpleSceneManagerRefPtr mgr;
OSG::NodeRecPtr               scene;
OSG::ComponentTransformRecPtr ct;
OSG::UInt32 frame = 0;
// 0 = translation
// 1 = rotation
// 2 = scalation
OSG::UInt8 mode = 0;

int setupGLUT(int *argc, char *argv[]);


const char *getNodeName(OSG::Node const *node)
{
    if(node == NULL)
        return NULL;

    // get node name
    OSG::NameRecPtr nodename = 
        dynamic_cast<OSG::Name *>(node->findAttachment(OSG::Name::getClassType()));

    // no node name, try core name
    if(nodename == NULL && node->getCore() != NULL)
    {
        nodename = 
            dynamic_cast<OSG::Name *>(
                node->getCore()->findAttachment(OSG::Name::getClassType()));
    }

    if(nodename != NULL)
        return nodename->getFieldPtr()->getValue().c_str();
    else
    {
        if(node->getCore() != NULL)
            return node->getCore()->getType().getName().c_str();
    }

    return NULL;
}

// this function will return the node named "FACESET_Woman"
// if there is no such node NullFC will be returned
OSG::Node *checkName(OSG::Node *n)
{
    OSG::UInt32 children = n->getNChildren();
    
    //make sure a name existes
    if (getName(n))
    {
        //check if it is the name we are looking for
        if (getName(n)== std::string("FACESET_Woman"))
            // We got the node!
            return n;
    }
    
    //check all children
    for(OSG::UInt32 i = 0; i < children; i++)
    {
        OSG::Node *r = checkName(n->getChild(i));
        if(r != NULL)
            // if it is not NULL it is the node we are looking for
            // so just pass it through
            return r;
    }
    
    // no children's name matches or there are no more childs
    // so return NULL, indicating that the node was not found yet
    return NULL;
}

OSG::NodeTransitPtr createScenegraph(void)
{
    // At first we load all needed models from file
    OSG::NodeRecPtr w_high   = 
        OSG::SceneFileHandler::the()->read("Data/woman_high.wrl");

    OSG::NodeRecPtr w_medium = 
        OSG::SceneFileHandler::the()->read("Data/woman_medium.wrl");

    OSG::NodeRecPtr w_low    = 
        OSG::SceneFileHandler::the()->read("Data/woman_low.wrl");
    
    // we check the result
    // we check the result
    if((w_high == NULL) || (w_medium == NULL)|| (w_low == NULL))
    {
        std::cout << "It was not possible to load all needed models from file"
                  << std::endl;
        return OSG::NodeTransitPtr();
    }
    
    // now the LOD core
    OSG::DistanceLODRecPtr lod = OSG::DistanceLOD::create();
    lod->editSFCenter()->setValue(OSG::Pnt3f(0,0,0));
    lod->editMFRange()->push_back(200);
    lod->editMFRange()->push_back(500);
    
    // the node containing the LOD core. The three models will be
    // added as its children
    OSG::NodeRecPtr lodNode = OSG::Node::create();
    lodNode->setCore(lod);
    lodNode->addChild(w_high);
    lodNode->addChild(w_medium);
    lodNode->addChild(w_low);
    
    // create the node with switch core ********************
    OSG::SwitchRecPtr sw = OSG::Switch::create();
    //Notice: the first choice is 0
    sw->setChoice(0);
    
    OSG::NodeRecPtr switchNode = OSG::Node::create();
    switchNode->setCore(sw);
    switchNode->addChild(lodNode);
    
    //end witch creation **********************************
    
    OSG::NodeRecPtr root = OSG::Node::create();
    root->setCore(OSG::Group::create());
    root->addChild(switchNode);
    
    // we know want to extract the mesh geometry out of the graph
    // it is sufficent to pass the model only as root for searching
    OSG::NodeRecPtr womanGeometry = checkName(w_high);
    if(womanGeometry == NULL)
    {
        std::cout << "Couldn't find geometry node 'FACESET_Woman'!"
                  << std::endl;
        return OSG::NodeTransitPtr();
    }

    OSG::GeometryRecPtr geo = 
        dynamic_cast<OSG::Geometry *>(womanGeometry->getCore());

    if(geo == NULL)
    {
        std::cout << "Node 'FACESET_Woman' is not a geometry node!"
                  << std::endl;
        return OSG::NodeTransitPtr();
    }

    // generating a material *********************************
    
    OSG::SimpleMaterialRecPtr mat = OSG::SimpleMaterial::create();
    mat->setAmbient (OSG::Color3f(0.2f, 0.2f, 0.2f));
    mat->setDiffuse (OSG::Color3f(0.6f, 0.3f, 0.1f));
    mat->setSpecular(OSG::Color3f(1.0f, 1.0f, 1.0f));
    mat->setShininess(0.8f);
    
    geo->setMaterial(mat);
    
    // end material generation *******************************
    
    //new node with "old" geometry core referenced
    OSG::NodeRecPtr woman = OSG::Node::create();
    woman->setCore(geo);
    
    /* the old transformation is not needed any longer
    //translate it a bit to see both women
    NodeRecPtr      womanTrans = Node::create();
    TransformRecPtr t          = Transform::create();
    Matrix m;
    m.setIdentity();
    m.setTranslate(Vec3f(0.0f, 0.0f, 200.f));
    t->setMatrix(m);

    womanTrans->setCore(t);
    womanTrans->addChild(woman);
    */
    
    // component transform ************************************
    OSG::NodeRecPtr ctNode = OSG::Node::create();
    
    //this one is declared globally
    ct = OSG::ComponentTransform::create();

    ct->setTranslation(OSG::Vec3f(0,0,200));
    ct->setScale(OSG::Vec3f(1,1,1));
    ct->setRotation(OSG::Quaternion(OSG::Vec3f(0,1,0),0));
    
    ctNode->setCore(ct);
    ctNode->addChild(woman);
    // end component transform ********************************
    
    //add it to the root
    root->addChild(ctNode);
    
    return OSG::NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        scene = createScenegraph();
        
        if(scene == NULL)
            return 1;
    
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        OSG::commitChanges();
    }
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    frame++;
    OSG::Real32 time = glutGet(GLUT_ELAPSED_TIME);
    
    switch(mode)
    {
    case 0 :
        ct->setTranslation(OSG::Vec3f(0,cos(time/2000.f)*100,200));
        break;
    case 1 :
        ct->setRotation(OSG::Quaternion(OSG::Vec3f(0,1,0), time/2000));
        break;
    case 2 :
        ct->setScale(OSG::Vec3f(cos(time/2000), 
                                sin(time/2000), 
                                tan(time/2000)));
        break;
    }


    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
    switch (k)
    {
    case 't' : mode = 0; break;
    case 'r' : mode = 1; break;
    case 's' : mode = 2; break;
    }
}


int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    
    return winid;
}
