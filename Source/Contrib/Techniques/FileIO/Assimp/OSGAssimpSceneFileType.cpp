/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <codecvt>
#include <locale>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
//#include <boost/locale.hpp>

#include "OSGConfig.h"
#include "OSGAssimpSceneFileType.h"

#include "OSGAssimpLog.h"
#include "OSGAssimpExaminer.h"
#include "OSGAssimpMaterialProcessor.h"
#include "OSGAssimpMeshProcessor.h"
#include "OSGAssimpNodeProcessor.h"
#include "OSGAssimpOptions.h"
#include "OSGDescMaterial.h"
#include "OSGDescMaterialManager.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGGeoOptimization.h"
#include "OSGGroup.h"
#include "OSGImageFileHandler.h"
#include "OSGMaterialChunkOverrideGroup.h"
#include "OSGMaterialDesc.h"
#include "OSGMaterialGroup.h"
#include "OSGMatrix.h"
#include "OSGMultiSwitch.h"
#include "OSGNameAttachment.h"
#include "OSGNode.h"
#include "OSGPathHandler.h"
#include "OSGQuaternion.h"
#include "OSGSceneFileHandler.h"
#include "OSGSimpleTexturedMaterial.h"
#include "OSGSwitch.h"
#include "OSGTextureDesc.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGTriangleIterator.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGVisitSubTree.h"

#ifdef OSG_WITH_ASSIMP
#pragma warning( push )
#pragma warning(disable : 4800)

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#include <assimp/ProgressHandler.hpp>

#include <assimp/color4.h>
#include <assimp/importerdesc.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/metadata.h>
#include <assimp/pbrmaterial.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

#pragma warning( pop )
#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

#ifdef WIN32
static std::string from_acp_to_utf8(const std::string& str)
{
    int sz = ::MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), NULL, 0);

    if (sz > 0)
    {
        std::wstring tmp(sz, 0);
	sz = ::MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), &tmp[0], sz);

        if (sz > 0)
        {
            int sz = ::WideCharToMultiByte(CP_UTF8, 0, &tmp[0], (int)tmp.size(), NULL, 0, NULL, NULL);

            if (sz > 0)
            {
                std::string result(sz, 0);
	
                ::WideCharToMultiByte(CP_UTF8, 0, &tmp[0], (int)tmp.size(), &result[0], (int)result.size(), NULL, NULL);

                if (sz > 0)
                    return result;
            }
        }
    }

    return std::string();
}
#endif

#ifdef OSG_WITH_ASSIMP
class ProgressHandler : public Assimp::ProgressHandler
{
public:
     bool Update(float percentage)
     {
        if (percentage >= 0)
        {
            if (_read)
                SceneFileHandler::the()->updateReadProgress(static_cast<UInt32>(100.f * percentage));
            else
                SceneFileHandler::the()->updateWriteProgress(static_cast<UInt32>(100.f * percentage));
        }
        else
        {
            _cnt++;
            if (_cnt >= 100)
                _cnt = 0;

            if (_read)
                SceneFileHandler::the()->updateReadProgress(_cnt);
            else
                SceneFileHandler::the()->updateWriteProgress(_cnt);
        }

        return true;
     }

     ProgressHandler(bool read) : _read(read), _cnt(0) {}

private:
    UInt32  _cnt;
    bool    _read;
};

class LogStream : public Assimp::LogStream
{
public:
             LogStream() : ss() {}
    virtual ~LogStream() {}

    virtual void write(const char* message)
    {
        ss << message;
    }

    std::string getLog() { ss << std::flush; return ss.str(); }

private:
    std::stringstream ss;
};
#endif // OSG_WITH_ASSIMP

#ifdef OSG_WITH_ASSIMP
//
// Supported import extensions
//
const Char8 *AssimpSceneFileType::_suffixA[] =  
    { 
            "3ds", "prj",                       // 3D Studio Max 3DS-Format
            "3mf",                              // D3MF-Format
            "ac", "ac3d", "acc",                // AC3D AC-Format
            "amf",                              // AMF-Format
            "ase", "ask",                       // 3D Studio Max ASE-Format
            "assbin",                           // Assimp Binary ASSBIN-Format
            "b3d",                              // B3D-Format
            "blend",                            // BLENDER-Format
            "bvh",                              // Biovision BVH-Format
            "c4d",                              // C4D-Format
            "cob", "scn",                       // TrueSpace COB-Format
            "dae", "zae",                       // COLLADA-Format
            "csm",                              // CharacterStudio Motion CSM-Format
            "dxf",                              // Autodesk, AutoCAD DXF-Format
            "fbx",                              // Autodesk FBX-Format
            "gltf", "glb",                      // glTF-Format
            "gltf", "glb",                      // gltf2-Format
            "hmp",                              // 3D GameStudio Terrain HMP-Format
            "ifc", "ifczip",                    // Industry Foundation Classes loader IFC-Format
            "stp", "step",                      // Step IFC-Format
            "irr", "irrmesh", "xml",            // Irrlicht Scene IRR-Format
            "lwo", "lxo",                       // LightWave Model LWO-Format
            "lws", "mot",                       // LightWave Scene LWS-Format
            "md2",                              // Quake II MD2-Format
            "md3",                              // Quake III MD3-Format
            "md5anim", "md5mesh", "md5camera",  // Doom 3 MD5-Format
            "mdc",                              // RtCW MDC-Format
            "mdl",                              // Quake I MDL-Format
            "pmx",                              // MMD-Format
            "ms3d",                             // Milkshape 3D MS3D-Format
            "ndo",                              // NDO-Format
            "nff", "enff",                      // Neutral File Format NFF-Format
            "obj",                              // Wavefront Object OBJ-Format
            "off",                              // Object File OFF-Format
            "mesh", "mesh.xml",                 // Ogre MESH-Format
            "ogex",                             // OPENGEX-Format
            "ply", "plyb",                      // Stanford Polygon Library PLY-Format
            "pk3",                              // Quake 3 BSP Q3BSP-Format
            "q3s", "q3o",                       // Quick3D Q3D-Format
            "raw",                              // Raw Triangles RAW-Format
            "sib",                              // SIB-Format
            "smd", "vta",                       // Valve Model SMD-Format
            "stl", "stlb",                      // Stereolithography STL-Format
            "ter",                              // Terragen Terrain TER-Format
            "3d", "uc",                         // UNREAL 3D-Format
            "x3d", "x3db",                      // Extensible X3D-Format
            "x",                                // DirectX X-Format
            "xgl", "zgl", "xml",                // XGL-Format
            "m3d", "a3d",                       // Model 3D M3D-Format
    };

//
// Supported export extensions
//
const Char8 *AssimpSceneFileType::_suffixB[] =  
    { 
            "3ds",          // 3D Studio Max 3DS-Format
            "3mf",          // D3MF-Format
            "assbin",       // Assimp Binary ASSBIN-Format
            "assxml",       // Assimp XML Document ASSXML-Format
            "json",         // Assimp JASON Document JSON-Format
            "dae",          // COLLADA-Format
            "fbx",          // Autodesk FBX-Format
            "gltf", "glb",  // glTF-Format
            "gltf", "glb",  // gltf2-Format
            "stp",          // Step IFC-Format
            "obj",          // Wavefront Object OBJ-Format
            "ply",          // Stanford Polygon Library PLY-Format
            "plyb",         // Stanford Polygon Library PLY-Format
            "stl",          // Stereolithography STL-Format
            "stlb",         // Stereolithography STL-Format
            "x3d",          // Extensible X3D-Format
            "x",            // DirectX X-Format
            "m3d", "a3d",   // Model 3D M3D-Format
    };

#else
const Char8 *AssimpSceneFileType::_suffixA[] =  {};
const Char8 *AssimpSceneFileType::_suffixB[] =  {};
#endif

AssimpSceneFileType::OptStringT AssimpSceneFileType::getExtension(const Char8 *fileNameOrExtension) const
{
    if (fileNameOrExtension)
    {
        const Char8 separator = '.';

        std::string fe = fileNameOrExtension;

        SizeT p = fe.rfind(separator);

        std::string ext;

        if(p != std::string::npos)
        {
            ext = fe.substr(p + 1, fe.length() - p - 1);
        }
        else
        {
            ext = fe; // extension without '.'
        }

        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        return ext;
    }

    return boost::none;
}

