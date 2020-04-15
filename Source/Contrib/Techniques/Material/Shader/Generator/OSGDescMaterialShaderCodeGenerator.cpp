/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#include "OSGDescMaterialShaderCodeGenerator.h"
#include "OSGDescMaterial.h"

#include "OSGMaterialDesc.h"
#include "OSGEnvironmentDesc.h"
#include "OSGTextureDesc.h"
#include "OSGShaderDesc.h"

#include "OSGMultiLightChunk.h"
#include "OSGMultiLightShadowStage.h"
#include "OSGClusterShadingStage.h"
#include "OSGSSAOStage.h"
#include "OSGIBLStage.h"

#include "OSGShaderUtility.h"

//#define OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDescMaterialShaderCodeGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDescMaterialShaderCodeGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DescMaterialShaderCodeGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DescMaterialShaderCodeGenerator::DescMaterialShaderCodeGenerator(void) :
    Inherited()
{
}

DescMaterialShaderCodeGenerator::DescMaterialShaderCodeGenerator(const DescMaterialShaderCodeGenerator &source) :
    Inherited(source)
{
}

DescMaterialShaderCodeGenerator::~DescMaterialShaderCodeGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DescMaterialShaderCodeGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DescMaterialShaderCodeGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DescMaterialShaderCodeGenerator NI" << std::endl;
}

/*------------------------------- Interface -------------------------------*/

ShaderDescStoreTransitPtr DescMaterialShaderCodeGenerator::getShaderDescStore(
    ChunkMaterial* chunkMat)
{
    ShaderDescStoreUnrecPtr store = ShaderDescStore::createLocal();

    DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(chunkMat);

    if (descMaterial)
    {
        //
        // Vertex shader first, ...
        //
        std::stringstream vert_ost;

        getVertexProgram(vert_ost, descMaterial);

        ShaderDescUnrecPtr vertShaderDesc = ShaderDesc::createLocal();

        vertShaderDesc->setShaderType(GL_VERTEX_SHADER);
        vertShaderDesc->setProgram   (vert_ost.str());

        //
        // In case of fallback 2 we do not use uniform blocks, but individual uniform variables
        //
        if (!isFallbackShader2())
        {
            vertShaderDesc->editMFUniformBlockNames ()->push_back(descMaterial->getVertUniformBlockName  ());
            vertShaderDesc->editMFUniformBindingPnts()->push_back(descMaterial->getVertMaterialBindingPnt());
        }

        vertShaderDesc->editMFOSGVariables()->push_back("OSGWorldMatrix");
        vertShaderDesc->editMFOSGVariables()->push_back("OSGTransInvWorldMatrix");
        vertShaderDesc->editMFOSGVariables()->push_back("OSGProjectionMatrix");

        store->pushToStore(vertShaderDesc);

        //
        // ... then Fragment shader
        //

        std::stringstream frag_ost;
        
        getFragmentProgram(frag_ost, descMaterial);

        ShaderDescUnrecPtr fragShaderDesc = ShaderDesc::createLocal();

        fragShaderDesc->setShaderType(GL_FRAGMENT_SHADER);
        fragShaderDesc->setProgram   (frag_ost.str());

        //
        // In case of fallback 2 we do not use uniform blocks, but individual uniform variables
        //
        if (!isFallbackShader2())
        {
            fragShaderDesc->editMFUniformBlockNames ()->push_back(descMaterial->getFragEnvUniformBlockName  ());
            fragShaderDesc->editMFUniformBindingPnts()->push_back(descMaterial->getFragEnvironmentBindingPnt());

            fragShaderDesc->editMFUniformBlockNames ()->push_back(descMaterial->getFragUniformBlockName     ());
            fragShaderDesc->editMFUniformBindingPnts()->push_back(descMaterial->getFragMaterialBindingPnt   ());
        }

        fragShaderDesc->editMFOSGVariables()->push_back("OSGViewMatrix");
        fragShaderDesc->editMFOSGVariables()->push_back("OSGProjectionMatrix");
        fragShaderDesc->editMFOSGVariables()->push_back("OSGCameraPosition");

        //
        // If multilight is not supported or active we fallback to classic GL lights
        //
        MultiLightChunk* pChunk = isValidMultiLight() ? findMultiLightChunk() : NULL;
        if (pChunk)
        {
            fragShaderDesc->editMFShaderStorageBlockNames ()->push_back(pChunk->getLightBlockName ());
            fragShaderDesc->editMFShaderStorageBindingPnts()->push_back(        getLightBindingPnt());
        }
        else
        {
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight0Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight1Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight2Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight3Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight4Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight5Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight6Active");
            fragShaderDesc->editMFOSGVariables()->push_back("OSGLight7Active");
        }

        store->pushToStore(fragShaderDesc);
    }

    return ShaderDescStoreTransitPtr(store);
}

/*--------------------------- Shader Detail ---------------------------------*/

