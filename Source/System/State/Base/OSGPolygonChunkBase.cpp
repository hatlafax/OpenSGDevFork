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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class PolygonChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>


#include <OSGGL.h>                        // CullFace default header
#include <OSGGL.h>                        // FrontFace default header
#include <OSGGL.h>                        // FrontMode default header
#include <OSGGL.h>                        // BackMode default header
#include <OSGGL.h>                        // Smooth default header
#include <OSGGL.h>                        // OffsetPoint default header
#include <OSGGL.h>                        // OffsetLine default header
#include <OSGGL.h>                        // OffsetFill default header


#include "OSGPolygonChunkBase.h"
#include "OSGPolygonChunk.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PolygonChunk
    \ingroup GrpSystemState

    See \ref PageSystemPolygonChunk for details.

    The parameters of the following functions are wrapped here:
    <ul>
    <li>glCullFace() (OSG::PolygonChunk::_sfCullFace),</li>
    <li>glFrontFace()(OSG::PolygonChunk::_sfFrontFace),</li>
    <li>glPolygonMode() (OSG::PolygonChunk::_sfFrontMode, OSG::PolygonChunk::_sfBackMode),</li>
    <li>glEnable(GL_POLYGON_SMOOTH) (OSG::PolygonChunk::_sfSmooth),</li>
    <li>glPolygonOffset() (OSG::PolygonChunk::_sfOffsetFactor, OSG::PolygonChunk::_sfOffsetBias),</li>
    <li>glEnable(GL_POLYGON_OFFSET_POINT) (OSG::PolygonChunk::_sfOffsetPoint),</li>
    <li>glEnable(GL_POLYGON_OFFSET_LINE) (OSG::PolygonChunk::_sfOffsetLine),</li>
    <li>glEnable(GL_POLYGON_OFFSET_FILL) (OSG::PolygonChunk::_sfOffsetFill),</li>
    <li>glStipplePattern() and glEnable(GL_POLYGON_STIPPLE) (OSG::PolygonChunk::_sfStipple).</li>
    </ul>
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var GLenum          PolygonChunkBase::_sfCullFace
    Defines which side of the polygon is invisible. Set to GL_NONE to not cull anything. See glCullFace.
*/

/*! \var GLenum          PolygonChunkBase::_sfFrontFace
    Defines which side of the polygon is considered the front side base on vertex ordering
    of clockwise (CW) of counter clockwise (CCW). defaults to GL_CCW.  See glFrontFace.
*/

/*! \var GLenum          PolygonChunkBase::_sfFrontMode
    Defines if polygon front sides are rendered filled (default), outlined or as points.  See glPolygonMode.
*/

/*! \var GLenum          PolygonChunkBase::_sfBackMode
    Defines if polygon front sides are rendered filled (default), outlined or as points. See glPolygonMode.
*/

/*! \var bool            PolygonChunkBase::_sfSmooth
    Defines if polygon antialiasing is used.  See GL_POLYGON_SMOOTH.
*/

/*! \var Real32          PolygonChunkBase::_sfOffsetFactor
    Defines the offset factor.  See glPolygonOffset.
*/

/*! \var Real32          PolygonChunkBase::_sfOffsetBias
    Defines the offset bias.  See glPolygonOffset.
*/

/*! \var bool            PolygonChunkBase::_sfOffsetPoint
    Enables offsetting for points.
*/

/*! \var bool            PolygonChunkBase::_sfOffsetLine
    Enables offsetting for lines.
*/

/*! \var bool            PolygonChunkBase::_sfOffsetFill
    Enables offsetting for polygons.
*/

/*! \var Int32           PolygonChunkBase::_mfStipple
    Defines the stipple pattern. Is only valid and used if it contains 
    32 elements.
*/


void PolygonChunkBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "cullFace",
        "Defines which side of the polygon is invisible. Set to GL_NONE to not cull anything. See glCullFace.\n",
        CullFaceFieldId, CullFaceFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleCullFace),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleCullFace));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "frontFace",
        "Defines which side of the polygon is considered the front side base on vertex ordering\n"
        "of clockwise (CW) of counter clockwise (CCW). defaults to GL_CCW.  See glFrontFace.\n",
        FrontFaceFieldId, FrontFaceFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleFrontFace),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleFrontFace));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "frontMode",
        "Defines if polygon front sides are rendered filled (default), outlined or as points.  See glPolygonMode.\n",
        FrontModeFieldId, FrontModeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleFrontMode),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleFrontMode));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "backMode",
        "Defines if polygon front sides are rendered filled (default), outlined or as points. See glPolygonMode.\n",
        BackModeFieldId, BackModeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleBackMode),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleBackMode));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "smooth",
        "Defines if polygon antialiasing is used.  See GL_POLYGON_SMOOTH.\n",
        SmoothFieldId, SmoothFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleSmooth),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleSmooth));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "offsetFactor",
        "Defines the offset factor.  See glPolygonOffset.\n",
        OffsetFactorFieldId, OffsetFactorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleOffsetFactor),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleOffsetFactor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "offsetBias",
        "Defines the offset bias.  See glPolygonOffset.\n",
        OffsetBiasFieldId, OffsetBiasFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleOffsetBias),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleOffsetBias));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "offsetPoint",
        "Enables offsetting for points.\n",
        OffsetPointFieldId, OffsetPointFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleOffsetPoint),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleOffsetPoint));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "offsetLine",
        "Enables offsetting for lines.\n",
        OffsetLineFieldId, OffsetLineFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleOffsetLine),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleOffsetLine));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "offsetFill",
        "Enables offsetting for polygons.\n",
        OffsetFillFieldId, OffsetFillFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleOffsetFill),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleOffsetFill));

    oType.addInitialDesc(pDesc);

    pDesc = new MFInt32::Description(
        MFInt32::getClassType(),
        "stipple",
        "Defines the stipple pattern. Is only valid and used if it contains \n"
        "32 elements.\n",
        StippleFieldId, StippleFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&PolygonChunk::editHandleStipple),
        static_cast<FieldGetMethodSig >(&PolygonChunk::getHandleStipple));

    oType.addInitialDesc(pDesc);
}


