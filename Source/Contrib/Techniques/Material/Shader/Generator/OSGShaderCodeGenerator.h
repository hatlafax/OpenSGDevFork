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

#ifndef _OSGSHADERCODEGENERATOR_H_
#define _OSGSHADERCODEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderCodeGeneratorBase.h"
#include "OSGShaderDescStore.h"
#include "OSGCapabilitiesDesc.h"

OSG_BEGIN_NAMESPACE

class ChunkMaterial;
class Window;
class MultiLightChunk;

/*! \brief ShaderCodeGenerator class. See \ref
           PageContribTechniquesShaderCodeGenerator for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ShaderCodeGenerator : public ShaderCodeGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef ShaderCodeGeneratorBase Inherited;
    typedef ShaderCodeGenerator     Self;

    typedef UInt64                  HashKeyType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    virtual ShaderDescStoreTransitPtr getShaderDescStore(ChunkMaterial* chunkMat) = 0;
    virtual HashKeyType               getEnvironmentHash(Window*        win);

    void    updateEnvironment               (Window* win);

    void    setPlatformCapabilities         (const UInt32 value);
    void    setRequestedCapabilities        (const UInt32 value);
    void    setRuntimeCapabilities          (const UInt32 value);

    UInt32  getPlatformCapabilities         () const;
    UInt32  getRequestedCapabilities        () const;
    UInt32  getRuntimeCapabilities          () const;

    bool    bUseCapabilities                (UInt32 capabilities) const;
    bool    bUsePlatformCapabilities        (UInt32 capabilities) const;
    bool    bUseRequestedCapabilities       (UInt32 capabilities) const;

    bool    isFallbackFixedFunction         () const;
    bool    isFallbackShader2               () const;
    bool    isFallbackShader3               () const;
    bool    isFallbackShader4               () const;

    bool    hasSwitchSupport                () const;
    bool    hasBitOpsSupport                () const;
    bool    hasGLSL130Support               () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderCodeGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderCodeGenerator(void);
    ShaderCodeGenerator(const ShaderCodeGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderCodeGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    void onCreate      (const ShaderCodeGenerator *source      = NULL);
    void onCreateAspect(const ShaderCodeGenerator *createAspect,
                        const ShaderCodeGenerator *source      = NULL);
    void onDestroy(           UInt32               uiId              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Check                                   */
    /*! \{                                                                 */

    void    initFixedFunctionPipeline       (Window* pWin);
    void    initShaderMaterial2             (Window* pWin);
    void    initShaderMaterial3             (Window* pWin);
    void    initShaderMaterial4             (Window* pWin);
    void    initHDR2Stage                   (Window* pWin);
    void    initSSAOStage                   (Window* pWin);
    void    initMultiLight                  (Window* pWin);
    void    initMultiLightShadowStage       (Window* pWin);
    void    initClusterShadingStage         (Window* pWin);
    void    initClipPlanes                  (Window* pWin);
    void    initBitOperations               (Window* pWin);
    void    initSwitchStatement             (Window* pWin);

    void    validateFixedFunctionPipeline   ();
    void    validateShaderMaterial2         ();
    void    validateShaderMaterial3         ();
    void    validateShaderMaterial4         ();
    void    validateHDR2Stage               ();
    void    validateSSAOStage               ();
    void    validateMultiLight              ();
    void    validateMultiLightShadowStage   ();
    void    validateClusterShadingStage     ();
    void    validateClipPlanes              ();
    void    validateBitOperations           ();
    void    validateSwitchStatement         ();

    bool    isValidHDR2Stage                () const;
    bool    isValidClusterShadingStage      () const;
    bool    isValidMultiLightShadowStage    () const;
    bool    isValidSSAOStage                () const;
    bool    isValidMultiLight               () const;
    bool    isValidModernShaderSupport      () const;
    bool    isValidFull440ShaderSupport     () const;
    bool    isValidClipPlanes               () const;
    bool    isValidBitOperations            () const;
    bool    isValidSwitchStatement          () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extensions                              */
    /*! \{                                                                 */

    typedef std::set<std::string> ExtensionStore;

    const ExtensionStore& getExtensions () const;
    UInt32                getGLSLVersion() const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Helper                                */
    /*! \{                                                                 */
    
    MultiLightChunk*    findMultiLightChunk() const;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:
    ExtensionStore      _extensions;
    UInt32              _glslVersion;

    static UInt32 _extVertexBufferObject;
    static UInt32 _extUniformBufferObject;    
    static UInt32 _extProgramInterfaceQuery;
    static UInt32 _extShaderStorageBufferObject;
    static UInt32 _extFramebufferObject;
    static UInt32 _extFramebufferBlit;
    static UInt32 _extPackedDepthStencil;
    static UInt32 _extShaderProgram;
    static UInt32 _extTextureCubeMapArray;
    static UInt32 _extTextureArray;
    static UInt32 _extGeometryShader4;
    static UInt32 _extComputeShader;
    static UInt32 _extShaderImageLoadStore;
    static UInt32 _extShadingLanguage420Pack;
    static UInt32 _extGPUShader4;

    friend class FieldContainer;
    friend class ShaderCodeGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderCodeGenerator &source);
};

typedef ShaderCodeGenerator *ShaderCodeGeneratorP;

OSG_END_NAMESPACE

#include "OSGShaderCodeGeneratorBase.inl"
#include "OSGShaderCodeGenerator.inl"

#endif /* _OSGSHADERCODEGENERATOR_H_ */
