// OpenSG Test Example: descmaterial1.cpp
//
// This example shows the basic usage of the 'description' material DescMaterial
// and of the material manager DescMaterialManager.
// This material manager simply takes a MaterialDesc instance and returns a proper
// DescMaterial instance. Internally, it ensures that the DescMaterial instances
// are shared for equal descriptions.
// Function setupMaterial() performs all of the material related task of this
// example.
// The example also shows the usage alternatives of standard OpenGL lights vs
// multi lights (MultiLightGroup).
// Additionally, the example uses the following stages: HDR2Stage and SSAOStage.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGBaseHash.h>
#include <OSGChunkMaterial.h>
#include <OSGContribDDSImageFileType.h>
#include <OSGContribKTXImageFileType.h>
#include <OSGDescMaterial.h>
#include <OSGDescMaterialManager.h>
#include <OSGDirectionalLight.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGGroup.h>
#include <OSGHashKeyToFieldContainerMap.h>
#include <OSGHDR2Stage.h>
#include <OSGImageFileHandler.h>
#include <OSGMaterialDesc.h>
#include <OSGMaterialGroup.h>
#include <OSGMultiLightGroup.h>
#include <OSGPointLight.h>
#include <OSGSceneFileHandler.h>
#include <OSGShaderProgram.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSkyBackground.h>
#include <OSGSolidBackground.h>
#include <OSGSpotLight.h>
#include <OSGSSAOStage.h>
#include <OSGTextureDesc.h>
#include <OSGTextureObjChunk.h>
#include <OSGTransform.h>
#else
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseHash.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGContribDDSImageFileType.h>
#include <OpenSG/OSGContribKTXImageFileType.h>
#include <OpenSG/OSGDescMaterial.h>
#include <OpenSG/OSGDescMaterialManager.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGHashKeyToFieldContainerMap.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGMaterialDesc.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMultiLightGroup.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGSSAOStage.h>
#include <OpenSG/OSGTextureDesc.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTransform.h>
#endif

