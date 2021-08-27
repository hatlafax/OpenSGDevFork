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

#include <boost/bind/bind.hpp>

#include "OSGConfig.h"

#include "OSGShaderExecutableChunk.h"
#include "OSGShaderProgramChunk.h"
#include "OSGShaderVariables.h"

#include "OSGGLFuncProtos.h"
#include "OSGConceptPropertyChecks.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderExecutableChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderExecutableChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderExecutableChunk::_class("ShaderExecutable", 1, 7);
volatile UInt16 ShaderExecutableChunk::_uiChunkCounter = 1;

UInt32 ShaderExecutableChunk::_extSHL = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderExecutableChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extSHL = Window::registerExtension("GL_ARB_shading_language_100");
    }
}

void ShaderExecutableChunk::resolveLinks(void)
{
    FragmentShaderIt fIt  = _mfFragmentShader.begin();
    FragmentShaderIt fEnd = _mfFragmentShader.end  ();

    for(; fIt != fEnd; ++fIt)
    {
        if(*fIt != NULL)
            (*fIt)->subParent(this);
    }

    GeometryShaderIt gIt  = _mfGeometryShader.begin();
    GeometryShaderIt gEnd = _mfGeometryShader.end  ();

    for(; gIt != gEnd; ++gIt)
    {
        if(*gIt != NULL)
            (*gIt)->subParent(this);
    }

    TessEvalShaderIt teIt  = _mfTessEvaluationShader.begin();
    TessEvalShaderIt teEnd = _mfTessEvaluationShader.end  ();

    for(; teIt != teEnd; ++teIt)
    {
        if(*teIt != NULL)
            (*teIt)->subParent(this);
    }

    TessControlShaderIt tcIt  = _mfTessControlShader.begin();
    TessControlShaderIt tcEnd = _mfTessControlShader.end  ();

    for(; tcIt != tcEnd; ++tcIt)
    {
        if(*tcIt != NULL)
            (*tcIt)->subParent(this);
    }

    VertexShaderIt vIt  = _mfVertexShader.begin();
    VertexShaderIt vEnd = _mfVertexShader.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        if(*vIt != NULL)
            (*vIt)->subParent(this);
    }
    
    Inherited::resolveLinks();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderExecutableChunk::ShaderExecutableChunk(void) :
     Inherited( ),
    _uiChunkId(0)
{
}

ShaderExecutableChunk::ShaderExecutableChunk(
    const ShaderExecutableChunk &source) :

     Inherited(source),
    _uiChunkId(0     )
{
}

ShaderExecutableChunk::~ShaderExecutableChunk(void)
{
}

void ShaderExecutableChunk::onCreate(const ShaderExecutableChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&ShaderExecutableChunk::handleGL, 
                        ShaderExecutableChunkMTUncountedPtr(this), 
                        ::boost::placeholders::_1,
                        ::boost::placeholders::_2,
                        ::boost::placeholders::_3,
                        ::boost::placeholders::_4),
            &ShaderExecutableChunk::handleDestroyGL));

    _uiChunkId = _uiChunkCounter++;
}

void ShaderExecutableChunk::onCreateAspect(
    const ShaderExecutableChunk *createAspect,
    const ShaderExecutableChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void ShaderExecutableChunk::onDestroy(UInt32 uiId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiId);
}

const StateChunkClass *ShaderExecutableChunk::getClass(void) const
{
    return &_class;
}

UInt16 ShaderExecutableChunk::getChunkId(void)
{
    return _uiChunkId;
}

