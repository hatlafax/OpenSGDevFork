/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGShaderProgram.h"
#include "OSGGLFuncProtos.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderProgram.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 ShaderProgram::_extSHL                           = Window::invalidExtensionID;
UInt32 ShaderProgram::_extCG                            = Window::invalidExtensionID;
UInt32 ShaderProgram::_extGeoShader4                    = Window::invalidExtensionID;
UInt32 ShaderProgram::_extGPUShader4                    = Window::invalidExtensionID;
UInt32 ShaderProgram::_extTransformFeedback2            = Window::invalidExtensionID;
UInt32 ShaderProgram::_extUniformBufferObject           = Window::invalidExtensionID;
UInt32 ShaderProgram::_extProgramInterfaceQuery         = Window::invalidExtensionID;
UInt32 ShaderProgram::_extShaderStorageBufferObject     = Window::invalidExtensionID;

UInt32 ShaderProgram::FuncIdCreateShader                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdDeleteShader                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdShaderSource                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdCompileShader               = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdAttachShader                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetShaderiv                 = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetShaderInfoLog            = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetActiveAttrib             = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdCreateProgram               = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdDeleteProgram               = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdLinkProgram                 = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetProgramiv                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetProgramInfoLog           = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUseProgram                  = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdGetUniformLocation          = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniform1i                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2i                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3i                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4i                   = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniform1ui                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2ui                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3ui                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4ui                  = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniform1f                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2f                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3f                   = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4f                   = Window::invalidFunctionID;


UInt32 ShaderProgram::FuncIdUniform1iv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2iv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3iv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4iv                  = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniform1uiv                 = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2uiv                 = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3uiv                 = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4uiv                 = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniform1fv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform2fv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform3fv                  = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniform4fv                  = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdUniformMatrix2fv            = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniformMatrix3fv            = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniformMatrix4fv            = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdGetUniformiv                = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetUniformfv                = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdProgramParameteri           = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdBindAttribLocation          = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdBindBufferBase              = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdTransformFeedbackVaryings   = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdBeginTransformFeedback      = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdEndTransformFeedback        = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdPauseTransformFeedback      = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdResumeTransformFeedback     = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdGetUniformBlockIndex        = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdUniformBlockBinding         = Window::invalidFunctionID;

UInt32 ShaderProgram::FuncIdGetProgramResourceIndex     = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdGetProgramResourceiv        = Window::invalidFunctionID;
UInt32 ShaderProgram::FuncIdShaderStorageBlockBinding   = Window::invalidFunctionID;

const Char8 *ShaderProgram::NextBufferToken = "gl_NextBuffer";

ShaderProgram::ProgramIdPool *ShaderProgram::_pProgIdPool = NULL;

