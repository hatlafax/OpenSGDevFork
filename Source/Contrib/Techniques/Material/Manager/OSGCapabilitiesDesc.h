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

#ifndef _OSGCAPABILITIESDESC_H_
#define _OSGCAPABILITIESDESC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCapabilitiesDescBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CapabilitiesDesc class. See \ref
           PageContribTechniquesCapabilitiesDesc for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING CapabilitiesDesc : public CapabilitiesDescBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CapabilitiesDescBase Inherited;
    typedef CapabilitiesDesc     Self;

    enum Capabilities
    {
        FIXED_FUNCTION_PIPELINE = 0x00000001,

        SHADER_MATERIAL_2       = 0x00000002,   // >= OpenGL 2.1, GLSL 1.2
        SHADER_MATERIAL_3       = 0x00000004,   // >= OpenGL 3.3, GLSL 3.3
        SHADER_MATERIAL_4       = 0x00000008,   // >= OpenGL 4.4, GLSL 4.4

        SHADER_MATERIAL         = SHADER_MATERIAL_2,

        SILHOUETTES             = 0x00000100,   // Not used here
        MULTISAMPLE             = 0x00000200,   // Not used here
        DYNAMIC_VIEWPORT        = 0x00000400,   // Not used here
        CLIP_PLANES             = 0x00000800,

        HDR                     = 0x00010000,
        SSAO                    = 0x00020000,
        MULTILIGHT              = 0x00040000,
        MULTILIGHT_SHADOW       = 0x00080000,
        CLUSTER_SHADING         = 0x00100000,

        BIT_OPERATIONS          = 0x01000000,
        SWITCH_STATEMENT        = 0x02000000,
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Interface                                  */
    /*! \{                                                                 */

    bool    bUseCapabilities                (UInt32 capabilities) const;
    bool    bUsePlatformCapabilities        (UInt32 capabilities) const;
    bool    bUseRequestedCapabilities       (UInt32 capabilities) const;

    bool    isFallbackFixedFunction         () const;
    bool    isFallbackShader2               () const;
    bool    isFallbackShader3               () const;
    bool    isFallbackShader4               () const;

    bool    hasHDRSupport                   () const;
    bool    hasClusterShadingSupport        () const;
    bool    hasMultiLightShadowSupport      () const;
    bool    hasSSAOSupport                  () const;
    bool    hasMultiLightSupport            () const;
    bool    hasModernShaderSupport          () const;
    bool    hasFull440ShaderSupport         () const;
    bool    hasdClipPlanesSupport           () const;

    bool    hasSwitchSupport                () const;
    bool    hasBitOpsSupport                () const;

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

    // Variables should all be in CapabilitiesDescBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CapabilitiesDesc(void);
    CapabilitiesDesc(const CapabilitiesDesc &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CapabilitiesDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CapabilitiesDescBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CapabilitiesDesc &source);
};

typedef CapabilitiesDesc *CapabilitiesDescP;

OSG_END_NAMESPACE

#include "OSGCapabilitiesDescBase.inl"
#include "OSGCapabilitiesDesc.inl"

#endif /* _OSGCAPABILITIESDESC_H_ */
