/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

template <class ParentT> inline
bool ComputeElementHandlerMixin<ParentT>::requestRun(void)
{
    Self::editSField(Self::RequestRunFieldMask);

    return true;
}

template <class ParentT> inline
void ComputeElementHandlerMixin<ParentT>::changed(ConstFieldMaskArg whichField, 
                                                  UInt32            origin,
                                                  BitVector         details)
{
#if 0
    if(0x0000 != (whichField & RequestRunFieldMask))
    {
        Window::requestStageRun(_iStageId);
    }
#endif

    Inherited::changed(whichField, origin, details);
}

#ifdef WIN32
template <class ParentT> inline
void ComputeElementHandlerMixin<ParentT>::setData(TraversalData    *pData, 
                                                  Int32             iDataSlotId,
                                                  RenderActionBase *pAction    )
{
    Inherited::setData(pData, iDataSlotId, pAction);
}
#endif

template <class ParentT> inline
void ComputeElementHandlerMixin<ParentT>::setData(
    HardwareContextData *pData, 
    Int32                iDataSlotId,
    HardwareContext     *pContext   )
{
    HardwareContextData *pStoredData = 
        pContext->template getData<HardwareContextData *>(this->_iDataSlotId);

    OSG_ASSERT(iDataSlotId == this->_iDataSlotId);

    if(pStoredData == NULL)
    {
        pContext->setData(pData, this->_iDataSlotId);

        if(this->hasDestroyedFunctor(
               boost::bind(&ContextDataSlotHandler::clearData,
                           pContext,
                           ::boost::placeholders::_1,
                           ::boost::placeholders::_2,
                           this->_iDataSlotId)) == false)
        {
            this->addDestroyedFunctor(
                boost::bind(&ContextDataSlotHandler::clearData,
                            static_cast<ContextDataSlotHandler *>(pContext),
                            ::boost::placeholders::_1,
                            ::boost::placeholders::_2,
                            this->_iDataSlotId), "");

            pContext->addDestroyedFunctorFor(
                boost::bind(&Self::template clearDestroyedFunctorFor<
                                ContextDataSlotHandler>,
                            this,
                            ::boost::placeholders::_1),
                this);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
ComputeElementHandlerMixin<ParentT>::ComputeElementHandlerMixin(void) :
    Inherited()
{
#if 0
    _tmpStatus = StageValidator::Finished;
#endif
}

template <class ParentT> inline
ComputeElementHandlerMixin<ParentT>::ComputeElementHandlerMixin(
    const ComputeElementHandlerMixin &source) :

    Inherited(source)
{
#if 0
    _tmpStatus = StageValidator::Finished;
#endif
}

template <class ParentT> inline
ComputeElementHandlerMixin<ParentT>::~ComputeElementHandlerMixin(void)
{
}

template <class ParentT> inline
void ComputeElementHandlerMixin<ParentT>::dump(      UInt32    uiIndent,
                                               const BitVector bvFlags ) const
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

