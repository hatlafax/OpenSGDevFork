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

#ifndef _OSGMATERIALMANAGER_H_
#define _OSGMATERIALMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/call_traits.hpp>

#include "OSGMaterialManagerBase.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialDesc.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaterialManager class. See \ref
           PageSystemMaterialManager for a description.
*/

class OSG_SYSTEM_DLLMAPPING MaterialManager : public MaterialManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialManagerBase Inherited;
    typedef MaterialManager     Self;

    typedef UInt64                                      KeyType;
    typedef boost::call_traits<KeyType>::param_type     KeyParamType;
    typedef boost::call_traits<KeyType>::value_type     KeyValueType;

    typedef std::vector<KeyType>                        KeyTypeStore;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    typedef std::pair<KeyValueType, ChunkMaterial*> ManagedMaterialT;

    virtual ManagedMaterialT    addMaterial     (MaterialDesc* matDesc ) = 0;
    virtual bool                addMaterial     (KeyParamType key, ChunkMaterial* mat) = 0;
    virtual ManagedMaterialT    updateMaterial  (KeyParamType key) = 0;
    virtual KeyTypeStore        updateMaterials (                ) = 0;
    virtual bool                removeMaterial  (KeyParamType key) = 0;
    virtual ChunkMaterial*      getMaterial     (KeyParamType key) const = 0;
    virtual const MaterialDesc* getMaterialDesc (KeyParamType key) const = 0;
    virtual bool                hasMaterial     (KeyParamType key) const = 0;

    virtual void                clear           () = 0;
    virtual void                recycle         () = 0;

    virtual void                updateProgram   () = 0;

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

    // Variables should all be in MaterialManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialManager(void);
    MaterialManager(const MaterialManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialManager &source);
};

typedef MaterialManager *MaterialManagerP;

OSG_END_NAMESPACE

#include "OSGMaterialManagerBase.inl"
#include "OSGMaterialManager.inl"

#endif /* _OSGMATERIALMANAGER_H_ */
