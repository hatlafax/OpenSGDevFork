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

#include "OSGFieldContainerUtils.h"
#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGAttachment.h"
#include "OSGAttachmentMapSFields.h"
#include "OSGNameAttachment.h"
#include "OSGNode.h"

#include <boost/bind/bind.hpp>
#include <boost/format.hpp>

#include <ostream>
#include <set>

OSG_BEGIN_NAMESPACE

namespace
{
    // anonymous namespace for implementation details of the container
    // function.

typedef std::set<const FieldContainer *> FCSet;

// forward declarations
bool comparePointerFields(
    GetFieldHandlePtr  lhsField,
    GetFieldHandlePtr  rhsField,
    FCSet             &lhsVisitedSet,
    FCSet             &rhsVisitedSet,
    bool               ignoreAttachments,
    bool               compareIdentity   );

/*! Implementation of \c compareContainerEqual. The two \c FCSet parameters
    keep track of visited fields in each hierarchy to avoid looping.
 */
bool compareContainerEqualImpl(
    const FieldContainer *lhs,
    const FieldContainer *rhs,
          FCSet          &lhsVisitedSet,
          FCSet          &rhsVisitedSet,
          bool            ignoreAttachments,
          bool            compareIdentity   )
{
    // compare pointers
    if(lhs == rhs)
        return true;

    if(lhs == NULL || rhs == NULL)
        return false;

    // different types ?
    if(lhs->getType() != rhs->getType())
        return false;

    UInt32 lhsFCount = lhs->getType().getNumFieldDescs();
    UInt32 rhsFCount = rhs->getType().getNumFieldDescs();

    // different number of (dynamic) fields ?
    if(lhsFCount != rhsFCount)
        return false;

    lhsVisitedSet.insert(lhs);
    rhsVisitedSet.insert(rhs);

    bool returnValue = true;

    for(UInt32 i = 1; i <= lhsFCount && returnValue == true; ++i)
    {
        GetFieldHandlePtr lhsField = lhs->getField(i);
        GetFieldHandlePtr rhsField = rhs->getField(i);

        // valid handles ?
        if(lhsField == NULL || lhsField->isValid() == false ||
           rhsField == NULL || rhsField->isValid() == false   )
            continue;

        if(lhsField->getType() != rhsField->getType())
        {
            returnValue = false;
            continue;
        }

        // skip internal and parent fields
        if(lhsField->isInternal()            == true                      ||
           lhsField->getType   ().getClass() == FieldType::ParentPtrField   )
            continue;

        SFAttachmentPtrMap::GetHandlePtr  lhsAMHandle =
            boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                lhsField);

        if(lhsAMHandle            != NULL && 
           lhsAMHandle->isValid() == true &&
           ignoreAttachments      == true  )
        {
            continue;
        }

        if(compareIdentity == true)
        {
            if(lhsField->equal(rhsField) == false)
                returnValue = false;
        }
        else
        {
            if(lhsField->isPointerField() == true)
            {
                returnValue = comparePointerFields(
                    lhsField,          rhsField,
                    lhsVisitedSet,     rhsVisitedSet,
                    ignoreAttachments, compareIdentity);
            }
            else
            {
                if(lhsField->equal(rhsField) == false)
                    returnValue = false;
            }
        }
    }

    return returnValue;
}

/*! Compares two PointerFields \a lhsField and \a rhsField by recursively
    comparing the pointed-to containers.
    This function is only used in \c compareContainer below.
 */
