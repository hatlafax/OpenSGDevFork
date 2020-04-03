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

#ifndef _OSGMULTILIGHTSHADOWSTAGEDATA_H_
#define _OSGMULTILIGHTSHADOWSTAGEDATA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiLight.h"
#include "OSGMultiLightShadowStageDataBase.h"
#include "OSGMultiLightShadowTechniqueBase.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTransform.h"
#include "OSGCamera.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiLightShadowStageData class. See \ref
           PageEffectGroupsMultiLightShadowStageData for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowStageData : public MultiLightShadowStageDataBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    struct LightAssoc
    {
        LightAssoc()
            : type              (MultiLight::POINT_LIGHT)
            , enabled           (false)
            , shadow            (false)
            , shadowParamIdx    (-1)
            , beacon            (NULL)
            , transform         (NULL)
            , camera            (NULL) {}

        LightAssoc(const LightAssoc& rhs)
            : type              (rhs.type)
            , enabled           (rhs.enabled)
            , shadow            (rhs.shadow)
            , shadowParamIdx    (rhs.shadowParamIdx)
            , beacon            (rhs.beacon)
            , transform         (rhs.transform)
            , camera            (rhs.camera) {}

        LightAssoc& operator=(const LightAssoc& rhs)
        {
            if (&rhs != this)
            {
                type            = rhs.type;
                enabled         = rhs.enabled;
                shadow          = rhs.shadow;
                shadowParamIdx  = rhs.shadowParamIdx;

                beacon          = rhs.beacon;
                transform       = rhs.transform;
                camera          = rhs.camera;
            }
            return *this;
        }

        MultiLight::Type  type;
        bool              enabled;
        bool              shadow;
        Int32             shadowParamIdx;

        NodeUnrecPtr      beacon;
        TransformUnrecPtr transform;
        CameraUnrecPtr    camera;
    };

  public:

    typedef MultiLightShadowStageDataBase       Inherited;
    typedef MultiLightShadowStageData           Self;

    typedef std::vector<NodeUnrecPtr>           NodeStore;
    typedef std::vector<UInt32>                 TravMaskStore;

    typedef std::vector<LightAssoc>             LightAssocStore;
    typedef std::vector<UInt32>                 LightIndexStore;

    typedef MultiLightShadowTechniqueBase       Technique;
    typedef MultiLightShadowTechniqueBaseRefPtr TechniqueRefPtr;
  
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
    /*! \name                     Access                                   */
    /*! \{                                                                 */
    void                setTechnique                (Technique* pTechnique);
    Technique*          getTechnique                ();
    
    NodeStore&          getTransparents             ();
    TravMaskStore&      getExcludeNodeTravMask      ();
    TravMaskStore&      getTransparentNodeTravMask  ();
    LightAssocStore&    getLightAssocData           ();

    LightIndexStore&    getPointLightIndices        ();
    LightIndexStore&    getSpotLightIndices         ();
    LightIndexStore&    getDirLightIndices          ();

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiLightShadowStageDataBase.
    bool                _bRunning;
    TechniqueRefPtr     _pTechnique;
    NodeStore           _vTransparents;
    TravMaskStore       _vExcludeNodeTravMask;
    TravMaskStore       _vTransparentNodeTravMask;
    LightAssocStore     _vLightAssocData;
    LightIndexStore     _vPointLightIndices;
    LightIndexStore     _vSpotLightIndices;
    LightIndexStore     _vDirLightIndices;
  
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightShadowStageData(void);
    MultiLightShadowStageData(const MultiLightShadowStageData &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowStageData(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiLightShadowStageDataBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightShadowStageData &source);
};

typedef MultiLightShadowStageData *MultiLightShadowStageDataP;

OSG_END_NAMESPACE

#include "OSGMultiLightShadowStageDataBase.inl"
#include "OSGMultiLightShadowStageData.inl"

#endif /* _OSGMULTILIGHTSHADOWSTAGEDATA_H_ */
