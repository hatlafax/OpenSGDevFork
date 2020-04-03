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

#ifndef _OSGDESCMATERIALSHADERCODEGENERATOR_H_
#define _OSGDESCMATERIALSHADERCODEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDescMaterialShaderCodeGeneratorBase.h"

OSG_BEGIN_NAMESPACE

class DescMaterial;

/*! \brief DescMaterialShaderCodeGenerator class. See \ref
           PageContribTechniquesDescMaterialShaderCodeGenerator for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING DescMaterialShaderCodeGenerator : public DescMaterialShaderCodeGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DescMaterialShaderCodeGeneratorBase Inherited;
    typedef DescMaterialShaderCodeGenerator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    virtual ShaderDescStoreTransitPtr getShaderDescStore(ChunkMaterial* chunkMat);

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

    // Variables should all be in DescMaterialShaderCodeGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DescMaterialShaderCodeGenerator(void);
    DescMaterialShaderCodeGenerator(const DescMaterialShaderCodeGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DescMaterialShaderCodeGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Modern Shader Detail                         */
    /*! \{                                                                 */
    
    void getVertexProgram           (std::stringstream& ost, DescMaterial* descMat) const;
    void getFragmentProgram         (std::stringstream& ost, DescMaterial* descMat) const;

    void getLightProgram            (std::stringstream& ost, DescMaterial* descMat) const;
    void getShadowProgram           (std::stringstream& ost) const;
    void getClusterProgram          (std::stringstream& ost) const;
    void getSSAOProgram             (std::stringstream& ost, bool hasAO) const;
    void getToneMapProgram          (std::stringstream& ost, DescMaterial* descMat) const;
    void getGammaCorrectionProgram  (std::stringstream& ost, DescMaterial* descMat) const;

    void getMainFuncProgram         (std::stringstream& ost, DescMaterial* descMat) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DescMaterialShaderCodeGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DescMaterialShaderCodeGenerator &source);
};

typedef DescMaterialShaderCodeGenerator *DescMaterialShaderCodeGeneratorP;

OSG_END_NAMESPACE

#include "OSGDescMaterialShaderCodeGeneratorBase.inl"
#include "OSGDescMaterialShaderCodeGenerator.inl"

#endif /* _OSGDESCMATERIALSHADERCODEGENERATOR_H_ */
