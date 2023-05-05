/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGAssimpOptions.h"
#include "OSGAssimpLog.h"

OSG_BEGIN_NAMESPACE

Char8* AssimpOptions::format_collada  = "collada";  // "dae"      COLLADA - Digital Asset Exchange Schema
Char8* AssimpOptions::format_x        = "x";        // "x"        X Files
Char8* AssimpOptions::format_stp      = "stp";      // "stp"      Step Files
Char8* AssimpOptions::format_obj      = "obj";      // "obj"      Wavefront OBJ format
Char8* AssimpOptions::format_objnomtl = "objnomtl"; // "obj"      Wavefront OBJ format without material file
Char8* AssimpOptions::format_stl      = "stl";      // "stl"      Stereolithography
Char8* AssimpOptions::format_stlb     = "stlb";     // "stl"      Stereolithography (binary)
Char8* AssimpOptions::format_ply      = "ply";      // "ply"      Stanford Polygon Library  
Char8* AssimpOptions::format_plyb     = "plyb";     // "ply"      Stanford Polygon Library (binary)
Char8* AssimpOptions::format_3ds      = "3ds";      // "3ds"      Autodesk 3DS (legacy)
Char8* AssimpOptions::format_gltf2    = "gltf2";    // "gltf"     GL Transmission Format v. 2
Char8* AssimpOptions::format_glb2     = "glb2";     // "glb"      GL Transmission Format v. 2 (binary)
Char8* AssimpOptions::format_gltf     = "gltf";     // "gltf"     GL Transmission Format
Char8* AssimpOptions::format_glb      = "glb";      // "glb"      GL Transmission Format (binary) glb
Char8* AssimpOptions::format_assbin   = "assbin";   // "assbin"   Assimp Binary File
Char8* AssimpOptions::format_assxml   = "assxml";   // "assxml"   Assimp XML Document
Char8* AssimpOptions::format_x3d      = "x3d";      // "x3d"      Extensible 3D 
Char8* AssimpOptions::format_fbx      = "fbx";      // "fbx"      Autodesk FBX (binary)
Char8* AssimpOptions::format_fbxa     = "fbxa";     // "fbx"      Autodesk FBX (ascii)   
Char8* AssimpOptions::format_m3d      = "m3d";      // "m3d"      Model 3D (binary)
Char8* AssimpOptions::format_m3da     = "m3da";     // "a3d"      Model 3D (ascii)   
Char8* AssimpOptions::format_3mf      = "3mf";      // "3mf"      The 3MF-File-Format
Char8* AssimpOptions::format_assjson  = "assjson";  // "json"     Assimp JSON Document

AssimpOptions::AssimpOptions(void)
: _postProcessingFlags   (DefaultPostProcessingOptions)
, _preProcessingFlags    (0)
, _examineFlags          (0xFFFF)
, _examineFilename       ()
, _examine               (false)
, _exitOnExamination     (false)
, _invertHeight          (false)
, _invertDisplacement    (true)
, _forceTwosided         (false)
, _forceOpacityCorrection(true)
, _forceTexCoord0        (false)
, _transformUVCoords     (false)
, _writeMtyOnObjExport   (false)
, _globalScaleOnImport   (1.f)
, _shadingModel          (0)
, _writeFormatIdentifier ()
, _textureSubDirectory   ("textures")
, _transformZToYOnExport (false)
, _transformYToZOnImport (false)
, _logMaterialDescOnWrite(getEnvBoolOption("OSG_LOG_ASSIMP_MATERIAL_ON_WRITE"))
, _logMaterialDescOnRead (getEnvBoolOption("OSG_LOG_ASSIMP_MATERIAL_ON_READ"))
{
}

