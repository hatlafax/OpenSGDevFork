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

#include "OSGConstantSizeTransform.h"

#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGConstantSizeTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGConstantSizeTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConstantSizeTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ConstantSizeTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ConstantSizeTransform::intersectLeave));

        RenderAction::registerEnterDefault(
            ConstantSizeTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ConstantSizeTransform::renderEnter));

        RenderAction::registerLeaveDefault(
            ConstantSizeTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(&ConstantSizeTransform::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ConstantSizeTransform::ConstantSizeTransform(void) :
    Inherited()
{
}

ConstantSizeTransform::ConstantSizeTransform(const ConstantSizeTransform &source) :
    Inherited(source)
{
}

ConstantSizeTransform::~ConstantSizeTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ConstantSizeTransform::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ConstantSizeTransform::dump(      UInt32    ,
                                 const BitVector ) const
{
    SLOG << "Dump ConstantSizeTransform NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

/*------------------------- volume update -------------------------------*/

void ConstantSizeTransform::adjustVolume(Volume &volume)
{
    volume.transform(this->getMatrix());
    volume.setInfinite(true);
/*
    Pnt3f min, max;
    volume.getBounds(min, max);

    Vec3f  dia    = max - min;
    Pnt3f  center = min + dia * .5;
    Real32 extend = dia.maxValue();

    dia.setValues(extend * 10.f, extend * 10.f, extend * 10.f);

    volume.extendBy( center - dia );
    volume.extendBy( center + dia );
*/
}

void ConstantSizeTransform::accumulateMatrix(Matrix &result)
{
    result.mult(this->getTransform());
}

/*------------------------- calc matrix ---------------------------------*/

void ConstantSizeTransform::calcMatrix(Action *action)
{
    RenderAction* a = dynamic_cast<RenderAction *>(action);

    RenderPartition* pPart = a->getActivePartition();
    DrawEnv&         oEnv  = pPart->getDrawEnv();

    Int32 vpWidth  = pPart->getViewportWidth ();
    Int32 vpHeight = pPart->getViewportHeight();

    const Matrix& matSSFromES = oEnv.getVPCameraProjection();
    const Matrix& matSSFromWS = oEnv.getVPWorldToScreen();
    const Matrix& camToWorld  = oEnv.getVPCameraToWorld();
    const Matrix& matrix      = getMatrix();

    Matrix transform = pPart->getMatrixStackTop().second;
    transform.mult(matrix);
    transform.multLeft(camToWorld);

    Real32 dist = 0.f;

    bool isOrthographicProjection = false;

    Real32 m32 = matSSFromES[2][3];
    Real32 m33 = matSSFromES[3][3];

    if (osgAbs(m32) < Eps && osgAbs(m33 - 1.f) < Eps)
    {
        isOrthographicProjection = true;
    }
    
    if (isOrthographicProjection)
    {
        Matrix matWSFromSS;
        matSSFromWS.inverse(matWSFromSS);

        Vec3f Vss, Vws;
        Vss = Vec3f(1,0,0);
        matWSFromSS.multFull(Vss, Vws);
        Vws.normalize();
        matSSFromWS.multFull(Vws, Vss);

        dist = osgMax(Vss.length() * vpWidth, Eps);
    }
    else
    {
        Pnt3f eyepos(0.f, 0.f, 0.f);
        Pnt3f objpos(0.f, 0.f, 0.f);

        camToWorld.mult(eyepos, eyepos);
        transform .mult(objpos, objpos);

        Vec3f dir = eyepos - objpos;
        Vec3f up;   up.setValue(camToWorld[0]); up = dir.cross(up);

        up.normalize();
        dir.normalize();

        Vec3f x = up.cross(dir); x.normalize();

        Pnt3f p1, p2; Real32 R = 1.f;
        p1 = objpos;
        p2 = p1 + (R*x);

        matSSFromWS.multFull(p1, p1);
        matSSFromWS.multFull(p2, p2);

        Vec3f d = p2 - p1;

        dist = osgMax(d.length() * vpWidth, Eps);
    }

    Real32 f = this->getDistance() / dist;

    Matrix scale; scale.setScale(f);
    transform.mult(scale);

    if(transform != this->getTransform())
    {
        this->setTransform(transform);
        invalidateVolume();
    }
}

Action::ResultE ConstantSizeTransform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(this->getTransform());

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

Action::ResultE ConstantSizeTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(this->getTransform());

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

Action::ResultE ConstantSizeTransform::renderEnter(Action* action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    calcMatrix(a);

    a->pushVisibility();
    a->pushMatrix    (this->getTransform());

    return Action::Continue;
}

Action::ResultE ConstantSizeTransform::renderLeave(Action* action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->popMatrix();
    a->popVisibility();

    return Action::Continue;
}

OSG_END_NAMESPACE