UInt32 ShaderExecutableChunk::handleGL(DrawEnv                 *pEnv, 
                                       UInt32                   id, 
                                       Window::GLObjectStatusE  mode,
                                       UInt64                   uiOptions)
{
    UInt32  returnValue = 0;
    Window *pWin        = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_extSHL, 0x0200, 0x0200))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find "
                  "extension 'GL_ARB_shading_language_100'!\n"));

        pWin->setGLObjectId(getGLId(), 0);

        return returnValue;
    }

    if(mode == Window::initialize   || 
       mode == Window::reinitialize ||
       mode == Window::needrefresh   )
    {
        GLuint uiProgram = GLuint(pWin->getGLObjectId(getGLId()));;

        if(mode != Window::needrefresh)
        {
            if(uiProgram != 0)
            {
                OSGGETGLFUNCBYID_GL3_ES(
                    glDeleteProgram,
                    osgGlDeleteProgram,
                    ShaderProgram::getFuncIdDeleteProgram(),
                    pWin);

                osgGlDeleteProgram(uiProgram);
            }

            OSGGETGLFUNCBYID_GL3_ES(glCreateProgram,
                                    osgGlCreateProgram,
                                    ShaderProgram::getFuncIdCreateProgram(),
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glAttachShader,
                                    osgGlAttachShader,
                                    ShaderProgram::getFuncIdAttachShader(),
                                    pWin);

            OSGGETGLFUNCBYID_GL3_ES(glLinkProgram,
                                    osgGlLinkProgram,
                                    ShaderProgram::getFuncIdLinkProgram(),
                                    pWin);

            uiProgram = osgGlCreateProgram();

            FragmentShaderIt fIt  = _mfFragmentShader.begin();
            FragmentShaderIt fEnd = _mfFragmentShader.end  ();
            
            for(; fIt != fEnd; ++fIt)
            {
                (*fIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*fIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }
    
            std::vector<const Char8 *> vTFVaryings;
            UInt32                     uiVaryingBufferIndex = 0;

            GeometryShaderIt gIt  = _mfGeometryShader.begin();
            GeometryShaderIt gEnd = _mfGeometryShader.end  ();
            
            for(; gIt != gEnd; ++gIt)
            {
                (*gIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*gIt)->getGLId()));

                if(uiShader != 0)
                {
                    osgGlAttachShader(uiProgram, uiShader);

                    (*gIt)->accumulateFeedback(pEnv,
                                               uiProgram, 
                                               vTFVaryings,
                                               uiVaryingBufferIndex);
                }
            }
        
            TessEvalShaderIt teIt  = _mfTessEvaluationShader.begin();
            TessEvalShaderIt teEnd = _mfTessEvaluationShader.end  ();
            
            for(; teIt != teEnd; ++teIt)
            {
                (*teIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*teIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }


            TessControlShaderIt tcIt  = _mfTessControlShader.begin();
            TessControlShaderIt tcEnd = _mfTessControlShader.end  ();
            
            for(; tcIt != tcEnd; ++tcIt)
            {
                (*tcIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*tcIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }


            VertexShaderIt vIt  = _mfVertexShader.begin();
            VertexShaderIt vEnd = _mfVertexShader.end  ();

            for(; vIt != vEnd; ++vIt)
            {
                (*vIt)->validate(pEnv);

                GLuint uiShader = 
                    GLuint(pWin->getGLObjectId((*vIt)->getGLId()));

                if(uiShader != 0)
                    osgGlAttachShader(uiProgram, uiShader);
            }

            if(vTFVaryings.size() != 0)
            {
                OSGGETGLFUNCBYID_GL3(
                    glTransformFeedbackVaryings,
                    osgGlTransformFeedbackVaryings,
                    ShaderProgram::getFuncIdTransformFeedbackVaryings(),
                    pEnv->getWindow()                                  );

                osgGlTransformFeedbackVaryings(uiProgram, 
                                               GLsizei(vTFVaryings.size()), 
                                               &(vTFVaryings.front()),
                                               GL_INTERLEAVED_ATTRIBS); 
            }

            // attribute binding must be done before linking
            updateAttribBindings(pEnv, uiProgram);

            // parameters must be set before linking
            updateParameters(pEnv, uiProgram);
            
            osgGlLinkProgram(uiProgram);

            GLint  iInfoLength;
            Char8 *szInfoBuffer = NULL;

            OSGGETGLFUNCBYID_GL3_ES(glGetProgramiv,
                                    osgGlGetProgramiv,
                                    ShaderProgram::getFuncIdGetProgramiv(),
                                    pWin);

            osgGlGetProgramiv(uiProgram, 
                              GL_OBJECT_INFO_LOG_LENGTH_ARB, 
                              &iInfoLength);

            if(iInfoLength > 0)
            {
                szInfoBuffer = new Char8[iInfoLength];
                szInfoBuffer[0] = '\0';

                OSGGETGLFUNCBYID_GL3_ES(
                    glGetProgramInfoLog,
                    osgGlGetProgramInfoLog,
                    ShaderProgram::getFuncIdGetProgramInfoLog(),
                    pWin);

                osgGlGetProgramInfoLog( uiProgram, 
                                        iInfoLength, 
                                       &iInfoLength, 
                                        szInfoBuffer);
            }

            GLint iStatus = 0;

            osgGlGetProgramiv(uiProgram, GL_LINK_STATUS, &iStatus);

            GLint iNumAttribs      = 0;
            GLint iMaxAttribLength = 0;

            osgGlGetProgramiv(uiProgram, GL_ACTIVE_ATTRIBUTES, &iNumAttribs);

            osgGlGetProgramiv( uiProgram, 
                               GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
                              &iMaxAttribLength);

            if(iMaxAttribLength > 0)
            {
                Char8   *szAttribBuffer = NULL;
                GLsizei  iNameLength;
                GLint    iSizeTmp;
                GLenum   eTypeTmp;

                szAttribBuffer = new Char8[iMaxAttribLength];
                szAttribBuffer[0] = '\0';

                OSGGETGLFUNCBYID_GL3_ES(
                    glGetActiveAttrib,
                    osgGlGetActiveAttrib,
                    ShaderProgram::getFuncIdGetActiveAttrib(),
                    pWin);

                for(GLint i = 0; i < iNumAttribs; ++i)
                {
                    osgGlGetActiveAttrib( uiProgram,
                                          i, 
                                          iMaxAttribLength, 
                                         &iNameLength, 
                                         &iSizeTmp,
                                         &eTypeTmp,
                                          szAttribBuffer);

                    if(iNameLength != 0)
                    {
                        if(iNameLength       < 3    ||
                           szAttribBuffer[0] != 'g' ||
                           szAttribBuffer[1] != 'l' ||
                           szAttribBuffer[2] != '_'  )
                        {
                            pWin->setGLObjectInfo(getGLId(), UsesAttribs);

                            break;
                        }  
                        
                    }
                }

                delete [] szAttribBuffer;
            }

            if(iStatus == 0)
            {
                if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
                {
                    FFATAL(("Couldn't link vertex and fragment program!\n%s\n",
                            szInfoBuffer));

#ifdef OSG_DEBUG
                    if(!getMFVertexShader()->empty())
                    {
                        SINFO << "Vertex Shader Code:\n";

                        vIt  = getMFVertexShader()->begin();
                        vEnd = getMFVertexShader()->end  ();

                        for(; vIt != vEnd; ++vIt)
                        {
                            PINFO << (*vIt)->getProgram()
                                  << "\n";
                        }
                    }

                    if(!getMFTessControlShader()->empty())
                    {
                        SINFO << "TessControl Shader Code:\n";

                        tcIt  = getMFTessControlShader()->begin();
                        tcEnd = getMFTessControlShader()->end  ();

                        for(; tcIt != tcEnd; ++tcIt)
                        {
                            PINFO << (*tcIt)->getProgram()
                                  << "\n";
                        }
                    }

                    if(!getMFTessEvaluationShader()->empty())
                    {
                        SINFO << "TessEvaluation Shader Code:\n";

                        teIt  = getMFTessEvaluationShader()->begin();
                        teEnd = getMFTessEvaluationShader()->end  ();

                        for(; teIt != teEnd; ++teIt)
                        {
                            PINFO << (*teIt)->getProgram()
                                  << "\n";
                        }
                    }

                    if(!getMFGeometryShader()->empty())
                    {
                        SINFO << "Geometry Shader Code:\n";

                        gIt  = getMFGeometryShader()->begin();
                        gEnd = getMFGeometryShader()->end  ();

                        for(; gIt != gEnd; ++gIt)
                        {
                            PINFO << (*gIt)->getProgram()
                                  << "\n";
                        }
                    }

                    if(!getMFFragmentShader()->empty())
                    {
                        SINFO << "Fragment Shader Code:\n";

                        fIt  = getMFFragmentShader()->begin();
                        fEnd = getMFFragmentShader()->end  ();

                        for(; fIt != fEnd; ++fIt)
                        {
                            PINFO << (*fIt)->getProgram()
                                  << "\n";
                        }
                    }
#endif // OSG_DEBUG
                }
                else
                {
                    FFATAL(("Couldn't link vertex and fragment program!\n"
                            "No further info available\n"));
                }

                OSGGETGLFUNCBYID_GL3_ES(glDeleteProgram,
                                        osgGlDeleteProgram,
                                        ShaderProgram::getFuncIdDeleteProgram(),
                                        pWin);

                osgGlDeleteProgram(uiProgram);

                uiProgram = 0;
            }
            else
            {
                if(szInfoBuffer != NULL && szInfoBuffer[0] != '\0')
                {
                    FWARNING(("SHLChunk: link status: %s\n", szInfoBuffer));
                }
            }

            pWin->setGLObjectId(getGLId(), uiProgram);

            updateVariableLocations(pEnv, uiProgram);
            
            delete [] szInfoBuffer;
        }

        if(uiProgram != 0)
        {
            OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                    osgGlUseProgram,
                                    ShaderProgram::getFuncIdUseProgram(),
                                    pWin);

            pEnv->setActiveShader(uiProgram);
            osgGlUseProgram      (uiProgram);
        
            updateVariables(pEnv, uiProgram);
        
            if(0x0000 == (uiOptions & KeepProgActive))
            {
                pEnv->setActiveShader(0);
                osgGlUseProgram      (0);
            }
            else
            {
                returnValue |= ProgActive;
            }
        }
    }

    return returnValue;
}