bool comparePointerFields(
    GetFieldHandlePtr  lhsField,
    GetFieldHandlePtr  rhsField,
    FCSet             &lhsVisitedSet,
    FCSet             &rhsVisitedSet,
    bool               ignoreAttachments,
    bool               compareIdentity   )
{
    bool returnValue = true;

    if(lhsField->getCardinality() == FieldType::SingleField)
    {
        FieldContainerPtrSFieldBase::GetHandlePtr lhsSFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(lhsField);
        FieldContainerPtrSFieldBase::GetHandlePtr rhsSFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(rhsField);

        if(lhsSFHandle != NULL && lhsSFHandle->isValid() &&
           rhsSFHandle != NULL && rhsSFHandle->isValid()   )
        {
            if(lhsVisitedSet.count(lhsSFHandle->get()) == 0 ||
               rhsVisitedSet.count(rhsSFHandle->get()) == 0   )
            {
                returnValue = compareContainerEqualImpl(
                    lhsSFHandle->get(), rhsSFHandle->get(),
                    lhsVisitedSet,      rhsVisitedSet,
                    ignoreAttachments,  compareIdentity     );
            }
        }
        else
        {
            SFAttachmentPtrMap::GetHandlePtr  lhsAMHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                    lhsField);
            SFAttachmentPtrMap::GetHandlePtr  rhsAMHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                    rhsField);

            if(lhsAMHandle != NULL && lhsAMHandle->isValid() &&
               rhsAMHandle != NULL && rhsAMHandle->isValid()   )
            {
                const AttachmentMap &lhsAM = (*lhsAMHandle)->getValue();
                const AttachmentMap &rhsAM = (*rhsAMHandle)->getValue();

                // skip attachments, if the option is set
                if(ignoreAttachments)
                {
                    returnValue = true;
                }
                else if(lhsAM.size() != rhsAM.size())
                {
                    returnValue = false;
                }
                else
                {
                    AttachmentMap::const_iterator lhsAMIt  = lhsAM.begin();
                    AttachmentMap::const_iterator lhsAMEnd = lhsAM.end  ();

                    AttachmentMap::const_iterator rhsAMIt  = rhsAM.begin();

                    for(; lhsAMIt != lhsAMEnd && returnValue == true;
                        ++lhsAMIt, ++rhsAMIt)
                    {
                        if(lhsVisitedSet.count(lhsAMIt->second) == 0 ||
                           rhsVisitedSet.count(rhsAMIt->second) == 0   )
                        {
                            returnValue = compareContainerEqualImpl(
                                lhsAMIt->second,   rhsAMIt->second,
                                lhsVisitedSet,     rhsVisitedSet,
                                ignoreAttachments, compareIdentity );
                        }
                    }
                }
            }
        }
    }
    else
    {
        FieldContainerPtrMFieldBase::GetHandlePtr lhsMFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(lhsField);
        FieldContainerPtrMFieldBase::GetHandlePtr rhsMFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(rhsField);

        if(lhsMFHandle != NULL && lhsMFHandle->isValid() &&
                rhsMFHandle != NULL && rhsMFHandle->isValid()   )
        {
            if(lhsMFHandle->size() != rhsMFHandle->size())
            {
                returnValue = false;
            }
            else
            {
                for(UInt32 i = 0; i           <  lhsMFHandle->size() &&
                                  returnValue == true;                  ++i)
                {
                    if(lhsVisitedSet.count(lhsMFHandle->get(i)) == 0 ||
                       rhsVisitedSet.count(rhsMFHandle->get(i)) == 0   )
                    {
                        returnValue = compareContainerEqualImpl(
                            lhsMFHandle->get(i), rhsMFHandle->get(i),
                            lhsVisitedSet,       rhsVisitedSet,
                            ignoreAttachments,   compareIdentity     );
                    }
                }
            }
        }
    }

    return returnValue;
}

/*! \nohierarchy
 */


struct FieldPathEntry
{
    std::string szName;
    Int32       iIndex;

    FieldPathEntry(void) : szName(), iIndex(0) {}
};