bool AssimpSceneFileType::supportExtension(const Char8 *fileNameOrExtension, UInt32 flags) const
{
    if ((getFlags() & flags) == flags)
    {
        OptStringT suffix = getExtension(fileNameOrExtension);

        if (suffix)
        {
            int count = 0;

            if (flags == SceneFileType::OSG_WRITE_SUPPORTED)
            {
                count = (sizeof(_suffixB) / sizeof(const Char8*));
            }
            else
            {
                count = (sizeof(_suffixA) / sizeof(const Char8*));
            }

            for (int i = 0; i < count; ++i)
            {
                if (flags == SceneFileType::OSG_WRITE_SUPPORTED)
                {
                    if (*suffix == _suffixB[i])
                    {
                        return true;
                    }
                }
                else
                {
                    if (*suffix == _suffixA[i])
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//
// The override and overridePriority parameters are used for initialization
// on the very first call of the function.
//
AssimpSceneFileType& AssimpSceneFileType::the(
    bool   override, 
    UInt32 overridePriority)
{
    //
    // Attention:
    //  The implementation of the Assimp scene file type differs from the other OpenSG
    //  scene file types. The reason is that the Assimp scene file type can handle many
    //  file types, especially, file types for which OpenSG already provides scene file
    //  types. For instance the "obj" file format is already handled by the OBJSceneFileType.
    //
    //  A global static AssimpSceneFileType varibale would be subject of global static
    //  initialization ordering and the implentation would define which handler would 
    //  be used for instance for the "obj" file format. This is unwanted. The end user
    //  of the library should be able to decide which handler is going to be used.
    //
    //  The lazy initialization scheme implemented here allows the end user to define
    //  the order of the scene type handlers for which already handlers exist.
    //
    static AssimpSceneFileType _the(_suffixA,
                                    sizeof(_suffixA),
                                    override,
                                    overridePriority,
                                    (   SceneFileType::OSG_READ_SUPPORTED 
                                      | SceneFileType::OSG_WRITE_SUPPORTED 
                                      | SceneFileType::OSG_NOT_ZIP_COMPRESSIBLE
                                      | SceneFileType::OSG_STREAMING_UNSUPPORTED
                                    ));
    return _the;
}

AssimpSceneFileType::AssimpSceneFileType(
    const Char8* suffixArray[],
    UInt16       suffixByteCount,
    bool         override,
    UInt32       overridePriority,
    UInt32       flags)
: SceneFileType(suffixArray,
                suffixByteCount,
                override,
                overridePriority,
                flags)
{
    _nonStreamIO = true;
}

AssimpSceneFileType::AssimpSceneFileType(const AssimpSceneFileType &obj)
: SceneFileType(obj)
{
    _nonStreamIO = true;
}

AssimpSceneFileType::~AssimpSceneFileType(void)
{
}

const Char8 *AssimpSceneFileType::getName(void) const
{
    return "Assimp file loader";
}

NodeTransitPtr AssimpSceneFileType::read(
    std::istream& is,
    const Char8*  file,
    Resolver) const
{
    OSG_ASSIMP_LOG(("AssimpSceneFileType::read\n"));

    // Hack
    //std::ifstream* ifs = dynamic_cast<std::ifstream*>(&is);
    //if(ifs != NULL && ifs->is_open())
    //{
    //    ifs->close();
    //}

    AssimpOptions options(this->getOptions());

    NodeUnrecPtr rootPtr = NULL;

    SceneFileHandler::the()->updateReadProgress(0);

#ifdef OSG_WITH_ASSIMP

    if (supportExtension(file, SceneFileType::OSG_READ_SUPPORTED))
    {
        ProgressHandler progress(true);

        Assimp::Importer importer;
        importer.SetProgressHandler(&progress);

        LogStream* logStream = NULL;

        if (options.getExamine())
        {
            importer.SetPropertyBool(AI_CONFIG_GLOB_MEASURE_TIME, true);

            logStream = new LogStream;

            const unsigned int severity = Assimp::Logger::Debugging
                                        | Assimp::Logger::Info
                                        | Assimp::Logger::Err
                                        | Assimp::Logger::Warn;

            Assimp::Logger::LogSeverity log_severity = Assimp::Logger::VERBOSE;

            Assimp::DefaultLogger::create("", log_severity, 0);

            Assimp::DefaultLogger::get()->attachStream(logStream, severity);
        }

        importer.SetPropertyInteger(AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
        importer.SetPropertyFloat  (AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.f);
        importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE 
                                                           | aiPrimitiveType_POINT);

        importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_COLORS 
                                                          | aiComponent_BONEWEIGHTS 
                                                          | aiComponent_LIGHTS 
                                                          | aiComponent_CAMERAS 
                                                          | aiComponent_ANIMATIONS);

        importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, options.getGlobalScaleOnImport());

        //
        // Assimp does expect an utf8 filename.
        //
        std::string utf8_file = file;
#ifdef WIN32
        std::string encoded_file = file;
        utf8_file = from_acp_to_utf8(encoded_file);
#endif

        const aiScene* scene = importer.ReadFile(utf8_file, options.getPostProcessingFlags());

        std::string importer_name;

        int idx = importer.GetPropertyInteger("importerIndex");
        if (idx >= 0 && idx < importer.GetImporterCount())
        {
            const aiImporterDesc* desc = importer.GetImporterInfo(idx);
            if (desc && desc->mName)
            {
                importer_name = desc->mName;
            }
        }

        bool eval_scene = true;

        if (options.getExamine())
        {
            std::string examineFile = options.getExamineFilename();
            if (examineFile.empty())
            {
                examineFile = std::string(file) + ".examine";
            }

            AssimpExaminer examiner(options, importer_name);
            examiner.setFilename(examineFile);
            examiner.setLog(logStream->getLog());
            examiner.examine(scene);

            Assimp::DefaultLogger::kill();

            eval_scene = !options.getExitOnExamination();
        }

        if (eval_scene)
        {
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                SWARNING << "AssimpSceneFileType::read: Failed '"
                             << importer.GetErrorString() << "'" << std::endl;
            }
            else
            {
                std::string directory = std::string(file);
                directory = directory.substr(0, directory.find_last_of("/\\"));

                bool result;

                if (importer_name == "Stereolithography (STL) Importer")
                {
                    options.setTransformYToZOnImport(false);
                    options.setForceTwosided(true);
                }

                AssimpMaterialProcessor materialProc(options, importer_name, directory);
                result = materialProc.process(scene);

                if (result)
                {
                    AssimpMeshProcessor meshProc(options, importer_name, materialProc);
                    result = meshProc.process(scene);

                    if (result)
                    {
                        AssimpNodeProcessor nodeProc(options, importer_name, meshProc);
                        result = nodeProc.process(scene);

                        if (result)
                        {
                            rootPtr = nodeProc.getRoot();
                        }
                    }
                }

                commitChanges();
            }
        }

        importer.SetProgressHandler(NULL);
    }

#endif // OSG_WITH_ASSIMP

    SceneFileHandler::the()->updateReadProgress(100);

    return NodeTransitPtr(rootPtr);
}

bool AssimpSceneFileType::write(
    Node* const   node, 
    std::ostream& os,
    const Char8*  file) const
{
    bool result = false;


    OSG_ASSIMP_LOG(("AssimpSceneFileType::write\n"));

    AssimpOptions options(this->getOptions());

    //// Hack
    //std::ofstream* ofs = dynamic_cast<std::ofstream*>(&os);
    //if(ofs != NULL  && ofs->is_open())
    //{
    //    ofs->close();
    //}

    SceneFileHandler::the()->updateWriteProgress(0);

#ifdef OSG_WITH_ASSIMP

    if (supportExtension(file, SceneFileType::OSG_WRITE_SUPPORTED))
    {
        ProgressHandler progress(true);

        Assimp::Exporter exporter;
        exporter.SetProgressHandler(&progress);

        LogStream* logStream = NULL;

        if (options.getExamine())
        {
            logStream = new LogStream;

            const unsigned int severity = Assimp::Logger::Debugging
                                        | Assimp::Logger::Info
                                        | Assimp::Logger::Err
                                        | Assimp::Logger::Warn;

            Assimp::Logger::LogSeverity log_severity = Assimp::Logger::VERBOSE;

            Assimp::DefaultLogger::create("", log_severity, 0);

            Assimp::DefaultLogger::get()->attachStream(logStream, severity);
        }

        std::string exporterName;
        std::string formatId;
        std::string extension;

        std::unique_ptr<aiScene> scene;

        bool eval_scene = !options.getExitOnExamination();

        if (eval_scene)
        {
            Assimp::ExportProperties* pProperties = NULL;

            //
            // Remark: The following function call, basically determines the proper exporter.
            //         It uses either a user provided format identifier (see AssimpOptions)
            //         or the extension of the user provided output file name.
            //         In the former case the file extension intrinsic to the exporter might 
            //         differ from the extension of the user provided file name. Generally, the
            //         user file name is always used, but the file content is always determined
            //         by the exporter.
            //         In short: The user file name extension is not used for finding the exporter
            //                   in case that the AssimpOption "writeFormatIdentifier" is set, but
            //                   the exported file is named as requested by the user.
            //
            OptIndexT descIndex = getExportFormatDescriptionIndex(file, exporter, options);

            if (descIndex)
            {
                const aiExportFormatDesc* desc = exporter.GetExportFormatDescription(*descIndex);
                exporterName  = desc->description;
                formatId      = desc->id;
                extension     = desc->fileExtension;

                BoostPath outFile(file);
                outFile.make_preferred();
                outFile= boost::filesystem::absolute(outFile);

                BoostPath destination = outFile.parent_path();

                destination.make_preferred();
                destination = boost::filesystem::absolute(destination);

                 try
                {
                    scene = getAssimpScene(node, options, exporterName, formatId, destination, outFile);

                    if (scene)
                    {
                        //
                        // Assimp does expect an utf8 filename.
                        //
                        std::string utf8_file = file;
#ifdef WIN32
                        std::string encoded_file = file;
                        utf8_file = from_acp_to_utf8(encoded_file);
#endif
                        aiReturn ret = exporter.Export(scene.get(), formatId, utf8_file, options.getPreProcessingFlags(), pProperties);

                        result = ret == AI_SUCCESS ?  true : false;
                    }
                }
                catch (const boost::filesystem::filesystem_error&)
                {
                }
            }
        }

        if (options.getExamine())
        {
            std::string examineFile = options.getExamineFilename();
            if (examineFile.empty())
            {
                examineFile = std::string(file) + ".examine";
            }

            AssimpExaminer examiner(options, exporterName);
            examiner.setFilename(examineFile);
            examiner.setLog(logStream->getLog());

            if (scene)
            {
                examiner.examine(scene.get());
            }

            Assimp::DefaultLogger::kill();
        }

        exporter.SetProgressHandler(NULL);
    }

#endif // OSG_WITH_ASSIMP

    SceneFileHandler::the()->updateWriteProgress(100);

    return result;
}

#ifdef OSG_WITH_ASSIMP

std::unique_ptr<aiScene> AssimpSceneFileType::getAssimpScene(
    Node* const          node, 
    const AssimpOptions& options, 
    const std::string&   exporter,
    const std::string&   formatId,
    const BoostPath&     destination,
    const BoostPath&     file) const
{
    std::unique_ptr<aiScene> scene(new aiScene);

    if (node && node->getCore())
    {
        SceneWriteData data(options, exporter, formatId, destination, file);

        handleAssociatedFiles(data);

        if (options.getTransformZToYOnExport())
        {
            Quaternion q(Vec3f(0.f, 0.f, 1.f), Vec3f(0.f, 1.f, 0.f));
            Matrix rotZToY; rotZToY.setRotate(q);
            data.vecMatrices.push_back(rotZToY);
        }

        scene->mRootNode = handleNode(data, node, NULL);

        if (options.getTransformZToYOnExport())
        {
            data.vecMatrices.pop_back();
        }

        if (options.getForceTexCoord0())
        {
            bool clear_trafo = options.getTransformUVCoords();

            std::set<UInt32>::const_iterator iter = data.setPrimaryMaterials.begin();
            std::set<UInt32>::const_iterator  end = data.setPrimaryMaterials.end  ();

            for (; iter != end; ++iter)
            {
                setPrimaryMaterialData(data, *iter, clear_trafo);
            }
        }

        unsigned int mFlags = 0;

        if (!data.vecAiMeshes.empty())
        {
            scene->mMeshes    = new aiMesh*[data.vecAiMeshes.size()];
            scene->mNumMeshes = static_cast<unsigned int>(data.vecAiMeshes.size());

            for (std::size_t i = 0; i < data.vecAiMeshes.size(); ++i)
            {
                scene->mMeshes[i] = data.vecAiMeshes[i];
            }
        }
        else
        {
            scene->mMeshes    = NULL;
            scene->mNumMeshes = 0;

            mFlags |= AI_SCENE_FLAGS_INCOMPLETE;
        }

        if (!data.vecAiMaterials.empty())
        {
            scene->mMaterials    = new aiMaterial*[data.vecAiMaterials.size()];
            scene->mNumMaterials = static_cast<unsigned int>(data.vecAiMaterials.size());

            for (std::size_t i = 0; i < data.vecAiMaterials.size(); ++i)
            {
                scene->mMaterials[i] = data.vecAiMaterials[i];
            }
        }
        else
        {
            scene->mMaterials    = NULL;
            scene->mNumMaterials = 0;
        }

        if (!data.vecAiTextures.empty())
        {
            scene->mTextures    = new aiTexture*[data.vecAiTextures.size()];
            scene->mNumTextures = static_cast<unsigned int>(data.vecAiTextures.size());

            for (std::size_t i = 0; i < data.vecAiTextures.size(); ++i)
            {
                scene->mTextures[i] = data.vecAiTextures[i];
            }
        }
        else
        {
            scene->mTextures    = NULL;
            scene->mNumTextures = 0;
        }

        scene->mFlags = mFlags;
    }

    return scene;
}

void AssimpSceneFileType::handleAssociatedFiles(SceneWriteData& data) const
{
    if (data.formatId == AssimpOptions::format_obj)
    {
        handleAssociatedFilesOBJ(data);
    }
}

void AssimpSceneFileType::handleAssociatedFilesOBJ(SceneWriteData& data) const
{
    BoostPath mtyFile = data.file;
    mtyFile.replace_extension(".mty");

    if (data.options.getWriteMtyOnObjExport())
    {
        data.spMtyStream = OutStreamPtr(new boost::filesystem::ofstream(mtyFile));
    }

    if (data.spMtyStream)
    {
        OutStreamT& os = *data.spMtyStream;

        //
        // Write a preamble
        //
        os << "#" << std::endl
           << "# written by CADdy++ CAD application from DataSolid GmbH Germany" << std::endl
           << "# http://www.DataSolid.com" << std::endl
           << "#" << std::endl
           << std::endl;
    }
}

aiNode* AssimpSceneFileType::handleNode(SceneWriteData& data, Node* const node, aiNode* parent) const
{
    if (!node) return NULL;

    NodeCore* core = node->getCore();
    if (!core) return NULL;

    aiNode* ai_node = new aiNode;

    ai_node->mParent = parent;

    if (OSG::getName(node))
    {
        ai_node->mName = OSG::getName(node);
    }

    ai_node->mNumChildren = 0;
    ai_node->mNumMeshes   = 0;

    ai_node->mChildren    = NULL;
    ai_node->mMeshes      = NULL;

    ai_node->mMetaData    = NULL;

    std::vector<aiNode*> vecChildAiNodes;

    MFUnrecChildNodePtr::const_iterator iter;
    MFUnrecChildNodePtr::const_iterator end;

    if (core->getType().isDerivedFrom(MaterialGroup::getClassType()))
    {
        MaterialGroup* mg = dynamic_cast<MaterialGroup*>(core);

        data.stackMaterials.push(mg->getMaterial());

        iter = node->getMFChildren()->begin();
        end  = node->getMFChildren()->end  ();

        for(; iter != end; ++iter)
        {
            aiNode* ai_child = handleNode(data, (*iter), ai_node);
            if (ai_child)
                vecChildAiNodes.push_back(ai_child);
        }

        data.stackMaterials.pop();
    }
    else
    if (core->getType().isDerivedFrom(MaterialChunkOverrideGroup::getClassType()))
    {
        MaterialChunkOverrideGroup* cmog = dynamic_cast<MaterialChunkOverrideGroup*>(core);

        data.stackOverrideMaterials.push(cmog->getMaterial());

        iter = node->getMFChildren()->begin();
        end  = node->getMFChildren()->end  ();

        for(; iter != end; ++iter)
        {
            aiNode* ai_child = handleNode(data, (*iter), ai_node);
            if (ai_child)
                vecChildAiNodes.push_back(ai_child);
        }

        data.stackOverrideMaterials.pop();
    }
    else
    if (core->getType().isDerivedFrom(Geometry::getClassType()))
    {
        handleGeometry(data, node, ai_node);
    }
    else
    if (core->getType().isDerivedFrom(VisitSubTree::getClassType()))
    {
        VisitSubTree* c = dynamic_cast<VisitSubTree*>(core);
        if (c)
        {
            Node* visit = c->getSubTreeRoot();

            if (visit)
            {
                Matrix mat = node->getToWorld();

                data.vecMatrices.push_back(mat);

                aiNode* ai_child = handleNode(data, visit, ai_node);
                if (ai_child)
                    vecChildAiNodes.push_back(ai_child);

                data.vecMatrices.pop_back();
            }
        }
    }
    else
    if (core->getType().isDerivedFrom(MultiSwitch::getClassType()))
    {
        MultiSwitch* c = dynamic_cast<MultiSwitch*>(core);
        if (c)
        {
            if (c->getSwitchMode() == MultiSwitch::ALL)
            {
                iter = node->getMFChildren()->begin();
                end  = node->getMFChildren()->end  ();

                for(; iter != end; ++iter)
                {
                    aiNode* ai_child = handleNode(data, (*iter), ai_node);
                    if (ai_child)
                        vecChildAiNodes.push_back(ai_child);
                }
            }
            else
            if (c->getSwitchMode() == MultiSwitch::CHOICES)
            {
                UInt32 numNodes = node->getNChildren();

                MultiSwitch::MFChoicesType::const_iterator choiceIt  = c->getMFChoices()->begin();
                MultiSwitch::MFChoicesType::const_iterator choiceEnd = c->getMFChoices()->end();

                for(; choiceIt != choiceEnd; ++choiceIt)
                {
                    if(*choiceIt < numNodes)
                    {
                        Node* child = node->getChild(*choiceIt);
                        if (child)
                        {
                            aiNode* ai_child = handleNode(data, child, ai_node);
                            if (ai_child)
                                vecChildAiNodes.push_back(ai_child);
                        }
                    }
                }

            }
        }
    }
    else
    if (core->getType().isDerivedFrom(Switch::getClassType()))
    {
        Switch* c = dynamic_cast<Switch*>(core);
        if (c)
        {
            if (c->getChoice() != Switch::NONE)
            {
                if (c->getChoice() == Switch::ALL)
                {
                    iter = node->getMFChildren()->begin();
                    end  = node->getMFChildren()->end  ();

                    for(; iter != end; ++iter)
                    {
                        aiNode* ai_child = handleNode(data, (*iter), ai_node);
                        if (ai_child)
                            vecChildAiNodes.push_back(ai_child);
                    }
                }
                else
                {
                    UINT32 idx = static_cast<UINT32>(c->getChoice());

                    if (idx >= 0 && idx < node->getNChildren())
                    {
                        Node* child = node->getChild(idx);
                        if (child)
                        {
                            aiNode* ai_child = handleNode(data, child, ai_node);
                            if (ai_child)
                                vecChildAiNodes.push_back(ai_child);
                        }
                    }
                }
            }
        }
    }
    else
    if (core->getType().isDerivedFrom(Group::getClassType()))
    {
        iter = node->getMFChildren()->begin();
        end  = node->getMFChildren()->end  ();

        for(; iter != end; ++iter)
        {
            aiNode* ai_child = handleNode(data, (*iter), ai_node);
            if (ai_child)
                vecChildAiNodes.push_back(ai_child);
        }
    }

    if (!vecChildAiNodes.empty())
    {
        ai_node->mNumChildren = static_cast<unsigned int>(vecChildAiNodes.size());
        ai_node->mChildren    = new aiNode*[vecChildAiNodes.size()];

        for (std::size_t i = 0; i < vecChildAiNodes.size(); ++i)
        {
            ai_node->mChildren[i] = vecChildAiNodes[i];
        }
    }

    return ai_node;
}

void AssimpSceneFileType::handleGeometry(SceneWriteData& data, Node* const node, aiNode* ai_node) const
{
    if (!node) return;

    NodeCore* core = node->getCore();
    if (!core) return;

    Geometry* geom = dynamic_cast<Geometry*>(core);

    //
    // Precondition for geometry handling: geometry must be single indexed
    //
    if (geom && !geom->isSingleIndex())
    {
        makeSingleIndexed(geom);
    }

    if (geom && geom->getPositions() && geom->getNormals() && geom->isSingleIndex())
    {
        //
        // 1. Evaluate transformation
        //
        Matrix matToWorld = node->getToWorld();

        std::vector<Matrix>::reverse_iterator iter = data.vecMatrices.rbegin(); // None empty range iff visitation has happen!
        std::vector<Matrix>::reverse_iterator end  = data.vecMatrices.rend();

        for (; iter != end; ++iter)
        {
            matToWorld.multLeft(*iter);
        }

        aiMatrix4x4 ai_matrix;

        for (UInt32 i = 0; i < 4; ++i)
        {
            for (UInt32 j = 0; j < 4; ++j)
            {
                *(ai_matrix[i] + j) = matToWorld[j][i]; // Assimp matrices differ in internal layout to OpenSG matrices.
            }
        }

        ai_node->mTransformation = ai_matrix;

        //
        // 2. Evaluate geometry material
        //
        Material* material = geom->getMaterial();
        if (material)
            data.stackMaterials.push(material);

        //
        // 3. Evaluate meshes
        //
        VecIndicesT vecIndices = handleMeshes(data, geom);

        if (!vecIndices.empty())
        {
            ai_node->mNumMeshes = static_cast<unsigned int>(vecIndices.size());
            ai_node->mMeshes    = new unsigned int[ai_node->mNumMeshes];

            for (std::size_t i = 0; i < vecIndices.size(); ++i)
            {
                ai_node->mMeshes[i] = static_cast<unsigned int>(vecIndices[i]);
            }
        }

        if (material)
            data.stackMaterials.pop();
    }
}

AssimpSceneFileType::VecIndicesT AssimpSceneFileType::handleMeshes(SceneWriteData& data, Geometry* const geom) const
{
    if (!geom) return VecIndicesT();

    OptIndexT matIndex = handleMaterial(data);

    unsigned int mMaterialIndex = matIndex ? static_cast<unsigned int>(*matIndex) : 0;

    //
    // The current implementation has a one to one mapping between OpenSG Geometry and Assimp aiMesh.
    // The Assimp aiNode, however, allows to attach multiple aiMeshes.
    //

    MapGeometriesT::const_iterator geom_iter = data.mapGeometries.find(geom);
    if (geom_iter != data.mapGeometries.end())
    {
        const VecIndicesT& rvecMeshIndices = geom_iter->second;

        OSG_ASSERT(!rvecMeshIndices.empty());

        unsigned int firstIdx = rvecMeshIndices[0];

        //
        // If shared geometry does not have identical material we have to build a new aiMesh
        //
        if (data.vecAiMeshes[firstIdx]->mMaterialIndex == mMaterialIndex)
            return rvecMeshIndices;
    }

    Matrix primaryTrafo;
    OptIndexT primaryUVIdx;

    if (data.options.getForceTexCoord0())
    {
        Matrix trafo;
        primaryUVIdx = getPrimaryMaterialData(data, mMaterialIndex, trafo);

        if (primaryUVIdx)
        {
            data.setPrimaryMaterials.insert(mMaterialIndex);

            if (data.options.getTransformUVCoords())
                primaryTrafo = trafo;
        }
    }

    UInt32 numVertices        = geom->getPositions      (                         ) ? geom->getPositions      (                         )->size32() : 0;
    UInt32 numNormals         = geom->getNormals        (                         ) ? geom->getNormals        (                         )->size32() : 0;
    UInt32 numTangents        = geom->getProperty       (Geometry::Attribute5Index) ? geom->getProperty       (Geometry::Attribute5Index)->size32() : 0;
    UInt32 numBitangents      = geom->getProperty       (Geometry::Attribute6Index) ? geom->getProperty       (Geometry::Attribute6Index)->size32() : 0;
    UInt32 numColors          = geom->getColors         (                         ) ? geom->getColors         (                         )->size32() : 0;
    UInt32 numSecondaryColors = geom->getSecondaryColors(                         ) ? geom->getSecondaryColors(                         )->size32() : 0;
    UInt32 numTexCoords0      = geom->getTexCoords      (                         ) ? geom->getTexCoords      (                         )->size32() : 0;
    UInt32 numTexCoords1      = geom->getTexCoords1     (                         ) ? geom->getTexCoords1     (                         )->size32() : 0;
    UInt32 numTexCoords2      = geom->getTexCoords2     (                         ) ? geom->getTexCoords2     (                         )->size32() : 0;
    UInt32 numTexCoords3      = geom->getTexCoords3     (                         ) ? geom->getTexCoords3     (                         )->size32() : 0;
    UInt32 numTexCoords4      = geom->getTexCoords4     (                         ) ? geom->getTexCoords4     (                         )->size32() : 0;
    UInt32 numTexCoords5      = geom->getTexCoords5     (                         ) ? geom->getTexCoords5     (                         )->size32() : 0;
    UInt32 numTexCoords6      = geom->getTexCoords6     (                         ) ? geom->getTexCoords6     (                         )->size32() : 0;
    UInt32 numTexCoords7      = geom->getTexCoords7     (                         ) ? geom->getTexCoords7     (                         )->size32() : 0;

    bool consistency = numVertices != 0 ? true : false;

    if (numNormals         && numNormals         != numVertices) consistency = false;
    if (numTangents        && numTangents        != numVertices) consistency = false;
    if (numBitangents      && numBitangents      != numVertices) consistency = false;
    if (numColors          && numColors          != numVertices) consistency = false;
    if (numSecondaryColors && numSecondaryColors != numVertices) consistency = false;
    if (numTexCoords0      && numTexCoords0      != numVertices) consistency = false;
    if (numTexCoords1      && numTexCoords1      != numVertices) consistency = false;
    if (numTexCoords2      && numTexCoords2      != numVertices) consistency = false;
    if (numTexCoords3      && numTexCoords3      != numVertices) consistency = false;
    if (numTexCoords4      && numTexCoords4      != numVertices) consistency = false;
    if (numTexCoords5      && numTexCoords5      != numVertices) consistency = false;
    if (numTexCoords6      && numTexCoords6      != numVertices) consistency = false;
    if (numTexCoords7      && numTexCoords7      != numVertices) consistency = false;

    if (!consistency)
        return VecIndicesT();

    unsigned int cntColors    = 0;
    unsigned int cntTexCoords = 0;

    if (numColors          > 0) cntColors++;
    if (numSecondaryColors > 0) cntColors++;
    if (numTexCoords0      > 0) cntTexCoords++;
    if (numTexCoords1      > 0) cntTexCoords++;
    if (numTexCoords2      > 0) cntTexCoords++;
    if (numTexCoords3      > 0) cntTexCoords++;
    if (numTexCoords4      > 0) cntTexCoords++;
    if (numTexCoords5      > 0) cntTexCoords++;
    if (numTexCoords6      > 0) cntTexCoords++;
    if (numTexCoords7      > 0) cntTexCoords++;

    VecIndicesT vecMeshIndices;

    aiMesh* ai_mesh = new aiMesh;

    ai_mesh->mMaterialIndex  = mMaterialIndex;
    ai_mesh->mPrimitiveTypes = aiPrimitiveType_TRIANGLE;
    ai_mesh->mNumVertices    = numVertices;

    //
    // Provide storage
    //

    if (numVertices   > 0) ai_mesh->mVertices   = new aiVector3D[numVertices];
    if (numNormals    > 0) ai_mesh->mNormals    = new aiVector3D[numVertices];
    if (numTangents   > 0) ai_mesh->mTangents   = new aiVector3D[numVertices];
    if (numBitangents > 0) ai_mesh->mBitangents = new aiVector3D[numVertices];

    for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_COLOR_SETS; ++i)
    {
        if (i < cntColors)
        {
            ai_mesh->mColors[i] = new aiColor4D[numVertices];
        }
        else
        {
            ai_mesh->mColors[i] = NULL;
        }
    }

    for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i)
    {
        if (i < cntTexCoords)
        {
            ai_mesh->mTextureCoords  [i] = new aiVector3D[numVertices];
            ai_mesh->mNumUVComponents[i] = 2;   // Only 2D uv coordinates are supported // ????
        }
        else
        {
            ai_mesh->mTextureCoords  [i] = NULL;
            ai_mesh->mNumUVComponents[i] = 0;
        }
    }

    //
    // Fill data
    //
    for(UInt32 i = 0 ; i < numVertices; ++i)
    {
        cntColors    = 0;
        cntTexCoords = 0;

        Pnt3f   p;
        Vec3f   v;
        Pnt3f   uvw;
        Color4f c;

        geom->getPositions()->getValue(p, i);
        ai_mesh->mVertices[i] = aiVector3D(p[0], p[1], p[2]);

        if (numNormals > 0)
        {
            geom->getNormals()->getValue(v, i);
            ai_mesh->mNormals[i] = aiVector3D(v[0], v[1], v[2]);
        }

        if (numTangents > 0)
        {
            geom->getProperty(Geometry::Attribute5Index)->getValue(v, i);
            ai_mesh->mTangents[i] = aiVector3D(v[0], v[1], v[2]);
        }

        if (numBitangents > 0)
        {
            geom->getProperty(Geometry::Attribute6Index)->getValue(v, i);
            ai_mesh->mBitangents[i] = aiVector3D(v[0], v[1], v[2]);
        }

        if (numColors > 0 && cntColors < AI_MAX_NUMBER_OF_COLOR_SETS)
        {
            geom->getColors()->getValue(c, i);
            ai_mesh->mColors[cntColors][i] = aiColor4D(c[0], c[1], c[2], c[3]);
            cntColors++;
        }

        if (numSecondaryColors > 0 && cntColors < AI_MAX_NUMBER_OF_COLOR_SETS)
        {
            geom->getSecondaryColors()->getValue(c, i);
            ai_mesh->mColors[cntColors][i] = aiColor4D(c[0], c[1], c[2], c[3]);
            cntColors++;
        }

        if (primaryUVIdx)
        {
            std::size_t uv_idx = *primaryUVIdx;

            switch (uv_idx)
            {
                case 0: if (numTexCoords0) geom->getTexCoords ()->getValue(uvw, i); break;
                case 1: if (numTexCoords1) geom->getTexCoords1()->getValue(uvw, i); break;
                case 2: if (numTexCoords2) geom->getTexCoords2()->getValue(uvw, i); break;
                case 3: if (numTexCoords3) geom->getTexCoords3()->getValue(uvw, i); break;
                case 4: if (numTexCoords4) geom->getTexCoords4()->getValue(uvw, i); break;
                case 5: if (numTexCoords5) geom->getTexCoords5()->getValue(uvw, i); break;
                case 6: if (numTexCoords6) geom->getTexCoords6()->getValue(uvw, i); break;
                case 7: if (numTexCoords7) geom->getTexCoords7()->getValue(uvw, i); break;
                
                default:
                        if (numTexCoords0) geom->getTexCoords()->getValue(uvw, i);  break;
            }

            uvw = primaryTrafo * uvw;
            ai_mesh->mTextureCoords[0][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
            cntTexCoords++;
        }
        else
        {
            if (numTexCoords0 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords1 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords1()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords2 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords2()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords3 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords3()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords4 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords4()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords5 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords5()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords6 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords6()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }

            if (numTexCoords7 > 0 && cntTexCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS) 
            {
                geom->getTexCoords7()->getValue(uvw, i);
                ai_mesh->mTextureCoords[cntTexCoords][i] = aiVector3D(uvw[0], uvw[1], uvw[2]);
                cntTexCoords++;
            }
        }
    }

    std::vector<aiFace> vecAiFaces;

    TriangleIterator trian_iter = geom->beginTriangles();
    TriangleIterator trian_end  = geom->endTriangles  ();

    const INT32 numIndices = 3;

    for ( ; trian_iter != trian_end; ++trian_iter)
    {
        aiFace ai_face;

        ai_face.mNumIndices = static_cast<unsigned int>(numIndices);
        ai_face.mIndices    = new unsigned int[numIndices];

        for (Int32 which = 0; which < numIndices; ++which)
        {
            ai_face.mIndices[which] = trian_iter.getPositionIndex(which);
        }

        vecAiFaces.push_back(ai_face);
    }

    if (!vecAiFaces.empty())
    {
        ai_mesh->mNumFaces = static_cast<unsigned int>(vecAiFaces.size());
        ai_mesh->mFaces    = new aiFace[vecAiFaces.size()];

        for (std::size_t i = 0; i < vecAiFaces.size(); ++i)
        {
            ai_mesh->mFaces[i] = vecAiFaces[i];
        }
    }
    else
    {
        ai_mesh->mNumFaces = 0;
        ai_mesh->mFaces    = NULL;
    }

    data.vecAiMeshes.push_back(ai_mesh);

    std::size_t mesh_index = data.vecAiMeshes.size() - 1;

    vecMeshIndices.push_back(mesh_index);

    data.mapGeometries.insert(MapGeometriesT::value_type(geom, vecMeshIndices));

    return vecMeshIndices;
}

AssimpSceneFileType::OptIndexT AssimpSceneFileType::handleMaterial(SceneWriteData& data) const
{
    if (data.stackMaterials.empty())
        return boost::none;

    Material* mat = data.stackMaterials.top();

    if (!mat) return boost::none;

    MapMaterialsT::const_iterator iter = data.mapMaterials.find(mat);
    if (iter != data.mapMaterials.end())
        return iter->second;

    aiMaterial* ai_mat = new aiMaterial;

    if (mat->getType().isDerivedFrom(DescMaterial::getClassType()))
    {
        DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(mat);
        handleDescMaterial(data, descMaterial, ai_mat);
    }
    else
    if (mat->getType().isDerivedFrom(SimpleTexturedMaterial::getClassType()))
    {
        SimpleTexturedMaterial* simpleTexMaterial = dynamic_cast<SimpleTexturedMaterial*>(mat);
        handleSimpleTexturedMaterial(data, simpleTexMaterial, ai_mat);
    }
    else
    if (mat->getType().isDerivedFrom(SimpleMaterial::getClassType()))
    {
        SimpleMaterial* simpleMaterial = dynamic_cast<SimpleMaterial*>(mat);
        handleSimpleMaterial(data, simpleMaterial, ai_mat);
    }
    else
    if (mat->getType().isDerivedFrom(ChunkMaterial::getClassType()))
    {
        ChunkMaterial* chunkMaterial = dynamic_cast<ChunkMaterial*>(mat);
        handleChunkMaterial(data, chunkMaterial, ai_mat);
    }

    data.vecAiMaterials.push_back(ai_mat);

    std::size_t index = data.vecAiMaterials.size() - 1;

    data.mapMaterials.insert(MapMaterialsT::value_type(mat, index));

    return index;
}

namespace Details
{
    struct MaterialParameters
    {
        aiString        ai_name;
        aiString        ai_alpha_mode;
        unsigned int    ai_alpha_mode_enum;
        aiShadingMode   ai_model;
        aiBlendMode     ai_blend_func;

        aiColor4D       ai_diffuse;
        aiColor3D       ai_specular;
        aiColor3D       ai_emissive;
        aiColor3D       ai_ambient;
        aiColor3D       ai_transparent;
        aiColor3D       ai_reflective;
        aiColor3D       ai_sub_surface;
        aiColor3D       ai_sheen_color;

        float           ai_opacity;
        float           ai_bump_scale;
        float           ai_shininess;
        float           ai_shininess_strength;
        float           ai_emissive_strength;
        float           ai_reflectivity;
        float           ai_refractive_index;
        float           ai_metalness;
        float           ai_roughness;
        float           ai_alpha_cutoff;
        float           ai_gloss_factor;
        float           ai_clearcoat;
        float           ai_clearcoat_roughness;

        bool            ai_wireframe;
        bool            ai_twosided;
        bool            ai_pbr_specular;
        bool            ai_unlit;
    };

    struct TextureParameters
    {
        TextureParameters() 
            : ai_type           (aiTextureType_NONE   )
            , ai_number         (0                    )
            , ai_filename       (                     )
            , ai_data_type      (                     )
            , ai_pixel_format   (                     )
            , ai_srgb_encoding  (true                 )
            , ai_blend_factor   (1.f                  )
            , ai_mapping        (aiTextureMapping_UV  )
            , ai_uv_index       (0                    ) 
            , ai_min_filter     (0                    )
            , ai_mag_filter     (0                    )
            , ai_operation      (aiTextureOp_Multiply )
            , ai_mapping_mode_u (aiTextureMapMode_Wrap)
            , ai_mapping_mode_v (aiTextureMapMode_Wrap)
            , ai_mapping_mode_U (GL_REPEAT            )
            , ai_mapping_mode_V (GL_REPEAT            )
            , ai_map_axis       (                     )
            , ai_texture_flags  (0                    )
            , ai_transform      (                     )
            , ai_matrix         (                     )
            , has_transform     (false                )
        {}

        TextureParameters(const TextureParameters& rhs)
            : ai_type           (rhs.ai_type          )
            , ai_number         (rhs.ai_number        )
            , ai_filename       (rhs.ai_filename      )
            , ai_data_type      (rhs.ai_data_type     )
            , ai_pixel_format   (rhs.ai_pixel_format  )
            , ai_srgb_encoding  (rhs.ai_srgb_encoding )
            , ai_blend_factor   (rhs.ai_blend_factor  )
            , ai_mapping        (rhs.ai_mapping       )
            , ai_uv_index       (rhs.ai_uv_index      )
            , ai_min_filter     (rhs.ai_min_filter    )
            , ai_mag_filter     (rhs.ai_mag_filter    )
            , ai_operation      (rhs.ai_operation     )
            , ai_mapping_mode_u (rhs.ai_mapping_mode_u)
            , ai_mapping_mode_v (rhs.ai_mapping_mode_v)
            , ai_mapping_mode_U (rhs.ai_mapping_mode_U)
            , ai_mapping_mode_V (rhs.ai_mapping_mode_V)
            , ai_map_axis       (rhs.ai_map_axis      )
            , ai_texture_flags  (rhs.ai_texture_flags )
            , ai_transform      (rhs.ai_transform     )
            , ai_matrix         (rhs.ai_matrix        )
            , has_transform     (rhs.has_transform    )
        {}

        TextureParameters& operator=(const TextureParameters& rhs)
        {
            if (&rhs == this)
                return *this;

            ai_type             = rhs.ai_type;
            ai_number           = rhs.ai_number;
            ai_filename         = rhs.ai_filename;
            ai_data_type        = rhs.ai_data_type;
            ai_pixel_format     = rhs.ai_pixel_format;
            ai_srgb_encoding    = rhs.ai_srgb_encoding;
            ai_blend_factor     = rhs.ai_blend_factor;
            ai_mapping          = rhs.ai_mapping;
            ai_uv_index         = rhs.ai_uv_index;
            ai_min_filter       = rhs.ai_min_filter;
            ai_mag_filter       = rhs.ai_mag_filter;
            ai_operation        = rhs.ai_operation;
            ai_mapping_mode_u   = rhs.ai_mapping_mode_u;
            ai_mapping_mode_v   = rhs.ai_mapping_mode_v;
            ai_mapping_mode_U   = rhs.ai_mapping_mode_U;
            ai_mapping_mode_V   = rhs.ai_mapping_mode_V;
            ai_map_axis         = rhs.ai_map_axis;
            ai_texture_flags    = rhs.ai_texture_flags;
            ai_transform        = rhs.ai_transform;
            ai_matrix           = rhs.ai_matrix;
            has_transform       = rhs.has_transform;

            return *this;
        }

        aiTextureType       ai_type;
        unsigned int        ai_number;
        aiString            ai_filename;
        unsigned int        ai_data_type;
        unsigned int        ai_pixel_format;
        bool                ai_srgb_encoding;
        float               ai_blend_factor;
        aiTextureMapping    ai_mapping;
        unsigned int        ai_uv_index;
        unsigned int        ai_min_filter;
        unsigned int        ai_mag_filter;
        aiTextureOp         ai_operation;
        aiTextureMapMode    ai_mapping_mode_u;
        aiTextureMapMode    ai_mapping_mode_v;
        unsigned int        ai_mapping_mode_U;
        unsigned int        ai_mapping_mode_V;
        aiVector3D          ai_map_axis;
        unsigned int        ai_texture_flags;
        aiUVTransform       ai_transform;
        Matrix              ai_matrix;
        bool                has_transform;

    };

    typedef std::vector<TextureParameters>  VecTextureParametersT;

    static aiTextureMapping getTextureMapping       (UInt32 mappingMode);      // TextureDesc::UV_MAPPING -> aiTextureMapping_UV, ...
    static aiTextureMapMode getTextureMappingMode   (UInt32 wrap       );      // GL_REPEAT -> aiTextureMapMode_Wrap, ...
    static unsigned int     getTextureFlags         (UInt32 flags      );      // TextureDesc::INVERT_FLAG -> aiTextureFlags_Invert, ...
    static aiTextureOp      getTextureOperation     (UInt32 operation  );      // TextureDesc::MULTIPLY_OPERATION -> aiTextureOp_Multiply, ...
    static float            getTextureBlendFactor   (Real32 factor, UInt32 operation);
}

void AssimpSceneFileType::prepareNonTexMaterialParamsGLTF2(SceneWriteData& data, Details::MaterialParameters& params) const
{
    //
    // Assimp/gltf2 can only store pbr rough/metal or specular/gloss workflow
    //
    if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
    {
        switch (params.ai_model)
        {
            case aiShadingMode_Gouraud:
            case aiShadingMode_OrenNayar:
                params.ai_specular = aiColor3D(0.f, 0.f, 0.f);
                break;
        }

        if (params.ai_model != aiShadingMode_CookTorrance)
        {
            params.ai_pbr_specular = true;
            params.ai_model        = aiShadingMode_CookTorrance;
        }

        //
        // Gltf expects color values (better color factors) to be in linear space.
        // At this point in code all color values are in sRGB space. We therefore
        // must linearize them.
        //
        for (int i = 0; i < 3; ++i)
        {
            params.ai_diffuse    [i] = SRGBToLinear(params.ai_diffuse    [i]);
            params.ai_specular   [i] = SRGBToLinear(params.ai_specular   [i]);
            params.ai_emissive   [i] = SRGBToLinear(params.ai_emissive   [i]);
            params.ai_ambient    [i] = SRGBToLinear(params.ai_ambient    [i]);
            params.ai_transparent[i] = SRGBToLinear(params.ai_transparent[i]);
            params.ai_reflective [i] = SRGBToLinear(params.ai_reflective [i]);
            params.ai_sub_surface[i] = SRGBToLinear(params.ai_sub_surface[i]);
            params.ai_sheen_color[i] = SRGBToLinear(params.ai_sheen_color[i]);
        }
    }
}

void AssimpSceneFileType::prepareNonTexMaterialParamsOBJ(SceneWriteData& data, Details::MaterialParameters& params) const
{
    if (data.formatId == AssimpOptions::format_obj)
    {
    }
}

void AssimpSceneFileType::handleNonTexMaterialParamsCommon(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    prepareNonTexMaterialParamsGLTF2(data, params);
    prepareNonTexMaterialParamsOBJ  (data, params);

    aiColor4D rgba_white(1.f, 1.f, 1.f, 1.f);
    aiColor3D rgb_white(1.f, 1.f, 1.f);

    if (data.vecCorrectFactor[aiTextureType_AMBIENT  ]) params.ai_ambient   = rgb_white;
    if (data.vecCorrectFactor[aiTextureType_DIFFUSE  ]) params.ai_diffuse   = rgba_white;
    if (data.vecCorrectFactor[aiTextureType_SPECULAR ]) params.ai_specular  = rgb_white;
    if (data.vecCorrectFactor[aiTextureType_EMISSIVE ]) params.ai_emissive  = rgb_white;
    if (data.vecCorrectFactor[aiTextureType_SHININESS]) params.ai_shininess = 1.f;
    if (data.vecCorrectFactor[aiTextureType_OPACITY  ]) params.ai_opacity   = 1.f;
    
    ai_mat->AddProperty(&params.ai_name,                  AI_MATKEY_NAME);
    ai_mat->AddProperty(&params.ai_ambient,            1, AI_MATKEY_COLOR_AMBIENT);
    ai_mat->AddProperty(&params.ai_diffuse,            1, AI_MATKEY_COLOR_DIFFUSE);
    ai_mat->AddProperty(&params.ai_specular,           1, AI_MATKEY_COLOR_SPECULAR);
    ai_mat->AddProperty(&params.ai_emissive,           1, AI_MATKEY_COLOR_EMISSIVE);
    ai_mat->AddProperty(&params.ai_transparent,        1, AI_MATKEY_COLOR_TRANSPARENT);
    ai_mat->AddProperty(&params.ai_reflective,         1, AI_MATKEY_COLOR_REFLECTIVE);
    ai_mat->AddProperty(&params.ai_model,              1, AI_MATKEY_SHADING_MODEL);
    ai_mat->AddProperty(&params.ai_twosided,           1, AI_MATKEY_TWOSIDED);
    ai_mat->AddProperty(&params.ai_wireframe,          1, AI_MATKEY_ENABLE_WIREFRAME);
    ai_mat->AddProperty(&params.ai_blend_func,         1, AI_MATKEY_BLEND_FUNC);
    ai_mat->AddProperty(&params.ai_opacity,            1, AI_MATKEY_OPACITY);
    ai_mat->AddProperty(&params.ai_bump_scale,         1, AI_MATKEY_BUMPSCALING);
    ai_mat->AddProperty(&params.ai_shininess,          1, AI_MATKEY_SHININESS);
    ai_mat->AddProperty(&params.ai_shininess_strength, 1, AI_MATKEY_SHININESS_STRENGTH);
    ai_mat->AddProperty(&params.ai_reflectivity,       1, AI_MATKEY_REFLECTIVITY);
    ai_mat->AddProperty(&params.ai_refractive_index,   1, AI_MATKEY_REFRACTI);

    handleNonTexMaterialParamsGLTF2(data, params, ai_mat);
    handleNonTexMaterialParamsOBJ  (data, params, ai_mat);
}

void AssimpSceneFileType::handleNonTexMaterialParamsGLTF2(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
    {
        ai_mat->AddProperty(&params.ai_diffuse,        1, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_FACTOR);

        if (params.ai_pbr_specular)
        {
            if (data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS]) params.ai_gloss_factor = 1.f;

            ai_mat->AddProperty(&params.ai_pbr_specular, 1, AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS);
            ai_mat->AddProperty(&params.ai_gloss_factor, 1, AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS_GLOSSINESS_FACTOR);
        }
        else
        {
            if (data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS]) params.ai_roughness = 1.f;
            if (data.vecCorrectFactor[aiTextureType_METALNESS        ]) params.ai_metalness = 1.f;

            ai_mat->AddProperty(&params.ai_roughness,    1, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR);
            ai_mat->AddProperty(&params.ai_metalness,    1, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR);
        }
        
        ai_mat->AddProperty(&params.ai_alpha_mode,        AI_MATKEY_GLTF_ALPHAMODE);
        ai_mat->AddProperty(&params.ai_alpha_cutoff,   1, AI_MATKEY_GLTF_ALPHACUTOFF);

        ai_mat->AddProperty(&params.ai_unlit,          1, AI_MATKEY_GLTF_UNLIT);
    }
}