template<> inline
void SimpleReusePool<Int32, 
                     ShaderProgram::ProgramIdPoolTag, 
                     SingleLockPolicy               >::initializeValue(void)
{
    _currentValue = 1;
}

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgram::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extSHL        = 
            Window::registerExtension("GL_ARB_shading_language_100");

        _extCG         = 
            Window::registerExtension("GL_EXT_Cg_shader");

        _extGeoShader4 = 
            Window::registerExtension("GL_EXT_geometry_shader4");

        _extGPUShader4  =
            Window::registerExtension("GL_EXT_gpu_shader4");

        _extTransformFeedback2 = 
            Window::registerExtension("GL_EXT_transform_feedback2");

        _extUniformBufferObject = 
            Window::registerExtension("GL_ARB_uniform_buffer_object");

        _extProgramInterfaceQuery = 
            Window::registerExtension("GL_ARB_program_interface_query");

        _extShaderStorageBufferObject = 
            Window::registerExtension("GL_ARB_shader_storage_buffer_object");


        FuncIdCreateShader =
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glCreateShader",
             _extSHL);

        FuncIdDeleteShader =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDeleteShader",
                _extSHL);
        
        FuncIdShaderSource =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glShaderSource",
                _extSHL);
        
        FuncIdCompileShader =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCompileShader",
                _extSHL);
        
        FuncIdAttachShader =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glAttachShader",
                _extSHL);
        
        FuncIdGetShaderiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetShaderiv",
                _extSHL);
        
        FuncIdGetShaderInfoLog =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetShaderInfoLog",
                _extSHL);

        FuncIdGetActiveAttrib =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetActiveAttrib",
                _extSHL);


        FuncIdCreateProgram =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCreateProgram",
                _extSHL);

        FuncIdDeleteProgram =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDeleteProgram",
                _extSHL);

        FuncIdLinkProgram =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glLinkProgram",
                _extSHL);

        FuncIdGetProgramiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetProgramiv",
                _extSHL);

        FuncIdGetProgramInfoLog =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetProgramInfoLog",
                _extSHL);

        FuncIdUseProgram =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUseProgram",
                _extSHL);


        FuncIdGetUniformLocation =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformLocationARB",
                _extSHL);

        // int{,2,3,4} uniforms
        FuncIdUniform1i =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1iARB",
                _extSHL);

        FuncIdUniform2i =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2iARB",
                _extSHL);

        FuncIdUniform3i =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3iARB",
                _extSHL);

        FuncIdUniform4i =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4iARB",
                _extSHL);

        // uint{,2,3,4} uniforms
        FuncIdUniform1ui =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1uiEXT",
                _extSHL);

        FuncIdUniform2ui =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2uiEXT",
                _extSHL);

        FuncIdUniform3ui =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3uiEXT",
                _extSHL);

        FuncIdUniform4ui =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4uiEXT",
                _extSHL);

        // float, vec{2,3,4} uniforms
        FuncIdUniform1f =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1fARB",
                _extSHL);

        FuncIdUniform2f =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2fARB",
                _extSHL);

        FuncIdUniform3f =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3fARB",
                _extSHL);

        FuncIdUniform4f =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4fARB",
                _extSHL);

        // int{,2,3,4} uniform arrays
        FuncIdUniform1iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1ivARB",
                _extSHL);

        FuncIdUniform2iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2ivARB",
                _extSHL);
        FuncIdUniform3iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3ivARB",
                _extSHL);
        FuncIdUniform4iv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4ivARB",
                _extSHL);

        // uint{,2,3,4} uniform arrays
        FuncIdUniform1uiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1uivEXT",
                _extSHL);

        FuncIdUniform2uiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2uivEXT",
                _extSHL);
        FuncIdUniform3uiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3uivEXT",
                _extSHL);
        FuncIdUniform4uiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4uivEXT",
                _extSHL);

        // float, vec{2,3,4} uniform arrays
        FuncIdUniform1fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform1fvARB",
                _extSHL);

        FuncIdUniform2fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform2fvARB",
                _extSHL);

        FuncIdUniform3fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform3fvARB",
                _extSHL);

        FuncIdUniform4fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniform4fvARB",
                _extSHL);


        FuncIdUniformMatrix2fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniformMatrix2fvARB",
                _extSHL);

        FuncIdUniformMatrix3fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniformMatrix3fvARB",
                _extSHL);

        FuncIdUniformMatrix4fv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniformMatrix4fvARB",
                _extSHL);

        FuncIdGetUniformiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformivARB",
                _extSHL);

        FuncIdGetUniformfv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformfvARB",
                _extSHL);

        FuncIdProgramParameteri =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glProgramParameteriEXT", 
                _extGeoShader4);

        FuncIdBindAttribLocation = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBindAttribLocationARB",
                _extSHL);

        FuncIdBindBufferBase = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBindBufferBase",
                _extTransformFeedback2);

        FuncIdTransformFeedbackVaryings =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glTransformFeedbackVaryings",
                _extTransformFeedback2);

        FuncIdBeginTransformFeedback =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBeginTransformFeedback",
                _extTransformFeedback2);

        FuncIdEndTransformFeedback =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glEndTransformFeedback",
                _extTransformFeedback2);

        FuncIdPauseTransformFeedback =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glPauseTransformFeedback",
                _extTransformFeedback2);

        FuncIdResumeTransformFeedback =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glResumeTransformFeedback",
                _extTransformFeedback2);

        FuncIdGetUniformBlockIndex =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetUniformBlockIndex",
                _extUniformBufferObject);

        FuncIdUniformBlockBinding =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glUniformBlockBinding",
                _extUniformBufferObject);

        FuncIdGetProgramResourceIndex =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetProgramResourceIndex",
                _extProgramInterfaceQuery);

        FuncIdGetProgramResourceiv =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGetProgramResourceiv",
                _extProgramInterfaceQuery);

        FuncIdShaderStorageBlockBinding =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glShaderStorageBlockBinding",
                _extShaderStorageBufferObject);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderProgram::ShaderProgram(void) :
     Inherited( ),
    _uiProgId (0)
{
}

