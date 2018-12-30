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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class UniformBufferObjStd140Chunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#ifdef WIN32 
#pragma warning(disable: 4355) // turn off 'this' : used in base member initializer list warning
#pragma warning(disable: 4290) // disable exception specification warning
#endif

#include "OSGConfig.h"




#include "OSGUniformBufferObjStd140ChunkBase.h"
#include "OSGUniformBufferObjStd140Chunk.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::UniformBufferObjStd140Chunk
    See \ref PageSystemUniformBufferObjChunk for a description.

    This chunk wraps the OpenGL uniform buffer object extension (ARB_uniform_buffer_object). 
    Basically, it holds a raw memory buffer and a buffer object binding point. The raw memory 
    buffer is expected to be provided by the chunk user in a OpenGL std140 compatible format. 
    Any shader binding  an uniform block to the very same binding point is expected to respect 
    the corresponding block layout.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var GLenum          UniformBufferObjStd140ChunkBase::_sfGLId
    The OpenGL object id for this uniform buffer object.
*/

/*! \var GLenum          UniformBufferObjStd140ChunkBase::_sfUsage
    Specifies the expected usage pattern of the data store. The symbolic constant must be 
    GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, 
    GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
    GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
*/

/*! \var UInt8           UniformBufferObjStd140ChunkBase::_mfBuffer
    The uniform buffer storage. The layout of this memory block is governed by the
    shader uniform block layout according to OpenGL std140 specification.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<UniformBufferObjStd140Chunk *, nsOSG>::_type(
    "UniformBufferObjStd140ChunkPtr", 
    "UniformBufferObjBaseChunkPtr", 
    UniformBufferObjStd140Chunk::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(UniformBufferObjStd140Chunk *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           UniformBufferObjStd140Chunk *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           UniformBufferObjStd140Chunk *,
                           nsOSG)

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void UniformBufferObjStd140ChunkBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "GLId",
        "The OpenGL object id for this uniform buffer object.\n",
        GLIdFieldId, GLIdFieldMask,
        true,
        (Field::FClusterLocal),
        static_cast<FieldEditMethodSig>(&UniformBufferObjStd140Chunk::editHandleGLId),
        static_cast<FieldGetMethodSig >(&UniformBufferObjStd140Chunk::getHandleGLId));

    oType.addInitialDesc(pDesc);

    pDesc = new SFGLenum::Description(
        SFGLenum::getClassType(),
        "usage",
        "Specifies the expected usage pattern of the data store. The symbolic constant must be \n"
        "GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, \n"
        "GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, \n"
        "GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.\n",
        UsageFieldId, UsageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&UniformBufferObjStd140Chunk::editHandleUsage),
        static_cast<FieldGetMethodSig >(&UniformBufferObjStd140Chunk::getHandleUsage));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUInt8::Description(
        MFUInt8::getClassType(),
        "buffer",
        "The uniform buffer storage. The layout of this memory block is governed by the\n"
        "shader uniform block layout according to OpenGL std140 specification.\n",
        BufferFieldId, BufferFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&UniformBufferObjStd140Chunk::editHandleBuffer),
        static_cast<FieldGetMethodSig >(&UniformBufferObjStd140Chunk::getHandleBuffer));

    oType.addInitialDesc(pDesc);
}


UniformBufferObjStd140ChunkBase::TypeObject UniformBufferObjStd140ChunkBase::_type(
    UniformBufferObjStd140ChunkBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&UniformBufferObjStd140ChunkBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&UniformBufferObjStd140Chunk::initMethod),
    reinterpret_cast<ExitContainerF>(&UniformBufferObjStd140Chunk::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&UniformBufferObjStd140Chunk::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"UniformBufferObjStd140Chunk\"\n"
    "    parent=\"UniformBufferObjBaseChunk\"\n"
    "    library=\"System\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    docGroupBase=\"GrpSystemState\"\n"
    "    >\n"
    "    See \\ref PageSystemUniformBufferObjChunk for a description.\n"
    "\n"
    "    This chunk wraps the OpenGL uniform buffer object extension (ARB_uniform_buffer_object). \n"
    "    Basically, it holds a raw memory buffer and a buffer object binding point. The raw memory \n"
    "    buffer is expected to be provided by the chunk user in a OpenGL std140 compatible format. \n"
    "    Any shader binding  an uniform block to the very same binding point is expected to respect \n"
    "    the corresponding block layout.\n"
    "\n"
    "    <Field\n"
    "        name=\"GLId\"\n"
    "        type=\"GLenum\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"internal\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"0\"\n"
    "        fieldFlags=\"FClusterLocal\"\n"
    "\t>\n"
    "            The OpenGL object id for this uniform buffer object.\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"usage\"\n"
    "        type=\"GLenum\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "        defaultValue=\"GL_STATIC_DRAW\"\n"
    "        potential_values=\"GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY\"\n"
    "\t>\n"
    "                Specifies the expected usage pattern of the data store. The symbolic constant must be \n"
    "                 GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, \n"
    "                 GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, \n"
    "                 GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.\n"
    "    </Field>\n"
    "<Field\n"
    "        name=\"buffer\"\n"
    "        type=\"UInt8\"\n"
    "        cardinality=\"multi\"\n"
    "        visibility=\"external\"\n"
    "        access=\"public\"\n"
    "\t>\n"
    "\tThe uniform buffer storage. The layout of this memory block is governed by the\n"
    "                shader uniform block layout according to OpenGL std140 specification.\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "See \\ref PageSystemUniformBufferObjChunk for a description.\n"
    "\n"
    "This chunk wraps the OpenGL uniform buffer object extension (ARB_uniform_buffer_object). \n"
    "Basically, it holds a raw memory buffer and a buffer object binding point. The raw memory \n"
    "buffer is expected to be provided by the chunk user in a OpenGL std140 compatible format. \n"
    "Any shader binding  an uniform block to the very same binding point is expected to respect \n"
    "the corresponding block layout.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &UniformBufferObjStd140ChunkBase::getType(void)
{
    return _type;
}

const FieldContainerType &UniformBufferObjStd140ChunkBase::getType(void) const
{
    return _type;
}

UInt32 UniformBufferObjStd140ChunkBase::getContainerSize(void) const
{
    return sizeof(UniformBufferObjStd140Chunk);
}

/*------------------------- decorator get ------------------------------*/


