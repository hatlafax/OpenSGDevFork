// all needed include files
#ifdef OSG_BUILD_ACTIVE
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGSceneFileHandler.h>
#include <OSGNameAttachment.h>

#include <OSGGraphOpSeq.h>
#include <OSGSplitGraphOp.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGSharePtrGraphOp.h>
#else
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGNameAttachment.h>

#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGSplitGraphOp.h>
#include <OpenSG/OSGVerifyGeoGraphOp.h>
#include <OpenSG/OSGSharePtrGraphOp.h>
#endif

OSG::SimpleSceneManagerRefPtr mgr;
OSG::NodeRecPtr               scene;

// A simple class that counts the number of entered nodes
class counter
{
    public:
        //constructor
        counter(void) : mCount(0)
        {
        }
        
        //method that will be called when entering
        //a new node
        OSG::Action::ResultE enter(OSG::Node * const)
        {
            mCount++;
            return OSG::Action::Continue;
        }
        
        OSG::UInt16 getCount(void)
        {
            return mCount;
        }
        
        void reset(void)
        {
            mCount = 0;
        }
    
    private:
        OSG::UInt16 mCount;
};


int setupGLUT( int *argc, char *argv[] );

//This is the function that will be called when a node
//is entered during traversal.
OSG::Action::ResultE enter(OSG::Node * const node)
{
    if (getName(node))
    {
        std::cout << getName(node) << std::endl;
    }
    else
    {
        std::cout << "No name was set!" << std::endl;
    }

    return OSG::Action::Continue; 
}

//This function will test if the core is of type
//geometry and if it is, it will print the node's
//name
OSG::Action::ResultE isGeometry(OSG::Node * const node)
{
    // this tests if the core is derived from geometry
    if (node->getCore()->getType().isDerivedFrom(OSG::Geometry::getClassType()))
    {
        if (getName(node))
        {
            std::cout << "Found a geometry core stored in " << getName(node)
                      << std::endl;
        }
        else
        {
            std::cout << "Found a geometry core but node has no name"
                      << std::endl;
        }
    }
    
    return OSG::Action::Continue;
}

OSG::NodeTransitPtr createScenegraph(const char* filename)
{
    OSG::NodeRecPtr n = OSG::SceneFileHandler::the()->read(filename);
    
    //we check the result
    if(n == NULL)
    {
        std::cout << "Loading the specified file was not possible!"
                << std::endl;
        return OSG::NodeTransitPtr();
    }
    
    return OSG::NodeTransitPtr(n);
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin= OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        if (argc > 1)
            scene = createScenegraph(argv[1]);
        else
            scene = createScenegraph("Data/brick_quads.wrl");
        
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
    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
    {
        mgr->mouseButtonRelease(button, x, y);
    }
    else
    {
        mgr->mouseButtonPress(button, x, y);
    
        OSG::Line                  ray  = mgr->calcViewRay(x, y);
        OSG::IntersectActionRefPtr iAct = OSG::IntersectAction::create();
        iAct->setLine(ray);
        iAct->apply(scene);
    
        if(iAct->didHit())
        {
            OSG::Pnt3f p = iAct->getHitPoint();
            std::cout << "Hit point : " << p[0] << " " << p[1] << " " << p[2]
                      << std::endl;
            OSG::NodeRecPtr n      = iAct->getHitObject();
            OSG::NodeRecPtr parent = n->getParent();
            
            parent->subChild(n);
        }

        iAct = NULL;
    }
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:
    {
        // clean up global variables
        scene = NULL;
        mgr   = NULL;
        
        OSG::osgExit();
        exit(1);
    }
    break;
    
    // this will print the names of all nodes
    // in the whole graph
    case 'p':
    {
        std::cout << std::endl << std::endl;
        std::cout << "Printing all node names";
        std::cout << "---------------------------------------";
        std::cout << std::endl << std::endl;
        
        // now we invoke the traversal
        traverse(scene, enter);
    }
    break;
    
    // this will only print the names of nodes
    // which have a geometry core
    case 'g':
    {
        std::cout << std::endl << std::endl;
        std::cout << "Printing all geometry nodes";
        std::cout << "---------------------------------------";
        std::cout << std::endl << std::endl;
    
        // traverse the graph
        traverse(scene, isGeometry);
    }
    break;
    
    case 's':
        std::cout << "Splitting Graph now...";
        
        counter c;
        
        traverse(scene, boost::bind(&counter::enter, &c, ::boost::placeholders::_1));
                
        std::cout << "Number of nodes before splitting: " << c.getCount()
                  << std::endl;
        
        OSG::SplitGraphOpRefPtr spo = OSG::SplitGraphOp::create();
        spo->setMaxPolygons(50);
        spo->traverse(scene);
        
        std::cout << "done" << std::endl;
        
        c.reset();
        
        traverse(scene, boost::bind(&counter::enter, &c, ::boost::placeholders::_1));
        
        std::cout << "Number of nodes after splitting: " << c.getCount()
                  << std::endl;
    break;

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
