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

#ifndef _OSGCONTRIBDDSIMAGEFILETYPE_H_
#define _OSGCONTRIBDDSIMAGEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGContribTechniquesDef.h"

#include "OSGBaseTypes.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief DDS File Handler. Used to read/write DDS files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOContribDDS
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ContribDDSImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    ContribDDSImageFileType();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ContribDDSImageFileType (void);

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

    ContribDDSImageFileType(const Char8  *mimeType,
                            const Char8  *suffixArray[], 
                                  UInt16  suffixByteCount,
                                  UInt32  flags          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy Op                                */
    /*! \{                                                                 */

          ContribDDSImageFileType            (const ContribDDSImageFileType &obj);
    const ContribDDSImageFileType &operator =(const ContribDDSImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    //static  ContribDDSImageFileType _the;

    typedef ImageFileType    Inherited;
};

typedef ContribDDSImageFileType *ContribDDSImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGCONTRIBDDSIMAGEFILETYPE_H_
