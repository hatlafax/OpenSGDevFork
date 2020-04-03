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

#ifndef _OSGMATERIALFACTORY_H_
#define _OSGMATERIALFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialFactoryBase.h"
#include "OSGChunkMaterial.h"

OSG_BEGIN_NAMESPACE

class MaterialDesc;

/*! \brief MaterialFactory class. See \ref
           PageContribTechniquesMaterialFactory for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MaterialFactory : public MaterialFactoryBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialFactoryBase Inherited;
    typedef MaterialFactory     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    virtual ChunkMaterialTransitPtr getMaterial   (MaterialDesc*  matDesc) = 0;
    virtual void                    updateMaterial(ChunkMaterial* mat    ) = 0;
    virtual void                    clearShaders  (                      ) = 0;

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

    // Variables should all be in MaterialFactoryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialFactory(void);
    MaterialFactory(const MaterialFactory &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialFactoryBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialFactory &source);
};

typedef MaterialFactory *MaterialFactoryP;

OSG_END_NAMESPACE

#include "OSGMaterialFactoryBase.inl"
#include "OSGMaterialFactory.inl"

#endif /* _OSGMATERIALFACTORY_H_ */
