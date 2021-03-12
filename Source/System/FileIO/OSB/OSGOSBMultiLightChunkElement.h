/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#ifndef _OSGOSBMULTILIGHTCHUNKELEMENT_H_
#define _OSGOSBMULTILIGHTCHUNKELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"

#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactoryHelper.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING OSBMultiLightChunkElement : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OSBCommonElement          Inherited;
    typedef OSBMultiLightChunkElement Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBMultiLightChunkElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBMultiLightChunkElement(void);

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
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper methods                                       */
    /*! \{                                                                 */

    //bool readFieldContainerHeader(std::string &typeName,
    //                              UInt32      &fcId);

    //bool           readFieldHeader       (const std::string    &endMarkers,
    //                                            std::string    &fieldName,
    //                                            std::string    &fieldTypeName,
    //                                            UInt32         &fieldSize     );
    //bool           readFieldHeaderContinue(
    //                                     const std::string &endMarkers,
    //                                     const std::string &fieldName,
    //                                           std::string &fieldTypeName,
    //                                           UInt32      &fieldSize         );
    //bool           readFieldContent      (const std::string    &fieldName,
    //                                      const std::string    &fieldTypeName,
    //                                      const UInt32          fieldSize,
    //                                      const std::string    &excludeFields,
    //                                            PtrFieldListIt &ptrFieldIt    );
    std::string     readFields           (const std::string    &excludeFields,
                                          const std::string    &endMarkers    );
    //std::string    readFieldsContinue    (const std::string &fieldName,
    //                                      const std::string &excludeFields,
    //                                      const std::string &endMarkers       );
    //void           skipFields            (      void                          );
    //PtrFieldListIt readPtrSingleField    (const UInt32          fieldId       );
    //PtrFieldListIt readPtrMultiField     (const UInt32          fieldId,
    //                                      const UInt32          fieldSize     );
    //PtrFieldListIt readAttachmentMapField(const UInt32          fieldId,
    //                                      const UInt32          fieldSize     );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' if needed)       */
    OSBMultiLightChunkElement(const OSBMultiLightChunkElement &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const OSBMultiLightChunkElement &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading Helper Functions                                     */
    /*! \{                                                                 */

    void readTypeField(void);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/

    static OSBElementRegistrationHelper<OSBMultiLightChunkElement> _regHelper;
};

OSG_END_NAMESPACE

#endif /* _OSGOSBMULTILIGHTCHUNKELEMENT_H_ */
