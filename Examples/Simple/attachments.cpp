// OpenSG Tutorial Example: Attachments
//
// In many cases there is a need to attach some data to existing structures
// instead of deriving new classes. Many systems have a void* userdata 
// to do that. OpenSG uses the more flexible concept of Attachments. 
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <string>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSceneFileHandler.h>

// New Headers
#include <OSGAttachment.h>
#include <OSGNameAttachment.h>
#include <OSGVoidPAttachment.h>

/*
    These two headers are needed to define the new MyAttachment type below
*/
#include <OSGSimpleAttachment.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <string>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGSceneFileHandler.h>

// New Headers
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGVoidPAttachment.h>

/*
    These two headers are needed to define the new MyAttachment type below
*/
#include <OpenSG/OSGSimpleAttachment.h>
#endif

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// Helper class to find a named node
// This class uses the NameAttachment directly, see below for more on name
// handling.
class NamedNodeFinder
{
  public:
    NamedNodeFinder(void) : _found(), _name() {}

    OSG::Node *operator() (OSG::Node *root, const std::string &name)
    {
        _name  = name;
        _found = NULL;
        
        traverse(root, boost::bind(&NamedNodeFinder::checkNode, this, ::boost::placeholders::_1));
        
        return _found;
    }
    
  private:
     
    // %$#%$#% OS X trashes check symbol so we need to use checkNode
    OSG::Action::ResultE checkNode(OSG::Node *node)
    {
        OSG::Attachment *a = node->findAttachment(OSG::Name::getClassType());
        
        if(a != NULL)
        {
            OSG::Name *n = dynamic_cast<OSG::Name *>(a);
            
            if(n->getField().getValue() == _name)
            {
                _found = node;
                return OSG::Action::Quit;
            }
        }
        
        return OSG::Action::Continue;
    }

    OSG::NodeRefPtr _found;
    std::string     _name;
};

/*
   Define a simple Attachment using only a single Field
   
   You need to define the type of the field and a couple names and put it 
   into the AttachmentDesc. This is a trait used to define a SimpleAttachment
   and its Ptr.
   
   Access to the value is done via the getField() method (see below).
   
   This is just a convenience class for simple attachments. If you need
   more complex attachments you have to define them just like any other
   FieldContainer and derive them from Attachment. See Examples/NewTypes
   for info on how to do that.
   
   Note that if you want to put this into a library and use it from the outside
   you have to make sure that the static _type and _desc members are only
   instantiated in the library, not in the user's code. The procedure is the 
   same for any FieldContainer, see Examples/NewTypes for details.
*/
struct MyAttachmentDesc
{
    typedef OSG::SFInt32            FieldTypeT;

    static const OSG::Char8         *getTypeName  (void) 
    {
        return "My";
    }

    static const OSG::Char8         *getFieldName (void) 
    {
        return "myValue";
    }

    static const OSG::Char8         *getGroupName (void) 
    { 
        return "my";
    }

    static const OSG::Char8         *getParentTypeName(void) 
    {
        return "Attachment";
    }

    static OSG::InitContainerF       getInitMethod(void) { return NULL;  }
};

/*
    The following three specializations need to be in the OpenSG namespace.
*/
OSG_BEGIN_NAMESPACE

OSG_SIMPLEATTACHMENT_INST(MyAttachmentDesc);

template <>
SimpleAttachment<MyAttachmentDesc>::TypeObject &
    SimpleAttachment<MyAttachmentDesc>::getType(void)
{
    return _type;
}

template <>
const SimpleAttachment<MyAttachmentDesc>::TypeObject &
    SimpleAttachment<MyAttachmentDesc>::getType(void) const
{
    return _type;
}

template <>
SimpleAttachment<MyAttachmentDesc>::TypeObject &
    SimpleAttachment<MyAttachmentDesc>::getClassType(void)
{
    return _type;
}



/*
    Give the new attachment a simple name to refer to it.
*/
typedef SimpleAttachment<MyAttachmentDesc> MyAttachment;

/*
    Generate all the different pointer types.
*/
OSG_GEN_CONTAINERPTR(MyAttachment);