void AssimpSceneFileType::handleNonTexMaterialParamsOBJ(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_obj)
    {
        if (params.ai_pbr_specular)
        {
            if (data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS]) params.ai_gloss_factor = 1.f;
        }
        else
        {
            if (data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS]) params.ai_roughness = 1.f;
            if (data.vecCorrectFactor[aiTextureType_METALNESS        ]) params.ai_metalness = 1.f;
        }

        if (data.spMtyStream)
        {
            OutStreamT& os = *data.spMtyStream;

            std::string space  = " ";
            std::string space4 = "    ";

            os << std::fixed << std::setprecision( 6 );
            os << "newmtl" << space << params.ai_name.C_Str() << std::endl;

            bool hasAmbient   = false;
            bool hasDiffuse   = false;
            bool hasSpecular  = false;
            bool hasEmissive  = false;
            bool hasMetalness = false;
            bool hasRoughness = false;
            bool hasShininess = false;
            bool hasClearcoat = false;

            switch (params.ai_model)
            {
                case aiShadingMode_NoShading:
                    {
                        hasAmbient = hasDiffuse = hasEmissive = true;
                        os << space4 << "shader_model" << space << MaterialDesc::NO_SHADING_MODEL << std::endl;
                    }
                    break;
                case aiShadingMode_Gouraud:
                    {
                        hasAmbient = hasDiffuse = hasEmissive = true;
                        os << space4 << "shader_model" << space << MaterialDesc::GOURAUD_SHADING_MODEL << std::endl;
                    }
                    break;
                case aiShadingMode_Flat:
                    {
                        hasAmbient = hasDiffuse = hasEmissive = true;
                        os << space4 << "shader_model" << space << MaterialDesc::GOURAUD_SHADING_MODEL << std::endl;
                        os << space4 << "flat" << std::endl;
                    }
                    break;
                case aiShadingMode_Phong:
                    {
                        hasAmbient = hasDiffuse = hasSpecular = hasEmissive = hasShininess = true;
                        os << space4 << "shader_model" << space << MaterialDesc::PHONG_SHADING_MODEL << std::endl;
                    }
                    break;
                case aiShadingMode_Blinn:
                    {
                        hasAmbient = hasDiffuse = hasSpecular = hasEmissive = hasShininess = true;
                        os << space4 << "shader_model" << space << MaterialDesc::BLINN_PHONG_SHADING_MODEL << std::endl;
                    }
                    break;
                case aiShadingMode_CookTorrance:
                    {
                        if (params.ai_pbr_specular)
                        {
                            hasAmbient = hasDiffuse = hasSpecular = hasEmissive = hasShininess /*= hasClearcoat*/= true;
                            os << space4 << "shader_model" << space << MaterialDesc::BLINN_PHONG_SHADING_MODEL << std::endl;
                        }
                        else
                        {
                            hasDiffuse = hasEmissive = hasMetalness = hasRoughness = true;
                            os << space4 << "shader_model" << space << MaterialDesc::COOK_TORRANCE_SHADING_MODEL << std::endl;
                        }
                    
                    }
                    break;
                case aiShadingMode_OrenNayar:
                    {
                        hasDiffuse = hasEmissive = hasMetalness = hasRoughness = true;
                        os << space4 << "shader_model" << space << MaterialDesc::OREN_NAYAR_SHADING_MODEL << std::endl;
                    }
                    break;
                case aiShadingMode_Toon:
                    {
                        hasAmbient = hasDiffuse = hasSpecular = hasEmissive = hasShininess = true;
                        os << space4 << "shader_model" << space << MaterialDesc::TOON_SHADING_MODEL << std::endl;
                    }
                    break;
            }

            if (hasAmbient)
            {
                os << space4 << "Ka" << space << params.ai_ambient [0]  << space << params.ai_ambient [1]  << space << params.ai_ambient [2]  << std::endl;
            }

            if (hasDiffuse)
            {
                os << space4 << "Kd" << space << params.ai_diffuse [0]  << space << params.ai_diffuse [1]  << space << params.ai_diffuse [2]  << std::endl;
            }

            if (hasSpecular)
            {
                os << space4 << "Ks" << space << params.ai_specular[0]  << space << params.ai_specular[1]  << space << params.ai_specular[2]  << std::endl;
            }

            if (hasEmissive)
            {
                os << space4 << "Ke" << space << params.ai_emissive[0]  << space << params.ai_emissive[1]  << space << params.ai_emissive[2]  << std::endl;
                os << space4 << "emissive_strength"  << space << params.ai_emissive_strength << std::endl;
            }

            if (hasShininess)
            {
                os << space4 << "shininess" << space << params.ai_shininess << std::endl;
            }

            if (hasMetalness)
            {
                os << space4 << "metalness" << space << params.ai_metalness << std::endl;
            }

            if (hasRoughness)
            {
                os << space4 << "roughness" << space << params.ai_roughness << std::endl;
            }

            os << space4 << "opacity"        << space << params.ai_opacity         << std::endl;
            os << space4 << "opacity_mode"   << space << params.ai_alpha_mode_enum << std::endl;
            os << space4 << "opacity_cutoff" << space << params.ai_alpha_cutoff    << std::endl;

            if (hasClearcoat)
            {
                os << space4 << "clearcoat"           << space << params.ai_clearcoat           << std::endl;
                os << space4 << "clearcoat_roughness" << space << params.ai_clearcoat_roughness << std::endl;

                os << space4 << "sub_surface_color"   << space << params.ai_sub_surface[0]  << space << params.ai_sub_surface[1]  << space << params.ai_sub_surface[2]  << std::endl;
                os << space4 << "sheen_color"         << space << params.ai_sheen_color[0]  << space << params.ai_sheen_color[1]  << space << params.ai_sheen_color[2]  << std::endl;
            }

            os << space4 << "reflectivity"    << space << params.ai_reflectivity           << std::endl;
            os << space4 << "refractionRatio" << space << 1.f / params.ai_refractive_index << std::endl;
        }
    }
}

