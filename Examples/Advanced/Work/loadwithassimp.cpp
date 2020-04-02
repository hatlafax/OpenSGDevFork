// OpenSG Test Example: ambientocclusion
//
// This example uses the SSAOStage in order to generate
// an ambient occlusion texture image that is then used
// for ambient lighting in the light shader.
//

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGFileSystem.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGSolidBackground.h>

// new headers: 
#include <OSGGLEXT.h>
#include <OSGSceneFileHandler.h>
#include <OSGAssimpSceneFileType.h>
#include <OSGAssimpOptions.h>
#include <OSGDescMaterialManager.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSSAOStage.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFileSystem.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>

// new headers: 
#include <OSGGLEXT.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGAssimpSceneFileType.h>
#include <OpenSG/OSGAssimpOptions.h>
#include <OpenSG/OSGDescMaterialManager.h>
#endif

// Test: Examination of Assimp supported files
bool disableExamine = true;

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// The scene
//
OSG::NodeRefPtr scene;

//
// DescMaterialManager
//
OSG::DescMaterialManagerRefPtr materialMan;

std::size_t file_index = 0;
std::vector<std::string> assimp_files;
std::map<std::string, OSG::UInt32> assimp_flags;

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

void print_state();
void print_help();

void initShader(OSG::ShaderProgram* shader)
{
}

void updateShader(OSG::ShaderProgram* shader)
{
}

void initialize_assimp_files()
{
    //assimp_files.push_back("d:/_xxx/work/tmp/Assimp/MetalRoughSpheresNoTextures/glTF/MetalRoughSpheresNoTextures.gltf");

    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SpecGlossVsMetalRough/glTF/SpecGlossVsMetalRough.gltf");
/*
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheres/glTF/MetalRoughSpheres.gltf");
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BarramundiFish/glTF/BarramundiFish.gltf");
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SciFiHelmet/glTF/SciFiHelmet.gltf");

    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SpecGlossVsMetalRough/glTF/SpecGlossVsMetalRough.gltf");
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SpecGlossVsMetalRough/glTF-Binary/SpecGlossVsMetalRough.glb");

    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF/BoxTextured.gltf");
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Binary/BoxTextured.glb");
    assimp_files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Embedded/BoxTextured.gltf");
*/
    //assimp_files.push_back("d:/_xxx/CADdyMFM2017_64/User/MOD/holder.stl");

    //assimp_files.push_back("d:/_xxx/work/tmp/test/Umgebung1.obj");
    //assimp_files.push_back("d:/_7561/CADdyMFM2018_64/User/MOD/x1.obj");
    //assimp_files.push_back("Data/dinopet.3ds");
    //assimp_files.push_back("Data/jet/HORNET_L.3DS");
    //assimp_files.push_back("Data/3D-Grafik/Clock/Clock N050411.3DS");

    //assimp_files.push_back("Data/MyNanoSuit.obj");
    //assimp_files.push_back("Data/industrial/EX50U.obj");
    //assimp_files.push_back("Data/nanosuit/nanosuit.obj");
    //assimp_files.push_back("Data/cyborg/cyborg.obj");
    //assimp_files.push_back("Data/3D-Grafik/A380/A380.obj");
    //assimp_flags["Data/3D-Grafik/A380/A380.obj"] = OSG::AssimpOptions::FlipWindingOrder | OSG::AssimpOptions::FlipUVs | OSG::AssimpOptions::FixInfacingNormals;
    //assimp_files.push_back("Data/3D-Grafik/AC Cobra/Shelby.obj");
    //assimp_files.push_back("Data/3D-Grafik/AirbusA310/Airbus A310.obj");
    //assimp_files.push_back("Data/3D-Grafik/AudiR8Spyder/3D Models/Audi_R8_2017.obj");
    //assimp_files.push_back("Data/3D-Grafik/Aventador/Avent.obj");
    //assimp_files.push_back("Data/3D-Grafik/BarChair/Bar_chair_2.obj");
    //assimp_files.push_back("Data/3D-Grafik/BB8/bb8.obj");
    //assimp_files.push_back("Data/3D-Grafik/BMW_M3_GTR/BMW_M3_GTR.obj");
    //assimp_files.push_back("Data/3D-Grafik/bugatti/bugatti.obj");
    //assimp_files.push_back("Data/3D-Grafik/Bullet/shareablebullet.obj");
    //assimp_files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-layers.obj");
    //assimp_files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-open.obj");
    //assimp_files.push_back("Data/3D-Grafik/Car/CCars09-10-sport.obj");
    //assimp_files.push_back("Data/3D-Grafik/Chair/Chair.obj");
    //assimp_files.push_back("Data/3D-Grafik/CHEVROLET_CAMARO_BB/obj/CAMARO.obj");
    //assimp_files.push_back("Data/3D-Grafik/Clocks/Clock_obj.obj");
    //assimp_files.push_back("Data/3D-Grafik/CocaCan/coke can 2.obj");
    //assimp_files.push_back("Data/3D-Grafik/CocaCola/Lata de refresco (alta resolución).obj");
    //assimp_files.push_back("Data/3D-Grafik/CocaCola/Lata de refresco (baja resolución).obj");
    //assimp_files.push_back("Data/3D-Grafik/Cyborg/el_negro_fullSize_no_stand_mm.obj");
    //assimp_files.push_back("Data/3D-Grafik/Diamond/Diamond.obj");
    //assimp_files.push_back("Data/3D-Grafik/DODGE_CHALLENGER_383_MAGNUM/CHALLENGER71.obj");
    //assimp_files.push_back("Data/3D-Grafik/Ferrari LaFerrari/OBJ Files/LaFerrari.obj");

    //assimp_files.push_back("Data/3D-Grafik/Gibson 335/Gibson 335_High_Poly.obj");
    //assimp_files.push_back("Data/3D-Grafik/Gibson 335/Gibson 335_Low_Poly.obj");
    //assimp_files.push_back("Data/3D-Grafik/Glock/OBJ MTL/Glock 3d.obj");
    //assimp_files.push_back("Data/3D-Grafik/HouseInterior/luxury house interior.obj");
    //assimp_files.push_back("Data/3D-Grafik/ImperialStarDestroyer/imperial.obj");
    //assimp_files.push_back("Data/3D-Grafik/IronMan/Iron_Man.obj");
    //assimp_files.push_back("Data/3D-Grafik/IronMan1/IronMan.obj");
    //assimp_files.push_back("Data/3D-Grafik/knight/knight.obj");
    //assimp_files.push_back("Data/3D-Grafik/Mark42_helmet/Mark 42 Helm.obj");
    //assimp_files.push_back("Data/3D-Grafik/MercedesBenzSLSAMG/sls_amg.obj");
    //assimp_files.push_back("Data/3D-Grafik/millenium-falcon/millenium-falcon.obj");
    //assimp_files.push_back("Data/3D-Grafik/Mustang-P-51/P-51 Mustang.obj");
    //assimp_files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.obj");
    //assimp_files.push_back("Data/3D-Grafik/P911GT/Porsche_911_GT2.obj");
    //assimp_files.push_back("Data/3D-Grafik/PorscheCarreraGT/carrgt.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks1.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks2.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks3.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks4.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks5.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks6.obj");
    //assimp_files.push_back("Data/3D-Grafik/Rocks/rocks7.obj");
    //assimp_files.push_back("Data/3D-Grafik/RS7/RS7.obj");
    //assimp_files.push_back("Data/3D-Grafik/TieFighter/TIE-fighter.obj");
    //assimp_files.push_back("Data/3D-Grafik/Truck/scania.obj");
    //assimp_files.push_back("Data/3D-Grafik/UH-60 Blackhawk/uh60.obj");
    //assimp_files.push_back("Data/3D-Grafik/VW/Touareg.obj");
    //assimp_files.push_back("Data/3D-Grafik/VW_Bus/VW_Bus.obj");
    //assimp_files.push_back("Data/3D-Grafik/Yamaha/Yamaha.obj");
}

