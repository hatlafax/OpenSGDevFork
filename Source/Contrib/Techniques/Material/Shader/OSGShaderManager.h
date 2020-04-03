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

#ifndef _OSGSHADERMANAGER_H_
#define _OSGSHADERMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderManagerBase.h"
#include "OSGShaderProgramChunk.h"
#include "OSGHashKeyToFieldContainerMap.h"

OSG_BEGIN_NAMESPACE

class ChunkMaterial;
class MaterialDesc;

/*! \brief ShaderManager class. See \ref
           PageContribTechniquesShaderManager for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ShaderManager : public ShaderManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderManagerBase Inherited;
    typedef ShaderManager     Self;

    typedef UInt64                                      KeyType;
    typedef boost::call_traits<KeyType>::param_type     KeyParamType;
    typedef boost::call_traits<KeyType>::value_type     KeyValueType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    virtual ShaderProgramChunk* getShaderProgramChunk
                                    (
                                        ChunkMaterial* chunkMat
                                    );

    virtual void                clearShaderProgramChunks();

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

    // Variables should all be in ShaderManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderManager(void);
    ShaderManager(const ShaderManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    void onCreate      (const ShaderManager *source      = NULL);
    void onCreateAspect(const ShaderManager *createAspect,
                        const ShaderManager *source      = NULL);
    void onDestroy(           UInt32         uiId              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 ProgramChunkMap                              */
    /*! \{                                                                 */

    ShaderProgramChunk* getShaderProgramChunk(KeyParamType key) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderManager &source);
};

typedef ShaderManager *ShaderManagerP;

OSG_END_NAMESPACE

#include "OSGShaderManagerBase.inl"
#include "OSGShaderManager.inl"

#endif /* _OSGSHADERMANAGER_H_ */