AssimpOptions::AssimpOptions(const OptionSet &optSet)
: _postProcessingFlags   (DefaultPostProcessingOptions)
, _preProcessingFlags    (0)
, _examineFlags          (0xFFFF)
, _examineFilename       ()
, _examine               (false)
, _exitOnExamination     (false)
, _invertHeight          (false)
, _invertDisplacement    (true)
, _forceTwosided         (false)
, _forceOpacityCorrection(true)
, _forceTexCoord0        (false)
, _transformUVCoords     (false)
, _writeMtyOnObjExport   (false)
, _globalScaleOnImport   (1.f)
, _shadingModel          (0)
, _writeFormatIdentifier ()
, _textureSubDirectory   ("textures")
, _transformZToYOnExport (false)
, _transformYToZOnImport (false)
, _logMaterialDescOnWrite(getEnvBoolOption("OSG_LOG_ASSIMP_MATERIAL_ON_WRITE"))
, _logMaterialDescOnRead (getEnvBoolOption("OSG_LOG_ASSIMP_MATERIAL_ON_READ"))
{
    parseOptions(optSet);
}

AssimpOptions::~AssimpOptions(void)
{
}

void AssimpOptions::parseOptions(const OptionSet &optSet)
{
    OSG_ASSIMP_LOG(("AssimpOptions::parseOptions\n"));

    IOFileTypeBase::getOptionAs<UInt32>(
        optSet, "postProcessingFlags", _postProcessingFlags);

    IOFileTypeBase::getOptionAs<UInt32>(
        optSet, "preProcessingFlags", _preProcessingFlags);

    IOFileTypeBase::getOptionAs<UInt32>(
        optSet, "examineFlags", _examineFlags);

    IOFileTypeBase::getOptionAs<std::string>(
        optSet, "examineFilename", _examineFilename);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "examine", _examine);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "exitOnExamination", _exitOnExamination);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "invertHeight", _invertHeight);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "invertDisplacement", _invertDisplacement);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "forceTwosided", _forceTwosided);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "forceOpacityCorrection", _forceOpacityCorrection);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "transformZToYOnExport", _transformZToYOnExport);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "transformYToZOnImport", _transformYToZOnImport);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "forceTexCoord0", _forceTexCoord0);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "transformUVCoords", _transformUVCoords);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "writeMtyOnObjExport", _writeMtyOnObjExport);

    IOFileTypeBase::getOptionAs<float>(
        optSet, "globalScaleOnImport", _globalScaleOnImport);

    IOFileTypeBase::getOptionAs<UInt32>(
        optSet, "shadingModel", _shadingModel);

    IOFileTypeBase::getOptionAs<std::string>(
        optSet, "writeFormatIdentifier", _writeFormatIdentifier);

    IOFileTypeBase::getOptionAs<std::string>(
        optSet, "textureSubDirectory", _textureSubDirectory);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "logMaterialDescOnWrite", _logMaterialDescOnWrite);

    IOFileTypeBase::getOptionAs<bool>(
        optSet, "logMaterialDescOnRead", _logMaterialDescOnRead);
}

UInt32 AssimpOptions::getPostProcessingFlags(void) const
{
    return _postProcessingFlags;
}

void AssimpOptions::setPostProcessingFlags(UInt32 value)
{
    _postProcessingFlags = value;
}

UInt32 AssimpOptions::getPreProcessingFlags(void) const
{
    return _preProcessingFlags;
}

void AssimpOptions::setPreProcessingFlags(UInt32 value)
{
    _preProcessingFlags = value;
}

UInt32 AssimpOptions::getExamineFlags(void) const
{
    return _examineFlags;
}

bool AssimpOptions::hasExamineFlag(Examine flag ) const
{
    if ((_examineFlags & flag) == 0)
        return false;
    else
        return true;
}

void AssimpOptions::setExamineFlags(UInt32 value)
{
    _examineFlags = value;
}

const std::string& AssimpOptions::getExamineFilename(void) const
{
    return _examineFilename;
}

void AssimpOptions::setExamineFilename(const std::string& value)
{
    _examineFilename = value;
}

