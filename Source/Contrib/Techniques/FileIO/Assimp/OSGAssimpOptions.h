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

#ifndef _OSGASSIMPOPTIONS_H_
#define _OSGASSIMPOPTIONS_H_

/*! \file OSGAssimpOptions.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"
#include "OSGIOFileTypeBase.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTECHNIQUES_DLLMAPPING AssimpOptions
{
    /*==========================  PUBLIC  =================================*/
  public:
        //
        // The post processing flags are documented in the Assimp Lib documentation
        // (see file assimp/include/assimp/postprocess.h or
        //  http://sir-kimmi.de/assimp/lib_html/postprocess_8h.html#a64795260b95f5a4b3f3dc1be4f52e410)
        //
        enum PostProcessSteps
        {
            //
            // Calculates the tangents and bitangents for the imported meshes.
            //
            // Does nothing if a mesh does not have normals. You might want this post
            // processing step to be executed if you plan to use tangent space calculations
            // such as normal mapping  applied to the meshes. There's an importer property,
            // #AI_CONFIG_PP_CT_MAX_SMOOTHING_ANGLE, which allows you to specify
            // a maximum smoothing angle for the algorithm. However, usually you'll
            // want to leave it at the default value.
            //
            CalcTangentSpace            = 0x1,

            //
            // Identifies and joins identical vertex data sets within all
            // imported meshes.
            //
            // After this step is run, each mesh contains unique vertices,
            // so a vertex may be used by multiple faces. You usually want
            // to use this post processing step. If your application deals with
            // indexed geometry, this step is compulsory or you'll just waste rendering
            // time. If this flag is not specified, no vertices are referenced by
            // more than one face and no index buffer is required for rendering.
            //
            JoinIdenticalVertices       = 0x2,

            //
            // Converts all the imported data to a left-handed coordinate space.
            //
            // By default the data is returned in a right-handed coordinate space (which
            // OpenGL prefers). In this space, +X points to the right,
            // +Z points towards the viewer, and +Y points upwards. In the DirectX
            // coordinate space +X points to the right, +Y points upwards, and +Z points
            // away from the viewer.
            //
            // You'll probably want to consider this flag if you use Direct3D for
            // rendering. The ConvertToLeftHanded flag supersedes this
            // setting and bundles all conversions typically required for D3D-based
            // applications.
            //
            MakeLeftHanded              = 0x4,

            //
            // Triangulates all faces of all meshes.
            //
            // By default the imported mesh data might contain faces with more than 3
            // indices. For rendering you'll usually want all faces to be triangles.
            // This post processing step splits up faces with more than 3 indices into
            // triangles. Line and point primitives are//not* modified! If you want
            // 'triangles only' with no other kinds of primitives, try the following
            // solution:
            // 
            // Specify both Triangulate and SortByPType 
            // Ignore all point and line meshes when you process assimp's output
            // 
            //
            Triangulate                 = 0x8,

            //
            // Removes some parts of the data structure (animations, materials,
            // light sources, cameras, textures, vertex components).
            //
            // The  components to be removed are specified in a separate
            // importer property, #AI_CONFIG_PP_RVC_FLAGS. This is quite useful
            // if you don't need all parts of the output structure. Vertex colors
            // are rarely used today for example... Calling this step to remove unneeded
            // data from the pipeline as early as possible results in increased
            // performance and a more optimized output data structure.
            // This step is also useful if you want to force Assimp to recompute
            // normals or tangents. The corresponding steps don't recompute them if
            // they're already there (loaded from the source asset). By using this
            // step you can make sure they are NOT there.
            //
            // This flag is a poor one, mainly because its purpose is usually
            // misunderstood. Consider the following case: a 3D model has been exported
            // from a CAD app, and it has per-face vertex colors. Vertex positions can't be
            // shared, thus the JoinIdenticalVertices step fails to
            // optimize the data because of these nasty little vertex colors.
            // Most apps don't even process them, so it's all for nothing. By using
            // this step, unneeded components are excluded as early as possible
            // thus opening more room for internal optimizations.
            //
            RemoveComponent             = 0x10,

            //
            // Generates normals for all faces of all meshes.
            //
            // This is ignored if normals are already there at the time this flag
            // is evaluated. Model importers try to load them from the source file, so
            // they're usually already there. Face normals are shared between all points
            // of a single face, so a single point can have multiple normals, which
            // forces the library to duplicate vertices in some cases.
            // JoinIdenticalVertices is//senseless* then.
            //
            // This flag may not be specified together with GenSmoothNormals.
            //
            GenNormals                  = 0x20,

            //
            // Generates smooth normals for all vertices in the mesh.
            //
            // This is ignored if normals are already there at the time this flag
            // is evaluated. Model importers try to load them from the source file, so
            // they're usually already there.
            //
            // This flag may not be specified together with
            // GenNormals. There's a importer property,
            // #AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE which allows you to specify
            // an angle maximum for the normal smoothing algorithm. Normals exceeding
            // this limit are not smoothed, resulting in a 'hard' seam between two faces.
            // Using a decent angle here (e.g. 80 degrees) results in very good visual
            // appearance.
            //
            GenSmoothNormals            = 0x40,

            //
            // Splits large meshes into smaller sub-meshes.
            //
            // This is quite useful for real-time rendering, where the number of triangles
            // which can be maximally processed in a single draw-call is limited
            // by the video driver/hardware. The maximum vertex buffer is usually limited
            // too. Both requirements can be met with this step: you may specify both a
            // triangle and vertex limit for a single mesh.
            //
            // The split limits can (and should!) be set through the
            // #AI_CONFIG_PP_SLM_VERTEX_LIMIT and #AI_CONFIG_PP_SLM_TRIANGLE_LIMIT
            // importer properties. The default values are #AI_SLM_DEFAULT_MAX_VERTICES and
            // #AI_SLM_DEFAULT_MAX_TRIANGLES.
            //
            // Note that splitting is generally a time-consuming task, but only if there's
            // something to split. The use of this step is recommended for most users.
            //
            SplitLargeMeshes            = 0x80,

            //
            // Removes the node graph and pre-transforms all vertices with
            // the local transformation matrices of their nodes.
            //
            // The output scene still contains nodes, however there is only a
            // root node with children, each one referencing only one mesh,
            // and each mesh referencing one material. For rendering, you can
            // simply render all meshes in order - you don't need to pay
            // attention to local transformations and the node hierarchy.
            // Animations are removed during this step.
            // This step is intended for applications without a scenegraph.
            // The step CAN cause some problems: if e.g. a mesh of the asset
            // contains normals and another, using the same material index, does not,
            // they will be brought together, but the first meshes's part of
            // the normal list is zeroed. However, these artifacts are rare.
            // Note: The #AI_CONFIG_PP_PTV_NORMALIZE configuration property
            // can be set to normalize the scene's spatial dimension to the -1...1
            // range.
            //
            PreTransformVertices        = 0x100,

            //
            // Limits the number of bones simultaneously affecting a single vertex
            // to a maximum value.
            //
            // If any vertex is affected by more than the maximum number of bones, the least
            // important vertex weights are removed and the remaining vertex weights are
            // renormalized so that the weights still sum up to 1.
            // The default bone weight limit is 4 (defined as #AI_LMW_MAX_WEIGHTS in
            // config.h), but you can use the #AI_CONFIG_PP_LBW_MAX_WEIGHTS importer
            // property to supply your own limit to the post processing step.
            //
            // If you intend to perform the skinning in hardware, this post processing
            // step might be of interest to you.
            //
            LimitBoneWeights            = 0x200,

            //
            // Validates the imported scene data structure.
            // This makes sure that all indices are valid, all animations and
            // bones are linked correctly, all material references are correct .. etc.
            //
            // It is recommended that you capture Assimp's log output if you use this flag,
            // so you can easily find out what's wrong if a file fails the
            // validation. The validator is quite strict and will find//all*
            // inconsistencies in the data structure... It is recommended that plugin
            // developers use it to debug their loaders. There are two types of
            // validation failures:
            // 
            // Error: There's something wrong with the imported data. Further
            //  postprocessing is not possible and the data is not usable at all.
            //  The import fails. #Importer::GetErrorString() or #aiGetErrorString()
            //  carry the error message around.
            // Warning: There are some minor issues (e.g. 1000000 animation
            //  keyframes with the same time), but further postprocessing and use
            //  of the data structure is still safe. Warning details are written
            //  to the log file, #AI_SCENE_FLAGS_VALIDATION_WARNING is set
            //  in #aiScene::mFlags
            // 
            //
            // This post-processing step is not time-consuming. Its use is not
            // compulsory, but recommended.
            //
            ValidateDataStructure       = 0x400,

            //
            // Reorders triangles for better vertex cache locality.
            //
            // The step tries to improve the ACMR (average post-transform vertex cache
            // miss ratio) for all meshes. The implementation runs in O(n) and is
            // roughly based on the 'tipsify' algorithm (see 
            // "http://www.cs.princeton.edu/gfx/pubs/Sander_2007_%3ETR/tipsy.pdf").
            //
            // If you intend to render huge models in hardware, this step might
            // be of interest to you. The #AI_CONFIG_PP_ICL_PTCACHE_SIZE
            // importer property can be used to fine-tune the cache optimization.
            //
            ImproveCacheLocality        = 0x800,

            //
            // Searches for redundant/unreferenced materials and removes them.
            //
            // This is especially useful in combination with the
            // PreTransformVertices and OptimizeMeshes flags.
            // Both join small meshes with equal characteristics, but they can't do
            // their work if two meshes have different materials. Because several
            // material settings are lost during Assimp's import filters,
            // (and because many exporters don't check for redundant materials), huge
            // models often have materials which are are defined several times with
            // exactly the same settings.
            //
            // Several material settings not contributing to the final appearance of
            // a surface are ignored in all comparisons (e.g. the material name).
            // So, if you're passing additional information through the
            // content pipeline (probably using//magic* material names), don't
            // specify this flag. Alternatively take a look at the
            // #AI_CONFIG_PP_RRM_EXCLUDE_LIST importer property.
            //
            RemoveRedundantMaterials    = 0x1000,

            //
            // This step tries to determine which meshes have normal vectors
            // that are facing inwards and inverts them.
            //
            // The algorithm is simple but effective:
            // the bounding box of all vertices + their normals is compared against
            // the volume of the bounding box of all vertices without their normals.
            // This works well for most objects, problems might occur with planar
            // surfaces. However, the step tries to filter such cases.
            // The step inverts all in-facing normals. Generally it is recommended
            // to enable this step, although the result is not always correct.
            //
            FixInfacingNormals          = 0x2000,

            //
            // This step splits meshes with more than one primitive type in
            // homogeneous sub-meshes.
            //
            // The step is executed after the triangulation step. After the step
            // returns, just one bit is set in aiMesh::mPrimitiveTypes. This is
            // especially useful for real-time rendering where point and line
            // primitives are often ignored or rendered separately.
            // You can use the #AI_CONFIG_PP_SBP_REMOVE importer property to
            // specify which primitive types you need. This can be used to easily
            // exclude lines and points, which are rarely used, from the import.
            //
            SortByPType                 = 0x8000,

            //
            // This step searches all meshes for degenerate primitives and
            // converts them to proper lines or points.
            //
            // A face is 'degenerate' if one or more of its points are identical.
            // To have the degenerate stuff not only detected and collapsed but
            // removed, try one of the following procedures:
            // 1. (if you support lines and points for rendering but don't
            //   want the degenerates)
            // 
            //  Specify the FindDegenerates flag.
            //  
            //  Set the #AI_CONFIG_PP_FD_REMOVE importer property to
            //      1. This will cause the step to remove degenerate triangles from the
            //      import as soon as they're detected. They won't pass any further
            //      pipeline steps.
            //  
            // 
            // 2.(if you don't support lines and points at all)
            // 
            //  Specify the FindDegenerates flag.
            //  
            //  Specify the SortByPType flag. This moves line and
            //    point primitives to separate meshes.
            //  
            //  Set the #AI_CONFIG_PP_SBP_REMOVE importer property to
            //       aiPrimitiveType_POINTS | aiPrimitiveType_LINES
            //       to cause SortByPType to reject point
            //      and line meshes from the scene.
            //  
            // 
            //
            // This step also removes very small triangles with a surface area smaller
            // than 10^-6. If you rely on having these small triangles, or notice holes
            // in your model, set the property #AI_CONFIG_PP_FD_CHECKAREA to
            // false.
            // Note: Degenerate polygons are not necessarily evil and that's why
            // they're not removed by default. There are several file formats which
            // don't support lines or points, and some exporters bypass the
            // format specification and write them as degenerate triangles instead.
            //
            FindDegenerates             = 0x10000,

            //
            // This step searches all meshes for invalid data, such as zeroed
            // normal vectors or invalid UV coords and removes/fixes them. This is
            // intended to get rid of some common exporter errors.
            //
            // This is especially useful for normals. If they are invalid, and
            // the step recognizes this, they will be removed and can later
            // be recomputed, i.e. by the GenSmoothNormals flag.
            // The step will also remove meshes that are infinitely small and reduce
            // animation tracks consisting of hundreds if redundant keys to a single
            // key. The AI_CONFIG_PP_FID_ANIM_ACCURACY config property decides
            // the accuracy of the check for duplicate animation tracks.
            //
            FindInvalidData             = 0x20000,

            //
            // This step converts non-UV mappings (such as spherical or
            // cylindrical mapping) to proper texture coordinate channels.
            //
            // Most applications will support UV mapping only, so you will
            // probably want to specify this step in every case. Note that Assimp is not
            // always able to match the original mapping implementation of the
            // 3D app which produced a model perfectly. It's always better to let the
            // modelling app compute the UV channels - 3ds max, Maya, Blender,
            // LightWave, and Modo do this for example.
            //
            // Note: If this step is not requested, you'll need to process the
            // #AI_MATKEY_MAPPING material property in order to display all assets
            // properly.
            //
            GenUVCoords                 = 0x40000,

            //
            // This step applies per-texture UV transformations and bakes
            // them into stand-alone vtexture coordinate channels.
            //
            // UV transformations are specified per-texture - see the
            // #AI_MATKEY_UVTRANSFORM material key for more information.
            // This step processes all textures with
            // transformed input UV coordinates and generates a new (pre-transformed) UV channel
            // which replaces the old channel. Most applications won't support UV
            // transformations, so you will probably want to specify this step.
            //
            // Note: UV transformations are usually implemented in real-time apps by
            // transforming texture coordinates at vertex shader stage with a 3x3
            // (homogenous) transformation matrix.
            //
            TransformUVCoords           = 0x80000,

            //
            // This step searches for duplicate meshes and replaces them
            // with references to the first mesh.
            //
            // This step takes a while, so don't use it if speed is a concern.
            // Its main purpose is to workaround the fact that many export
            // file formats don't support instanced meshes, so exporters need to
            // duplicate meshes. This step removes the duplicates again. Please
            // note that Assimp does not currently support per-node material
            // assignment to meshes, which means that identical meshes with
            // different materials are currently//not* joined, although this is
            // planned for future versions.
            //
            FindInstances               = 0x100000,

            //
            // A post-processing step to reduce the number of meshes.
            //
            // This will, in fact, reduce the number of draw calls.
            //
            // This is a very effective optimization and is recommended to be used
            // together with OptimizeGraph, if possible. The flag is fully
            // compatible with both SplitLargeMeshes and SortByPType.
            //
            OptimizeMeshes              = 0x200000,


            //
            // A post-processing step to optimize the scene hierarchy.
            //
            // Nodes without animations, bones, lights or cameras assigned are
            // collapsed and joined.
            //
            // Node names can be lost during this step. If you use special 'tag nodes'
            // to pass additional information through your content pipeline, use the
            // #AI_CONFIG_PP_OG_EXCLUDE_LIST importer property to specify a
            // list of node names you want to be kept. Nodes matching one of the names
            // in this list won't be touched or modified.
            //
            // Use this flag with caution. Most simple files will be collapsed to a
            // single node, so complex hierarchies are usually completely lost. This is not
            // useful for editor environments, but probably a very effective
            // optimization if you just want to get the model data, convert it to your
            // own format, and render it as fast as possible.
            //
            // This flag is designed to be used with OptimizeMeshes for best
            // results.
            //
            // Note: 'Crappy' scenes with thousands of extremely small meshes packed
            // in deeply nested nodes exist for almost all file formats.
            // OptimizeMeshes in combination with OptimizeGraph
            // usually fixes them all and makes them renderable.
            //
            OptimizeGraph               = 0x400000,

            //
            // This step flips all UV coordinates along the y-axis and adjusts
            // material settings and bitangents accordingly.
            //
            // Output UV coordinate system:
            // 
            // 0y|0y ---------- 1x|0y
            // |                 |
            // |                 |
            // |                 |
            // 0x|1y ---------- 1x|1y
            // 
            //
            // You'll probably want to consider this flag if you use Direct3D for
            // rendering. The ConvertToLeftHanded flag supersedes this
            // setting and bundles all conversions typically required for D3D-based
            // applications.
            //
            FlipUVs                     = 0x800000,

            //
            // This step adjusts the output face winding order to be CW.
            //
            // The default face winding order is counter clockwise (CCW).
            //
            // Output face order:
            // 
            //      x2
            //
            //                        x0
            // x1
            //
            FlipWindingOrder            = 0x1000000,

            //
            // This step splits meshes with many bones into sub-meshes so that each
            // sub-mesh has fewer or as many bones as a given limit.
            //
            SplitByBoneCount            = 0x2000000,

            //
            // This step removes bones losslessly or according to some threshold.
            //
            // In some cases (i.e. formats that require it) exporters are forced to
            // assign dummy bone weights to otherwise static meshes assigned to
            // animated meshes. Full, weight-based skinning is expensive while
            // animating nodes is extremely cheap, so this step is offered to clean up
            // the data in that regard.
            //
            // Use #AI_CONFIG_PP_DB_THRESHOLD to control this.
            // Use #AI_CONFIG_PP_DB_ALL_OR_NONE if you want bones removed if and
            // only if all bones within the scene qualify for removal.
            //
            Debone                      = 0x4000000,

            //
            // This step will perform a global scale of the model.
            //
            // Some importers are providing a mechanism to define a scaling unit for the
            // model. This post processing step can be used to do so. You need to get the
            // global scaling from your importer settings like in FBX. Use the flag
            // AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY from the global property table to configure this.
            //
            // Use #AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY to setup the global scaling factor.
            //
            GlobalScale                 = 0x8000000,

            //
            // A postprocessing step to embed of textures.
            //
            // This will remove external data dependencies for textures.
            // If a texture's file does not exist at the specified path
            // (due, for instance, to an absolute path generated on another system),
            // it will check if a file with the same name exists at the root folder
            // of the imported model. And if so, it uses that.
            //
            EmbedTextures               = 0x10000000,

            ForceGenNormals             = 0x20000000,

            //
            // Drops normals for all faces of all meshes.
            //
            // This is ignored if no normals are present.
            // Face normals are shared between all points of a single face,
            // so a single point can have multiple normals, which
            // forces the library to duplicate vertices in some cases.
            // JoinIdenticalVertices is//senseless* then.
            // This process gives sense back to JoinIdenticalVertices
            //
            DropNormals                 = 0x40000000,

            //
            // 
            //
            GenBoundingBoxes            = 0x80000000,

            //
            //  Supersedes the MakeLeftHanded and FlipUVs and FlipWindingOrder flags.
            //
            //  The output data matches Direct3D's conventions: left-handed geometry, upper-left
            //  origin for UV coordinates and finally clockwise face order, suitable for CCW culling.
            //
            ConvertToLeftHanded         =
                MakeLeftHanded          |
                FlipUVs                 |
                FlipWindingOrder,

            //
            // Default postprocess configuration optimizing the data for real-time rendering.
            //
            // Applications would want to use this preset to load models on end-user PCs,
            // maybe for direct use in game.
            //
            // If you're using DirectX, don't forget to combine this value with
            // the ConvertToLeftHanded step. If you don't support UV transformations
            // in your application apply the TransformUVCoords step, too.
            // Note: Please take the time to read the docs for the steps enabled by this preset.
            // Some of them offer further configurable properties, while some of them might not be of
            // use for you so it might be better to not specify them.
            //
            TargetRealtime_Fast         =
                CalcTangentSpace        |
                GenNormals              |
                JoinIdenticalVertices   |
                Triangulate             |
                GenUVCoords             |
                SortByPType,

            //
            // Default postprocess configuration optimizing the data for real-time rendering.
            //
            // Unlike TargetRealtime_Fast, this configuration
            // performs some extra optimizations to improve rendering speed and
            // to minimize memory usage. It could be a good choice for a level editor
            // environment where import speed is not so important.
            //
            // If you're using DirectX, don't forget to combine this value with
            // the ConvertToLeftHanded step. If you don't support UV transformations
            // in your application apply the TransformUVCoords step, too.
            // Note: Please take the time to read the docs for the steps enabled by this preset.
            // Some of them offer further configurable properties, while some of them might not be
            // of use for you so it might be better to not specify them.
            //
            TargetRealtime_Quality      =
                CalcTangentSpace        |
                GenSmoothNormals        |
                JoinIdenticalVertices   |
                ImproveCacheLocality    |
                LimitBoneWeights        |
                RemoveRedundantMaterials|
                SplitLargeMeshes        |
                Triangulate             |
                GenUVCoords             |
                SortByPType             |
                FindDegenerates         |
                FindInvalidData,

            //
            // Default postprocess configuration optimizing the data for real-time rendering.
            //
            // This preset enables almost every optimization step to achieve perfectly
            // optimized data. It's your choice for level editor environments where import speed
            // is not important.
            //
            // If you're using DirectX, don't forget to combine this value with
            // the ConvertToLeftHanded step. If you don't support UV transformations
            // in your application, apply the TransformUVCoords step, too.
            // Note: Please take the time to read the docs for the steps enabled by this preset.
            // Some of them offer further configurable properties, while some of them might not be
            // of use for you so it might be better to not specify them.
            //
            TargetRealtime_MaxQuality   =
                TargetRealtime_Quality  |
                FindDegenerates         |
                FindInvalidData         |
                FindInstances           |
                ValidateDataStructure   |
                OptimizeMeshes,

            TargetRealtime_MaxOptimized   =
                TargetRealtime_MaxQuality |
                OptimizeGraph,

            DefaultPostProcessingOptions = 
                TargetRealtime_MaxOptimized |
                RemoveComponent,
        };

        enum Examine
        {
            ExamineNodes            = 0x00001,
            ExamineMesh             = 0x00002,
            ExamineTextures         = 0x00004,
            ExamineMaterial         = 0x00008,
            ExamineLights           = 0x00010,
            ExamineCameras          = 0x00020,
            ExamineAnimations       = 0x00040,
            ExamineBones            = 0x00080,
            ExamineFaces            = 0x00100,
            ExamineNormals          = 0x00200,
            ExaminePositions        = 0x00400,
            ExamineTangents         = 0x00800,
            ExamineUVCoords         = 0x01000,
            ExamineColors           = 0x02000,
            ExamineAniMesh          = 0x04000,
            ExamineNodeAnim         = 0x08000,
            ExamineMeshAnim         = 0x10000,
            ExamineMeshMorphAnim    = 0x20000,

            ExamineNoDetails        = ExamineNodes
                                    | ExamineMesh
                                    | ExamineTextures
                                    | ExamineMaterial,
            ExamineAll              = 0xfffff
        };

    static Char8* format_collada  ;  // "dae"      COLLADA - Digital Asset Exchange Schema
    static Char8* format_x        ;  // "x"        X Files
    static Char8* format_stp      ;  // "stp"      Step Files
    static Char8* format_obj      ;  // "obj"      Wavefront OBJ format
    static Char8* format_objnomtl ;  // "obj"      Wavefront OBJ format without material file
    static Char8* format_stl      ;  // "stl"      Stereolithography
    static Char8* format_stlb     ;  // "stl"      Stereolithography (binary)
    static Char8* format_ply      ;  // "ply"      Stanford Polygon Library  
    static Char8* format_plyb     ;  // "ply"      Stanford Polygon Library (binary)
    static Char8* format_3ds      ;  // "3ds"      Autodesk 3DS (legacy)
    static Char8* format_gltf2    ;  // "gltf"     GL Transmission Format v. 2
    static Char8* format_glb2     ;  // "glb"      GL Transmission Format v. 2 (binary)
    static Char8* format_gltf     ;  // "gltf"     GL Transmission Format
    static Char8* format_glb      ;  // "glb"      GL Transmission Format (binary) glb
    static Char8* format_assbin   ;  // "assbin"   Assimp Binary File
    static Char8* format_assxml   ;  // "assxml"   Assimp XML Document
    static Char8* format_x3d      ;  // "x3d"      Extensible 3D 
    static Char8* format_fbx      ;  // "fbx"      Autodesk FBX (binary)
    static Char8* format_fbxa     ;  // "fbx"      Autodesk FBX (ascii)   
    static Char8* format_m3d      ;  // "m3d"      Model 3D (binary)
    static Char8* format_m3da     ;  // "a3d"      Model 3D (ascii)   
    static Char8* format_3mf      ;  // "3mf"      The 3MF-File-Format
    static Char8* format_assjson  ;  // "json"     Assimp JSON Document

  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef AssimpOptions              Self;
    typedef IOFileTypeBase::OptionSet  OptionSet;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor/Destructor                                       */
    /*! \{                                                                 */

    explicit  AssimpOptions(      void             );
    explicit  AssimpOptions(const OptionSet &optSet);
             ~AssimpOptions(      void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Options                                                      */
    /*! \{                                                                 */

    void parseOptions(const OptionSet &optSet);

    UInt32              getPostProcessingFlags   (void                    ) const;
    void                setPostProcessingFlags   (UInt32             value);

    UInt32              getPreProcessingFlags    (void                    ) const;
    void                setPreProcessingFlags    (UInt32             value);

    UInt32              getExamineFlags          (void                    ) const;
    bool                hasExamineFlag           (Examine            flag ) const;
    void                setExamineFlags          (UInt32             value);

    const std::string&  getExamineFilename       (void                    ) const;
    void                setExamineFilename       (const std::string& value);

    bool                getExamine               (void                    ) const;
    void                setExamine               (bool               value);

    bool                getExitOnExamination     (void                    ) const;
    void                setExitOnExamination     (bool               value);

    bool                getInvertHeight          (void                    ) const;
    void                setInvertHeight          (bool               value);

    bool                getInvertDisplacement    (void                    ) const;
    void                setInvertDisplacement    (bool               value);

    bool                getForceTwosided         (void                    ) const;
    void                setForceTwosided         (bool               value);

    bool                getForceOpacityCorrection(void                    ) const;
    void                setForceOpacityCorrection(bool               value);

    bool                getNoSpecGlossGLTFExport (void                    ) const;
    void                setNoSpecGlossGLTFExport (bool               value);

    bool                getForceTexCoord0        (void                    ) const;
    void                setForceTexCoord0        (bool               value);

    bool                getTransformUVCoords     (void                    ) const;
    void                setTransformUVCoords     (bool               value);

    bool                getWriteMtyOnObjExport   (void                    ) const;
    void                setWriteMtyOnObjExport   (bool               value);

    bool                getTransformZToYOnExport (void                    ) const;
    void                setTransformZToYOnExport (bool               value);

    bool                getTransformYToZOnImport (void                    ) const;
    void                setTransformYToZOnImport (bool               value);

    Real32              getGlobalScaleOnImport   (void                    ) const;
    void                setGlobalScaleOnImport   (Real32             value);

    UInt32              getShadingModel          (void                    ) const;
    void                setShadingModel          (UInt32             value);

    const std::string&  getWriteFormatIdentifier (void                    ) const;
    void                setWriteFormatIdentifier (const std::string& value);

    const std::string&  getTextureSubDirectory   (void                    ) const;
    void                setTextureSubDirectory   (const std::string& value);

    bool                getLogMaterialDescOnWrite(void                   ) const;
    void                setLogMaterialDescOnWrite(bool               value);

    bool                getLogMaterialDescOnRead (void                    ) const;
    void                setLogMaterialDescOnRead (bool               value);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    static bool         getEnvBoolOption         (const Char8* option);

    UInt32      _postProcessingFlags;
    UInt32      _preProcessingFlags;
    UInt32      _examineFlags;
    std::string _examineFilename;
    bool        _examine;
    bool        _exitOnExamination;
    bool        _invertHeight;
    bool        _invertDisplacement;
    bool        _forceTwosided;
    bool        _forceOpacityCorrection;
    bool        _noSpecGlossGLTFExport;
    bool        _transformZToYOnExport;
    bool        _transformYToZOnImport;
    bool        _forceTexCoord0;
    bool        _transformUVCoords;
    bool        _writeMtyOnObjExport;
    Real32      _globalScaleOnImport;

    UInt32      _shadingModel;
    std::string _writeFormatIdentifier;
    std::string _textureSubDirectory;

    bool        _logMaterialDescOnWrite;
    bool        _logMaterialDescOnRead;
};

OSG_END_NAMESPACE

#endif // _OSGASSIMPOPTIONS_H_