ShaderProgram::ShaderProgram(const ShaderProgram &source) :
     Inherited(source),
    _uiProgId (0     )
{
}

ShaderProgram::~ShaderProgram(void)
{
}

void ShaderProgram::onCreate(const ShaderProgram *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
    {
        if(_pProgIdPool == NULL)
        {
            _pProgIdPool = new ProgramIdPool;
        }

        return;
    }

    setGLId(               
        Window::registerGLObject(
            boost::bind(&ShaderProgram::handleGL, 
                        ShaderProgramMTUncountedPtr(this), 
                        ::boost::placeholders::_1,
                        ::boost::placeholders::_2,
                        ::boost::placeholders::_3,
                        ::boost::placeholders::_4),
            &ShaderProgram::handleDestroyGL));

    _uiProgId = _pProgIdPool->create();
}

void ShaderProgram::onCreateAspect(const ShaderProgram *createAspect,
                                   const ShaderProgram *source)
{
    Inherited::onCreateAspect(createAspect, source);

    _uiProgId = createAspect->_uiProgId;
}

void ShaderProgram::onDestroy(UInt32 uiId)
{
    if(GlobalSystemState == OSG::Running)
    {
        _pProgIdPool->release(_uiProgId);

        if(getGLId() > 0)
            Window::destroyGLObject(getGLId(), 1);
    }
    else if(GlobalSystemState == OSG::Shutdown)
    {
        delete _pProgIdPool;
        
        _pProgIdPool = NULL;
    }

    Inherited::onDestroy(uiId);
}

