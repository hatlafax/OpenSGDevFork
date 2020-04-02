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

#ifndef _OSGCONTRIBKTXMAGEFILETYPE_H_
#define _OSGCONTRIBKTXIMAGEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGContribTechniquesDef.h"

#include "OSGBaseTypes.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief KTX File Handler. Used to read/write KTX files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOContribKTX
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ContribKTXImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    ContribKTXImageFileType();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ContribKTXImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Methods                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read (      Image            *pImage, 
                             std::istream     &is, 
                       const std::string      &mimetype);

    virtual bool write(const Image            *pImage, 
                             std::ostream     &os, 
                       const std::string      &mimetype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */
 
    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    ContribKTXImageFileType(const Char8  *mimeType,
                            const Char8  *suffixArray[], 
                                  UInt16  suffixByteCount,
                                  UInt32  flags          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy Op                                */
    /*! \{                                                                 */

          ContribKTXImageFileType            (const ContribKTXImageFileType &obj);
    const ContribKTXImageFileType &operator =(const ContribKTXImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    //static  ContribKTXImageFileType _the;

    typedef ImageFileType    Inherited;
};

typedef ContribKTXImageFileType *ContribKTXImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGCONTRIBKTXIMAGEFILETYPE_H_