void DescMaterialShaderCodeGenerator::getVertexProgram(
    std::stringstream& ost, 
    DescMaterial*      descMaterial) const
{
    using namespace std;

    //
    // The information how the vertex shader is to be build come from
    //  a) the environment
    //  b) the material description
    //

    MaterialDesc* matDesc = descMaterial->getMaterialDesc();
    if (!matDesc)
        return;

    UInt32 numUVTextures = descMaterial->getNumUVTextures();

    //
    // The material specific code generation details are handeled by the 
    // description material object itself.
    //
    std::string vertProgramSnippet = descMaterial->getVertexProgramSnippet();

    //
    // We differentiate two type of shaders
    //  a) the modern shader that uses OpenGL language of 3.3. GLSL 3.30 and above
    //  b) fallback shader with differing capabilities like GSLS 120, 130,...
    //     support for bit operations and support for the switch statement.
    //

    std::string spc;

    //
    // On fallback we use shader language 120 or if possible 130
    //
    if (isFallbackShader2())
    {
        if (hasGLSL130Support())
        {
            ost 
            << endl << "#version 130"
            << endl << ""
            ;
        }
        else
        {
            ost 
            << endl << "#version 120"
            << endl << ""
            ;
        }
    }
    else
    {
        UInt32 glslVer = getGLSLVersion();

        UInt32 major = (glslVer >> 8);
        UInt32 minor = glslVer - (major << 8);

        ost 
        << endl << "#version " << major << minor << " compatibility"
        << endl << ""
        ;

        //
        // If we do not have completee OpenGL >= 4.40 support, we do
        // reley on extensions.
        //
        if (!isValidFull440ShaderSupport())
        {
            const ExtensionStore& extensions = getExtensions();

            ExtensionStore::const_iterator iter = extensions.begin();
            ExtensionStore::const_iterator end  = extensions.end  ();

            for (; iter != end; ++iter)
            {
                const std::string& ext = *iter;
                ost << endl << "#extension " << ext << " : enable";
            }

            ost
            << endl << ""
            ;
        }
    }

    UInt32 channels = matDesc->getNumUVChannels();
    UInt32 colors   = osgMin(matDesc->getNumColorChannels(), 2U);

    spc = channels > 2 ? " " : "";

    //
    // GLSL 120 does not know about in and out, but 130 does!
    // Modern GLSL however does support the layout location qualifier.
    //
    if (isFallbackShader2())
    {
        ost
        << endl << "attribute vec4 aVertex;"
        << endl << "attribute vec3 aNormal;"
        ;

        for (UInt32 c = 0; c < colors; ++c)
        {
            ost 
            << endl << "attribute vec3 aColor" << c << ";"
            ;
        }

        if (matDesc->getHasTangentsAndBitangentsMode())
        {
            ost
            << endl << "attribute vec3 aTangent;"
            << endl << "attribute vec3 aBitangent;"
            ;
        }

        for (UInt32 channel = 0; channel < channels; ++channel)
        {
            ost 
            << endl << "attribute vec2 aTexCoords" << channel << ";"
            ;
            //ost 
            //<< endl << "vec2 aTexCoords" << channel << " = gl_MultiTexCoord" << channel << ".xy;"
            //;
        }
    }
    else
    {
        ost
        << endl << "layout (location = " << spc << "0) in vec4 aVertex;"
        << endl << "layout (location = " << spc << "2) in vec3 aNormal;"
        ;

        for (UInt32 c = 0; c < colors; ++c)
        {
            ost 
            << endl << "layout (location = " << spc << 3 + c << ") in vec3 aColor" << c << ";"
            ;
        }

        if (matDesc->getHasTangentsAndBitangentsMode())
        {
            ost
            << endl << "layout (location = " << spc << "5) in vec3 aTangent;"
            << endl << "layout (location = " << spc << "6) in vec3 aBitangent;"
            ;
        }

        for (UInt32 channel = 0; channel < channels; ++channel)
        {
            ost 
            << endl << "layout (location = " << spc << 8 + channel << ") in vec2 aTexCoords" << channel << ";"
            ;
        }
    }

    ost 
    << endl << ""
    << endl << "uniform mat4 OSGWorldMatrix;"
    << endl << "uniform mat4 OSGTransInvWorldMatrix;"
    << endl << "uniform mat4 OSGProjectionMatrix;"
    << endl << ""
    ;

    std::string out = (isFallbackShader2() && !hasGLSL130Support() ? "varying" : "out");
#ifdef OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
    if (isValidClipPlanes())
    {
        if (isFallbackShader2())
        {
            if (hasGLSL130Support())
            {
                ost
                << endl << "uniform vec4 uClipPlanes[" << descMaterial->getMaxNumClipPlanes() << "];"
                << endl << ""
                << endl << out << " " << "float gl_ClipDistance[" << descMaterial->getMaxNumClipPlanes() << "];"
                << endl << ""
                ;
            }
        }
        else
        {
            ost
            << endl << "uniform vec4 uClipPlanes[" << descMaterial->getMaxNumClipPlanes() << "];"
            << endl << ""
            << endl << out << " " << "float gl_ClipDistance[" << descMaterial->getMaxNumClipPlanes() << "];"
            << endl << ""
            ;
        }
    }
#endif
    if (isFallbackShader2())
    {
        ;
    }
    else
    {
        ost
        << endl << "flat"
        ;
    }

    ost
    << endl << out << " " << "vec3 vNormalESFlat;"
    << endl << out << " " << "vec3 vNormalES;"
    ;
    if (matDesc->getHasTangentsAndBitangentsMode())
    {
        ost
        << endl << out << " " << "vec3 vTangentES;"
        << endl << out << " " << "vec3 vBitangentES;"
        ;
    }
    ost
    << endl << out << " " << "vec3 vPositionES;"
    << endl << ""
    << endl << out << " " << "vec3 vNormalWS;"
    << endl << out << " " << "vec3 vPositionWS;"
    << endl << ""
    ;
    if (colors > 0)
    {
        ost 
        << endl << out << " " << "vec3 vColors[" << colors << "];"
        << endl << ""
        ;
    }

    ost
    << vertProgramSnippet
    << endl << "void main()"
    << endl << "{"
    << endl << "    vec4 fragPosES = gl_ModelViewMatrix * aVertex;"
    << endl << "    vec4 fragPosWS =     OSGWorldMatrix * aVertex;"
    << endl << ""
    << endl << "    vPositionES = fragPosES.xyz;"
    << endl << "    vPositionWS = fragPosWS.xyz;"
    << endl << ""
    << endl << "    vNormalES =                gl_NormalMatrix * aNormal;"
    << endl << "    vNormalWS = mat3x3(OSGTransInvWorldMatrix) * aNormal;"
    << endl << ""
    ;
    if (matDesc->getHasTangentsAndBitangentsMode())
    {
        ost
    << endl << "    vTangentES   = gl_NormalMatrix * aTangent;"
    << endl << "    vBitangentES = gl_NormalMatrix * aBitangent;"
    << endl << ""
        ;
    }

    ost
    << endl << "    vNormalESFlat = vNormalES;"
    << endl << ""
    ;

    if (colors > 0)
    {
        for (UInt32 c = 0; c < colors; ++c)
        {
            ost 
    << endl << "    vColors[" << c << "] = aColor" << c << ";"
            ;
        }

        ost 
        << endl << ""
        ;
    }

    if (channels > 0 && numUVTextures > 0)
    {
        ost
    << endl << "    CalcTexCoords();"
    << endl << ""
        ;
    }

#ifdef OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
    if (isValidClipPlanes())
    {
        if (isFallbackShader2())
        {
            if (hasGLSL130Support())
            {
                ost
                << endl << ""
                << endl << "    for (int i = 0; i < " << descMaterial->getMaxNumClipPlanes() << "; ++i)"
                << endl << "        gl_ClipDistance[i] = dot(uClipPlanes[i], fragPosWS);"
                << endl << ""
                ;
            }
            else
            {
                ost
                << endl << "    gl_ClipVertex = gl_ModelViewMatrix * aVertex;"
                ;
            }
        }
        else
        {
            ost
            << endl << ""
            << endl << "    for (int i = 0; i < " << descMaterial->getMaxNumClipPlanes() << "; ++i)"
            << endl << "        gl_ClipDistance[i] = dot(uClipPlanes[i], fragPosWS);"
            << endl << ""
            ;
        }
    }
#else
    if (isValidClipPlanes())
    {
        ost
        << endl << "    gl_ClipVertex = gl_ModelViewMatrix * aVertex;"
        ;
    }
#endif
    ost
    << endl << "    gl_Position   = OSGProjectionMatrix * fragPosES;"
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterialShaderCodeGenerator::getFragmentProgram(
    std::stringstream& ost,
    DescMaterial*      descMaterial) const
{
    using namespace std;

    //
    // The information how the fragment shader is to be build come from
    //  a) the environment
    //  b) the material description
    //

    MaterialDesc* matDesc = descMaterial->getMaterialDesc   ();
    if (!matDesc)
        return;

    MultiLightChunk* pMLChunk = isValidMultiLight() ? findMultiLightChunk() : NULL;

    //
    // The material specific code generation details are handeled by the 
    // description material object itself.
    //
    DescMaterial::PairShadersT fragProgramSnippet = descMaterial->getFragmentProgramSnippet();

    //
    // We differentiate two type of shaders
    //  a) the modern shader that uses OpenGL language of 3.3. GLSL 3.30 and above
    //  b) fallback shader with differing capabilities like GSLS 120, 130,...
    //     support for bit operations and support for the switch statement.
    //

    //
    // On fallback we use shader language 120 or if possible 130
    //
    if (isFallbackShader2())
    {
        if (hasGLSL130Support())
        {
            ost 
            << endl << "#version 130"
            << endl << ""
            ;
        }
        else
        {
            ost 
            << endl << "#version 120"
            << endl << ""
            ;
        }

        const ExtensionStore& extensions = getExtensions();

        ExtensionStore::const_iterator iter = extensions.begin();
        ExtensionStore::const_iterator end  = extensions.end  ();

        for (; iter != end; ++iter)
        {
            const std::string& ext = *iter;
            ost << endl << "#extension " << ext << " : enable";
        }

        ost
        << endl << ""
        ;
    }
    else
    {
        UInt32 glslVer = getGLSLVersion();

        UInt32 major = (glslVer >> 8);
        UInt32 minor = glslVer - (major << 8);

        ost 
        << endl << "#version " << major << minor << " compatibility"
        << endl << ""
        ;

        //
        // If we do not have completee OpenGL >= 4.40 support, we do
        // reley on extensions.
        //
        if (!isValidFull440ShaderSupport())
        {
            const ExtensionStore& extensions = getExtensions();

            ExtensionStore::const_iterator iter = extensions.begin();
            ExtensionStore::const_iterator end  = extensions.end  ();

            for (; iter != end; ++iter)
            {
                const std::string& ext = *iter;
                ost << endl << "#extension " << ext << " : enable";
            }

            ost
            << endl << ""
            ;
        }
    }

    switch (matDesc->getShadingModel())
    {
        case MaterialDesc::NO_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// No shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::GOURAUD_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Gouraud shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::PHONG_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Phong shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
            break;
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Blinn-Phong shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
            break;
        case MaterialDesc::COOK_TORRANCE_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Cook-Torrance shading model with " << (matDesc->getPbrSpecularMode() ? "specular/glossiness" : "roughness/metalness") << " workflow"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Oren-Nayar shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::TOON_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Toon shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::GOOCH_SHADING_MODEL:
            {
                ost
                << endl << "//"
                << endl << "// Gooch shading model"
                << endl << "//"
                << endl << ""
                ;
            }
            break;
    }

    ost 
    << endl << Shader::getConstantsSnippet()
    << endl << ""
    << endl << Shader::getLanguageExtSnippet()
    << endl << ""
    << endl << Shader::getLocalFrameSnippet()
    << endl << ""
    << endl << Shader::getSRGBConversionSnippet(false)
    << endl << ""
#ifdef _DEBUG
    << endl << Shader::getEqualEpsSnippet()
    << endl << ""
    << endl << "vec3 error = vec3(0.5, 0.0, 0.0);"
    << endl << "vec3 red   = vec3(0.5, 0.0, 0.0);"
    << endl << "vec3 green = vec3(0.0, 0.5, 0.0);"
    << endl << "vec3 blue  = vec3(0.0, 0.0, 0.5);"
    << endl << "vec3 black = vec3(0.0, 0.0, 0.0);"
    << endl << ""
#endif
    ;

    if (isFallbackShader2() && !bUseCapabilities(CapabilitiesDesc::BIT_OPERATIONS))
    {
        ost
        << endl << "int BitAndOp(in int n1, in int n2)"
        << endl << "{"
        << endl << "    float v1 = float(n1);"
        << endl << "    float v2 = float(n2);"
        << endl << ""
        << endl << "    int byteVal = 1;"
        << endl << "    int result  = 0;"
        << endl << ""
        << endl << "    for (int i = 0; i < 32; i++)"
        << endl << "    {"
        << endl << "        bool keepGoing = v1 > 0.0 || v2 > 0.0;"
        << endl << "        if (keepGoing)"
        << endl << "        {"
        << endl << "            bool addOn = mod(v1, 2.0) > 0.0 && mod(v2, 2.0) > 0.0;"
        << endl << ""
        << endl << "            if (addOn)"
        << endl << "            {"
        << endl << "                result += byteVal;"
        << endl << "            }"
        << endl << ""
        << endl << "            v1 = floor(v1 / 2.0);"
        << endl << "            v2 = floor(v2 / 2.0);"
        << endl << ""
        << endl << "            byteVal *= 2;"
        << endl << "        }"
        << endl << "        else"
        << endl << "        {"
        << endl << "            return result;"
        << endl << "        }"
        << endl << "    }"
        << endl << "    return result;"
        << endl << "}"
        << endl << ""
        ;
    }

    if (isFallbackShader2())
    {
        ;
    }
    else
    {
        ost
        << endl << "flat"
        ;
    }

    std::string in = (isFallbackShader2() && !hasGLSL130Support() ? "varying" : "in");

    ost
    << endl << in << " " << "vec3 vNormalESFlat;"
    << endl << in << " " << "vec3 vNormalES;"
    ;
    if (matDesc->getHasTangentsAndBitangentsMode())
    {
        ost
        << endl << in << " " << "vec3 vTangentES;"
        << endl << in << " " << "vec3 vBitangentES;"
        ;
    }
    ost
    << endl << in << " " << "vec3 vPositionES;"
    << endl << ""
    << endl << in << " " << "vec3 vNormalWS;"
    << endl << in << " " << "vec3 vPositionWS;"
    ;

    UInt32 colors = osgMin(matDesc->getNumColorChannels(), 2U);

    if (colors > 0)
    {
        ost 
        << endl << ""
        << endl << in << " " << "vec3 vColors[" << colors << "];"
        ;
    }

    ost
    << endl << ""
    << endl << "uniform mat4 OSGViewMatrix;"
    << endl << "uniform mat4 OSGProjectionMatrix;"
    << endl << "uniform vec3 OSGCameraPosition;"
    << endl << ""
    ;

    if (isFallbackShader2())
    {
        ;
    }
    else
    {
        ost
        << endl << "layout(location = 0) out vec4 vFragColor;"
        << endl << ""
        ;
    }

    ost
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0);" // eye is at vec3(0,0,0) in eye space!
    ;

    ost
    << endl << ""
    << endl << "struct GeometricContext"
    << endl << "{"
    << endl << "    float frontCond;"
    << endl << "    vec3  N;"
    << endl << "    vec3  F;"
    << endl << "    vec3  V;"
    << endl << "    vec3  P;"
    << endl << "    vec3  L;"
    << endl << "    vec3  H;"
    << endl << "    float NdotL;"
    << endl << "    float NdotV;"
    << endl << "    float NdotH;"
    << endl << "    float LdotH;"
    ;
    if (descMaterial->getNeedTangentSpace())
    {
        ost
    << endl << "    vec3  T;"
    << endl << "    vec3  B;"
    << endl << "    mat3  matESFromTS;"
    << endl << "    mat3  matTSFromES;"
        ;
    }
    ost
    << endl << "};"
    << endl << ""
    << endl << "GeometricContext geomContext;"
    ;
    
    ost
    << endl << ""
    << fragProgramSnippet.first;
    ;

    getLightProgram(ost, descMaterial);

    if (isFallbackShader2())
    {
        ;
    }
    else
    {
        getShadowProgram(ost);
        getClusterProgram(ost);
        getSSAOProgram(ost, false); //descMaterial->getHasAmbientOcclusion());
    }

    getToneMapProgram(ost, descMaterial);

    ost
    << endl << ""
    << fragProgramSnippet.second;
    ;

    ost
    << endl << ""
    << endl << "void InitializeLight()"
    << endl << "{"
    ;
    if (!pMLChunk)
    {
        ost
    << endl << "    InitializeActiveLights();"
    << endl << ""
        ;
    }
    ost
    << endl << "    outLight = OutgoingLight(vec3(0.0),vec3(0.0),vec3(0.0),vec3(0.0), material.emissive);"
    << endl << "}"
    << endl << ""
    << endl << "void InitializeGeometryContext()"
    << endl << "{"
    ;

    if (matDesc->getCullFace() == GL_NONE)
    {
        ost
    << endl << "    geomContext.frontCond = float(gl_FrontFacing) * 2.0 - 1.0;"
    << endl << ""
    << endl << "    geomContext.P = vPositionES;"
    << endl << "    geomContext.N = geomContext.frontCond * normalize(vNormalES);"
    << endl << "    geomContext.F = geomContext.frontCond * normalize(vNormalESFlat);"
        ;
        if (descMaterial->getNeedTangentSpace())
        {
            if (matDesc->getHasTangentsAndBitangentsMode())
            {
                ost
    << endl << "    geomContext.T = geomContext.frontCond * normalize(vTangentES);"
    << endl << "    geomContext.B = geomContext.frontCond * normalize(vBitangentES);"
                ;
            }
        }
    }
    else
    {
        ost
    << endl << "    geomContext.P = vPositionES;"
    << endl << "    geomContext.N = normalize(vNormalES);"
    << endl << "    geomContext.F = normalize(vNormalESFlat);"
        ;
        if (descMaterial->getNeedTangentSpace())
        {
            if (matDesc->getHasTangentsAndBitangentsMode())
            {
                ost
    << endl << "    geomContext.T = normalize(vTangentES);"
    << endl << "    geomContext.B = normalize(vBitangentES);"
                ;
            }
        }
    }

    ost
    << endl << ""
    << endl << "    if (abs(OSGProjectionMatrix[2][3]) < OSG_EPS)"
    << endl << "        geomContext.V = vec3(0.0, 0.0, 1.0);"
    << endl << "    else"
    << endl << "        geomContext.V = normalize(cCameraPositionES - vPositionES);"
    << endl << "}"
    << endl << ""
    ;

    getMainFuncProgram(ost, descMaterial);
}