// Test code only begin
std::vector<std::string> init_ddsAndktxFiles()
{
    std::vector<std::string> files;

    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_11.dds");
    files.push_back("d:/_xxx/work/image/dds/yellow_girder_a.dds");
    files.push_back("d:/_xxx/work/image/dds/windmill_diffuse1.dds");
    files.push_back("d:/_xxx/work/image/dds/white_4x4.dds");
    files.push_back("d:/_xxx/work/image/dds/wallpaper20Bump.dds");
    files.push_back("d:/_xxx/work/image/dds/vent_02_DM.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_round_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/vase_round.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_hanging_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/Uffizi.dds");
    files.push_back("d:/_xxx/work/image/dds/tex1.dds");
    files.push_back("d:/_xxx/work/image/dds/terrain_heightmap.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/re_bar_a.dds");
    files.push_back("d:/_xxx/work/image/dds/Pisa.dds");
/*
    files.push_back("Data/pbr/mytest-brdf-lut.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/array_r8_uint.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/array_r8_uint.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/cube_rgba8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/cube_rgba8_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_a8_unorm.dds");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgr8_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgr8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgra8_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgra8_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgra8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgra8_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgrx8_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_bgrx8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_l8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r_ati1n_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r_ati1n_unorm_decompressed.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r_eac_snorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r_eac_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r16_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r5g6b5_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r5g6b5_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r8_sint.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_r8_uint.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg_ati2n_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg_ati2n_unorm_decompressed.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg_eac_snorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg_eac_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg11b10_ufloat.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rg11b10_ufloat.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_atc_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_dxt1_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_dxt1_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_etc1_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_etc1_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_etc2_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_etc2_srgb.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_etc2_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_pvrtc_2bpp_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_pvrtc_2bpp_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_pvrtc_4bpp_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb_pvrtc_4bpp_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb10a2_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb10a2u.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb5a1_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb5a1_unorm.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb5a1_unorm_.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb8_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb8_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb9e5_ufloat.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgb9e5_ufloat.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_astc12x12_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_astc4x4_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_astc4x4_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_astc8x5_srgb.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_astc8x8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_atc_explicit_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_atc_interpolate_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt1_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt1_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt1_unorm_decompressed.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt3_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt3_unorm_decompressed.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_unorm_decompressed.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_unorm1.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_dxt5_unorm2.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_etc2_a1_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_etc2_srgb.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_pvrtc2_2bpp_srgb.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_pvrtc2_2bpp_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_pvrtc2_4bpp_srgb.ktx");
    //files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_pvrtc2_4bpp_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba_pvrtc2_4bpp_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba16_sfloat.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba16_sfloat.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba4_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba4_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba8_snorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba8_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba8_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken7_rgba8_unorm.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken8_bgr8_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken8_rgba_dxt1_unorm.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken8_rgba8_srgb.dds");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/kueken8_rgba8_srgb.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/npot.ktx");
    files.push_back("d:/_xxx/Comp/prebuild/extern/gli/data/test.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/Dodge.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/Ennis.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/Glacier.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/GraceCathedral.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/Pisa.dds");
    files.push_back("d:/_xxx/work/Data/Cubemaps/Uffizi.dds");

    files.push_back("d:/_xxx/work/image/dds/arial_16_0.dds");
    files.push_back("d:/_xxx/work/image/dds/arial_64_0.dds");
    //files.push_back("d:/_xxx/work/image/dds/array.dds");
    files.push_back("d:/_xxx/work/image/dds/atlas.dds");
    files.push_back("d:/_xxx/work/image/dds/background.dds");
    files.push_back("d:/_xxx/work/image/dds/background_NRM.DDS");
    //files.push_back("d:/_xxx/work/image/dds/Bands.dds");
    files.push_back("d:/_xxx/work/image/dds/basket_map.dds");
    files.push_back("d:/_xxx/work/image/dds/Black_White_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_02.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_03.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_04.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_05.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_06.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_07.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_08.dds");
    files.push_back("d:/_xxx/work/image/dds/Blue_Fish_09.dds");
    files.push_back("d:/_xxx/work/image/dds/BODY03_color.dds");
    files.push_back("d:/_xxx/work/image/dds/brick_normal.dds");
    files.push_back("d:/_xxx/work/image/dds/buildingMap1_ILM.dds");
    files.push_back("d:/_xxx/work/image/dds/buildingMap2_ILM.dds");
    files.push_back("d:/_xxx/work/image/dds/buildingMap3_ILM.dds");
    files.push_back("d:/_xxx/work/image/dds/caustic1.dds");
    files.push_back("d:/_xxx/work/image/dds/caustic2.dds");
    files.push_back("d:/_xxx/work/image/dds/chain_texture.dds");
    files.push_back("d:/_xxx/work/image/dds/chain_texture_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/checker.dds");
    files.push_back("d:/_xxx/work/image/dds/checker_gamma.dds");
    files.push_back("d:/_xxx/work/image/dds/checker_linear.dds");
    files.push_back("d:/_xxx/work/image/dds/Clouds.dds");
    files.push_back("d:/_xxx/work/image/dds/command_a.dds");
    files.push_back("d:/_xxx/work/image/dds/con_edge.dds");
    files.push_back("d:/_xxx/work/image/dds/concrete649_small.dds");
    files.push_back("d:/_xxx/work/image/dds/container_grn_num.dds");
    files.push_back("d:/_xxx/work/image/dds/container_gry_num.dds");
    files.push_back("d:/_xxx/work/image/dds/container_hab_num.dds");
    files.push_back("d:/_xxx/work/image/dds/container_orn_num.dds");
    files.push_back("d:/_xxx/work/image/dds/crane_light.dds");
    files.push_back("d:/_xxx/work/image/dds/crane_wheel.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_clamp_a.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_a.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_c.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_d.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_e.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_f.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_g.dds");
    files.push_back("d:/_xxx/work/image/dds/crn_pan_i.dds");
    files.push_back("d:/_xxx/work/image/dds/cube.dds");
    files.push_back("d:/_xxx/work/image/dds/Cyan_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/day.dds");
    files.push_back("d:/_xxx/work/image/dds/Default.dds");
    files.push_back("d:/_xxx/work/image/dds/Default_bump_normal.dds");
    //files.push_back("d:/_xxx/work/image/dds/Default_reflection.dds");
    files.push_back("d:/_xxx/work/image/dds/DefaultBlack.dds");
    files.push_back("d:/_xxx/work/image/dds/DefaultNormalMap.dds");
    files.push_back("d:/_xxx/work/image/dds/DefaultRoughness.dds");
    files.push_back("d:/_xxx/work/image/dds/diffuse.DDS");
    files.push_back("d:/_xxx/work/image/dds/Doge.dds");
    files.push_back("d:/_xxx/work/image/dds/dsc_1621_small.dds");
    files.push_back("d:/_xxx/work/image/dds/dxutcontrols.dds");
    files.push_back("d:/_xxx/work/image/dds/ele_bot.dds");
    files.push_back("d:/_xxx/work/image/dds/ele_floor.dds");
    files.push_back("d:/_xxx/work/image/dds/ele_support.dds");
    files.push_back("d:/_xxx/work/image/dds/ele_track_a.dds");
    files.push_back("d:/_xxx/work/image/dds/Ennis.dds");
    files.push_back("d:/_xxx/work/image/dds/ExampleBillboard.DDS");
    files.push_back("d:/_xxx/work/image/dds/fan_blde.dds");
    files.push_back("d:/_xxx/work/image/dds/fan_housing_b.dds");
    files.push_back("d:/_xxx/work/image/dds/fan_hub.dds");
    files.push_back("d:/_xxx/work/image/dds/field_128_cube.dds");
    //files.push_back("d:/_xxx/work/image/dds/Flashlight.dds");
    files.push_back("d:/_xxx/work/image/dds/floor_wood_3.dds");
    files.push_back("d:/_xxx/work/image/dds/floor_wood_3Bump.dds");
    files.push_back("d:/_xxx/work/image/dds/floor_wood_4.dds");
    files.push_back("d:/_xxx/work/image/dds/floor_wood_4Bump.dds");
    files.push_back("d:/_xxx/work/image/dds/flower1024.dds");
    files.push_back("d:/_xxx/work/image/dds/Font.dds");
    files.push_back("d:/_xxx/work/image/dds/font_Arial_12.dds");
    files.push_back("d:/_xxx/work/image/dds/Future.dds");
    files.push_back("d:/_xxx/work/image/dds/gate_diffuse_dxt1.dds");
    files.push_back("d:/_xxx/work/image/dds/gate_diffuse_rgb.dds");
    files.push_back("d:/_xxx/work/image/dds/gate_glow_dxt1.dds");
    files.push_back("d:/_xxx/work/image/dds/gate_glow_rgb.dds");
    files.push_back("d:/_xxx/work/image/dds/Glacier.dds");
    files.push_back("d:/_xxx/work/image/dds/gr_trans_b.dds");
    files.push_back("d:/_xxx/work/image/dds/GraceCathedral.dds");
    files.push_back("d:/_xxx/work/image/dds/Gradient.dds");
    files.push_back("d:/_xxx/work/image/dds/grass.dds");
    files.push_back("d:/_xxx/work/image/dds/grass_rgba.dds");
    files.push_back("d:/_xxx/work/image/dds/gravel_a.dds");
    files.push_back("d:/_xxx/work/image/dds/gravel_c.dds");
    files.push_back("d:/_xxx/work/image/dds/grt_sm_a.dds");
    files.push_back("d:/_xxx/work/image/dds/grt_sm_b.dds");
    files.push_back("d:/_xxx/work/image/dds/HEAD03_color.dds");
    files.push_back("d:/_xxx/work/image/dds/hill_mound_b.dds");
    files.push_back("d:/_xxx/work/image/dds/hz_a.dds");
    files.push_back("d:/_xxx/work/image/dds/img_test.dds");
    files.push_back("d:/_xxx/work/image/dds/IrregularPoint.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-ati1n.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-ati2n.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-bgr8.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-dxt1.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-dxt5.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken1-rgb10a2.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-bc4.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-bc5.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-bc7.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-bgra8.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-dxt1.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken2-dxt5.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken3-bgr8.dds");
    files.push_back("d:/_xxx/work/image/dds/kueken4-dxt1.dds");
    files.push_back("d:/_xxx/work/image/dds/LEG03_color.dds");
    files.push_back("d:/_xxx/work/image/dds/lichen6.dds");
    files.push_back("d:/_xxx/work/image/dds/lichen6_normal.dds");
    files.push_back("d:/_xxx/work/image/dds/lichen6_rock.dds");
    files.push_back("d:/_xxx/work/image/dds/light2.dds");
    files.push_back("d:/_xxx/work/image/dds/light2Bump.dds");
    files.push_back("d:/_xxx/work/image/dds/lightmap.DDS");
    files.push_back("d:/_xxx/work/image/dds/lion.dds");
    files.push_back("d:/_xxx/work/image/dds/lion_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/LogoGL.dds");
    files.push_back("d:/_xxx/work/image/dds/LogoGLES.dds");
    files.push_back("d:/_xxx/work/image/dds/LogoNVIDIA.dds");
    files.push_back("d:/_xxx/work/image/dds/LogoVulkan.dds");
    files.push_back("d:/_xxx/work/image/dds/main.dds");
    files.push_back("d:/_xxx/work/image/dds/mask.dds");
    files.push_back("d:/_xxx/work/image/dds/mav_a_ring.dds");
    files.push_back("d:/_xxx/work/image/dds/mav_b_body.dds");
    files.push_back("d:/_xxx/work/image/dds/mav_b_lit.dds");
    files.push_back("d:/_xxx/work/image/dds/mountain_cube.dds");
    files.push_back("d:/_xxx/work/image/dds/normalmap.dds");
    files.push_back("d:/_xxx/work/image/dds/NV0.dds");
    files.push_back("d:/_xxx/work/image/dds/NV1.dds");
    files.push_back("d:/_xxx/work/image/dds/NV10.dds");
    files.push_back("d:/_xxx/work/image/dds/NV100.dds");
    files.push_back("d:/_xxx/work/image/dds/NV101.dds");
    files.push_back("d:/_xxx/work/image/dds/NV102.dds");
    files.push_back("d:/_xxx/work/image/dds/NV103.dds");
    files.push_back("d:/_xxx/work/image/dds/NV104.dds");
    files.push_back("d:/_xxx/work/image/dds/NV105.dds");
    files.push_back("d:/_xxx/work/image/dds/NV106.dds");
    files.push_back("d:/_xxx/work/image/dds/NV107.dds");
    files.push_back("d:/_xxx/work/image/dds/NV108.dds");
    files.push_back("d:/_xxx/work/image/dds/NV109.dds");
    files.push_back("d:/_xxx/work/image/dds/NV11.dds");
    files.push_back("d:/_xxx/work/image/dds/NV110.dds");
    files.push_back("d:/_xxx/work/image/dds/NV111.dds");
    files.push_back("d:/_xxx/work/image/dds/NV112.dds");
    files.push_back("d:/_xxx/work/image/dds/NV113.dds");
    files.push_back("d:/_xxx/work/image/dds/NV114.dds");
    files.push_back("d:/_xxx/work/image/dds/NV115.dds");
    files.push_back("d:/_xxx/work/image/dds/NV116.dds");
    files.push_back("d:/_xxx/work/image/dds/NV117.dds");
    files.push_back("d:/_xxx/work/image/dds/NV118.dds");
    files.push_back("d:/_xxx/work/image/dds/NV119.dds");
    files.push_back("d:/_xxx/work/image/dds/NV12.dds");
    files.push_back("d:/_xxx/work/image/dds/NV120.dds");
    files.push_back("d:/_xxx/work/image/dds/NV121.dds");
    files.push_back("d:/_xxx/work/image/dds/NV122.dds");
    files.push_back("d:/_xxx/work/image/dds/NV123.dds");
    files.push_back("d:/_xxx/work/image/dds/NV124.dds");
    files.push_back("d:/_xxx/work/image/dds/NV125.dds");
    files.push_back("d:/_xxx/work/image/dds/NV126.dds");
    files.push_back("d:/_xxx/work/image/dds/NV127.dds");
    files.push_back("d:/_xxx/work/image/dds/NV128.dds");
    files.push_back("d:/_xxx/work/image/dds/NV129.dds");
    files.push_back("d:/_xxx/work/image/dds/NV13.dds");
    files.push_back("d:/_xxx/work/image/dds/NV130.dds");
    files.push_back("d:/_xxx/work/image/dds/NV131.dds");
    files.push_back("d:/_xxx/work/image/dds/NV132.dds");
    files.push_back("d:/_xxx/work/image/dds/NV133.dds");
    files.push_back("d:/_xxx/work/image/dds/NV134.dds");
    files.push_back("d:/_xxx/work/image/dds/NV135.dds");
    files.push_back("d:/_xxx/work/image/dds/NV136.dds");
    files.push_back("d:/_xxx/work/image/dds/NV137.dds");
    files.push_back("d:/_xxx/work/image/dds/NV138.dds");
    files.push_back("d:/_xxx/work/image/dds/NV139.dds");
    files.push_back("d:/_xxx/work/image/dds/NV14.dds");
    files.push_back("d:/_xxx/work/image/dds/NV140.dds");
    files.push_back("d:/_xxx/work/image/dds/NV141.dds");
    files.push_back("d:/_xxx/work/image/dds/NV142.dds");
    files.push_back("d:/_xxx/work/image/dds/NV143.dds");
    files.push_back("d:/_xxx/work/image/dds/NV144.dds");
    files.push_back("d:/_xxx/work/image/dds/NV145.dds");
    files.push_back("d:/_xxx/work/image/dds/NV146.dds");
    files.push_back("d:/_xxx/work/image/dds/NV147.dds");
    files.push_back("d:/_xxx/work/image/dds/NV148.dds");
    files.push_back("d:/_xxx/work/image/dds/NV149.dds");
    files.push_back("d:/_xxx/work/image/dds/NV15.dds");
    files.push_back("d:/_xxx/work/image/dds/NV150.dds");
    files.push_back("d:/_xxx/work/image/dds/NV151.dds");
    files.push_back("d:/_xxx/work/image/dds/NV152.dds");
    files.push_back("d:/_xxx/work/image/dds/NV153.dds");
    files.push_back("d:/_xxx/work/image/dds/NV154.dds");
    files.push_back("d:/_xxx/work/image/dds/NV155.dds");
    files.push_back("d:/_xxx/work/image/dds/NV156.dds");
    files.push_back("d:/_xxx/work/image/dds/NV157.dds");
    files.push_back("d:/_xxx/work/image/dds/NV158.dds");
    files.push_back("d:/_xxx/work/image/dds/NV159.dds");
    files.push_back("d:/_xxx/work/image/dds/NV16.dds");
    files.push_back("d:/_xxx/work/image/dds/NV160.dds");
    files.push_back("d:/_xxx/work/image/dds/NV161.dds");
    files.push_back("d:/_xxx/work/image/dds/NV162.dds");
    files.push_back("d:/_xxx/work/image/dds/NV163.dds");
    files.push_back("d:/_xxx/work/image/dds/NV164.dds");
    files.push_back("d:/_xxx/work/image/dds/NV165.dds");
    files.push_back("d:/_xxx/work/image/dds/NV166.dds");
    files.push_back("d:/_xxx/work/image/dds/NV167.dds");
    files.push_back("d:/_xxx/work/image/dds/NV168.dds");
    files.push_back("d:/_xxx/work/image/dds/NV169.dds");
    files.push_back("d:/_xxx/work/image/dds/NV17.dds");
    files.push_back("d:/_xxx/work/image/dds/NV170.dds");
    files.push_back("d:/_xxx/work/image/dds/NV171.dds");
    files.push_back("d:/_xxx/work/image/dds/NV172.dds");
    files.push_back("d:/_xxx/work/image/dds/NV173.dds");
    files.push_back("d:/_xxx/work/image/dds/NV174.dds");
    files.push_back("d:/_xxx/work/image/dds/NV175.dds");
    files.push_back("d:/_xxx/work/image/dds/NV176.dds");
    files.push_back("d:/_xxx/work/image/dds/NV177.dds");
    files.push_back("d:/_xxx/work/image/dds/NV178.dds");
    files.push_back("d:/_xxx/work/image/dds/NV179.dds");
    files.push_back("d:/_xxx/work/image/dds/NV18.dds");
    files.push_back("d:/_xxx/work/image/dds/NV180.dds");
    files.push_back("d:/_xxx/work/image/dds/NV19.dds");
    files.push_back("d:/_xxx/work/image/dds/NV2.dds");
    files.push_back("d:/_xxx/work/image/dds/NV20.dds");
    files.push_back("d:/_xxx/work/image/dds/NV21.dds");
    files.push_back("d:/_xxx/work/image/dds/NV22.dds");
    files.push_back("d:/_xxx/work/image/dds/NV23.dds");
    files.push_back("d:/_xxx/work/image/dds/NV24.dds");
    files.push_back("d:/_xxx/work/image/dds/NV25.dds");
    files.push_back("d:/_xxx/work/image/dds/NV26.dds");
    files.push_back("d:/_xxx/work/image/dds/NV27.dds");
    files.push_back("d:/_xxx/work/image/dds/NV28.dds");
    files.push_back("d:/_xxx/work/image/dds/NV29.dds");
    files.push_back("d:/_xxx/work/image/dds/NV3.dds");
    files.push_back("d:/_xxx/work/image/dds/NV30.dds");
    files.push_back("d:/_xxx/work/image/dds/NV31.dds");
    files.push_back("d:/_xxx/work/image/dds/NV32.dds");
    files.push_back("d:/_xxx/work/image/dds/NV33.dds");
    files.push_back("d:/_xxx/work/image/dds/NV34.dds");
    files.push_back("d:/_xxx/work/image/dds/NV35.dds");
    files.push_back("d:/_xxx/work/image/dds/NV36.dds");
    files.push_back("d:/_xxx/work/image/dds/NV37.dds");
    files.push_back("d:/_xxx/work/image/dds/NV38.dds");
    files.push_back("d:/_xxx/work/image/dds/NV39.dds");
    files.push_back("d:/_xxx/work/image/dds/NV4.dds");
    files.push_back("d:/_xxx/work/image/dds/NV40.dds");
    files.push_back("d:/_xxx/work/image/dds/NV41.dds");
    files.push_back("d:/_xxx/work/image/dds/NV42.dds");
    files.push_back("d:/_xxx/work/image/dds/NV43.dds");
    files.push_back("d:/_xxx/work/image/dds/NV44.dds");
    files.push_back("d:/_xxx/work/image/dds/NV45.dds");
    files.push_back("d:/_xxx/work/image/dds/NV46.dds");
    files.push_back("d:/_xxx/work/image/dds/NV47.dds");
    files.push_back("d:/_xxx/work/image/dds/NV48.dds");
    files.push_back("d:/_xxx/work/image/dds/NV49.dds");
    files.push_back("d:/_xxx/work/image/dds/NV5.dds");
    files.push_back("d:/_xxx/work/image/dds/NV50.dds");
    files.push_back("d:/_xxx/work/image/dds/NV51.dds");
    files.push_back("d:/_xxx/work/image/dds/NV52.dds");
    files.push_back("d:/_xxx/work/image/dds/NV53.dds");
    files.push_back("d:/_xxx/work/image/dds/NV54.dds");
    files.push_back("d:/_xxx/work/image/dds/NV55.dds");
    files.push_back("d:/_xxx/work/image/dds/NV56.dds");
    files.push_back("d:/_xxx/work/image/dds/NV57.dds");
    files.push_back("d:/_xxx/work/image/dds/NV58.dds");
    files.push_back("d:/_xxx/work/image/dds/NV59.dds");
    files.push_back("d:/_xxx/work/image/dds/NV6.dds");
    files.push_back("d:/_xxx/work/image/dds/NV60.dds");
    files.push_back("d:/_xxx/work/image/dds/NV61.dds");
    files.push_back("d:/_xxx/work/image/dds/NV62.dds");
    files.push_back("d:/_xxx/work/image/dds/NV63.dds");
    files.push_back("d:/_xxx/work/image/dds/NV64.dds");
    files.push_back("d:/_xxx/work/image/dds/NV65.dds");
    files.push_back("d:/_xxx/work/image/dds/NV66.dds");
    files.push_back("d:/_xxx/work/image/dds/NV67.dds");
    files.push_back("d:/_xxx/work/image/dds/NV68.dds");
    files.push_back("d:/_xxx/work/image/dds/NV69.dds");
    files.push_back("d:/_xxx/work/image/dds/NV7.dds");
    files.push_back("d:/_xxx/work/image/dds/NV70.dds");
    files.push_back("d:/_xxx/work/image/dds/NV71.dds");
    files.push_back("d:/_xxx/work/image/dds/NV72.dds");
    files.push_back("d:/_xxx/work/image/dds/NV73.dds");
    files.push_back("d:/_xxx/work/image/dds/NV74.dds");
    files.push_back("d:/_xxx/work/image/dds/NV75.dds");
    files.push_back("d:/_xxx/work/image/dds/NV76.dds");
    files.push_back("d:/_xxx/work/image/dds/NV77.dds");
    files.push_back("d:/_xxx/work/image/dds/NV78.dds");
    files.push_back("d:/_xxx/work/image/dds/NV79.dds");
    files.push_back("d:/_xxx/work/image/dds/NV8.dds");
    files.push_back("d:/_xxx/work/image/dds/NV80.dds");
    files.push_back("d:/_xxx/work/image/dds/NV81.dds");
    files.push_back("d:/_xxx/work/image/dds/NV82.dds");
    files.push_back("d:/_xxx/work/image/dds/NV83.dds");
    files.push_back("d:/_xxx/work/image/dds/NV84.dds");
    files.push_back("d:/_xxx/work/image/dds/NV85.dds");
    files.push_back("d:/_xxx/work/image/dds/NV86.dds");
    files.push_back("d:/_xxx/work/image/dds/NV87.dds");
    files.push_back("d:/_xxx/work/image/dds/NV88.dds");
    files.push_back("d:/_xxx/work/image/dds/NV89.dds");
    files.push_back("d:/_xxx/work/image/dds/NV9.dds");
    files.push_back("d:/_xxx/work/image/dds/NV90.dds");
    files.push_back("d:/_xxx/work/image/dds/NV91.dds");
    files.push_back("d:/_xxx/work/image/dds/NV92.dds");
    files.push_back("d:/_xxx/work/image/dds/NV93.dds");
    files.push_back("d:/_xxx/work/image/dds/NV94.dds");
    files.push_back("d:/_xxx/work/image/dds/NV95.dds");
    files.push_back("d:/_xxx/work/image/dds/NV96.dds");
    files.push_back("d:/_xxx/work/image/dds/NV97.dds");
    files.push_back("d:/_xxx/work/image/dds/NV98.dds");
    files.push_back("d:/_xxx/work/image/dds/NV99.dds");
    files.push_back("d:/_xxx/work/image/dds/nvidia_logo.dds");
    files.push_back("d:/_xxx/work/image/dds/pad_big_b.dds");
    files.push_back("d:/_xxx/work/image/dds/pad_pan_a.dds");
    files.push_back("d:/_xxx/work/image/dds/palm.dds");
    files.push_back("d:/_xxx/work/image/dds/particle.dds");
    files.push_back("d:/_xxx/work/image/dds/Pink_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/pipe_a.dds");
    files.push_back("d:/_xxx/work/image/dds/pipe_b.dds");
    files.push_back("d:/_xxx/work/image/dds/pipe_d.dds");
    files.push_back("d:/_xxx/work/image/dds/pipe_e.dds");
    files.push_back("d:/_xxx/work/image/dds/Pisa.dds");
    files.push_back("d:/_xxx/work/image/dds/Planetarium.dds");
    //files.push_back("d:/_xxx/work/image/dds/PointsOfLight.dds");
    files.push_back("d:/_xxx/work/image/dds/rail.dds");
    files.push_back("d:/_xxx/work/image/dds/re_bar_a.dds");
    files.push_back("d:/_xxx/work/image/dds/re_bar_trans.dds");
    files.push_back("d:/_xxx/work/image/dds/Red_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/red_girder_a.dds");
    files.push_back("d:/_xxx/work/image/dds/ring_a.dds");
    files.push_back("d:/_xxx/work/image/dds/road_end.dds");
    files.push_back("d:/_xxx/work/image/dds/road_end_a.dds");
    files.push_back("d:/_xxx/work/image/dds/road_end_b.dds");
    files.push_back("d:/_xxx/work/image/dds/road_loop_a.dds");
    files.push_back("d:/_xxx/work/image/dds/road_st_a.dds");
    files.push_back("d:/_xxx/work/image/dds/rock.dds");
    files.push_back("d:/_xxx/work/image/dds/rock_normal.dds");
    files.push_back("d:/_xxx/work/image/dds/rock_rgba.dds");
    files.push_back("d:/_xxx/work/image/dds/rock2_rgba.dds");
    files.push_back("d:/_xxx/work/image/dds/rough645_small.dds");
    files.push_back("d:/_xxx/work/image/dds/sand.dds");
    files.push_back("d:/_xxx/work/image/dds/seamless_rock1_small.dds");
    files.push_back("d:/_xxx/work/image/dds/shellDiffuse.dds");
    files.push_back("d:/_xxx/work/image/dds/SHSpecularA.dds");
    files.push_back("d:/_xxx/work/image/dds/SHSpecularB.dds");
    files.push_back("d:/_xxx/work/image/dds/sky.dds");
    files.push_back("d:/_xxx/work/image/dds/sky_cube.dds");
    files.push_back("d:/_xxx/work/image/dds/sky128.dds");
    files.push_back("d:/_xxx/work/image/dds/sm_pan_a.dds");
    files.push_back("d:/_xxx/work/image/dds/snow_flat_rgba.dds");
    files.push_back("d:/_xxx/work/image/dds/snow_rgba.dds");
    files.push_back("d:/_xxx/work/image/dds/specular.DDS");
    files.push_back("d:/_xxx/work/image/dds/spnza_bricks_a_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/spnza_bricks_a_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_arch_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_arch_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_ceiling_a_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_ceiling_a_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_a_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_a_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_b_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_b_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_c_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_column_c_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_blue_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_blue_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_green_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_curtain_green_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_details_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_details_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_blue_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_blue_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_green_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_fabric_green_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_flagpole_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_flagpole_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_floor_a_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_floor_a_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_roof_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/sponza_roof_diff_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/sponza_thorn_diff.dds");
    files.push_back("d:/_xxx/work/image/dds/tank_side.dds");
    files.push_back("d:/_xxx/work/image/dds/tank_top.dds");
    files.push_back("d:/_xxx/work/image/dds/terrain_colormap.dds");
    files.push_back("d:/_xxx/work/image/dds/terrain_heightmap.dds");
    files.push_back("d:/_xxx/work/image/dds/terrain_tex.dds");
    files.push_back("d:/_xxx/work/image/dds/test_ground_b.dds");
    files.push_back("d:/_xxx/work/image/dds/tex1.dds");
    files.push_back("d:/_xxx/work/image/dds/tow_rib_ a.dds");
    files.push_back("d:/_xxx/work/image/dds/tow_rib_c.dds");
    files.push_back("d:/_xxx/work/image/dds/trench_b.dds");
    files.push_back("d:/_xxx/work/image/dds/trench_end.dds");
    files.push_back("d:/_xxx/work/image/dds/trench_surround.dds");
    files.push_back("d:/_xxx/work/image/dds/truss_a.dds");
    files.push_back("d:/_xxx/work/image/dds/truss_end.dds");
    files.push_back("d:/_xxx/work/image/dds/tw_tex_a.dds");
    files.push_back("d:/_xxx/work/image/dds/Tx_wood_brown_shelf_small.dds");
    files.push_back("d:/_xxx/work/image/dds/Tx_wood_brown_shelf_smallBump.dds");
    files.push_back("d:/_xxx/work/image/dds/Uffizi.dds");
    files.push_back("d:/_xxx/work/image/dds/uvmap.DDS");
    files.push_back("d:/_xxx/work/image/dds/uvtemplate.DDS");
    files.push_back("d:/_xxx/work/image/dds/vase_dif.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_dif_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/vase_hanging.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_hanging_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/vase_plant.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_plant_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/vase_round.dds");
    files.push_back("d:/_xxx/work/image/dds/vase_round_NRM.DDS");
    files.push_back("d:/_xxx/work/image/dds/vent_01_DM.dds");
    files.push_back("d:/_xxx/work/image/dds/vent_02_DM.dds");
    files.push_back("d:/_xxx/work/image/dds/Violet_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/walkway_a.dds");
    files.push_back("d:/_xxx/work/image/dds/wall_tex_a.dds");
    files.push_back("d:/_xxx/work/image/dds/wall_tex_b.dds");
    files.push_back("d:/_xxx/work/image/dds/wallpaper20.dds");
    files.push_back("d:/_xxx/work/image/dds/wallpaper20Bump.dds");
    files.push_back("d:/_xxx/work/image/dds/wheel_house.dds");
    files.push_back("d:/_xxx/work/image/dds/white_4x4.dds");
    files.push_back("d:/_xxx/work/image/dds/white_dummy.dds");
    files.push_back("d:/_xxx/work/image/dds/windmill_diffuse.dds");
    files.push_back("d:/_xxx/work/image/dds/windmill_diffuse1.dds");
    files.push_back("d:/_xxx/work/image/dds/windows_DM.dds");
    files.push_back("d:/_xxx/work/image/dds/wood4_rotate.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_02.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_03.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_04.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_05.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_06 .dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_07.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_08.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_09.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_10.dds");
    files.push_back("d:/_xxx/work/image/dds/Yellow_Fish_11.dds");
    files.push_back("d:/_xxx/work/image/dds/yellow_girder_a.dds");
*/
    return files;
}

