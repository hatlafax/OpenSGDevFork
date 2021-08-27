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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGOSGLoader.h"
#include "OSGLog.h"


#include "OSGSysSFields.h"
#include "OSGSysMFields.h"

#include "OSGBaseSFields.h"
#include "OSGBaseMFields.h"

#include "OSGMathSFields.h"
#include "OSGMathMFields.h"

#include "OSGVecSFields.h"
#include "OSGVecMFields.h"

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"

#include "OSGAspectIdFields.h"

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.h"

#include "OSGNode.h"
#include "OSGGroup.h"

#include "OSGAttachmentMapSFields.h"
#include "OSGNameAttachment.h"
#include "OSGShaderParameterFields.h"
#include "OSGShaderAttributeFields.h"
#include "OSGFieldConnector.h"
#include "OSGMaterialMapFields.h"
#include "OSGChunkBlockMapFields.h"

#include "OSGFieldContainerUtils.h"

#include "OSGDynFieldContainerInterface.h"


OSG_BEGIN_NAMESPACE

OSG_DYNFIELDATTACHMENT_INST(OSGGenericAttDesc)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGLoader::initFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfBool);

/*
    setIntExtMapping(ScanParseSkel::OSGsfColor,
               ::getClassType().getId());
*/

    setIntExtMapping(SFReal32::getClassType().getId(),
                     ScanParseSkel::OSGsfFloat);
    setIntExtMapping(SFReal64::getClassType().getId(),
                     ScanParseSkel::OSGsfFloat);
/*
    setIntExtMapping(SFImagePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfString);
*/
    setIntExtMapping(SFInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);


    setIntExtMapping(SFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGsfRotation);

    setIntExtMapping(SFString::getClassType().getId(),
                     ScanParseSkel::OSGsfString);

    setIntExtMapping(SFTime::getClassType().getId(),
                     ScanParseSkel::OSGsfTime);

    setIntExtMapping(SFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2f);
    setIntExtMapping(SFVec2d::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2f);

    setIntExtMapping(SFVec2s::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2i);

    setIntExtMapping(SFVec2i::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2i);

    setIntExtMapping(SFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);
    setIntExtMapping(SFVec3d::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);

    setIntExtMapping(SFVec3i::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3i);

    setIntExtMapping(SFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec4f);

    setIntExtMapping(SFVec4d::getClassType().getId(),
                     ScanParseSkel::OSGsfVec4d);

    setIntExtMapping(SFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor4f);

    setIntExtMapping(SFColor4ub::getClassType().getId(),
                     ScanParseSkel::OSGsfColor4i);

    setIntExtMapping(SFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor3f);