void DescMaterialShaderCodeGenerator::getLightProgram(
    std::stringstream& ost, DescMaterial* descMat) const
{
    using namespace std;

    const EnvironmentDesc* envDesc = descMat->getEnvironmentDesc();

    MultiLightChunk* pChunk = findMultiLightChunk();

    if (pChunk && isValidMultiLight())
    {
        //
        // The multi light knows best the correct shader layout
        //
        ost 
        << endl << ""
        << pChunk->getFragmentProgramSnippet(true, true)
        ;
    }
    else
    {
        // Provide default light implementation
        ost 
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
        ;

        if (pChunk)
        {
            ost 
            << pChunk->getFragmentProgramSnippet(true, false)
            ;
        }
        else
        {
            //
            // Here we must use standard OpenGL light
            //
            ost 
            << endl << ""
            << endl << "const int POINT_LIGHT       = " << MultiLight::POINT_LIGHT       << ";"
            << endl << "const int DIRECTIONAL_LIGHT = " << MultiLight::DIRECTIONAL_LIGHT << ";"
            << endl << "const int SPOT_LIGHT        = " << MultiLight::SPOT_LIGHT        << ";"
            << endl << "const int CINEMA_LIGHT      = " << MultiLight::CINEMA_LIGHT      << ";"
            << endl << ""
            << endl << "struct Light"
            << endl << "{"
            << endl << "    vec3  position;"
            << endl << "    vec3  direction;"
            << endl << "    vec3  intensity;"
            << endl << "    float constantAttenuation;"
            << endl << "    float linearAttenuation;"
            << endl << "    float quadraticAttenuation;"
            << endl << "    float cosSpotlightAngle;"
            << endl << "    float spotlightExponent;"
            << endl << "    int   type;"
            << endl << "    bool  enabled;"
            << endl << "};"
            << endl << ""
            << endl << "//"
            << endl << "// Calculate the attenuation of the light based on its"
            << endl << "// constant, linear and quadratic attenuation factors"
            << endl << "// and the distance d of the light to the current point."
            << endl << "//"
            << endl << "float calcAttenuation("
            << endl << "    in float c,"
            << endl << "    in float l,"
            << endl << "    in float q,"
            << endl << "    in float d)"
            << endl << "{"
            << endl << "    return 1.0 / (q*d*d + l*d + c);"
            << endl << "}"
            << endl << ""
            << endl << "//"
            << endl << "// Calculate the attenuation with respect to the spot light cone."
            << endl << "// Parameters:"
            << endl << "//      coneCos  :  cosine of the spot cutoff angle"
            << endl << "//      exponent :  the spot exponent"
            << endl << "//      l        :  normalized direction between fragment and light position"
            << endl << "//      s        :  normalized light direction"
            << endl << "//"
            << endl << "float spotAttenuation("
            << endl << "    in float coneCos,"
            << endl << "    in float exponent,"
            << endl << "    in vec3  l,"
            << endl << "    in vec3  s)"
            << endl << "{"
            << endl << "    float attenuation = 0.0;"
            << endl << "    float l_dot_s = dot(-l, s);"
            << endl << "    if (l_dot_s >= coneCos)"
            << endl << "        attenuation = pow(l_dot_s, exponent);"
            << endl << "    return attenuation;"
            << endl << "}"
            ;
        }

        // Provide default light implementation
        ost
        << endl << ""
        << endl << "bool activeLights[8];"
        << endl << ""
        << endl << "void InitializeActiveLights()"
        << endl << "{"
        << endl << "    activeLights[0] = OSGLight0Active;"
        << endl << "    activeLights[1] = OSGLight1Active;"
        << endl << "    activeLights[2] = OSGLight2Active;"
        << endl << "    activeLights[3] = OSGLight3Active;"
        << endl << "    activeLights[4] = OSGLight4Active;"
        << endl << "    activeLights[5] = OSGLight5Active;"
        << endl << "    activeLights[6] = OSGLight6Active;"
        << endl << "    activeLights[7] = OSGLight7Active;"
        << endl << "}"
        << endl << ""
        << endl << "vec3 globalAmbientIntensity()"
        << endl << "{"
        ;
        if (envDesc && envDesc->getHasFeatureClassicLightExtension())
        {
            ost
        << endl << "    return environment.ambientIntensity;"
            ;
        }
        else
        {
            ost
        << endl << "    return gl_LightModel.ambient.rgb;"
            ;
        }
        ost
        << endl << "}"
        << endl << ""
        ;

        if (pChunk)
        {
            ost
            << endl << "Light getLight(in int idx)"
            << endl << "{"
            << endl << "    Light light;"
            << endl << "    light.enabled = false;"
            << endl << ""
            << endl << "    if (idx < 8 && activeLights[idx] == true)"
            << endl << "    {"
            << endl << "        if (gl_LightSource[idx].position.w == 0.0)"
            << endl << "        {"
            << endl << "            light.type = DIRECTIONAL_LIGHT;"
            << endl << "            light.direction = -normalize(gl_LightSource[idx].position.xyz);"
            << endl << "        }"
            << endl << "        else"
            << endl << "        {"
            << endl << "            light.position = gl_LightSource[idx].position.xyz;"
            << endl << ""
            << endl << "            if (gl_LightSource[idx].spotCutoff == 180.0)"
            << endl << "            {"
            << endl << "                light.type = POINT_LIGHT;"
            << endl << "            }"
            << endl << "            else"
            << endl << "            {"
            << endl << "                light.type                      = SPOT_LIGHT;"
            << endl << "                light.direction                 = gl_LightSource[idx].spotDirection;"
            << endl << "                light.cosSpotlightAngle         = gl_LightSource[idx].spotCosCutoff;"
            << endl << "                light.cosSpotlightPenumbraAngle = gl_LightSource[idx].spotExponent;     // by design !"
            << endl << "            }"
            << endl << ""
            << endl << "            light.decayAttenuation     = gl_LightSource[idx].constantAttenuation;"
            << endl << "            light.lengthFactor         = gl_LightSource[idx].linearAttenuation;"
            << endl << "            light.rangeCutOn           = 0.0;"
            << endl << "            light.rangeCutOff          = gl_LightSource[idx].quadraticAttenuation;"
            << endl << "        }"
            << endl << ""
            << endl << "        light.intensity = gl_LightSource[idx].diffuse.rgb;"
            << endl << ""
            << endl << "        light.enabled = true;"
            << endl << "    }"
            << endl << ""
            << endl << "    return light;"
            << endl << "}"
            << endl << ""
            ;
        }
        else
        {
            ost
            << endl << "Light getLight(in int idx)"
            << endl << "{"
            << endl << "    Light light;"
            << endl << "    light.enabled = false;"
            << endl << ""
            << endl << "    if (idx < 8 && activeLights[idx] == true)"
            << endl << "    {"
            << endl << "        if (gl_LightSource[idx].position.w == 0.0)"
            << endl << "        {"
            << endl << "            light.type = DIRECTIONAL_LIGHT;"
            << endl << "            light.direction = -normalize(gl_LightSource[idx].position.xyz);"
            << endl << "        }"
            << endl << "        else"
            << endl << "        {"
            << endl << "            light.position = gl_LightSource[idx].position.xyz;"
            << endl << ""
            << endl << "            if (gl_LightSource[idx].spotCutoff == 180.0)"
            << endl << "            {"
            << endl << "                light.type = POINT_LIGHT;"
            << endl << "            }"
            << endl << "            else"
            << endl << "            {"
            << endl << "                light.type               = SPOT_LIGHT;"
            << endl << "                light.direction          = gl_LightSource[idx].spotDirection;"
            << endl << "                light.cosSpotlightAngle  = gl_LightSource[idx].spotCosCutoff;"
            << endl << "                light.spotlightExponent  = gl_LightSource[idx].spotExponent;"
            << endl << "            }"
            << endl << ""
            << endl << "            light.constantAttenuation    = gl_LightSource[idx].constantAttenuation;"
            << endl << "            light.linearAttenuation      = gl_LightSource[idx].linearAttenuation;"
            << endl << "            light.quadraticAttenuation   = gl_LightSource[idx].quadraticAttenuation;"
            << endl << "        }"
            << endl << ""
            << endl << "        light.intensity = gl_LightSource[idx].diffuse.rgb;"
            << endl << ""
            << endl << "        light.enabled = true;"
            << endl << "    }"
            << endl << ""
            << endl << "    return light;"
            << endl << "}"
            << endl << ""
            ;
        }
        ost
        << endl << "struct OutgoingLight"
        << endl << "{"
        << endl << "    vec3 directDiffuse;"
        << endl << "    vec3 directSpecular;"
        << endl << "    vec3 indirectDiffuse;"
        << endl << "    vec3 indirectSpecular;"
        << endl << "    vec3 emissiveRadiance;"
        << endl << "};"
        << endl << ""
        << endl << "OutgoingLight outLight;"
        << endl << ""
        ;
    }
}

