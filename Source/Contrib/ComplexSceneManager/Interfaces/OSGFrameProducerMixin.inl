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

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
FrameProducerMixin<ParentT>::FrameProducerMixin(void) :
    Inherited   (    ),
    Interface   (    )
{
}

template <class ParentT> inline
FrameProducerMixin<ParentT>::FrameProducerMixin(
    const FrameProducerMixin &source) :

    Inherited   (source),
    Interface   (      )
{
}

template <class ParentT> inline
FrameProducerMixin<ParentT>::~FrameProducerMixin(void)
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState < Shutdown && ComplexSceneManager::the() != NULL)
    {
        ComplexSceneManager::the()->removeFrameProducer(this);
    }
}

template <class ParentT> inline
void FrameProducerMixin<ParentT>::dump(      UInt32    uiIndent,
                                       const BitVector bvFlags ) const
{
}

template <class ParentT> inline
void FrameProducerMixin<ParentT>::onCreateAspect(
    const FrameProducerMixin *createAspect,
    const FrameProducerMixin *source       )
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running || ComplexSceneManager::the() == NULL)
        return;

    if(this == createAspect)
    {
        fprintf(stderr, "add producer (oc) %p %p\n", this, createAspect);

        ComplexSceneManager::the()->addFrameProducer(this);
    }
}

template <class ParentT> inline
void FrameProducerMixin<ParentT>::onDestroyAspect(
    UInt32 uiContainerId, UInt32 uiAspect)
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState < Shutdown && ComplexSceneManager::the() != NULL)
    {
        ComplexSceneManager::the()->removeFrameProducer(this);
    }

    Inherited::onDestroyAspect(uiContainerId, uiAspect);
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