void splitFieldPath(      std::vector<FieldPathEntry> &vSplitPath,
                    const Char8                       *szFieldPath)
{
    std::string tmpName(szFieldPath);

    std::string::size_type sStart    = 0;
    std::string::size_type sEnd      = 0;
    std::string::size_type sLength   = 0;
    std::string::size_type sLastChar = 0;
    FieldPathEntry         tmpEntry;

    std::string            szIdx;

    do
    {
        sEnd = tmpName.find("/", sStart);

        if(sEnd != std::string::npos)
        {
            sLength = sEnd - sStart;
        }
        else
        {
            sLength = tmpName.length() - sStart;
        }
 
        sLastChar = sStart + sLength - 1;

        vSplitPath.push_back(tmpEntry);

        vSplitPath.back().iIndex = -1;

        if(tmpName[sLastChar] == ')')
        {
            std::string::size_type sIdxStart = 
                tmpName.rfind('(', sLastChar); //, sLength);

            if(sIdxStart == std::string::npos)
            {
                vSplitPath.clear();

                return;
            }

            tmpName[sIdxStart] = '$';
            tmpName[sLastChar] = '$';

            sLength -= sLastChar - sIdxStart + 1;

            ++sIdxStart;

            szIdx.assign(tmpName,
                         sIdxStart,
                         sLastChar - sIdxStart);

            vSplitPath.back().iIndex = 
                TypeTraits<UInt32>::getFromCString(szIdx.c_str());
        }

        vSplitPath.back().szName.assign(tmpName, sStart, sLength);

        sStart = sEnd + 1;
    }
    while(sEnd != std::string::npos);
}

FieldContainer *resolveFieldPath(std::vector<FieldPathEntry> &vSplitPath, 
                                 FieldContainer              *pRoot     )
{
    if(pRoot == NULL)
        return NULL;

    FieldContainer *returnValue = pRoot;

    OSG::GetFieldHandlePtr fHandle;

    for(UInt32 i = 1; i < vSplitPath.size(); ++i)
    {
        fHandle = returnValue->getField(vSplitPath[i].szName.c_str());

        if(fHandle == NULL || fHandle->isValid() == false) 
        {
            FWARNING(("Unknown field '%s'\n", 
                      vSplitPath[i].szName.c_str()));

            returnValue = NULL;

            break;
        }

        OSG::FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
            boost::dynamic_pointer_cast<
              OSG::FieldContainerPtrSFieldBase::GetHandle>(fHandle);
            
        OSG::FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
            boost::dynamic_pointer_cast<
                OSG::FieldContainerPtrMFieldBase::GetHandle>(fHandle);

        if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
        {
            returnValue = (*sfFCPtr)->getValue();
        }
        else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
        {
            UInt32 uiIndex = 
                vSplitPath[i].iIndex == -1 ? 0 : vSplitPath[i].iIndex;

            if(uiIndex >= mfFCPtr->size())
            {
                FWARNING(("Unknown index %d to large for field '%s'\n", 
                          uiIndex,
                          vSplitPath[i].szName.c_str()));
                
                returnValue = NULL;
                
                break;
            }

            returnValue = (**mfFCPtr)[uiIndex];
        }
    }

    return returnValue;
}

FieldContainer *resolveFieldPathImpl(const Char8             *szNodeName, 
                                           ContainerResolver  oResolver )
{
    std::vector<FieldPathEntry> vSplitPath;

    splitFieldPath(vSplitPath, szNodeName);

    if(vSplitPath.size() == 0)
        return NULL;

    FieldContainer *returnValue = oResolver(vSplitPath[0].szName.c_str());

    returnValue = resolveFieldPath(vSplitPath, returnValue);

    return returnValue;
}



struct ContainerVisitRecord
{
    typedef std::vector<UInt32>::iterator VisitedIt;

    std::vector<UInt32> vVisitedIds;

    bool visit(UInt32 uiContainerId);

    ContainerVisitRecord(void) : vVisitedIds() {}
};

bool ContainerVisitRecord::visit(UInt32 uiContainerId)
{
    VisitedIt vIt = std::lower_bound(vVisitedIds.begin(),
                                     vVisitedIds.end  (),
                                     uiContainerId      );

    if(vIt != vVisitedIds.end())
    {
        if(*vIt == uiContainerId)
            return false;
     
        vVisitedIds.insert(vIt, uiContainerId);
    }
    else
    {
        vVisitedIds.push_back(uiContainerId);
    }

    return true;
}

