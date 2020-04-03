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

#ifndef _OSGSHADERPROGRAMMANAGER_H_
#define _OSGSHADERPROGRAMMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderProgramManagerBase.h"
#include "OSGHashKeyToFieldContainerMap.h"
#include "OSGShaderProgram.h"

OSG_BEGIN_NAMESPACE

class ShaderCodeGenerator;
class ShaderDesc;

/*! \brief ShaderProgramManager class. See \ref
           PageContribTechniquesShaderProgramManager for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ShaderProgramManager : public ShaderProgramManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderProgramManagerBase Inherited;
    typedef ShaderProgramManager     Self;

    typedef UInt64                                      KeyType;
    typedef boost::call_traits<KeyType>::param_type     KeyParamType;
    typedef boost::call_traits<KeyType>::value_type     KeyValueType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    typedef boost::function<void (ShaderProgram *)> ShaderProgramCallback;

    virtual void createProgram(ShaderDesc* shaderDesc, ShaderCodeGenerator* generator);
    virtual void updateProgram();
    virtual void clearPrograms();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    void setInitCallback    (ShaderProgramFunctor func, const std::string& createSymbol);
    void setUpdateCallback  (ShaderProgramFunctor func, const std::string& createSymbol);

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

    // Variables should all be in ShaderProgramManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderProgramManager(void);
    ShaderProgramManager(const ShaderProgramManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderProgramManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    void onCreate      (const ShaderProgramManager *source      = NULL);
    void onCreateAspect(const ShaderProgramManager *createAspect,
                        const ShaderProgramManager *source      = NULL);
    void onDestroy(           UInt32                uiId              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     ProgramMap                               */
    /*! \{                                                                 */

    ShaderProgram* getShaderProgram(KeyParamType key) const;
    ShaderProgram* getShaderProgram(UInt32 idx) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

    void createVertexProgram    (ShaderDesc*            shaderDesc, 
                                 KeyParamType           hash, 
                                 ShaderCodeGenerator*   generator);
    void createFragmentProgram  (ShaderDesc*            shaderDesc, 
                                 KeyParamType           hash, 
                                 ShaderCodeGenerator*   generator);

    void createDefaultAttribMapping(ShaderProgram* shader);

  private:

    friend class FieldContainer;
    friend class ShaderProgramManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderProgramManager &source);
};

typedef ShaderProgramManager *ShaderProgramManagerP;

OSG_END_NAMESPACE

#include "OSGShaderProgramManagerBase.inl"
#include "OSGShaderProgramManager.inl"

#endif /* _OSGSHADERPROGRAMMANAGER_H_ */