SFGLenum *UniformBufferObjStd140ChunkBase::editSFGLId(void)
{
    editSField(GLIdFieldMask);

    return &_sfGLId;
}

const SFGLenum *UniformBufferObjStd140ChunkBase::getSFGLId(void) const
{
    return &_sfGLId;
}


SFGLenum *UniformBufferObjStd140ChunkBase::editSFUsage(void)
{
    editSField(UsageFieldMask);

    return &_sfUsage;
}

const SFGLenum *UniformBufferObjStd140ChunkBase::getSFUsage(void) const
{
    return &_sfUsage;
}


MFUInt8 *UniformBufferObjStd140ChunkBase::editMFBuffer(void)
{
    editMField(BufferFieldMask, _mfBuffer);

    return &_mfBuffer;
}

const MFUInt8 *UniformBufferObjStd140ChunkBase::getMFBuffer(void) const
{
    return &_mfBuffer;
}






/*------------------------------ access -----------------------------------*/

SizeT UniformBufferObjStd140ChunkBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        returnValue += _sfGLId.getBinSize();
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        returnValue += _sfUsage.getBinSize();
    }
    if(FieldBits::NoField != (BufferFieldMask & whichField))
    {
        returnValue += _mfBuffer.getBinSize();
    }

    return returnValue;
}

void UniformBufferObjStd140ChunkBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyToBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        _sfUsage.copyToBin(pMem);
    }
    if(FieldBits::NoField != (BufferFieldMask & whichField))
    {
        _mfBuffer.copyToBin(pMem);
    }
}

void UniformBufferObjStd140ChunkBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        editSField(GLIdFieldMask);
        _sfGLId.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (UsageFieldMask & whichField))
    {
        editSField(UsageFieldMask);
        _sfUsage.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (BufferFieldMask & whichField))
    {
        editMField(BufferFieldMask, _mfBuffer);
        _mfBuffer.copyFromBin(pMem);
    }
}