void ShaderProgram::onDestroyAspect(UInt32 uiContainerId,
                                    UInt32 uiAspect     )
{
    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

void ShaderProgram::resolveLinks(void)
{
    MFDestroyedFunctorsType::const_iterator dfIt  =
        _mfDestroyedFunctors.begin();
    MFDestroyedFunctorsType::const_iterator dfEnd =
        _mfDestroyedFunctors.end();

    for(; dfIt != dfEnd; ++dfIt)
    {
        if(dfIt->_func.empty() == false)
            (dfIt->_func)(this, 0x0000, ChangedOrigin::External);
    }

    Inherited::resolveLinks();
}

UInt32 ShaderProgram::handleGL(DrawEnv                 *pEnv, 
                               UInt32                   id, 
                               Window::GLObjectStatusE  mode,
                               UInt64                   uiOptions)
{
    Window *pWin = pEnv->getWindow();

    if(pWin->hasExtOrVersion(_extSHL, 0x0200, 0x0200) == false)
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        pWin->setGLObjectId(id, 0);

        return 0;
    }

    if(mode == Window::initialize   || 
       mode == Window::reinitialize ||
       mode == Window::needrefresh   )
    {
        if( mode                         != Window::needrefresh && 
           _sfProgram.getValue().empty() == false                )
        {
            GLuint uiShader = GLuint(pWin->getGLObjectId(getGLId()));

#ifdef OSG_DEBUG
            if(mode == Window::initialize && uiShader != 0)
            {
                FWARNING(("ShaderProgram::handleGL: "
                          "Initialize with non-zero GL object Id.\n"));

                uiShader = 0;
            }
#endif

            if(uiShader == 0)
//            if(mode == Window::initialize)
            {      
                OSGGETGLFUNCBYID_GL3_ES(glCreateShader,
                                        osgGlCreateShader,
                                        FuncIdCreateShader,
                                        pWin);

                GLenum shaderType = _sfShaderType.getValue();

                if(_sfCgFrontEnd.getValue() == true)
                {
                    if(pWin->hasExtension(_extCG))
                    {
                        switch(shaderType)
                        {
                            case GL_VERTEX_SHADER:
                                shaderType = GL_CG_VERTEX_SHADER_EXT;
                                break;
                            case GL_FRAGMENT_SHADER:
                                shaderType = GL_CG_FRAGMENT_SHADER_EXT;
                                break;
                        }
                    }
                    else
                    {
                        FWARNING(("EXT_Cg_shader extension not supported, "
                                  "using GLSL front end!\n"));
                    }
                }

                uiShader = osgGlCreateShader(shaderType);
            }

            if(uiShader == 0)
                return 0;

            const Char8 *source  = _sfProgram.getValue().c_str();

            OSGGETGLFUNCBYID_GL3_ES(glShaderSource,
                                    osgGlShaderSource,
                                    FuncIdShaderSource,
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glCompileShader,
                                    osgGlCompileShader,
                                    FuncIdCompileShader,
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glGetShaderiv,
                                    osgGlGetShaderiv,
                                    FuncIdGetShaderiv,
                                    pWin);

            if(_sfDefines.getValue().empty() == true)
            {
                osgGlShaderSource(uiShader, 
                                  1, 
                                  static_cast<const char **>(&source), 
                                  0);
            }
            else
            {
                const Char8 *defines = _sfDefines.getValue().c_str();

                const char *shaderSources[2] = 
                {
                    defines,
                    source
                };

                osgGlShaderSource(uiShader, 
                                  2, 
                                  shaderSources, 
                                  0);
            }

            osgGlCompileShader(uiShader);

            GLint iStatus = 0;

            osgGlGetShaderiv( uiShader, 
                              GL_COMPILE_STATUS, 
                             &iStatus);

            if(iStatus == 0)
            {
                GLint  iDebugLength;

                osgGlGetShaderiv( uiShader, 
                                  GL_INFO_LOG_LENGTH, 
                                 &iDebugLength);

                if(iDebugLength > 0)
                {
                    Char8 *szDebug = new Char8[iDebugLength];

                    OSGGETGLFUNCBYID_GL3_ES(glGetShaderInfoLog,
                                            osgGlGetShaderInfoLog,
                                            FuncIdGetShaderInfoLog,
                                            pWin);

                    osgGlGetShaderInfoLog( uiShader, 
                                           iDebugLength, 
                                          &iDebugLength, 
                                           szDebug     );
                    
                    FFATAL(( "Couldn't compile shader program (0x%x)!\n%s\n", 
                            _sfShaderType.getValue(),
                             szDebug));

                    delete [] szDebug;
                }

                // log source that failed to compile
                FINFO(("Shader source was:\n"));

                if(_sfDefines.getValue().empty() == false)
                {
                    FPINFO(("%s\n", _sfDefines.getValue().c_str()));
                }

                FPINFO(("%s\n", source));

                OSGGETGLFUNCBYID_GL3_ES(glDeleteShader,
                                        osgGlDeleteShader,
                                        FuncIdDeleteShader,
                                        pWin);

                osgGlDeleteShader(uiShader);

                uiShader = 0;
            }

            pWin->setGLObjectId(getGLId(), uiShader);
        }

        //updateProgramParameters(win);
        //updateParameters(win,
        //*getMFParameters(),
        //true,
        //true /*mode != Window::needrefresh*/);
    }

    return 0;
}