FieldContainer *findNamedComponentImpl(      ContainerVisitRecord &oVisited,
                                             FieldContainer       *pCnt,
                                       const Char8                *szName  )
{
    if(pCnt == NULL)
        return NULL;

    const Char8 *szTmpName = NULL;

    const AttachmentContainer *pAC = 
        dynamic_cast<const AttachmentContainer *>(pCnt);

#if 0
    fprintf(stderr, "findNamedComponent::visit %p type %s\n",
            pCnt,
            pCnt->getType().getCName());
#endif            

    szTmpName = OSG::getName(pAC);
        
    if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
    {
        return pCnt;
    }
    
    if(oVisited.visit(pCnt->getId()) == false)
    {
        return NULL;
    }

    const Node *pNode = dynamic_cast<const Node *>(pCnt);

    if(pNode != NULL)
    {
        if(0x0000 == (pNode->getTravMask() & 
                      TraversalMasks::FindNamedComponentTraversal))
        {
            return NULL;
        }
    }

    BitVector bvExcludedFields = TypeTraits<BitVector>::BitsSet;

    const ControlFindNamedElemInterface *pCFNInterface =
        dynamic_cast<ControlFindNamedElemInterface *>(pCnt);

    if(pCFNInterface != NULL)
    {
        bvExcludedFields = pCFNInterface->excludeFields();
    }

    const FieldContainerType &fcType = pCnt->getType();
          UInt32              fCount = fcType.getNumFieldDescs();

    for(UInt32 i = 1; i <= fCount; ++i)
    {
        const FieldDescriptionBase *fDesc = fcType.getFieldDesc(i);

        if(fDesc->getFieldType().getClass() == FieldType::ParentPtrField)
            continue;

        if(0x0000 == (bvExcludedFields & fDesc->getFieldMask()))
            continue;

        GetFieldHandlePtr srcField = pCnt->getField(i);

        FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
            boost::dynamic_pointer_cast<
                      FieldContainerPtrSFieldBase::GetHandle>(srcField);

        FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
            boost::dynamic_pointer_cast<
                      FieldContainerPtrMFieldBase::GetHandle>(srcField);

        if(  sfFCPtr              != NULL && 
             sfFCPtr->isValid()   == true && 
           (*sfFCPtr)->getValue() != NULL   )
        {
            FieldContainer *rc = findNamedComponentImpl(oVisited, 
                                                        (*sfFCPtr)->getValue(),
                                                        szName                );
            if(rc != NULL)
                return rc;
        }
        else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
        {
            SizeT mfSize = (*mfFCPtr)->size();
            
            for(SizeT j = 0; j < mfSize; j++)
            {
                if((**mfFCPtr)[j] != NULL)
                {
                    FieldContainer *rc = findNamedComponentImpl(oVisited,
                                                                (**mfFCPtr)[j],
                                                                szName);

                    if(rc != NULL)
                        return rc;
                }
            }
        }
    }

    return NULL;
}

FieldContainer *findNamedComponentImpl(      FieldContainer *pCnt,
                                       const Char8          *szName)
{
    ContainerVisitRecord oVisited;

    return findNamedComponentImpl(oVisited, pCnt, szName);
}

} // namespace

/*! Compares two FieldContainer \a lhs and \a rhs for equivalence. The meaning
    of this comparison can be tweaked with the additional arguments.
    If \a ignoreAttachments is \c true, Attachments are excluded from the
    comparison.
    If \a compareIdentity is \c true, pointers are compared by
    address otherwise the pointed-to objects are compared for equivalence.
 */
bool compareContainerEqual(
    const FieldContainer *lhs,
    const FieldContainer *rhs,
          bool            ignoreAttachments,
          bool            compareIdentity   )
{
    FCSet lhsVisitedSet;
    FCSet rhsVisitedSet;

    return compareContainerEqualImpl(
        lhs, rhs, lhsVisitedSet, rhsVisitedSet,
        ignoreAttachments, compareIdentity     );
}

//---------------------------------------------------------------------------
//  MemoryConsumption
//---------------------------------------------------------------------------