void ShaderExecutableChunk::handleDestroyGL(DrawEnv                 *pEnv, 
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

    // BUG this is not called for every window!
    if(mode == Window::destroy)
    {
        GLuint uiProgram = GLuint(pWin->getGLObjectId(id));

        if(uiProgram != 0)
        {
            OSGGETGLFUNCBYID_GL3_ES(glDeleteProgram,
                                    osgGlDeleteProgram,
                                    ShaderProgram::getFuncIdDeleteProgram(),
                                    pWin);

            osgGlDeleteProgram(uiProgram);

            pWin->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
}

/*----------------------------- class specific ----------------------------*/

void ShaderExecutableChunk::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    bool bMarkChanged = false;

    if(0x0000 != (whichField & VariablesFieldMask))
    {
        ShaderProgramVariables *pVars = _sfVariables.getValue();

        if(pVars != NULL)
        {
            if(details == 0x0001)
            {
                // be save reset all locations

                if(pVars->getMFVariables()->size() == 0)
                {
                    editMFVariableLocations()->clear();
                }
                else
                {
                    editMFVariableLocations()->resize(
                        pVars->getMFVariables()->size(), 
                        -1);

                    std::fill(editMFVariableLocations()->begin(),
                              editMFVariableLocations()->end  (),
                              -1);
                }

                // be save reset all locations

                if(pVars->getMFProceduralVariables()->size() == 0     )
                {
                    editMFProceduralVariableLocations()->clear();
                }
                else
                {
                    editMFProceduralVariableLocations()->resize(
                        pVars->getMFProceduralVariables()->size(), 
                        -1);

                    std::fill(editMFProceduralVariableLocations()->begin(),
                              editMFProceduralVariableLocations()->end  (),
                              -1);
                }
            }
        }

        Window::refreshGLObject(this->getGLId());
    }

    if(0x0000 != (whichField & (VertexShaderFieldMask   | 
                                GeometryShaderFieldMask |
                                FragmentShaderFieldMask )))
    {
        if(details == ShaderProgram::ProgramFieldMask)
        {
            Window::reinitializeGLObject(this->getGLId());
        }

        else if(details == ShaderProgram::VariablesFieldMask)
        {
            this->remergeVariables();

            Window::refreshGLObject(this->getGLId());
        }
        
        bMarkChanged = true;
    }

    if(0x0000 != (whichField & (GeometryVerticesOutFieldMask | 
                                GeometryInputTypeFieldMask   | 
                                GeometryOutputTypeFieldMask  )))
    {
        // changing parameters requires re-linking the shader
        Window::reinitializeGLObject(this->getGLId());
    }

    if(bMarkChanged == true)
    {
        // be save reset all locations

        std::fill(editMFVariableLocations()->begin(),
                  editMFVariableLocations()->end  (),
                  -1);

        std::fill(editMFProceduralVariableLocations()->begin(),
                  editMFProceduralVariableLocations()->end  (),
                  -1);
    
        if(_sfVariables.getValue() != NULL)
        {
            _sfVariables.getValue()->markAllChanged();
        }
    }

    Inherited::changed(whichField, origin, details);
}

void ShaderExecutableChunk::dump(      UInt32    ,
                                 const BitVector ) const
{
    SLOG << "Dump ShaderExecutableChunk NI" << std::endl;
}

void ShaderExecutableChunk::activate(DrawEnv    *pEnv,              
                                     UInt32      uiIdx)
{
    Window *pWin     = pEnv->getWindow();
    UInt32  uiValRes = pWin->validateGLObject(getGLId(),
                                              pEnv,
                                              KeepProgActive);

    GLuint uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

    if(uiProgId == 0)
        return;

    if(0x0000 == (uiValRes & ProgActive))
    {
        OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                osgGlUseProgram,
                                ShaderProgram::getFuncIdUseProgram(),
                                pWin);

        pEnv->setActiveShader(uiProgId);
        osgGlUseProgram      (uiProgId);
    }

    if(_mfAttributes.size()                             == 0      && 
       (pWin->getGLObjectInfo(getGLId()) & UsesAttribs) == 0x0000   )
    {
        pEnv->addRequiredOGLFeature(HardwareContext::HasAttribAliasing);
    }

    pEnv->incNumShaderChanges();

    updateProceduralVariables(pEnv, ShaderProcVariable::SHDAll);

    if(_sfPointSize.getValue() == true)
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
}