void AssimpSceneFileType::finishNonTexMaterialParamsCommon(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    finishNonTexMaterialParamsGLTF2(data, params, ai_mat);
    finishNonTexMaterialParamsOBJ  (data, params, ai_mat);
}

void AssimpSceneFileType::finishNonTexMaterialParamsGLTF2(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
    {
    }
}

void AssimpSceneFileType::finishNonTexMaterialParamsOBJ(SceneWriteData& data, Details::MaterialParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_obj)
    {
        if (data.spMtyStream)
        {
            OutStreamT& os = *data.spMtyStream;
            os <<  std::endl;
        }
    }
}

void AssimpSceneFileType::handleTexMaterialTextureParams(SceneWriteData& data, Details::TextureParameters& params, aiMaterial* ai_mat) const
{
    if (data.vecCorrectFactor[params.ai_type]) params.ai_blend_factor = 1.f;

    ai_mat->AddProperty(&params.ai_filename,          _AI_MATKEY_TEXTURE_BASE,       params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_blend_factor,   1, _AI_MATKEY_TEXBLEND_BASE,      params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_mapping,        1, _AI_MATKEY_MAPPING_BASE,       params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_uv_index,       1, _AI_MATKEY_UVWSRC_BASE,        params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_operation,      1, _AI_MATKEY_TEXOP_BASE,         params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_mapping_mode_u, 1, _AI_MATKEY_MAPPINGMODE_U_BASE, params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_mapping_mode_v, 1, _AI_MATKEY_MAPPINGMODE_V_BASE, params.ai_type, params.ai_number);
    ai_mat->AddProperty(&params.ai_texture_flags,  1, _AI_MATKEY_TEXFLAGS_BASE,      params.ai_type, params.ai_number);

    if (!params.ai_map_axis.Equal(aiVector3D(0.f,0.f,0.f)))
        ai_mat->AddProperty(&params.ai_map_axis,       1, _AI_MATKEY_TEXMAP_AXIS_BASE,   params.ai_type, params.ai_number);

    if (params.has_transform)
        ai_mat->AddProperty(&params.ai_transform,      1, _AI_MATKEY_UVTRANSFORM_BASE,   params.ai_type, params.ai_number);

    handleTexMaterialTextureParamsGLTF2(data, params, ai_mat);
    handleTexMaterialTextureParamsOBJ  (data, params, ai_mat);
}

void AssimpSceneFileType::handleTexMaterialTextureParamsGLTF2(SceneWriteData& data, Details::TextureParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
    {
        ai_mat->AddProperty(&params.ai_min_filter,   1, _AI_MATKEY_GLTF_MAPPINGFILTER_MIN_BASE, params.ai_type, params.ai_number);
        ai_mat->AddProperty(&params.ai_mag_filter,   1, _AI_MATKEY_GLTF_MAPPINGFILTER_MAG_BASE, params.ai_type, params.ai_number);

        ai_mat->AddProperty(&params.ai_uv_index, 1, _AI_MATKEY_GLTF_TEXTURE_TEXCOORD_BASE, params.ai_type, params.ai_number);

        if (params.ai_mapping_mode_u == aiTextureMapMode_Decal) params.ai_mapping_mode_u = aiTextureMapMode_Clamp;
        if (params.ai_mapping_mode_v == aiTextureMapMode_Decal) params.ai_mapping_mode_v = aiTextureMapMode_Clamp;

        ai_mat->AddProperty(&params.ai_mapping_mode_u, 1, _AI_MATKEY_MAPPINGMODE_U_BASE, params.ai_type, params.ai_number);
        ai_mat->AddProperty(&params.ai_mapping_mode_v, 1, _AI_MATKEY_MAPPINGMODE_V_BASE, params.ai_type, params.ai_number);
    }
}

void AssimpSceneFileType::handleTexMaterialTextureParamsOBJ(SceneWriteData& data, Details::TextureParameters& params, aiMaterial* ai_mat) const
{
    if (data.formatId == AssimpOptions::format_obj)
    {
        if (data.spMtyStream)
        {
            OutStreamT& os = *data.spMtyStream;

            std::string space  = " ";
            std::string space4 = "    ";

            switch (params.ai_type)
            {
                case aiTextureType_NONE:
                    break;
                case aiTextureType_DIFFUSE:
                case aiTextureType_BASE_COLOR:
                    os << space4 << "map_Kd" << space;
                    break;
                case aiTextureType_SPECULAR:
                    os << space4 << "map_Ks" << space;
                    break;
                case aiTextureType_AMBIENT:
                    os << space4 << "map_Ka" << space;
                    break;
                case aiTextureType_EMISSIVE:
                case aiTextureType_EMISSION_COLOR:
                    os << space4 << "map_Ke" << space;
                    break;
                case aiTextureType_HEIGHT:
                    os << space4 << "map_Bump" << space;
                    break;
                case aiTextureType_NORMALS:
                    os << space4 << "map_Normal" << space;
                    break;
                case aiTextureType_SHININESS:
                    os << space4 << "map_Ns" << space;
                    break;
                case aiTextureType_OPACITY:
                    os << space4 << "map_Opacity" << space;
                    break;
                case aiTextureType_DISPLACEMENT:
                    os << space4 << "map_Displacement" << space;
                    break;
                case aiTextureType_LIGHTMAP:
                    break;
                case aiTextureType_REFLECTION:
                    break;
                case aiTextureType_NORMAL_CAMERA:
                    // not supported
                    break;
                case aiTextureType_METALNESS:
                    os << space4 << "map_Metalness" << space;
                    break;
                case aiTextureType_DIFFUSE_ROUGHNESS:
                    os << space4 << "map_Roughness" << space;
                    break;
                case aiTextureType_AMBIENT_OCCLUSION:
                    os << space4 << "map_AO" << space;
                    break;
                case aiTextureType_UNKNOWN:
                    os << space4 << "map_ORM" << space;
                    break;
            }

            switch (params.ai_type)
            {
                case aiTextureType_DIFFUSE:
                case aiTextureType_BASE_COLOR:
                case aiTextureType_SPECULAR:
                case aiTextureType_AMBIENT:
                case aiTextureType_EMISSIVE:
                case aiTextureType_EMISSION_COLOR:
                case aiTextureType_HEIGHT:
                case aiTextureType_NORMALS:
                case aiTextureType_SHININESS:
                case aiTextureType_OPACITY:
                case aiTextureType_DISPLACEMENT:
                case aiTextureType_METALNESS:
                case aiTextureType_DIFFUSE_ROUGHNESS:
                case aiTextureType_AMBIENT_OCCLUSION:
                case aiTextureType_UNKNOWN:
                    {
                        os << "-mapping"      << space << "uv"                                          << space
                           << "-minFilter"    << space << params.ai_min_filter                          << space
                           << "-magFilter"    << space << params.ai_mag_filter                          << space
                           << "-wrapS"        << space << params.ai_mapping_mode_U                      << space
                           << "-wrapT"        << space << params.ai_mapping_mode_V                      << space
                           << "-data_type"    << space << params.ai_data_type                           << space
                           << "-pixel_format" << space << params.ai_pixel_format                        << space
                           << "-encoding"     << space << (params.ai_srgb_encoding ? "srgb" : "linear") << space
                           ;

                        if (params.has_transform && !data.options.getTransformUVCoords())
                        {
                            const Matrix& m = params.ai_matrix;

                            Vec4f c0 = m[0];
                            Vec4f c1 = m[1];
                            Vec4f c2 = m[2];
                            Vec4f c3 = m[3];

                            Real32 m00 = c0[0]; Real32 m01 = c1[0]; Real32 m02 = c3[0];
                            Real32 m10 = c0[1]; Real32 m11 = c1[1]; Real32 m12 = c3[1];
                            Real32 m20 = c0[3]; Real32 m21 = c1[3]; Real32 m22 = c3[3];

                            os << "-M" 
                               << space  << m00 << space << m01 << space << m02 
                               << space  << m10 << space << m11 << space << m12 
                               << space  << m20 << space << m21 << space << m22 
                               << space;
                        }

                        os << params.ai_filename.C_Str()  << std::endl;
                    }
                    break;

                case aiTextureType_LIGHTMAP:
                    break;
                case aiTextureType_REFLECTION:
                    break;
                case aiTextureType_NORMAL_CAMERA:
                    // not supported
                    break;

            }
        }
    }
}

//
// handleDescMaterial
//

void AssimpSceneFileType::handleDescMaterial(SceneWriteData& data, const DescMaterial* descMat, aiMaterial* ai_mat) const
{
    MaterialDesc* matDesc = descMat->getMaterialDesc();

    prepareDescMaterialTex(data, descMat);

    Details::MaterialParameters params;

    std::string name = matDesc->getName();

    if (name.empty())
    {
        name = "Undefined";
    }
    else if (name == "< ? >")
    {
        name = "Unknown";
    }

    //
    // We must ensure that the material name is unique
    //
    MapMaterialNamesT::iterator iter = data.mapMaterialNames.find(name);
    if (iter != data.mapMaterialNames.end())
    {
        iter->second++;

        std::stringstream ss;
        ss << name << " " << iter->second;

        name = ss.str();
    }
    else
    {
        data.mapMaterialNames.insert(MapMaterialNamesT::value_type(name, 1));
    }

    params.ai_name.Set(name);

    params.ai_model = aiShadingMode_Blinn;

    switch (matDesc->getShadingModel())
    {
        case MaterialDesc::GOURAUD_SHADING_MODEL:
            {
                if (matDesc->getFlatShadingMode())
                    params.ai_model = aiShadingMode_Flat;
                else
                    params.ai_model = aiShadingMode_Gouraud;
            }
            break;

        case MaterialDesc::PHONG_SHADING_MODEL:         params.ai_model = aiShadingMode_Phong;        break;
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:   params.ai_model = aiShadingMode_Blinn;        break;
        case MaterialDesc::TOON_SHADING_MODEL:          params.ai_model = aiShadingMode_Toon;         break;
        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:    params.ai_model = aiShadingMode_OrenNayar;    break;
        case MaterialDesc::COOK_TORRANCE_SHADING_MODEL: params.ai_model = aiShadingMode_CookTorrance; break;
        case MaterialDesc::NO_SHADING_MODEL:            params.ai_model = aiShadingMode_NoShading;    break;
        default:
            params.ai_model = aiShadingMode_Blinn;
    }

    //
    // Most export file formats store sRGB color values
    //
    bool linear = !matDesc->getSRGBColorMode();
    
    Color3f albedo      = matDesc->getAlbedo          (); if (linear) for (int i = 0; i < 3; ++i) albedo     [i] = LinearToSRGB(albedo     [i]);
    Color3f specular    = matDesc->getSpecular        (); if (linear) for (int i = 0; i < 3; ++i) specular   [i] = LinearToSRGB(specular   [i]);
    Color3f emissive    = matDesc->getEmissive        (); if (linear) for (int i = 0; i < 3; ++i) emissive   [i] = LinearToSRGB(emissive   [i]);
    Color3f ambient     = 0.333f * albedo;
    Color3f transparent = matDesc->getTransparent     (); if (linear) for (int i = 0; i < 3; ++i) transparent[i] = LinearToSRGB(transparent[i]);
    Color3f reflective  = matDesc->getReflective      (); if (linear) for (int i = 0; i < 3; ++i) reflective [i] = LinearToSRGB(reflective [i]);
    Color3f subSurface  = matDesc->getSubSurfaceColor (); if (linear) for (int i = 0; i < 3; ++i) subSurface [i] = LinearToSRGB(subSurface [i]);
    Color3f sheenColor  = matDesc->getSheenColor      (); if (linear) for (int i = 0; i < 3; ++i) sheenColor [i] = LinearToSRGB(sheenColor [i]);

    params.ai_diffuse     = aiColor4D(albedo     [0], albedo     [1], albedo     [2], matDesc->getOpacity());
    params.ai_specular    = aiColor3D(specular   [0], specular   [1], specular   [2]);
    params.ai_emissive    = aiColor3D(emissive   [0], emissive   [1], emissive   [2]);
    params.ai_ambient     = aiColor3D(ambient    [0], ambient    [1], ambient    [2]);
    params.ai_transparent = aiColor3D(transparent[0], transparent[1], transparent[2]);
    params.ai_reflective  = aiColor3D(reflective [0], reflective [1], reflective [2]);
    params.ai_sub_surface = aiColor3D(subSurface [0], subSurface [1], subSurface [2]);
    params.ai_sheen_color = aiColor3D(sheenColor [0], sheenColor [1], sheenColor [2]);

    params.ai_wireframe = false;    // not supported

    params.ai_blend_func = aiBlendMode_Default;

    switch (matDesc->getBlendMode())
    {
        case MaterialDesc::DEFAULT_BLEND_MODE:  params.ai_blend_func = aiBlendMode_Default;  break;
        case MaterialDesc::ADDITIVE_BLEND_MODE: params.ai_blend_func = aiBlendMode_Additive; break;
    }

    params.ai_opacity             = matDesc->getOpacity();
    params.ai_bump_scale          = matDesc->getBumpScaling();
    params.ai_shininess           = matDesc->getShininess();
    params.ai_shininess_strength  = matDesc->getSpecularStrength();
    params.ai_emissive_strength   = matDesc->getEmissiveStrength();
    params.ai_reflectivity        = matDesc->getReflectivity();
    params.ai_refractive_index    = matDesc->getRefractiveIndex();
    params.ai_metalness           = matDesc->getMetalness();
    params.ai_roughness           = matDesc->getRoughness();
    params.ai_clearcoat           = matDesc->getClearCoatStrength();
    params.ai_clearcoat_roughness = matDesc->getClearCoatRoughness();

    params.ai_twosided           = false;

    switch (matDesc->getCullFace())
    {
        case GL_NONE: params.ai_twosided = true;  break;
        case GL_BACK: params.ai_twosided = false; break;
    }

    if (data.options.getForceTwosided() || osgAbs(1.f - matDesc->getOpacity()) > Eps)
    {
        params.ai_twosided = true;
    }

    params.ai_alpha_mode.Set("OPAQUE");
    params.ai_alpha_mode_enum = matDesc->getOpacityMode();

    switch (matDesc->getOpacityMode())
    {
        case MaterialDesc::NO_OPACITY_MODE:
        case MaterialDesc::OPAQUE_OPACITY_MODE:
            params.ai_alpha_mode.Set("OPAQUE");
            break;
        case MaterialDesc::MASK_OPACITY_MODE:
            params.ai_alpha_mode.Set("MASK");
            break;
        case MaterialDesc::BLEND_OPACITY_MODE :
            params.ai_alpha_mode.Set("BLEND");
            break;
    }

    float gloss_correction_factor = 0.92f;

    params.ai_alpha_cutoff = matDesc->getOpacityCutOff  ();
    params.ai_pbr_specular = matDesc->getPbrSpecularMode();
    params.ai_gloss_factor = (1.f - matDesc->getRoughness());
    params.ai_unlit        = matDesc->getUnlitMode      ();

    switch (matDesc->getShadingModel())
    {
        case MaterialDesc::GOURAUD_SHADING_MODEL:
        case MaterialDesc::PHONG_SHADING_MODEL:
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:
        case MaterialDesc::TOON_SHADING_MODEL:
        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:
            params.ai_gloss_factor *= gloss_correction_factor;
            break;
    }

    handleNonTexMaterialParamsCommon(data, params, ai_mat);

    //
    // Finally, handle textures
    //
    handleDescMaterialTex(data, descMat, ai_mat);

    //
    // and some additional stuff
    //
    finishNonTexMaterialParamsCommon(data, params, ai_mat);
}

