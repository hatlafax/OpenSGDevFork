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

#ifndef _OSGSTRINGTOFIELDCONTAINERMAP_H_
#define _OSGSTRINGTOFIELDCONTAINERMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <algorithm>
#include <functional>
#include <utility>

#include "OSGStringToFieldContainerMapBase.h"
#include "OSGKeyValue.h"

OSG_BEGIN_NAMESPACE

/*! \brief StringToFieldContainerMap class. See \ref
           PageBaseStringToFieldContainerMap for a description.
*/

class OSG_BASE_DLLMAPPING StringToFieldContainerMap : public StringToFieldContainerMapBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StringToFieldContainerMapBase Inherited;
    typedef StringToFieldContainerMap     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                  Map Interface                               */
    /*! \{                                                                 */

    bool                empty   () const;
    bool                insert  (const std::string& key, FieldContainer* value);
    bool                erase   (const std::string& key);
    FieldContainer*     find    (const std::string& key) const;
    FieldContainer*     at      (UInt32 idx) const;
    const std::string&  key     (UInt32 idx) const;
    void                clear   ();
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

    class value_compare : public std::binary_function<KeyValueUnrecPtr, std::string, bool>
    {
    public:
        value_compare() {}
        bool operator()(const KeyValue* lhs, const std::string& rhs) const
        { 
            return lhs->getKey() <  rhs;
        }
    };

    MFUnrecKeyValuePtr::const_iterator  find_   (const std::string& key) const;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StringToFieldContainerMap(void);
    StringToFieldContainerMap(const StringToFieldContainerMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StringToFieldContainerMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class StringToFieldContainerMapBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StringToFieldContainerMap &source);
};

typedef StringToFieldContainerMap *StringToFieldContainerMapP;

OSG_END_NAMESPACE

#include "OSGStringToFieldContainerMapBase.inl"
#include "OSGStringToFieldContainerMap.inl"

#endif /* _OSGSTRINGTOFIELDCONTAINERMAP_H_ */