std::vector<std::string> ddsAndktxFiles = init_ddsAndktxFiles();

// Test code only end

OSG::Real32 testValue = 0.1f;

//
// This number if models is always hold in memory allowing to switch
// back the model without model reloading.
//
OSG::Int32 numTrackedModels = 4;

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// A sky background
//
bool backgroundIsSRGB   = false;
OSG::UInt32 numSkyBgnds = 7;
OSG::UInt32 bgndIdx     = 6;
std::vector<std::string> skyFiles;

//
// A separate transformation for every object
//
OSG::TransformRefPtr geo1Trans, geo2Trans;

//
// Material groups
//
OSG::MaterialGroupRefPtr materialGroup1 = NULL;
OSG::MaterialGroupRefPtr materialGroup2 = NULL;

OSG::NodeRefPtr mat1Node = NULL;
OSG::NodeRefPtr mat2Node = NULL;

bool useModelMaterial = false;

//
// The scene
//
OSG::NodeRefPtr scene;

//
// Tonemapping
//
OSG::HDR2StageRefPtr hdr2Stage;
bool useHdrStage = true;
//
// The Screen Space Ambient Occlusion stage
//
OSG::SSAOStageRefPtr ssaoStage;
bool useSSAOStage = false;

//
// MaterialManager
//
OSG::DescMaterialManagerRefPtr          materialManager;
OSG::HashKeyToFieldContainerMapRefPtr   imageMap;

//
// Lights
//
OSG::NodeRefPtr lightRoot;

OSG::UInt32 nlights   = 6;
OSG:: Int32 currLight = -1;

std::vector<OSG::TransformRefPtr> lightBeacons;
std::vector<OSG::LightRefPtr>     lights;

OSG::MultiLightGroupRefPtr multiLightGroup;
const OSG::UInt32 lightBndPnt = 2;

bool useMultiLight = false;
bool useFlatShading = false;

//
// Shading Model
//
OSG::Int32 shadingModelIdx = OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL;
std::vector<OSG::UInt32> shadingModels;

//
// Example Index
//
OSG::Int32 numExamples  = 18;
OSG::Int32 exampleIndex = 3; //numExamples-1;

//
// Some examples has tightly bound materials
//
enum ExampleType
{
    normal_example = 0,
    cyborg_example
};

ExampleType exampleType = normal_example;

void setupMaterial0 ();
void setupMaterial1 ();
void setupMaterial2 ();
void setupMaterial3 ();
void setupMaterial4 ();
void setupMaterial5 ();
void setupMaterial6 ();
void setupMaterial7 ();
void setupMaterial8 ();
void setupMaterial9 ();
void setupMaterial10();
void setupMaterial11();
void setupMaterial12();
void setupMaterial13();
void setupMaterial14();
void setupMaterial15();
void setupMaterial16();
void setupMaterial17();
void setupMaterial18();
void setupMaterial19();
void setupMaterial20();
void setupMaterial21();

void setupMaterialCyborg();

void setupMaterial()
{
    switch (exampleType)
    {
        case normal_example:
            switch (exampleIndex)
            {
                case  0: setupMaterial0 (); break;
                case  1: setupMaterial1 (); break;
                case  2: setupMaterial2 (); break;
                case  3: setupMaterial3 (); break;
                case  4: setupMaterial4 (); break;
                case  5: setupMaterial5 (); break;
                case  6: setupMaterial6 (); break;
                case  7: setupMaterial7 (); break;
                case  8: setupMaterial8 (); break;
                case  9: setupMaterial9 (); break;
                case 10: setupMaterial10(); break;
                case 11: setupMaterial11(); break;
                case 12: setupMaterial12(); break;
                case 13: setupMaterial13(); break;
                case 14: setupMaterial14(); break;
                case 15: setupMaterial15(); break;
                case 16: setupMaterial16(); break;
                case 17: setupMaterial17(); break;
                case 18: setupMaterial18(); break;
                case 19: setupMaterial19(); break;
                case 20: setupMaterial20(); break;
                case 21: setupMaterial21(); break;
            }
            break;
        case cyborg_example:
            setupMaterialCyborg();
            break;
    }
}

//
// Geometry Index
//
OSG::Int32 numGeoTypes  = 18;
OSG::Int32 geoTypeIndex = 0;

typedef std::pair<OSG::NodeRefPtr, OSG::NodeRefPtr> NodePair;
typedef std::vector<NodePair> NodePairStore;

NodePairStore nodePairStore;

void setupScene0(OSG::Int32 storeIdx);
void setupScene1(OSG::Int32 storeIdx);
void setupScene2(OSG::Int32 storeIdx);
void setupScene3(OSG::Int32 storeIdx);
void setupScene4(OSG::Int32 storeIdx);
void setupScene5(OSG::Int32 storeIdx);

void setupSceneIdx(OSG::Int32 storeIdx, const OSG::Char8* name, OSG::Int32 idx);

void setupScene()
{
    ExampleType lastExampleType = exampleType;
    exampleType = normal_example;

    switch (geoTypeIndex)
    {
        case  0: setupScene0 (geoTypeIndex); break;
        case  1: setupScene1 (geoTypeIndex); break;
        case  2: setupScene2 (geoTypeIndex); break;
        case  3: setupScene3 (geoTypeIndex); break;
        case  4: setupScene4 (geoTypeIndex); break;
        case  5: setupScene5 (geoTypeIndex); break;

        //
        // generic models...
        //
        default:
            setupSceneIdx(geoTypeIndex, "data/machine", geoTypeIndex-6);
    }

    if (lastExampleType != normal_example && exampleType == normal_example)
    {
        setupMaterial();
    }
}

void clear_console();

void print_usage()
{
    clear_console();
    std::cout << "Usage:" << std::endl
              << "======" << std::endl
              << "  " << "General:" << std::endl
              << "  " << "--------" << std::endl
              << "    " << "ESC" << "\t" << "Exit example" << std::endl
              << "    " << "h"   << "\t" << "Print this help" << std::endl
              << "    " << "A"   << "\t" << "Toggle use of the SSAO stage" << std::endl
              << "    " << "H"   << "\t" << "Toggle use of the HDR stage" << std::endl
              << "    " << "S"   << "\t" << "Toggle statistic output" << std::endl
              << "    " << "b"   << "\t" << "Forward loop through backgrounds" << std::endl
              << "    " << "B"   << "\t" << "Backward loop through backgrounds" << std::endl
              << "    " << "V"   << "\t" << "Toggle color space of background: Linear/sRGB" << std::endl
              << "  " << "Animation:" << std::endl
              << "  " << "----------" << std::endl
              << "    " << "l"   << "\t" << "Toggle light animation" << std::endl
              << "    " << "SPC" << "\t" << "Toggle object animation" << std::endl
              << "  " << "Lights:" << std::endl
              << "  " << "-------" << std::endl
              << "    " << "L"   << "\t" << "Toggle use of multi vs classic light" << std::endl
              << "    " << "a"   << "\t" << "Activate all lights" << std::endl
              << "    " << "d"   << "\t" << "Deactivate all but the directional lights" << std::endl
              << "    " << "p"   << "\t" << "Deactivate all but the point lights" << std::endl
              << "    " << "s"   << "\t" << "Deactivate all but the spot lights" << std::endl
              << "    " << "1"   << "\t" << "Deactivate all lights and then loop through the point lights" << std::endl
              << "    " << "2"   << "\t" << "Deactivate all lights and then loop through the diretional lights" << std::endl
              << "    " << "3"   << "\t" << "Deactivate all lights and then loop through the spot lights" << std::endl
              << "  " << "Example:" << std::endl
              << "  " << "--------" << std::endl
              << "    " << "e"   << "\t" << "Forward loop through supported examples" << std::endl
              << "    " << "E"   << "\t" << "Backward loop through supported examples" << std::endl
              << "    " << "g"   << "\t" << "Forward loop through supported scene geometries" << std::endl
              << "    " << "G"   << "\t" << "Backward loop through supported scene geometries" << std::endl
              << "    " << "m"   << "\t" << "Forward loop through supported shading models" << std::endl
              << "    " << "M"   << "\t" << "Backward loop through supported shading models" << std::endl
              << "    " << "N"   << "\t" << "Toggle use of models own material" << std::endl
              << "  " << "Remark:" << std::endl
              << "  " << "-------" << std::endl
              << "    " << "The textures are expected to be in the 'Data' folder relative to the current working directory."  << std::endl
              << "    " << "This can be setup in the 'Debugging' pane of the project settings in the MS DevStudio." << std::endl
              << std::endl
              ;
}

void print_shadingModel(OSG::UInt32 shadingModel)
{
    std::cout << "Shading Model: ";
    switch (shadingModel)
    {
        case OSG::MaterialDesc::NO_SHADING_MODEL:               std::cout << "NO_SHADING_MODEL";                break;
        case OSG::MaterialDesc::GOURAUD_SHADING_MODEL:          std::cout << "GOURAUD_SHADING_MODEL";           break;
        case OSG::MaterialDesc::PHONG_SHADING_MODEL:            std::cout << "PHONG_SHADING_MODEL";             break;
        case OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL:      std::cout << "BLINN_PHONG_SHADING_MODEL";       break;
        case OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL:    std::cout << "COOK_TORRANCE_SHADING_MODEL";     break;
        case OSG::MaterialDesc::OREN_NAYAR_SHADING_MODEL:       std::cout << "OREN_NAYAR_SHADING_MODEL";        break;
        case OSG::MaterialDesc::TOON_SHADING_MODEL:             std::cout << "TOON_SHADING_MODEL";              break;
        case OSG::MaterialDesc::GOOCH_SHADING_MODEL:            std::cout << "GOOCH_SHADING_MODEL";             break;
    }
    std::cout << (useFlatShading ? " with flat shading" : "") << std::endl;
}

