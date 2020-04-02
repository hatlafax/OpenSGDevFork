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

#ifndef _OSGASSIMPEXAMINER_H_
#define _OSGASSIMPEXAMINER_H_

/*! \file OSGAssimpExaminer.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"
#include "OSGIOFileTypeBase.h"

#include "OSGAssimpOptions.h"

#ifdef OSG_WITH_ASSIMP

#include <assimp/vector3.h>
#include <assimp/color4.h>

struct aiScene;
struct aiMesh;
struct aiFace;
struct aiBone;
struct aiAnimMesh;
struct aiMaterial;
struct aiAnimation;
struct aiCamera;
struct aiLight;
struct aiTexture;
struct aiNode;
struct aiNodeAnim;
struct aiMeshAnim;
struct aiMeshMorphAnim;
struct aiMetadata;
enum aiTextureType;
#endif

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpExaminer
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef AssimpExaminer      Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Set/Get                                                      */
    /*! \{                                                                 */

    void                setFilename (const std::string& filename);
    const std::string&  getFilename () const;

    void                setLog      (const std::string& log);
    const std::string&  getLog      () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name examine                                                      */
    /*! \{                                                                 */
#ifdef OSG_WITH_ASSIMP
    bool                examine(const aiScene* scene);
#endif
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  AssimpExaminer(const AssimpOptions&  options, 
                             const std::string&    importer);
             ~AssimpExaminer(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
#ifdef OSG_WITH_ASSIMP
    void        doExamine       (const aiScene*         scene,         std::ofstream& os);
    void        doExamine       (const aiMesh*          mesh,          std::ofstream& os);
    void        doExamine       (const aiFace*          face,          std::ofstream& os);
    void        doExamine       (const aiBone*          bone,          std::ofstream& os);
    void        doExamine       (const aiAnimMesh*      mesh,          std::ofstream& os);
    void        doExamine       (const aiMaterial*      mat,           std::ofstream& os);
    void        doExamine       (const aiAnimation*     animation,     std::ofstream& os);
    void        doExamine       (const aiCamera*        camera,        std::ofstream& os);
    void        doExamine       (const aiLight*         light,         std::ofstream& os);
    void        doExamine       (const aiTexture*       texture,       std::ofstream& os);
    void        doExamine       (const aiNode*          node,          std::ofstream& os);
    void        doExamine       (const aiNodeAnim*      nodeAnim,      std::ofstream& os);
    void        doExamine       (const aiMeshAnim*      meshAnim,      std::ofstream& os);
    void        doExamine       (const aiMeshMorphAnim* meshMorphAnim, std::ofstream& os);
    void        doExamine       (const aiMetadata*      metadata,      std::ofstream& os);

    void        doExamine       (const aiMaterial*  mat, aiTextureType type, std::ofstream& os);

    void        doExamine       (const char* kind, const char* name, const aiVector3D* vec, unsigned int num, std::ofstream& os);
    void        doExamine       (const char* kind, const char* name, const aiColor4D*  col, unsigned int num, std::ofstream& os);
#endif

  private:
    AssimpOptions               _options;
    std::string                 _importer;
    std::string                 _filename;
    std::string                 _log;
    std::stack<std::string>     _spaces;
};

OSG_END_NAMESPACE

#include "OSGAssimpExaminer.inl"

#endif // _OSGASSIMPEXAMINER_H_
