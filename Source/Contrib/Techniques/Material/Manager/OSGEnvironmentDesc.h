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

#ifndef _OSGENVIRONMENTDESC_H_
#define _OSGENVIRONMENTDESC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGEnvironmentDescBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief EnvironmentDesc class. See \ref
           PageContribTechniquesEnvironmentDesc for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING EnvironmentDesc : public EnvironmentDescBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EnvironmentDescBase Inherited;
    typedef EnvironmentDesc     Self;

    enum Feature
    {
        FEATURE_TONEMAPPING              = 0x01,
        FEATURE_GAMMA_CORRECTION         = 0x02,
        FEATURE_CLASSIC_LIGHT_EXTENSIONS = 0x04,
        FEATURE_FOG                      = 0x08,
        FEATURE_CLIP_PLANES              = 0x10
    };

    enum ToneMappingModes
    {
        NO_TONE_MAPPING = 0,
        LOGARITHMIC_TONE_MAPPING,
        EXPONENTIAL_TONE_MAPPING,
        DRAGO_LOGARITHMIC_TONE_MAPPING, 
        REINHARD_TONE_MAPPING,
        REINHARD_MODIFIED_TONE_MAPPING,
        FILMIC_HABLE_TONE_MAPPING,
        FILMIC_UNCHARTED2_TONE_MAPPING,
        FILMIC_ACES_TONE_MAPPING,
        FILMIC_HEJ2015_TONE_MAPPING,
        FILMIC_ACES_2_TONE_MAPPING,
    };

    enum AutoExposureMode
    {
        MANUAL = 0,
        KEY_VALUE, 
        AUTOMATIC,
        SATURATION_BASED,
        STANDARD_OUTPUT_BASED
    };

    /*---------------------------------------------------------------------*/
    /*! \name                     Interface                                */
    /*! \{                                                                 */

    void setHasFeatureTonemapping               (bool value);
    void setHasFeatureGammaCorrection           (bool value);
    void setHasFeatureClassicLightExtension     (bool value);
    void setHasFeatureFog                       (bool value);
    void setHasFeatureClipPlanes                (bool value);

    bool getHasFeatureTonemapping               () const;
    bool getHasFeatureGammaCorrection           () const;
    bool getHasFeatureClassicLightExtension     () const;
    bool getHasFeatureFog                       () const;
    bool getHasFeatureClipPlanes                () const;

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

    // Variables should all be in EnvironmentDescBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EnvironmentDesc(void);
    EnvironmentDesc(const EnvironmentDesc &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EnvironmentDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EnvironmentDescBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const EnvironmentDesc &source);

    void setFeatureImpl(UInt32 feature);
};

typedef EnvironmentDesc *EnvironmentDescP;

OSG_END_NAMESPACE

#include "OSGEnvironmentDescBase.inl"
#include "OSGEnvironmentDesc.inl"

#endif /* _OSGENVIRONMENTDESC_H_ */
