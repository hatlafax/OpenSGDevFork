/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGSHADERUTILITY_H_
#define _OSGSHADERUTILITY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

namespace Shader {

/*! \name Shader Functions
    Shader utility functions that provide common shader code for easy
    integration into existing shader on the source code level.
    \{
 */

OSG_SYSTEM_DLLMAPPING std::string getConstantsSnippet                   ();

OSG_SYSTEM_DLLMAPPING std::string getLanguageExtSnippet                 ();

OSG_SYSTEM_DLLMAPPING std::string getEqualEpsDeclSnippet                ();
OSG_SYSTEM_DLLMAPPING std::string getEqualEpsSnippet                    ();

OSG_SYSTEM_DLLMAPPING std::string getEqualDefaultTestMatrixDeclSnippet  ();
OSG_SYSTEM_DLLMAPPING std::string getEqualDefaultTestMatrixSnippet      ();

OSG_SYSTEM_DLLMAPPING std::string getColorsDeclSnippet                  ();
OSG_SYSTEM_DLLMAPPING std::string getColorsSnippet                      ();

OSG_SYSTEM_DLLMAPPING std::string getCubemapDeclSnippet                 ();
OSG_SYSTEM_DLLMAPPING std::string getCubemapSnippet                     ();

OSG_SYSTEM_DLLMAPPING std::string getLocalFrameDeclSnippet              ();
OSG_SYSTEM_DLLMAPPING std::string getLocalFrameSnippet                  ();

OSG_SYSTEM_DLLMAPPING std::string getUtilityFunctionsDeclSnippet        ();
OSG_SYSTEM_DLLMAPPING std::string getUtilityFunctionsSnippet            ();

OSG_SYSTEM_DLLMAPPING std::string getSRGBConversionDeclSnippet          ();
OSG_SYSTEM_DLLMAPPING std::string getSRGBConversionSnippet              (bool sRGBApprox);

OSG_SYSTEM_DLLMAPPING std::string getColorSpaceConversionDeclSnippet    ();
OSG_SYSTEM_DLLMAPPING std::string getColorSpaceConversionSnippet        (bool sRGBApprox);

/*! \} 
 */

} // namespace Shader

OSG_END_NAMESPACE

#endif /* _OSGSHADERUTILITY_H_ */