void ShaderExecutableChunk::changeFrom(DrawEnv    *pEnv, 
                                       StateChunk *pOther, 
                                       UInt32      uiIdx)
{
    ShaderExecutableChunk *pOld = dynamic_cast<ShaderExecutableChunk *>(pOther);

    // pOther can be a SimpleSHLChunk, since we share our StateClass id with it
    if(pOld != NULL)
    {
        Window   *pWin     = pEnv->getWindow();
        GLuint    uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

        UInt32 uiDep = ShaderProcVariable::SHDObject;

        if(uiProgId != pEnv->getActiveShader())
        {
            UInt32 uiValRes = pWin->validateGLObject(getGLId(),
                                                     pEnv,
                                                     KeepProgActive);


            uiProgId = GLuint(pWin->getGLObjectId(getGLId()));

            if(uiProgId == 0)
                return;

            if(0x0000 == (uiValRes & ProgActive))
            {
                OSGGETGLFUNCBYID_GL3_ES(glUseProgram,
                                        osgGlUseProgram,
                                        ShaderProgram::getFuncIdUseProgram(),
                                        pWin);

                pEnv->setActiveShader(uiProgId);
                osgGlUseProgram      (uiProgId);
            }

            if(_mfAttributes.size()                             == 0     && 
               (pWin->getGLObjectInfo(getGLId()) & UsesAttribs) == 0x0000 )
            {
                pEnv->addRequiredOGLFeature(
                    HardwareContext::HasAttribAliasing);
            }

            if(_sfPointSize.getValue() == true)
            {
                if(pOld->getPointSize() == false)
                {
                    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
                }
            }
            else
            {
                if(pOld->getPointSize() == true)
                {
                    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
                }
            }

            uiDep = ShaderProcVariable::SHDAll;

            pEnv->incNumShaderChanges();
        }
        
        updateProceduralVariables(pEnv, uiDep);
    }
    else
    {
        pOther->deactivate(pEnv, uiIdx);
        activate          (pEnv, uiIdx);

        pEnv->incNumShaderChanges();
    }
}