void print_example()
{
    std::cout << "Example ";
    switch (exampleIndex)
    {
        case 0: std::cout << " 0: Simple non textured material" << std::endl; break;
        case 1: std::cout << " 1: Simple textured material:" << std::endl;
                std::cout << "    Object 1: wood.png,   ALBEDO_TEXTURE,  REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 1: wood.png,   AMBIENT_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 2: marble.jpg, ALBEDO_TEXTURE,  MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                break;
        case 2: std::cout << " 2: Simple textured material:" << std::endl;
                std::cout << "    Object 1: lenna_color.gif, ALBEDO_TEXTURE, REPLACE_OPERATION,  GL_REPEAT,          IGNORE_ALPHA_FLAG"      << std::endl;
                std::cout << "    Object 2: penguin.png,     ALBEDO_TEXTURE, DECAL_OPERATION,    GL_MIRRORED_REPEAT, texture transformation" << std::endl;
                break;
        case 3: std::cout << " 3: Multi textured material:" << std::endl;
                std::cout << "    Object 1: bricks2.jpg,     ALBEDO_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                std::cout << "              penguin.png,     ALBEDO_TEXTURE, DECAL_OPERATION,    GL_MIRRORED_REPEAT, USE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "    Object 2: metal.png,       ALBEDO_TEXTURE, MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                std::cout << "              worldground.jpg, ALBEDO_TEXTURE, MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, INVERT_FLAG"         << std::endl;
                break;
        case 4: std::cout << " 4: PBR material 1:" << std::endl;
                std::cout << "    Object 1: pbr/gold/albedo.png,           ALBEDO_TEXTURE,    REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/gold/metallic.png,         METAL_TEXTURE,     REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/gold/roughness.png,        ROUGH_TEXTURE,     REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "    Object 2: pbr/rusted_iron/albedo.png,    ALBEDO_TEXTURE,    REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/rusted_iron/metallic.png,  METAL_TEXTURE,     REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/rusted_iron/roughness.png, ROUGH_TEXTURE,     REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                break;
        case 5: std::cout << " 5: Textured material:" << std::endl;
                std::cout << "    Object 1: container2.png,          ALBEDO_TEXTURE,   REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 2: container2.png,          ALBEDO_TEXTURE,   REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              container2_specular.png, SPECULAR_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                break;
        case 6: std::cout << " 6: Specular and Shininess:" << std::endl;
                std::cout << "    Object 1: container2.png,          ALBEDO_TEXTURE,    REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 2: container2.png,          ALBEDO_TEXTURE,    REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              container2_specular.png, SPECULAR_TEXTURE,  REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              container2_specular.png, SHININESS_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
        case 7: std::cout << " 7: Textured material:" << std::endl;
                std::cout << "    Object 1: container2.png,          ALBEDO_TEXTURE,   REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 2: container2.png,          ALBEDO_TEXTURE,   REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              container2_specular.png, SPECULAR_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              matrix.jpg,              EMISSIVE_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                break;
        case 8: std::cout << " 8: Normal mapping:" << std::endl;
                std::cout << "    Object 1: brickwall.jpg,        ALBEDO_TEXTURE,  REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                 << std::endl;
                std::cout << "    Object 2: brickwall.jpg,        ALBEDO_TEXTURE,  REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                 << std::endl;
                std::cout << "              brickwall_normal.jpg, NORMALS_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, MirrorVertical" << std::endl;
                break;
        case 9: std::cout << " 9: Normal mapping:" << std::endl;
                std::cout << "    Object 1: maps/SpecularMapWave.png, ALBEDO_TEXTURE,   MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "              maps/SpecularMapWave.png, SPECULAR_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "    Object 1: maps/SpecularMapWave.png, ALBEDO_TEXTURE,   MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "              maps/SpecularMapWave.png, SPECULAR_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "              maps/NormalMapWave.png,   NORMALS_TEXTURE,  REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, texture transformation, MirrorVertical" << std::endl;
                break;
        case 10:std::cout << "10: Displacement mapping:" << std::endl;
                std::cout << "    Object 1: bricks2.jpg,        ALBEDO_TEXTURE,       REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              bricks2_normal.jpg, NORMALS_TEXTURE,      REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "    Object 2: bricks2.jpg,        ALBEDO_TEXTURE,       REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              bricks2_normal.jpg, NORMALS_TEXTURE,      REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                std::cout << "              bricks2_disp.jpg,   DISPLACEMENT_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG" << std::endl;
                break;
        case 11:std::cout << "11: Multi textured material with opacity:" << std::endl;
                std::cout << "    Object 1: bricks2.jpg,     ALBEDO_TEXTURE,  REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                std::cout << "              penguin.png,     ALBEDO_TEXTURE,  DECAL_OPERATION,    GL_MIRRORED_REPEAT, USE_ALPHA_FLAG, texture transformation" << std::endl;
                std::cout << "              ornament.png,    OPACITY_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                std::cout << "    Object 2: metal.png,       ALBEDO_TEXTURE,  MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                std::cout << "              worldground.jpg, ALBEDO_TEXTURE,  MULTIPLY_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, INVERT_FLAG"         << std::endl;
                std::cout << "              circles.jpg,     OPACITY_TEXTURE, REPLACE_OPERATION,  GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"                      << std::endl;
                break;
        case 12:std::cout << "12: PBR material 'wall/plastic' with normal and ambient occlusion map:" << std::endl;
                std::cout << "    Object 1: pbr/wall/albedo.png,       ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/wall/metallic.png,     METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/wall/roughness.png,    ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/wall/normal.png,       NORMALS_TEXTURE,           REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/wall/ao.png,           AMBIENT_OCCLUSION_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "    Object 2: pbr/plastic/albedo.png,    ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/plastic/metallic.png,  METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/plastic/roughness.png, ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/plastic/normal.png,    NORMALS_TEXTURE,           REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/plastic/ao.png,        AMBIENT_OCCLUSION_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                break;
        case 13:std::cout << "13: PBR material 'wall/grass' with normal and ambient occlusion map:" << std::endl;
                std::cout << "    Object 1: pbr/wall/albedo.png,     ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/wall/metallic.png,   METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/wall/roughness.png,  ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/wall/normal.png,     NORMALS_TEXTURE,           REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/wall/ao.png,         AMBIENT_OCCLUSION_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "    Object 2: pbr/grass/albedo.png,    ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/grass/metallic.png,  METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/grass/roughness.png, ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/grass/normal.png,    NORMALS_TEXTURE,           REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/grass/ao.png,        AMBIENT_OCCLUSION_TEXTURE, REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                break;
        case 14:std::cout << "14: PBR material 'gold/rusted_iron' with shared six reflection maps:" << std::endl;
                std::cout << "    Object 1: pbr/gold/albedo.png,           ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/gold/metallic.png,         METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/gold/roughness.png,        ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              hdr/newport_loft_vstrip.hdr,   REFLECTION_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                std::cout << "    Object 2: pbr/rusted_iron/albedo.png,    ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/rusted_iron/metallic.png,  METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/rusted_iron/roughness.png, ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              skyFiles[POS_X, ...],          REFLECTION_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                break;
        case 15:std::cout << "15: PBR material 'gold/rusted_iron' with one cross/strip cube reflection map:" << std::endl;
                std::cout << "    Object 1: pbr/gold/albedo.png,           ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/gold/metallic.png,         METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/gold/roughness.png,        ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              skyFiles[POS_X, ...],          REFLECTION_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                std::cout << "    Object 2: pbr/rusted_iron/albedo.png,    ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/rusted_iron/metallic.png,  METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/rusted_iron/roughness.png, ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              skyFiles[POS_X, ...],          REFLECTION_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                break;
        case 16:std::cout << "16: PBR material 'gold/rusted_iron' with hdr/tga lat long reflection maps:" << std::endl;
                std::cout << "    Object 1: pbr/gold/albedo.png,           ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/gold/metallic.png,         METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/gold/roughness.png,        ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              hdr/newport_loft_latlong.hdr,  REFLECTION_TEXTURE,        EQUIRECTANGULAR_MAP, GL_CLAMP_TO_EDGE"                           << std::endl;
                std::cout << "    Object 2: pbr/rusted_iron/albedo.png,    ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/rusted_iron/metallic.png,  METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/rusted_iron/roughness.png, ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                //std::cout << "              hdr/newport_loft_latlong.tga,  REFLECTION_TEXTURE,        EQUIRECTANGULAR_MAP, GL_CLAMP_TO_EDGE"                           << std::endl;
                break;
        case 17:std::cout << "17: PBR material 'gold/rusted_iron' with irradiance and pre-filter map:" << std::endl;
                std::cout << "    Object 1: pbr/gold/albedo.png,                  ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/gold/metallic.png,                METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/gold/roughness.png,               ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              hdr/irradiance.hdr,                   IRRADIANCE_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE, GL_LINEAR"                           << std::endl;
                std::cout << "              hdr/newport_loft_radiance_hcross.hdr, PRE_FILTER_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                std::cout << "    Object 2: pbr/rusted_iron/albedo.png,           ALBEDO_TEXTURE,            REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG"        << std::endl;
                std::cout << "              pbr/rusted_iron/metallic.png,         METAL_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              pbr/rusted_iron/roughness.png,        ROUGH_TEXTURE,             REPLACE_OPERATION, GL_MIRRORED_REPEAT, IGNORE_ALPHA_FLAG, GL_R8" << std::endl;
                std::cout << "              hdr/irradiance.hdr,                   IRRADIANCE_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE, GL_LINEAR"                           << std::endl;
                //std::cout << "              hdr/newport_loft_radiance_hcross.hdr, PRE_FILTER_TEXTURE,        CUBE_MAP, GL_CLAMP_TO_EDGE"                                      << std::endl;
                break;
        case 18:std::cout << "18: not implemented" << std::endl;
                break;
        case 19:std::cout << "19: not implemented" << std::endl;
                break;
        case 20:std::cout << "20: not implemented" << std::endl;
                break;
        case 21:std::cout << "21: not implemented" << std::endl;
                break;
    }
    std::cout << "    Color Space setting isSRGB = " << (backgroundIsSRGB ? "true" : "false") << std::endl;
    std::cout << std::endl;
}

void initShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
//        shader->addUniformVariable("testValue", testValue);
    }
}

void updateShader(OSG::ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_FRAGMENT_SHADER)
    {
//        shader->updateUniformVariable("testValue", testValue);
    }
}

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

// create the motion matrix for a light source at time t
void makeMatrix(OSG::Real32 t, OSG::Matrix &result)
{
    OSG::Matrix m;
    
    result.setTransform(OSG::Quaternion(OSG::Vec3f(0,0,1), -OSG::Pi / 2));    
    
    m.setTransform(OSG::Vec3f(1, 0, 0));
    result.multLeft(m);
    
    m.setTransform(OSG::Quaternion(OSG::Vec3f(0,1,0), t / 1000.f));    
    result.multLeft(m);

    m.setTransform(OSG::Vec3f(2, 0, 0));
    result.multLeft(m);
    
    m.setTransform(OSG::Quaternion(OSG::Vec3f(0,0,1), t / 3000.f));
    result.multLeft(m); 
}

void createLights(OSG::Node* root, OSG::Node* scene)
{
    std::cout << "Using " << (useMultiLight ? "multi" : "classic") << " lights" << std::endl;

    if (useMultiLight)
    {
        root->clearChildren();

        lightBeacons.clear();
        lights      .clear();

        lightBeacons.resize(nlights);

        multiLightGroup = OSG::MultiLightGroup::create();

        multiLightGroup->setLightBindingPnt(lightBndPnt);

        multiLightGroup->setUsage(GL_DYNAMIC_DRAW);
        multiLightGroup->setLayoutType(OSG::MultiLight::OPENGL_LAYOUT);

        materialManager->setMultiLightGroup(multiLightGroup);
        materialManager->setLightBindingPnt(lightBndPnt);

        for(OSG::UInt16 i = 0; i < nlights; ++i)
        {
            // create the light source
            OSG::NodeRefPtr geo_node;

            OSG::UInt32 idx;

            switch ((i % 3) + 0)
            {
                case 0:
                {
                    idx = multiLightGroup->addLight(OSG::MultiLight::POINT_LIGHT);

                    multiLightGroup->setPosition   (idx, OSG::Pnt3f(0, 0, 0));
                    multiLightGroup->setAttenuation(idx, OSG::Vec3f(1, 0, 3));

                    // a little sphere to show where the light is
                    geo_node = OSG::makeLatLongSphere(8, 8, 0.1f);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);
                }
                break;

                case 1:
                {
                    idx = multiLightGroup->addLight(OSG::MultiLight::DIRECTIONAL_LIGHT);

                    // (*) Old OpenGL stores the light direction in the 4D position parameter
                    //     with w=0. A value of (1,0,0) represents a light at infinity in the
                    //     positive x-direction. This light shines into the (-1,0,0) direction.
                    //     In our multi light we provide the light direction directly, i.e.
                    //     (-1,0,0) in the example.
                    multiLightGroup->setDirection(idx, OSG::Vec3f(0, 0, -1));

                    // a little cylinder to show where the light is
                    geo_node = OSG::makeCylinder(.1f, .03f, 8, true, true, true);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);
                }
                break;

                case 2:
                {
                    idx = multiLightGroup->addLight(OSG::MultiLight::SPOT_LIGHT);

                    multiLightGroup->setPosition      (idx, OSG::Pnt3f(0, 0, 0));
                    multiLightGroup->setDirection     (idx, OSG::Vec3f(0,-1, 0));
                    multiLightGroup->setAttenuation   (idx, OSG::Vec3f(1, 0, 3));

                    multiLightGroup->setSpotlightAngle   (idx, 45.f);
                    multiLightGroup->setSpotlightExponent(idx, 2.f);

                    // a little cone to show where the light is
                    geo_node = OSG::makeCone(.2f, .2f, 8, true, true);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);
                }
                break;
            }

            // create the beacon and attach it to the scene
            OSG::NodeRefPtr         beacon      = OSG::Node::create();
            OSG::TransformRefPtr    beacon_core = OSG::Transform::create();

            lightBeacons[i] = beacon_core;

            beacon->setCore(beacon_core);
            beacon->addChild(geo_node);

            root->addChild(beacon);

            OSG::Vec3f white(1,1,1);

            multiLightGroup->setAmbient (idx, white);
            multiLightGroup->setDiffuse (idx, white);
            multiLightGroup->setSpecular(idx, white);
            multiLightGroup->setEnabled (idx, true);
            multiLightGroup->setBeacon  (idx, beacon);
        }

        root->setCore(multiLightGroup);
        root->addChild(scene);
    }
    else
    {
        root->clearChildren();

        materialManager->setMultiLightGroup(NULL);

        lightRoot->setCore(OSG::Group::create());

        // helper node to keep the lights on top of each other
        OSG::NodeRefPtr lastnode = scene;

        // create the light sources
        if(nlights > 8)
        {
            FWARNING(("Currently only 8 classic lights are supported\n"));
            nlights = 8;
        }

        lightBeacons.clear();
        lights      .clear();

        lightBeacons.resize(nlights);
        lights      .resize(nlights);

        for(OSG::UInt16 i = 0; i < nlights; ++i)
        {
            // create the light source
            OSG::NodeRefPtr     light = OSG::Node::create();
            OSG::LightRefPtr    light_core;
            OSG::NodeRefPtr     geo_node;

            switch ((i % 3) + 0)
            {
                case 0:
                {
                    OSG::PointLightRefPtr l = OSG::PointLight::create();

                    l->setPosition             (0, 0, 0);
                    l->setConstantAttenuation  (1);
                    l->setLinearAttenuation    (0);
                    l->setQuadraticAttenuation (3);

                    // a little sphere to show where the light is
                    geo_node = OSG::makeLatLongSphere(8, 8, 0.1f);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);

                    light_core = l;
                }
                break;

                case 1:
                {
                    OSG::DirectionalLightRefPtr l = OSG::DirectionalLight::create();

                    l->setDirection(0, 0, 1);

                    // a little cylinder to show where the light is
                    geo_node = OSG::makeCylinder(.1f, .03f, 8, true, true, true);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);

                    light_core = l;
                }
                break;

                case 2:
                {
                    OSG::SpotLightRefPtr l = OSG::SpotLight::create();

                    l->setPosition             (OSG::Pnt3f(0,  0, 0));
                    l->setDirection            (OSG::Vec3f(0, -1, 0));
                    l->setSpotExponent         (2);
                    l->setSpotCutOff           (OSG::osgDegree2Rad(45));
                    l->setConstantAttenuation  (1);
                    l->setLinearAttenuation    (0);
                    l->setQuadraticAttenuation (3);

                    // a little cone to show where the light is
                    geo_node = OSG::makeCone(.2f, .2f, 8, true, true);

                    OSG::GeometryRefPtr       geo = dynamic_cast<OSG::Geometry *>(geo_node->getCore());
                    OSG::SimpleMaterialRefPtr sm  = OSG::SimpleMaterial::create();

                    sm->setLit(false);
                    sm->setDiffuse(OSG::Color3f(0.f,0.f,0.8f));

                    geo->setMaterial(sm);

                    light_core = l;
                }
                break;
            }

            // create the beacon and attach it to the scene
            OSG::NodeRefPtr         beacon      = OSG::Node::create();
            OSG::TransformRefPtr    beacon_core = OSG::Transform::create();

            lightBeacons[i] = beacon_core;

            beacon->setCore(beacon_core);
            beacon->addChild(geo_node);

            root->addChild(beacon);

            OSG::Color4f white(1,1,1,1);

            light_core->setAmbient (white);
            light_core->setDiffuse (white);
            light_core->setSpecular(white);
            light_core->setBeacon  (beacon);

            light->setCore(light_core);
            light->addChild(lastnode);

            lights[i] = light_core;
            lastnode = light;
        }

        root->addChild(lastnode);
    }
}