void DescMaterialShaderCodeGenerator::getShadowProgram(
    std::stringstream& ost) const
{
    using namespace std;

    MultiLightShadowStage* pStage = isValidMultiLightShadowStage() ? getMultiLightShadowStage() : NULL;
    
    if (pStage)
    {
        ost
        << endl << ""
        << pStage->getFragmentProgramSnippet()
        ;
    }
}

void DescMaterialShaderCodeGenerator::getClusterProgram(
    std::stringstream& ost) const
{
    using namespace std;

    ClusterShadingStage* pStage = isValidClusterShadingStage() ? getClusterShadingStage() : NULL;

    if (pStage)
    {
        ost
        << endl << ""
        << pStage->getFragmentProgramSnippet(true, true)
        ;
    }
}

void DescMaterialShaderCodeGenerator::getSSAOProgram(
    std::stringstream& ost,
    bool hasAO) const
{
    using namespace std;

    SSAOStage* pStage = isValidSSAOStage() ? getSSAOStage() : NULL;

    if (!hasAO)
    {
        if (pStage)
        {
            ost
            << endl << ""
            << endl << "layout(binding = " << pStage->getAmbientOcclusionTexUnit()   << ") uniform sampler2DRect uAmbientOcclusionMap;"
            << endl << ""
            << endl << "float getStageAmbientOcclusion()"
            << endl << "{"
            << endl << "    vec2 uv = gl_FragCoord.xy;"
            << endl << "    return texture2DRect(uAmbientOcclusionMap, uv).r;"
            << endl << "}"
            ;
        }
    }
}