void  AssimpSceneFileType::prepareDescMaterialTex(SceneWriteData& data, const DescMaterial* descMat) const
{
    //
    // We can not export multiple textures of the same type, e.g. specular textures.
    // In order to proceed, we just take the first texture found and ignore any 
    // further textures of the same texture type.
    //
    // Additionally, we drop textures that we currently do not know how to handle them.
    //
    DescMaterial::TextureDescStore::const_iterator iter1 = descMat->getActiveTextureDescs().begin();
    DescMaterial::TextureDescStore::const_iterator end1  = descMat->getActiveTextureDescs().end  ();

    data.vecTextureDescs.clear();

    std::vector<UInt32> vecTextureCnts (TextureDesc::MAX_NUM_TEXTURE_TYPES, 0);
    std::vector<bool>   vecTextureFound(TextureDesc::MAX_NUM_TEXTURE_TYPES, false);

    for (; iter1 != end1; ++iter1)
    {
        TextureDesc* texDesc = *iter1;

        UInt32 textureType = texDesc->getTextureType();
        vecTextureCnts[textureType]++;

        bool export_texture = false;

        // only the first texture is used
        if (!vecTextureFound[textureType] && validDescMaterialTexType(data, descMat, textureType))
        {
            export_texture = true;
            vecTextureFound[textureType] = true;
        }

        if (export_texture)
        {
            // we might change the TextureDesc instance later, so we make a copy
            TextureDescUnrecPtr copyTexDesc = dynamic_pointer_cast<TextureDesc>(texDesc->shallowCopy());

            data.vecTextureDescs.push_back(copyTexDesc);
        }
    }

    //
    // Evaluate additional runtime data
    //
    data.vecCorrectFactor.swap(std::vector<bool>(AI_TEXTURE_TYPE_MAX+1, false));

    TextureDescStore::const_iterator iter2 = data.vecTextureDescs.begin();
    TextureDescStore::const_iterator end2  = data.vecTextureDescs.end  ();

    for (; iter2 != end2; ++iter2)
    {
        TextureDesc* texDesc = *iter2;

        UInt32 textureType = texDesc->getTextureType();

        //
        // Assimp does not know about the TextureDesc::REPLACE_OPERATION operation. 
        // If we use this operation we instead use the multiply operation with a factor
        // of one. In order to recognize that, we track the vecCorrectFactor data.
        //
        if (texDesc->getOperation() == TextureDesc::REPLACE_OPERATION)
        {
            std::size_t idx = 0;

            switch (textureType)
            {
                case TextureDesc::NONE_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_NONE             ] = true;
                    break;
                case TextureDesc::UNKNOWN_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_UNKNOWN          ] = true;
                    break;
                case TextureDesc::ALBEDO_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_AMBIENT          ] = true;
                    data.vecCorrectFactor[aiTextureType_DIFFUSE          ] = true;
                    data.vecCorrectFactor[aiTextureType_BASE_COLOR       ] = true;
                    break;
                case TextureDesc::SPECULAR_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_SPECULAR         ] = true;
                    break;
                case TextureDesc::EMISSIVE_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_EMISSIVE         ] = true;
                    data.vecCorrectFactor[aiTextureType_EMISSION_COLOR   ] = true;
                    break;
                case TextureDesc::SHININESS_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_SHININESS        ] = true;
                    break;
                case TextureDesc::OPACITY_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_OPACITY          ] = true;
                    break;
                case TextureDesc::NORMALS_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_NORMALS          ] = true;
                    data.vecCorrectFactor[aiTextureType_NORMAL_CAMERA    ] = true;
                    break;
                case TextureDesc::HEIGHT_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_HEIGHT           ] = true;
                    break;
                case TextureDesc::DISPLACEMENT_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_HEIGHT           ] = true;
                    data.vecCorrectFactor[aiTextureType_DISPLACEMENT     ] = true;
                    break;
                case TextureDesc::REFLECTION_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_REFLECTION       ] = true;
                    break;
                case TextureDesc::REFRACTION_TEXTURE:
                    break;
                case TextureDesc::ANISOTROPY_U_TEXTURE:
                    break;
                case TextureDesc::ANISOTROPY_V_TEXTURE:
                    break;
                case TextureDesc::ANISOTROPY_UV_TEXTURE:
                    break;
                case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_AMBIENT_OCCLUSION] = true;
                    data.vecCorrectFactor[aiTextureType_LIGHTMAP         ] = true;
                    break;
                case TextureDesc::ROUGH_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS] = true;
                    break;
                case TextureDesc::METAL_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_METALNESS        ] = true;
                    break;
                case TextureDesc::ROUGH_METAL_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS] = true;
                    data.vecCorrectFactor[aiTextureType_METALNESS        ] = true;
                    break;
                case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_AMBIENT_OCCLUSION] = true;
                    data.vecCorrectFactor[aiTextureType_LIGHTMAP         ] = true;
                    data.vecCorrectFactor[aiTextureType_DIFFUSE_ROUGHNESS] = true;
                    data.vecCorrectFactor[aiTextureType_METALNESS        ] = true;
                    break;
                case TextureDesc::IRRADIANCE_TEXTURE:
                    break;
                case TextureDesc::PRE_FILTER_TEXTURE:
                    break;
                case TextureDesc::BRDF_LUT_TEXTURE:
                    break;
                case TextureDesc::STANDARD_MATERIAL_TEXTURE:
                    data.vecCorrectFactor[aiTextureType_AMBIENT          ] = true;
                    data.vecCorrectFactor[aiTextureType_DIFFUSE          ] = true;
                    data.vecCorrectFactor[aiTextureType_EMISSIVE         ] = true;
                    data.vecCorrectFactor[aiTextureType_EMISSION_COLOR   ] = true;
                    break;
            }
        }
    }

    //
    // Now we can merge textures that needs merging
    //
    mergeDescMaterialTex(data, descMat);
}

void AssimpSceneFileType::mergeDescMaterialTex(SceneWriteData& data, const DescMaterial* descMat) const
{
    MaterialDesc* matDesc = descMat->getMaterialDesc();

    if (matDesc->getShadingModel() == MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
    {
        if (matDesc->getPbrSpecularMode())
        {
            mergeDescMaterialTexPbrSpecularGloss(data, descMat);
        }
        else
        {
            mergeDescMaterialTexPbrRoughMetal(data, descMat);
        }
    }
}

void AssimpSceneFileType::mergeDescMaterialTexPbrRoughMetal(SceneWriteData& data, const DescMaterial* descMat) const
{
    TextureDescUnrecPtr occlusion        = findTextureDesc(TextureDesc::AMBIENT_OCCLUSION_TEXTURE, data.vecTextureDescs);
    TextureDescUnrecPtr roughness        = findTextureDesc(TextureDesc::ROUGH_TEXTURE,             data.vecTextureDescs);
    TextureDescUnrecPtr metalness        = findTextureDesc(TextureDesc::METAL_TEXTURE,             data.vecTextureDescs);
    TextureDescUnrecPtr rough_metal      = findTextureDesc(TextureDesc::ROUGH_METAL_TEXTURE,       data.vecTextureDescs);
    TextureDescUnrecPtr occl_rough_metal = findTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE,  data.vecTextureDescs);

    bool remove_occlusion        = false;
    bool remove_roughness        = false;
    bool remove_metalness        = false;
    bool remove_rough_metal      = false;
    bool remove_occl_rough_metal = false;

    if (occl_rough_metal)
    {
        // nothing to do
    }
    else if (rough_metal)
    {
        if (occlusion)
        {
            if (bMergeableTextures(occlusion, rough_metal))
            {
                ImageUnrecPtr occl_rough_metal_img = mergeOcclRoughMetal(occlusion, rough_metal);

                if (occl_rough_metal_img)
                {
                    occl_rough_metal = createTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE, occlusion);
                    occl_rough_metal->setTexImage(occl_rough_metal_img);

                    data.vecTextureDescs.push_back(occl_rough_metal);
                }
            }
        }
    }
    else if (occlusion && (roughness || metalness))
    {
        if (roughness && metalness)
        {
            if (bMergeableTextures(occlusion, roughness, metalness))
            {
                ImageUnrecPtr occl_rough_metal_img = mergeOcclRoughMetal(occlusion, roughness, metalness);

                if (occl_rough_metal_img)
                {
                    occl_rough_metal = createTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE, occlusion);
                    occl_rough_metal->setTexImage(occl_rough_metal_img);

                    data.vecTextureDescs.push_back(occl_rough_metal);
                }
            }
        }
        else if (roughness)
        {
            if (bMergeableTextures(occlusion, roughness))
            {
                ImageUnrecPtr occl_rough_metal_img = mergeOcclRoughMetal(occlusion, roughness);

                if (occl_rough_metal_img)
                {
                    occl_rough_metal = createTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE, occlusion);
                    occl_rough_metal->setTexImage(occl_rough_metal_img);

                    data.vecTextureDescs.push_back(occl_rough_metal);
                }
            }
        }
        else if (metalness)
        {
            if (bMergeableTextures(occlusion, metalness))
            {
                ImageUnrecPtr occl_rough_metal_img = mergeOcclRoughMetal(occlusion, metalness);

                if (occl_rough_metal_img)
                {
                    occl_rough_metal = createTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE, occlusion);
                    occl_rough_metal->setTexImage(occl_rough_metal_img);

                    data.vecTextureDescs.push_back(occl_rough_metal);
                }
            }
        }
    }
    else if (roughness || metalness)
    {
        if (roughness && metalness)
        {
            if (bMergeableTextures(roughness, metalness))
            {
                ImageUnrecPtr rough_metal_img = mergeRoughMetal(roughness, metalness);

                if (rough_metal_img)
                {
                    rough_metal = createTextureDesc(TextureDesc::ROUGH_METAL_TEXTURE, roughness);
                    rough_metal->setTexImage(rough_metal_img);

                    data.vecTextureDescs.push_back(rough_metal);
                }
            }
        }
        else if (roughness)
        {
            ImageUnrecPtr rough_metal_img = mergeRoughMetal(roughness);

            if (rough_metal_img)
            {
                rough_metal = createTextureDesc(TextureDesc::ROUGH_METAL_TEXTURE, roughness);
                rough_metal->setTexImage(rough_metal_img);

                data.vecTextureDescs.push_back(rough_metal);
            }
        }
        else if (metalness)
        {
            ImageUnrecPtr rough_metal_img = mergeRoughMetal(metalness);

            if (rough_metal_img)
            {
                rough_metal = createTextureDesc(TextureDesc::ROUGH_METAL_TEXTURE, metalness);
                rough_metal->setTexImage(rough_metal_img);

                data.vecTextureDescs.push_back(rough_metal);
            }
        }
    }

    if (occl_rough_metal)
    {
        remove_occlusion   = true;
        remove_roughness   = true;
        remove_metalness   = true;
        remove_rough_metal = true;
    }
    else if (rough_metal)
    {
        remove_occlusion = true;
        remove_roughness = true;
        remove_metalness = true;
    }

    if (remove_occlusion       ) removeTextureDesc(occlusion,        data.vecTextureDescs);
    if (remove_roughness       ) removeTextureDesc(roughness,        data.vecTextureDescs);
    if (remove_metalness       ) removeTextureDesc(metalness,        data.vecTextureDescs);
    if (remove_rough_metal     ) removeTextureDesc(rough_metal,      data.vecTextureDescs);
    if (remove_occl_rough_metal) removeTextureDesc(occl_rough_metal, data.vecTextureDescs);
}

void AssimpSceneFileType::mergeDescMaterialTexPbrSpecularGloss(SceneWriteData& data, const DescMaterial* descMat) const
{
    TextureDescUnrecPtr specular         = findTextureDesc(TextureDesc::SPECULAR_TEXTURE,          data.vecTextureDescs);
    TextureDescUnrecPtr roughness        = findTextureDesc(TextureDesc::ROUGH_TEXTURE,             data.vecTextureDescs);
    TextureDescUnrecPtr rough_metal      = findTextureDesc(TextureDesc::ROUGH_METAL_TEXTURE,       data.vecTextureDescs);
    TextureDescUnrecPtr occl_rough_metal = findTextureDesc(TextureDesc::OCCL_ROUGH_METAL_TEXTURE,  data.vecTextureDescs);

    TextureDescUnrecPtr specular_gloss   = NULL;

    bool remove_specular         = false;
    bool remove_roughness        = false;
    bool remove_rough_metal      = false;
    bool remove_occl_rough_metal = false;

    TextureDesc* gloss = NULL;

    if (occl_rough_metal)
    {
        gloss = occl_rough_metal;
    }
    else if (rough_metal)
    {
        gloss = rough_metal;
    }
    else if (roughness)
    {
        gloss = roughness;
    }

    if (gloss)
    {
        if (specular)
        {
            ImageUnrecPtr specular_gloss_img = mergeSpecularGloss(specular, gloss);

            if (specular_gloss_img)
            {
                specular_gloss = createTextureDesc(TextureDesc::SPECULAR_TEXTURE, specular);
                specular_gloss->setTexImage(specular_gloss_img);

                data.vecTextureDescs.push_back(specular_gloss);
            }
        }
        else
        {
            ImageUnrecPtr specular_gloss_img = mergeSpecularGloss(gloss);

            if (specular_gloss_img)
            {
                specular_gloss = createTextureDesc(TextureDesc::SPECULAR_TEXTURE, gloss);
                specular_gloss->setTexImage(specular_gloss_img);

                data.vecTextureDescs.push_back(specular_gloss);
            }
        }
    }

    if (specular_gloss)
    {
        remove_roughness        = true;
        remove_rough_metal      = true;
        remove_occl_rough_metal = false;    // We still need occlusion!

        if (specular)
        {
            remove_specular = true;         // in this case we now have two SPECULR textures in our vector. The one
                                            // to be removed is the first one which will be removed removeTextureDesc() call.
        }
    }

    if (remove_specular        ) removeTextureDesc(specular,         data.vecTextureDescs);
    if (remove_roughness       ) removeTextureDesc(roughness,        data.vecTextureDescs);
    if (remove_rough_metal     ) removeTextureDesc(rough_metal,      data.vecTextureDescs);
    if (remove_occl_rough_metal) removeTextureDesc(occl_rough_metal, data.vecTextureDescs);
}