void ShaderProgram::handleDestroyGL(DrawEnv                 *pEnv, 
                                    UInt32                   id, 
                                    Window::GLObjectStatusE  mode)
{
    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_extSHL, 0x0200, 0x0200))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        pWin->setGLObjectId(id, 0);

        return;
    }

    if(mode == Window::destroy)
    {
        GLuint uiShader = GLuint(pWin->getGLObjectId(id));

        if(uiShader != 0)
        {
            OSGGETGLFUNCBYID_GL3_ES(glDeleteShader,
                                    osgGlDeleteShader,
                                    FuncIdDeleteShader,
                                    pWin);
            
            osgGlDeleteShader(uiShader);

            pWin->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
}


/*----------------------------- class specific ----------------------------*/

void ShaderProgram::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & VariablesFieldMask))
    {
        if(details ==  0x0001)
        {
            MFParentFieldContainerPtr::const_iterator parentsIt  = 
                this->_mfParents.begin();
        
            MFParentFieldContainerPtr::const_iterator parentsEnd = 
                this->_mfParents.end();
            
            while(parentsIt != parentsEnd)
            {
                (*parentsIt)->changed(
                    TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
                    ChangedOrigin::Child,
                    VariablesFieldMask);
                
                ++parentsIt;
            }
        }
    }

    if(0x0000 != (whichField & ProgramFieldMask))
    {
        MFParentFieldContainerPtr::const_iterator parentsIt  = 
            this->_mfParents.begin();
        
        MFParentFieldContainerPtr::const_iterator parentsEnd = 
            this->_mfParents.end();
        
        while(parentsIt != parentsEnd)
        {
            (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
                ChangedOrigin::Child,
                ProgramFieldMask);
            
            ++parentsIt;
        }


        Window::reinitializeGLObject(this->getGLId());
    }
}

ShaderProgramTransitPtr ShaderProgram::createVertexShader(
    bool bCreateDefAttribMap)
{
    ShaderProgramTransitPtr returnValue = ShaderProgram::create();

    returnValue->setShaderType(GL_VERTEX_SHADER);

    if(bCreateDefAttribMap == true)
        returnValue->createDefaulAttribMapping();

    return returnValue;
}

ShaderProgramTransitPtr ShaderProgram::createGeometryShader(void)
{
    ShaderProgramTransitPtr returnValue = ShaderProgram::create();

    returnValue->setShaderType(GL_GEOMETRY_SHADER_EXT);

    return returnValue;
}

ShaderProgramTransitPtr ShaderProgram::createFragmentShader(void)
{
    ShaderProgramTransitPtr returnValue = ShaderProgram::create();

    returnValue->setShaderType(GL_FRAGMENT_SHADER);

    return returnValue;
}

void ShaderProgram::accumulateFeedback(
    DrawEnv                    *pEnv,
    UInt32                      uiProgram,
    std::vector<const Char8 *> &vTFVaryings,
    UInt32                     &uiVaryingBufferIndex)
{
    if(((_sfShaderType.getValue() == GL_VERTEX_SHADER)      ||
        (_sfShaderType.getValue() == GL_GEOMETRY_SHADER_EXT)  ) == false)
    {
        return;
    }

    if(vTFVaryings.size() != 0)
    {
        vTFVaryings.push_back(NextBufferToken);
    }

    MFFeedbackVaryingsType::const_iterator vIt  =
        this->getMFFeedbackVaryings()->begin();
    MFFeedbackVaryingsType::const_iterator vEnd =
        this->getMFFeedbackVaryings()->end  ();
    
    for(; vIt != vEnd; ++vIt)
    {
        vTFVaryings.push_back((*vIt).c_str());
    }
}

void ShaderProgram::addParent(FieldContainer * const pParent,
                              UInt16                 uiParentFieldId)
{
    editMField(ParentsFieldMask, _mfParents);
    
    OSG_ASSERT(pParent != NULL);

    _mfParents.push_back(pParent, uiParentFieldId);
}

void ShaderProgram::subParent(FieldContainer * const pParent)
{
    Int32 iParentIdx = _mfParents.findIndex(pParent);

    if(iParentIdx != -1)
    {
        editMField(ParentsFieldMask, _mfParents);

        _mfParents.erase(iParentIdx);
    }
}

void ShaderProgram::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderProgram NI" << std::endl;
}

bool ShaderProgram::readProgram(const Char8 *file)
{
    return readProgram(editSFProgram()->getValue(), file);
}