void DescMaterialShaderCodeGenerator::getToneMapProgram(
    std::stringstream& ost, 
    DescMaterial*      descMat) const
{
    using namespace std;

    if (!isValidHDR2Stage())
    {
        const EnvironmentDesc* envDesc = descMat->getEnvironmentDesc();

        if (envDesc && envDesc->getHasFeatureTonemapping())
        {
            ost 
            << endl << "float CalcLuminance(in vec3 color)"
            << endl << "{"
            ;
            if (envDesc->getUse_ITU_R_BT_709())
                ost << endl << "    return max(dot(color, vec3(0.2126, 0.7152, 0.0722)), 0.0001);" ;
            else
                ost << endl << "    return max(dot(color, vec3(0.299, 0.587, 0.114)), 0.0001);" ;
            ost
            << endl << "}"
            << endl << ""
            << endl << "vec3 ColorCorrection(in vec3 color, in float pixelLuminance)"
            << endl << "{"
            ;
            if (envDesc->getUseLinChromCorrection())
                ost << endl << "    return ((color / pixelLuminance - 1.0) * environment.saturation + 1.0 );" ;
            else
                ost << endl << "    return OSGPow(color / pixelLuminance, environment.saturation);" ;
            ost
            << endl << "}"
            << endl << ""
            << endl << "vec3 ContrastCorrection(in vec3 color)"
            << endl << "{"
            << endl << "    const vec3 logMidpoint = log2(vec3(0.18,0.18,0.18));"
            << endl << ""
            << endl << "    vec3 logColor = log2(color + vec3(0.00001));"
            << endl << "    vec3 adjColor = logMidpoint + (logColor - logMidpoint) * environment.contrast;"
            << endl << ""
            << endl << "    return max(vec3(0.0), exp2(adjColor) - vec3(0.00001));"
            << endl << "}"
            << endl << ""
            << endl << "vec3 SaturationCorrection(in vec3 color, in float pixelLuminance)"
            << endl << "{"
            << endl << "    float a = 1.0 - environment.saturation;"
            << endl << "    return mix(color, vec3(pixelLuminance), a);"
            << endl << "}"
            << endl << ""
            ;
            switch(envDesc->getToneMappingMode())
            {
                case EnvironmentDesc::NO_TONE_MAPPING:
                    break; // Do nothing
                case EnvironmentDesc::LOGARITHMIC_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapLogarithmic(in vec3 color)"
                    << endl << "{"
                    << endl << "    float pixelLuminance      = CalcLuminance(color);"
                    << endl << "    float toneMappedLuminance = OSGLog10(1.0 + pixelLuminance) / OSGLog10(1.0 + environment.whiteLevel);"
                    << endl << ""
                    << endl << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::EXPONENTIAL_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapExponential(in vec3 color)"
                    << endl << "{"
                    << endl << "    float pixelLuminance      = CalcLuminance(color);"
                    << endl << "    float toneMappedLuminance = 1.0 - exp(-pixelLuminance / environment.whiteLevel;"
                    << endl << ""
                    << endl << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::DRAGO_LOGARITHMIC_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapDragoLogarithmic(in vec3 color)"
                    << endl << "{"
                    << endl << "    float pixelLuminance      = CalcLuminance(color);"
                    << endl << "    float toneMappedLuminance = OSGLog10(1.0 + pixelLuminance);"
                    << endl << ""
                    << endl << "    toneMappedLuminance /= OSGLog10(1.0 + environment.whiteLevel);"
                    << endl << "    toneMappedLuminance /= OSGLog10(2.0 + 8.0 * (pow((pixelLuminance / environment.whiteLevel), OSGLog10(environment.dragoBias) / OSGLog10(0.5))));"
                    << endl << ""
                    << endl << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::REINHARD_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapReinhard(in vec3 color)"
                    << endl << "{"
                    << endl << "    float pixelLuminance      = CalcLuminance(color);"
                    << endl << "    float toneMappedLuminance = pixelLuminance / (pixelLuminance + 1.0);"
                    << endl << ""
                    << endl << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::REINHARD_MODIFIED_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapReinhardModified(in vec3 color)"
                    << endl << "{"
                    << endl << "    float pixelLuminance      = CalcLuminance(color);"
                    << endl << "    float toneMappedLuminance = pixelLuminance * (1.0 + pixelLuminance / (environment.whiteLevel * environment.whiteLevel)) / (1.0 + pixelLuminance);"
                    << endl << ""
                    << endl << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::FILMIC_HABLE_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapFilmicALU(in vec3 color)"
                    << endl << "{"
                    << endl << "    color = max(vec3(0), color - 0.004);"
                    << endl << "    color = (color * (6.2 * color + 0.5)) / (color * (6.2 * color + 1.7)+ 0.06);"
                    << endl << ""
                    << endl << "    color = OSGSRGBToLinear(color); // result color is sRGB, i.e. has 1/2.2 baked in"
                    << endl << ""
                    << endl << "    float pixelLuminance = CalcLuminance(color);"
                    << endl << "    color = SaturationCorrection(color, pixelLuminance);"
                    << endl << ""
                    << endl << "    return color;"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::FILMIC_UNCHARTED2_TONE_MAPPING:
                    break; // Do nothing, not supported
                case EnvironmentDesc::FILMIC_ACES_TONE_MAPPING:
                    ost
                    << endl << "const mat3 matACESIn = mat3("
                    << endl << "    0.59719, 0.07600, 0.02840,"
                    << endl << "    0.35458, 0.90834, 0.13383,"
                    << endl << "    0.04823, 0.01566, 0.83777);"
                    << endl << ""
                    << endl << "const mat3 matACESOut = mat3("
                    << endl << "     1.60475, -0.10208, -0.00327,"
                    << endl << "    -0.53108,  1.10813, -0.07276,"
                    << endl << "    -0.07367, -0.00605,  1.07602);"
                    << endl << ""
                    << endl << "vec3 ToneMapFilmicACES(in vec3 color)"
                    << endl << "{"
                    << endl << "    color = 1.8 * matACESIn * color;"
                    << endl << ""
                    << endl << "    vec3 a = color * (color + 0.0245786) - 0.000090537;"
                    << endl << "    vec3 b = color * (0.983729 * color + 0.4329510) + 0.238081;"
                    << endl << "    color = a / b;"
                    << endl << ""
                    << endl << "    color = matACESOut * color;"
                    << endl << ""
                    << endl << "    float pixelLuminance = CalcLuminance(color);"
                    << endl << "    color = SaturationCorrection(color, pixelLuminance);"
                    << endl << ""
                    << endl << "    return color;"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::FILMIC_HEJ2015_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapFilmicHejl2015(in vec3 color)"
                    << endl << "{"
                    << endl << "    vec4 vh = vec4(color, environment.whiteLevel);"
                    << endl << "    vec4 va = (1.435 * vh) + 0.05;"
                    << endl << "    vec4 vf = ((vh * va + 0.004) / ((vh * (va + 0.55) + 0.0491))) - 0.0821;"
                    << endl << ""
                    << endl << "    color = vf.xyz / vf.www;"
                    << endl << ""
                    << endl << "    float pixelLuminance = CalcLuminance(color);"
                    << endl << "    color = SaturationCorrection(color, pixelLuminance);"
                    << endl << ""
                    << endl << "    return color;"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
                case EnvironmentDesc::FILMIC_ACES_2_TONE_MAPPING:
                    ost
                    << endl << "vec3 ToneMapFilmicACES2(in vec3 color)"
                    << endl << "{"
                    << endl << "    vec3 a = color * ( 2.51 * color + 0.03 );"
                    << endl << "    vec3 b = color * ( 2.43 * color + 0.59 ) + 0.14;"
                    << endl << "    color = a / b;"
                    << endl << ""
                    << endl << "    float pixelLuminance = CalcLuminance(color);"
                    << endl << "    color = SaturationCorrection(color, pixelLuminance);"
                    << endl << ""
                    << endl << "    return color;"
                    << endl << "}"
                    << endl << ""
                    ;
                    break;
            }

            ost
            << endl << ""
            << endl << "float Log2Exposure(in float avgLuminance)"
            << endl << "{"
            << endl << "    float exposure = 0.0f;"
            << endl << ""
            ;
            switch (envDesc->getAutoExposureMode())
            {
                case EnvironmentDesc::MANUAL:
                    ost
                    << endl << "    exposure = -environment.exposure - 0.263034406;"
                    ;
                    break;
                case EnvironmentDesc::KEY_VALUE:
                    ost
                    << endl << "    avgLuminance = max(avgLuminance, 0.00001);"
                    << endl << ""
                    << endl << "    float linearExposure = (environment.keyValue / avgLuminance);"
                    << endl << "    exposure = log2(max(linearExposure, 0.0001));"
                    ;
                    break;
                case EnvironmentDesc::AUTOMATIC:
                    ost
                    << endl << "    avgLuminance = max(avgLuminance, 0.00001);"
                    << endl << ""
                    << endl << "    float keyValue = 1.03 - (2.0 / (2.0 + OSGLog10(avgLuminance + 1.0)));"
                    << endl << ""
                    << endl << "    float linearExposure = (keyValue / avgLuminance);"
                    << endl << "    exposure = log2(max(linearExposure, 0.0001));"
                    ;
                    break;
                case EnvironmentDesc::SATURATION_BASED:
                    ost
                    << endl << "    float maxLuminance = (7800.0 / 65.0)"
                    << endl << "                 * (environment.apertureFNumber * environment.apertureFNumber)"
                    << endl << "                 / (environment.iso * environment.shutterSpeed);"
                    << endl << ""
                    << endl << "    exposure = log2(1.0 / maxLuminance);"
                    ;
                    break;
                case EnvironmentDesc::STANDARD_OUTPUT_BASED:
                    ost
                    << endl << "    float middleGrey = 0.18;"
                    << endl << "    "
                    << endl << "    float lAvg = (1000.0 / 65.0)"
                    << endl << "                 * (environment.apertureFNumber * environment.apertureFNumber)"
                    << endl << "                 / (environment.iso * environment.shutterSpeed);"
                    << endl << ""
                    << endl << "    exposure = log2(middleGrey / lAvg);"
                    ;
                    break;
            }
            ost
            << endl << ""
            << endl << "    return exposure;"
            << endl << "}"
            << endl << ""
            << endl << "vec3 CalcExposedColor(in vec3 color, in float avgLuminance, in float threshold)"
            << endl << "{"
            << endl << "    float exposure = Log2Exposure(avgLuminance);"
            << endl << ""
            << endl << "    exposure -= threshold;"
            << endl << "    return max(exp2(exposure) * color, 0.0);"
            << endl << "}"
            << endl << ""
            << endl << "vec3 ToneMap(in vec3 color, in float avgLuminance, in float threshold)"
            << endl << "{"
            << endl << "    color = CalcExposedColor(color, avgLuminance, threshold);"
            << endl << ""
            ;

            switch(envDesc->getToneMappingMode())
            {
                case EnvironmentDesc::NO_TONE_MAPPING:                                                                                 break; // Do nothing
                case EnvironmentDesc::LOGARITHMIC_TONE_MAPPING:         ost << endl << "    color = ToneMapLogarithmic(color);"      ; break;
                case EnvironmentDesc::EXPONENTIAL_TONE_MAPPING:         ost << endl << "    color = ToneMapExponential(color);"      ; break;
                case EnvironmentDesc::DRAGO_LOGARITHMIC_TONE_MAPPING:   ost << endl << "    color = ToneMapDragoLogarithmic(color);" ; break;
                case EnvironmentDesc::REINHARD_TONE_MAPPING:            ost << endl << "    color = ToneMapReinhard(color);"         ; break;
                case EnvironmentDesc::REINHARD_MODIFIED_TONE_MAPPING:   ost << endl << "    color = ToneMapReinhardModified(color);" ; break;
                case EnvironmentDesc::FILMIC_HABLE_TONE_MAPPING:        ost << endl << "    color = ToneMapFilmicALU(color);"        ; break;
                case EnvironmentDesc::FILMIC_UNCHARTED2_TONE_MAPPING:                                                                  break; // Do nothing, not supported
                case EnvironmentDesc::FILMIC_ACES_TONE_MAPPING:         ost << endl << "    color = ToneMapFilmicACES(color);"       ; break;
                case EnvironmentDesc::FILMIC_HEJ2015_TONE_MAPPING:      ost << endl << "    color = ToneMapFilmicHejl2015(color);"   ; break;
                case EnvironmentDesc::FILMIC_ACES_2_TONE_MAPPING:       ost << endl << "    color = ToneMapFilmicACES2(color);"      ; break;
            }

            ost
            << endl << ""
            << endl << "    color *= environment.filterColor;"
            << endl << "    color = ContrastCorrection(color);"
            << endl << ""
            << endl << "    return color;"
            << endl << "}"
            ;
        }
        else
        {
            ost
                << endl << "vec3 ToneMap(in vec3 color, in float avgLuminance, in float threshold)"
                << endl << "{"
                << endl << "    color = color / (color + vec3(1.0));"
                << endl << "    return color;"
                << endl << "}"
            ;
        }
    }
}