void setupMaterial0()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the material description
    matDesc1->setShadingModel    (shadingModel);
    matDesc1->setFlatShadingMode (useFlatShading);
    matDesc1->setEmissive    (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo      (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular    (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess   (0.2f * 128.f);
    matDesc1->setOpacity     (1.0f);
    matDesc1->setSRGBColorMode (true);
    matDesc1->setRoughness   (0.5f);
    matDesc1->setMetalness   (0.8f);

    matDesc2->setShadingModel(shadingModel);
    matDesc2->setFlatShadingMode (useFlatShading);
    matDesc2->setEmissive    (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo      (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular    (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess   (0.65f * 128.f);
    matDesc2->setOpacity     (1.0f);
    matDesc2->setSRGBColorMode (true);
    matDesc2->setRoughness   (0.5f);
    matDesc2->setMetalness   (0.8f);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial1()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc2  = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    //texDesc11->setFilename(ddsAndktxFiles[0].c_str());//"Data/pbr/mytest-brdf-lut.dds");//"Data/wood.png");
    texDesc11->setFilename("Data/wood.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc2->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc2->setIsSRGBTexture(true);
    texDesc2->setFilename("Data/marble.jpg");
    texDesc2->setUVChannel(0);
    texDesc2->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc2->setBlendFactor(100.f);
    texDesc2->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc2->setWrapS(GL_MIRRORED_REPEAT);
    texDesc2->setWrapT(GL_MIRRORED_REPEAT);
    texDesc2->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc2->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc2);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::MaterialManager::KeyType key1 = m1.first;
    OSG::MaterialManager::KeyType key2 = m2.first;

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    // Test Begin
    //OSG::MaterialManager::ManagedMaterialT m3 = materialManager->updateMaterial(m1.first);
    //OSG::ChunkMaterial* descMaterial3 = m3.second;

    //OSG::DescMaterial* descMaterialTest1 = dynamic_cast<OSG::DescMaterial*>(descMaterial1);

    //OSG::NodeRefPtr testNode = OSG::Node::create();
    //testNode->setCore(OSG::Group::create());

    //OSG::NodeRefPtr testNode1 = OSG::Node::create();
    //OSG::NodeRefPtr testNode2 = OSG::Node::create();

    //testNode->addChild(testNode1);
    //testNode->addChild(testNode2);

    //OSG::MaterialGroupRefPtr matGrp1 = OSG::MaterialGroup::create();
    //OSG::MaterialGroupRefPtr matGrp2 = OSG::MaterialGroup::create();

    //testNode1->setCore(matGrp1);
    //testNode2->setCore(matGrp2);

    //matGrp1->setMaterial(descMaterialTest1);
    //matGrp2->setMaterial(descMaterialTest1);

    //std::string h1 = descMaterialTest1->getMaterialDesc()->getHashValue();

    //bool result = OSG::SceneFileHandler::the()->write(testNode, "d:/DescMatTest1.osb");
    //if (result)
    //{
    //    materialManager->clearMaterials();

    //    OSG::NodeRefPtr loadNode = OSG::SceneFileHandler::the()->read("d:/DescMatTest1.osb");
    //    if (loadNode)
    //    {
    //        materialManager->clearMaterials();

    //        OSG::MaterialGroup* matGrpTest1 = dynamic_cast<OSG::MaterialGroup*>(loadNode->getChild(0)->getCore());
    //        OSG::MaterialGroup* matGrpTest2 = dynamic_cast<OSG::MaterialGroup*>(loadNode->getChild(1)->getCore());

    //        if (matGrpTest1 && matGrpTest2)
    //        {
    //            OSG::DescMaterial* descMaterialTest21 = dynamic_cast<OSG::DescMaterial*>(matGrpTest1->getMaterial());
    //            OSG::DescMaterial* descMaterialTest22 = dynamic_cast<OSG::DescMaterial*>(matGrpTest2->getMaterial());

    //            if (descMaterialTest21 && descMaterialTest22)
    //            {
    //                std::string h21 = descMaterialTest21->getMaterialDesc()->getHashValue();
    //                std::string h22 = descMaterialTest22->getMaterialDesc()->getHashValue();

    //                bool r21 = materialManager->addMaterial(h21, descMaterialTest21);

    //                materialManager->removeMaterial(h21);

    //                bool r22 = materialManager->addMaterial(h22, descMaterialTest22);

    //                OSG::MaterialManager::ManagedMaterialT m31 = materialManager->updateMaterial(h21);
    //                OSG::MaterialManager::ManagedMaterialT m32 = materialManager->updateMaterial(h22);

    //                int isdf  = 345;
    //            }
    //        }
    //    }
    //}
    // Test End

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial2()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDesc1->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc1->setIsSRGBTexture(true);
    texDesc1->setFilename("Data/lenna_color.gif");
    texDesc1->setUVChannel(0);
    texDesc1->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc1->setBlendFactor(1.f);
    texDesc1->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc1->setWrapS(GL_REPEAT);
    texDesc1->setWrapT(GL_REPEAT);
    texDesc1->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc1->setImageMap(imageMap);

    texDesc2->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc2->setIsSRGBTexture(true);
    texDesc2->setFilename("Data/penguin.png");
    texDesc2->setUVChannel(0);
    texDesc2->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc2->setBlendFactor(1.f);
    texDesc2->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc2->setWrapS(GL_MIRRORED_REPEAT);
    texDesc2->setWrapT(GL_MIRRORED_REPEAT);
    texDesc2->setHasUVTransform(true);
    texDesc2->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc2->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc2->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc1);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc2);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}
     
void setupMaterial3()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description for the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/bricks2.jpg");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc12->setIsSRGBTexture(true);
    texDesc12->setFilename("Data/penguin.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::USE_ALPHA_FLAG);
    texDesc12->setHasUVTransform(true);
    texDesc12->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc12->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc12->setImageMap(imageMap);

    // Setup the texture description for the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/metal.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(100.f);
    texDesc21->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc22->setIsSRGBTexture(true);
    texDesc22->setFilename("Data/worldground.jpg");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG|OSG::TextureDesc::INVERT_FLAG);
    texDesc22->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial4()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial5()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial6()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse   = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescShininess = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(imageMap);

    texDescShininess->setTextureType(OSG::TextureDesc::SHININESS_TEXTURE);
    texDescShininess->setIsSRGBTexture(true);
    texDescShininess->setFilename("Data/container2_specular.png");
    texDescShininess->setUVChannel(0);
    texDescShininess->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescShininess->setBlendFactor(50.f);
    texDescShininess->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDescShininess->setWrapS(GL_MIRRORED_REPEAT);
    texDescShininess->setWrapT(GL_MIRRORED_REPEAT);
    texDescShininess->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescShininess->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescSpecular);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);
    matDesc2->addTexture        (texDescShininess);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial7()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescEmissive = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/container2.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/container2_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(imageMap);

    texDescEmissive->setTextureType(OSG::TextureDesc::EMISSIVE_TEXTURE);
    texDescEmissive->setIsSRGBTexture(true);
    texDescEmissive->setFilename("Data/matrix.jpg");
    texDescEmissive->setUVChannel(0);
    texDescEmissive->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescEmissive->setBlendFactor(1.f);
    texDescEmissive->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescEmissive->setWrapS(GL_MIRRORED_REPEAT);
    texDescEmissive->setWrapT(GL_MIRRORED_REPEAT);
    texDescEmissive->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescEmissive->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);
    matDesc2->addTexture        (texDescEmissive);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial8()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/brickwall.jpg");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/brickwall_normal.jpg");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0.2f,0.2f,0.2f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0.2f,0.2f,0.2f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescNormals);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial9()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals  = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/maps/SpecularMapWave.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.0f);
    texDescDiffuse->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setHasUVTransform(true);
    texDescDiffuse->setScale(OSG::Vec2f(4.0, 4.0));
    texDescDiffuse->setImageMap(imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/maps/SpecularMapWave.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setHasUVTransform(true);
    texDescSpecular->setScale(OSG::Vec2f(4.0, 4.0));
    texDescSpecular->setImageMap(imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/maps/NormalMapWave.png");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setMirrorFlags(OSG::TextureDesc::MIRROR_VERTICAL_DIRECTION);
    texDescNormals->setHasUVTransform(true);
    texDescNormals->setScale(OSG::Vec2f(4.0, 4.0));
    texDescNormals->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescSpecular);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescNormals);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial10()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescDisplace = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/bricks2.jpg");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.0f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/bricks2_normal.jpg");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setImageMap(imageMap);
    
    texDescDisplace->setTextureType(OSG::TextureDesc::DISPLACEMENT_TEXTURE);
    texDescDisplace->setIsSRGBTexture(false);
    texDescDisplace->setFilename("Data/bricks2_disp.jpg");
    texDescDisplace->setUVChannel(0);
    texDescDisplace->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDisplace->setBlendFactor(1.f);
    texDescDisplace->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDisplace->setWrapS(GL_MIRRORED_REPEAT);
    texDescDisplace->setWrapT(GL_MIRRORED_REPEAT);
    texDescDisplace->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDisplace->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescNormals);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->setBumpScaling    (0.1f);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescNormals);
    matDesc2->addTexture        (texDescDisplace);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial11()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description for the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/bricks2.jpg");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc12->setIsSRGBTexture(true);
    texDesc12->setFilename("Data/penguin.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::DECAL_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::USE_ALPHA_FLAG);
    texDesc12->setHasUVTransform(true);
    texDesc12->setRotate(OSG::osgDegree2Rad(10.f));
    texDesc12->setScale(OSG::Vec2f(8.f, 8.f));
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::OPACITY_TEXTURE);
    texDesc13->setIsSRGBTexture(true);
    texDesc13->setFilename("Data/ornament.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setImageMap(imageMap);

    // Setup the texture description for the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/metal.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(100.f);
    texDesc21->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc22->setIsSRGBTexture(true);
    texDesc22->setFilename("Data/worldground.jpg");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::MULTIPLY_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG|OSG::TextureDesc::INVERT_FLAG);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::OPACITY_TEXTURE);
    texDesc23->setIsSRGBTexture(true);
    texDesc23->setFilename("Data/circles.jpg");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setOpacityCutOff  (0.1f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.5f);
    matDesc1->setMetalness      (0.8f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setOpacityCutOff  (0.1f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.5f);
    matDesc2->setMetalness      (0.8f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial12()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc14 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc15 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc24 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc25 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/wall/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/wall/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/wall/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    texDesc14->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc14->setIsSRGBTexture(false);
    texDesc14->setFilename("Data/pbr/wall/normal.png");
    texDesc14->setUVChannel(0);
    texDesc14->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc14->setBlendFactor(1.f);
    texDesc14->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc14->setWrapS(GL_MIRRORED_REPEAT);
    texDesc14->setWrapT(GL_MIRRORED_REPEAT);
    texDesc14->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc14->setImageMap(imageMap);

    texDesc15->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc15->setIsSRGBTexture(false);
    texDesc15->setFilename("Data/pbr/wall/ao.png");
    texDesc15->setUVChannel(0);
    texDesc15->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc15->setBlendFactor(1.f);
    texDesc15->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc15->setWrapS(GL_MIRRORED_REPEAT);
    texDesc15->setWrapT(GL_MIRRORED_REPEAT);
    texDesc15->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc15->setInternalFormat(GL_R8);
    texDesc15->setImageMap(imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/plastic/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/plastic/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/plastic/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    texDesc24->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc24->setIsSRGBTexture(false);
    texDesc24->setFilename("Data/pbr/plastic/normal.png");
    texDesc24->setUVChannel(0);
    texDesc24->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc24->setBlendFactor(1.f);
    texDesc24->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc24->setWrapS(GL_MIRRORED_REPEAT);
    texDesc24->setWrapT(GL_MIRRORED_REPEAT);
    texDesc24->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc24->setImageMap(imageMap);

    texDesc25->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc25->setIsSRGBTexture(false);
    texDesc25->setFilename("Data/pbr/plastic/ao.png");
    texDesc25->setUVChannel(0);
    texDesc25->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc25->setBlendFactor(1.f);
    texDesc25->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc25->setWrapS(GL_MIRRORED_REPEAT);
    texDesc25->setWrapT(GL_MIRRORED_REPEAT);
    texDesc25->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc25->setInternalFormat(GL_R8);
    texDesc25->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDesc14);
    matDesc1->addTexture        (texDesc15);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDesc24);
    matDesc2->addTexture        (texDesc25);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial13()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc14 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc15 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc24 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc25 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/wall/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/wall/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/wall/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    texDesc14->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc14->setIsSRGBTexture(false);
    texDesc14->setFilename("Data/pbr/wall/normal.png");
    texDesc14->setUVChannel(0);
    texDesc14->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc14->setBlendFactor(1.f);
    texDesc14->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc14->setWrapS(GL_MIRRORED_REPEAT);
    texDesc14->setWrapT(GL_MIRRORED_REPEAT);
    texDesc14->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc14->setImageMap(imageMap);

    texDesc15->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc15->setIsSRGBTexture(false);
    texDesc15->setFilename("Data/pbr/wall/ao.png");
    texDesc15->setUVChannel(0);
    texDesc15->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc15->setBlendFactor(1.f);
    texDesc15->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc15->setWrapS(GL_MIRRORED_REPEAT);
    texDesc15->setWrapT(GL_MIRRORED_REPEAT);
    texDesc15->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc15->setInternalFormat(GL_R8);
    texDesc15->setImageMap(imageMap);


    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/grass/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/grass/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/grass/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    texDesc24->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDesc24->setIsSRGBTexture(false);
    texDesc24->setFilename("Data/pbr/grass/normal.png");
    texDesc24->setUVChannel(0);
    texDesc24->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc24->setBlendFactor(1.f);
    texDesc24->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc24->setWrapS(GL_MIRRORED_REPEAT);
    texDesc24->setWrapT(GL_MIRRORED_REPEAT);
    texDesc24->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc24->setImageMap(imageMap);

    texDesc25->setTextureType(OSG::TextureDesc::AMBIENT_OCCLUSION_TEXTURE);
    texDesc25->setIsSRGBTexture(false);
    texDesc25->setFilename("Data/pbr/grass/ao.png");
    texDesc25->setUVChannel(0);
    texDesc25->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc25->setBlendFactor(1.f);
    texDesc25->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc25->setWrapS(GL_MIRRORED_REPEAT);
    texDesc25->setWrapT(GL_MIRRORED_REPEAT);
    texDesc25->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc25->setInternalFormat(GL_R8);
    texDesc25->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDesc14);
    matDesc1->addTexture        (texDesc15);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDesc24);
    matDesc2->addTexture        (texDesc25);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial14()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();


    OSG::TextureDescRefPtr  texDescReflection = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    if (skyFiles.size() == 6)
    {
        texDescReflection->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
        texDescReflection->setIsSRGBTexture(backgroundIsSRGB);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::POS_X].c_str(), OSG::TextureDesc::POS_X);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::POS_Y].c_str(), OSG::TextureDesc::POS_Y);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::POS_Z].c_str(), OSG::TextureDesc::POS_Z);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::NEG_X].c_str(), OSG::TextureDesc::NEG_X);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::NEG_Y].c_str(), OSG::TextureDesc::NEG_Y);
        texDescReflection->setFilename(skyFiles[OSG::TextureDesc::NEG_Z].c_str(), OSG::TextureDesc::NEG_Z);
        texDescReflection->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
        texDescReflection->setBlendFactor(1.f);
        texDescReflection->setWrapS(GL_CLAMP_TO_EDGE);
        texDescReflection->setWrapT(GL_CLAMP_TO_EDGE);
        texDescReflection->setWrapR(GL_CLAMP_TO_EDGE);
        texDescReflection->setImageMap(imageMap);

        //texDescReflection->setFilename("Data/Cubemaps/axis/+x.png", OSG::TextureDesc::POS_X);
        //texDescReflection->setFilename("Data/Cubemaps/axis/+y.png", OSG::TextureDesc::POS_Y);
        //texDescReflection->setFilename("Data/Cubemaps/axis/+z.png", OSG::TextureDesc::POS_Z);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-x.png", OSG::TextureDesc::NEG_X);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-y.png", OSG::TextureDesc::NEG_Y);
        //texDescReflection->setFilename("Data/Cubemaps/axis/-z.png", OSG::TextureDesc::NEG_Z);
    }

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescReflection);
        matDesc2->addTexture        (texDescReflection);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial15()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();


    OSG::TextureDescRefPtr  texDescRefl1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescRefl2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    texDescRefl1->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl1->setIsSRGBTexture(backgroundIsSRGB);
    texDescRefl1->setFilename("Data/hdr/newport_loft_hcross.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_vcross.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_hstrip.hdr");
    texDescRefl1->setFilename("Data/hdr/newport_loft_vstrip.hdr");
    texDescRefl1->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
    texDescRefl1->setBlendFactor(1.f);
    texDescRefl1->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl1->setImageMap(imageMap);

    if (skyFiles.size() == 6)
    {
        texDescRefl2->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
        texDescRefl2->setIsSRGBTexture(backgroundIsSRGB);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::POS_X].c_str(), OSG::TextureDesc::POS_X);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::POS_Y].c_str(), OSG::TextureDesc::POS_Y);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::POS_Z].c_str(), OSG::TextureDesc::POS_Z);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::NEG_X].c_str(), OSG::TextureDesc::NEG_X);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::NEG_Y].c_str(), OSG::TextureDesc::NEG_Y);
        texDescRefl2->setFilename(skyFiles[OSG::TextureDesc::NEG_Z].c_str(), OSG::TextureDesc::NEG_Z);
        texDescRefl2->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
        texDescRefl2->setBlendFactor(1.f);
        texDescRefl2->setWrapS(GL_CLAMP_TO_EDGE);
        texDescRefl2->setWrapT(GL_CLAMP_TO_EDGE);
        texDescRefl2->setWrapR(GL_CLAMP_TO_EDGE);
        texDescRefl2->setImageMap(imageMap);
    }

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescRefl1);
        matDesc2->addTexture        (texDescRefl2);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial16()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDescRefl1 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescRefl2 = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    texDescRefl1->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl1->setIsSRGBTexture(backgroundIsSRGB);
    texDescRefl1->setFilename("Data/hdr/newport_loft_latlong.hdr");
    texDescRefl1->setEnvironmentMapType(OSG::TextureDesc::EQUIRECTANGULAR_MAP);
    texDescRefl1->setBlendFactor(1.f);
    texDescRefl1->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl1->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl1->setImageMap(imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    texDescRefl2->setTextureType(OSG::TextureDesc::REFLECTION_TEXTURE);
    texDescRefl2->setIsSRGBTexture(backgroundIsSRGB);
    texDescRefl2->setFilename("Data/hdr/newport_loft_latlong.tga");
    texDescRefl2->setEnvironmentMapType(OSG::TextureDesc::EQUIRECTANGULAR_MAP);
    texDescRefl2->setBlendFactor(1.f);
    texDescRefl2->setWrapS(GL_CLAMP_TO_EDGE);
    texDescRefl2->setWrapT(GL_CLAMP_TO_EDGE);
    texDescRefl2->setWrapR(GL_CLAMP_TO_EDGE);
    texDescRefl2->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);

    if (skyFiles.size() == 6)
    {
        matDesc1->addTexture        (texDescRefl1);
        matDesc2->addTexture        (texDescRefl2);
    }

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial17()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDesc11 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc12 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc13 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDesc21 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc22 = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDesc23 = OSG::TextureDesc::create();

    OSG::TextureDescRefPtr  texDescIrradiance  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescPreFiltered = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescBrdf        = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture descriptions of the first object
    texDesc11->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc11->setIsSRGBTexture(true);
    texDesc11->setFilename("Data/pbr/gold/albedo.png");
    texDesc11->setUVChannel(0);
    texDesc11->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc11->setBlendFactor(1.f);
    texDesc11->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc11->setWrapS(GL_MIRRORED_REPEAT);
    texDesc11->setWrapT(GL_MIRRORED_REPEAT);
    texDesc11->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc11->setImageMap(imageMap);

    texDesc12->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc12->setIsSRGBTexture(false);
    texDesc12->setFilename("Data/pbr/gold/metallic.png");
    texDesc12->setUVChannel(0);
    texDesc12->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc12->setBlendFactor(1.f);
    texDesc12->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc12->setWrapS(GL_MIRRORED_REPEAT);
    texDesc12->setWrapT(GL_MIRRORED_REPEAT);
    texDesc12->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc12->setInternalFormat(GL_R8);
    texDesc12->setImageMap(imageMap);

    texDesc13->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc13->setIsSRGBTexture(false);
    texDesc13->setFilename("Data/pbr/gold/roughness.png");
    texDesc13->setUVChannel(0);
    texDesc13->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc13->setBlendFactor(1.f);
    texDesc13->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc13->setWrapS(GL_MIRRORED_REPEAT);
    texDesc13->setWrapT(GL_MIRRORED_REPEAT);
    texDesc13->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc13->setInternalFormat(GL_R8);
    texDesc13->setImageMap(imageMap);

    // Setup the texture descriptions of the second object
    texDesc21->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDesc21->setIsSRGBTexture(true);
    texDesc21->setFilename("Data/pbr/rusted_iron/albedo.png");
    texDesc21->setUVChannel(0);
    texDesc21->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc21->setBlendFactor(1.f);
    texDesc21->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc21->setWrapS(GL_MIRRORED_REPEAT);
    texDesc21->setWrapT(GL_MIRRORED_REPEAT);
    texDesc21->setImageMap(imageMap);

    texDesc22->setTextureType(OSG::TextureDesc::METAL_TEXTURE);
    texDesc22->setIsSRGBTexture(false);
    texDesc22->setFilename("Data/pbr/rusted_iron/metallic.png");
    texDesc22->setUVChannel(0);
    texDesc22->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc22->setBlendFactor(1.f);
    texDesc22->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc22->setWrapS(GL_MIRRORED_REPEAT);
    texDesc22->setWrapT(GL_MIRRORED_REPEAT);
    texDesc22->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc22->setInternalFormat(GL_R8);
    texDesc22->setImageMap(imageMap);

    texDesc23->setTextureType(OSG::TextureDesc::ROUGH_TEXTURE);
    texDesc23->setIsSRGBTexture(false);
    texDesc23->setFilename("Data/pbr/rusted_iron/roughness.png");
    texDesc23->setUVChannel(0);
    texDesc23->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDesc23->setBlendFactor(1.f);
    texDesc23->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDesc23->setWrapS(GL_MIRRORED_REPEAT);
    texDesc23->setWrapT(GL_MIRRORED_REPEAT);
    texDesc23->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDesc23->setInternalFormat(GL_R8);
    texDesc23->setImageMap(imageMap);

    texDescIrradiance->setTextureType(OSG::TextureDesc::IRRADIANCE_TEXTURE);
    texDescIrradiance->setIsSRGBTexture(false);
    texDescIrradiance->setFilename("Data/hdr/irradiance.hdr");
    texDescIrradiance->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
    texDescIrradiance->setBlendFactor(1.f);
    texDescIrradiance->setWrapS(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setWrapT(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setWrapR(GL_CLAMP_TO_EDGE);
    texDescIrradiance->setMinFilter(GL_LINEAR);
    texDescIrradiance->setMagFilter(GL_LINEAR);
    texDescIrradiance->setImageMap(imageMap);

    texDescPreFiltered->setTextureType(OSG::TextureDesc::PRE_FILTER_TEXTURE);
    texDescPreFiltered->setIsSRGBTexture(false);
    texDescPreFiltered->setFilename("Data/hdr/newport_loft_radiance_hcross.hdr");
    texDescPreFiltered->setEnvironmentMapType(OSG::TextureDesc::CUBE_MAP);
    texDescPreFiltered->setBlendFactor(1.f);
    texDescPreFiltered->setWrapS(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setWrapT(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setWrapR(GL_CLAMP_TO_EDGE);
    texDescPreFiltered->setImageMap(imageMap);

    texDescBrdf->setTextureType(OSG::TextureDesc::PRE_FILTER_TEXTURE);
    texDescBrdf->setIsSRGBTexture(false);
    texDescBrdf->setFilename("Data/pbr/ibl_brdf_lut.png");
    texDescBrdf->setBlendFactor(1.f);
    texDescBrdf->setWrapS(GL_CLAMP_TO_EDGE);
    texDescBrdf->setWrapT(GL_CLAMP_TO_EDGE);
    texDescBrdf->setWrapR(GL_CLAMP_TO_EDGE);
    texDescBrdf->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0.71373f, 0.42745f, 0.18039f));
    matDesc1->setSpecular       (OSG::Color3f(0.39216f, 0.27059f, 0.16863f));
    matDesc1->setShininess      (0.2f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setReflectivity   (1.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDesc11);
    matDesc1->addTexture        (texDesc12);
    matDesc1->addTexture        (texDesc13);
    matDesc1->addTexture        (texDescIrradiance);
    //matDesc1->addTexture        (texDescPreFiltered);
    //matDesc1->addTexture        (texDescBrdf);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0.34902f, 0.30980f, 0.09020f));
    matDesc2->setSpecular       (OSG::Color3f(0.80000f, 0.72157f, 0.21176f));
    matDesc2->setShininess      (0.65f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setReflectivity   (1.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDesc21);
    matDesc2->addTexture        (texDesc22);
    matDesc2->addTexture        (texDesc23);
    matDesc2->addTexture        (texDescIrradiance);
    //matDesc2->addTexture        (texDescPreFiltered);
    //matDesc2->addTexture        (texDescBrdf);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

void setupMaterial18()
{
}

void setupMaterial19()
{
}

void setupMaterial20()
{
}

void setupMaterial21()
{
}

void setupMaterialCyborg()
{
    OSG::MaterialDescRefPtr matDesc1 = OSG::MaterialDesc::create();
    OSG::MaterialDescRefPtr matDesc2 = OSG::MaterialDesc::create();

    OSG::TextureDescRefPtr  texDescDiffuse  = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescSpecular = OSG::TextureDesc::create();
    OSG::TextureDescRefPtr  texDescNormals  = OSG::TextureDesc::create();

    OSG::UInt32 shadingModel = shadingModels[shadingModelIdx];

    // Setup the texture description
    texDescDiffuse->setTextureType(OSG::TextureDesc::ALBEDO_TEXTURE);
    texDescDiffuse->setIsSRGBTexture(true);
    texDescDiffuse->setFilename("Data/cyborg/cyborg_diffuse.png");
    texDescDiffuse->setUVChannel(0);
    texDescDiffuse->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescDiffuse->setBlendFactor(1.0f);
    texDescDiffuse->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescDiffuse->setWrapS(GL_MIRRORED_REPEAT);
    texDescDiffuse->setWrapT(GL_MIRRORED_REPEAT);
    texDescDiffuse->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescDiffuse->setImageMap(imageMap);

    texDescSpecular->setTextureType(OSG::TextureDesc::SPECULAR_TEXTURE);
    texDescSpecular->setIsSRGBTexture(true);
    texDescSpecular->setFilename("Data/cyborg/cyborg_specular.png");
    texDescSpecular->setUVChannel(0);
    texDescSpecular->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescSpecular->setBlendFactor(1.f);
    texDescSpecular->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescSpecular->setWrapS(GL_MIRRORED_REPEAT);
    texDescSpecular->setWrapT(GL_MIRRORED_REPEAT);
    texDescSpecular->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescSpecular->setImageMap(imageMap);

    texDescNormals->setTextureType(OSG::TextureDesc::NORMALS_TEXTURE);
    texDescNormals->setIsSRGBTexture(false);
    texDescNormals->setFilename("Data/cyborg/cyborg_normal.png");
    texDescNormals->setUVChannel(0);
    texDescNormals->setMappingMode(OSG::TextureDesc::UV_MAPPING);
    texDescNormals->setBlendFactor(1.f);
    texDescNormals->setOperation(OSG::TextureDesc::REPLACE_OPERATION);
    texDescNormals->setWrapS(GL_MIRRORED_REPEAT);
    texDescNormals->setWrapT(GL_MIRRORED_REPEAT);
    texDescNormals->setTextureFlags(OSG::TextureDesc::IGNORE_ALPHA_FLAG);
    texDescNormals->setImageMap(imageMap);

    // Setup the material description
    matDesc1->setShadingModel   (shadingModel);
    matDesc1->setFlatShadingMode    (useFlatShading);
    matDesc1->setEmissive       (OSG::Color3f(0,0,0));
    matDesc1->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc1->setSpecular       (OSG::Color3f(0,0,0));
    matDesc1->setShininess      (0.5f * 128.f);
    matDesc1->setOpacity        (1.0f);
    matDesc1->setSRGBColorMode    (true);
    matDesc1->setRoughness      (0.f);
    matDesc1->setMetalness      (0.f);
    matDesc1->setNumUVChannels  (1);
    matDesc1->addTexture        (texDescDiffuse);
    matDesc1->addTexture        (texDescSpecular);

    matDesc2->setShadingModel   (shadingModel);
    matDesc2->setFlatShadingMode    (useFlatShading);
    matDesc2->setEmissive       (OSG::Color3f(0,0,0));
    matDesc2->setAlbedo         (OSG::Color3f(0,0,0));
    matDesc2->setSpecular       (OSG::Color3f(0,0,0));
    matDesc2->setShininess      (0.5f * 128.f);
    matDesc2->setOpacity        (1.0f);
    matDesc2->setSRGBColorMode    (true);
    matDesc2->setRoughness      (0.f);
    matDesc2->setMetalness      (0.f);
    matDesc2->setNumUVChannels  (1);
    matDesc2->addTexture        (texDescNormals);
    matDesc2->addTexture        (texDescDiffuse);
    matDesc2->addTexture        (texDescSpecular);

    // get the final description material
    OSG::MaterialManager::ManagedMaterialT m1 = materialManager->addMaterial(matDesc1);
    OSG::MaterialManager::ManagedMaterialT m2 = materialManager->addMaterial(matDesc2);

    OSG::ChunkMaterial* descMaterial1 = m1.second;
    OSG::ChunkMaterial* descMaterial2 = m2.second;

    if (materialGroup1) materialGroup1->setMaterial(descMaterial1);
    if (materialGroup2) materialGroup2->setMaterial(descMaterial2);
}

typedef std::vector<OSG::GeometryRefPtr> GeometryStore;

class find_geom_cores_helper
{
public:
    explicit find_geom_cores_helper(GeometryStore& vecGeoms) : _vecGeoms(vecGeoms) {}

    OSG::Action::ResultE enter(OSG::Node* node)
    {
        OSG::Geometry* geomCore = dynamic_cast<OSG::Geometry*>(node->getCore());
        if (geomCore)
            _vecGeoms.push_back(geomCore);

        return OSG::Action::Continue;
    }

private:
    GeometryStore&  _vecGeoms;
};

void assembleScene(OSG::Node* geo1Node, OSG::Node* geo2Node)
{
    if (geo1Node == NULL || geo2Node == NULL)
        return;

    OSG::commitChanges();

    geo1Node->updateVolume();
    geo2Node->updateVolume();

    const OSG::BoxVolume& vol1 = geo1Node->getVolume();
    const OSG::BoxVolume& vol2 = geo2Node->getVolume();

    OSG::Real32 szX1, szY1, szZ1;
    OSG::Real32 szX2, szY2, szZ2;

    vol1.getSize(szX1, szY1, szZ1);
    vol2.getSize(szX2, szY2, szZ2);

    OSG::Real32 sz1 = OSG::osgMax(szX1, OSG::osgMax(szY1, szZ1));
    OSG::Real32 sz2 = OSG::osgMax(szX2, OSG::osgMax(szY2, szZ2));

    OSG::Real32 f1, f2;
    OSG::Real32 v1, v2;

    f1 = 1.f / sz1;
    f2 = 1.f / sz2;

    v1 = 0.8f;
    v2 = 0.8f;

    OSG::Vec3f scale1(f1,f1,f1);
    OSG::Vec3f scale2(f2,f2,f2);

    OSG::Vec3f move1(v1,v1,v1);
    OSG::Vec3f move2(v2,v2,v2);

    if (materialGroup1 == NULL) materialGroup1 = OSG::MaterialGroup::create();
    if (materialGroup2 == NULL) materialGroup2 = OSG::MaterialGroup::create();

    mat1Node = OSG::Node::create();
    mat2Node = OSG::Node::create();

    OSG::TransformRefPtr geo1Trans1 = OSG::Transform::create();
    OSG::TransformRefPtr geo2Trans1 = OSG::Transform::create();

    OSG::NodeRefPtr geo1TransNode   = OSG::Node::create();
    OSG::NodeRefPtr geo2TransNode   = OSG::Node::create();

    OSG::NodeRefPtr geo1TransNode1  = OSG::Node::create();
    OSG::NodeRefPtr geo2TransNode1  = OSG::Node::create();

    OSG::Matrix geo1Mat;
    OSG::Matrix geo2Mat;

    geo1Mat.setTranslate (-move1);
    geo1Mat.setScale     (scale1);
    geo1Trans1->setMatrix(geo1Mat);

    geo2Mat.setTranslate (move2);
    geo2Mat.setScale     (scale2);
    geo2Trans1->setMatrix(geo2Mat);

    if (useModelMaterial)
    {
        mat1Node->setCore(OSG::Group::create());
        mat2Node->setCore(OSG::Group::create());
    }
    else
    {
        mat1Node->setCore(materialGroup1);
        mat2Node->setCore(materialGroup2);
    }

    geo1TransNode->setCore (geo1Trans);
    geo2TransNode->setCore (geo2Trans);

    geo1TransNode1->setCore(geo1Trans1);
    geo2TransNode1->setCore(geo2Trans1);

    geo1TransNode ->addChild(geo1TransNode1);
    geo2TransNode ->addChild(geo2TransNode1);

    geo1TransNode1->addChild(geo1Node);
    geo2TransNode1->addChild(geo2Node);

    mat1Node->addChild(geo1TransNode);
    mat2Node->addChild(geo2TransNode);

    scene->addChild(mat1Node);
    scene->addChild(mat2Node);
}

void manageNodePairStore(OSG::Int32 storeIdx)
{
    storeIdx -= numTrackedModels;
    if (storeIdx < 0)
        storeIdx = numGeoTypes + storeIdx;

    OSG_ASSERT(0 <= storeIdx && storeIdx < nodePairStore.size());

    OSG::NodeRefPtr geo1Node = NULL;
    OSG::NodeRefPtr geo2Node = NULL;
    nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
}

void setupScene0(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::makeTorus   ( .2f, 1, 24, 36 );
        geo2Node = OSG::makeCylinder( 1.4f, .3f, 24, true, true, true );

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void setupScene1(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::makeBox(1,1,1,10,10,10);
        geo2Node = OSG::makeBox(1,1,1,10,10,10);

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void setupScene2(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::Node::create();
        geo2Node = OSG::Node::create();

        OSG::GeometryRefPtr geo1 = NULL;
        OSG::GeometryRefPtr geo2 = NULL;

        OSG::NodeRefPtr node;
        node = OSG::SceneFileHandler::the()->read("data/box1.osb");
        if (node != NULL)
        {
            GeometryStore v;
            find_geom_cores_helper helper(v);
            traverse(node, boost::bind(&find_geom_cores_helper::enter, &helper, _1));

            if (!v.empty())
            {
                geo1 = v[0];
            }
        }

        node = OSG::SceneFileHandler::the()->read("data/box2.osb");
        if (node != NULL)
        {
            GeometryStore v;
            find_geom_cores_helper helper(v);
            traverse(node, boost::bind(&find_geom_cores_helper::enter, &helper, _1));

            if (!v.empty())
            {
                geo2 = v[0];
            }
        }

        geo1Node->setCore(geo1);
        geo2Node->setCore(geo2);

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void setupScene3(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::makeSphere(3,1);
        geo2Node = OSG::makeSphere(3,1);

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void setupScene4(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::SceneFileHandler::the()->read("data/dinopet.3ds");
        geo2Node = OSG::SceneFileHandler::the()->read("data/tie.wrl");

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void setupScene5(OSG::Int32 storeIdx)
{
    scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        geo1Node = OSG::SceneFileHandler::the()->read("data/cyborg/cyborg.obj");
        geo2Node = OSG::SceneFileHandler::the()->read("data/cyborg/cyborg.obj");

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);

    setupMaterialCyborg();

    exampleType = cyborg_example;
}

void setupSceneIdx(OSG::Int32 storeIdx, const OSG::Char8* name, OSG::Int32 idx)
{
   scene->clearChildren();

    OSG::NodeRefPtr geo1Node = nodePairStore[storeIdx].first;
    OSG::NodeRefPtr geo2Node = nodePairStore[storeIdx].second;

    if (geo1Node == NULL || geo2Node == NULL)
    {
        manageNodePairStore(storeIdx);

        std::stringstream ss;
        ss << name << idx << ".osb" << std::flush;

        geo1Node = OSG::SceneFileHandler::the()->read(ss.str().c_str(), NULL);
        geo2Node = OSG::SceneFileHandler::the()->read(ss.str().c_str(), NULL);

        nodePairStore[storeIdx] = std::make_pair(geo1Node, geo2Node);
    }

    assembleScene(geo1Node, geo2Node);
}

void initBackground()
{
    if (bgndIdx > 0)
    {
        skyFiles.clear();

        switch (bgndIdx)
        {
        case 1:
            skyFiles.push_back("Data/Cubemaps/CoitTower2/posx.jpg");
            skyFiles.push_back("Data/Cubemaps/CoitTower2/posy.jpg");
            skyFiles.push_back("Data/Cubemaps/CoitTower2/posz.jpg");
            skyFiles.push_back("Data/Cubemaps/CoitTower2/negx.jpg");
            skyFiles.push_back("Data/Cubemaps/CoitTower2/negy.jpg");
            skyFiles.push_back("Data/Cubemaps/CoitTower2/negz.jpg");
            break;
        case 2:
            skyFiles.push_back("Data/Cubemaps/GamlaStan/posx.jpg");
            skyFiles.push_back("Data/Cubemaps/GamlaStan/posy.jpg");
            skyFiles.push_back("Data/Cubemaps/GamlaStan/posz.jpg");
            skyFiles.push_back("Data/Cubemaps/GamlaStan/negx.jpg");
            skyFiles.push_back("Data/Cubemaps/GamlaStan/negy.jpg");
            skyFiles.push_back("Data/Cubemaps/GamlaStan/negz.jpg");
            break;
        case 3:
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+x.jpg");
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+y.jpg");
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/+z.jpg");
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-x.jpg");
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-y.jpg");
            skyFiles.push_back("Data/Cubemaps/NiagaraFalls2/-z.jpg");
            break;
        case 4:
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posx.jpg");
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posy.jpg");
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/posz.jpg");
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negx.jpg");
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negy.jpg");
            skyFiles.push_back("Data/Cubemaps/SaintLazarusChurch3/negz.jpg");
            break;
        case 5:
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posx.jpg");
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posy.jpg");
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/posz.jpg");
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negx.jpg");
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negy.jpg");
            skyFiles.push_back("Data/Cubemaps/SanFrancisco4/negz.jpg");
            break;
        case 6:
            skyFiles.push_back("Data/hdr/newport_loft_posx.hdr");
            skyFiles.push_back("Data/hdr/newport_loft_posy.hdr");
            skyFiles.push_back("Data/hdr/newport_loft_posz.hdr");
            skyFiles.push_back("Data/hdr/newport_loft_negx.hdr");
            skyFiles.push_back("Data/hdr/newport_loft_negy.hdr");
            skyFiles.push_back("Data/hdr/newport_loft_negz.hdr");
            break;
        case 7:
            skyFiles.push_back("Data/Cubemaps/mountain_orange/+x.jpg");
            skyFiles.push_back("Data/Cubemaps/mountain_orange/+y.jpg");
            skyFiles.push_back("Data/Cubemaps/mountain_orange/+z.jpg");
            skyFiles.push_back("Data/Cubemaps/mountain_orange/-x.jpg");
            skyFiles.push_back("Data/Cubemaps/mountain_orange/-y.jpg");
            skyFiles.push_back("Data/Cubemaps/mountain_orange/-z.jpg");
        }

        OSG_ASSERT(skyFiles.size() == 6);
    }
}

void setupBackground()
{
    if (bgndIdx == 0)
    {
        std::cout << "SetupBackground: solid background" << std::endl;

        OSG::SolidBackgroundRefPtr background = OSG::SolidBackground::create();
        background->setColor(OSG::Color3f(0.5f,0.5f,0.5f));
        mgr->setBackground(background);
    }
    else
    {
        initBackground();

        OSG_ASSERT(skyFiles.size() == 6);

        std::cout << "SetupBackground: sky background : " << skyFiles[0] << ", ... Color Space setting isSRGB = " << (backgroundIsSRGB ? "true" : "false") << std::endl;

        OSG::SkyBackgroundRefPtr skyBgnd = OSG::SkyBackground::create();

        OSG::ImageUnrecPtr images[6];
        OSG::TextureObjChunkUnrecPtr texObjs[6];

        for (OSG::UInt32 i = OSG::TextureDesc::POS_X; i <= OSG::TextureDesc::NEG_Z; ++i)
        {
            typedef OSG::HashKeyToFieldContainerMap::HashKeyType HashKeyType;
            HashKeyType key;

            key = OSG::Hash64::hash(&skyFiles[i][0], skyFiles[i].size(), 0);
            images[i] = dynamic_cast<OSG::Image*>(imageMap->find(key));

            if (images[i] == NULL)
            {
                images[i] = OSG::ImageFileHandler::the()->read(skyFiles[i].c_str());
                imageMap->insert(key, images[i]);
            }

            texObjs[i] = OSG::TextureObjChunk::create();

            if (backgroundIsSRGB)
            {
                texObjs[i]->setInternalFormat(GL_SRGB);
            }

            texObjs[i]->setImage(images[i]);

            texObjs[i]->setWrapS(GL_CLAMP_TO_EDGE);
            texObjs[i]->setWrapT(GL_CLAMP_TO_EDGE);
        }

        skyBgnd->setBackTexture  (texObjs[OSG::TextureDesc::NEG_Z]);
        skyBgnd->setFrontTexture (texObjs[OSG::TextureDesc::POS_Z]);
        skyBgnd->setLeftTexture  (texObjs[OSG::TextureDesc::NEG_X]);
        skyBgnd->setRightTexture (texObjs[OSG::TextureDesc::POS_X]);
        skyBgnd->setBottomTexture(texObjs[OSG::TextureDesc::NEG_Y]);
        skyBgnd->setTopTexture   (texObjs[OSG::TextureDesc::POS_Y]);

        mgr->setBackground(skyBgnd);
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

/*
    OSG::ImageRefPtr aoImage    = OSG::ImageFileHandler::the()->read("d:/_xxx/work/Data/pbrMaterials/texturehaven/Bricks/test/brick_4_AO_1k.jpg");
    OSG::ImageRefPtr roughImage = OSG::ImageFileHandler::the()->read("d:/_xxx/work/Data/pbrMaterials/texturehaven/Bricks/test/brick_4_rough_1k.jpg");
    OSG::ImageRefPtr metalImage = OSG::ImageFileHandler::the()->read("d:/_xxx/work/Data/pbrMaterials/texturehaven/Bricks/test/brick_4_spec_1k.jpg");
    OSG::ImageRefPtr dispImage  = OSG::ImageFileHandler::the()->read("d:/_xxx/work/Data/pbrMaterials/texturehaven/Bricks/test/brick_4_disp_1k.jpg");

    OSG::ImageRefPtr dstImage1 = OSG::Image::create();
    OSG::ImageRefPtr dstImage2 = OSG::Image::create();

    dstImage1->copyComponent(metalImage, 0, 0, OSG::Image::OSG_RGBA_PF);
    dstImage1->copyComponent(roughImage, 0, 1, OSG::Image::OSG_RGBA_PF);
    dstImage1->copyComponent(dispImage,  0, 2, OSG::Image::OSG_RGBA_PF);
    dstImage1->copyComponent(aoImage,    0, 3, OSG::Image::OSG_RGBA_PF);

    dstImage2->copyComponent(metalImage, 0, 0, OSG::Image::OSG_RGBA_PF);
    dstImage2->copyComponent(roughImage, 0, 1, OSG::Image::OSG_RGBA_PF);
    dstImage2->copyComponent(dispImage,  0, 2, OSG::Image::OSG_RGBA_PF);
    dstImage2->copyComponent(aoImage,    0, 3, OSG::Image::OSG_RGBA_PF);

    dstImage1->write("d:/work/test.png");

    dstImage1->flipComponent(2, false);
    dstImage2->flipComponent(2, true);

    dstImage1->write("d:/work/test_flip_false.png");
    dstImage2->write("d:/work/test_flip_true.png");

    exit(0);
*/
    //OSG::ContribDDSImageFileType* ddsImageFileType = new OSG::ContribDDSImageFileType();
    //OSG::ContribKTXImageFileType* ktxImageFileType = new OSG::ContribKTXImageFileType();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // Test only ddsAndktxFiles
    //{
    //    std::size_t sz = ddsAndktxFiles.size();

    //    for (std::size_t i = 0; i < sz; ++i)
    //    {
    //        const std::string& f = ddsAndktxFiles[i];

    //        {
    //            std::ofstream os("d:/work/readDDSAndKtx.log", std::ofstream::out | std::ofstream::app);
    //            os << "file = " <<  f << std::endl;
    //        }

    //        OSG::ImageUnrecPtr image = OSG::Image::createLocal();
    //        bool result = image->read(f.c_str());
    //    }
    //}

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

//        OSG::NodeRefPtr loadNode = OSG::SceneFileHandler::the()->read("d:/DescMatTest1.osb");
//        mgr->setRoot(loadNode);

        OSG::ShaderProgramFunctor   initFunctor = boost::bind(::initShader,   _1);
        OSG::ShaderProgramFunctor updateFunctor = boost::bind(::updateShader, _1);
        
        // create the DescMaterialManager
        materialManager = OSG::DescMaterialManager::createDefault(initFunctor, "", updateFunctor, "");
        materialManager->setWindow(gwin);

        imageMap = materialManager->getImageMap();

        nodePairStore.resize(numGeoTypes);

        //
        // Simple shading models
        //
        shadingModels.push_back(OSG::MaterialDesc::NO_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::GOURAUD_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::PHONG_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::BLINN_PHONG_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::COOK_TORRANCE_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::OREN_NAYAR_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::TOON_SHADING_MODEL);
        shadingModels.push_back(OSG::MaterialDesc::GOOCH_SHADING_MODEL);

        // The scene
        hdr2Stage = OSG::HDR2Stage::create();
        hdr2Stage->setActivate        (useHdrStage);
        hdr2Stage->setAutoExposureMode(OSG::HDR2Stage::KEY_VALUE);
        hdr2Stage->setKeyValue        (0.6f);
        hdr2Stage->setPerformBloom    (false);
        hdr2Stage->setAdjustLuminance (false);
        hdr2Stage->setForceBackground (true);
        hdr2Stage->setNumSamples(4);

        OSG::NodeRefPtr hdr2Node = OSG::Node::create();
        hdr2Node->setCore(hdr2Stage);

        if (hdr2Stage->getActivate())
        {
            materialManager->setHDR2Stage(hdr2Stage);
        }
        
        ssaoStage = OSG::SSAOStage::create();
        ssaoStage->setActivate(useSSAOStage);
        ssaoStage->setCalcPosFromDepth(true);
        
        OSG::NodeRefPtr ssaoNode = OSG::Node::create();
        ssaoNode->setCore(ssaoStage);

        if (ssaoStage->getActivate())
        {
            materialManager->setSSAOStage(ssaoStage);
        }

        lightRoot = OSG::Node::create();

        hdr2Node->addChild(ssaoNode);
        ssaoNode->addChild(lightRoot);

        scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());

        createLights(lightRoot, scene);

        // We will animate the geometry of the scene a little
        geo1Trans = OSG::Transform::create();
        geo2Trans = OSG::Transform::create();

        initBackground();

        setupScene();
        
        setupMaterial();

        mgr->setRoot(hdr2Node);

        // show the whole scene
        mgr->showAll();

        setupBackground();
    
        OSG::commitChanges();
    }

    print_usage();
    print_shadingModel(shadingModelIdx);
    print_example();

    //bool result = OSG::SceneFileHandler::the()->write(mgr->getRoot(), "d:/DescMatTest1.osb");

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//
bool object_animation = false;
bool  light_animation = false;

//
// redraw the window
//
void display(void)
{
    if (object_animation || light_animation)
    {
        OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );

        if (light_animation)
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                OSG::Matrix lightMatrix;
        
                makeMatrix(t - 2000 * i, lightMatrix);

                lightBeacons[i]->setMatrix(lightMatrix);
            }
        }

        if (object_animation)
        {
            OSG::Matrix m;

            // set the transforms' matrices
            m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                           OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

            geo1Trans->setMatrix(m);
    
            m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                           OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

            geo2Trans->setMatrix(m);
        }

        OSG::commitChanges();
    }
    
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
    switch (k)
    {
        case 27:    
        {
            // clean up global variables
            geo1Trans       = NULL;
            geo2Trans       = NULL;
            mgr             = NULL;

            materialGroup1  = NULL;
            materialGroup2  = NULL;

            mat1Node        = NULL;
            mat2Node        = NULL;

            scene           = NULL;

            hdr2Stage       = NULL;
            ssaoStage       = NULL;

            imageMap        = NULL;
            materialManager = NULL;

            lightRoot       = NULL;
            multiLightGroup = NULL;

            lightBeacons.clear();
            lights      .clear();

            nodePairStore.clear();

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'h':   // show help
        {
            print_usage();
        }
        break;

        case '1':   // Deactivate all lights and then loop through the point lights
        {
            OSG::Int32 maxLight = nlights / 3;
            currLight++;
            if (currLight >= maxLight)
                currLight = 0;

            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                lights[i]->setOn(false);
            }

            for(OSG::UInt16 i = 0, idx = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() == OSG::PointLight::getClassTypeId())
                {
                    if (currLight == idx++)
                    {
                        lights[i]->setOn(true);
                    }
                }
            }
            OSG::commitChanges();
        }
        break;

        case '2':   // Deactivate all lights and then loop through the directional lights
        {
            OSG::Int32 maxLight = nlights / 3;
            currLight++;
            if (currLight >= maxLight)
                currLight = 0;

            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                lights[i]->setOn(false);
            }

            for(OSG::UInt16 i = 0, idx = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() == OSG::DirectionalLight::getClassTypeId())
                {
                    if (currLight == idx++)
                    {
                        lights[i]->setOn(true);
                    }
                }
            }
            OSG::commitChanges();
        }
        break;

        case '3':   // Deactivate all lights and then loop through the spot lights
        {
            OSG::Int32 maxLight = nlights / 3;
            currLight++;
            if (currLight >= maxLight)
                currLight = 0;

            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                lights[i]->setOn(false);
            }

            for(OSG::UInt16 i = 0, idx = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() == OSG::SpotLight::getClassTypeId())
                {
                    if (currLight == idx++)
                    {
                        lights[i]->setOn(true);
                    }
                }
            }
            OSG::commitChanges();
        }
        break;

        case 'a':   // activate all lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                lights[i]->setOn(true);
            }
        }
        break;
         
        case 's':   // deactivate all but the spot lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != OSG::SpotLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;
         
        case 'd':   // deactivate all but the directional lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != 
                                      OSG::DirectionalLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;
         
        case 'p':   // deactivate all but the point lights
        {
            for(OSG::UInt16 i = 0; i < nlights; ++i)
            {
                if(lights[i]->getTypeId() != OSG::PointLight::getClassTypeId())
                {
                    lights[i]->setOn(false);
                }
                else
                {
                    lights[i]->setOn(true);
                }
            }
            OSG::commitChanges();
        }
        break;

        case 'S':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;

        case 'l':
        {
            light_animation = !light_animation;
        }
        break;

        case 'L':
        {
            useMultiLight = !useMultiLight;

            createLights(lightRoot, scene);
            setupMaterial();

            OSG::commitChanges();
        }
        break;

        case 'm':
        {
            shadingModelIdx++;
            if (shadingModelIdx >= shadingModels.size())
                shadingModelIdx = 0;

            setupMaterial();
            print_shadingModel(shadingModelIdx);

            OSG::commitChanges();
        }
        break;

        case 'M':
        {
            shadingModelIdx--;
            if (shadingModelIdx < 0)
                shadingModelIdx = static_cast<OSG::Int32>(shadingModels.size())-1;

            setupMaterial();
            print_shadingModel(shadingModelIdx);

            OSG::commitChanges();
        }
        break;

        case 'e':
        {
            if (exampleType == normal_example)
            {
                exampleIndex++;
                if (exampleIndex >= numExamples)
                    exampleIndex = 0;

                setupMaterial();
                print_example();

                OSG::commitChanges();
            }
        }
        break;

        case 'E':
        {
            if (exampleType == normal_example)
            {
                exampleIndex--;
                if (exampleIndex < 0)
                    exampleIndex = numExamples-1;

                setupMaterial();
                print_example();

                OSG::commitChanges();
            }
        }
        break;

        case 'g':
        {
            geoTypeIndex++;
            if (geoTypeIndex >= numGeoTypes)
                geoTypeIndex = 0;

            setupScene();

            OSG::commitChanges();
        }
        break;

        case 'G':
        {
            geoTypeIndex--;
            if (geoTypeIndex < 0)
                geoTypeIndex = numGeoTypes-1;

            setupScene();

            OSG::commitChanges();
        }
        break;

        case 'N':
        {
            useModelMaterial = !useModelMaterial;

            if (useModelMaterial)
            {
                mat1Node->setCore(OSG::Group::create());
                mat2Node->setCore(OSG::Group::create());

                std::cout << "Usage of model's material" << std::endl;
            }
            else
            {
                mat1Node->setCore(materialGroup1);
                mat2Node->setCore(materialGroup2);

                std::cout << "Usage of description material" << std::endl;
            }

            OSG::commitChanges();
        }
        break;

        case 'H':
        {
            useHdrStage = !useHdrStage;

            hdr2Stage->setActivate(useHdrStage);

            std::cout << "HDR stage "<< (useHdrStage ? "is " : "is in") << "active" << std::endl;

            if (hdr2Stage->getActivate())
            {
                materialManager->setHDR2Stage(hdr2Stage);
            }
            else
            {
                materialManager->setHDR2Stage(NULL);
            }

            OSG::commitChanges();

            setupMaterial();

            OSG::commitChanges();
        }
        break;

        case 'A':
        {
            useSSAOStage = !useSSAOStage;

            ssaoStage->setActivate(useSSAOStage);

            std::cout << "SSAO stage "<< (useSSAOStage ? "is " : "is in") << "active" << std::endl;

            if (ssaoStage->getActivate())
            {
                materialManager->setSSAOStage(ssaoStage);
            }
            else
            {
                materialManager->setSSAOStage(NULL);
            }

            OSG::commitChanges();

            setupMaterial();

            OSG::commitChanges();
        }
        break;


        case 'x':
        {
            testValue += 0.0005f;
            if (testValue > 1.f)
                testValue = 0.f;

            materialManager->updateProgram();

            std::cout << "testValue = " << testValue << std::endl;

            OSG::commitChanges();
        }
        break;

        case 'X':
        {
            testValue -= 0.0005f;
            if (testValue < 0.f)
                testValue = 1.f;

            materialManager->updateProgram();

            std::cout << "testValue = " << testValue << std::endl;

            OSG::commitChanges();
        }
        break;

        case 'b':
        {
            bgndIdx++;
            if (bgndIdx > numSkyBgnds)
                bgndIdx = 0;

            setupBackground();

            OSG::commitChanges();

            setupMaterial();

            OSG::commitChanges();
        }
        break;

        case 'B':
        {
            if (bgndIdx == 0)
                bgndIdx = numSkyBgnds+1;

            bgndIdx--;

            setupBackground();

            OSG::commitChanges();

            setupMaterial();

            OSG::commitChanges();
        }
        break;

        case 'V':
        {
            backgroundIsSRGB = !backgroundIsSRGB;

            setupBackground();

            OSG::commitChanges();

            setupMaterial();

            OSG::commitChanges();
        }
        break;

        case 'f':
        {
            useFlatShading = !useFlatShading;

            setupMaterial();

            OSG::commitChanges();
        }
        break;


        case 32:
        {
            object_animation = !object_animation;
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
    glutInitWindowSize(1000, 800);
    
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

void clear_console()
{
#ifdef WIN32
    COORD topLeft  = { 0, 0 };
    HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO sbi;

    ::GetConsoleScreenBufferInfo(console, &sbi);

    DWORD written;
    DWORD cells = sbi.dwSize.X * sbi.dwSize.Y;

    ::FillConsoleOutputCharacter(console, 
                                 ' ', 
                                 cells, 
                                 topLeft, 
                                 &written);
    ::SetConsoleCursorPosition  (console, topLeft);
#else
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
#endif
}