void MemoryConsumption::scan(void)
{
    FieldContainerFactory::the()->lockStore();

    FieldContainerFactoryBase::ContainerStoreConstIt sIt  =
        FieldContainerFactory::the()->beginStore();
    FieldContainerFactoryBase::ContainerStoreConstIt sEnd =
        FieldContainerFactory::the()->endStore();

    for(; sIt != sEnd; ++sIt)
    {
        FieldContainer *pFC = (*sIt).second->getPtr();

        if(pFC == NULL)
            continue;

        TypeMemMapIt tmIt    = _memMap.find(pFC->getType().getId());
        SizeT        binSize = pFC->getBinSize(TypeTraits<BitVector>::BitsSet);

        if(tmIt != _memMap.end())
        {
            tmIt->second.first  += binSize;
            tmIt->second.second += 1;
        }
        else
        {
            _memMap[pFC->getType().getId()] = MemCountPair(binSize, 1);
        }
    }

    FieldContainerFactory::the()->unlockStore();
}


void MemoryConsumption::print(std::ostream &os, bool ignoreProto) const
{
    TypeMemMapConstIt tmIt  = _memMap.begin();
    TypeMemMapConstIt tmEnd = _memMap.end  ();

    SizeT         totalMem   = 0;
    UInt32        totalCount = 0;
    boost::format formatter("%|1$-25| [%|2$8|] Byte [%|3$8.0f|] kByte [%|4$4|]\n");

    for(; tmIt != tmEnd; ++tmIt)
    {
        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(tmIt->first);

        if(fcType == NULL)
            continue;

        if(ignoreProto && tmIt->second.second == 1)
            continue;

        os << formatter % fcType->getCName()
                        % tmIt->second.first
                        % (tmIt->second.first / 1024.f)
                        % tmIt->second.second;

        totalMem   += tmIt->second.first;
        totalCount += tmIt->second.second;
    }

    os << "--------------------------------------------\n";
    os << formatter % "Total"
                    % totalMem
                    % (totalMem / 1024.f)
                    % totalCount;
}

void MemoryConsumption::print_sorted(std::ostream &os, bool ignoreProto, bool sort_by_name) const
{
    std::size_t maxNameLength = 0;

    typedef std::vector<TypeMemMapConstIt> IteratorStorage;

    IteratorStorage iterStore;
    
    typedef std::map<std::string,      TypeMemMapConstIt> NameToIteratorMapT;
    typedef std::multimap<std::size_t, TypeMemMapConstIt> SizeToIteratorMapT;

    NameToIteratorMapT sorterByName;
    SizeToIteratorMapT sorterBySize;

    TypeMemMapConstIt tmIt  = _memMap.begin();
    TypeMemMapConstIt tmEnd = _memMap.end  ();

    for(; tmIt != tmEnd; ++tmIt)
    {
        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(tmIt->first);

        if(fcType == NULL)
            continue;

        if(ignoreProto && tmIt->second.second == 1)
            continue;

        maxNameLength = std::max(fcType->getName().size(), maxNameLength);

        if (sort_by_name)
        {
            sorterByName.insert(NameToIteratorMapT::value_type(fcType->getName(), tmIt));
        }
        else
        {
            sorterBySize.insert(SizeToIteratorMapT::value_type(tmIt->second.first, tmIt));
        }
    }

    if (sort_by_name)
    {
        NameToIteratorMapT::const_iterator mapIt  = sorterByName.begin();
        NameToIteratorMapT::const_iterator mapEnd = sorterByName.end  ();

        for (; mapIt != mapEnd; ++mapIt)
            iterStore.push_back(mapIt->second);
    }
    else
    {
        SizeToIteratorMapT::const_iterator mapIt  = sorterBySize.begin();
        SizeToIteratorMapT::const_iterator mapEnd = sorterBySize.end  ();

        for (; mapIt != mapEnd; ++mapIt)
            iterStore.push_back(mapIt->second);
    }

    std::stringstream format;
    format << "%|1$-" << maxNameLength << "| [%|2$10|] Byte [%|3$8.0f|] kByte [%|4$5|]\n";

    IteratorStorage::const_iterator iter = iterStore.begin();
    IteratorStorage::const_iterator end  = iterStore.end  ();

    SizeT         totalMem   = 0;
    UInt32        totalCount = 0;
    boost::format formatter(format.str());

    for(; iter != end; ++iter)
    {
        TypeMemMapConstIt tmIt = *iter;

        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(tmIt->first);

        if(fcType == NULL)
            continue;

        if(ignoreProto && tmIt->second.second == 1)
            continue;

        os << formatter % fcType->getCName()
                        % tmIt->second.first
                        % (tmIt->second.first / 1024.f)
                        % tmIt->second.second;

        totalMem   += tmIt->second.first;
        totalCount += tmIt->second.second;
    }

    os << "--------------------------------------------\n";
    os << formatter % "Total"
                    % totalMem
                    % (totalMem / 1024.f)
                    % totalCount;
}