bool AssimpSceneFileType::validDescMaterialTexType(SceneWriteData& data, const DescMaterial* descMat, UInt32 textureType) const
{
    MaterialDesc* matDesc = descMat->getMaterialDesc();

    //
    // First we filter some textures due to the shading model in use
    //
    switch (matDesc->getShadingModel())
    {
        case MaterialDesc::GOURAUD_SHADING_MODEL:
            switch (textureType)
            {
                case TextureDesc::SPECULAR_TEXTURE:
                case TextureDesc::SHININESS_TEXTURE:
                case TextureDesc::ROUGH_TEXTURE:
                case TextureDesc::METAL_TEXTURE:
                case TextureDesc::ROUGH_METAL_TEXTURE:
                //case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:     // valid due to occlusion
                    return false;
            }
            break;

        case MaterialDesc::PHONG_SHADING_MODEL:
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:
        case MaterialDesc::TOON_SHADING_MODEL:
            switch (textureType)
            {
                case TextureDesc::ROUGH_TEXTURE:
                case TextureDesc::METAL_TEXTURE:
                case TextureDesc::ROUGH_METAL_TEXTURE:
                //case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:     // valid due to occlusion
                    return false;
            }
            break;

        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:
            switch (textureType)
            {
                case TextureDesc::SPECULAR_TEXTURE:
                case TextureDesc::METAL_TEXTURE:
                    return false;
            }
            break;
        case MaterialDesc::COOK_TORRANCE_SHADING_MODEL:
            if (matDesc->getPbrSpecularMode())
            {
                switch (textureType)
                {
                    case TextureDesc::METAL_TEXTURE:
                        return false;
                }
            }
            else
            {
                switch (textureType)
                {
                    case TextureDesc::SPECULAR_TEXTURE:
                        return false;
                }
                break;
            }
            break;
    }

    //
    // next filter generically
    //
    switch (textureType)
    {
        case TextureDesc::NONE_TEXTURE:
        case TextureDesc::UNKNOWN_TEXTURE:
            return false;

        case TextureDesc::ALBEDO_TEXTURE:
        case TextureDesc::SPECULAR_TEXTURE:
        case TextureDesc::EMISSIVE_TEXTURE:
        case TextureDesc::STANDARD_MATERIAL_TEXTURE:
        case TextureDesc::OPACITY_TEXTURE:
        case TextureDesc::NORMALS_TEXTURE:
        case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
        case TextureDesc::ROUGH_TEXTURE:
        case TextureDesc::METAL_TEXTURE:
        case TextureDesc::ROUGH_METAL_TEXTURE:
        case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
            return true;

        case TextureDesc::SHININESS_TEXTURE:
            // handled per exporter
            break;

        case TextureDesc::HEIGHT_TEXTURE:
        case TextureDesc::DISPLACEMENT_TEXTURE:
            return false;

        case TextureDesc::REFLECTION_TEXTURE:
        case TextureDesc::REFRACTION_TEXTURE:
        case TextureDesc::ANISOTROPY_U_TEXTURE:
        case TextureDesc::ANISOTROPY_V_TEXTURE:
        case TextureDesc::ANISOTROPY_UV_TEXTURE:
            return false;

        case TextureDesc::IRRADIANCE_TEXTURE:
        case TextureDesc::PRE_FILTER_TEXTURE:
        case TextureDesc::BRDF_LUT_TEXTURE:
            return false;
    }

    //
    // next handled per exporter
    //
    if (data.formatId == AssimpOptions::format_obj)
    {
        return validDescMaterialTexTypeOBJ(data, descMat, textureType);
    }

    if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
    {
        return validDescMaterialTexTypeGLTF(data, descMat, textureType);
    }

    return true;
}

bool AssimpSceneFileType::validDescMaterialTexTypeOBJ(SceneWriteData& data, const DescMaterial* descMat, UInt32 textureType) const
{
    switch (textureType)
    {
        case TextureDesc::SHININESS_TEXTURE:
            return true;
    }

    return true;
}

bool AssimpSceneFileType::validDescMaterialTexTypeGLTF(SceneWriteData& data, const DescMaterial* descMat, UInt32 textureType) const
{
    switch (textureType)
    {
        case TextureDesc::SHININESS_TEXTURE:
            return false;
    }

    return true;
}

void AssimpSceneFileType::handleDescMaterialTex(SceneWriteData& data, const DescMaterial* descMat, aiMaterial* ai_mat) const
{
    MaterialDesc* matDesc = descMat->getMaterialDesc();

    const BoostPath& dstDir = data.destination;
    BoostPath        folder = data.options.getTextureSubDirectory();

    Details::VecTextureParametersT vecTextureParameters;

    //
    // In the next texture iteration loop we copy all simple non merge textures to the destination.
    // 
    TextureDescStore::const_iterator iter = data.vecTextureDescs.begin();
    TextureDescStore::const_iterator  end = data.vecTextureDescs.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        UInt32 textureType = texDesc->getTextureType();

        BoostPath          filename      = texDesc->getFilename       ();
        ImageUnrecPtr      image         = texDesc->getTexImage       ();
        bool               hasSwizzle    = texDesc->hasSwizzle        ();
        bool               isSRGBTexture = texDesc->getIsSRGBTexture  ();
        UInt32             uvindex       = texDesc->getUVChannel      ();
        Real32             blendFactor   = texDesc->getBlendFactor    ();
        UInt32             mappingMode   = texDesc->getMappingMode    ();
        UInt32             operation     = texDesc->getOperation      ();
        GLenum             wrapS         = texDesc->getWrapS          ();
        GLenum             wrapT         = texDesc->getWrapT          ();
        GLenum             wrapR         = texDesc->getWrapR          ();
        GLenum             minFilter     = texDesc->getMinFilter      ();
        GLenum             magFilter     = texDesc->getMagFilter      ();
        Vec3f              mapAxis       = texDesc->getMapAxis        ();
        UInt32             textureFlags  = texDesc->getTextureFlags   ();
        bool               invertTexture = (textureFlags & TextureDesc::INVERT_FLAG) != 0;
        bool               hasTrafo      = texDesc->getHasUVTransform ();

        Details::TextureParameters primaryTexParam;

        aiUVTransform ai_transfrom;

        if (hasTrafo)
        {
            primaryTexParam.ai_matrix = texDesc->getMatrix();

            //
            // Assimp assumes a rotation around point P=(0.5,0.5).
            // The TextureDesc expects the rotation around point P'=(0,0)
            // The parameters scale,translate and rotate must be adapted accordingly
            //
            //
            // Assimp:       M  = S(sx,sy) * T(0.5,0.5) * R(r) * T(-0.5,-0.5) * T(tx,ty)
            // DescMaterial: M  = S(sx_,sy_) * R(r_) * T(tx_,ty_)
            //
            const Real32 PiFourth = 0.785398163398f;
            const Real32 InvSqrt2 = 0.707106781188f;

            Real32 r_  = texDesc->getRotate   ();
            Real32 sx_ = texDesc->getScale    ().x();
            Real32 sy_ = texDesc->getScale    ().y();
            Real32 tx_ = texDesc->getTranslate().x();
            Real32 ty_ = texDesc->getTranslate().y();

            Real32 r   = r_;
            Real32 sx  = sx_;
            Real32 sy  = sy_;
            Real32 tx  = tx_ - InvSqrt2 * osgSin(r + PiFourth) + 0.5f;
            Real32 ty  = ty_ - InvSqrt2 * osgCos(r + PiFourth) + 0.5f;
      
            ai_transfrom.mRotation    = r;
            ai_transfrom.mScaling     = aiVector2D(sx, sy);
            ai_transfrom.mTranslation = aiVector2D(tx, ty);

            if (!(   osgAbs(ai_transfrom.mRotation       ) > Eps
                  || osgAbs(1.f - ai_transfrom.mScaling.x) > Eps
                  || osgAbs(1.f - ai_transfrom.mScaling.y) > Eps
                  || osgAbs(  ai_transfrom.mTranslation.x) > Eps
                  || osgAbs(  ai_transfrom.mTranslation.y) > Eps))
            {
                hasTrafo = false;
            }
        }

        primaryTexParam.ai_number         = 0;
        primaryTexParam.ai_data_type      = image->getDataType();
        primaryTexParam.ai_pixel_format   = image->getPixelFormat();
        primaryTexParam.ai_srgb_encoding  = isSRGBTexture;
        primaryTexParam.ai_blend_factor   = Details::getTextureBlendFactor(blendFactor, operation);
        primaryTexParam.ai_mapping        = Details::getTextureMapping(mappingMode);
        primaryTexParam.ai_uv_index       = uvindex;
        primaryTexParam.ai_min_filter     = minFilter;
        primaryTexParam.ai_mag_filter     = magFilter;
        primaryTexParam.ai_operation      = Details::getTextureOperation(operation);
        primaryTexParam.ai_mapping_mode_u = Details::getTextureMappingMode(wrapS);
        primaryTexParam.ai_mapping_mode_v = Details::getTextureMappingMode(wrapT);
        primaryTexParam.ai_mapping_mode_U = wrapS;
        primaryTexParam.ai_mapping_mode_V = wrapT;
        primaryTexParam.ai_map_axis       = aiVector3D(mapAxis[0], mapAxis[1], mapAxis[2]);
        primaryTexParam.ai_texture_flags  = Details::getTextureFlags(textureFlags);
        primaryTexParam.ai_transform      = ai_transfrom;
        primaryTexParam.has_transform     = hasTrafo;

        image = resolveSwizzle(image, texDesc);
        image = resolveInvert(image, texDesc);

        if (image != texDesc->getTexImage())
        {
            filename = image->getName();
        }
        else
        {
            namespace fs = boost::filesystem;

            if (!fs::exists(filename) || !fs::is_regular_file(filename))
            {
                BoostPath alternaitve_filename = image->getName();

                if (fs::exists(alternaitve_filename) && fs::is_regular_file(alternaitve_filename))
                {
                    filename = alternaitve_filename;
                }
            }
        }

        Details::TextureParameters secondaryTexParam1, secondaryTexParam2;

        switch (textureType)
        {
            case TextureDesc::NONE_TEXTURE:
            case TextureDesc::UNKNOWN_TEXTURE:
                break;

            case TextureDesc::ALBEDO_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_DIFFUSE;

                        if (data.formatId != AssimpOptions::format_gltf2 && data.formatId != AssimpOptions::format_glb2)
                        {
                            secondaryTexParam1 = primaryTexParam;
                            secondaryTexParam1.ai_type = aiTextureType_AMBIENT;
                        }
                    }
                }
                break;
            case TextureDesc::SPECULAR_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_SPECULAR;
                    }
                }
                break;
            case TextureDesc::EMISSIVE_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_EMISSIVE;
                    }
                }
                break;
            case TextureDesc::SHININESS_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_SHININESS;
                    }
                }
                break;
            case TextureDesc::OPACITY_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_OPACITY;
                    }
                }
                break;
            case TextureDesc::NORMALS_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_NORMALS;
                    }
                }
                break;
            case TextureDesc::HEIGHT_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_HEIGHT;
                    }
                }
                break;
            case TextureDesc::DISPLACEMENT_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_HEIGHT; // inversion ???
                    }
                }
                break;
            case TextureDesc::ANISOTROPY_U_TEXTURE:
            case TextureDesc::ANISOTROPY_V_TEXTURE:
            case TextureDesc::ANISOTROPY_UV_TEXTURE:
                {
                    // not supported
                }
                break;
            case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_LIGHTMAP;
                    }
                }
                break;

            case TextureDesc::ROUGH_TEXTURE:
            case TextureDesc::METAL_TEXTURE:
                // We do only export ROUGH_METAL_TEXTURE or OCCL_ROUGH_METAL_TEXTURE
                // Normally, we won't have these textures anymore in the list. However, if they are still
                // in the list, we just ingnore them.
                break;
            // Env
            case TextureDesc::REFLECTION_TEXTURE:
            case TextureDesc::REFRACTION_TEXTURE:
            case TextureDesc::IRRADIANCE_TEXTURE:
            case TextureDesc::PRE_FILTER_TEXTURE:
            case TextureDesc::BRDF_LUT_TEXTURE:
                break;

            case TextureDesc::STANDARD_MATERIAL_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type     = aiTextureType_DIFFUSE;

                        if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
                        {
                            secondaryTexParam1 = primaryTexParam;
                            secondaryTexParam1.ai_type = aiTextureType_EMISSIVE;
                        }
                        else
                        {
                            secondaryTexParam1 = primaryTexParam;
                            secondaryTexParam2 = primaryTexParam;
                            
                            secondaryTexParam1.ai_type = aiTextureType_EMISSIVE;
                            secondaryTexParam2.ai_type = aiTextureType_AMBIENT;
                        }
                    }
                }
                break;

            case TextureDesc::ROUGH_METAL_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type = aiTextureType_UNKNOWN;
                    }
                }
                break;
            case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
                {
                    OptPathT primary_filename = copyOrWriteTexture(filename, dstDir, folder, image);
                    if (primary_filename)
                    {
                        primaryTexParam.ai_filename = primary_filename->generic_string();
                        primaryTexParam.ai_type = aiTextureType_UNKNOWN;

                        secondaryTexParam1 = primaryTexParam;
                        secondaryTexParam1.ai_type = aiTextureType_LIGHTMAP;    // ambient occlusion
                    }
                }
                break;
        }

        if (  primaryTexParam .ai_type != aiTextureType_NONE) vecTextureParameters.push_back(  primaryTexParam );
        if (secondaryTexParam1.ai_type != aiTextureType_NONE) vecTextureParameters.push_back(secondaryTexParam1);
        if (secondaryTexParam2.ai_type != aiTextureType_NONE) vecTextureParameters.push_back(secondaryTexParam2);
    }

    BOOST_FOREACH(Details::TextureParameters& params, vecTextureParameters)
    {
        handleTexMaterialTextureParams(data, params, ai_mat);
    }
}
    
//
// handleSimpleTextureMaterial
//

void AssimpSceneFileType::handleSimpleTexturedMaterial(SceneWriteData& data, const SimpleTexturedMaterial* mat, aiMaterial* ai_mat) const
{
}

//
// handleSimpleMaterial
//

void AssimpSceneFileType::handleSimpleMaterial(SceneWriteData& data, const SimpleMaterial* mat, aiMaterial* ai_mat) const
{
}

//
// handleChunkMaterial
//

void AssimpSceneFileType::handleChunkMaterial(SceneWriteData& data, const ChunkMaterial* mat, aiMaterial* ai_mat) const
{
}

AssimpSceneFileType::OptIndexT AssimpSceneFileType::getPrimaryMaterialData(SceneWriteData& data, unsigned int materialIndex, Matrix& trafo) const
{
    aiMaterial* ai_mat = NULL;
    if (!data.vecAiMaterials.empty())
        ai_mat = data.vecAiMaterials[materialIndex];
    
    if (ai_mat)
    {
        //
        // The primary UV coord index is by design the index of the first diffuse texture.
        //
        std::vector<aiTextureType> vecTypes;
        vecTypes.push_back(aiTextureType_DIFFUSE);
        vecTypes.push_back(aiTextureType_UNKNOWN);
        vecTypes.push_back(aiTextureType_SPECULAR);
        vecTypes.push_back(aiTextureType_AMBIENT);
        vecTypes.push_back(aiTextureType_EMISSIVE);
        vecTypes.push_back(aiTextureType_HEIGHT);
        vecTypes.push_back(aiTextureType_NORMALS);
        vecTypes.push_back(aiTextureType_SHININESS);
        vecTypes.push_back(aiTextureType_OPACITY);
        vecTypes.push_back(aiTextureType_DISPLACEMENT);
        vecTypes.push_back(aiTextureType_LIGHTMAP);
        vecTypes.push_back(aiTextureType_REFLECTION);
        vecTypes.push_back(aiTextureType_BASE_COLOR);
        vecTypes.push_back(aiTextureType_NORMAL_CAMERA);
        vecTypes.push_back(aiTextureType_EMISSION_COLOR);
        vecTypes.push_back(aiTextureType_METALNESS);
        vecTypes.push_back(aiTextureType_DIFFUSE_ROUGHNESS);
        vecTypes.push_back(aiTextureType_AMBIENT_OCCLUSION);

        BOOST_FOREACH(aiTextureType type, vecTypes)
        {
            unsigned int cnt = ai_mat->GetTextureCount(type);
            if (cnt >= 1)
            {
                for(unsigned int index = 0; index < cnt; index++)
                {
                    int mapping = static_cast<int>(aiTextureMapping_UV);
                    aiGetMaterialInteger(ai_mat, AI_MATKEY_MAPPING(type, index), &mapping);

                    if (mapping == aiTextureMapping_UV)
                    {
                        int uv_index = 0;
                        if (aiGetMaterialInteger(ai_mat, AI_MATKEY_UVWSRC(type, index), &uv_index) == AI_SUCCESS)
                        {
                            std::size_t primary_uv_index = static_cast<std::size_t>(uv_index);

                            trafo.setIdentity();
                            aiUVTransform ai_transfrom;
                            if (aiGetMaterialUVTransform(ai_mat, AI_MATKEY_UVTRANSFORM(type, index), &ai_transfrom) == AI_SUCCESS)
                            {
                                Real32 r  = ai_transfrom.mRotation;
                                Real32 sx = ai_transfrom.mScaling.x;
                                Real32 sy = ai_transfrom.mScaling.y;
                                Real32 tx = ai_transfrom.mTranslation.x;
                                Real32 ty = ai_transfrom.mTranslation.y;

                                if (   osgAbs(r)        > Eps
                                    || osgAbs(1.f - sx) > Eps
                                    || osgAbs(1.f - sy) > Eps
                                    || osgAbs(tx)       > Eps
                                    || osgAbs(ty)       > Eps)
                                {
                                    const Real32 PiFourth = 0.785398163398f;
                                    const Real32 InvSqrt2 = 0.707106781188f;

                                    Real32 r_  = r;
                                    Real32 sx_ = sx;
                                    Real32 sy_ = sy;
                                    Real32 tx_ = tx + InvSqrt2 * osgSin(r + PiFourth) - 0.5f;
                                    Real32 ty_ = ty + InvSqrt2 * osgCos(r + PiFourth) - 0.5f;

                                    Matrix mT;
                                    mT.setTranslate(tx_,ty_,0);
                                    Matrix mS;
                                    mS.setScale(sx_,sy_,0);
                                    Quaternion q;
                                    q.setValueAsAxisRad(Vec3f(0.f, 0.f, 1.f), r_);
                                    Matrix mR;
                                    mR.setRotate(q);

                                    trafo = mT;
                                    trafo.multLeft(mR);
                                    trafo.multLeft(mS);
                                }
                            }

                            return primary_uv_index;
                        }
                    }
                }
            }
        }
    }

    return boost::none;
}

