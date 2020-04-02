/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGASSIMPMESHPROCESSOR_H_
#define _OSGASSIMPMESHPROCESSOR_H_

/*! \file OSGAssimpMeshProcessor.h
    \ingroup GrpLoader
 */

#include <map>

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"
#include "OSGIOFileTypeBase.h"
#include "OSGGeometry.h"

#include "OSGAssimpOptions.h"

#ifdef OSG_WITH_ASSIMP

#include <assimp/vector3.h>
#include <assimp/color4.h>

struct aiScene;
struct aiMesh;

#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

class AssimpMaterialProcessor;

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpMeshProcessor
{
    /*==========================  PUBLIC  =================================*/
public:
    /*---------------------------------------------------------------------*/
    /*! \name Set/Get                                                      */
    /*! \{                                                                 */

    Geometry*  getGeometry      (unsigned int idx) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name examine                                                      */
    /*! \{                                                                 */
#ifdef OSG_WITH_ASSIMP
    bool            process     (const aiScene* scene);
#endif
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  AssimpMeshProcessor(
                    const AssimpOptions&            options,
                    const std::string&              importer,
                    const AssimpMaterialProcessor&  materialProcessor);
             ~AssimpMeshProcessor(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
#ifdef OSG_WITH_ASSIMP
    GeometryTransitPtr  process     (const aiMesh* mesh);

    Pnt3f               toPnt3f     (const aiVector3D& v);
    Vec1f               toVec1f     (const aiVector3D& v);
    Vec2f               toVec2f     (const aiVector3D& v);
    Vec3f               toVec3f     (const aiVector3D& v);
    Color4f             toColor4f   (const aiColor4D&  c);
#endif

private:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef AssimpMeshProcessor      Self;

    typedef std::map<UInt32, GeometryUnrecPtr> GeometryMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

private:
    GeometryMap                     _geometryMap;
    AssimpOptions                   _options;
    std::string                     _importer;
    const AssimpMaterialProcessor&  _materialProcessor;
};

OSG_END_NAMESPACE

#include "OSGAssimpMeshProcessor.inl"

#endif // _OSGASSIMPMESHPROCESSOR_H_
