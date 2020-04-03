/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#include<OSGSystemDef.h>
#include<OSGFieldDescriptionBase.h>
#include<OSGShaderProgramFunctorCallbackFields.h>

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<ShaderProgramFunctorCallback     >::_type(
    "ShaderProgramFunctorCallback",
    NULL);

OSG_FIELDTRAITS_GETTYPE   (ShaderProgramFunctorCallback     )

#endif

OSG_FIELD_DLLEXPORT_DEF1(SField, ShaderProgramFunctorCallback)
OSG_FIELD_DLLEXPORT_DEF1(MField, ShaderProgramFunctorCallback)

#if 0
template <>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<ShaderProgramFunctorCallback>,
                      SingleField                         >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription::cloneValues called for sf shader program functors.\n"));
}

template <>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<ShaderProgramFunctorCallback>,
                      SingleField                         >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription::shareValues called for sf shader program functors.\n"));
}

template <>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<ShaderProgramFunctorCallback>,
                      MultiField                          >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription::cloneValues called for mf shader program functors.\n"));
}

template <>
OSG_DLL_EXPORT
void FieldDescription<FieldTraits<ShaderProgramFunctorCallback>,
                      MultiField                          >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription::shareValues called for mf shader program functors.\n"));
}
#endif

OSG_END_NAMESPACE