//! create a new instance of the class
UniformBufferObjStd140ChunkTransitPtr UniformBufferObjStd140ChunkBase::createLocal(BitVector bFlags)
{
    UniformBufferObjStd140ChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<UniformBufferObjStd140Chunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
UniformBufferObjStd140ChunkTransitPtr UniformBufferObjStd140ChunkBase::createDependent(BitVector bFlags)
{
    UniformBufferObjStd140ChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<UniformBufferObjStd140Chunk>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
UniformBufferObjStd140ChunkTransitPtr UniformBufferObjStd140ChunkBase::create(void)
{
    UniformBufferObjStd140ChunkTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<UniformBufferObjStd140Chunk>(tmpPtr);
    }

    return fc;
}

UniformBufferObjStd140Chunk *UniformBufferObjStd140ChunkBase::createEmptyLocal(BitVector bFlags)
{
    UniformBufferObjStd140Chunk *returnValue;

    newPtr<UniformBufferObjStd140Chunk>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
UniformBufferObjStd140Chunk *UniformBufferObjStd140ChunkBase::createEmpty(void)
{
    UniformBufferObjStd140Chunk *returnValue;

    newPtr<UniformBufferObjStd140Chunk>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr UniformBufferObjStd140ChunkBase::shallowCopyLocal(
    BitVector bFlags) const
{
    UniformBufferObjStd140Chunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const UniformBufferObjStd140Chunk *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr UniformBufferObjStd140ChunkBase::shallowCopyDependent(
    BitVector bFlags) const
{
    UniformBufferObjStd140Chunk *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const UniformBufferObjStd140Chunk *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr UniformBufferObjStd140ChunkBase::shallowCopy(void) const
{
    UniformBufferObjStd140Chunk *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const UniformBufferObjStd140Chunk *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

UniformBufferObjStd140ChunkBase::UniformBufferObjStd140ChunkBase(void) :
    Inherited(),
    _sfGLId                   (GLenum(0)),
    _sfUsage                  (GLenum(GL_STATIC_DRAW)),
    _mfBuffer                 ()
{
}

UniformBufferObjStd140ChunkBase::UniformBufferObjStd140ChunkBase(const UniformBufferObjStd140ChunkBase &source) :
    Inherited(source),
    _sfGLId                   (source._sfGLId                   ),
    _sfUsage                  (source._sfUsage                  ),
    _mfBuffer                 (source._mfBuffer                 )
{
}


/*-------------------------- destructors ----------------------------------*/

UniformBufferObjStd140ChunkBase::~UniformBufferObjStd140ChunkBase(void)
{
}


GetFieldHandlePtr UniformBufferObjStd140ChunkBase::getHandleGLId            (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfGLId,
             this->getType().getFieldDesc(GLIdFieldId),
             const_cast<UniformBufferObjStd140ChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr UniformBufferObjStd140ChunkBase::editHandleGLId           (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfGLId,
             this->getType().getFieldDesc(GLIdFieldId),
             this));


    editSField(GLIdFieldMask);

    return returnValue;
}

GetFieldHandlePtr UniformBufferObjStd140ChunkBase::getHandleUsage           (void) const
{
    SFGLenum::GetHandlePtr returnValue(
        new  SFGLenum::GetHandle(
             &_sfUsage,
             this->getType().getFieldDesc(UsageFieldId),
             const_cast<UniformBufferObjStd140ChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr UniformBufferObjStd140ChunkBase::editHandleUsage          (void)
{
    SFGLenum::EditHandlePtr returnValue(
        new  SFGLenum::EditHandle(
             &_sfUsage,
             this->getType().getFieldDesc(UsageFieldId),
             this));


    editSField(UsageFieldMask);

    return returnValue;
}

GetFieldHandlePtr UniformBufferObjStd140ChunkBase::getHandleBuffer          (void) const
{
    MFUInt8::GetHandlePtr returnValue(
        new  MFUInt8::GetHandle(
             &_mfBuffer,
             this->getType().getFieldDesc(BufferFieldId),
             const_cast<UniformBufferObjStd140ChunkBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr UniformBufferObjStd140ChunkBase::editHandleBuffer         (void)
{
    MFUInt8::EditHandlePtr returnValue(
        new  MFUInt8::EditHandle(
             &_mfBuffer,
             this->getType().getFieldDesc(BufferFieldId),
             this));


    editMField(BufferFieldMask, _mfBuffer);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void UniformBufferObjStd140ChunkBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    UniformBufferObjStd140Chunk *pThis = static_cast<UniformBufferObjStd140Chunk *>(this);

    pThis->execSync(static_cast<UniformBufferObjStd140Chunk *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *UniformBufferObjStd140ChunkBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    UniformBufferObjStd140Chunk *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const UniformBufferObjStd140Chunk *>(pRefAspect),
                  dynamic_cast<const UniformBufferObjStd140Chunk *>(this));

    return returnValue;
}
#endif

void UniformBufferObjStd140ChunkBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfBuffer.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
