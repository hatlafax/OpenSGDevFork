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

#ifndef _OSGDESCMATERIALMANAGER_H_
#define _OSGDESCMATERIALMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDescMaterialManagerBase.h"
#include "OSGShaderProgramFunctorFieldTraits.h"

OSG_BEGIN_NAMESPACE

class HDR2Stage;
class ClusterShadingStage;
class MultiLightShadowStage;
class SSAOStage;
class MultiLightChunk;
class MultiLightGroup;
class ShaderCodeGenerator;
class EnvironmentDesc;

/*! \brief DescMaterialManager class. See \ref
           PageContribTechniquesDescMaterialManager for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING DescMaterialManager : public DescMaterialManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DescMaterialManagerBase Inherited;
    typedef DescMaterialManager     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    virtual ManagedMaterialT    addMaterial     (MaterialDesc* matDesc );
    virtual bool                addMaterial     (KeyParamType key, ChunkMaterial* mat);
    virtual ManagedMaterialT    updateMaterial  (KeyParamType key);
    virtual KeyTypeStore        updateMaterials (                );
    virtual bool                removeMaterial  (KeyParamType key);
    virtual ChunkMaterial*      getMaterial     (KeyParamType key) const;
    virtual const MaterialDesc* getMaterialDesc (KeyParamType key) const;
    virtual bool                hasMaterial     (KeyParamType key) const;
    virtual void                clear           ();
    virtual void                recycle         ();

    virtual void                updateProgram   ();

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static DescMaterialManagerTransitPtr    createDefault();
    static DescMaterialManagerTransitPtr    createDefault(
        ShaderProgramFunctor   initFunctor, const std::string&   initSymbol,
        ShaderProgramFunctor updateFunctor, const std::string& updateSymbol);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Utilities                                */
    /*! \{                                                                 */

    bool setCapabilities                (const UInt32 platform, const UInt32 requested) const;

    bool setEnvironmentDesc             (EnvironmentDesc*       envDesc) const;
    bool setHDR2Stage                   (HDR2Stage*             stage  ) const;
    bool setClusterShadingStage         (ClusterShadingStage*   stage  ) const;
    bool setMultiLightShadowStage       (MultiLightShadowStage* stage  ) const;
    bool setSSAOStage                   (SSAOStage*             stage  ) const;
    bool setMultiLightGroup             (MultiLightGroup*       group  ) const;
    bool setLightBindingPnt             (UInt32                 idx    ) const;
    bool setHasClipPlanes               (bool                   flag   ) const;

    ShaderCodeGenerator*        getShaderCodeGenerator() const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DescMaterialManager(void);
    DescMaterialManager(const DescMaterialManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DescMaterialManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    void onCreate      (const DescMaterialManager *source      = NULL);
    void onCreateAspect(const DescMaterialManager *createAspect,
                        const DescMaterialManager *source      = NULL);
    void onDestroy(           UInt32               uiId              );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DescMaterialManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DescMaterialManager &source);
};

typedef DescMaterialManager *DescMaterialManagerP;

OSG_END_NAMESPACE

#include "OSGDescMaterialManagerBase.inl"
#include "OSGDescMaterialManager.inl"

#endif /* _OSGDESCMATERIALMANAGER_H_ */
