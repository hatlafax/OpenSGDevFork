/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#ifndef _OSGOSBCUBETEXTURECHUNKELEMENT_H_
#define _OSGOSBCUBETEXTURECHUNKELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"

#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactoryHelper.h"

#include "OSGCubeTextureObjChunkFields.h"
#include "OSGTextureEnvChunkFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBCubeTextureChunkElement : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBCommonElement           Inherited;
    typedef OSBCubeTextureChunkElement Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBCubeTextureChunkElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBCubeTextureChunkElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read    (const std::string &typeName);
    virtual void postRead(      void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

    virtual void preWrite(FieldContainer * const fc);
    virtual void write   (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name State access                                                 */
    /*! \{                                                                 */

    inline CubeTextureObjChunk *getCubeTexObjChunk(void) const;
    inline TextureEnvChunk     *getTexEnvChunk    (void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBCubeTextureChunkElement(const OSBCubeTextureChunkElement &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBCubeTextureChunkElement &source);

    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper Functions                                     */
    /*! \{                                                                 */

    bool isTexObjField(const std::string &fieldName) const;
    bool isTexEnvField(const std::string &fieldName) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static OSBElementRegistrationHelper<OSBCubeTextureChunkElement> _regHelper;
    
    CubeTextureObjChunkUnrecPtr _pCubeTexObj;
    TextureEnvChunkUnrecPtr     _pTexEnv;
};

OSG_END_NAMESPACE

#include "OSGOSBCubeTextureChunkElement.inl"

#endif /* _OSGOSBCUBETEXTURECHUNKELEMENT_H_ */
