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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGMultiLightGroup.h"

#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiLightGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiLightGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiLightGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            MultiLightGroup::getClassType(),
            reinterpret_cast<Action::Callback>(&MultiLightGroup::renderEnter));

        RenderAction::registerLeaveDefault(
            MultiLightGroup::getClassType(),
            reinterpret_cast<Action::Callback>(&MultiLightGroup::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiLightGroup::MultiLightGroup(void) :
    Inherited()
{
}

MultiLightGroup::MultiLightGroup(const MultiLightGroup &source) :
    Inherited(source)
{
}

MultiLightGroup::~MultiLightGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiLightGroup::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MultiLightGroup::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiLightGroup NI" << std::endl;
}

/*-------------------------------- Render ---------------------------------*/

Action::ResultE MultiLightGroup::renderEnter(Action *action)
{
    RenderAction* pAction = dynamic_cast<RenderAction*>(action);

    Action::ResultE r = Group::renderEnter(action);

    // ok all children are culled away so we leave
    // immediately and don't set the material!
    if(r == Action::Skip)
        return r;

    if (getActivate()              == true &&
        pAction                    != NULL &&
        this->getMultiLightChunk() != NULL  )
    {
        pAction->pushState();
        pAction->addOverride(getMultiLightChunk()->getClassId() + getLightBindingPnt(), getMultiLightChunk());
    }

    return r;
}

Action::ResultE MultiLightGroup::renderLeave(Action *action)
{
    Action::ResultE r = Action::Continue;

    RenderAction* pAction = dynamic_cast<RenderAction*>(action);
    if (getActivate()              == true &&
        pAction                    != NULL  )
    {
        pAction->popState();
    }

    return Group::renderLeave(action);
}

MultiLightChunk* MultiLightGroup::getChunk()
{
    MultiLightChunk* pChunk = getMultiLightChunk();
    if (pChunk == NULL)
    {
        MultiLightChunkUnrecPtr chunk = MultiLightChunk::createLocal();
        setMultiLightChunk(chunk);
        return getMultiLightChunk();
    }
    else
        return pChunk;
}

const MultiLightChunk* MultiLightGroup::getChunk() const
{
    return const_cast<MultiLightGroup*>(this)->getChunk();
}

OSG_END_NAMESPACE