/*
    setIntExtMapping(ScanParseSkel::OSGmfColor,
               ::getClassType().getId());
*/

    setIntExtMapping(MFReal32::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);

    setIntExtMapping(MFInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(MFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGmfRotation);

    setIntExtMapping(MFString::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFTime::getClassType().getId(),
                     ScanParseSkel::OSGmfTime);


    setIntExtMapping(MFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec2f);

    setIntExtMapping(MFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec4f);

    setIntExtMapping(MFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor4f);

    setIntExtMapping(MFColor4ub::getClassType().getId(),
                     ScanParseSkel::OSGmfColor4i);

    setIntExtMapping(MFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor3f);

    setIntExtMapping(SFUnrecNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFUnrecNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);
    setIntExtMapping(MFUnrecChildNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);


    /* To Base Type Mappings */

    setIntExtMapping(SFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    setIntExtMapping(SFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFInt16::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFInt16::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    setIntExtMapping(SFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFGLenum::getClassType().getId(),
                     ScanParseSkel::OSGsfString);
    setIntExtMapping(MFGLenum::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(SFAspectId::getClassType().getId(),
                     ScanParseSkel::OSGsfString);
//    setIntExtMapping(MFGLenum::getClassType().getId(),
//                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFShaderParameter::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFShaderAttribute::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    /* To Node Mappings */

    setIntExtMapping(SFAttachmentPtrMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFMaterialPtrMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFChunkBlockPtrMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    /* extended types */

    setIntExtMapping(SFMatrix::getClassType().getId(),
                     ScanParseSkel::OSGsfMatrix);

    setIntExtMapping(SFPnt4f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt4f);

    setIntExtMapping(MFPnt4f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt4f);

    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt3f);

    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt3f);

    setIntExtMapping(SFPnt2f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt2f);

    setIntExtMapping(MFPnt2f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt2f);

    setIntExtMapping(SFPlane::getClassType().getId(),
                     ScanParseSkel::OSGsfPlane);
    setIntExtMapping(MFPlane::getClassType().getId(),
                     ScanParseSkel::OSGmfPlane);

    setIntExtMapping(SFBoxVolume::getClassType().getId(),
                     ScanParseSkel::OSGsfVolume);


    // Map from scanner/parser to OSG

    setExtIntMapping(ScanParseSkel::OSGsfBool,
                     SFBool::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfColor,
                     SFColor3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfColorRGBA,
                     SFColor4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfDouble,
                     SFReal64::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfFloat,
                     SFReal32::getClassType().getId());

#if 0
    setExtIntMapping(ScanParseSkel::OSGsfImage,
                    ::getClassType().getId());
#endif

    setExtIntMapping(ScanParseSkel::OSGsfInt32,
                     SFInt32::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGsfMatrix3d,
                    ::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfMatrix3f,
                    ::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGsfMatrix4d,
                     SFMatrix4d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfMatrix4f,
                     SFMatrix::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGsfNode,
                    ::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGsfRotation,
                     SFQuaternion::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfString,
                     SFString::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfTime,
                     SFTime::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec2d,
                     SFVec2d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec2f,
                     SFVec2f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec3d,
                     SFVec3d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec3f,
                     SFVec3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec4d,
                     SFVec4d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVec4f,
                     SFVec4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfBool,
                     MFBool::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfColor,
                     MFColor3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfColorRGBA,
                     MFColor4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfDouble,
                     MFReal64::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfFloat,
                     MFReal32::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGmfImage,
                     ::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGmfInt32,
                     MFInt32::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGmfMatrix3d,
                     ::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfMatrix3f,
                    ::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGmfMatrix4d,
                     MFMatrix4d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfMatrix4f,
                     MFMatrix::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGmfNode,
                    ::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGmfRotation,
                     MFQuaternion::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfString,
                     MFString::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfTime,
                     MFTime::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec2d,
                     MFVec2d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec2f,
                     MFVec2f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec3d,
                     MFVec3d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec3f,
                     MFVec3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec4d,
                     MFVec4d::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec4f,
                     MFVec4f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfColor4f,
                     MFColor4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfColor4i,
                     MFColor4ub::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfColor3f,
                     MFColor3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfMatrix,
                     MFMatrix::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfPnt2f,
                     MFPnt2f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfPnt3f,
                     MFPnt3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfPnt4f,
                     MFPnt4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfPlane,
                     MFPlane::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfColor4f,
                     SFColor4f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfColor4i,
                     SFColor4ub::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfColor3f,
                     SFColor3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfMatrix,
                     SFMatrix::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfPnt2f,
                     SFPnt2f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfPnt3f,
                     SFPnt3f::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfPnt4f,
                     SFPnt4f::getClassType().getId());
#if 0
    setExtIntMapping(ScanParseSkel::OSGsfVec2i,
                     SFVec2i::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGmfVec2i,
                     MFVec2i::getClassType().getId());
#endif
    setExtIntMapping(ScanParseSkel::OSGsfPlane,
                     SFPlane::getClassType().getId());
    setExtIntMapping(ScanParseSkel::OSGsfVolume,
                     SFBoxVolume::getClassType().getId());

}

void OSGLoader::setFieldContainerValue(FieldContainer *pNewNode)
{
    if(_pCurrentField != NULL)
    {
        FieldContainerPtrSFieldBase::EditHandlePtr pSFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::EditHandle>(
                    _pCurrentField);

        FieldContainerPtrMFieldBase::EditHandlePtr pMFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::EditHandle>(
                    _pCurrentField);

        EditMapFieldHandlePtr pMapHandle = 
            boost::dynamic_pointer_cast<
                EditMapFieldHandle>(_pCurrentField);

        if(pSFHandle != NULL && pSFHandle->isValid())
        {
            bool rc = pSFHandle->set(pNewNode);

            if(rc == false)
            {
                Node *pNode = dynamic_cast<Node *>(pNewNode);

                if(pNode != NULL)
                {
                    pSFHandle->set(pNode->getCore());
                }
            }
        }
        else if(pMFHandle != NULL && pMFHandle->isValid())
        {
            bool rc = pMFHandle->add(pNewNode);

            if(rc == false)
            {
                Node *pNode = dynamic_cast<Node *>(pNewNode);

                if(pNode != NULL)
                {
                    pMFHandle->add(pNode->getCore());
                }
            }
        }
        else if(pMapHandle != NULL && pMapHandle->isValid())
        {
            pMapHandle->add(pNewNode, "0");

#if 0
            if(rc == false)
            {
                Node *pNode = dynamic_cast<Node *>(pNewNode);

                if(pNode != NULL)
                {
                    pMapHandle->add(pNode->getCore(), "0");
                }
            }
#endif
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGLoader::OSGLoader(const std::vector<Functor>  &       endNodeFunctors,
                           FileContextAttachment * const pFileContext   ) :
     Inherited        (               ),
    _pCurrentFC       (NULL           ),
    _pRootNode        (NULL           ),
    _pRootContainer   (NULL           ),
    _pCurrentField    (               ),
    _pCurrentFieldDesc(NULL           ),
    _defMap           (               ),
    _bReadContainer   (false          ),
    _fResolver        (NULL           ),
    _endNodeFunctors  (endNodeFunctors),
    _fcStack          (               ),
    _fStack           (               ),
    _fdStack          (               ),
    _bvChanged        (              0),
    _sChangedStack    (               ),
    _pFileContext     (pFileContext   )
{
    Self::setReferenceHeader("#OSG V1.0 ");
    initFieldTypeMapper();
}

/** \brief Destructor
 */

OSGLoader::~OSGLoader(void)
{
}

/*------------------------------ access -----------------------------------*/

NodeTransitPtr OSGLoader::scanStream(std::istream &iStream,
                                     Resolver      fResolver)
{
    NodeTransitPtr returnValue(NULL);

    if(iStream)
    {
        _pRootNode         = NULL;
        _pRootContainer    = NULL;
        _pCurrentFC        = NULL;

        _pCurrentField.reset();

        _pCurrentFieldDesc = NULL;
        _bReadContainer    = false;
        _fResolver         = fResolver;

        _defMap .clear();

        Inherited::scanStream(iStream);

        returnValue = _pRootNode;

        _pRootNode      = NULL;
        _pRootContainer = NULL;
        _pCurrentFC     = NULL;
        _fResolver      = NULL;
    }

    return returnValue;
}

FieldContainerTransitPtr OSGLoader::scanStreamContainer(std::istream &iStream,
                                                        Resolver      fResolver)
{
    FieldContainerTransitPtr returnValue(NULL);

    if(iStream)
    {
        _pRootNode         = NULL;
        _pRootContainer    = NULL;
        _pCurrentFC        = NULL;

        _pCurrentField.reset();

        _pCurrentFieldDesc = NULL;
        _bReadContainer    = true;
        _fResolver         = fResolver;

        _defMap .clear();

        Inherited::scanStream(iStream);

        returnValue = _pRootContainer;

        _bReadContainer = false;
        _pRootNode      = NULL;
        _pRootContainer = NULL;
        _pCurrentFC     = NULL;
        _fResolver      = NULL;
    }

    return returnValue;
}

bool OSGLoader::checkHeader(void)
{
    return true;
}

#if defined(OSG_WIN32_ICL)
#pragma warning (disable : 383)
#endif

void OSGLoader::beginNode(const Char8     *szNodeTypename,
                          const Char8     *szNodename,
                          const BitVector  bvLocalFlags  )
{
    FieldContainerUnrecPtr pNewNode;

    if(szNodeTypename == NULL)
        return;

    PINFO << "Begin node : " << szNodeTypename << " | ";

    if(szNodename == NULL)
    {
        PINFO << "NULL";
    }
    else
    {
        PINFO << szNodename;
    }

    PINFO << std::endl;

    if(bvLocalFlags != TypeTraits<BitVector>::BitsClear)
    {
        pNewNode =
            FieldContainerFactory::the()->createLocalContainer(szNodeTypename,
                                                               bvLocalFlags   );
    }
    else
    {
        pNewNode =
            FieldContainerFactory::the()->createContainer(szNodeTypename);
    }
    
    if(pNewNode == NULL)
    {
        PWARNING << "Unknow container type " << szNodeTypename << std::endl;
    }
    
    PINFO << "  Got ptr " << pNewNode << std::endl;

    if(szNodename != NULL && pNewNode != NULL)
    {
        AttachmentContainer *pAttCon =
            dynamic_cast<AttachmentContainer *>(pNewNode.get());

        if(pAttCon != NULL)
        {
            setName(pAttCon, szNodename);
        }

        _defMap.insert(std::make_pair(std::string(szNodename), pNewNode));
    }

    // assign nodepointer to current sf|mf field

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        if(_bReadContainer == false)
        {
            NodeUnrecPtr pNode = NULL;
            
            if(_pCurrentFC->getType().isNode())
            {
                pNode = dynamic_cast<Node *>(_pCurrentFC.get());
            }
            else if(_pCurrentFC->getType().isNodeCore())
            {
                pNode = Node::create();
                
                pNode->setCore(dynamic_cast<NodeCore *>(_pCurrentFC.get()));
            }
            else
            {
                SLOG << "Fieldcontainer " << szNodeTypename
                     << "is neither Node nor NodeCore " << std::endl;
            }
            
            if(_pRootNode == NULL)
            {
                GroupUnrecPtr pGroup = Group::create();
                
                _pRootNode = Node::create();
                
                _pRootNode->setCore(pGroup);
            }
            
            _pRootNode->addChild(pNode);
        }
        else
        {
            _pRootContainer = pNewNode;
        }
    }

    _sChangedStack.push(_bvChanged);

    _bvChanged = 0;
}

#if defined(OSG_WIN32_ICL)
#pragma warning (default : 383)
#endif

void OSGLoader::endNode(void)
{
    PINFO << "End Node" << std::endl;

    if(_pCurrentFC != NULL)
    {
        if(_pCurrentFC->getType().isNode() == true)
        {
            Node *pNode = dynamic_cast<Node *>(_pCurrentFC.get());

            if(pNode->getCore() == NULL)
            {
                GroupUnrecPtr pGroup = Group::create();

                pNode->setCore(pGroup);
            }
        }

        UInt32 uiFunctorIndex = _pCurrentFC->getType().getId();

        if(uiFunctorIndex < _endNodeFunctors.size() && 
           ! _endNodeFunctors[uiFunctorIndex].empty())
        {
            (_endNodeFunctors[uiFunctorIndex])(_pCurrentFC, _pFileContext);
        }
    }

    setFieldContainerValue(_pCurrentFC);

    _fcStack.pop();

    if(_fcStack.size() != 0)
    {
        _pCurrentFC = _fcStack.top();
    }
    else
    {
        _pCurrentFC = NULL;
    }

    if(_sChangedStack.size() != 0)
    {
        _bvChanged = _sChangedStack.top();
    }
    else
    {
        _bvChanged = 0;
    }

    _sChangedStack.pop();
}

void OSGLoader::nullNode(void)
{
    setFieldContainerValue(NULL);
}

void OSGLoader::use(const Char8 *szName)
{
    if(szName == NULL)
        return;

    FieldContainer *pUseNode = NULL;
    NodeUnrecPtr    pClone   = NULL;

    // try to find a container with the given name attachment

    if(szName[0] == '@')
    {
        pUseNode = getReference(&(szName[1]));

        Node *pNode = dynamic_cast<Node *>(pUseNode);

        if(pNode != NULL)
        {
            if(pNode->getParent() != NULL)
            {
                pClone = OSG::cloneTree(pNode, "", "");

                pUseNode = pClone;
            }
        }
    }
    else
    {
        pUseNode = getReference(szName);
    }

    if(pUseNode == NULL)
    {
        SLOG << "No FieldContainer found with name " << szName << std::endl;
    }
    else
    {
        // assign nodepointer to current sf|mf field
        setFieldContainerValue(pUseNode);
    }

    pClone = NULL;
}

void OSGLoader::addFieldValue(const Char8 *szFieldVal)
{
    PINFO << "\t\tFV : " << szFieldVal << std::endl;

    if(_pCurrentField != NULL)
    {
//        _pCurrentFieldDesc->pushValueFromCString( szFieldVal,
//                                                 _pCurrentField);

        _pCurrentField->pushValueFromCString(szFieldVal);
    }
}

UInt32 OSGLoader::getFieldType(const Char8 *szFieldname)
{
    UInt32                returnValue = 0;
    FieldDescriptionBase *pFieldDesc  = NULL;

    if(szFieldname == NULL)
        return returnValue;

    if(_pCurrentFC != NULL)
    {
        pFieldDesc = _pCurrentFC->getFieldDescription(szFieldname);

        PINFO << "GF : " << szFieldname << " " << pFieldDesc << std::endl;

        if(pFieldDesc != NULL)
        {
            returnValue = pFieldDesc->getFieldType().getScanTypeId();
        }
    }

    return returnValue;
}


void OSGLoader::addRoute(const Char8  *szOutNodename,
                         const Char8  *szOutFieldname,
                         const Char8  *szInNodename,
                         const Char8  *szInFieldname)
{
    if(szOutNodename == NULL || szOutFieldname == NULL ||
       szInNodename  == NULL || szInFieldname  == NULL  )
    {
        FWARNING(("addRoute missing params\n"));
    }

    FieldContainer *pSrcNode = getReference(szOutNodename);
    FieldContainer *pDstNode = getReference(szInNodename );

    if(pSrcNode == NULL)
    {
        pSrcNode = resolveFieldPath(szOutNodename, 
                                    boost::bind(&OSGLoader::getReference,
                                                this,
                                                ::boost::placeholders::_1));
    }

    AttachmentContainer *pSrc = dynamic_cast<AttachmentContainer *>(pSrcNode);

    if(pSrc == NULL)
    {
        FWARNING(("Unknow src node %s\n", szOutNodename));
        return;
    }

    if(pDstNode == NULL)
    {
        pDstNode = resolveFieldPath(szInNodename, 
                                    boost::bind(&OSGLoader::getReference,
                                                this,
                                                ::boost::placeholders::_1));
    }

    if(pDstNode == NULL)
    {
        FWARNING(("Unknow dst node %s\n", szInNodename));
        return;
    }

    addConnection(pSrc,     szOutFieldname,
                  pDstNode, szInFieldname );
}


Int32 OSGLoader::mapExtIntFieldType(const Char8 *szFieldname,
                                    const Int32  iFieldTypeId)
{
    Int32 returnValue = Inherited::mapExtIntFieldType(szFieldname,
                                                      iFieldTypeId);

    if(returnValue < 0 && szFieldname != NULL && _pCurrentFC != NULL)
    {
        FieldDescriptionBase *pFieldDesc = 
            _pCurrentFC->getFieldDescription(szFieldname);

        if(pFieldDesc != NULL)
        {
            const FieldType &oFieldType = pFieldDesc->getFieldType();

            PINFO << "FieldTypeId invalid, trying to fix. " << std::endl;
            PINFO << oFieldType.getContentType().getCName()
                  << " comparing with "
                  << FieldTraits<FieldContainer *>::getType().getCName()
                  << std::endl;


            if(oFieldType.getContentType().isDerivedFrom(
                   FieldTraits<FieldContainer *>::getType()) == true)
            {
                PINFO << "FieldContainer * or derived class, "
                      << "parsing as Node"
                      << std::endl;

                if(oFieldType.getCardinality() == FieldType::SingleField)
                {
                    returnValue = ScanParseSkel::OSGsfNode;
                }
                else
                {
                    returnValue = ScanParseSkel::OSGmfNode;
                }
            }
        }
    }

    return returnValue;
}

void OSGLoader::beginField(const Char8 *szFieldname,
                           const UInt32 )
{
    PINFO << "BeginField "
          << szFieldname
          << " "
          << _pCurrentField
          << std::endl;

    if(szFieldname == NULL)
        return;

    _pCurrentField.reset();

    if(_pCurrentFC != NULL)
    {
        _pCurrentField     = _pCurrentFC->editField(szFieldname);

        _pCurrentFieldDesc =
            _pCurrentFC->getType().getFieldDesc(szFieldname);

        PINFO << "BF : "
              <<  szFieldname       << " "
              << _pCurrentField     << " "
              << _pCurrentFieldDesc << std::endl;

        if(_pCurrentFieldDesc != NULL)
        {
            _bvChanged |= _pCurrentFieldDesc->getFieldMask();
        }
    }

    _fStack.push (_pCurrentField);
    _fdStack.push(_pCurrentFieldDesc);
}

void OSGLoader::endField(void)
{
    PINFO << "End Field" << std::endl;

    _fStack.pop();

    if(_fStack.size() != 0)
    {
        _pCurrentField = _fStack.top();
    }
    else
    {
        _pCurrentField.reset();
    }

    _fdStack.pop();

    if(_fdStack.size() != 0)
    {
        _pCurrentFieldDesc = _fdStack.top();
    }
    else
    {
        _pCurrentFieldDesc = NULL;
    }
}

FieldContainer *OSGLoader::getReference(const Char8 *szName)
{
    // Find a previously DEF'ed FC by its name and return Ptr to it

    NamedFCMap::iterator entry = _defMap.find(std::string(szName));

    if(entry == _defMap.end())
    {
        if(_fResolver)
        {
            return _fResolver(szName, 
                              _pCurrentFC,
                              (_pCurrentFieldDesc != NULL) ? 
                                _pCurrentFieldDesc->getFieldId() : -1);

        }
        return NULL;
    }

    return entry->second; // return the stored FCPtr
}

void OSGLoader::beginFieldDecl(const Char8  *szFieldType,
                               const UInt32  uiFieldTypeId,
                               const Char8  *szFieldName  )
{
    UInt32 uiOSGFieldTypeId = mapIntExtFieldType(szFieldName, uiFieldTypeId);
    
    DynFieldContainerInterface *pIf = 
        dynamic_cast<DynFieldContainerInterface *>(_pCurrentFC.get());

    if(pIf != NULL)
    {
        GetFieldHandlePtr pField = _pCurrentFC->getField(szFieldName);

        if(pField == NULL || pField->isValid() == false)
        {
            if(uiFieldTypeId == 0)
            {
                pIf->addField(szFieldType, szFieldName);
            }
            else
            {
                pIf->addField(uiOSGFieldTypeId, szFieldName);
            }
        }

        _pCurrentField     = _pCurrentFC->editField(szFieldName);
        _pCurrentFieldDesc =
            _pCurrentFC->getType().getFieldDesc(szFieldName);
    }
    else
    {
        AttachmentContainer *pAttCnt = 
            dynamic_cast<AttachmentContainer *>(_pCurrentFC.get());

        if(pAttCnt != NULL)
        {
            OSGGenericAttUnrecPtr pGenAtt = 
                dynamic_cast<OSGGenericAtt *>(
                    pAttCnt->findAttachment(OSGGenericAtt::getClassGroupId()));

            if(pGenAtt == NULL)
            {
                pGenAtt = OSGGenericAtt::create();
                
                pAttCnt->addAttachment(pGenAtt);
            }
            
            GetFieldHandlePtr pField = pGenAtt->getField(szFieldName);

            if(pField == NULL || pField->isValid() == false)
            {
                if(uiFieldTypeId == 0)
                {
//                    pGenAtt->addField(szFieldType, szFieldName);
                }
                else
                {
                    pGenAtt->addField(uiOSGFieldTypeId, szFieldName);
                }
            }
            
            _pCurrentField     = pGenAtt->editField(szFieldName);
            _pCurrentFieldDesc =
                pGenAtt->getType().getFieldDesc(szFieldName);

        }
    }

    _fStack.push (_pCurrentField);
    _fdStack.push(_pCurrentFieldDesc);
}

void OSGLoader::endFieldDecl(void)
{
    endField();
}

OSG_END_NAMESPACE