void ShaderExecutableChunk::deactivate(DrawEnv    *pEnv,              
                                       UInt32      uiIdx)
{
    if(pEnv->getWindow()->getGLObjectId(getGLId()) == 0)
        return;

    OSGGETGLFUNC_GL3_ES(glUseProgram,
                        osgGlUseProgram,
                        ShaderProgram::getFuncIdUseProgram());
    
    if(_sfPointSize.getValue() == true)
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }

    pEnv->setActiveShader(0);

    pEnv->subRequiredOGLFeature(HardwareContext::HasAttribAliasing);

    if(pEnv->_openGLState.isTransformFeedbackActive() == true)
    {
        pEnv->_openGLState.setTransformFeedbackInactive();

        OSGGETGLFUNCBYID_GL3(glEndTransformFeedback,
                             osgGlEndTransformFeedback,
                             ShaderProgram::getFuncIdEndTransformFeedback(),
                             pEnv->getWindow());

        osgGlEndTransformFeedback();
    }

    osgGlUseProgram(0);
}

void ShaderExecutableChunk::updateObjectDependencies(DrawEnv    *pEnv, 
                                                     UInt32      index)
{
    updateProceduralVariables(pEnv, ShaderProcVariable::SHDObject);
}

void ShaderExecutableChunk::merge(const ShaderProgramChunk *pChunk)
{
    editMField(VertexShaderFieldMask,         _mfVertexShader        );
    editMField(TessControlShaderFieldMask,    _mfTessControlShader   );
    editMField(TessEvaluationShaderFieldMask, _mfTessEvaluationShader);
    editMField(GeometryShaderFieldMask,       _mfGeometryShader      );
    editMField(FragmentShaderFieldMask,       _mfFragmentShader      );
    editMField(AttributesFieldMask,           _mfAttributes          );

    if(_sfVariables.getValue() == NULL)
    {
        ShaderProgramVariablesUnrecPtr pVar = 
            ShaderProgramVariables::createDependent(
                this->getFieldFlags()->_bNamespaceMask);

        setVariables(pVar);
    }

    _mfVertexShader.reserve(_mfVertexShader.size() + 
                             pChunk->getMFVertexShader()->size());

    ShaderProgramChunk::MFVertexShaderType::const_iterator sIt  = 
        pChunk->getMFVertexShader()->begin();

    ShaderProgramChunk::MFVertexShaderType::const_iterator sEnd = 
        pChunk->getMFVertexShader()->end();

    _mfAttributes.clear();

    bool bPointSize = false;

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, VertexShaderFieldId);

        _mfVertexShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());

        bPointSize |= (*sIt)->getPointSize();

        if((*sIt)->hasAttributes() == true)
        {
            _mfAttributes.reserve(_mfAttributes.size() + 
                                  (*sIt)->getMFAttributes()->size());

            _mfAttributes.insert(_mfAttributes.end(),
                                 (*sIt)->getMFAttributes()->begin(),
                                 (*sIt)->getMFAttributes()->end  ());
        }
    }

    if(bPointSize != _sfPointSize.getValue())
    {
        this->setPointSize(bPointSize);
    }

    _mfTessControlShader.reserve(_mfTessControlShader.size() + 
                                  pChunk->getMFTessControlShader()->size());

    sIt  = pChunk->getMFTessControlShader()->begin();
    sEnd = pChunk->getMFTessControlShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, TessControlShaderFieldId);

        _mfTessControlShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());
    }

    _mfTessEvaluationShader.reserve(
        _mfTessEvaluationShader.size() + 
         pChunk->getMFTessEvaluationShader()->size());

    sIt  = pChunk->getMFTessEvaluationShader()->begin();
    sEnd = pChunk->getMFTessEvaluationShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, TessEvaluationShaderFieldId);

        _mfTessEvaluationShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());
    }



    _mfGeometryShader.reserve(_mfGeometryShader.size() + 
                               pChunk->getMFGeometryShader()->size());

    sIt  = pChunk->getMFGeometryShader()->begin();
    sEnd = pChunk->getMFGeometryShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, GeometryShaderFieldId);

        _mfGeometryShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());

        if((*sIt)->hasParameter() == true)
        {
            ShaderProgram::MFParameterType::const_iterator pIt  = 
                (*sIt)->getMFParameter()->begin();

            ShaderProgram::MFParameterType::const_iterator pEnd = 
                (*sIt)->getMFParameter()->end  ();

            while(pIt != pEnd)
            {
                switch(pIt->first)
                {
                    case GL_GEOMETRY_INPUT_TYPE_EXT:
                        this->setGeometryInputType(pIt->second);
                        break;
                        
                    case GL_GEOMETRY_OUTPUT_TYPE_EXT:
                        this->setGeometryOutputType(pIt->second);
                        break;

                    case GL_GEOMETRY_VERTICES_OUT_EXT:
                        this->setGeometryVerticesOut(pIt->second);
                        break;
                }

                ++pIt;
            }
        }
    }


    _mfFragmentShader.reserve(_mfFragmentShader.size() + 
                               pChunk->getMFFragmentShader()->size());

    sIt  = pChunk->getMFFragmentShader()->begin();
    sEnd = pChunk->getMFFragmentShader()->end  ();

    for(; sIt != sEnd; ++sIt)
    {
        (*sIt)->addParent(this, FragmentShaderFieldId);

        _mfFragmentShader.push_back(*sIt);
        
        _sfVariables.getValue()->merge(
            (*sIt)->getVariables(),
            this->editMFVariableLocations(),
            this->editMFProceduralVariableLocations());
    }
}

