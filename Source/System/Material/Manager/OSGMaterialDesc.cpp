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

#include "OSGMaterialDesc.h"
#include "OSGTextureDesc.h"
#include "OSGImage.h"

#include "OSGBaseHash.h"

#include "OSGAttachment.h"

OSG_BEGIN_NAMESPACE

MaterialDesc::BinaryWriteHandler::BinaryWriteHandler(Hash64& hasher)
: BinaryDataHandler(1   )
, _writeMemory     (8192)
, _hasher          (hasher)
{
    writeBufAdd(&_writeMemory[0], _writeMemory.size());
}

MaterialDesc::BinaryWriteHandler::~BinaryWriteHandler(void)
{
}

void MaterialDesc::BinaryWriteHandler::write(MemoryHandle mem, UInt32 size)
{
    _hasher.update(reinterpret_cast<const void*>(mem), size);
}



// Documentation for this class is emitted in the
// OSGMaterialDescBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialDesc.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialDesc::initMethod(InitPhase ePhase)
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

MaterialDesc::MaterialDesc(void) :
    Inherited()
{
}

MaterialDesc::MaterialDesc(const MaterialDesc &source) :
    Inherited(source)
{
}

MaterialDesc::~MaterialDesc(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialDesc::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MaterialDesc::dump(      UInt32    ,
                         const BitVector ) const
{
    std::string spc = "    ";

    SLOG << "Dump MaterialDesc NI" << std::endl;

    SLOG << spc << "Name                         = " << getName() << std::endl;

    SLOG << spc << "SRGBColorMode                = " << getSRGBColorMode() << std::endl;
    SLOG << spc << "ShadowOnlyMode               = " << getShadowOnlyMode() << std::endl;
    SLOG << spc << "PbrSpecularMode              = " << getPbrSpecularMode() << std::endl;
    SLOG << spc << "PbrClearCoatMode             = " << getPbrClearCoatMode() << std::endl;
    SLOG << spc << "PbrSheenColorMode            = " << getPbrSheenColorMode() << std::endl;
    SLOG << spc << "PbrAnisotropyMode            = " << getPbrAnisotropyMode() << std::endl;
    SLOG << spc << "UnlitMode                    = " << getUnlitMode() << std::endl;
    SLOG << spc << "HasNormalsMode               = " << getHasNormalsMode() << std::endl;
    SLOG << spc << "HasTangentsAndBitangentsMode = " << getHasTangentsAndBitangentsMode() << std::endl;
    SLOG << spc << "FlatShadingMode              = " << getFlatShadingMode() << std::endl;
    SLOG << spc << "OffsetPointMode              = " << getOffsetPointMode() << std::endl;
    SLOG << spc << "OffsetLineMode               = " << getOffsetLineMode() << std::endl;
    SLOG << spc << "OffsetFillMode               = " << getOffsetFillMode() << std::endl;
    SLOG << spc << "XORMode                      = " << getXORMode() << std::endl;
    SLOG << spc << "NoDepthTestMode              = " << getNoDepthTestMode() << std::endl;

    SLOG << spc << "RefractiveIndex              = " << getRefractiveIndex() << std::endl;
    SLOG << spc << "Shininess                    = " << getShininess() << std::endl;

    SLOG << spc << "DescHash                     = " << getDescHash() << std::endl;
    SLOG << spc << "NumUVChannels                = " << getNumUVChannels() << std::endl;

    for (UInt32 idx = 0; idx < _mfUVDimension.size32(); ++idx)
    {
        SLOG << spc << "UVDimension[" << idx << "]" << "         = " << static_cast<unsigned int>(getUVDimension(idx)) << std::endl;
    }

    SLOG << spc << "NumColorChannels             = " << getNumColorChannels() << std::endl;

    std::string shading_model = "NO_SHADING_MODEL";
    switch (getShadingModel())
    {
        case NO_SHADING_MODEL:            shading_model = "NO_SHADING_MODEL";            break;
        case GOURAUD_SHADING_MODEL:       shading_model = "GOURAUD_SHADING_MODEL";       break;
        case PHONG_SHADING_MODEL:         shading_model = "PHONG_SHADING_MODEL";         break;
        case BLINN_PHONG_SHADING_MODEL:   shading_model = "BLINN_PHONG_SHADING_MODEL";   break;
        case COOK_TORRANCE_SHADING_MODEL: shading_model = "COOK_TORRANCE_SHADING_MODEL"; break;
        case OREN_NAYAR_SHADING_MODEL:    shading_model = "OREN_NAYAR_SHADING_MODEL";    break;
        case TOON_SHADING_MODEL:          shading_model = "TOON_SHADING_MODEL";          break;
        case GOOCH_SHADING_MODEL:         shading_model = "GOOCH_SHADING_MODEL";         break;
    }
    SLOG << spc << "ShadingModel                 = " << shading_model << std::endl;


    std::string override_shading_model = "NO_SHADING_MODEL";
    switch (getOverrideShadingModel())
    {
        case NO_SHADING_MODEL:            override_shading_model = "NO_SHADING_MODEL";            break;
        case GOURAUD_SHADING_MODEL:       override_shading_model = "GOURAUD_SHADING_MODEL";       break;
        case PHONG_SHADING_MODEL:         override_shading_model = "PHONG_SHADING_MODEL";         break;
        case BLINN_PHONG_SHADING_MODEL:   override_shading_model = "BLINN_PHONG_SHADING_MODEL";   break;
        case COOK_TORRANCE_SHADING_MODEL: override_shading_model = "COOK_TORRANCE_SHADING_MODEL"; break;
        case OREN_NAYAR_SHADING_MODEL:    override_shading_model = "OREN_NAYAR_SHADING_MODEL";    break;
        case TOON_SHADING_MODEL:          override_shading_model = "TOON_SHADING_MODEL";          break;
        case GOOCH_SHADING_MODEL:         override_shading_model = "GOOCH_SHADING_MODEL";         break;
    }
    SLOG << spc << "OverrideShadingModel         = " << override_shading_model << std::endl;

    std::string blend_mode = "DEFAULT_BLEND_MODE";
    switch (getBlendMode())
    {
        case DEFAULT_BLEND_MODE:        blend_mode = "DEFAULT_BLEND_MODE";        break;
        case ADDITIVE_BLEND_MODE:       blend_mode = "ADDITIVE_BLEND_MODE";       break;
        case MULTIPLICATIVE_BLEND_MODE: blend_mode = "MULTIPLICATIVE_BLEND_MODE"; break;
        case INTERPOLATION_BLEND_MODE:  blend_mode = "INTERPOLATION_BLEND_MODE";  break;
    }
    SLOG << spc << "BlendMode                    = " << blend_mode << std::endl;

    SLOG << spc << "Emissive                     = " << getEmissive() << std::endl;
    SLOG << spc << "Albedo                       = " << getAlbedo() << std::endl;
    SLOG << spc << "Specular                     = " << getSpecular() << std::endl;
    SLOG << spc << "Transparent                  = " << getTransparent() << std::endl;
    SLOG << spc << "Reflective                   = " << getReflective() << std::endl;
    
    SLOG << spc << "SpecularStrength             = " << getSpecularStrength() << std::endl;
    SLOG << spc << "EmissiveStrength             = " << getEmissiveStrength() << std::endl;
    SLOG << spc << "Opacity                      = " << getOpacity() << std::endl;
    SLOG << spc << "OpacityCutOff                = " << getOpacityCutOff() << std::endl;

    std::string opacity_mode = "NO_OPACITY_MODE";
    switch (getOpacityMode())
    {
        case NO_OPACITY_MODE:     opacity_mode = "NO_OPACITY_MODE";     break;
        case OPAQUE_OPACITY_MODE: opacity_mode = "OPAQUE_OPACITY_MODE"; break;
        case MASK_OPACITY_MODE:   opacity_mode = "MASK_OPACITY_MODE";   break;
        case BLEND_OPACITY_MODE:  opacity_mode = "BLEND_OPACITY_MODE";  break;
    }
    SLOG << spc << "OpacityMode                  = " << opacity_mode << std::endl;

    SLOG << spc << "Reflectivity                 = " << getReflectivity() << std::endl;
    SLOG << spc << "Reflectance                  = " << getReflectance() << std::endl;
    SLOG << spc << "BumpScaling                  = " << getBumpScaling() << std::endl;
    SLOG << spc << "Anisotropy                   = " << getAnisotropy() << std::endl;
    SLOG << spc << "Roughness                    = " << getRoughness() << std::endl;
    SLOG << spc << "Metalness                    = " << getMetalness() << std::endl;
    SLOG << spc << "ClearCoatStrength            = " << getClearCoatStrength() << std::endl;
    SLOG << spc << "ClearCoatRoughness           = " << getClearCoatRoughness() << std::endl;
    
    SLOG << spc << "SheenColor                   = " << getSheenColor() << std::endl;
    SLOG << spc << "SubSurfaceColor              = " << getSubSurfaceColor() << std::endl;
    SLOG << spc << "ToonLevels                   = " << getToonLevels() << std::endl;
    SLOG << spc << "GoochCool                    = " << getGoochCool() << std::endl;
    SLOG << spc << "GoochWarm                    = " << getGoochWarm() << std::endl;
    SLOG << spc << "GoochMixin                   = " << getGoochMixin() << std::endl;
    SLOG << spc << "GoochCoolMixin               = " << getGoochCoolMixin() << std::endl;
    SLOG << spc << "GoochWarmMixin               = " << getGoochWarmMixin() << std::endl;

    SLOG << spc << "CullFace                     = " << getCullFace() << std::endl;
    SLOG << spc << "FrontFace                    = " << getFrontFace() << std::endl;

    std::string front_mode = "UNKNOWN";
    switch (getFrontMode())
    {
        case GL_POINT: front_mode = "GL_POINT"; break;
        case GL_LINE:  front_mode = "GL_LINE";  break;
        case GL_FILL:  front_mode = "GL_FILL";  break;
    }
    SLOG << spc << "FrontMode                    = " << front_mode << std::endl;

    std::string back_mode = "UNKNOWN";
    switch (getBackMode())
    {
        case GL_POINT: back_mode = "GL_POINT"; break;
        case GL_LINE:  back_mode = "GL_LINE";  break;
        case GL_FILL:  back_mode = "GL_FILL";  break;
    }
    SLOG << spc << "BackMode                     = " << back_mode << std::endl;

    SLOG << spc << "OffsetFactor                 = " << getOffsetFactor() << std::endl;
    SLOG << spc << "OffsetBias                   = " << getOffsetBias() << std::endl;

    MFUnrecTextureDescPtr::const_iterator iter, end;

    iter = _mfTextureDesc.begin();
    end  = _mfTextureDesc.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;
        texDesc->dump();
    }
}