PolygonChunkBase::TypeObject PolygonChunkBase::_type(
    PolygonChunkBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&PolygonChunkBase::createEmptyLocal),
    PolygonChunk::initMethod,
    PolygonChunk::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&PolygonChunkBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"PolygonChunk\"\n"
    "\tparent=\"StateChunk\"\n"
    "\tlibrary=\"System\"\n"
    "\tstructure=\"concrete\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "><![CDATA[\n"
    "\\ingroup GrpSystemState\n"
    "\n"
    "See \\ref PageSystemPolygonChunk for details.\n"
    "\n"
    "The parameters of the following functions are wrapped here:\n"
    "<ul>\n"
    "<li>glCullFace() (OSG::PolygonChunk::_sfCullFace),</li>\n"
    "<li>glFrontFace()(OSG::PolygonChunk::_sfFrontFace),</li>\n"
    "<li>glPolygonMode() (OSG::PolygonChunk::_sfFrontMode, OSG::PolygonChunk::_sfBackMode),</li>\n"
    "<li>glEnable(GL_POLYGON_SMOOTH) (OSG::PolygonChunk::_sfSmooth),</li>\n"
    "<li>glPolygonOffset() (OSG::PolygonChunk::_sfOffsetFactor, OSG::PolygonChunk::_sfOffsetBias),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_POINT) (OSG::PolygonChunk::_sfOffsetPoint),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_LINE) (OSG::PolygonChunk::_sfOffsetLine),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_FILL) (OSG::PolygonChunk::_sfOffsetFill),</li>\n"
    "<li>glStipplePattern() and glEnable(GL_POLYGON_STIPPLE) (OSG::PolygonChunk::_sfStipple).</li>\n"
    "</ul>]]>\n"
    "\t<Field\n"
    "\t\tname=\"cullFace\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_NONE\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "                potential_values=\"GL_NONE,GL_FRONT,GL_BACK,GL_FRONT_AND_BACK\"\n"
    "\t>\n"
    "\tDefines which side of the polygon is invisible. Set to GL_NONE to not cull anything. See glCullFace.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"frontFace\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_CCW\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "                potential_values=\"GL_CCW,GL_CW\"\n"
    "\t>\n"
    "\tDefines which side of the polygon is considered the front side base on vertex ordering\n"
    "        of clockwise (CW) of counter clockwise (CCW). defaults to GL_CCW.  See glFrontFace.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"frontMode\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FILL\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "                potential_values=\"GL_FILL,GL_LINE,GL_POINT\"\n"
    "\t>\n"
    "\tDefines if polygon front sides are rendered filled (default), outlined or as points.  See glPolygonMode.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"backMode\"\n"
    "\t\ttype=\"GLenum\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FILL\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "                potential_values=\"GL_FILL,GL_LINE,GL_POINT\"                \n"
    "\t>\n"
    "\tDefines if polygon front sides are rendered filled (default), outlined or as points. See glPolygonMode.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"smooth\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FALSE\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "\t>\n"
    "\tDefines if polygon antialiasing is used.  See GL_POLYGON_SMOOTH.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"offsetFactor\"\n"
    "\t\ttype=\"Real32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "\t>\n"
    "\tDefines the offset factor.  See glPolygonOffset.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"offsetBias\"\n"
    "\t\ttype=\"Real32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "\t>\n"
    "\tDefines the offset bias.  See glPolygonOffset.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"offsetPoint\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FALSE\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "\t>\n"
    "\tEnables offsetting for points.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"offsetLine\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FALSE\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "\t>\n"
    "\tEnables offsetting for lines.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"offsetFill\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"GL_FALSE\"\n"
    "\t\tdefaultHeader=\"&lt;OSGGL.h&gt;\"\n"
    "\t>\n"
    "\tEnables offsetting for polygons.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"stipple\"\n"
    "\t\ttype=\"Int32\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"\"\n"
    "\t>\n"
    "\tDefines the stipple pattern. Is only valid and used if it contains \n"
    "        32 elements.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "\\ingroup GrpSystemState\n"
    "\n"
    "See \\ref PageSystemPolygonChunk for details.\n"
    "\n"
    "The parameters of the following functions are wrapped here:\n"
    "<ul>\n"
    "<li>glCullFace() (OSG::PolygonChunk::_sfCullFace),</li>\n"
    "<li>glFrontFace()(OSG::PolygonChunk::_sfFrontFace),</li>\n"
    "<li>glPolygonMode() (OSG::PolygonChunk::_sfFrontMode, OSG::PolygonChunk::_sfBackMode),</li>\n"
    "<li>glEnable(GL_POLYGON_SMOOTH) (OSG::PolygonChunk::_sfSmooth),</li>\n"
    "<li>glPolygonOffset() (OSG::PolygonChunk::_sfOffsetFactor, OSG::PolygonChunk::_sfOffsetBias),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_POINT) (OSG::PolygonChunk::_sfOffsetPoint),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_LINE) (OSG::PolygonChunk::_sfOffsetLine),</li>\n"
    "<li>glEnable(GL_POLYGON_OFFSET_FILL) (OSG::PolygonChunk::_sfOffsetFill),</li>\n"
    "<li>glStipplePattern() and glEnable(GL_POLYGON_STIPPLE) (OSG::PolygonChunk::_sfStipple).</li>\n"
    "</ul>\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &PolygonChunkBase::getType(void)
{
    return _type;
}

const FieldContainerType &PolygonChunkBase::getType(void) const
{
    return _type;
}

UInt32 PolygonChunkBase::getContainerSize(void) const
{
    return sizeof(PolygonChunk);
}

/*------------------------- decorator get ------------------------------*/


SFGLenum *PolygonChunkBase::editSFCullFace(void)
{
    editSField(CullFaceFieldMask);

    return &_sfCullFace;
}

const SFGLenum *PolygonChunkBase::getSFCullFace(void) const
{
    return &_sfCullFace;
}


SFGLenum *PolygonChunkBase::editSFFrontFace(void)
{
    editSField(FrontFaceFieldMask);

    return &_sfFrontFace;
}

const SFGLenum *PolygonChunkBase::getSFFrontFace(void) const
{
    return &_sfFrontFace;
}


SFGLenum *PolygonChunkBase::editSFFrontMode(void)
{
    editSField(FrontModeFieldMask);

    return &_sfFrontMode;
}

const SFGLenum *PolygonChunkBase::getSFFrontMode(void) const
{
    return &_sfFrontMode;
}


SFGLenum *PolygonChunkBase::editSFBackMode(void)
{
    editSField(BackModeFieldMask);

    return &_sfBackMode;
}

const SFGLenum *PolygonChunkBase::getSFBackMode(void) const
{
    return &_sfBackMode;
}


SFBool *PolygonChunkBase::editSFSmooth(void)
{
    editSField(SmoothFieldMask);

    return &_sfSmooth;
}

const SFBool *PolygonChunkBase::getSFSmooth(void) const
{
    return &_sfSmooth;
}


SFReal32 *PolygonChunkBase::editSFOffsetFactor(void)
{
    editSField(OffsetFactorFieldMask);

    return &_sfOffsetFactor;
}

const SFReal32 *PolygonChunkBase::getSFOffsetFactor(void) const
{
    return &_sfOffsetFactor;
}


SFReal32 *PolygonChunkBase::editSFOffsetBias(void)
{
    editSField(OffsetBiasFieldMask);

    return &_sfOffsetBias;
}

const SFReal32 *PolygonChunkBase::getSFOffsetBias(void) const
{
    return &_sfOffsetBias;
}


SFBool *PolygonChunkBase::editSFOffsetPoint(void)
{
    editSField(OffsetPointFieldMask);

    return &_sfOffsetPoint;
}

const SFBool *PolygonChunkBase::getSFOffsetPoint(void) const
{
    return &_sfOffsetPoint;
}


SFBool *PolygonChunkBase::editSFOffsetLine(void)
{
    editSField(OffsetLineFieldMask);

    return &_sfOffsetLine;
}

const SFBool *PolygonChunkBase::getSFOffsetLine(void) const
{
    return &_sfOffsetLine;
}


SFBool *PolygonChunkBase::editSFOffsetFill(void)
{
    editSField(OffsetFillFieldMask);

    return &_sfOffsetFill;
}

const SFBool *PolygonChunkBase::getSFOffsetFill(void) const
{
    return &_sfOffsetFill;
}


MFInt32 *PolygonChunkBase::editMFStipple(void)
{
    editMField(StippleFieldMask, _mfStipple);

    return &_mfStipple;
}

const MFInt32 *PolygonChunkBase::getMFStipple(void) const
{
    return &_mfStipple;
}






/*------------------------------ access -----------------------------------*/

UInt32 PolygonChunkBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (CullFaceFieldMask & whichField))
    {
        returnValue += _sfCullFace.getBinSize();
    }
    if(FieldBits::NoField != (FrontFaceFieldMask & whichField))
    {
        returnValue += _sfFrontFace.getBinSize();
    }
    if(FieldBits::NoField != (FrontModeFieldMask & whichField))
    {
        returnValue += _sfFrontMode.getBinSize();
    }
    if(FieldBits::NoField != (BackModeFieldMask & whichField))
    {
        returnValue += _sfBackMode.getBinSize();
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        returnValue += _sfSmooth.getBinSize();
    }
    if(FieldBits::NoField != (OffsetFactorFieldMask & whichField))
    {
        returnValue += _sfOffsetFactor.getBinSize();
    }
    if(FieldBits::NoField != (OffsetBiasFieldMask & whichField))
    {
        returnValue += _sfOffsetBias.getBinSize();
    }
    if(FieldBits::NoField != (OffsetPointFieldMask & whichField))
    {
        returnValue += _sfOffsetPoint.getBinSize();
    }
    if(FieldBits::NoField != (OffsetLineFieldMask & whichField))
    {
        returnValue += _sfOffsetLine.getBinSize();
    }
    if(FieldBits::NoField != (OffsetFillFieldMask & whichField))
    {
        returnValue += _sfOffsetFill.getBinSize();
    }
    if(FieldBits::NoField != (StippleFieldMask & whichField))
    {
        returnValue += _mfStipple.getBinSize();
    }

    return returnValue;
}

void PolygonChunkBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (CullFaceFieldMask & whichField))
    {
        _sfCullFace.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FrontFaceFieldMask & whichField))
    {
        _sfFrontFace.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FrontModeFieldMask & whichField))
    {
        _sfFrontMode.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BackModeFieldMask & whichField))
    {
        _sfBackMode.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        _sfSmooth.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetFactorFieldMask & whichField))
    {
        _sfOffsetFactor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetBiasFieldMask & whichField))
    {
        _sfOffsetBias.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetPointFieldMask & whichField))
    {
        _sfOffsetPoint.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetLineFieldMask & whichField))
    {
        _sfOffsetLine.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OffsetFillFieldMask & whichField))
    {
        _sfOffsetFill.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StippleFieldMask & whichField))
    {
        _mfStipple.copyToBin(pMem);
    }
}

void PolygonChunkBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (CullFaceFieldMask & whichField))
    {
        _sfCullFace.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FrontFaceFieldMask & whichField))
    {
        _sfFrontFace.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FrontModeFieldMask & whichField))
    {
        _sfFrontMode.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BackModeFieldMask & whichField))
    {
        _sfBackMode.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SmoothFieldMask & whichField))
    {
        _sfSmooth.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetFactorFieldMask & whichField))
    {
        _sfOffsetFactor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetBiasFieldMask & whichField))
    {
        _sfOffsetBias.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetPointFieldMask & whichField))
    {
        _sfOffsetPoint.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetLineFieldMask & whichField))
    {
        _sfOffsetLine.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OffsetFillFieldMask & whichField))
    {
        _sfOffsetFill.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StippleFieldMask & whichField))
    {
        _mfStipple.copyFromBin(pMem);
    }
}

