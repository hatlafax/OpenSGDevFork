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

#ifndef _OSGHASHKEYTOFIELDCONTAINERMAP_H_
#define _OSGHASHKEYTOFIELDCONTAINERMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <algorithm>
#include <functional>
#include <utility>

#include "OSGHashKeyToFieldContainerMapBase.h"
#include "OSGHashKeyValue.h"

OSG_BEGIN_NAMESPACE

/*! \brief HashKeyToFieldContainerMap class. See \ref
           PageBaseHashKeyToFieldContainerMap for a description.
*/

class OSG_BASE_DLLMAPPING HashKeyToFieldContainerMap : public HashKeyToFieldContainerMapBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HashKeyToFieldContainerMapBase Inherited;
    typedef HashKeyToFieldContainerMap     Self;

    typedef UInt64                         HashKeyType;

    /*---------------------------------------------------------------------*/
    /*! \name                  Map Interface                               */
    /*! \{                                                                 */

    bool                empty   () const;
    bool                insert  (HashKeyType key, FieldContainer* value);
    bool                erase   (HashKeyType key);
    FieldContainer*     find    (HashKeyType key) const;
    FieldContainer*     at      (UInt32 idx) const;
    HashKeyType         key     (UInt32 idx) const;
    void                clear   ();
    void                recycle ();
    UInt32              size    () const;

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

    class value_compare
    {
    public:
        value_compare() {}
        bool operator()(const HashKeyValue* lhs, HashKeyType rhs) const
        { 
            return lhs->getKey() <  rhs;
        }
    };

    MFUnrecHashKeyValuePtr::const_iterator  find_(HashKeyType key) const;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HashKeyToFieldContainerMap(void);
    HashKeyToFieldContainerMap(const HashKeyToFieldContainerMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HashKeyToFieldContainerMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HashKeyToFieldContainerMapBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HashKeyToFieldContainerMap &source);
};

typedef HashKeyToFieldContainerMap *HashKeyToFieldContainerMapP;

OSG_END_NAMESPACE

#include "OSGHashKeyToFieldContainerMapBase.inl"
#include "OSGHashKeyToFieldContainerMap.inl"

#endif /* _OSGHASHKEYTOFIELDCONTAINERMAP_H_ */