void ShaderExecutableChunk::remergeVariables(void)
{
    OSG_ASSERT(_sfVariables.getValue() != NULL);

    _sfVariables.getValue()->clearVariables();
    _sfVariables.getValue()->clearProceduralVariables();

    this->editMFVariableLocations          ()->clear();
    this->editMFProceduralVariableLocations()->clear();


    ShaderExecutableChunk::MFVertexShaderType::const_iterator sIt  = 
        _mfVertexShader.begin();

    ShaderExecutableChunk::MFVertexShaderType::const_iterator sEnd = 
        _mfVertexShader.end();


    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations(),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfTessControlShader.begin();
    sEnd = _mfTessControlShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfTessEvaluationShader.begin();
    sEnd = _mfTessEvaluationShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfGeometryShader.begin();
    sEnd = _mfGeometryShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }



    sIt  = _mfFragmentShader.begin();
    sEnd = _mfFragmentShader.end  ();

    for(; sIt != sEnd; ++sIt)
    {
        if(*sIt != NULL)
        {
            _sfVariables.getValue()->merge(
                (*sIt)->getVariables(),
                this->editMFVariableLocations          (),
                this->editMFProceduralVariableLocations());
        }
    }
}

void ShaderExecutableChunk::updateVariableLocations(DrawEnv *pEnv,
                                                    UInt32   uiProgram)
{
    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFVariablesType           *pMFVars     = NULL;
    const ShaderProgramVariables::MFProceduralVariablesType *pMFProcVars = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars     = _sfVariables.getValue()->getMFVariables          ();
        pMFProcVars = _sfVariables.getValue()->getMFProceduralVariables();
    }

    if(pMFVars != NULL && pMFVars->size() != 0)
    {
        MFInt32 &vVarLocations = *this->editMFVariableLocations();

        OSG_ASSERT(pMFVars->size() == vVarLocations.size());

        MFInt32::iterator mLocIt = vVarLocations.begin();
        
        ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
            pMFVars->begin();
        ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
            pMFVars->end  ();
        
        for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
        {
            osgUniformShaderVariableLocationSwitch(pEnv, *mVarIt, *mLocIt, uiProgram);
        }
    }

    if(pMFProcVars != NULL && pMFProcVars->size() != 0)
    {
        MFInt32 &vVarLocations = *this->editMFProceduralVariableLocations();

        OSG_ASSERT(pMFProcVars->size() == vVarLocations.size());

        MFInt32::iterator mLocIt = vVarLocations.begin();
        
        ShaderProgramVariables::MFProceduralVariablesType::const_iterator 
            mVarIt  = pMFProcVars->begin();
        ShaderProgramVariables::MFProceduralVariablesType::const_iterator 
            mVarEnd = pMFProcVars->end  ();
        
        for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
        {
            osgUniformShaderVariableLocationSwitch(pEnv, *mVarIt, *mLocIt, uiProgram);
        }
    }
}