bool examineAssimpSupportedFiles(bool disabled)
{
    if (disabled)
        return false;

    OSG::UInt32 examineFlags = OSG::AssimpOptions::ExamineAll & ~OSG::AssimpOptions::ExamineFaces;//ExamineNoDetails;

    //std::string test_file = "Data/industrial/EX50U.obj";
    //std::string test_file = "Data/dinopet.3ds";
    //std::string test_file = "Data/jet/HORNET_L.3DS";     // uesd if flag 'with_tests == false'
    //std::string test_file = "d:/_xxx/work/tmp/Assimp/MetalRoughSpheresNoTextures/glTF/MetalRoughSpheresNoTextures.gltf";

    std::string test_file = "d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF/BoxTextured.gltf";
    //std::string test_file = "d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Binary/BoxTextured.glb";
    //std::string test_file = "d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Embedded/BoxTextured.gltf";

    bool with_tests       = true;  // if false the test file 'test_file' is used only, otherwise the file list below is used
    bool with_data        = true;   // files from data resource directory
    bool with_assimp_test = true;

    bool with_regular     = true;  // seems to be ok
    bool with_crashed     = true;  // application crashes
    bool with_no_scene    = true;  // no scene is generated
    bool with_incomplete  = true;  // loaded but buggy
    bool with_not_valid   = true;  // unsupported format

    bool with_3d,   with_3ds,     with_3mf, with_ac,   with_amf, with_ase, with_b3d, with_blend,   with_bvh, with_cd4,
         with_cob,  with_csm,     with_dae, with_dxf,  with_fbx, with_glb, with_glt, with_gltf,    with_hmp, with_ifc,
         with_irr,  with_irrmesh, with_lwo, with_lws,  with_lxo, with_md2, with_md3, with_md5mesh, with_mdl, with_mesh,
         with_ms3d, with_nff,     with_obj, with_ogex, with_off, with_pk3, with_ply, with_q3o,     with_q3s, with_raw,
         with_sib,  with_smd,     with_stl, with_ter,  with_wrl, with_x,   with_x3d, with_xml,     with_zgl, with_xgl;

    with_3d   = with_3ds     = with_3mf = with_ac   = with_amf = with_ase = with_b3d = with_blend   = with_bvh = with_cd4  =
    with_cob  = with_csm     = with_dae = with_dxf  = with_fbx = with_glb = with_glt = with_gltf    = with_hmp = with_ifc  =
    with_irr  = with_irrmesh = with_lwo = with_lws  = with_lxo = with_md2 = with_md3 = with_md5mesh = with_mdl = with_mesh =
    with_ms3d = with_nff     = with_obj = with_ogex = with_off = with_pk3 = with_ply = with_q3o     = with_q3s = with_raw  =
    with_sib  = with_smd     = with_stl = with_ter  = with_wrl = with_x   = with_x3d = with_xml     = with_zgl = with_xgl  = false;

    with_glb = with_gltf = true;

    with_cd4 = false;  // CD4 needs extra SDK

    std::vector<std::string> files;

    if (with_tests)
    {
        if (with_data)
        {
            if (with_obj)
            {
                if (with_regular   ) files.push_back("Data/MyNanoSuit.obj");
                if (with_regular   ) files.push_back("Data/industrial/EX50U.obj");
                if (with_regular   ) files.push_back("Data/nanosuit/nanosuit.obj");
                if (with_regular   ) files.push_back("Data/cyborg/cyborg.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/A380/A380.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/Shelby.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AirbusA310/Airbus A310.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AudiR8Spyder/3D Models/Audi_R8_2017.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Aventador/Avent.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_2.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BB8/bb8.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BMW_M3_GTR/BMW_M3_GTR.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/bugatti/bugatti.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Bullet/shareablebullet.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-layers.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-open.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Chair/Chair.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CHEVROLET_CAMARO_BB/obj/CAMARO.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_obj.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCan/coke can 2.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCola/Lata de refresco (alta resolución).obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCola/Lata de refresco (baja resolución).obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Cyborg/el_negro_fullSize_no_stand_mm.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Diamond/Diamond.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/DODGE_CHALLENGER_383_MAGNUM/CHALLENGER71.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Ferrari LaFerrari/OBJ Files/LaFerrari.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Gibson 335/Gibson 335_High_Poly.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Gibson 335/Gibson 335_Low_Poly.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Glock/OBJ MTL/Glock 3d.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/HouseInterior/luxury house interior.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/ImperialStarDestroyer/imperial.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/IronMan/Iron_Man.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/IronMan1/IronMan.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/knight/knight.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Mark42_helmet/Mark 42 Helm.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/MercedesBenzSLSAMG/sls_amg.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/millenium-falcon/millenium-falcon.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Mustang-P-51/P-51 Mustang.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/P911GT/Porsche_911_GT2.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/PorscheCarreraGT/carrgt.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks1.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks2.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks3.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks4.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks5.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks6.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks7.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/RS7/RS7.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/TieFighter/TIE-fighter.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Truck/scania.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/UH-60 Blackhawk/uh60.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/VW/Touareg.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/VW_Bus/VW_Bus.obj");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Yamaha/Yamaha.obj");
            }

            if (with_3ds)
            {
                if (with_regular   ) files.push_back("Data/dinopet.3ds");
                if (with_regular   ) files.push_back("Data/84mosque-ciro.3DS");
                if (with_regular   ) files.push_back("Data/jet/HORNET_L.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/ShelbyWD.3ds");
                if (with_no_scene  ) files.push_back("Data/3D-Grafik/AirbusA310/Airbus A310.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_2.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BMW_M3_GTR/BMW_M3_GTR.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Boat2kristeff/Boat2kristeff.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-layers.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-open.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CHEVROLET_CAMARO_BB/3ds/CAMARO.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clock/Clock N050411.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_3ds.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Diamond/Diamond.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/DODGE_CHALLENGER_383_MAGNUM/CHALLENGER71.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/DODGE_CHALLENGER_383_MAGNUM/LICENSE.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Enginieer/MP_US_Engi.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/ImperialStarDestroyer/imperial.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Kamaz-5511/kamaz.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/millenium-falcon/millenium-falcon.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/MURCIELAGO640/LICENSE.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/MURCIELAGO640/MURCIELAGO640.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Mustang-P-51/P-51 Mustang.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Palme/Palm N080211.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Pflanze/Palm N270511.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks1.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks2.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks3.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks4.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks5.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks6.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks7.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/TieFighter/TIE-fighter.3DS");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Trees/trees9.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Truck/scania.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/UH-60 Blackhawk/uh60.3ds");
                if (with_regular   ) files.push_back("Data/3D-Grafik/VW/Touareg.3DS");
                if (with_regular   ) files.push_back("Data/build/cc-7.3DS");
                if (with_regular   ) files.push_back("Data/g3d/3ds/boulder/boulder.3DS");
                if (with_regular   ) files.push_back("Data/g3d/3ds/fantasy/house/hansehaus3_3ds.3ds");
                if (with_regular   ) files.push_back("Data/g3d/3ds/planes/cessna/CSSNA140.3DS");
                if (with_regular   ) files.push_back("Data/g3d/3ds/planes/cobra/COBRA.3DS");
                if (with_regular   ) files.push_back("Data/g3d/3ds/planes/f18/F18.3DS");
            }

            if (with_fbx)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/Shelby.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AirbusA310/Airbus A310.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Audi R8/Models/Audi R8.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AudiR8Spyder/3D Models/Audi_R8_2017.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Ballones/bat konak.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_2.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BB8/bb8.FBX");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_fbx.fbx");
                if (with_not_valid ) files.push_back("Data/3D-Grafik/CocaCan/coke can 2.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Engine Of Plane/Plane_Engine.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Enginieer/MP_US_Engi.FBX");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Glock/FBX/Glock 3d.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/ModernDesktop/Computer Desk.FBX");
                if (with_regular   ) files.push_back("Data/3D-Grafik/MURCIELAGO640/MURCIELAGO640.FBX");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.FBX");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Pillow/pillow.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks1.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks2.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks3.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks4.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks5.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks6.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks7.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/RS7/RS7.fbx");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Steam_Locomotive/Steam Locomotive.fbx");
            }

            if (with_blend)
            {
                if (with_no_scene  ) files.push_back("Data/cyborg/cyborg.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/Shelby.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/ShelbyWD.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AirbusA310/Airbus A310.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Audi R8/Audi R8- Studio Render Scene.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Audi R8/Audi R8.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AudiR8Spyder/3D Models/Audi_R8_2017.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Banketka/banketka/banketka.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_3_subdividion-ready.blend");
                if (with_crashed   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_4_subdividion-ready.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_Cycles.blend");
                if (with_crashed   ) files.push_back("Data/3D-Grafik/bugatti/bugatti.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Bullet/shareablebullet.blend");
                if (with_crashed   ) files.push_back("Data/3D-Grafik/Clocks/BGE_Clock.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_for_CYCLES.blend");
                if (with_crashed   ) files.push_back("Data/3D-Grafik/Clocks/Constrain_Clock.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Gibson 335/Gibson 335.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Glock/BLENDER FILES/Glock 3d.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.blend");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Pillow/pillow.blend");
            }

            if (with_cd4)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/Ballones/bat konak.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/BMW_M3_GTR/BMW_M3_GTR.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CC09-10-sport.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CC09-10-sport_C4DV9-Slider.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Chair/Chair.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCan/coke can 2.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCan/coke can.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCola/Lata de refresco.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Diamond/Diamond.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Estade/tutorialc4d.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Ferrari LaFerrari/Cinema 4D Files/laferrari 2.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/knight/knight.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Mark42_helmet/Mark 42 Helm.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Mustang-P-51/P-51 Mustang.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/RoboBaby/robot baby 3d.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks1.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks2.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks3.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks4.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks5.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks6.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks7.c4d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Yamaha/Yamaha.c4d");
            }

            if (with_dae)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/ShelbyWD.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Audi R8/Models/Audi R8.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Bullet/shareablebullet.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Carrier/model.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_dae.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Glock/DAE/Glock 3d.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/IronMan/Iron_Man.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks1.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks2.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks3.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks4.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks5.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks6.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Rocks/rocks7.dae");
                if (with_regular   ) files.push_back("Data/3D-Grafik/VW_Bus/VW_Bus.dae");
            }

            if (with_lwo)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/A380/A380.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Aventador/Avent-inter.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/x10-sport-layers.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/x10-sport-open.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/x10-sport.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/MercedesBenzSLSAMG/sls_amg.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/RS7/RS7.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Truck/scania.lwo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/UH-60 Blackhawk/uh60.lwo");
            }

            if (with_stl)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/AC Cobra/ShelbyWD.stl");
                if (with_regular   ) files.push_back("Data/3D-Grafik/AudiR8Spyder/3D Models/Audi_R8_2017.stl");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Cyborg/el_negro_fullSize_no_stand_mm.stl");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Glock/STL/Glock 3d.stl");
            }

            if (with_wrl)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-layers.wrl");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport-open.wrl");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Car/CCars09-10-sport.wrl");
            }

            if (with_lxo)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/Aventador/Avent-inter.lxo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Enginieer/MP_US_Engi.lxo");
                if (with_regular   ) files.push_back("Data/3D-Grafik/RS7/RS7.lxo");
            }

            if (with_x3d)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/BarChair/Bar_chair_2.x3d");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Clocks/Clock_x3d.x3d");
            }

            if (with_dxf)
            {
                if (with_regular   ) files.push_back("Data/3D-Grafik/CocaCan/coke can 2.dxf");
                if (with_regular   ) files.push_back("Data/3D-Grafik/Old House/Old House 2 3D Models.DXF");
            }

            if (with_md3)
            {
                if (with_regular   ) files.push_back("Data/g3d/md3/marvin/models/players/marvin/head.md3");
                if (with_regular   ) files.push_back("Data/g3d/md3/marvin/models/players/marvin/upper.md3");
                if (with_regular   ) files.push_back("Data/g3d/md3/marvin/models/players/marvin/lower.md3");
            }

            if (with_md2)
            {
                if (with_regular   ) files.push_back("Data/g3d/quake2/speedway/ferrari/weapon.md2");
            }

            if (with_pk3)
            {
                if (with_regular   ) files.push_back("Data/g3d/quake3/industrial/industrial.pk3");
                if (with_no_scene  ) files.push_back("Data/g3d/quake3/giantshome/giantshome.pk3");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/PK3/SGDTT3.pk3");
            }
        }
    
        if (with_assimp_test)
        {
            if (with_3d)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3D/box_a.3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3D/box_d.3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3D/mar_rifle_a.3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3D/mar_rifle_d.3d");
            }

            if (with_3ds)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/CameraRollAnim.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/CameraRollAnimWithChildObject.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/cubes_with_alpha.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/cube_with_diffuse_texture.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/cube_with_specular_texture.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/fels.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/RotatingCube.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/TargetCameraAnim.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/test1.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_Cube.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_Cube_ScaleUV2x_clampUV.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_Normal.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_OffsetU0.56V0.5_ScaleU10V2_Rotate45.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_OffsetU0.5_ScaleUV2_Rotate45_clampUV.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_OffsetUV0.5-clampUV.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_OffsetUV0.5-mirrorUV.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_OffsetUV0.5.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_ScaleUV1-2_OffsetUV0-0.9_Rotate-72_mirrorU.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_ScaleUV10-2_OffsetUV10-mirrorUV.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_ScaleUV2x.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3DS/UVTransformTest/UVTransform_ScaleUV2x_Rotate45.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/cart_wheel.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/Granate.3DS");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/jeep1.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/mar_rifle.3ds");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/mp5_sil.3ds");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/3DS/pyramob.3DS");
            }

            if (with_3mf)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/3MF/box.3mf");
            }

            if (with_ac)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/closedLine.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/nosurfaces.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/openLine.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/sample_subdiv.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/SphereWithLight.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/SphereWithLightUvScaling4X.ac");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/SphereWithLight_UTF16LE.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/SphereWithLight_UTF8BOM.ac");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AC/Wuson.ac");
            }

            if (with_amf)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test1.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test2.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test3.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test4.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test5.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test5a.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test6.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test7.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test8.amf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/AMF/test9.amf");
            }

            if (with_ase)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/anim.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/anim2.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/CameraRollAnim.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/CameraRollAnimWithChildObject.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/MotionCaptureROM.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/RotatingCube.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/TargetCameraAnim.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/TestUVTransform/UVTransform_Normal.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/TestUVTransform/UVTransform_ScaleUV1-2_OffsetUV0-0.9_Rotate-72_mirrorU.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/TestUVTransform/UVTransform_ScaleUV2x.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/TestUVTransform/UVTransform_ScaleUV2x_Rotate45.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/ThreeCubesGreen.ASE");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/ThreeCubesGreen_UTF16BE.ASE");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/ASE/ThreeCubesGreen_UTF16LE.ASE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/ASE/Rifle.ase");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/ASE/Rifle2.ase");
            }
        
            if (with_b3d)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/B3D/WusonBlitz.b3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/B3D/dwarf2.b3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/B3D/turtle1.b3d");
            }

            if (with_blend)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/4Cubes4Mats_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/AreaLight_269.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_248.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_250.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_250_Compressed.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_262.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_269.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderDefault_271.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/BlenderMaterial_269.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/blender_269_regress1.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/box.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/CubeHierarchy_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/HUMAN.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/MirroredCube_252.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/NoisyTexturedCube_VoronoiGlob_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/SmoothVsSolidCube_248.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/SuzanneSubdiv_252.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/Suzanne_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/TexturedCube_ImageGlob_248.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/TexturedPlane_ImageUvPacked_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/TexturedPlane_ImageUv_248.blend");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/TorusLightsCams_250_compressed.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BLEND/yxa_1.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/BLEND/Bob.blend");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/BLEND/fleurOptonl.blend");
            }

            if (with_bvh)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BVH/01_01.bvh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BVH/01_03.bvh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/BVH/Boxing_Toes.bvh");
            }

            if (with_cob)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/dwarf.cob");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/dwarf_ascii.cob");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/molecule.cob");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/molecule_ascii.cob");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/spider_4_3.cob");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/spider_4_3_ascii.cob");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/spider_6_6.cob");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/COB/spider_6_6_ascii.cob");
            }

            if (with_dae)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/anims_with_full_rotations_between_keys.DAE");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cameras.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/Cinema4D.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/COLLADA.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/COLLADA_triangulate.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/ConcavePolygon.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_emptyTags.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_triangulate.dae");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_tristrips.dae");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_UTF16LE.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_UTF8BOM.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_with_2UVs.DAE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/cube_xmlspecialchars.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/duck.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/duck_triangulate.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/earthCylindrical.DAE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/kwxport_test_vcolors.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/library_animation_clips.dae");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/lights.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/regr01.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/sphere.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/sphere_triangulate.dae");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/teapots.DAE");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Collada/teapot_instancenodes.DAE");
            }

            if (with_csm)
            {
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/CSM/ThomasFechten.csm");
            }

            if (with_dxf)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/DXF/lineTest.dxf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/DXF/PinkEggFromLW.dxf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/DXF/wuson.dxf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/DXF/rifle.dxf");
            }

            if (with_fbx)
            {
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/FBX/box.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/FBX/global_settings.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/FBX/phong_cube.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/FBX/spider.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/Cinema4D.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/COLLADA.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/ConcavePolygon.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/cube_with_2UVs.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/duck.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/Granate.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/jeep1.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/kwxport_test_vcolors.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/mar_rifle.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/mp5_sil.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_ASCII/pyramob.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/anims_with_full_rotations_between_keys.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/Cinema4D.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/COLLADA.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/ConcavePolygon.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/cube_with_2UVs.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/duck.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/Granate.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/jeep1.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/kwxport_test_vcolors.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/mar_rifle.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/mp5_sil.fbx");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/multiple_animations_test.fbx");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/FBX/2013_BINARY/pyramob.fbx");
            }

            if (with_gltf)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/BoxTextured-glTF/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/BoxTextured-glTF-Embedded/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/BoxTextured-glTF-MaterialsCommon/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/CesiumMilkTruck/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/TwoBoxes/TwoBoxes.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/BoxTextured-glTF/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/BoxTextured-glTF-Embedded/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/BoxTextured-glTF-pbrSpecularGlossiness/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/BoxTextured-glTF-techniqueWebGL/BoxTextured.gltf");

                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/2CylinderEngine/glTF/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/2CylinderEngine/glTF-Embedded/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/2CylinderEngine/glTF-MaterialsCommon/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Avocado/glTF/Avocado.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Avocado/glTF-Embedded/Avocado.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BarramundiFish/glTF/BarramundiFish.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BarramundiFish/glTF-Embedded/BarramundiFish.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Box/glTF/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Box/glTF-Embedded/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Box/glTF-MaterialsCommon/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxAnimated/glTF/BoxAnimated.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxAnimated/glTF-Embedded/BoxAnimated.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxAnimated/glTF-MaterialsCommon/BoxAnimated.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxSemantics/glTF/BoxSemantics.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxSemantics/glTF-Embedded/BoxSemantics.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxSemantics/glTF-MaterialsCommon/BoxSemantics.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxTextured/glTF/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxTextured/glTF-Embedded/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxTextured/glTF-MaterialsCommon/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxWithoutIndices/glTF/BoxWithoutIndices.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxWithoutIndices/glTF-Embedded/BoxWithoutIndices.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxWithoutIndices/glTF-MaterialsCommon/BoxWithoutIndices.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BrainStem/glTF/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BrainStem/glTF-Embedded/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BrainStem/glTF-MaterialsCommon/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Buggy/glTF/Buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Buggy/glTF-Embedded/buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Buggy/glTF-MaterialsCommon/Buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMan/glTF/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMan/glTF-Embedded/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMan/glTF-MaterialsCommon/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMilkTruck/glTF/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMilkTruck/glTF-Embedded/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMilkTruck/glTF-MaterialsCommon/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Duck/glTF/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Duck/glTF-Embedded/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Duck/glTF-MaterialsCommon/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/GearboxAssy/glTF/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/GearboxAssy/glTF-Embedded/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/GearboxAssy/glTF-MaterialsCommon/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Monster/glTF/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Monster/glTF-Embedded/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Monster/glTF-MaterialsCommon/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/ReciprocatingSaw/glTF/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/ReciprocatingSaw/glTF-Embedded/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/ReciprocatingSaw/glTF-MaterialsCommon/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedFigure/glTF/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedFigure/glTF-Embedded/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedFigure/glTF-MaterialsCommon/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedSimple/glTF/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedSimple/glTF-Embedded/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedSimple/glTF-MaterialsCommon/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/SmilingFace/glTF/SmilingFace.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/SmilingFace/glTF-Embedded/SmilingFace.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/VC/glTF/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/VC/glTF-Embedded/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/VC/glTF-MaterialsCommon/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/WalkingLady/glTF/WalkingLady.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/WalkingLady/glTF-Embedded/WalkingLady.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/WalkingLady/glTF-MaterialsCommon/WalkingLady.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/2CylinderEngine/glTF/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/2CylinderEngine/glTF-Draco/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/2CylinderEngine/glTF-Embedded/2CylinderEngine.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AlphaBlendModeTest/glTF/AlphaBlendModeTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AlphaBlendModeTest/glTF-Embedded/AlphaBlendModeTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedCube/glTF/AnimatedCube.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedMorphCube/glTF/AnimatedMorphCube.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedMorphSphere/glTF/AnimatedMorphSphere.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedTriangle/glTF/AnimatedTriangle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedTriangle/glTF-Embedded/AnimatedTriangle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AntiqueCamera/glTF/AntiqueCamera.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Avocado/glTF/Avocado.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Avocado/glTF-Draco/Avocado.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Avocado/glTF-pbrSpecularGlossiness/Avocado.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BarramundiFish/glTF/BarramundiFish.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BarramundiFish/glTF-Draco/BarramundiFish.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BarramundiFish/glTF-pbrSpecularGlossiness/BarramundiFish.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoomBox/glTF/BoomBox.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoomBox/glTF-Draco/BoomBox.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoomBox/glTF-pbrSpecularGlossiness/BoomBox.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoomBoxWithAxes/glTF/BoomBoxWithAxes.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Box/glTF/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Box/glTF-Draco/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Box/glTF-Embedded/Box.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxAnimated/glTF/BoxAnimated.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxAnimated/glTF-Embedded/BoxAnimated.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxInterleaved/glTF/BoxInterleaved.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxInterleaved/glTF-Embedded/BoxInterleaved.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Embedded/BoxTextured.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTexturedNonPowerOfTwo/glTF/BoxTexturedNonPowerOfTwo.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTexturedNonPowerOfTwo/glTF-Embedded/BoxTexturedNonPowerOfTwo.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxVertexColors/glTF/BoxVertexColors.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxVertexColors/glTF-Embedded/BoxVertexColors.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BrainStem/glTF/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BrainStem/glTF-Draco/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BrainStem/glTF-Embedded/BrainStem.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Buggy/glTF/Buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Buggy/glTF-Draco/Buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Buggy/glTF-Embedded/Buggy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Cameras/glTF/Cameras.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Cameras/glTF-Embedded/Cameras.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMan/glTF/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMan/glTF-Draco/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMan/glTF-Embedded/CesiumMan.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMilkTruck/glTF/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMilkTruck/glTF-Draco/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMilkTruck/glTF-Embedded/CesiumMilkTruck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Corset/glTF/Corset.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Corset/glTF-Draco/Corset.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Corset/glTF-pbrSpecularGlossiness/Corset.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Cube/glTF/Cube.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/DamagedHelmet/glTF/DamagedHelmet.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/DamagedHelmet/glTF-Embedded/DamagedHelmet.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Duck/glTF/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Duck/glTF-Draco/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Duck/glTF-Embedded/Duck.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/EnvironmentTest/glTF/EnvironmentTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/EnvironmentTest/glTF-IBL/EnvironmentTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/FlightHelmet/glTF/FlightHelmet.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/GearboxAssy/glTF/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/GearboxAssy/glTF-Draco/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/GearboxAssy/glTF-Embedded/GearboxAssy.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/InterpolationTest/glTF/InterpolationTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Lantern/glTF/Lantern.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Lantern/glTF-Draco/Lantern.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Lantern/glTF-pbrSpecularGlossiness/Lantern.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheres/glTF/MetalRoughSpheres.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheres/glTF-Embedded/MetalRoughSpheres.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheresNoTextures/glTF/MetalRoughSpheresNoTextures.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Monster/glTF/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Monster/glTF-Draco/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Monster/glTF-Embedded/Monster.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MorphPrimitivesTest/glTF/MorphPrimitivesTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MultiUVTest/glTF/MultiUVTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MultiUVTest/glTF-Embedded/MultiUVTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentMirrorTest/glTF/NormalTangentMirrorTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentMirrorTest/glTF-Embedded/NormalTangentMirrorTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentTest/glTF/NormalTangentTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentTest/glTF-Embedded/NormalTangentTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/OrientationTest/glTF/OrientationTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/OrientationTest/glTF-Embedded/OrientationTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/ReciprocatingSaw/glTF/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/ReciprocatingSaw/glTF-Draco/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/ReciprocatingSaw/glTF-Embedded/ReciprocatingSaw.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedFigure/glTF/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedFigure/glTF-Draco/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedFigure/glTF-Embedded/RiggedFigure.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedSimple/glTF/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedSimple/glTF-Draco/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedSimple/glTF-Embedded/RiggedSimple.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SciFiHelmet/glTF/SciFiHelmet.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleMeshes/glTF/SimpleMeshes.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleMeshes/glTF-Embedded/SimpleMeshes.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleMorph/glTF/SimpleMorph.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleMorph/glTF-Embedded/SimpleMorph.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleSparseAccessor/glTF/SimpleSparseAccessor.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SimpleSparseAccessor/glTF-Embedded/SimpleSparseAccessor.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SpecGlossVsMetalRough/glTF/SpecGlossVsMetalRough.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Sponza/glTF/Sponza.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Suzanne/glTF/Suzanne.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureCoordinateTest/glTF/TextureCoordinateTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureCoordinateTest/glTF-Embedded/TextureCoordinateTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureSettingsTest/glTF/TextureSettingsTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureSettingsTest/glTF-Embedded/TextureSettingsTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureTransformTest/glTF/TextureTransformTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Triangle/glTF/Triangle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Triangle/glTF-Embedded/Triangle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TriangleWithoutIndices/glTF-Embedded/TriangleWithoutIndices.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TwoSidedPlane/glTF/TwoSidedPlane.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/UnlitTest/glTF/UnlitTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VC/glTF/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VC/glTF-Draco/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VC/glTF-Embedded/VC.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VertexColorTest/glTF/VertexColorTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VertexColorTest/glTF-Embedded/VertexColorTest.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/WaterBottle/glTF/WaterBottle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/WaterBottle/glTF-Draco/WaterBottle.gltf");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/WaterBottle/glTF-pbrSpecularGlossiness/WaterBottle.gltf");
            }

            if (with_glb)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF/BoxTextured-glTF-Binary/BoxTextured.glb");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/2CylinderEngine-glTF-Binary/2CylinderEngine.glb");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/glTF2/BoxTextured-glTF-Binary/BoxTextured.glb");

                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/2CylinderEngine/glTF-Binary/2CylinderEngine.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Avocado/glTF-Binary/Avocado.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BarramundiFish/glTF-Binary/BarramundiFish.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Box/glTF-Binary/Box.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxAnimated/glTF-Binary/BoxAnimated.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxSemantics/glTF-Binary/BoxSemantics.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxTextured/glTF-Binary/BoxTextured.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BoxWithoutIndices/glTF-Binary/BoxWithoutIndices.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/BrainStem/glTF-Binary/BrainStem.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Buggy/glTF-Binary/Buggy.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMan/glTF-Binary/CesiumMan.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/CesiumMilkTruck/glTF-Binary/CesiumMilkTruck.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Duck/glTF-Binary/Duck.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/GearboxAssy/glTF-Binary/GearboxAssy.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/Monster/glTF-Binary/Monster.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/ReciprocatingSaw/glTF-Binary/ReciprocatingSaw.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedFigure/glTF-Binary/RiggedFigure.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/RiggedSimple/glTF-Binary/RiggedSimple.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/SmilingFace/glTF-Binary/SmilingFace.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/VC/glTF-Binary/VC.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/1.0/WalkingLady/glTF-Binary/WalkingLady.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/2CylinderEngine/glTF-Binary/2CylinderEngine.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AlphaBlendModeTest/glTF-Binary/AlphaBlendModeTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedMorphCube/glTF-Binary/AnimatedMorphCube.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AnimatedMorphSphere/glTF-Binary/AnimatedMorphSphere.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/AntiqueCamera/glTF-Binary/AntiqueCamera.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Avocado/glTF-Binary/Avocado.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BarramundiFish/glTF-Binary/BarramundiFish.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoomBox/glTF-Binary/BoomBox.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Box/glTF-Binary/Box.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxAnimated/glTF-Binary/BoxAnimated.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxInterleaved/glTF-Binary/BoxInterleaved.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTextured/glTF-Binary/BoxTextured.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxTexturedNonPowerOfTwo/glTF-Binary/BoxTexturedNonPowerOfTwo.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BoxVertexColors/glTF-Binary/BoxVertexColors.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/BrainStem/glTF-Binary/BrainStem.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Buggy/glTF-Binary/Buggy.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMan/glTF-Binary/CesiumMan.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/CesiumMilkTruck/glTF-Binary/CesiumMilkTruck.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Corset/glTF-Binary/Corset.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/DamagedHelmet/glTF-Binary/DamagedHelmet.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Duck/glTF-Binary/Duck.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/GearboxAssy/glTF-Binary/GearboxAssy.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/InterpolationTest/glTF-Binary/InterpolationTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Lantern/glTF-Binary/Lantern.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheres/glTF-Binary/MetalRoughSpheres.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MetalRoughSpheresNoTextures/glTF-Binary/MetalRoughSpheresNoTextures.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/Monster/glTF-Binary/Monster.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MorphPrimitivesTest/glTF-Binary/MorphPrimitivesTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MorphPrimitivesTest/glTF-Draco/MorphPrimitivesTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/MultiUVTest/glTF-Binary/MultiUVTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentMirrorTest/glTF-Binary/NormalTangentMirrorTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/NormalTangentTest/glTF-Binary/NormalTangentTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/OrientationTest/glTF-Binary/OrientationTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/ReciprocatingSaw/glTF-Binary/ReciprocatingSaw.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedFigure/glTF-Binary/RiggedFigure.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/RiggedSimple/glTF-Binary/RiggedSimple.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/SpecGlossVsMetalRough/glTF-Binary/SpecGlossVsMetalRough.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureCoordinateTest/glTF-Binary/TextureCoordinateTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/TextureSettingsTest/glTF-Binary/TextureSettingsTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/UnlitTest/glTF-Binary/UnlitTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VC/glTF-Binary/VC.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/VertexColorTest/glTF-Binary/VertexColorTest.glb");
                if (with_regular   ) files.push_back("d:/Models/glTF-Sample-Models-master/2.0/WaterBottle/glTF-Binary/WaterBottle.glb");
            }

            if (with_hmp)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/HMP/terrain.hmp");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/HMP/terrain_withtexture.hmp");
            }

            if (with_ifc)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IFC/AC14-FZK-Haus.ifc");
            }

            if (with_irr)
            {
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/animMesh.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/box.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/dawfInCellar_ChildOfCellar.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/dawfInCellar_SameHierarchy.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/EpisodeII_TheDwarfesStrikeBack.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/EpisodeI_ANewDwarf.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/instancing.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/multipleAnimators.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/scenegraphAnim.irr");
                if (with_incomplete) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRR/sphere.irr");
            }

            if (with_irrmesh)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRRMesh/cellar.irrmesh");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/IRRMesh/spider.irrmesh");
            }

            if (with_lwo)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/boxuv.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/box_2uv_1unused.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/box_2vc_1unused.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/concave_polygon.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/concave_self_intersecting.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/hierarchy.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/hierarchy_smoothed.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_x.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_x_scale_222_wrap_21.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_y.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_y_scale_111.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_y_scale_111_wrap_21.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_cylindrical_z.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_planar_x.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_planar_y.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_planar_z.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_planar_z_scale_111.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_spherical_x.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_spherical_x_scale_222_wrap_22.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_spherical_y.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_spherical_z.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_spherical_z_wrap_22.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/MappingModes/earth_uv_cylindrical_y.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/ModoExport_vertNormals.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/nonplanar_polygon.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/shader_test/CellShader.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/shader_test/fastFresnel.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/shader_test/realFresnel.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/shader_test/SuperCellShader.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/sphere_with_gradient.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/sphere_with_mat_gloss_10pc.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/Subdivision.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/transparency.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/UglyVertexColors.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWO2/uvtest.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWOB/ConcavePolygon.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWOB/MappingModes/bluewithcylindrictexz.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWOB/sphere_with_mat_gloss_10pc.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LWOB/sphere_with_mat_gloss_50pc.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/simple_cube.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Arm-ForeArm.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Arm-Shoulder.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Arm-Tip.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--CabinPortals.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Chasis.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--GP-Gun.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--GP-Lid.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--GP-Pod.lwo");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Laserbeam.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Standin-Driver.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Wheels-Back.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/LWSReferences/QuickDraw--Wheels-Front.lwo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWO/LWO2/rifle.lwo");
            }

            if (with_lxo)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LXOB_Modo/CrazyEngine.lxo");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWO/LXOB_Modo/sphereWithVertMap.lxo");
            }

            if (with_lws)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_xz_bezier.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_xz_hermite.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_xz_linear.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_xz_spline.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_xz_stepped.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_oldformat_56.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_oldformat_6.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_post_constant.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_post_linear.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_post_offset_repeat.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_post_repeat.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_x_post_reset.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/LWS/move_y_pre_ofrep_post_osc.lws");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/LWS/QuickDraw v.2.2.lws");
            }

            if (with_md2)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MD2/faerie.md2");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MD2/sydney.md2");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD2/dolphin.md2");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD2/flag.md2");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD2/horse.md2");
            }

            if (with_md3)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD3/q3root/models/mapobjects/kt_kubalwagon/european_fnt_v2.md3");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD3/watercan.md3");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD3/watercan_dmg.md3");
            }

            if (with_md5mesh)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MD5/SimpleCube.md5mesh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD5/BoarMan.md5mesh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MD5/Bob.md5mesh");
            }

            if (with_mdl)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MDL/MDL3 (3DGS A4)/minigun.MDL");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MDL/MDL5 (3DGS A5)/minigun_mdl5.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MDL/MDL5 (3DGS A5)/PhosphoricAcid_MDl5.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MDL/MDL7 (3DGS A7)/PhosphoricAcid_MDl7.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MDL/MDL7 (3DGS A7)/Sphere_DiffPinkBlueSpec_Alpha90.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MDL/IDPO (Quake1)/gijoe.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MDL/IDPO (Quake1)/steg.mdl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MDL/IDPO (Quake1)/tekmechbot.MDL");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/MDL/MDL7 (3DGS A7)/broadleavedtreeD.mdl");
            }

            if (with_ms3d)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MS3D/jeep1.ms3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MS3D/twospheres.ms3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MS3D/twospheres_withmats.ms3d");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/MS3D/Wuson.ms3d");
            }

            if (with_nff)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/cone.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/cylinder.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/dodecahedron.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/hexahedron.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/ManyEarthsNotJustOne.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/octahedron.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/positionTest.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/spheres.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/tetrahedron.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/NFF/NFF/WithCamera.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/NFF/NFFSense8/cokecan.nff");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/NFF/NFFSense8/HOME4.NFF");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/NFF/NFFSense8/teapot.nff");
            }

            if (with_obj)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/box.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/box_longline.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/box_mat_with_spaces.obj");
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/box_UTF16BE.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/box_without_lineending.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/concave_polygon.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/cube_mtllib_after_g.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/cube_usemtl.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/cube_with_vertexcolors.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/empty_mat.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/multiple_spaces.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/number_formats.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/regr01.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/regr_3429812.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/space_in_material_name.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/spider.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/testline.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/testmixed.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/testpoints.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OBJ/WusonOBJ.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/OBJ/rifle.obj");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/OBJ/segment.obj");
            }

            if (with_off)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OFF/Cube.off");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OFF/invalid.off");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OFF/Wuson.off");
            }

            if (with_mesh)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/fish.mesh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/ninja.mesh");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/razor.mesh");
            }

            if (with_xml)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Ogre/TheThing/Mesh.mesh.xml");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/fish.mesh.xml");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/ninja.mesh.xml");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/Ogre/OgreSDK/razor.mesh.xml");
            }

            if (with_ogex)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OpenGEX/animation_example.ogex");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OpenGEX/camera.ogex");
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OpenGEX/collada.ogex");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OpenGEX/Example.ogex");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/OpenGEX/light_issue1262.ogex");
            }

            if (with_ply)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/cube.ply");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/cube_binary.ply");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/cube_uv.ply");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/float-color.ply");
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/issue623.ply");
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/pond.0.ply");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/PLY/Wuson.ply");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/PLY/ant-half.ply");
            }

            if (with_q3o)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Q3D/E-AT-AT.q3o");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Q3D/earth.q3o");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Q3D/WusonOrange.q3o");
            }

            if (with_q3s)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/Q3D/WusonOrange.q3s");
            }

            if (with_raw)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/RAW/WithColor.raw");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/RAW/WithTexture.raw");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/RAW/Wuson.raw");
            }

            if (with_sib)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/SIB/heffalump.sib");
            }

            if (with_smd)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/SMD/holy_grailref.smd");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/SMD/triangle.smd");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/SMD/WusonSMD.smd");
            }

            if (with_stl)
            {
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/3DSMaxExport.STL");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/sphereWithHole.stl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/Spider_ascii.stl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/Spider_binary.stl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/triangle.stl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/triangle_with_two_solids.stl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/STL/Wuson.stl");
            }

            if (with_ter)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/TER/RealisticTerrain.ter");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/TER/RealisticTerrain_Large.ter");
            }

            if (with_wrl)
            {
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/WRL/MotionCaptureROM.WRL");
                if (with_crashed   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/WRL/Wuson.wrl");
            }

            if (with_x)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/anim_test.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/BCN_Epileptic.X");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/fromtruespace_bin32.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/kwxport_test_cubewithvcolors.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/test.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/Testwuson.X");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/test_cube_binary.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/test_cube_compressed.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X/test_cube_text.x");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/X/dwarf.x");
            }

            if (with_x3d)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/X3D/ComputerKeyboard.x3d");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models-nonbsd/X3D/Chevy/ChevyTahoe.x3d");
            }

            if (with_zgl)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/BCN_Epileptic.zgl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/cubes_with_alpha.zgl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/sphere_with_mat_gloss_10pc.zgl");
                if (with_no_scene  ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/Spider_ascii.zgl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/Wuson.zgl");
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/wuson_dxf.zgl");
            }

            if (with_xgl)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/sample_official.xgl");
            }

            if (with_xml)
            {
                if (with_regular   ) files.push_back("d:/_xxx/Comp/builder/support/assimp/test/models/XGL/sample_official_asxml.xml");
            }
        }
    }
    else
    {
        files.push_back(test_file);
    }

    //std::random_shuffle(files.begin(), files.end());

    OSG::AssimpSceneFileType& sceneFileType = OSG::AssimpSceneFileType::the();

    sceneFileType.setOptionAs("examine", true);
    sceneFileType.setOptionAs("exitOnExamination", true);
    sceneFileType.setOptionAs("examineFlags", examineFlags);

    for (std::size_t i = 0; i < files.size(); ++i)
    {
        const std::string file = files[i];

        std::string result;

        std::size_t p = file.rfind('/');
        if (p != std::string::npos)
        {
            std::string base = file.substr(p+1, file.length()-p-1);
            std::string path = std::string("d:/work/");

            result = path + std::string("0_") + base + std::string(".dmp");

            OSG::UInt32 iCnt = 0;
            while (OSG::File::tstAttr(result.c_str(), OSG::AccessFlags::IsReadable))
            {
                iCnt++;
                std::stringstream ss;
                ss << iCnt << std::flush;
                result = path + ss.str() + std::string("_") + base + std::string(".dmp");
            }

            std::cout << "read : " << file << " ... ";

            sceneFileType.setOption("examineFilename", result);
            OSG::NodeRefPtr test = OSG::SceneFileHandler::the()->read(
                                                                file.c_str(), 
                                                                NULL, // OSG::SceneFileHandler::the()->getDefaultGraphOp(),
                                                                0,
                                                                &sceneFileType);

            std::cout << "finished" << std::endl;
        }
    }

    sceneFileType.unsetOption("examineFlags");
    sceneFileType.unsetOption("exitOnExamination");
    sceneFileType.unsetOption("examine");
    
    return true;
}