MaterialDesc::HashKeyType MaterialDesc::getHashValue()
{
    Hash64 hasher;
    MaterialDesc::BinaryWriteHandler wh(hasher);
    
    calcHash(this, wh, getExcludeHashingMask());

    return hasher.finish();
}

void MaterialDesc::calcHash(Image* img, BinaryWriteHandler& wh) const
{
    std::size_t hash = img->getHash();
    wh.putValue(hash);
}

void MaterialDesc::calcHash(FieldContainer* fc, BinaryWriteHandler& wh, BitVector excludeMask) const
{
    UInt32 fieldCount = fc->getType().getNumFieldDescs();

    for (UInt32 fieldId = 1; fieldId <= fieldCount; ++fieldId)
    {
        const FieldDescriptionBase *fieldDesc = fc->getFieldDescription(fieldId);
        const FieldType            &fieldType = fieldDesc->getFieldType();
        const std::string          &fieldName = fieldDesc->getName     ();
                BitVector           fieldMask = fieldDesc->getFieldMask();

        if (fieldDesc->isInternal())
        {
            continue;
        }

        if (fieldMask & excludeMask)
        {
            continue;
        }

        if (fieldType.getContentType().isDerivedFrom(
                FieldTraits<AttachmentMap>::getType()) == true)
        {
            continue;
        }
        else if (fieldType.getContentType().isDerivedFrom(
                    FieldTraits<FieldContainer *>::getMapType()) == true)
        {
            continue;
        }
        else if (fieldType.getContentType().isDerivedFrom(
                    FieldTraits<FieldContainer *>::getType()) == true)
        {
            if (fieldType.getCardinality() == FieldType::SingleField)
            {
                FieldContainerPtrSFieldBase::GetHandlePtr sfPtrField = boost::dynamic_pointer_cast<FieldContainerPtrSFieldBase::GetHandle>(fc->getField(fieldId));

                if (sfPtrField == NULL || sfPtrField->isValid() == false)
                    continue;

                FieldContainer *refedFC = (*sfPtrField)->getValue();

                if (refedFC == NULL)
                    continue;

                Image* img = dynamic_cast<Image*>(refedFC);
                if (img)
                {
                    calcHash(img, wh);
                }
                else
                {
                    calcHash(refedFC, wh, 0);
                }
            }
            else if (fieldType.getCardinality() == FieldType::MultiField)
            {
                FieldContainerPtrMFieldBase::GetHandlePtr mfPtrField = boost::dynamic_pointer_cast<FieldContainerPtrMFieldBase::GetHandle>(fc->getField(fieldId));

                if (mfPtrField == NULL || mfPtrField->isValid() == false)
                    continue;

                FieldContainerPtrMFieldBase::const_iterator fieldIt  = (*mfPtrField)->begin();
                FieldContainerPtrMFieldBase::const_iterator fieldEnd = (*mfPtrField)->end  ();

                for (; fieldIt != fieldEnd; ++fieldIt)
                {
                    FieldContainer *refedFC = *fieldIt;
                    if (refedFC == NULL)
                        continue;

                    Image* img = dynamic_cast<Image*>(refedFC);
                    if (img)
                    {
                        calcHash(img, wh);
                    }
                    else
                    {
                        calcHash(refedFC, wh, 0);
                    }
                }
            }
        }
        else
        {
            fc->copyToBin(wh, fieldMask);
        }
    }
}