//! create a new instance of the class
PolygonChunkTransitPtr PolygonChunkBase::createLocal(BitVector bFlags)
{
    PolygonChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<PolygonChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
PolygonChunkTransitPtr PolygonChunkBase::createDependent(BitVector bFlags)
{
    PolygonChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<PolygonChunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
PolygonChunkTransitPtr PolygonChunkBase::create(void)
{
    PolygonChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<PolygonChunk>(tmpPtr);
    }

    return fc;
}

PolygonChunk *PolygonChunkBase::createEmptyLocal(BitVector bFlags)
{
    PolygonChunk *returnValue;

    newPtr<PolygonChunk>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
PolygonChunk *PolygonChunkBase::createEmpty(void)
{
    PolygonChunk *returnValue;

    newPtr<PolygonChunk>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr PolygonChunkBase::shallowCopyLocal(
    BitVector bFlags) const
{
    PolygonChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PolygonChunk *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr PolygonChunkBase::shallowCopyDependent(
    BitVector bFlags) const
{
    PolygonChunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const PolygonChunk *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr PolygonChunkBase::shallowCopy(void) const
{
    PolygonChunk *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const PolygonChunk *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

PolygonChunkBase::PolygonChunkBase(void) :
    Inherited(),
    _sfCullFace               (GLenum(GL_NONE)),
    _sfFrontFace              (GLenum(GL_CCW)),
    _sfFrontMode              (GLenum(GL_FILL)),
    _sfBackMode               (GLenum(GL_FILL)),
    _sfSmooth                 (bool(GL_FALSE)),
    _sfOffsetFactor           (Real32(0)),
    _sfOffsetBias             (Real32(0)),
    _sfOffsetPoint            (bool(GL_FALSE)),
    _sfOffsetLine             (bool(GL_FALSE)),
    _sfOffsetFill             (bool(GL_FALSE)),
    _mfStipple                ()
{
}

PolygonChunkBase::PolygonChunkBase(const PolygonChunkBase &source) :
    Inherited(source),
    _sfCullFace               (source._sfCullFace               ),
    _sfFrontFace              (source._sfFrontFace              ),
    _sfFrontMode              (source._sfFrontMode              ),
    _sfBackMode               (source._sfBackMode               ),
    _sfSmooth                 (source._sfSmooth                 ),
    _sfOffsetFactor           (source._sfOffsetFactor           ),
    _sfOffsetBias             (source._sfOffsetBias             ),
    _sfOffsetPoint            (source._sfOffsetPoint            ),
    _sfOffsetLine             (source._sfOffsetLine             ),
    _sfOffsetFill             (source._sfOffsetFill             ),
    _mfStipple                (source._mfStipple                )
{
}


/*-------------------------- destructors ----------------------------------*/

PolygonChunkBase::~PolygonChunkBase(void)
{
}


GetFieldHandlePtr PolygonChunkBase::getHandleCullFace        (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfCullFace,
             this->getType().getFieldDesc(CullFaceFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleCullFace       (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfCullFace,
             this->getType().getFieldDesc(CullFaceFieldId)));


    editSField(CullFaceFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleFrontFace       (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfFrontFace,
             this->getType().getFieldDesc(FrontFaceFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleFrontFace      (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfFrontFace,
             this->getType().getFieldDesc(FrontFaceFieldId)));


    editSField(FrontFaceFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleFrontMode       (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfFrontMode,
             this->getType().getFieldDesc(FrontModeFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleFrontMode      (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfFrontMode,
             this->getType().getFieldDesc(FrontModeFieldId)));


    editSField(FrontModeFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleBackMode        (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfBackMode,
             this->getType().getFieldDesc(BackModeFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleBackMode       (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfBackMode,
             this->getType().getFieldDesc(BackModeFieldId)));


    editSField(BackModeFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleSmooth          (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfSmooth,
             this->getType().getFieldDesc(SmoothFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleSmooth         (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfSmooth,
             this->getType().getFieldDesc(SmoothFieldId)));


    editSField(SmoothFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleOffsetFactor    (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfOffsetFactor,
             this->getType().getFieldDesc(OffsetFactorFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleOffsetFactor   (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfOffsetFactor,
             this->getType().getFieldDesc(OffsetFactorFieldId)));


    editSField(OffsetFactorFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleOffsetBias      (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfOffsetBias,
             this->getType().getFieldDesc(OffsetBiasFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleOffsetBias     (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfOffsetBias,
             this->getType().getFieldDesc(OffsetBiasFieldId)));


    editSField(OffsetBiasFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleOffsetPoint     (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfOffsetPoint,
             this->getType().getFieldDesc(OffsetPointFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleOffsetPoint    (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfOffsetPoint,
             this->getType().getFieldDesc(OffsetPointFieldId)));


    editSField(OffsetPointFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleOffsetLine      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfOffsetLine,
             this->getType().getFieldDesc(OffsetLineFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleOffsetLine     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfOffsetLine,
             this->getType().getFieldDesc(OffsetLineFieldId)));


    editSField(OffsetLineFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleOffsetFill      (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfOffsetFill,
             this->getType().getFieldDesc(OffsetFillFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleOffsetFill     (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfOffsetFill,
             this->getType().getFieldDesc(OffsetFillFieldId)));


    editSField(OffsetFillFieldMask);

    return returnValue;
}

GetFieldHandlePtr PolygonChunkBase::getHandleStipple         (void) const
{
    MFInt32::GetHandlePtr returnValue(
        new  MFInt32::GetHandle(
             &_mfStipple,
             this->getType().getFieldDesc(StippleFieldId)));

    return returnValue;
}

EditFieldHandlePtr PolygonChunkBase::editHandleStipple        (void)
{
    MFInt32::EditHandlePtr returnValue(
        new  MFInt32::EditHandle(
             &_mfStipple,
             this->getType().getFieldDesc(StippleFieldId)));


    editMField(StippleFieldMask, _mfStipple);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void PolygonChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    PolygonChunk *pThis = static_cast<PolygonChunk *>(this);

    pThis->execSync(static_cast<PolygonChunk *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *PolygonChunkBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    PolygonChunk *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const PolygonChunk *>(pRefAspect),
                  dynamic_cast<const PolygonChunk *>(this));

    return returnValue;
}
#endif

void PolygonChunkBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfStipple.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<PolygonChunk *>::_type("PolygonChunkPtr", "StateChunkPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(PolygonChunk *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           PolygonChunk *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           PolygonChunk *,
                           0);

OSG_END_NAMESPACE
