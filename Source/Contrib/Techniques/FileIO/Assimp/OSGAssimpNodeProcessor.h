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

#ifndef _OSGASSIMPNODEPROCESSOR_H_
#define _OSGASSIMPNODEPROCESSOR_H_

/*! \file OSGAssimpNodeProcessor.h
    \ingroup GrpLoader
 */

#include <map>

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"
#include "OSGIOFileTypeBase.h"
#include "OSGNode.h"

#include "OSGAssimpOptions.h"

#ifdef OSG_WITH_ASSIMP

#include <assimp/matrix4x4.h>

struct aiScene;
struct aiNode;

#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

class AssimpMeshProcessor;

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpNodeProcessor
{
    /*==========================  PUBLIC  =================================*/
public:
    /*---------------------------------------------------------------------*/
    /*! \name Set/Get                                                      */
    /*! \{                                                                 */

    Node*       getRoot         () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name examine                                                      */
    /*! \{                                                                 */
#ifdef OSG_WITH_ASSIMP
    bool        process         (const aiScene* scene);
#endif
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  AssimpNodeProcessor(
                    const AssimpOptions&       options,
                    const std::string&         importer,
                    const AssimpMeshProcessor& meshProcessor);
             ~AssimpNodeProcessor(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
#ifdef OSG_WITH_ASSIMP
    NodeTransitPtr      process     (const aiNode* node, Node* parent);


    Matrix              toMatrix    (const aiMatrix4x4& m);
#endif

private:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef AssimpNodeProcessor      Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

private:
    AssimpOptions               _options;
    std::string                 _importer;
    const AssimpMeshProcessor&  _meshProcessor;
    NodeUnrecPtr                _root;
};

OSG_END_NAMESPACE

#include "OSGAssimpNodeProcessor.inl"

#endif // _OSGASSIMPNODEPROCESSOR_H_
