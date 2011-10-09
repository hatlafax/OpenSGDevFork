/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class AnimTimeSensor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &AnimTimeSensorBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 AnimTimeSensorBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 AnimTimeSensorBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the AnimTimeSensor::_sfEnabled field.

inline
bool &AnimTimeSensorBase::editEnabled(void)
{
    editSField(EnabledFieldMask);

    return _sfEnabled.getValue();
}

//! Get the value of the AnimTimeSensor::_sfEnabled field.
inline
      bool  AnimTimeSensorBase::getEnabled(void) const
{
    return _sfEnabled.getValue();
}

//! Set the value of the AnimTimeSensor::_sfEnabled field.
inline
void AnimTimeSensorBase::setEnabled(const bool value)
{
    editSField(EnabledFieldMask);

    _sfEnabled.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfIsActive field.

inline
bool &AnimTimeSensorBase::editIsActive(void)
{
    editSField(IsActiveFieldMask);

    return _sfIsActive.getValue();
}

//! Get the value of the AnimTimeSensor::_sfIsActive field.
inline
      bool  AnimTimeSensorBase::getIsActive(void) const
{
    return _sfIsActive.getValue();
}

//! Set the value of the AnimTimeSensor::_sfIsActive field.
inline
void AnimTimeSensorBase::setIsActive(const bool value)
{
    editSField(IsActiveFieldMask);

    _sfIsActive.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfLoop field.

inline
bool &AnimTimeSensorBase::editLoop(void)
{
    editSField(LoopFieldMask);

    return _sfLoop.getValue();
}

//! Get the value of the AnimTimeSensor::_sfLoop field.
inline
      bool  AnimTimeSensorBase::getLoop(void) const
{
    return _sfLoop.getValue();
}

//! Set the value of the AnimTimeSensor::_sfLoop field.
inline
void AnimTimeSensorBase::setLoop(const bool value)
{
    editSField(LoopFieldMask);

    _sfLoop.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfForward field.

inline
bool &AnimTimeSensorBase::editForward(void)
{
    editSField(ForwardFieldMask);

    return _sfForward.getValue();
}

//! Get the value of the AnimTimeSensor::_sfForward field.
inline
      bool  AnimTimeSensorBase::getForward(void) const
{
    return _sfForward.getValue();
}

//! Set the value of the AnimTimeSensor::_sfForward field.
inline
void AnimTimeSensorBase::setForward(const bool value)
{
    editSField(ForwardFieldMask);

    _sfForward.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfStartTime field.

inline
Time &AnimTimeSensorBase::editStartTime(void)
{
    editSField(StartTimeFieldMask);

    return _sfStartTime.getValue();
}

//! Get the value of the AnimTimeSensor::_sfStartTime field.
inline
const Time &AnimTimeSensorBase::getStartTime(void) const
{
    return _sfStartTime.getValue();
}

//! Set the value of the AnimTimeSensor::_sfStartTime field.
inline
void AnimTimeSensorBase::setStartTime(const Time &value)
{
    editSField(StartTimeFieldMask);

    _sfStartTime.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfStopTime field.

inline
Time &AnimTimeSensorBase::editStopTime(void)
{
    editSField(StopTimeFieldMask);

    return _sfStopTime.getValue();
}

//! Get the value of the AnimTimeSensor::_sfStopTime field.
inline
const Time &AnimTimeSensorBase::getStopTime(void) const
{
    return _sfStopTime.getValue();
}

//! Set the value of the AnimTimeSensor::_sfStopTime field.
inline
void AnimTimeSensorBase::setStopTime(const Time &value)
{
    editSField(StopTimeFieldMask);

    _sfStopTime.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfTime field.

inline
Time &AnimTimeSensorBase::editTime(void)
{
    editSField(TimeFieldMask);

    return _sfTime.getValue();
}

//! Get the value of the AnimTimeSensor::_sfTime field.
inline
const Time &AnimTimeSensorBase::getTime(void) const
{
    return _sfTime.getValue();
}

//! Set the value of the AnimTimeSensor::_sfTime field.
inline
void AnimTimeSensorBase::setTime(const Time &value)
{
    editSField(TimeFieldMask);

    _sfTime.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfCycleLength field.

inline
Time &AnimTimeSensorBase::editCycleLength(void)
{
    editSField(CycleLengthFieldMask);

    return _sfCycleLength.getValue();
}

//! Get the value of the AnimTimeSensor::_sfCycleLength field.
inline
const Time &AnimTimeSensorBase::getCycleLength(void) const
{
    return _sfCycleLength.getValue();
}

//! Set the value of the AnimTimeSensor::_sfCycleLength field.
inline
void AnimTimeSensorBase::setCycleLength(const Time &value)
{
    editSField(CycleLengthFieldMask);

    _sfCycleLength.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfTimeScale field.

inline
Real32 &AnimTimeSensorBase::editTimeScale(void)
{
    editSField(TimeScaleFieldMask);

    return _sfTimeScale.getValue();
}

//! Get the value of the AnimTimeSensor::_sfTimeScale field.
inline
      Real32  AnimTimeSensorBase::getTimeScale(void) const
{
    return _sfTimeScale.getValue();
}

//! Set the value of the AnimTimeSensor::_sfTimeScale field.
inline
void AnimTimeSensorBase::setTimeScale(const Real32 value)
{
    editSField(TimeScaleFieldMask);

    _sfTimeScale.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfFraction field.

inline
Real32 &AnimTimeSensorBase::editFraction(void)
{
    editSField(FractionFieldMask);

    return _sfFraction.getValue();
}

//! Get the value of the AnimTimeSensor::_sfFraction field.
inline
      Real32  AnimTimeSensorBase::getFraction(void) const
{
    return _sfFraction.getValue();
}

//! Set the value of the AnimTimeSensor::_sfFraction field.
inline
void AnimTimeSensorBase::setFraction(const Real32 value)
{
    editSField(FractionFieldMask);

    _sfFraction.setValue(value);
}
//! Get the value of the AnimTimeSensor::_sfAnimTime field.

inline
Real32 &AnimTimeSensorBase::editAnimTime(void)
{
    editSField(AnimTimeFieldMask);

    return _sfAnimTime.getValue();
}

//! Get the value of the AnimTimeSensor::_sfAnimTime field.
inline
      Real32  AnimTimeSensorBase::getAnimTime(void) const
{
    return _sfAnimTime.getValue();
}

//! Set the value of the AnimTimeSensor::_sfAnimTime field.
inline
void AnimTimeSensorBase::setAnimTime(const Real32 value)
{
    editSField(AnimTimeFieldMask);

    _sfAnimTime.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void AnimTimeSensorBase::execSync (      AnimTimeSensorBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
        _sfEnabled.syncWith(pFrom->_sfEnabled);

    if(FieldBits::NoField != (IsActiveFieldMask & whichField))
        _sfIsActive.syncWith(pFrom->_sfIsActive);

    if(FieldBits::NoField != (LoopFieldMask & whichField))
        _sfLoop.syncWith(pFrom->_sfLoop);

    if(FieldBits::NoField != (ForwardFieldMask & whichField))
        _sfForward.syncWith(pFrom->_sfForward);

    if(FieldBits::NoField != (StartTimeFieldMask & whichField))
        _sfStartTime.syncWith(pFrom->_sfStartTime);

    if(FieldBits::NoField != (StopTimeFieldMask & whichField))
        _sfStopTime.syncWith(pFrom->_sfStopTime);

    if(FieldBits::NoField != (TimeFieldMask & whichField))
        _sfTime.syncWith(pFrom->_sfTime);

    if(FieldBits::NoField != (CycleLengthFieldMask & whichField))
        _sfCycleLength.syncWith(pFrom->_sfCycleLength);

    if(FieldBits::NoField != (TimeScaleFieldMask & whichField))
        _sfTimeScale.syncWith(pFrom->_sfTimeScale);

    if(FieldBits::NoField != (FractionFieldMask & whichField))
        _sfFraction.syncWith(pFrom->_sfFraction);

    if(FieldBits::NoField != (AnimTimeFieldMask & whichField))
        _sfAnimTime.syncWith(pFrom->_sfAnimTime);
}
#endif


inline
const Char8 *AnimTimeSensorBase::getClassname(void)
{
    return "AnimTimeSensor";
}
OSG_GEN_CONTAINERPTR(AnimTimeSensor);

OSG_END_NAMESPACE