void AssimpSceneFileType::setPrimaryMaterialData(SceneWriteData& data, unsigned int materialIndex, bool clear_trafo) const
{
    aiMaterial* ai_mat = NULL;
    if (!data.vecAiMaterials.empty())
        ai_mat = data.vecAiMaterials[materialIndex];
    
    if (ai_mat)
    {
        //
        // The primary UV coord index is by design the index of the first diffuse texture.
        //
        std::vector<aiTextureType> vecTypes;
        vecTypes.push_back(aiTextureType_DIFFUSE);
        vecTypes.push_back(aiTextureType_UNKNOWN);
        vecTypes.push_back(aiTextureType_SPECULAR);
        vecTypes.push_back(aiTextureType_AMBIENT);
        vecTypes.push_back(aiTextureType_EMISSIVE);
        vecTypes.push_back(aiTextureType_HEIGHT);
        vecTypes.push_back(aiTextureType_NORMALS);
        vecTypes.push_back(aiTextureType_SHININESS);
        vecTypes.push_back(aiTextureType_OPACITY);
        vecTypes.push_back(aiTextureType_DISPLACEMENT);
        vecTypes.push_back(aiTextureType_LIGHTMAP);
        vecTypes.push_back(aiTextureType_REFLECTION);
        vecTypes.push_back(aiTextureType_BASE_COLOR);
        vecTypes.push_back(aiTextureType_NORMAL_CAMERA);
        vecTypes.push_back(aiTextureType_EMISSION_COLOR);
        vecTypes.push_back(aiTextureType_METALNESS);
        vecTypes.push_back(aiTextureType_DIFFUSE_ROUGHNESS);
        vecTypes.push_back(aiTextureType_AMBIENT_OCCLUSION);

        BOOST_FOREACH(aiTextureType type, vecTypes)
        {
            unsigned int cnt = ai_mat->GetTextureCount(type);
            if (cnt >= 1)
            {
                for(unsigned int index = 0; index < cnt; index++)
                {
                    int mapping = static_cast<int>(aiTextureMapping_UV);
                    aiGetMaterialInteger(ai_mat, AI_MATKEY_MAPPING(type, index), &mapping);

                    if (mapping == aiTextureMapping_UV)
                    {
                        int uv_index = 0;
                        ai_mat->AddProperty(&uv_index, 1, AI_MATKEY_UVWSRC(type, index));
                        if (data.formatId == AssimpOptions::format_gltf2 || data.formatId == AssimpOptions::format_glb2)
                            ai_mat->AddProperty(&uv_index, 1, AI_MATKEY_GLTF_TEXTURE_TEXCOORD(type, index));

                        if (clear_trafo)
                        {
                            ai_mat->RemoveProperty(AI_MATKEY_UVTRANSFORM(type, index));
                        }
                    }
                }
            }
        }
    }
}

//
// Details
//

std::string AssimpSceneFileType::getWriteFormatIdentifier(const std::string& suffix) const
{
    std::string result;

         if (suffix == "3ds"   ) result = AssimpOptions::format_3ds;     // 3D Studio Max 3DS-Format
    else if (suffix == "3mf"   ) result = AssimpOptions::format_3mf;     // D3MF-Format
    else if (suffix == "assbin") result = AssimpOptions::format_assbin;  // Assimp Binary ASSBIN-Format
    else if (suffix == "assxml") result = AssimpOptions::format_assxml;  // Assimp XML Document ASSXML-Format
    else if (suffix == "json"  ) result = AssimpOptions::format_assjson; // Assimp JASON Document JSON-Format
    else if (suffix == "dae"   ) result = AssimpOptions::format_collada; // COLLADA-Format
    else if (suffix == "fbx"   ) result = AssimpOptions::format_fbx;     // Autodesk FBX-Format
    else if (suffix == "gltf"  ) result = AssimpOptions::format_gltf2;   // glTF2-Format
    else if (suffix == "glb"   ) result = AssimpOptions::format_glb2;    // gltf2-Format
    else if (suffix == "stp"   ) result = AssimpOptions::format_stp;     // Step IFC-Format
    else if (suffix == "obj"   ) result = AssimpOptions::format_obj;     // Wavefront Object OBJ-Format
    else if (suffix == "ply"   ) result = AssimpOptions::format_ply;     // Stanford Polygon Library PLY-Format
    else if (suffix == "plyb"  ) result = AssimpOptions::format_plyb;    // Stanford Polygon Library PLY-Format
    else if (suffix == "stl"   ) result = AssimpOptions::format_stl;     // Stereolithography STL-Format
    else if (suffix == "stlb"  ) result = AssimpOptions::format_stlb;    // Stereolithography STL-Format
    else if (suffix == "x3d"   ) result = AssimpOptions::format_x3d;     // Extensible X3D-Format
    else if (suffix == "x"     ) result = AssimpOptions::format_x;       // DirectX X-Format
    else if (suffix == "m3d"   ) result = AssimpOptions::format_m3d;     // Model 3D M3D-Format
    else if (suffix == "a3d"   ) result = AssimpOptions::format_m3da;    // Model 3D M3D-Format

    return result;
}

AssimpSceneFileType::OptIndexT AssimpSceneFileType::getExportFormatDescriptionIndex(
    const Char8*            fileNameOrExtension, 
    const Assimp::Exporter& exporter,
    const AssimpOptions&    options) const
{
    OptStringT suffix = getExtension(fileNameOrExtension);

    if (suffix)
    {
        std::string requested_format_id = options.getWriteFormatIdentifier();

        if (requested_format_id.empty())
        {
            // map from extension
            requested_format_id = getWriteFormatIdentifier(suffix.get());
        }

        std::string formatId;
        std::string extension;

        std::size_t count = exporter.GetExportFormatCount();

        for (std::size_t idx = 0; idx < count; ++idx)
        {
            const aiExportFormatDesc* desc = exporter.GetExportFormatDescription(idx);
            if (desc)
            {
                formatId  = desc->id;
                extension = desc->fileExtension;

                if (requested_format_id.empty())
                {
                    if (extension == suffix)
                    {
                        return idx;
                    }
                }
                else
                {
                    if (requested_format_id == formatId)
                    {
                        return idx;
                    }
                }
            }
        }
    }

    return boost::none;
}

TextureDescTransitPtr AssimpSceneFileType::createTextureDesc(UInt32 type, const TextureDesc* texDesc) const
{
    TextureDescUnrecPtr newTexDesc = dynamic_pointer_cast<TextureDesc>(texDesc->shallowCopyLocal());

    if (newTexDesc)
    {
        newTexDesc->setFilename    ("");
        newTexDesc->setSwizzle     ("rgba");
        newTexDesc->setTextureFlags(TextureDesc::EMPTY_FLAG);
        newTexDesc->setTextureType (type);
        newTexDesc->setTexImage    (NULL);
    }

    return TextureDescTransitPtr(newTexDesc);
}

TextureDescTransitPtr AssimpSceneFileType::findTextureDesc(UInt32 requestedType, const TextureDescStore& store) const
{
    TextureDescStore::const_iterator iter = store.begin();
    TextureDescStore::const_iterator end  = store.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        UInt32 textureType = texDesc->getTextureType();

        if (textureType == requestedType)
            return TextureDescTransitPtr(texDesc);
    }

    return TextureDescTransitPtr(NULL);
}

void AssimpSceneFileType::removeTextureDesc(const TextureDesc* texDesc, TextureDescStore& store) const
{
    if (!texDesc) return;

    TextureDescStore::iterator iter = store.begin();
    TextureDescStore::iterator end  = store.end  ();

    for (; iter != end; ++iter)
    {
        if (*iter == texDesc)
        {
            store.erase(iter);
            return;
        }
    }
}

