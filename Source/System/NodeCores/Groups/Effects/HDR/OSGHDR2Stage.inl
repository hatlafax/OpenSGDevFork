/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
void HDR2Stage::renderQuad()
{
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(-1.f, 1.f);
        glVertex2f(-1.f,-1.f);
        glVertex2f( 1.f,-1.f);

        glVertex2f(-1.f, 1.f);
        glVertex2f( 1.f,-1.f);
        glVertex2f( 1.f, 1.f);
    }
    glEnd();
}

inline
Real32 HDR2Stage::getFilmicShoulderStrenght() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicShoulderStrenghtId];
}

inline
Real32 HDR2Stage::getFilmicLinearStrength() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicLinearStrengthId];
}

inline
Real32 HDR2Stage::getFilmicLinearAngle() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicLinearAngleId];
}

inline
Real32 HDR2Stage::getFilmicToeStrength() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicToeStrengthId];
}

inline
Real32 HDR2Stage::getFilmicToeNumerator() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicToeNumeratorId];
}

inline
Real32 HDR2Stage::getFilmicToeDenominator() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicToeDenominatorId];
}

inline
Real32 HDR2Stage::getFilmicLinearWhite() const
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    return _mfFilmicCurveParameters[FilmicLinearWhiteId];
}

inline
void HDR2Stage::setFilmicShoulderStrenght(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);
    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicShoulderStrenghtId] = value;
}

inline
void HDR2Stage::setFilmicLinearStrength(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicLinearStrengthId] = value;
}

inline
void HDR2Stage::setFilmicLinearAngle(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicLinearAngleId] = value;
}

inline
void HDR2Stage::setFilmicToeStrength(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicToeStrengthId] = value;
}

inline
void HDR2Stage::setFilmicToeNumerator(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicToeNumeratorId] = value;
}

inline
void HDR2Stage::setFilmicToeDenominator(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicToeDenominatorId] = value;
}

inline
void HDR2Stage::setFilmicLinearWhite(Real32 value)
{
    OSG_ASSERT(_mfFilmicCurveParameters.size() == FilmicCurveParameterAccessNumEntries);

    editMField(FilmicCurveParametersFieldMask, _mfFilmicCurveParameters);

    _mfFilmicCurveParameters[FilmicLinearWhiteId] = value;
}

OSG_END_NAMESPACE
