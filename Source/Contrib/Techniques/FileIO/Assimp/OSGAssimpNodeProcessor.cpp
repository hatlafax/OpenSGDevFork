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

#include <fstream>

#include "OSGBaseTypes.h"

#include "OSGAssimpNodeProcessor.h"
#include "OSGAssimpMeshProcessor.h"
#include "OSGAssimpLog.h"

#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGSceneFileHandler.h"
#include "OSGTransform.h"

#ifdef OSG_WITH_ASSIMP
#pragma warning( push )
#pragma warning(disable : 4800)

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/anim.h>
#include <assimp/metadata.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <assimp/postprocess.h>

#pragma warning( pop )
#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

AssimpNodeProcessor::AssimpNodeProcessor(
    const AssimpOptions&       options,
    const std::string&         importer,
    const AssimpMeshProcessor& meshProcessor)
: _root(NULL)
, _options(options)
, _importer(importer)
, _meshProcessor(meshProcessor)
{
}

AssimpNodeProcessor::~AssimpNodeProcessor(void)
{
}

#ifdef OSG_WITH_ASSIMP
bool AssimpNodeProcessor::process(const aiScene* scene)
{
    OSG_ASSERT(scene && (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == 0 && scene->mRootNode);

    //
    // End result: The complete model scene graph
    //

    _root = process(scene->mRootNode, NULL);

    return true;
}

NodeTransitPtr AssimpNodeProcessor::process(const aiNode* node, Node* parent)
{
    if (!node)
        return NodeTransitPtr(NULL);

    UInt32 numMeshes      = node->mNumMeshes;
    UInt32 numChildren    = node->mNumChildren;
    bool   isIdentity     = node->mTransformation.IsIdentity();

    NodeUnrecPtr root = NULL;

    bool merged_to_parent = false;

    if (parent == NULL)
    {
        bool transfOnImport = _options.getTransformYToZOnImport();

        root = Node::createLocal();

        if (isIdentity && !transfOnImport)
        {
            root->setCore(Group::create());
        }
        else if (isIdentity && transfOnImport)
        {
            Quaternion q(Vec3f(0.f, 1.f, 0.f), Vec3f(0.f, 0.f, 1.f));
            Matrix rotYToZ; rotYToZ.setRotate(q);

            TransformUnrecPtr trafo = Transform::createLocal();
            trafo->setMatrix(rotYToZ);

            root->setCore(trafo);
        }
        else
        {
            Matrix mat = toMatrix(node->mTransformation);

            Quaternion q(Vec3f(0.f, 1.f, 0.f), Vec3f(0.f, 0.f, 1.f));
            Matrix rotYToZ; rotYToZ.setRotate(q);

            mat.multLeft(rotYToZ);

            TransformUnrecPtr trafo = Transform::createLocal();
            trafo->setMatrix(mat);

            root->setCore(trafo);
        }
    }
    else
    {
        if (isIdentity)
        {
            root = parent;
            merged_to_parent = true;
        }
        else
        {
            root = Node::createLocal();

            Matrix mat = toMatrix(node->mTransformation);

            TransformUnrecPtr trafo = Transform::createLocal();
            trafo->setMatrix(mat);

            root->setCore(trafo);
        }
    }

    for (UInt32 i = 0; i < numChildren; ++i)
    {
        aiNode* child = node->mChildren[i];
        process(child, root);
    }

    for (UInt32 i = 0; i < numMeshes; ++i)
    {
        UInt32 meshIdx = node->mMeshes[i];
        Geometry* geo = _meshProcessor.getGeometry(meshIdx);
        if (geo)
        {
            NodeUnrecPtr geoNode = Node::createLocal();
            geoNode->setCore(geo);
            root->addChild(geoNode);
        }
    }

    if (parent == NULL)
    {
        return NodeTransitPtr(root);
    }
    else
    {
        if (!merged_to_parent)
        {
            parent->addChild(root);
        }
        return NodeTransitPtr(NULL);
    }
}

inline Matrix AssimpNodeProcessor::toMatrix(const aiMatrix4x4& m)
{
    return Matrix(m.a1, m.a2, m.a3, m.a4,
                  m.b1, m.b2, m.b3, m.b4,
                  m.c1, m.c2, m.c3, m.c4,
                  m.d1, m.d2, m.d3, m.d4);
}

#endif // OSG_WITH_ASSIMP

OSG_END_NAMESPACE