bool AssimpSceneFileType::bMergeableTextures(const TextureDesc* texDesc1, const TextureDesc* texDesc2) const
{
    if (texDesc1 == NULL || texDesc2 == NULL) return false;

    if (
            texDesc1->getUVChannel     () == texDesc2->getUVChannel     ()
         && texDesc1->getMappingMode   () == texDesc2->getMappingMode   ()
         && texDesc1->getOperation     () == texDesc2->getOperation     ()
         && texDesc1->getWrapS         () == texDesc2->getWrapS         ()
         && texDesc1->getWrapT         () == texDesc2->getWrapT         ()
         && texDesc1->getWrapR         () == texDesc2->getWrapR         ()
         && texDesc1->getMinFilter     () == texDesc2->getMinFilter     ()
         && texDesc1->getMagFilter     () == texDesc2->getMagFilter     ()
         && texDesc1->getHasUVTransform() == texDesc2->getHasUVTransform()

         && osgAbs(texDesc1->getBlendFactor() - texDesc2->getBlendFactor()) < Eps

         && texDesc1->getMirrorFlags   () == 0
         && texDesc2->getMirrorFlags   () == 0
       )
    {
        if (texDesc1->getHasUVTransform())
        {
            if (    texDesc1->getScale    ().equals(texDesc2->getScale    (), Eps)
                 && texDesc1->getTranslate().equals(texDesc2->getTranslate(), Eps)

                 && osgAbs(texDesc1->getRotate() - texDesc2->getRotate()) < Eps
               )
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool AssimpSceneFileType::bMergeableTextures(const TextureDesc* texDesc1, const TextureDesc* texDesc2, const TextureDesc* texDesc3) const
{
    bool mergeable12 = bMergeableTextures(texDesc1, texDesc2);
    bool mergeable13 = bMergeableTextures(texDesc1, texDesc3);

    return mergeable12 && mergeable13;
}



AssimpSceneFileType::OptPathT AssimpSceneFileType::copyOrWriteTexture(const BoostPath& file, const BoostPath& dst, const BoostPath& folder, Image* image) const
{
    if (file.empty())
        return writeTexture(dst, folder, image);

    bool ok = false;
    BoostPath filename;

    if (image)
    {
        namespace fs = boost::filesystem;
        
        BoostPath src_file(file);

        filename = folder.empty() ? src_file.filename() : folder / src_file.filename();
        BoostPath dst_file(dst);
        dst_file /= filename;

        src_file.make_preferred();
        dst_file.make_preferred();

        if (!fs::exists(dst_file))
        {
            if (!fs::exists(dst_file.parent_path()))
            {
                fs::create_directories(dst_file.parent_path());
            }

            if (fs::exists(src_file) && fs::is_regular_file(src_file))
            {
                fs::copy_file(src_file, dst_file);
                ok = true;
            }
            else if (image)
            {
                ok = image->write(dst_file.string().c_str());
            }
        }
        else
        {
            ok = true;
        }
    }

    if (!ok || filename.empty())
        return boost::none;

    return filename;
}

AssimpSceneFileType::OptPathT AssimpSceneFileType::writeTexture(const BoostPath& dst, const BoostPath& folder, Image* image) const
{
    bool ok = false;
    BoostPath filename;

    if (image)
    {
        namespace fs = boost::filesystem;

        std::stringstream ss;

        ss << image->getHash();

        switch(image->getPixelFormat())
        {
            case Image::OSG_L_PF:
            case Image::OSG_RGB_PF:
                ss << ".jpg";
                break;
            default:
                ss << ".png";
        }

        filename = folder.empty() ? ss.str() : folder / ss.str();
        BoostPath dst_file(dst);
        dst_file /= filename;
        dst_file.make_preferred();

        if (!fs::exists(dst_file))
        {
            if (!fs::exists(dst_file.parent_path()))
            {
                fs::create_directories(dst_file.parent_path());
            }

            ok = image->write(dst_file.string().c_str());
        }
        else
        {
            ok = true;
        }
    }

    if (!ok || filename.empty())
        return boost::none;

    return filename;
}

Int32 AssimpSceneFileType::mergeImageDataType(Image* image, Int32 other_data_type) const
{
    if (!image)
        return other_data_type;

    Int32 type = image->getDataType();

    switch (type)
    {
        case Image::OSG_INVALID_IMAGEDATATYPE:
            return other_data_type;
        case Image::OSG_UINT8_IMAGEDATA:       // = GL_UNSIGNED_BYTE,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_UINT8_IMAGEDATA:
                    return Image::OSG_UINT8_IMAGEDATA;
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                    return other_data_type;
                case Image::OSG_INT16_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_UINT16_IMAGEDATA:      // = GL_UNSIGNED_SHORT,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                    return Image::OSG_UINT16_IMAGEDATA;
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                    return other_data_type;
                case Image::OSG_INT16_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_UINT32_IMAGEDATA:      // = GL_UNSIGNED_INT,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                    return Image::OSG_UINT32_IMAGEDATA;
                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                    return other_data_type;
                case Image::OSG_INT16_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_FLOAT16_IMAGEDATA:     // = GL_HALF_FLOAT_NV,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_INT16_IMAGEDATA:
                    return Image::OSG_FLOAT16_IMAGEDATA;
                case Image::OSG_FLOAT32_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                    return Image::OSG_FLOAT32_IMAGEDATA;
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_FLOAT32_IMAGEDATA:     // = GL_FLOAT,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                case Image::OSG_INT16_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                    return Image::OSG_FLOAT32_IMAGEDATA;
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_INT16_IMAGEDATA:       // = GL_SHORT,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_INT16_IMAGEDATA:
                    return Image::OSG_INT16_IMAGEDATA;

                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                    return other_data_type;

                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_INT32_IMAGEDATA:       // = GL_INT,
            switch (other_data_type)
            {
                case Image::OSG_INVALID_IMAGEDATATYPE:
                case Image::OSG_INT16_IMAGEDATA:
                case Image::OSG_INT32_IMAGEDATA:
                    return Image::OSG_INT32_IMAGEDATA;

                case Image::OSG_FLOAT16_IMAGEDATA:
                case Image::OSG_FLOAT32_IMAGEDATA:
                    return Image::OSG_FLOAT32_IMAGEDATA;

                case Image::OSG_UINT8_IMAGEDATA:
                case Image::OSG_UINT16_IMAGEDATA:
                case Image::OSG_UINT32_IMAGEDATA:
                case Image::OSG_UINT24_8_IMAGEDATA:
                    return Image::OSG_INVALID_IMAGEDATATYPE;
            }
            break;
        case Image::OSG_UINT24_8_IMAGEDATA:    // = OSG_GL_UNSIGNED_INT_24_8,
            return Image::OSG_INVALID_IMAGEDATATYPE;

        default:
            return Image::OSG_INVALID_IMAGEDATATYPE;
    }

    return type;
}

bool AssimpSceneFileType::supportedMergeFormat(Image* image) const
{
    if (image->hasCompressedData())
        return false;

    switch(image->getPixelFormat())
    {
        case Image::OSG_RGB_PF:
        case Image::OSG_RGBA_PF:
            break;

        case Image::OSG_BGR_PF:
        case Image::OSG_BGRA_PF:
            break;

        case Image::OSG_L_PF:
        case Image::OSG_LA_PF:
            break;

        default:
            return false;
    }

    return true;
}

bool AssimpSceneFileType::supportedMergeFormats(Image* image1, Image* image2) const
{
    bool result1 = supportedMergeFormat(image1);
    bool result2 = supportedMergeFormat(image2);

    return result1 && result2;
}

bool AssimpSceneFileType::supportedMergeFormats(Image* image1, Image* image2, Image* image3) const
{
    bool result1 = supportedMergeFormat(image1);
    bool result2 = supportedMergeFormat(image2);
    bool result3 = supportedMergeFormat(image3);

    return result1 && result2 && result3;
}

AssimpSceneFileType::PixelFormat AssimpSceneFileType::reformatImagePixelFormat(Image* image) const
{
    switch(image->getPixelFormat())
    {
        case Image::OSG_BGR_PF:  return Image::OSG_RGB_PF;
        case Image::OSG_BGRA_PF: return Image::OSG_RGBA_PF;
    }

    return Image::OSG_INVALID_PF;
}

ImageTransitPtr AssimpSceneFileType::resolveSwizzle(ImageUnrecPtr image, const TextureDesc* texDesc) const
{
    bool            hasSwizzle = texDesc->hasSwizzle ();
    SwizzleIndicesT swizzle    = texDesc->getSwizzleIndices();

    if (hasSwizzle)
        image = swizzleChannels(image, swizzle);

    return ImageTransitPtr(image);
}

ImageTransitPtr AssimpSceneFileType::resolveInvert(ImageUnrecPtr image, const TextureDesc* texDesc) const
{
    if (texDesc->isInverted())
    {
        image = invertColorChannels(image, texDesc->getIsSRGBTexture());
    }

    return ImageTransitPtr(image);
}

ImageTransitPtr AssimpSceneFileType::createMergeableImages(UInt32 pixelFormat, ImageUnrecPtr& img1) const
{
    Int32 dataType = mergeImageDataType(img1, Image::OSG_INVALID_IMAGEDATATYPE);

    if (dataType != Image::OSG_INVALID_IMAGEDATATYPE)
    {
        PixelFormat pixelFormat1 = reformatImagePixelFormat(img1);

        Int32 width = 0, height = 0, depth = 0;

        width = std::max(width, img1->getWidth()); height = std::max(height, img1->getHeight()); depth = std::max(depth, img1->getDepth());

        if (pixelFormat1)
        {
            ImageUnrecPtr img1Copy = Image::create();  img1Copy->set(img1); img1Copy->reformat(pixelFormat1); img1 = img1Copy;
        }

        ImageUnrecPtr image = Image::create();
        image->set(pixelFormat, width, height, depth, 1, 1, 0.0, nullptr, dataType, true, 1);

        return ImageTransitPtr(image);
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::createMergeableImages(UInt32 pixelFormat, ImageUnrecPtr& img1, ImageUnrecPtr& img2) const
{
    Int32 dataType = mergeImageDataType(img1, Image::OSG_INVALID_IMAGEDATATYPE);
          dataType = mergeImageDataType(img2, dataType);

    if (dataType != Image::OSG_INVALID_IMAGEDATATYPE)
    {
        PixelFormat pixelFormat1 = reformatImagePixelFormat(img1);
        PixelFormat pixelFormat2 = reformatImagePixelFormat(img2);

        Int32 width = 0, height = 0, depth = 0;

        width = std::max(width, img1->getWidth()); height = std::max(height, img1->getHeight()); depth = std::max(depth, img1->getDepth());
        width = std::max(width, img2->getWidth()); height = std::max(height, img2->getHeight()); depth = std::max(depth, img2->getDepth());

        bool scale1 = img1->getWidth() != width || img1->getHeight() != height || img1->getDepth() != depth;
        bool scale2 = img2->getWidth() != width || img2->getHeight() != height || img2->getDepth() != depth;

        if (pixelFormat1 || scale1)
        {
            ImageUnrecPtr img1Copy = Image::create();  img1Copy->set(img1); img1Copy->reformat(pixelFormat1); img1 = img1Copy;
        }

        if (pixelFormat2 || scale2)
        {
            ImageUnrecPtr img2Copy = Image::create();  img2Copy->set(img2); img2Copy->reformat(pixelFormat2); img2 = img2Copy;
        }

        if (scale1)
            img1->scale(width, height, depth);

        if (scale2)
            img2->scale(width, height, depth);

        ImageUnrecPtr image = Image::create();
        image->set(pixelFormat, width, height, depth, 1, 1, 0.0, nullptr, dataType, true, 1);

        return ImageTransitPtr(image);
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::createMergeableImages(UInt32 pixelFormat, ImageUnrecPtr& img1, ImageUnrecPtr& img2, ImageUnrecPtr& img3) const
{
    Int32 dataType = mergeImageDataType(img1, Image::OSG_INVALID_IMAGEDATATYPE);
          dataType = mergeImageDataType(img2, dataType);
          dataType = mergeImageDataType(img3, dataType);

    if (dataType != Image::OSG_INVALID_IMAGEDATATYPE)
    {
        PixelFormat pixelFormat1 = reformatImagePixelFormat(img1);
        PixelFormat pixelFormat2 = reformatImagePixelFormat(img2);
        PixelFormat pixelFormat3 = reformatImagePixelFormat(img3);

        Int32 width = 0, height = 0, depth = 0;

        width = std::max(width, img1->getWidth()); height = std::max(height, img1->getHeight()); depth = std::max(depth, img1->getDepth());
        width = std::max(width, img2->getWidth()); height = std::max(height, img2->getHeight()); depth = std::max(depth, img2->getDepth());
        width = std::max(width, img3->getWidth()); height = std::max(height, img3->getHeight()); depth = std::max(depth, img3->getDepth());

        bool scale1 = img1->getWidth() != width || img1->getHeight() != height || img1->getDepth() != depth;
        bool scale2 = img2->getWidth() != width || img2->getHeight() != height || img2->getDepth() != depth;
        bool scale3 = img3->getWidth() != width || img3->getHeight() != height || img3->getDepth() != depth;

        if (pixelFormat1 || scale1)
        {
            ImageUnrecPtr img1Copy = Image::create();  img1Copy->set(img1); img1Copy->reformat(pixelFormat1); img1 = img1Copy;
        }

        if (pixelFormat2 || scale2)
        {
            ImageUnrecPtr img2Copy = Image::create();  img2Copy->set(img2); img2Copy->reformat(pixelFormat2); img2 = img2Copy;
        }

        if (pixelFormat3 || scale3)
        {
            ImageUnrecPtr img3Copy = Image::create();  img3Copy->set(img3); img3Copy->reformat(pixelFormat3); img3 = img3Copy;
        }

        if (scale1)
            img1->scale(width, height, depth);

        if (scale2)
            img2->scale(width, height, depth);

        if (scale3)
            img3->scale(width, height, depth);

        ImageUnrecPtr image = Image::create();
        image->set(pixelFormat, width, height, depth, 1, 1, 0.0, nullptr, dataType, true, 1);

        return ImageTransitPtr(image);
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeOcclRoughMetal(const TextureDesc* texDescOcclu, const TextureDesc* texDescRough, const TextureDesc* texDescMetal) const
{
    ImageUnrecPtr imageOcclu =  texDescOcclu->getTexImage();
    ImageUnrecPtr imageRough =  texDescRough->getTexImage();
    ImageUnrecPtr imageMetal =  texDescMetal->getTexImage();

    if (supportedMergeFormats(imageOcclu, imageRough, imageMetal))
    {
        imageOcclu = resolveSwizzle(imageOcclu, texDescOcclu);
        imageRough = resolveSwizzle(imageRough, texDescRough);
        imageMetal = resolveSwizzle(imageMetal, texDescMetal);

        ImageUnrecPtr occlRoughMetal = createMergeableImages(Image::OSG_RGB_PF, imageOcclu, imageRough, imageMetal);
        if (occlRoughMetal)
        {
            occlRoughMetal->copyComponent(imageOcclu, 0, 0, Image::OSG_RGB_PF);
            occlRoughMetal->copyComponent(imageRough, 0, 1, Image::OSG_RGB_PF);
            occlRoughMetal->copyComponent(imageMetal, 0, 2, Image::OSG_RGB_PF);

            if (texDescOcclu->getIsSRGBTexture()) occlRoughMetal->convertImage(0, Image::OSG_CONVERT_TO_LINEAR_SPACE);
            if (texDescRough->getIsSRGBTexture()) occlRoughMetal->convertImage(1, Image::OSG_CONVERT_TO_LINEAR_SPACE);
            if (texDescMetal->getIsSRGBTexture()) occlRoughMetal->convertImage(2, Image::OSG_CONVERT_TO_LINEAR_SPACE);

            if (texDescOcclu->isInverted()) occlRoughMetal->flipComponent(0, false);
            if (texDescRough->isInverted()) occlRoughMetal->flipComponent(1, false);
            if (texDescMetal->isInverted()) occlRoughMetal->flipComponent(2, false);

            return ImageTransitPtr(occlRoughMetal);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeOcclRoughMetal(const TextureDesc* texDescOcclu, const TextureDesc* texDescOther) const
{
    ImageUnrecPtr imageOcclu =  texDescOcclu->getTexImage();
    ImageUnrecPtr imageOther =  texDescOther->getTexImage();

    if (supportedMergeFormats(imageOcclu, imageOther))
    {
        imageOcclu = resolveSwizzle(imageOcclu, texDescOcclu);
        imageOther = resolveSwizzle(imageOther, texDescOther);

        ImageUnrecPtr occlRoughMetal = createMergeableImages(Image::OSG_RGB_PF, imageOcclu, imageOther);
        if (occlRoughMetal)
        {
            switch (texDescOther->getTextureType())
            {
                case TextureDesc::ROUGH_TEXTURE:
                    occlRoughMetal->copyComponent(imageOcclu, 0, 0, Image::OSG_RGB_PF);
                    occlRoughMetal->copyComponent(imageOther, 0, 1, Image::OSG_RGB_PF);
                    occlRoughMetal-> setComponent(               2, 1.0, false);

                    if (texDescOther->getIsSRGBTexture()) occlRoughMetal->convertImage (1, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (texDescOther->isInverted      ()) occlRoughMetal->flipComponent(1, false);
                    break;
                case TextureDesc::METAL_TEXTURE:
                    occlRoughMetal->copyComponent(imageOcclu, 0, 0, Image::OSG_RGB_PF);
                    occlRoughMetal-> setComponent(               1, 1.0, false);
                    occlRoughMetal->copyComponent(imageOther, 0, 2, Image::OSG_RGB_PF);

                    if (texDescOther->getIsSRGBTexture()) occlRoughMetal->convertImage (2, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (texDescOther->isInverted      ()) occlRoughMetal->flipComponent(2, false);
                    break;
                case TextureDesc::ROUGH_METAL_TEXTURE:
                    occlRoughMetal->copyComponent(imageOcclu, 0, 0, Image::OSG_RGB_PF);
                    occlRoughMetal->copyComponent(imageOther, 1, 1, Image::OSG_RGB_PF);
                    occlRoughMetal->copyComponent(imageOther, 2, 2, Image::OSG_RGB_PF);

                    if (texDescOther->getIsSRGBTexture()) occlRoughMetal->convertImage (1, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (texDescOther->getIsSRGBTexture()) occlRoughMetal->convertImage (2, Image::OSG_CONVERT_TO_LINEAR_SPACE);

                    if (texDescOther->isInverted      ()) occlRoughMetal->flipComponent(1, false);
                    if (texDescOther->isInverted      ()) occlRoughMetal->flipComponent(2, false);
                    break;
            }

            if (texDescOcclu->getIsSRGBTexture()) occlRoughMetal->convertImage (0, Image::OSG_CONVERT_TO_LINEAR_SPACE);
            if (texDescOcclu->isInverted      ()) occlRoughMetal->flipComponent(0, false);

            return ImageTransitPtr(occlRoughMetal);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeRoughMetal(const TextureDesc* texDescRough, const TextureDesc* texDescMetal) const
{
    ImageUnrecPtr imageRough =  texDescRough->getTexImage();
    ImageUnrecPtr imageMetal =  texDescMetal->getTexImage();

    if (supportedMergeFormats(imageRough, imageMetal))
    {
        imageRough = resolveSwizzle(imageRough, texDescRough);
        imageMetal = resolveSwizzle(imageMetal, texDescMetal);

        ImageUnrecPtr roughMetal = createMergeableImages(Image::OSG_RGB_PF, imageRough, imageMetal);
        if (roughMetal)
        {
            roughMetal-> setComponent(0, 1.0, false);
            roughMetal->copyComponent(imageRough, 0, 1, Image::OSG_RGB_PF);
            roughMetal->copyComponent(imageMetal, 0, 2, Image::OSG_RGB_PF);

            if (texDescRough->getIsSRGBTexture()) roughMetal->convertImage(1, Image::OSG_CONVERT_TO_LINEAR_SPACE);
            if (texDescMetal->getIsSRGBTexture()) roughMetal->convertImage(2, Image::OSG_CONVERT_TO_LINEAR_SPACE);

            if (texDescRough->isInverted()) roughMetal->flipComponent(1, false);
            if (texDescMetal->isInverted()) roughMetal->flipComponent(2, false);

            return ImageTransitPtr(roughMetal);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeRoughMetal(const TextureDesc* texDesc) const
{
    ImageUnrecPtr image = texDesc->getTexImage();

    if (supportedMergeFormat(image))
    {
        image = resolveSwizzle(image, texDesc);

        ImageUnrecPtr roughMetal = createMergeableImages(Image::OSG_RGB_PF, image);
        if (roughMetal)
        {
            switch (texDesc->getTextureType())
            {
                case TextureDesc::ROUGH_TEXTURE:
                    roughMetal-> setComponent(          0, 1.0, false);
                    roughMetal->copyComponent(image, 0, 1, Image::OSG_RGB_PF);
                    roughMetal-> setComponent(          2, 1.0, false);

                    if (texDesc->getIsSRGBTexture()) roughMetal->convertImage (1, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (texDesc->isInverted      ()) roughMetal->flipComponent(1, false);
                    break;
                case TextureDesc::METAL_TEXTURE:
                    roughMetal-> setComponent(          0, 1.0, false);
                    roughMetal-> setComponent(          1, 1.0, false);
                    roughMetal->copyComponent(image, 0, 2, Image::OSG_RGB_PF);

                    if (texDesc->getIsSRGBTexture()) roughMetal->convertImage (2, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (texDesc->isInverted      ()) roughMetal->flipComponent(2, false);
                    break;
            }

            return ImageTransitPtr(roughMetal);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeSpecularGloss(const TextureDesc* texDescSpecu, const TextureDesc* texDescOther) const
{
    ImageUnrecPtr imageSpecu =  texDescSpecu->getTexImage();
    ImageUnrecPtr imageOther =  texDescOther->getTexImage();

    if (supportedMergeFormats(imageSpecu, imageOther))
    {
        imageSpecu = resolveSwizzle(imageSpecu, texDescSpecu);
        imageOther = resolveSwizzle(imageOther, texDescOther);

        ImageUnrecPtr specularGloss = createMergeableImages(Image::OSG_RGBA_PF, imageSpecu, imageOther);
        if (specularGloss)
        {
            std::vector<UInt8> channels(3); channels[0] = 0; channels[1] = 1;  channels[2] = 2; 
            specularGloss->copyComponents(imageSpecu, channels, channels, Image::OSG_RGBA_PF);

            switch (texDescOther->getTextureType())
            {
                case TextureDesc::ROUGH_TEXTURE:
                    specularGloss->copyComponent(imageOther, 0, 3, Image::OSG_RGBA_PF);

                    if ( texDescOther->getIsSRGBTexture()) specularGloss->convertImage (3, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (!texDescOther->isInverted      ()) specularGloss->flipComponent(3, false);    // given roughness, but we need gloss = 1-roughness
                    break;
                case TextureDesc::ROUGH_METAL_TEXTURE:
                case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
                    specularGloss->copyComponent(imageOther, 1, 3, Image::OSG_RGBA_PF);

                    if ( texDescOther->getIsSRGBTexture()) specularGloss->convertImage (3, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (!texDescOther->isInverted      ()) specularGloss->flipComponent(3, false);    // given roughness, but we need gloss = 1-roughness
                    break;
            }

            // Do not convert SRGB to linear
            if (texDescSpecu->isInverted      ()) for (UInt8 i = 0; i < 3; ++i) specularGloss->flipComponent(i, texDescSpecu->getIsSRGBTexture());

            return ImageTransitPtr(specularGloss);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::mergeSpecularGloss(const TextureDesc* texDesc) const
{
    ImageUnrecPtr image = texDesc->getTexImage();

    if (supportedMergeFormat(image))
    {
        image = resolveSwizzle(image, texDesc);

        ImageUnrecPtr specularGloss = createMergeableImages(Image::OSG_RGBA_PF, image);
        if (specularGloss)
        {
            switch (texDesc->getTextureType())
            {
                case TextureDesc::ROUGH_TEXTURE:
                    specularGloss-> setComponent(          0, 1.0, false);
                    specularGloss-> setComponent(          1, 1.0, false);
                    specularGloss-> setComponent(          2, 1.0, false);
                    specularGloss->copyComponent(image, 0, 3, Image::OSG_RGBA_PF);

                    if ( texDesc->getIsSRGBTexture()) specularGloss->convertImage (3, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (!texDesc->isInverted      ()) specularGloss->flipComponent(3, false);    // given roughness, but we need gloss = 1-roughness
                    break;
                case TextureDesc::ROUGH_METAL_TEXTURE:
                case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
                    specularGloss-> setComponent(          0, 1.0, false);
                    specularGloss-> setComponent(          1, 1.0, false);
                    specularGloss-> setComponent(          2, 1.0, false);
                    specularGloss->copyComponent(image, 1, 3, Image::OSG_RGBA_PF);

                    if ( texDesc->getIsSRGBTexture()) specularGloss->convertImage (3, Image::OSG_CONVERT_TO_LINEAR_SPACE);
                    if (!texDesc->isInverted      ()) specularGloss->flipComponent(3, false);    // given roughness, but we need gloss = 1-roughness
                    break;
            }

            return ImageTransitPtr(specularGloss);
        }
    }

    return ImageTransitPtr(NULL);
}

ImageTransitPtr AssimpSceneFileType::swizzleChannels(Image* image, SwizzleIndicesT swizzle) const
{
    ImageUnrecPtr swizzledImage = Image::create();

    swizzledImage->set(image);

    UInt8 numChannels = 0;

    switch(swizzledImage->getPixelFormat())
    {
        case Image::OSG_RGB_PF:
        case Image::OSG_BGR_PF:
            numChannels = 3;
            break;

        case Image::OSG_RGBA_PF:
        case Image::OSG_BGRA_PF:
            numChannels = 4;
            break;

        case Image::OSG_LA_PF:
            numChannels = 2;
            break;
    }

    for (UInt8 i = 0; i < numChannels; ++i)
    {
        UInt8 srcChannel = swizzle[i];
        UInt8 dstChannel = i;

        if (srcChannel != dstChannel && srcChannel < numChannels && dstChannel < numChannels)
        {
            swizzledImage->copyComponent(image, srcChannel, dstChannel);
        }
    }

    return ImageTransitPtr(swizzledImage);
}

ImageTransitPtr AssimpSceneFileType::invertColorChannels(Image* image, bool isSRGB) const
{
    ImageUnrecPtr invertedImage = Image::create();

    invertedImage->set(image);

    UInt8 numChannels = 0;

    switch(invertedImage->getPixelFormat())
    {
        case Image::OSG_RGB_PF:
        case Image::OSG_BGR_PF:
            numChannels = 3;
            break;

        case Image::OSG_RGBA_PF:
        case Image::OSG_BGRA_PF:
            numChannels = 3;    // only color channels
            break;

        case Image::OSG_LA_PF:  // only color channels
            numChannels = 1;
            break;
    }

    for (UInt8 i = 0; i < numChannels; ++i)
    {
        invertedImage->flipComponent(i, isSRGB);
    }

    return ImageTransitPtr(invertedImage);
}

namespace Details
{

aiTextureMapping getTextureMapping(UInt32 mappingMode)
{
    switch (mappingMode)
    {
        case TextureDesc::UV_MAPPING:           return aiTextureMapping_UV;
        case TextureDesc::SPHERE_MAPPING:       return aiTextureMapping_SPHERE;
        case TextureDesc::CYLINDER_MAPPING:     return aiTextureMapping_CYLINDER;
        case TextureDesc::BOX_MAPPING:          return aiTextureMapping_BOX;
        case TextureDesc::PLANE_MAPPING:        return aiTextureMapping_PLANE;
        case TextureDesc::OTHER_MAPPING:        return aiTextureMapping_OTHER;
        default:                                return aiTextureMapping_UV;
    }
}

aiTextureMapMode getTextureMappingMode(UInt32 wrap)
{
    switch (wrap)
    {
        case GL_REPEAT:          return aiTextureMapMode_Wrap;
        case GL_CLAMP_TO_EDGE:   return aiTextureMapMode_Clamp;
        case GL_CLAMP_TO_BORDER: return aiTextureMapMode_Decal;
        case GL_MIRRORED_REPEAT: return aiTextureMapMode_Mirror;
        default:                 return aiTextureMapMode_Wrap;
    }
}

unsigned int getTextureFlags(UInt32 flags)
{
    unsigned int ai_flags = 0;

    if (flags & TextureDesc::      INVERT_FLAG) ai_flags |= aiTextureFlags_Invert;
    if (flags & TextureDesc::   USE_ALPHA_FLAG) ai_flags |= aiTextureFlags_UseAlpha;
    if (flags & TextureDesc::IGNORE_ALPHA_FLAG) ai_flags |= aiTextureFlags_IgnoreAlpha;

    return ai_flags;
}

aiTextureOp getTextureOperation(UInt32 operation)
{
    switch (operation)
    {
        case TextureDesc::REPLACE_OPERATION:    return aiTextureOp_Multiply;    // see getBlendFactor()
        case TextureDesc::MULTIPLY_OPERATION:   return aiTextureOp_Multiply;
        case TextureDesc::ADD_OPERATION:        return aiTextureOp_Add;
        case TextureDesc::SUBTRACT_OPERATION:   return aiTextureOp_Subtract;
        case TextureDesc::DIVIDE_OPERATION:     return aiTextureOp_Divide;
        case TextureDesc::SMOOTHADD_OPERATION:  return aiTextureOp_SmoothAdd;
        case TextureDesc::SIGNEDADD_OPERATION:  return aiTextureOp_SignedAdd;
        default:                                return aiTextureOp_Multiply;
    }
}

float getTextureBlendFactor(Real32 factor, UInt32 operation)
{
    return (operation == TextureDesc::REPLACE_OPERATION ? 1.f : factor);
}

} // namespace Details

#endif // OSG_WITH_ASSIMP

OSG_END_NAMESPACE