void loadModel()
{
/*
        //
        // General explanation
        //
        OSG::NodeRefPtr modelNode;

        //
        // The AssimpSceneFileType is lazily initialized on first access. On default,
        // the specific OpenSG file type handler take precedence over the AssimpSceneFileType
        // handler.
        // In order to let the AssimpSceneFileType be favored, we have two alternatives.
        //
        // A) The first one is to lazy initialize the AssimpSceneFileType so that it is
        //    always preferred and the specific OpenSG handlers are not used in case that
        //    the AssimpSceneFileType handles the specific file format (i.e. "obj")
        //
        //OSG::AssimpSceneFileType& sceneFileType = OSG::AssimpSceneFileType::the(true, 30);

        //modelNode = OSG::SceneFileHandler::the()->read("Data/dinopet.3ds");
        //modelNode = OSG::SceneFileHandler::the()->read("Data/MyNanoSuit.obj");
        //modelNode = OSG::SceneFileHandler::the()->read("Data/84mosque-ciro.3DS");

        //
        // B) The second alternative is to use the default initialization scheme, that prefere
        //    the standard OpenSG handlers, but to explicitely provide the AssimpSceneFileType
        //    instance to the file I/O API. The advantage is that the application can use multiple
        //    handlers for one file format.
        //
        OSG::AssimpSceneFileType& sceneFileType = OSG::AssimpSceneFileType::the();

        //sceneFileType.setOptionAs("examine", true);
        //sceneFileType.setOptionAs("exitOnExamination", true);
        //modelNode = OSG::SceneFileHandler::the()->read(
        //                                                "Data/dinopet.3ds", 
        //                                                OSG::SceneFileHandler::the()->getDefaultGraphOp(),
        //                                                0,
        //                                                &sceneFileType);
        //sceneFileType.unsetOption("exitOnExamination");
        //sceneFileType.unsetOption("examine");

        //sceneFileType.setOption("examineFilename", "d:\\work\\MyNanoSuit.txt");
        //modelNode = OSG::SceneFileHandler::the()->read(
        //                                               "Data/MyNanoSuit.obj", 
        //                                               OSG::SceneFileHandler::the()->getDefaultGraphOp(),
        //                                               0,
        //                                               &sceneFileType);

        //modelNode = OSG::SceneFileHandler::the()->read(
        //                                               "Data/84mosque-ciro.3DS", 
        //                                               OSG::SceneFileHandler::the()->getDefaultGraphOp(),
        //                                               0,
        //                                               &sceneFileType);

        modelNode = OSG::SceneFileHandler::the()->read(
                                                       "Data/dinopet.3ds", 
                                                       OSG::SceneFileHandler::the()->getDefaultGraphOp(),
                                                       0,
                                                       &sceneFileType);

        scene->addChild(modelNode);
*/
    scene->clearChildren();

    const std::string& file = assimp_files[file_index];

    std::cout << "file = " << file << " ... ";

    OSG::AssimpSceneFileType& sceneFileType = OSG::AssimpSceneFileType::the();

    OSG::UInt32 uiExtraPostProcessSteps = 0;
    std::map<std::string, OSG::UInt32>::const_iterator iter = assimp_flags.find(file);
    if (iter != assimp_flags.end())
        uiExtraPostProcessSteps = iter->second;

    //sceneFileType.setOptionAs("forceTwosided", true);
    //sceneFileType.setOptionAs("shadingModel", OSG::MaterialDesc::GOURAUD_SHADING_MODEL);

    bool has_modified_opt = false;

    OSG::UInt32 flags = OSG::AssimpOptions::PostProcessSteps::TargetRealtime_Fast;
    flags &= ~OSG::AssimpOptions::PostProcessSteps::JoinIdenticalVertices;
    sceneFileType.setOptionAs("postProcessingFlags", flags);
    has_modified_opt = true;

    if (uiExtraPostProcessSteps != 0)
    {
        OSG::AssimpOptions options(sceneFileType.getOptions());
        OSG::UInt32 uiPostProcessSteps = options.getPostProcessingFlags();

        uiPostProcessSteps |= uiExtraPostProcessSteps;
        sceneFileType.setOptionAs("postProcessingFlags", uiPostProcessSteps);

        has_modified_opt = true;
    }

    OSG::NodeRefPtr modelNode = OSG::SceneFileHandler::the()->read(
                                                                    file.c_str(), 
                                                                    NULL, // OSG::SceneFileHandler::the()->getDefaultGraphOp(),
                                                                    0,
                                                                    &sceneFileType);
    if (has_modified_opt)
        sceneFileType.unsetOption("postProcessingFlags");


    // Test writing
    {
        
        std::string out_file = "d:\\work\\myTestFile.obj";

        //std::string out_file = "d:\\work\\myTestFile.gltf";
        //sceneFileType.setOptionAs("writeFormatIdentifier", OSG::AssimpOptions::format_gltf2);

        bool result = OSG::SceneFileHandler::the()->write(
                                                                modelNode,
                                                                out_file.c_str(), 
                                                                true,
                                                                &sceneFileType);

        sceneFileType.unsetOption("writeFormatIdentifier");
    }


    //sceneFileType.unsetOption("shadingModel");
    //sceneFileType.unsetOption("forceTwosided");

    if (modelNode != NULL)
    {
        scene->addChild(modelNode);

        std::cout << "Ok" << std::endl;
    }
    else
    {
        std::cout << "ERROR" << std::endl;
    }
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    // OSG init
    OSG::osgInit(argc,argv);

    print_help();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();

        // Test: Examination of Assimp supported files
        if (examineAssimpSupportedFiles(disableExamine))
            return 0;
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        //
        // Scene file handlers should use a material manager
        //
        // This examples uses the DescMaterialManager that can be setup as the
        // following verbose commented code snipped shows. However, a convenience
        // creation API 'createDefault' exist that make this tedious process as 
        // simple as it can be.
        //
        //OSG::ShaderProgramFunctor   initFunctor = boost::bind(::initShader,   _1);
        //OSG::ShaderProgramFunctor updateFunctor = boost::bind(::updateShader, _1);
        //
        //OSG::ShaderProgramManagerUnrecPtr shaderPrgMan = OSG::ShaderProgramManager::create();
        //shaderPrgMan->setInitCallback  (  initFunctor, "");
        //shaderPrgMan->setUpdateCallback(updateFunctor, "");
        //
        //OSG::DescMaterialShaderCodeGeneratorUnrecPtr generator = OSG::DescMaterialShaderCodeGenerator::create();
        //
        //OSG::ShaderManagerUnrecPtr shaderMan = OSG::ShaderManager::create();
        //shaderMan->setProgramManager(shaderPrgMan);
        //shaderMan->setCodeGenerator (generator);
        //
        //OSG::DescMaterialFactoryUnrecPtr factory = OSG::DescMaterialFactory::create();
        //factory->setShaderManager(shaderMan);
        //
        //materialMan = OSG::DescMaterialManager::create();
        //materialMan->setMaterialFactory(factory);
        //

        OSG::ShaderProgramFunctor   initFunctor = boost::bind(::initShader,   _1);
        OSG::ShaderProgramFunctor updateFunctor = boost::bind(::updateShader, _1);

        materialMan = OSG::DescMaterialManager::createDefault(initFunctor, "", updateFunctor, "");

        OSG::SceneFileHandler::the()->setMaterialManager(materialMan);

        scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());

        initialize_assimp_files();

        loadModel();

        OSG::commitChanges();
    
        mgr->setRoot(scene);
    
        // show the whole scene
        mgr->showAll();

        OSG::SolidBackgroundRefPtr background = OSG::SolidBackground::create();
        background->setColor(OSG::Color3f(0.5f,0.5f,0.5f));
        mgr->setBackground(background);

        OSG::commitChanges();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//
// redraw the window
//
void display(void)
{
    mgr->redraw();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            mgr          = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'n':
        {
            file_index++;
            if (file_index >= assimp_files.size())
                file_index = 0;

            loadModel();

            OSG::commitChanges();

            mgr->showAll();
        }
        break;
        case 'p':
        {
            if (file_index == 0)
                file_index = assimp_files.size();

            file_index--;

            loadModel();

            OSG::commitChanges();

            mgr->showAll();
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;

        case 'h':
        {
            print_help();
        }
        break;

        case 32:
        {
            std::cout << "Lool into the last model, obscure!" << std::endl;
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

void print_state()
{
}

void print_help()
{
    std::cout << "Esc : quit example" << std::endl;
    std::cout << "h   : print this help" << std::endl;
    std::cout << "n   : next model" << std::endl;
    std::cout << "p   : previous model" << std::endl;
    std::cout << "s   : statistic" << std::endl;
    std::cout << "SPC : statistic" << std::endl;
}