void MaterialDesc::addTexture(TextureDesc* texDesc)
{
    if (texDesc)
    {
        if (texDesc->getTexImage() == NULL)
        {
            texDesc->loadImage();
        }
        if (texDesc->hasTexImage())
        {
            pushToTextureDesc(texDesc);
        }
    }
}

//
// R := reflectance, the perceptual reflectance with R in [0,1]
// n := index of refrection
// f0 = fresnel reflection at normal incidence
//
//      f0 = (n-1)^2 / (n+1)^2
//
//      f0 = 0.16 * R^2 with R in [0,1] : R = 0.5 => f0 = 0.04
//                                        R = 1.0 => f0 = 0.16
//
//      R = sqrt(f0/0.16) = sqrt( (n-1)^2 / [0.16*(n+1)^2] ) = 2.5 * (n-1)/(n+1)
//

void MaterialDesc::setRefractiveIndex(Real32 value)
{
    Real32 reflectance = 2.5f * (value - 1.f) / (value + 1.f);

    reflectance = osgSaturate(reflectance);

    setReflectance(reflectance);
}

Real32 MaterialDesc::getRefractiveIndex() const
{
    return 2.f / (1.f - 0.4 * getReflectance()) - 1.f;
}

Real32 MaterialDesc::getShininess() const
{
    Real32 r = osgClamp(0.04f, getRoughness(), 1.f);
    //return osgClamp(0.01f, (2.f/(r*r)) - 2.f, 1000.f);  // left clamp due to 0^0 problems, 
    //                                                    // right clamp due to classic GL specification
    return osgClamp(0.01f, 4.f*( 2.f/(r*r) - 2.f), 4000.f);  // left clamp due to 0^0 problems, 
                                                        // right clamp due to classic GL specification
}

void MaterialDesc::setShininess(Real32 value)
{
    //setRoughness(osgSqrt(2.f/(value+2.f)));
    setRoughness(osgSqrt(2.f/(0.25f*value+2.f)));
}

OSG_END_NAMESPACE