MemoryConsumption::TypeMemMapConstIt MemoryConsumption::beginMap(void) const
{
    return _memMap.begin();
}

MemoryConsumption::TypeMemMapConstIt MemoryConsumption::endMap(void) const
{
    return _memMap.end();
}

ControlFindNamedElemInterface::ControlFindNamedElemInterface(void)
{
}

ControlFindNamedElemInterface::~ControlFindNamedElemInterface(void)
{
}


FieldContainer *resolveFieldPath(const Char8             *szNodeName, 
                                       ContainerResolver  oResolver )
{
    return resolveFieldPathImpl(szNodeName, oResolver);
}

FieldContainer *findNamedComponent(      FieldContainer *pCnt,
                                   const Char8          *szName)
{
    return findNamedComponentImpl(pCnt, szName);
}



FieldContainer *getFieldContainer(const std::string &szTypeName, 
                                  const std::string &szName)
{
    return getFieldContainer(
        FieldContainerFactory::the()->findType(szTypeName.c_str()), szName);
}

FieldContainer *getFieldContainer(const FieldContainerType *pType, 
                                  const std::string        &szName)
{
    if(pType == NULL)
    {
        SWARNING << "getFieldContainer(): The Field type is not defined."
                 << std::endl;

        return NULL;
    }

    const FieldContainerFactoryBase::ContainerStore &oFCStore(
        FieldContainerFactory::the()->getFieldContainerStore());

    FieldContainerFactoryBase::ContainerStore::const_iterator fcStoreIt =
        oFCStore.begin();

    FieldContainerFactoryBase::ContainerPtr                   pCont     = NULL;

    for(; fcStoreIt != oFCStore.end() ; ++fcStoreIt)
    {
#ifdef OSG_MT_CPTR_ASPECT
        pCont = (*fcStoreIt).second->getPtr();
#else
        pCont =  *fcStoreIt .second;
#endif

        if(pCont != NULL && pCont->getType() == (*pType))
        {
            const Char8 *szCntName = 
                getName(dynamic_cast<AttachmentContainer *>(pCont));

            if(szCntName != NULL && szName.compare(szCntName) == 0)
            {
                return pCont;
            }
        }
    }

    return NULL;
}


FieldContainer *getFieldContainer(const std::string &szName)
{
    const FieldContainerFactoryBase::ContainerStore &oFCStore =
        FieldContainerFactory::the()->getFieldContainerStore();

   FieldContainerFactoryBase::ContainerStore::const_iterator fcStoreIt = 
                  oFCStore.begin();

   FieldContainerFactoryBase::ContainerPtr                   pCont     = NULL;

   for(; fcStoreIt != oFCStore.end() ; ++fcStoreIt)
   {
       if((*fcStoreIt).second == NULL)
       {
           continue;
       }

#ifdef OSG_MT_CPTR_ASPECT
       pCont = (*fcStoreIt).second->getPtr();
#else
       pCont =  *fcStoreIt .second;
#endif
       const Char8 *szCntName =
           getName(dynamic_cast<AttachmentContainer *>(pCont));

       if(szCntName != NULL && szName.compare(szCntName) == 0)
       {
           return pCont;
       }
   }

   return NULL;
}


