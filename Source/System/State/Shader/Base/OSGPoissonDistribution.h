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

#ifndef _OSGPOISSONDISTRIBUTION_H_
#define _OSGPOISSONDISTRIBUTION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

namespace Shader {

/*! \name Ready to use single precision Poisson Disks.
    \{
 */
OSG_SYSTEM_DLLMAPPING std::string getPoissonDiskSnippet                 (std::vector<Int16>& sizes);

} // namespace Shader

namespace Distribution {

// Poisson distribution on Line [-1,1]
OSG_SYSTEM_DLLMAPPING std::vector<Real32> getPoissonLine                (UInt32 size);

// Poisson distrubution on unit disk [-1,1]^2 ^ |p| <= 1
OSG_SYSTEM_DLLMAPPING std::vector<Vec2f>  getPoissonDisk                (UInt32 size);
    
// Poisson distribution on unit quad [-1,1]^2
OSG_SYSTEM_DLLMAPPING std::vector<Vec2f>  getPoissonQuad                (UInt32 size);

// Poisson distribution on unit sphere [-1,1]^3 ^ |p| <= 1
OSG_SYSTEM_DLLMAPPING std::vector<Vec3f>  getPoissonSphere              (UInt32 size);
    
// Poisson distribution on unit box [-1,1]^3
OSG_SYSTEM_DLLMAPPING std::vector<Vec3f>  getPoissonBox                 (UInt32 size);

// Poisson distribution on unit hemisphere [-1,1]x[-1,1]x[0,1] ^ |p| <= 1
OSG_SYSTEM_DLLMAPPING std::vector<Vec3f>  getPoissonHemisphere          (UInt32 size);

// Poisson distribution on unit hemisphere [-1,1]x[-1,1]x[0,1] ^ |p| == 1
OSG_SYSTEM_DLLMAPPING std::vector<Vec3f>  getPoissonHemisphereSurface   (UInt32 size);
    

// Helper function for mapping Poisson distrubution on unit disk [-1,1]^2 ^ |p| <= 1
// to Poisson distribution on unit hemisphere [-1,1]x[-1,1]x[0,1] ^ |p| == 1
OSG_SYSTEM_DLLMAPPING std::vector<Vec3f>  calcHemisphereSurfaceFromDisk (const std::vector<Vec2f>& disk);

/*! \} 
 */

} // namespace Distribution

OSG_END_NAMESPACE

#endif /* _OSGPOISSONDISTRIBUTION_H_ */