void DescMaterialShaderCodeGenerator::getGammaCorrectionProgram(
    std::stringstream& ost, 
    DescMaterial*      descMat) const
{
    using namespace std;

    if (!isValidHDR2Stage())
    {
        const EnvironmentDesc* envDesc = descMat->getEnvironmentDesc();

        if (envDesc && envDesc->getHasFeatureGammaCorrection())
        {
            if (envDesc->getApplyGamma())
            {
                if (envDesc->getAccurateGamma())
                {
                    ost
                    << endl << "    color = OSGLinearToSRGB(color);"
                    << endl << ""
                    ;
                }
                else
                {
                    ost
                    << endl << "    color = OSGPow(color, 1.0 / environment.gamma);"
                    << endl << ""
                    ;
                }
            }
        }
        else
        {
            ost
                << endl << "    color = OSGLinearToSRGB(color);"
                << endl << ""
            ;
        }
    }
}

void DescMaterialShaderCodeGenerator::getMainFuncProgram(
    std::stringstream& ost,
    DescMaterial*      descMaterial) const
{
    using namespace std;

    

    MultiLightChunk*       pMLChunk             = findMultiLightChunk();
    MultiLightShadowStage* pMLShadowStage       = isValidMultiLightShadowStage() ? getMultiLightShadowStage() : NULL;
    ClusterShadingStage*   pClusterShadingStage = isValidClusterShadingStage  () ? getClusterShadingStage()   : NULL;
    SSAOStage*             pSSAOStage           = isValidSSAOStage            () ? getSSAOStage()             : NULL;

    bool isActiveMultiLight = pMLChunk && isValidMultiLight();

    MaterialDesc* matDesc = descMaterial->getMaterialDesc();

    ost
            << endl << "void main()"
            << endl << "{"
            << endl << "    InitializeGeometryContext();"
            << endl << "    InitializeMaterial();"
            << endl << "    InitializeLight();"
            << endl << ""
    ;

    if (pMLShadowStage && matDesc->getShadowOnlyMode())
    {
        ost
        << endl << "bool invisible_flag = true;"
        << endl << ""
        ;
    }

    if (pClusterShadingStage)
    {
        ost
            << endl << "    int list_idx    = 0;"
            << endl << "    int light_count = " << pMLChunk->getLightVariableName() << ".light.length();"
            << endl << ""
            << endl << "    if (clusteringData.enabled)"
            << endl << "    {"
            << endl << "        uvec2 grid_data = getGridData(gl_FragCoord.xy, vPositionES.z);"
            << endl << ""
            << endl << "        list_idx    = grid_data.x;"
            << endl << "        light_count = grid_data.y;"
            << endl << "    }"
            << endl << "    else"
            << endl << "    {"
            << endl << "        light_count = affectedLightIndexList.idx.length();"
            << endl << "    }"
            << endl << ""
            << endl << "    for (int i = 0; i < light_count; ++i)"
            << endl << "    {"
            << endl << "        int light_idx = (clusteringData.enabled) ? lightIndexList.idx[list_idx+i] : affectedLightIndexList.idx[i];"
            << endl << ""
            << endl << "        light = getLight(light_idx);"
        ;
    }
    else
    if (isActiveMultiLight)
    {
        ost
            << endl << "    int light_count = " << pMLChunk->getLightVariableName() << ".light.length();"
            << endl << ""
            << endl << "    for (int i = 0; i < light_count; ++i)"
            << endl << "    {"
            << endl << "        Light light = getLight(i);"
            << endl << ""
        ;
    }
    else
    if (!isActiveMultiLight)
    {
        ost
            << endl << "    for (int i = 0; i < 8; ++i)"
            << endl << "    {"
            << endl << "        Light light = getLight(i);"
            << endl << ""
        ;
    }

    ost
            << endl << "        if (light.enabled)"
            << endl << "        {"
            << endl << "            vec3  L;"
            << endl << "            float attDist    = 1.0;"
            << endl << "            float attSpot    = 1.0;"
            << endl << "            float attShadow  = 1.0;"
            << endl << ""
            << endl << "            if (light.type == DIRECTIONAL_LIGHT)"
            << endl << "            {"
    ;

    if (!isActiveMultiLight)
    {
        ost
            << endl << "                L = -light.direction.xyz;"
        ;
    }
    else
    {
        ost
            << endl << "                vec4 direction = OSGViewMatrix * vec4(light.direction, 0.0);"
            << endl << "                L = -direction.xyz;"
        ;
    }

    ost
            << endl << "            }"
            << endl << "            else"
            << endl << "            {"
    ;

    if (!isActiveMultiLight)
    {
        ost
            << endl << "                L = light.position.xyz - vPositionES;"
        ;
    }
    else
    {
        ost
            << endl << "                vec4 position = OSGViewMatrix * vec4(light.position, 1.0);"
            << endl << "                L = position.xyz - vPositionES;"
        ;
    }

    ost
            << endl << "                float d = length(L);"
            << endl << ""
    ;

    if (isActiveMultiLight && pMLChunk->getHasRangeCutOff() && pMLChunk->getHasRangeCutOn())
    {
        ost
            << endl << "                if (light.rangeCutOn > d || d > light.rangeCutOff)"
            << endl << "                    continue;"
            << endl << ""
        ;
    }
    else
    if (isActiveMultiLight && pMLChunk->getHasRangeCutOff() && !pMLChunk->getHasRangeCutOn())
    {
        ost
            << endl << "                if (d > light.rangeCutOff)"
            << endl << "                    continue;"
            << endl << ""
        ;
    }
    else
    if (isActiveMultiLight && !pMLChunk->getHasRangeCutOff() && pMLChunk->getHasRangeCutOn())
    {
        ost
            << endl << "                if (light.rangeCutOn > d)"
            << endl << "                    continue;"
            << endl << ""
        ;
    }

    if (isActiveMultiLight || pMLChunk)
    {
        ost
            << endl << "                //"
            << endl << "                // calculate the intensity to irradiance factor for punctual lights."
            << endl << "                //"
        ;

        if (pMLChunk->getCodeDistanceAttenuationClassic() && pMLChunk->getHasAttenuation())
        {
            ost
            << endl << "                attDist = calcAttenuation(light. constantAttenuation,"
            << endl << "                                          light.   linearAttenuation,"
            << endl << "                                          light.quadraticAttenuation,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getCodeDistanceAttenuationPhysical() && pMLChunk->getHasRangeCutOff())
        {
            ost
            << endl << "                attDist = calcAttenuation(" << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getCodeDistanceAttenuationDecay() && pMLChunk->getHasRangeCutOff() && pMLChunk->getHasDecayAttenuation())
        {
            ost
            << endl << "                attDist = calcAttenuation(light.decayAttenuation,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getCodeDistanceAttenuationMixPhysical() && pMLChunk->getHasRangeCutOff() && pMLChunk->getHasAttenuation())
        {
            ost
            << endl << "                attDist = calcAttenuation(light. constantAttenuation,"
            << endl << "                                          light.   linearAttenuation,"
            << endl << "                                          light.quadraticAttenuation,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getCodeDistanceAttenuationMixDecay() && pMLChunk->getHasRangeCutOff() && pMLChunk->getHasAttenuation() && pMLChunk->getHasDecayAttenuation())
        {
            ost
            << endl << "                attDist = calcAttenuation(light. constantAttenuation,"
            << endl << "                                          light.   linearAttenuation,"
            << endl << "                                          light.quadraticAttenuation,"
            << endl << "                                          light.decayAttenuation,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getCodeDistanceAttenuationSmoothHermite() && pMLChunk->getHasRangeCutOff())
        {
            ost
            << endl << "                attDist = calcAttenuation(" << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getHasAttenuation())
        {
            ost
            << endl << "                attDist = calcAttenuation(light. constantAttenuation,"
            << endl << "                                          light.   linearAttenuation,"
            << endl << "                                          light.quadraticAttenuation,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
        else if (pMLChunk->getHasRangeCutOff())
        {
            ost
            << endl << "                attDist = calcAttenuation(" << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "light.rangeCutOff,"
            << endl << "                                          " << (pMLChunk->getHasLengthFactor() ? "light.lengthFactor * " : "") << "d);"
            ;
        }
    }
    else
    {
        ost
            << endl << "                attDist = calcAttenuation(light. constantAttenuation,"
            << endl << "                                          light.   linearAttenuation,"
            << endl << "                                          light.quadraticAttenuation,"
            << endl << "                                          d);"
        ;
    }

    //
    // fallback for missing switch statement
    //
    if (isFallbackShader2() && !hasSwitchSupport())
    {
        ost
            << endl << "            }"
            << endl << ""
            << endl << "            geomContext.L = normalize(L);"
            << endl << ""
        ;

        if (pMLShadowStage)
        {
            ost
            << endl << "            if (light.type == DIRECTIONAL_LIGHT)"
            << endl << "            {"
            << endl << "                attShadow *= shadowAttenuationDirectionalLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            << endl << "            }"
            << endl << ""
            << endl << "            if (light.type == POINT_LIGHT)"
            << endl << "            {"
            << endl << "                attShadow *= shadowAttenuationPointLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            << endl << "            }"
            << endl << ""
            ;
        }

        ost
            << endl << "            if (light.type == SPOT_LIGHT)"
            << endl << "            {"
        ;

        if (!isActiveMultiLight)
        {
            ost
            << endl << "                vec3 S = light.direction;"
            ;
        }
        else
        {
            ost
            << endl << "                vec4 direction = OSGViewMatrix * vec4(light.direction, 0.0);"
            << endl << "                vec3 S = direction.xyz;"
            ;
        }

        ost
            << endl << "                        S = normalize(S);"
            << endl << ""
        ;

        if (pMLChunk && pMLChunk->getHasSpotlightExponent())
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.spotlightExponent, geomContext.L, S);"
            ;

        }
        else
        if (pMLChunk && pMLChunk->getHasSpotlightPenumbraFrostbite())
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.spotlightScale, light.spotlightOffset, geomContext.L, S);"
            ; 
        }
        else
        if (pMLChunk && (pMLChunk->getHasSpotlightPenumbraAngle() || pMLChunk->getHasSpotlightPenumbraFactor()))
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.cosSpotlightPenumbraAngle, geomContext.L, S);"
            ; 
        }
        else
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.spotlightExponent, geomContext.L, S);"
            ;
        }

        if (pMLShadowStage)
        {
            ost
            << endl << "                attShadow *= shadowAttenuationSpotLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            ;
        }

        ost
            << endl << "            }"
            << endl << ""
        ;
    
        if (isActiveMultiLight && pMLChunk->getHasCinemaLight())
        {
            ost
            << endl << "            if (light.type == CINEMA_LIGHT)"
            << endl << "            {"
            << endl << "                vec3 p_LS = (light.matLSFromES * vec4(vPositionES, 1.0)).xyz;"
            << endl << ""
            << endl << "                attSpot   *= clipSuperEllipses("
            << endl << "                                light.innerSuperEllipsesWidth,"
            << endl << "                                light.innerSuperEllipsesHeight,"
            << endl << "                                light.outerSuperEllipsesWidth,"
            << endl << "                                light.outerSuperEllipsesHeight,"
            << endl << "                                light.superEllipsesRoundness,"
            << endl << "                                light.superEllipsesTwist,"
            << endl << "                                p_LS);"
            << endl << ""
            ;

            if (pMLShadowStage)
            {
                ost
            << endl << "                attShadow *= shadowAttenuationCinemaLight(vPositionES.z, vPositionWS, vNormalWS, light);"
                ;
            }

            ost
            << endl << "            }"
            << endl << ""
            ;
        }
    }
    //
    // regular second
    //
    else
    {
        ost
            << endl << "            }"
            << endl << ""
            << endl << "            geomContext.L = normalize(L);"
            << endl << ""
            << endl << "            switch(light.type)"
            << endl << "            {"
        ;

        if (pMLShadowStage)
        {
            ost
            << endl << "                case DIRECTIONAL_LIGHT:"
            << endl << "                    {"
            << endl << "                        attShadow *= shadowAttenuationDirectionalLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            << endl << "                    }"
            << endl << "                    break;"
            << endl << "                case POINT_LIGHT:"
            << endl << "                    {"
            << endl << "                        attShadow *= shadowAttenuationPointLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            << endl << "                    }"
            << endl << "                    break;"
            ;
        }

        ost
            << endl << "                case SPOT_LIGHT:"
            << endl << "                    {"
        ;

        if (!isActiveMultiLight)
        {
            ost
            << endl << "                        vec3 S = light.direction;"
            ;
        }
        else
        {
            ost
            << endl << "                        vec4 direction = OSGViewMatrix * vec4(light.direction, 0.0);"
            << endl << "                        vec3 S = direction.xyz;"
            ;
        }

        ost
            << endl << "                        S = normalize(S);"
            << endl << ""
        ;

        if (pMLChunk && pMLChunk->getHasSpotlightExponent())
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.spotlightExponent, geomContext.L, S);"
            ;
        }
        else
        if (pMLChunk && pMLChunk->getHasSpotlightPenumbraFrostbite())
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.spotlightScale, light.spotlightOffset, geomContext.L, S);"
            ; 
        }
        else
        if (pMLChunk && (pMLChunk->getHasSpotlightPenumbraAngle() || pMLChunk->getHasSpotlightPenumbraFactor()))
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.cosSpotlightPenumbraAngle, geomContext.L, S);"
            ; 
        }
        else
        {
            ost
            << endl << "                        attSpot   *= spotAttenuation(light.cosSpotlightAngle, light.spotlightExponent, geomContext.L, S);"
            ;
        }

        if (pMLShadowStage)
        {
            ost
            << endl << "                        attShadow *= shadowAttenuationSpotLight(vPositionES.z, vPositionWS, vNormalWS, light);"
            ;
        }

        ost
            << endl << "                    }"
            << endl << "                    break;"
        ;
    
        if (isActiveMultiLight && pMLChunk->getHasCinemaLight())
        {
            ost
            << endl << "                case CINEMA_LIGHT:"
            << endl << "                    {"
            << endl << "                        vec3 p_LS = (light.matLSFromES * vec4(vPositionES, 1.0)).xyz;"
            << endl << ""
            << endl << "                        attSpot   *= clipSuperEllipses("
            << endl << "                                        light.innerSuperEllipsesWidth,"
            << endl << "                                        light.innerSuperEllipsesHeight,"
            << endl << "                                        light.outerSuperEllipsesWidth,"
            << endl << "                                        light.outerSuperEllipsesHeight,"
            << endl << "                                        light.superEllipsesRoundness,"
            << endl << "                                        light.superEllipsesTwist,"
            << endl << "                                        p_LS);"
            << endl << ""
            ;

            if (pMLShadowStage)
            {
                ost
            << endl << "                        attShadow *= shadowAttenuationCinemaLight(vPositionES.z, vPositionWS, vNormalWS, light);"
                ;
            }

            ost
            << endl << "                    }"
            << endl << "                    break;"
            ;
        }

        ost
            << endl << "            }"
        ;
    }

    //
    // end of the switch statement stuff
    //

    ost
            << endl << ""
            << endl << "            vec3 I = attDist * attSpot * attShadow * light.intensity;"
            << endl << ""
            << endl << "            DirectShading(I);"
    ;

    if (pMLShadowStage && matDesc->getShadowOnlyMode())
    {
    ost
            << endl << ""
            << endl << "            if (abs(attShadow) < 1.0 && abs(attDist * attSpot) >= OSG_EPS)"
            << endl << "            {"
            << endl << "                invisible_flag = false;"
            << endl << "            }"
    ;
    }

    ost
            << endl << "        }"
            << endl << "    }"
            << endl << ""

            << endl << "    vec3 color = outLight.directDiffuse  + outLight.indirectDiffuse"
            << endl << "               + outLight.directSpecular + outLight.indirectSpecular"
            << endl << "               + outLight.emissiveRadiance;"
            << endl << ""
    ;

    ost
            << endl << "    color += globalAmbientIntensity() * material.diffuse;"
    ;

    if (descMaterial->getHasImageBasedLight())
    {
        ost
            << endl << "    color += ImageBasedLight(material.normal, V);"
        ;
    }

    if (descMaterial->getHasAmbientOcclusion())
    {
        ost
            << endl << "    color *= getMaterialAmbientOcclusion();"
        ;
    }

    if (pSSAOStage)
    {
        ost
            << endl << "    color *= getStageAmbientOcclusion();"
        ;
    }

    if (descMaterial->getHasPostProcessColor())
    {
        ost
            << endl << "    color = PostProcessColor(color);"
        ;
    }

    if (!isValidHDR2Stage())
    {
        ost
        << endl << "    color = ToneMap(color, 0.5, 0.0);"
        ;
    }

    getGammaCorrectionProgram(ost, descMaterial);

    if (matDesc->getShadowOnlyMode())
    {
        if (pMLShadowStage)
        {
            ost
                << endl << "    if (invisible_flag)"
                << endl << "    {"
                << endl << "        material.opacity = 0.0;"
                << endl << "    }"
            ;
        }
        else
        {
            ost
                << endl << "    material.opacity = 0.0;"
            ;
        }
    }

    if (isFallbackShader2())
    {
        ost
                << endl << "    gl_FragColor = vec4(color, material.opacity);"
                << endl << "}"
                << endl << ""
        ;
    }
    else
    {
        ost
                << endl << "    vFragColor = vec4(color, material.opacity);"
                << endl << "}"
                << endl << ""
        ;
    }
}

OSG_END_NAMESPACE