bool ShaderProgram::subUniformVariable(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
#if 0
        return _sfVariables.getValue()->subUniformVariable(
            name,
            editMFVariableLocations(),
            editMFProceduralVariableLocations());
#else
        return _sfVariables.getValue()->subUniformVariable(
            name,
            NULL,
            NULL);
#endif                                                     
    }

    return false;
}

void ShaderProgram::clearUniformVariables(void)
{
    if(_sfVariables.getValue() != NULL)
    {
        _sfVariables.getValue()->clearUniformVariables();
    }
}


bool ShaderProgram::subUniformBlock(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
#if 0
        return _sfVariables.getValue()->subUniformBlock(
            name,
            editMFBlockLocations(),
            editMFProceduralVariableLocations());
#else
        return _sfVariables.getValue()->subUniformBlock(
            name,
            NULL,
            NULL);
#endif                                                     
    }

    return false;
}

bool ShaderProgram::subShaderStorageBlock(const Char8 *name)
{
    if(_sfVariables.getValue() != NULL)
    {
#if 0
        return _sfVariables.getValue()->subShaderStorageBlock(
            name,
            editMFBlockLocations(),
            editMFProceduralVariableLocations());
#else
        return _sfVariables.getValue()->subShaderStorageBlock(
            name,
            NULL,
            NULL);
#endif                                                     
    }

    return false;
}

bool ShaderProgram::addProceduralVariable(const Char8          *name,
                                                ProcVarFunctor  pFunc,
                                                UInt32          uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

#if 0
    return _sfVariables.getValue()->addProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
#else
    return _sfVariables.getValue()->addProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        NULL);
#endif
}

bool ShaderProgram::addNodeProceduralVariable(
    const Char8              *name,
          ProcVarNodeFunctor  pFunc,
          UInt32              uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

#if 0
    return _sfVariables.getValue()->addNodeProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        editMFProceduralVariableLocations());
#else
    return _sfVariables.getValue()->addNodeProceduralVariable(
        name, 
        pFunc,
        uiDependency,
        NULL);
#endif
}

/*! \nohierarchy
 */

struct ParamEqual
{
    GLenum _ref;

    ParamEqual(GLenum ref) : 
        _ref(ref) 
    {
    }
    
    bool operator() (const ShaderParameter &lhs)
    {
        return lhs.first == _ref;
    }
};

void ShaderProgram::setProgramParameter(GLenum name, UInt32 value)
{
    editMField(ParameterFieldMask, _mfParameter);

    MFShaderParameter::iterator pIt = 
        std::find_if(_mfParameter.begin(),
                     _mfParameter.end  (),
                     ParamEqual        (name));

    if(pIt != _mfParameter.end())
    {
        pIt->second = value;
    }
    else
    {
        ShaderParameter tmpParam;

        tmpParam.first  = name;
        tmpParam.second = value;

        _mfParameter.push_back(tmpParam);
    }
}

void ShaderProgram::subProgramParameter(GLenum name)
{
    MFShaderParameter::iterator pIt = 
        std::find_if(_mfParameter.begin(),
                     _mfParameter.end  (),
                     ParamEqual        (name));

    if(pIt != _mfParameter.end())
    {
        editMField(ParameterFieldMask, _mfParameter);
        
        _mfParameter.erase(pIt);
    }
}

struct AttribEqual
{
    UInt16 _ref;

    AttribEqual(UInt16 ref) : 
        _ref(ref) 
    {
    }
    
    bool operator() (const ShaderAttribute &lhs)
    {
        return lhs.first == _ref;
    }
};

void ShaderProgram::setProgramAttribute(UInt16 uiIndex, std::string szName)
{
    editMField(AttributesFieldMask, _mfAttributes);

    MFShaderAttribute::iterator aIt = 
        std::find_if(_mfAttributes.begin(),
                     _mfAttributes.end  (),
                     AttribEqual        (uiIndex));
    

    if(aIt != _mfAttributes.end())
    {
        aIt->second = szName;
    }
    else
    {
        ShaderAttribute tmpAttr;

        tmpAttr.first  = uiIndex;
        tmpAttr.second = szName;

        _mfAttributes.push_back(tmpAttr);
    }
}