void ShaderExecutableChunk::updateVariables(DrawEnv *pEnv,
                                            UInt32   uiProgram)
{
    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFVariablesType       *pMFVars   = NULL;
          ShaderProgramVariables::MFVariableChangedType *pMFVarChg = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars   = _sfVariables.getValue()->getMFVariables       ();
        pMFVarChg = _sfVariables.getValue()->editMFVariableChanged();
    }

    if(pMFVars == NULL || pMFVars->size() == 0 || pMFVarChg == NULL)
    {
        return;
    }

    OSG_ASSERT(pMFVars->size() == pMFVarChg->size());

    MFInt32 &vVarLocations = *this->editMFVariableLocations();

    OSG_ASSERT(pMFVars->size() == vVarLocations.size());

    MFInt32::iterator mLocIt = vVarLocations.begin();

    ShaderProgramVariables::MFVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

    ShaderProgramVariables::MFVariableChangedType::iterator mVarChgIt =
        pMFVarChg->begin();

    bool warnUnknown = ShaderVariable::WarnUnknown;

    for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt, ++mVarChgIt)
    {
        ShaderVariable *pVar = *mVarIt;

        if(pVar == NULL)
            continue;

        if(*mVarChgIt == false)
            continue;

        *mVarChgIt = false;

        osgUniformShaderVariableSwitch(pEnv,    pVar,
                                       *mLocIt, uiProgram, warnUnknown);
    }
}

void ShaderExecutableChunk::updateAttribBindings(DrawEnv *pEnv,
                                                 UInt32   uiProgram)
{
    MFAttributesType::const_iterator aIt  = _mfAttributes.begin();
    MFAttributesType::const_iterator aEnd = _mfAttributes.end  ();
        
    if(aIt == aEnd)
        return;

    OSGGETGLFUNC_GL3_ES(glBindAttribLocation,
                        osgGlBindAttribLocation,
                        ShaderProgram::getFuncIdBindAttribLocation());

    for(; aIt != aEnd; ++aIt)
    {
        osgGlBindAttribLocation(uiProgram, (*aIt).first, (*aIt).second.c_str());
    }
}