OSG_END_NAMESPACE

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

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
    
        // load the scene
    
        OSG::NodeRefPtr scene;
        
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
    
            scene = OSG::makeTorus(.5, 2, 16, 16);
        }
        else
        {
            scene = OSG::SceneFileHandler::the()->read(argv[1]);
        }
    
        /*   
        An Attachment is a special field container that can be attached to
        many of the internal classes like Nodes, NodeCores and many others.
        There can be multiple Attachments attached to an object.
    
        Attachments can be attached to all FieldContainers that are derived from
        AttachmentContainer. This includes most higher-level classes in the
        system, like Nodes, NodeCores, Windows, Viewports etc. See the
        inheritance graph for details.
    
        One predefined kind of Attachment is the Name, which can
        keep the name of an object. Some of loaders (e.g. the WRL loader)
        create these kinds of Attachments for named nodes.
        */
        
        /*
            An Attachment is a FieldContainer and as such needs to be created using
            ::create().
        */
        OSG::NameRefPtr name = OSG::Name::create();
        
        /* 
            The NameAttachment only has a single field, there's no need to use the
            mask here.
        */
        name->editFieldPtr()->setValue("Scene");
        
        /*
            Attach the name to the scene node.
        */
        scene->addAttachment(name);
        
        /*
            Check if the scene has a Name attachment
            
            Attachments are categorized by the GroupID of their class. Every
            AttachmentContainer generally keeps only one attachment of a specific
            kind. 
        */
        OSG::AttachmentRefPtr a;
        
        a = scene->findAttachment(OSG::Name::getClassType());
        
        if(a != NULL)
        {
            OSG::NameRefPtr n = OSG::dynamic_pointer_cast<OSG::Name>(a);
            
            SLOG << "Node name: " << n->getField().getValue() << OSG::endLog;
        }
        else
        {
            SLOG << "Node has no name!" << OSG::endLog;
        }
        
        /*
            As names are used quite often there are two convenience functions 
            that wrap the code given above: setName and getName. They are declared
            in OSGSimpleAttachments.h.
        */
        if(getName(scene))
        {
            SLOG << "Node is named: " << getName(scene) << OSG::endLog;
        }
        else
        {
            SLOG << "Node is unnamed." << OSG::endLog;
        }
        
        setName(scene, "Scene");
        
        
        // use the NamedNodeFinder helper to find a named object
    
             NamedNodeFinder f;
        OSG::NodeRefPtr      found;
        
        found = f(scene, "Scene");
        SLOG << "Found object " << found << " named Scene." << OSG::endLog;
        
        found = f(scene, "TF_DETAIL");
        if(found == NULL)
        {
            SLOG << "Found no object named TF_DETAIL (did you load the tie?)." 
                 << OSG::endLog;
        }
        else
        {
            SLOG << "Found object " << found << " named TF_DETAIL." 
                 << OSG::endLog;
        }
        
        
        
        // Use the simple attachment defined above
        
        OSG::MyAttachmentRefPtr mya = OSG::MyAttachment::create();
        
        mya->editFieldPtr()->setValue(42);
        
        // attach it to the scene
        scene->addAttachment(mya);
        
        // and check if it's still there       
        a = scene->findAttachment(OSG::MyAttachment::getClassType());
        
        if(a != NULL)
        {
            OSG::MyAttachmentRefPtr m = 
                OSG::dynamic_pointer_cast<OSG::MyAttachment>(a);
            
            SLOG << "Node my value: " << m->getField().getValue() 
                 << OSG::endLog;
        }
        else
        {
            SLOG << "Node has no myAttachment!" << OSG::endLog;
        }
        
        /*
        In case you don't want to create a new Attachment or cannot do that
        because it needs to reference external data, you just attach a void*
        using the VoidPAttachment. This is somewhat equivalent to the standard
        userdata pointer. 
        
        Note that the referenced data will not be threadsafe. Every thread has
        its own copy of the reference, but if if multiple threads reference the
        same data they can interfere. 
        
        Future versions will have some provisions to allow making this
        threadsafe. Stay tuned.
        */
        
        OSG::VoidPAttachmentRefPtr myvoid = OSG::VoidPAttachment::create();
        OSG::UInt32 dummy = 1234;
        
        myvoid->editFieldPtr()->setValue(&dummy);
        
        // attach it to the scene
        scene->addAttachment(myvoid);
    
        // and check if it's still there       
        a = scene->findAttachment(OSG::VoidPAttachment::getClassType());
        
        if(a != NULL)
        {
            OSG::VoidPAttachmentRefPtr m = 
                OSG::dynamic_pointer_cast<OSG::VoidPAttachment>(a);
            
            SLOG << "Node voidp value: " 
                << *(static_cast<OSG::UInt32 *>(m->getField().getValue()))
                << OSG::endLog;
        }
        else
        {
            SLOG << "Node has no voidp attachment!" << OSG::endLog;
        }
        
        
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
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
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            mgr = NULL;
            
            OSG::osgExit();
            exit(1);
        }
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
