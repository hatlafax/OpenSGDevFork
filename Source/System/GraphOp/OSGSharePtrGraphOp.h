/*---------------------------------------------------------------------------*\
*                                OpenSG                                     *
*                                                                           *
*                                                                           *
*             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
 
#ifndef _OSGSHAREPTRGRAPHOP_H_
#define _OSGSHAREPTRGRAPHOP_H_

#ifdef __sgi
#   pragma once
#endif

#include <map>
#include <set>
#include <vector>

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"
#include <OSGTime.h>

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! GraphOp class

class OSG_UTIL_DLLMAPPING SharePtrGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "SharePtrGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    SharePtrGraphOp(const char* name = "SharePtr");

    virtual GraphOpTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */
    
    bool traverse(Node *root);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void setParams(const std::string params);
    
    void setIncludes(const std::string &includes);
    void setExcludes(const std::string &excludes);

    std::string usage(void);

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/
protected:    

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SharePtrGraphOp(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:

    virtual Action::ResultE traverseEnter(Node            * const node );
    virtual Action::ResultE traverseLeave(Node            * const node,
                                          Action::ResultE         res  );
    
    FieldContainer *shareFC(FieldContainer *fc);
    
    typedef std::set<UInt32          > FCIdSet;
    typedef FCIdSet::iterator          FCIdSetIt;
    
    typedef std::set<FieldContainer *> FCSet;
    typedef FCSet::iterator            FCSetIt;
    
    typedef std::map<UInt32, FCSet   > FCTypeMap;
    typedef FCTypeMap::iterator        FCTypeMapIt;
    
    typedef std::map<UInt32, UInt32  > ShareCount;
    typedef ShareCount::iterator       ShareCountIt;
    
    FCTypeMap  _typeMap;

    FCIdSet    _includeSet;
    FCIdSet    _excludeSet;

    FCIdSet    _visitedSet;
    
    ShareCount _shareCount;
    Time       _totalTime;
    Time       _compareTime;
};

OSG_END_NAMESPACE

#endif /* _OSGSHAREPTRGRAPHOP_H_ */