void ShaderExecutableChunk::updateParameters(DrawEnv *pEnv,
                                             UInt32   uiProgram)
{
    if(uiProgram == 0 || this->getGeometryVerticesOut() == 0)
        return;

    OSGGETGLFUNC_EXT(glProgramParameteriEXT,
                     osgGlProgramParameteriEXT,
                     ShaderProgram::getFuncIdProgramParameteri());

    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_VERTICES_OUT_EXT, 
                              this->getGeometryVerticesOut());
    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_INPUT_TYPE_EXT, 
                              this->getGeometryInputType());
    osgGlProgramParameteriEXT(uiProgram,
                              GL_GEOMETRY_OUTPUT_TYPE_EXT, 
                              this->getGeometryOutputType());
}

void ShaderExecutableChunk::updateProceduralVariables(
    DrawEnv *pEnv,
    UInt32   uiUpdateDependents)
{
    UInt32 uiProgram = pEnv->getActiveShader();

    if(uiProgram == 0)
        return;

    const ShaderProgramVariables::MFProceduralVariablesType *pMFVars = NULL;

    if(_sfVariables.getValue() != NULL)
    {
        pMFVars   = _sfVariables.getValue()->getMFProceduralVariables();
    }

    if(pMFVars == NULL || pMFVars->size() == 0)
    {
        return;
    }

    MFInt32 &vVarLocations = *this->editMFProceduralVariableLocations();

    OSG_ASSERT(pMFVars->size() == vVarLocations.size());

    MFInt32::iterator mLocIt = vVarLocations.begin();

    ShaderProgramVariables::MFProceduralVariablesType::const_iterator mVarIt  =
        pMFVars->begin();
    ShaderProgramVariables::MFProceduralVariablesType::const_iterator mVarEnd =
        pMFVars->end  ();

    Window *pWin = pEnv->getWindow();

    osgSinkUnusedWarning(pWin);

#ifdef OSG_1_COMPATX
    if(_fParameterCallback)
    {
        OSGGETGLFUNCBYID_GL3_ES(glGetUniformLocation,
                                osgGlGetUniformLocation,
                                ShaderProgram::getFuncIdGetUniformLocation(),
                                pWin);

        _fParameterCallback(osgGlGetUniformLocation, pEnv, uiProgram);
    }
#endif

    for(; mVarIt != mVarEnd; ++mVarIt, ++mLocIt)
    {
        ShaderVariable *pVar = *mVarIt;

        switch(pVar->getTypeId())
        {
            case ShaderVariable::SHVTypeOSG:
            {
                ShaderVariableOSG *p =
                    dynamic_cast<ShaderVariableOSG *>(pVar);

                if(0x0000 == (p->getDependency() & uiUpdateDependents))
                    continue;

                if(*mLocIt == -1)
                {
                    osgUniformShaderVariableLocationSwitch(pEnv, p, *mLocIt, uiProgram);

#ifdef OSG_MULTISHADER_VARCHUNK
                    if(*mLocIt == -1)
                        *mLocIt = -2;
#endif
                }

                p->evaluate(pEnv, *mLocIt);                
            }
            break;

            case ShaderVariable::SHVTypeFunctor:
            {
                ShaderVariableFunctor *p =
                    dynamic_cast<ShaderVariableFunctor *>(pVar);

                if(0x0000 == (p->getDependency() & uiUpdateDependents))
                    continue;

                if(*mLocIt == -1)
                {
                    osgUniformShaderVariableLocationSwitch(pEnv, p, *mLocIt, uiProgram);

#ifdef OSG_MULTISHADER_VARCHUNK
                    if(*mLocIt == -1)
                        *mLocIt = -2;
#endif
                }

#ifdef OSG_1_COMPAT
                switch(p->getFuncMode())
                {
                    case 0:
                    {
                        p->evaluate(pEnv, *mLocIt);                
                    }
                    break;
                        
                    case 1:
                    {
                        OSGGETGLFUNCBYID_GL3_ES(
                            glGetUniformLocation,
                            osgGlGetUniformLocation,
                            ShaderProgram::getFuncIdGetUniformLocation(),
                            pWin);

                        p->evaluate(osgGlGetUniformLocation,
                                    pEnv,
                                    uiProgram);
                    }
                    break;

                    case 2:
                    {
                        p->evaluate(p,
                                    pEnv,
                                    uiProgram);
                    }
                    break;
                }
#else
                p->evaluate(pEnv, *mLocIt);                
#endif
            }
            break;

            default:
                break;
        }
    }
}

OSG_END_NAMESPACE