bool isFieldContentDerivedFrom(const FieldType          &oFieldType, 
                               const FieldContainerType *pFCType)
{
    if(oFieldType.isPtrField())
    {
        std::string szFieldPtrTypeName(oFieldType.getContentType().getName());

        switch(oFieldType.getClass())
        {
            case FieldType::PtrField:
            case FieldType::ParentPtrField:
            case FieldType::ChildPtrField:
                szFieldPtrTypeName = szFieldPtrTypeName.substr(
                    0,
                    szFieldPtrTypeName.size() - 3);
                break;
            default:
            case FieldType::ValueField:
                return false;
                break;
        }

        const FieldContainerType *pPtrContentType = 
            FieldContainerFactory::the()->findType(szFieldPtrTypeName.c_str());
        
        return pFCType->isDerivedFrom(*pPtrContentType);
    }
    else
    {
        return false;
    }

    return false;
}

const FieldContainerType *getFieldContainerTypeFromPtrType(
    const DataType &oType)
{
    std::string szFCPtrTypeName = 
        oType.getName().substr(0, oType.getName().size() - 3);

    return FieldContainerFactory::the()->findType(szFCPtrTypeName.c_str());
}



const FieldContainerType *getClosestAncestor(
    const FieldContainerType                       *pType,
          MFUnrecFieldContainerPtr::const_iterator  begin,
          MFUnrecFieldContainerPtr::const_iterator  end)
{
    if(pType == NULL)
    {
        return NULL;
    }

    const FieldContainerType *pAncestorType = NULL;
    const FieldContainerType *pFCType       = NULL;

    MFUnrecFieldContainerPtr::const_iterator it = begin;

    for(; it != end ; ++it)
    {
        pFCType = &((*it)->getType());

        if(pType->isDerivedFrom(*pFCType) &&
           (pAncestorType == NULL || pFCType->isDerivedFrom(*pAncestorType)))
        {
            pAncestorType = pFCType;
        }
    }

    return pAncestorType;
}

std::vector<FieldContainer *> getAllContainersByDerivedType(
    const FieldContainerType *pType)
{
    std::vector<FieldContainer *> vResult;

    const FieldContainerFactoryBase::ContainerStore &oFCStore = 
        FieldContainerFactory::the()->getFieldContainerStore();

    FieldContainerFactoryBase::ContainerStore::const_iterator fcStoreIt = 
        oFCStore.begin();

    FieldContainerFactoryBase::ContainerPtr                   pCont     =
        NULL;

    for(;fcStoreIt != oFCStore.end() ; ++fcStoreIt)
    {
        if((*fcStoreIt).second != NULL)
        {
#ifdef OSG_MT_CPTR_ASPECT
            pCont = (*fcStoreIt).second->getPtr();
#else
            pCont =  *fcStoreIt .second;
#endif
        }
        else
        {
            pCont = NULL;
        }
        if(pCont != NULL && pCont->getType().isDerivedFrom(*pType))
        {
            vResult.push_back(pCont);
        }
    }

    return vResult;
}

#if 0
std::vector<FieldContainerPtr> getAllContainersByType(const FieldContainerType *szType)
{
    std::vector<FieldContainerPtr> Result;

    const std::vector<FieldContainerPtr>* FCStore(    FieldContainerFactory::the()->getFieldContainerStore () );

    std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
    for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
    {
        if( (*FCStoreIter) != NullFC && (*FCStoreIter)->getType() == (*szType) )
        {
            Result.push_back(*FCStoreIter);
        }
    }
    
    return Result;
}


std::vector<FieldContainerPtr> getAllFieldContainers(const std::string &namestring)
{
    std::vector<FieldContainerPtr> Result;
    std::vector<FieldContainerPtr>::const_iterator FCStoreIter;

    const std::vector<FieldContainerPtr>* FCStore(    FieldContainerFactory::the()->getFieldContainerStore () );

    for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
    {
        const Char8 *Name( getName(AttachmentContainerPtr::dcast(*FCStoreIter)) );
        if(Name != NULL && namestring.compare(Name) == 0)
        {
            //Result.push_back(*FCStoreIter);
        }
    }
    return Result;
}

#endif

OSG_END_NAMESPACE