bool AssimpOptions::getExamine(void) const
{
    return _examine;
}

void AssimpOptions::setExamine(bool value)
{
    _examine = value;
}

bool AssimpOptions::getExitOnExamination(void) const
{
    return _exitOnExamination;
}

void AssimpOptions::setExitOnExamination(bool value)
{
    _exitOnExamination = value;
}

bool AssimpOptions::getInvertHeight(void) const
{
    return _invertHeight;
}

void AssimpOptions::setInvertHeight(bool value)
{
    _invertHeight = value;
}

bool AssimpOptions::getInvertDisplacement(void) const
{
    return _invertDisplacement;
}

void AssimpOptions::setInvertDisplacement(bool value)
{
    _invertDisplacement = value;
}

bool AssimpOptions::getForceTwosided(void) const
{
    return _forceTwosided;
}

void AssimpOptions::setForceTwosided(bool value)
{
    _forceTwosided = value;
}

bool AssimpOptions::getForceOpacityCorrection(void) const
{
    return _forceOpacityCorrection;
}

void AssimpOptions::setForceOpacityCorrection(bool value)
{
    _forceOpacityCorrection = value;
}

bool AssimpOptions::getForceTexCoord0(void) const
{
    return _forceTexCoord0;
}

void AssimpOptions::setForceTexCoord0(bool value)
{
    _forceTexCoord0 = value;
}

bool AssimpOptions::getTransformUVCoords(void) const
{
    return _transformUVCoords;
}

void AssimpOptions::setTransformUVCoords(bool value)
{
    _transformUVCoords = value;
}

bool AssimpOptions::getWriteMtyOnObjExport(void) const
{
    return _writeMtyOnObjExport;
}

void AssimpOptions::setWriteMtyOnObjExport(bool value)
{
    _writeMtyOnObjExport = value;
}

Real32 AssimpOptions::getGlobalScaleOnImport(void) const
{
    return _globalScaleOnImport;
}

void AssimpOptions::setGlobalScaleOnImport(Real32 value)
{
    _globalScaleOnImport = value;
}

bool AssimpOptions::getTransformZToYOnExport(void) const
{
    return _transformZToYOnExport;
}

void AssimpOptions::setTransformZToYOnExport(bool value)
{
    _transformZToYOnExport = value;
}

bool AssimpOptions::getTransformYToZOnImport(void) const
{
    return _transformYToZOnImport;
}

void AssimpOptions::setTransformYToZOnImport(bool value)
{
    _transformYToZOnImport = value;
}

UInt32 AssimpOptions::getShadingModel(void) const
{
    return _shadingModel;
}

void AssimpOptions::setShadingModel(UInt32 value)
{
    _shadingModel = value;
}

const std::string& AssimpOptions::getWriteFormatIdentifier(void) const
{
    return _writeFormatIdentifier;
}

void AssimpOptions::setWriteFormatIdentifier(const std::string& value)
{
    _writeFormatIdentifier = value;
}

const std::string& AssimpOptions::getTextureSubDirectory(void) const
{
    return _textureSubDirectory;
}

void AssimpOptions::setTextureSubDirectory(const std::string& value)
{
    _textureSubDirectory = value;
}

bool AssimpOptions::getLogMaterialDescOnWrite(void) const
{
    return _logMaterialDescOnWrite;
}

void AssimpOptions::setLogMaterialDescOnWrite(bool value)
{
    _logMaterialDescOnRead = value;
}

bool AssimpOptions::getLogMaterialDescOnRead(void) const
{
    return _logMaterialDescOnRead;
}

void AssimpOptions::setLogMaterialDescOnRead(bool value)
{
    _logMaterialDescOnRead = value;
}

bool AssimpOptions::getEnvBoolOption(const Char8* option)
{
    Char8 *szEnvVal = getenv(option);

    if(szEnvVal != NULL)
    {
        return true;
    }

    return false;
}

OSG_END_NAMESPACE