void ShaderProgram::subProgramAttribute(UInt16 uiIndex)
{
    MFAttributesType::iterator aIt = 
        std::find_if(_mfAttributes.begin(),
                     _mfAttributes.end  (),
                     AttribEqual        (uiIndex));

    if(aIt != _mfAttributes.end())
    {
        editMField(AttributesFieldMask, _mfAttributes);
        
        _mfAttributes.erase(aIt);
    }
}

void ShaderProgram::createDefaulAttribMapping(void)
{
    if(_sfShaderType.getValue() == GL_VERTEX_SHADER)
    {
        this->setProgramAttribute(ShaderConstants::Attribute0Index,  
                                  "osg_Vertex"                     );
        this->setProgramAttribute(ShaderConstants::Attribute2Index, 
                                  "osg_Normal"                     );

        this->setProgramAttribute(ShaderConstants::Attribute3Index,  
                                  "osg_Color"                      );
        this->setProgramAttribute(ShaderConstants::Attribute4Index,  
                                  "osg_SecondaryColor"             );

        this->setProgramAttribute(ShaderConstants::Attribute8Index,  
                                  "osg_MultiTexCoord0"             );
        this->setProgramAttribute(ShaderConstants::Attribute9Index,  
                                  "osg_MultiTexCoord1"             );
        this->setProgramAttribute(ShaderConstants::Attribute10Index, 
                                  "osg_MultiTexCoord2"             );
        this->setProgramAttribute(ShaderConstants::Attribute11Index,
                                  "osg_MultiTexCoord3"             );
        this->setProgramAttribute(ShaderConstants::Attribute12Index,
                                  "osg_MultiTexCoord4"             );
        this->setProgramAttribute(ShaderConstants::Attribute13Index,
                                  "osg_MultiTexCoord5"             );
        this->setProgramAttribute(ShaderConstants::Attribute14Index,
                                  "osg_MultiTexCoord6"             );
        this->setProgramAttribute(ShaderConstants::Attribute15Index,
                                  "osg_MultiTexCoord7"             );
    }
    else
    {
        FWARNING(("attrib map can only be created for a vertex shader"));
    }
}


bool ShaderProgram::addOSGVariable(const Char8 *name)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::create();

        setVariables(pVar);
    }

#if 0
    return _sfVariables.getValue()->addOSGVariable(
        name, 
        editMFProceduralVariableLocations());
#else
    return _sfVariables.getValue()->addOSGVariable(name, 
                                                   NULL);
#endif
}

bool ShaderProgram::updateProceduralVariable(const Char8          *name,
                                                   ProcVarFunctor  pFunc,
                                                   UInt32          uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateProceduralVariable(name, 
                                                             pFunc,
                                                             uiDependency);
}

bool ShaderProgram::updateNodeProceduralVariable(
    const Char8              *name,
          ProcVarNodeFunctor  pFunc,
          UInt32              uiDependency)
{
    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pParam = 
            ShaderProgramVariables::create();

        setVariables(pParam);
    }

    return _sfVariables.getValue()->updateNodeProceduralVariable(name, 
                                                                 pFunc,
                                                                 uiDependency);
}

bool ShaderProgram::readProgram(      std::string  &szTarget,
                                const Char8        *szFilename)
{
    std::ifstream s(szFilename);
    
    if(s.good())
    {
        return readProgram(szTarget, s);
    }
    else
    {
        FWARNING(("ShaderChunk::readProgram: couldn't open '%s' "
                  "for reading!\n", szFilename));

        return false;
    }

}

bool ShaderProgram::readProgram(std::string  &szTarget,
                                std::istream &iStream)
{
#define BUFSIZE 200
    
    szTarget.erase();

    Char8 buf[BUFSIZE];

    if(!iStream.good())
    {
        FWARNING(("SHLChunk::readProgram: stream is not good!\n"));

        return false;
    }
    
    do
    {
        iStream.read(buf, BUFSIZE);

        szTarget.append(buf, iStream.gcount());
    }
    while(!iStream.eof());
    
    return true;
}

OSG_END_NAMESPACE
