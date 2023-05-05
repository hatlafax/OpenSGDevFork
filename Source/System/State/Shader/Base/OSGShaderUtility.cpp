/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

// System declarations

#include "OSGShaderUtility.h"

OSG_BEGIN_NAMESPACE

namespace Shader {

OSG_SYSTEM_DLLMAPPING std::string getConstantsSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "const float OSG_PI         = 3.14159265359;"
    << endl << "const float OSG_HALF_PI    = 0.5*OSG_PI;"
    << endl << "const float OSG_INV_PI     = 1.0/OSG_PI;"
    << endl << "const float OSG_INV_2PI    = 1.0/(2.0*OSG_PI);"
    << endl << "const float OSG_INV_8PI    = 1.0/(8.0*OSG_PI);"
    << endl << "const float OSG_TWO_DIV_PI = 2.0*OSG_INV_PI;"
    << endl << "const vec2  OSG_INV_ATAN   = vec2(OSG_INV_2PI, OSG_INV_PI);"
    << endl << "const float OSG_EPS        = 1.0E-6;"
    << endl << "const float OSG_LN2        = 0.69314718056;"
    << endl << "const float OSG_INV_LN2    = 1.44269504089;"
    << endl << "const float OSG_INV_LOG_10 = 1.0/log(10.0);"
    << endl << "const vec3  OSG_BLACK      = vec3(0.0, 0.0, 0.0);"
    << endl << "const vec3  OSG_WHITE      = vec3(1.0, 1.0, 1.0);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getLanguageExtSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "#define saturate(x)             clamp(x, 0.0, 1.0)"
    << endl << "#define whiteCompliment(x)      (1.0 - saturate(x))"
    << endl << "#define lerp                    mix"
    << endl << "#define frac                    fract"
    << endl << ""
    << endl << "float OSGLog10(const in float x) { return OSG_INV_LOG_10 * log(x); }"
    << endl << "float OSGPow2 (const in float x) { return x*x;   }"
    << endl << "float OSGPow3 (const in float x) { return x*x*x; }"
    << endl << "float OSGPow4 (const in float x) { float x2 = x*x; return x2*x2; }"
    << endl << "vec3  OSGPow  (const in vec3 x, in float v) { return pow(x, vec3(v)); }"
    << endl << ""
    << endl << "float OSGMaxOf(const in vec3 x)  { return max(x.r, max(x.g, x.b)); }"
    << endl << "float OSGMinOf(const in vec3 x)  { return min(x.r, min(x.g, x.b)); }"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getEqualEpsDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "bool OSGEqualEps(in float a, in float b, in float eps);"
    << endl << "bool OSGEqualEps(in vec2  a, in vec2  b, in float eps);"
    << endl << "bool OSGEqualEps(in vec3  a, in vec3  b, in float eps);"
    << endl << "bool OSGEqualEps(in vec4  a, in vec4  b, in float eps);"
    << endl << "bool OSGEqualEps(in mat2  a, in mat2  b, in float eps);"
    << endl << "bool OSGEqualEps(in mat3  a, in mat3  b, in float eps);"
    << endl << "bool OSGEqualEps(in mat4  a, in mat4  b, in float eps);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getEqualEpsSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "bool OSGEqualEps(in float a, in float b, in float eps)"
    << endl << "{"
    << endl << "    if (abs(a - b) < eps)"
    << endl << "        return true;"
    << endl << "    else"
    << endl << "        return false;"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in vec2 a, in vec2 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a.x, b.x, eps) && OSGEqualEps(a.y, b.y, eps);"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in vec3 a, in vec3 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a.x, b.x, eps) && OSGEqualEps(a.y, b.y, eps) && OSGEqualEps(a.z, b.z, eps);"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in vec4 a, in vec4 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a.x, b.x, eps) && OSGEqualEps(a.y, b.y, eps) && OSGEqualEps(a.z, b.z, eps) && OSGEqualEps(a.w, b.w, eps);"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in mat2 a, in mat2 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a[0], b[0], eps) && OSGEqualEps(a[1], b[1], eps);"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in mat3 a, in mat3 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a[0], b[0], eps) && OSGEqualEps(a[1], b[1], eps) && OSGEqualEps(a[2], b[2], eps);"
    << endl << "}"
    << endl << ""
    << endl << "bool OSGEqualEps(in mat4 a, in mat4 b, in float eps)"
    << endl << "{"
    << endl << "    return OSGEqualEps(a[0], b[0], eps) && OSGEqualEps(a[1], b[1], eps) && OSGEqualEps(a[2], b[2], eps) && OSGEqualEps(a[3], b[3], eps);"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getEqualDefaultTestMatrixDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "bool OSGEqualDefaultTestMatrix(in mat4 m);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getEqualDefaultTestMatrixSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "bool OSGEqualDefaultTestMatrix(in mat4 m)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Setup some test code"
    << endl << "    //"
    << endl << "    //      The following mathematical matrix is provided. In GLSL the"
    << endl << "    //      constructor takes the elements in column major order."
    << endl << "    //"
    << endl << "    //      In OpenSG the very same matrix would be constructed with"
    << endl << "    //      the elements given in row major order."
    << endl << "    //"
    << endl << "    //              c0 c1 c2 c3"
    << endl << "    //             ( 1  2  3  4) r0"
    << endl << "    //      test = ( 5  6  7  8) r1"
    << endl << "    //             ( 9 10 11 12) r2"
    << endl << "    //             (13 14 15 16) r3"
    << endl << "    //"
    << endl << "    mat4 test = mat4(1,5,9,13,  2,6,10,14,  3,7,11,15,  4,8,12,16);"
    << endl << "    return OSGEqualEps(m, test, 1.E-3);"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getColorsDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "vec4 OSGGetHeatColor(in int idx);"
    << endl << "vec4 OSGGetHeatColor(in int idx, in int step, in int start, in int end);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getColorsSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "const vec4 OSGColorIndianRed            = vec4(0.804, 0.361, 0.361, 1.0);"
    << endl << "const vec4 OSGColorLightCoral           = vec4(0.941, 0.502, 0.502, 1.0);"
    << endl << "const vec4 OSGColorSalmon               = vec4(0.980, 0.502, 0.447, 1.0);"
    << endl << "const vec4 OSGColorDarkSalmon           = vec4(0.914, 0.588, 0.478, 1.0);"
    << endl << "const vec4 OSGColorLightSalmon          = vec4(1.000, 0.627, 0.478, 1.0);"
    << endl << "const vec4 OSGColorCrimson              = vec4(0.863, 0.078, 0.235, 1.0);"
    << endl << "const vec4 OSGColorRed                  = vec4(1.000, 0.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorFireBrick            = vec4(0.698, 0.133, 0.133, 1.0);"
    << endl << "const vec4 OSGColorDarkRed              = vec4(0.545, 0.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorPink                 = vec4(1.000, 0.753, 0.796, 1.0);"
    << endl << "const vec4 OSGColorLightPink            = vec4(1.000, 0.714, 0.757, 1.0);"
    << endl << "const vec4 OSGColorHotPink              = vec4(1.000, 0.412, 0.706, 1.0);"
    << endl << "const vec4 OSGColorDeepPink             = vec4(1.000, 0.078, 0.576, 1.0);"
    << endl << "const vec4 OSGColorMediumVioletRed      = vec4(0.780, 0.082, 0.522, 1.0);"
    << endl << "const vec4 OSGColorPaleVioletRed        = vec4(0.859, 0.439, 0.576, 1.0);"
    << endl << "const vec4 OSGColorCoral                = vec4(1.000, 0.498, 0.314, 1.0);"
    << endl << "const vec4 OSGColorTomato               = vec4(1.000, 0.388, 0.278, 1.0);"
    << endl << "const vec4 OSGColorOrangeRed            = vec4(1.000, 0.271, 0.000, 1.0);"
    << endl << "const vec4 OSGColorDarkOrange           = vec4(1.000, 0.549, 0.000, 1.0);"
    << endl << "const vec4 OSGColorOrange               = vec4(1.000, 0.647, 0.000, 1.0);"
    << endl << "const vec4 OSGColorGold                 = vec4(1.000, 0.843, 0.000, 1.0);"
    << endl << "const vec4 OSGColorYellow               = vec4(1.000, 1.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorLightYellow          = vec4(1.000, 1.000, 0.878, 1.0);"
    << endl << "const vec4 OSGColorLemonChion           = vec4(1.000, 0.980, 0.804, 1.0);"
    << endl << "const vec4 OSGColorLightGoldenrodYellow = vec4(0.980, 0.980, 0.824, 1.0);"
    << endl << "const vec4 OSGColorPapayaWhip           = vec4(1.000, 0.937, 0.835, 1.0);"
    << endl << "const vec4 OSGColorMoccasin             = vec4(1.000, 0.894, 0.710, 1.0);"
    << endl << "const vec4 OSGColorPeachPu              = vec4(1.000, 0.855, 0.725, 1.0);"
    << endl << "const vec4 OSGColorPaleGoldenrod        = vec4(0.933, 0.910, 0.667, 1.0);"
    << endl << "const vec4 OSGColorKhaki                = vec4(0.941, 0.902, 0.549, 1.0);"
    << endl << "const vec4 OSGColorDarkKhaki            = vec4(0.741, 0.718, 0.420, 1.0);"
    << endl << "const vec4 OSGColorLavender             = vec4(0.902, 0.902, 0.980, 1.0);"
    << endl << "const vec4 OSGColorThistle              = vec4(0.847, 0.749, 0.847, 1.0);"
    << endl << "const vec4 OSGColorPlum                 = vec4(0.867, 0.627, 0.867, 1.0);"
    << endl << "const vec4 OSGColorViolet               = vec4(0.933, 0.510, 0.933, 1.0);"
    << endl << "const vec4 OSGColorOrchid               = vec4(0.855, 0.439, 0.839, 1.0);"
    << endl << "const vec4 OSGColorFuchsia              = vec4(1.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorMagenta              = vec4(1.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorMediumOrchid         = vec4(0.729, 0.333, 0.827, 1.0);"
    << endl << "const vec4 OSGColorMediumPurple         = vec4(0.576, 0.439, 0.859, 1.0);"
    << endl << "const vec4 OSGColorBlueViolet           = vec4(0.541, 0.169, 0.886, 1.0);"
    << endl << "const vec4 OSGColorDarkViolet           = vec4(0.580, 0.000, 0.827, 1.0);"
    << endl << "const vec4 OSGColorDarkOrchid           = vec4(0.600, 0.196, 0.800, 1.0);"
    << endl << "const vec4 OSGColorDarkMagenta          = vec4(0.545, 0.000, 0.545, 1.0);"
    << endl << "const vec4 OSGColorPurple               = vec4(0.502, 0.000, 0.502, 1.0);"
    << endl << "const vec4 OSGColorIndigo               = vec4(0.294, 0.000, 0.510, 1.0);"
    << endl << "const vec4 OSGColorSlateBlue            = vec4(0.416, 0.353, 0.804, 1.0);"
    << endl << "const vec4 OSGColorDarkSlateBlue        = vec4(0.282, 0.239, 0.545, 1.0);"
    << endl << "const vec4 OSGColorGreenYellow          = vec4(0.678, 1.000, 0.184, 1.0);"
    << endl << "const vec4 OSGColorChartreuse           = vec4(0.498, 1.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorLawnGreen            = vec4(0.486, 0.988, 0.000, 1.0);"
    << endl << "const vec4 OSGColorLime                 = vec4(0.000, 1.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorLimeGreen            = vec4(0.196, 0.804, 0.196, 1.0);"
    << endl << "const vec4 OSGColorPaleGreen            = vec4(0.596, 0.984, 0.596, 1.0);"
    << endl << "const vec4 OSGColorLightGreen           = vec4(0.565, 0.933, 0.565, 1.0);"
    << endl << "const vec4 OSGColorMediumSpringGreen    = vec4(0.000, 0.980, 0.604, 1.0);"
    << endl << "const vec4 OSGColorSpringGreen          = vec4(0.000, 1.000, 0.498, 1.0);"
    << endl << "const vec4 OSGColorMediumSeaGreen       = vec4(0.235, 0.702, 0.443, 1.0);"
    << endl << "const vec4 OSGColorSeaGreen             = vec4(0.180, 0.545, 0.341, 1.0);"
    << endl << "const vec4 OSGColorForestGreen          = vec4(0.133, 0.545, 0.133, 1.0);"
    << endl << "const vec4 OSGColorGreen                = vec4(0.000, 0.502, 0.000, 1.0);"
    << endl << "const vec4 OSGColorDarkGreen            = vec4(0.000, 0.392, 0.000, 1.0);"
    << endl << "const vec4 OSGColorYellowGreen          = vec4(0.604, 0.804, 0.196, 1.0);"
    << endl << "const vec4 OSGColorOliveDrab            = vec4(0.420, 0.557, 0.137, 1.0);"
    << endl << "const vec4 OSGColorOlive                = vec4(0.502, 0.502, 0.000, 1.0);"
    << endl << "const vec4 OSGColorDarkOliveGreen       = vec4(0.333, 0.420, 0.184, 1.0);"
    << endl << "const vec4 OSGColorMediumAquamarine     = vec4(0.400, 0.804, 0.667, 1.0);"
    << endl << "const vec4 OSGColorDarkSeaGreen         = vec4(0.561, 0.737, 0.561, 1.0);"
    << endl << "const vec4 OSGColorLightSeaGreen        = vec4(0.125, 0.698, 0.667, 1.0);"
    << endl << "const vec4 OSGColorDarkCyan             = vec4(0.000, 0.545, 0.545, 1.0);"
    << endl << "const vec4 OSGColorTeal                 = vec4(0.000, 0.502, 0.502, 1.0);"
    << endl << "const vec4 OSGColorAqua                 = vec4(0.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorCyan                 = vec4(0.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorLightCyan            = vec4(0.878, 1.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorPaleTurquoise        = vec4(0.686, 0.933, 0.933, 1.0);"
    << endl << "const vec4 OSGColorAquamarine           = vec4(0.498, 1.000, 0.831, 1.0);"
    << endl << "const vec4 OSGColorTurquoise            = vec4(0.251, 0.878, 0.816, 1.0);"
    << endl << "const vec4 OSGColorMediumTurquoise      = vec4(0.282, 0.820, 0.800, 1.0);"
    << endl << "const vec4 OSGColorDarkTurquoise        = vec4(0.000, 0.808, 0.820, 1.0);"
    << endl << "const vec4 OSGColorCadetBlue            = vec4(0.373, 0.620, 0.627, 1.0);"
    << endl << "const vec4 OSGColorSteelBlue            = vec4(0.275, 0.510, 0.706, 1.0);"
    << endl << "const vec4 OSGColorLightSteelBlue       = vec4(0.690, 0.769, 0.871, 1.0);"
    << endl << "const vec4 OSGColorPowderBlue           = vec4(0.690, 0.878, 0.902, 1.0);"
    << endl << "const vec4 OSGColorLightBlue            = vec4(0.678, 0.847, 0.902, 1.0);"
    << endl << "const vec4 OSGColorSkyBlue              = vec4(0.529, 0.808, 0.922, 1.0);"
    << endl << "const vec4 OSGColorLightSkyBlue         = vec4(0.529, 0.808, 0.980, 1.0);"
    << endl << "const vec4 OSGColorDeepSkyBlue          = vec4(0.000, 0.749, 1.000, 1.0);"
    << endl << "const vec4 OSGColorDodgerBlue           = vec4(0.118, 0.565, 1.000, 1.0);"
    << endl << "const vec4 OSGColorCornlowerBlue        = vec4(0.392, 0.584, 0.929, 1.0);"
    << endl << "const vec4 OSGColorMediumSlateBlue      = vec4(0.482, 0.408, 0.933, 1.0);"
    << endl << "const vec4 OSGColorRoyalBlue            = vec4(0.255, 0.412, 0.882, 1.0);"
    << endl << "const vec4 OSGColorBlue                 = vec4(0.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorMediumBlue           = vec4(0.000, 0.000, 0.804, 1.0);"
    << endl << "const vec4 OSGColorDarkBlue             = vec4(0.000, 0.000, 0.545, 1.0);"
    << endl << "const vec4 OSGColorNavy                 = vec4(0.000, 0.000, 0.502, 1.0);"
    << endl << "const vec4 OSGColorMidnightBlue         = vec4(0.098, 0.098, 0.439, 1.0);"
    << endl << "const vec4 OSGColorCornsilk             = vec4(1.000, 0.973, 0.863, 1.0);"
    << endl << "const vec4 OSGColorBlanchedAlmond       = vec4(1.000, 0.922, 0.804, 1.0);"
    << endl << "const vec4 OSGColorBisque               = vec4(1.000, 0.894, 0.769, 1.0);"
    << endl << "const vec4 OSGColorNavajoWhite          = vec4(1.000, 0.871, 0.678, 1.0);"
    << endl << "const vec4 OSGColorWheat                = vec4(0.961, 0.871, 0.702, 1.0);"
    << endl << "const vec4 OSGColorBurlyWood            = vec4(0.871, 0.722, 0.529, 1.0);"
    << endl << "const vec4 OSGColorTan                  = vec4(0.824, 0.706, 0.549, 1.0);"
    << endl << "const vec4 OSGColorRosyBrown            = vec4(0.737, 0.561, 0.561, 1.0);"
    << endl << "const vec4 OSGColorSandyBrown           = vec4(0.957, 0.643, 0.376, 1.0);"
    << endl << "const vec4 OSGColorGoldenrod            = vec4(0.855, 0.647, 0.125, 1.0);"
    << endl << "const vec4 OSGColorDarkGoldenrod        = vec4(0.722, 0.525, 0.043, 1.0);"
    << endl << "const vec4 OSGColorPeru                 = vec4(0.804, 0.522, 0.247, 1.0);"
    << endl << "const vec4 OSGColorChocolate            = vec4(0.824, 0.412, 0.118, 1.0);"
    << endl << "const vec4 OSGColorSaddleBrown          = vec4(0.545, 0.271, 0.075, 1.0);"
    << endl << "const vec4 OSGColorSienna               = vec4(0.627, 0.322, 0.176, 1.0);"
    << endl << "const vec4 OSGColorBrown                = vec4(0.647, 0.165, 0.165, 1.0);"
    << endl << "const vec4 OSGColorMaroon               = vec4(0.502, 0.000, 0.000, 1.0);"
    << endl << "const vec4 OSGColorWhite                = vec4(1.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorSnow                 = vec4(1.000, 0.980, 0.980, 1.0);"
    << endl << "const vec4 OSGColorHoneydew             = vec4(0.941, 1.000, 0.941, 1.0);"
    << endl << "const vec4 OSGColorMintCream            = vec4(0.961, 1.000, 0.980, 1.0);"
    << endl << "const vec4 OSGColorAzure                = vec4(0.941, 1.000, 1.000, 1.0);"
    << endl << "const vec4 OSGColorAliceBlue            = vec4(0.941, 0.973, 1.000, 1.0);"
    << endl << "const vec4 OSGColorGhostWhite           = vec4(0.973, 0.973, 1.000, 1.0);"
    << endl << "const vec4 OSGColorWhiteSmoke           = vec4(0.961, 0.961, 0.961, 1.0);"
    << endl << "const vec4 OSGColorSeashell             = vec4(1.000, 0.961, 0.933, 1.0);"
    << endl << "const vec4 OSGColorBeige                = vec4(0.961, 0.961, 0.863, 1.0);"
    << endl << "const vec4 OSGColorOldLace              = vec4(0.992, 0.961, 0.902, 1.0);"
    << endl << "const vec4 OSGColorFloralWhite          = vec4(1.000, 0.980, 0.941, 1.0);"
    << endl << "const vec4 OSGColorIvory                = vec4(1.000, 1.000, 0.941, 1.0);"
    << endl << "const vec4 OSGColorAntiqueWhite         = vec4(0.980, 0.922, 0.843, 1.0);"
    << endl << "const vec4 OSGColorLinen                = vec4(0.980, 0.941, 0.902, 1.0);"
    << endl << "const vec4 OSGColorLavenderBlush        = vec4(1.000, 0.941, 0.961, 1.0);"
    << endl << "const vec4 OSGColorMistyRose            = vec4(1.000, 0.894, 0.882, 1.0);"
    << endl << "const vec4 OSGColorGainsboro            = vec4(0.863, 0.863, 0.863, 1.0);"
    << endl << "const vec4 OSGColorLightGrey            = vec4(0.827, 0.827, 0.827, 1.0);"
    << endl << "const vec4 OSGColorSilver               = vec4(0.753, 0.753, 0.753, 1.0);"
    << endl << "const vec4 OSGColorDarkGray             = vec4(0.663, 0.663, 0.663, 1.0);"
    << endl << "const vec4 OSGColorGray                 = vec4(0.502, 0.502, 0.502, 1.0);"
    << endl << "const vec4 OSGColorDimGray              = vec4(0.412, 0.412, 0.412, 1.0);"
    << endl << "const vec4 OSGColorLightSlateGray       = vec4(0.467, 0.533, 0.600, 1.0);"
    << endl << "const vec4 OSGColorSlateGray            = vec4(0.439, 0.502, 0.565, 1.0);"
    << endl << "const vec4 OSGColorDarkSlateGray        = vec4(0.184, 0.310, 0.310, 1.0);"
    << endl << "const vec4 OSGColorBlack                = vec4(0.000, 0.000, 0.000, 1.0);"
    << endl << ""
    << endl << "const vec4 OSGGHeatMapColors[] = vec4[]"
    << endl << "("
    << endl << "    OSGColorBlack,          OSGColorDarkSlateGray,  OSGColorNavy,           OSGColorBlue,           OSGColorRoyalBlue,      OSGColorDodgerBlue,     OSGColorDeepSkyBlue,    OSGColorTurquoise,"
    << endl << "    OSGColorAquamarine,     OSGColorCyan,           OSGColorDarkGreen,      OSGColorGreen,          OSGColorSpringGreen,    OSGColorLime,           OSGColorChartreuse,     OSGColorGreenYellow,"
    << endl << "    OSGColorYellow,         OSGColorGold,           OSGColorDarkOrange,     OSGColorOrangeRed,      OSGColorRed,            OSGColorFireBrick,      OSGColorDarkRed,        OSGColorBlueViolet,"
    << endl << "    OSGColorFuchsia,        OSGColorDeepPink,       OSGColorHotPink,        OSGColorPink,           OSGColorMistyRose,      OSGColorLavenderBlush,  OSGColorSeashell,       OSGColorWhite"
    << endl << ");"
    << endl << ""
    << endl << "vec4 OSGGetHeatColor(in int idx)"
    << endl << "{"
    << endl << "    return OSGGHeatMapColors[idx];"
    << endl << "}"
    << endl << ""
    << endl << "vec4 OSGGetHeatColor(in int idx, in int step, in int start, in int end)"
    << endl << "{"
    << endl << "    int  sz     = OSGGHeatMapColors.length();"
    << endl << "    int new_sz  = clamp(end-start+1, 0, sz);"
    << endl << "    int new_idx = int(mod(idx*step, new_sz)) + start;"
    << endl << "    return OSGGHeatMapColors[new_idx];"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getCubemapDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "int  OSGGetCubeMapIndexOffset(in vec3 s);"
    << endl << "vec3 OSGConvertCubeUV2XYZ(in int idx, in vec2 uv);"
    << endl << "vec2 OSGConvertXYZ2CubeUV(in vec3 s, out int idx);"
    << endl << "void OSGGetCubeMapLocalFrame(in vec3 s, out vec3 e1, out vec3 e2);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getCubemapSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "const int OSG_POSITIVE_X = 0;"
    << endl << "const int OSG_NEGATIVE_X = 1;"
    << endl << "const int OSG_POSITIVE_Y = 2;"
    << endl << "const int OSG_NEGATIVE_Y = 3;"
    << endl << "const int OSG_POSITIVE_Z = 4;"
    << endl << "const int OSG_NEGATIVE_Z = 5;"
    << endl << ""
    << endl << "const mat4 OSGMatCubeFaceInv[6] = mat4[]"
    << endl << "("
    << endl << "    // OSG_POSITIVE_X"
    << endl << "    mat4( 0.0,  0.0, -1.0,  0.0,"
    << endl << "          0.0, -1.0,  0.0,  0.0,"
    << endl << "         -1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0),"
    << endl << ""
    << endl << "    // OSG_NEGATIVE_X"
    << endl << "    mat4( 0.0,  0.0,  1.0,  0.0,"
    << endl << "          0.0, -1.0,  0.0,  0.0,"
    << endl << "          1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0),"
    << endl << ""
    << endl << "    // OSG_POSITIVE_Y"
    << endl << "    mat4( 1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  1.0,  0.0,"
    << endl << "          0.0, -1.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0),"
    << endl << ""
    << endl << "    // OSG_NEGATIVE_Y"
    << endl << "    mat4( 1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0, -1.0,  0.0,"
    << endl << "          0.0,  1.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0),"
    << endl << ""
    << endl << "    // OSG_POSITIVE_Z"
    << endl << "    mat4( 1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0, -1.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0, -1.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0),"
    << endl << ""
    << endl << "    // OSG_NEGATIVE_Z"
    << endl << "    mat4(-1.0,  0.0,  0.0,  0.0,"
    << endl << "          0.0, -1.0,  0.0,  0.0,"
    << endl << "          0.0,  0.0,  1.0,  0.0,"
    << endl << "          0.0,  0.0,  0.0,  1.0)"
    << endl << ");"
    << endl << ""
    << endl << "int OSGGetCubeMapIndexOffset(in vec3 s)"
    << endl << "{"
    << endl << "    float absX = abs(s.x);"
    << endl << "    float absY = abs(s.y);"
    << endl << "    float absZ = abs(s.z);"
    << endl << ""
    << endl << "    bool isXPositive = s.x > 0 ? true : false;"
    << endl << "    bool isYPositive = s.y > 0 ? true : false;"
    << endl << "    bool isZPositive = s.z > 0 ? true : false;"
    << endl << ""
    << endl << "    if ( isXPositive && absX >= absY && absX >= absZ) return OSG_POSITIVE_X;"
    << endl << "    if (!isXPositive && absX >= absY && absX >= absZ) return OSG_NEGATIVE_X;"
    << endl << "    if ( isYPositive && absY >= absX && absY >= absZ) return OSG_POSITIVE_Y;"
    << endl << "    if (!isYPositive && absY >= absX && absY >= absZ) return OSG_NEGATIVE_Y;"
    << endl << "    if ( isZPositive && absZ >= absX && absZ >= absY) return OSG_POSITIVE_Z;"
    << endl << "    if (!isZPositive && absZ >= absX && absZ >= absY) return OSG_NEGATIVE_Z;"
    << endl << ""
    << endl << "    return 0;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGConvertCubeUV2XYZ(in int idx, in vec2 uv)"
    << endl << "{"
    << endl << "    float uc = 2.0 * uv.x - 1.0;"
    << endl << "    float vc = 2.0 * uv.y - 1.0;"
    << endl << ""
    << endl << "    vec3 xyz;"
    << endl << "    if (idx == OSG_POSITIVE_X) return vec3( 1.0,  vc, -uc);"
    << endl << "    if (idx == OSG_NEGATIVE_X) return vec3(-1.0,  vc,  uc);"
    << endl << "    if (idx == OSG_POSITIVE_Y) return vec3(  uc, 1.0, -vc);"
    << endl << "    if (idx == OSG_NEGATIVE_Y) return vec3(  uc,-1.0,  vc);"
    << endl << "    if (idx == OSG_POSITIVE_Z) return vec3(  uc,  vc, 1.0);"
    << endl << "    if (idx == OSG_NEGATIVE_Z) return vec3( -uc,  vc,-1.0);"
    << endl << ""
    << endl << "    return vec3(0);"
    << endl << "}"
    << endl << ""
    << endl << "vec2 OSGConvertXYZ2CubeUV(in vec3 s, out int idx)"
    << endl << "{"
    << endl << "    float absX = abs(s.x);"
    << endl << "    float absY = abs(s.y);"
    << endl << "    float absZ = abs(s.z);"
    << endl << ""
    << endl << "    bool isXPositive = s.x > 0 ? true : false;"
    << endl << "    bool isYPositive = s.y > 0 ? true : false;"
    << endl << "    bool isZPositive = s.z > 0 ? true : false;"
    << endl << ""
    << endl << "    float maxAxis, uc, vc;"
    << endl << ""
    << endl << "    if ( isXPositive && absX >= absY && absX >= absZ)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from +z to -z"
    << endl << "        // v (0 to 1) goes from -y to +y"
    << endl << "        maxAxis = absX;"
    << endl << "        uc = -s.z;"
    << endl << "        vc =  s.y;"
    << endl << "        idx = OSG_POSITIVE_X;"
    << endl << "    }"
    << endl << ""
    << endl << "    if (!isXPositive && absX >= absY && absX >= absZ)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from -z to +z"
    << endl << "        // v (0 to 1) goes from -y to +y"
    << endl << "        maxAxis = absX;"
    << endl << "        uc = s.z;"
    << endl << "        vc = s.y;"
    << endl << "        idx = OSG_NEGATIVE_X;"
    << endl << "    }"
    << endl << ""
    << endl << "    if ( isYPositive && absY >= absX && absY >= absZ)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from -x to +x"
    << endl << "        // v (0 to 1) goes from +z to -z"
    << endl << "        maxAxis = absY;"
    << endl << "        uc =  s.x;"
    << endl << "        vc = -s.z;"
    << endl << "        idx = OSG_POSITIVE_Y;"
    << endl << "    }"
    << endl << ""
    << endl << "    if (!isYPositive && absY >= absX && absY >= absZ)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from -x to +x"
    << endl << "        // v (0 to 1) goes from -z to +z"
    << endl << "        maxAxis = absY;"
    << endl << "        uc = s.x;"
    << endl << "        vc = s.z;"
    << endl << "        idx = OSG_NEGATIVE_Y;"
    << endl << "    }"
    << endl << ""
    << endl << "    if ( isZPositive && absZ >= absX && absZ >= absY)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from -x to +x"
    << endl << "        // v (0 to 1) goes from -y to +y"
    << endl << "        maxAxis = absZ;"
    << endl << "        uc = s.x;"
    << endl << "        vc = s.y;"
    << endl << "        idx = OSG_POSITIVE_Z;"
    << endl << "    }"
    << endl << ""
    << endl << "    if (!isZPositive && absZ >= absX && absZ >= absY)"
    << endl << "    {"
    << endl << "        // u (0 to 1) goes from +x to -x"
    << endl << "        // v (0 to 1) goes from -y to +y"
    << endl << "        maxAxis = absZ;"
    << endl << "        uc = -s.x;"
    << endl << "        vc =  s.y;"
    << endl << "        idx = OSG_NEGATIVE_Z;"
    << endl << "    }"
    << endl << ""
    << endl << "    // Convert range from -1 to 1 to 0 to 1"
    << endl << "    vec2 uv = vec2(0.5 * (uc / maxAxis + 1.0),"
    << endl << "                   0.5 * (vc / maxAxis + 1.0));"
    << endl << ""
    << endl << "    return uv;"
    << endl << "}"
    << endl << ""
    << endl << "void OSGGetCubeMapLocalFrame(in vec3 s, out vec3 e1, out vec3 e2)"
    << endl << "{"
    << endl << "    float absX = abs(s.x);"
    << endl << "    float absY = abs(s.y);"
    << endl << "    float absZ = abs(s.z);"
    << endl << ""
    << endl << "    bool isXPositive = s.x > 0 ? true : false;"
    << endl << "    bool isYPositive = s.y > 0 ? true : false;"
    << endl << "    bool isZPositive = s.z > 0 ? true : false;"
    << endl << ""
    << endl << "    if ( isXPositive && absX >= absY && absX >= absZ) // OSG_POSITIVE_X"
    << endl << "    {"
    << endl << "        e1 = vec3( 0, 0,-1); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if (!isXPositive && absX >= absY && absX >= absZ) // OSG_NEGATIVE_X"
    << endl << "    {"
    << endl << "        e1 = vec3( 0, 0, 1); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if ( isYPositive && absY >= absX && absY >= absZ) // OSG_POSITIVE_Y"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 0,-1);"
    << endl << "    }"
    << endl << "    if (!isYPositive && absY >= absX && absY >= absZ) // OSG_NEGATIVE_Y"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 0, 1);"
    << endl << "    }"
    << endl << "    if ( isZPositive && absZ >= absX && absZ >= absY) // OSG_POSITIVE_Z"
    << endl << "    {"
    << endl << "        e1 = vec3( 1, 0, 0); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "    if (!isZPositive && absZ >= absX && absZ >= absY) // OSG_NEGATIVE_Z"
    << endl << "    {"
    << endl << "        e1 = vec3(-1, 0, 0); e2 = vec3( 0, 1, 0);"
    << endl << "    }"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getLocalFrameDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "vec3 OSGGetOrthogonal(in vec3 v);"
    << endl << "void OSGCalcLocalFrame(in vec3 a, out vec3 u, out vec3 v);"
    << endl << "mat3 OSGGetCoTangentFrame(in vec3 T, in vec3 B, in vec3 N)"
    << endl << "mat3 OSGGetCoTangentFrame(in vec3 N, in vec3 p, in vec2 uv)"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getLocalFrameSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// Always works if the input is non-zero."
    << endl << "// Doesn’t require the input to be normalised."
    << endl << "// Doesn’t normalise the output."
    << endl << "// http://lolengine.net/blog/2013/09/21/picking-orthogonal-vector-combing-coconuts"
    << endl << "//"
    << endl << "vec3 OSGGetOrthogonal(in vec3 v)"
    << endl << "{"
    << endl << "    return abs(v.x) > abs(v.z) ? vec3(-v.y, v.x, 0.0) : vec3(0.0, -v.z, v.y);"
    << endl << "}"
    << endl << ""
    << endl << "void OSGCalcLocalFrame("
    << endl << "    in  vec3 a, // expected to be normalized"
    << endl << "    out vec3 u, // normalized"
    << endl << "    out vec3 v) // dito"
    << endl << "{"
    << endl << "    u = normalize(OSGGetOrthogonal(a));"
    << endl << "    v = cross(a, u);"
    << endl << "}"
    << endl << ""
    << endl << "mat3 OSGGetCoTangentFrame(in vec3 T, in vec3 B, in vec3 N)"
    << endl << "{"
    << endl << "    // TBN must form a right handed coord system."
    << endl << "    // Some models have symmetric UVs. Check and fix."
    << endl << "    if (dot(cross(N, T), B) < 0.0)"
    << endl << "        T = T * -1.0;"
    << endl << ""
    << endl << "    return mat3(T, B, N);"
    << endl << "}"
    << endl << ""
    << endl << "mat3 OSGGetCoTangentFrame(in vec3 N, in vec3 p, in vec2 uv)"
    << endl << "{"
    << endl << "    // get edge vectors of the pixel triangle"
    << endl << "    vec3 dp1  = dFdx(p);"
    << endl << "    vec3 dp2  = dFdy(p);"
    << endl << "    vec2 duv1 = dFdx(uv);"
    << endl << "    vec2 duv2 = dFdy(uv);"
    << endl << ""
    << endl << "    // solve the linear system"
    << endl << "    vec3 dp2perp = cross(dp2, N);"
    << endl << "    vec3 dp1perp = cross(N, dp1);"
    << endl << ""
    << endl << "    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;"
    << endl << "    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;"
    << endl << ""
    << endl << "    // construct a scale-invariant frame"
    << endl << "    float invmax = inversesqrt(max(dot(T,T), dot(B,B)));"
    << endl << "    return mat3(T *invmax, B * invmax, N);"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getUtilityFunctionsDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "float smoothestepplus(in float edge0, in float edge1, in float x);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getUtilityFunctionsSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "float smoothestepplus(in float edge0, in float edge1, in float x)"
    << endl << "{"
    << endl << "    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);"
    << endl << "    return t*t*t*(t*(t * 6 - 15) + 10);"
    << endl << "}"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getSRGBConversionDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "float OSGSRGBToLinear(in float v);"
    << endl << "vec3  OSGSRGBToLinear(in vec3  v);"
    << endl << "vec4  OSGSRGBToLinear(in vec4  v);"
    << endl << "float OSGLinearToSRGB(in float v);"
    << endl << "vec3  OSGLinearToSRGB(in vec3  v);"
    << endl << "vec4  OSGLinearToSRGB(in vec4  v);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getSRGBConversionSnippet(bool sRGBApprox)
{
    using namespace std;

    stringstream ost;

    if (sRGBApprox)
    {
        ost     << "float OSGSRGBToLinear(in float v)"
        << endl << "{"
        << endl << "    return pow(v, 2.2);"
        << endl << "}"
        << endl << ""
        << endl << "vec3 OSGSRGBToLinear(in vec3 v)"
        << endl << "{"
        << endl << "    return pow(v, vec3(2.2));"
        << endl << "}"
        << endl << ""
        << endl << "vec4 OSGSRGBToLinear(in vec4 v)"
        << endl << "{"
        << endl << "    return vec4(OSGSRGBToLinear(v.rgb), v.a);"
        << endl << "}"
        << endl << ""
        << endl << "float OSGLinearToSRGB(in float v)"
        << endl << "{"
        << endl << "    return pow(v, 1.0/2.2);"
        << endl << "}"
        << endl << ""
        << endl << "vec3 OSGLinearToSRGB(in vec3 v)"
        << endl << "{"
        << endl << "    return pow(v, vec3(1.0/2.2));"
        << endl << "}"
        << endl << ""
        << endl << "vec4 OSGLinearToSRGB(in vec4 v)"
        << endl << "{"
        << endl << "    return vec4(OSGLinearToSRGB(v.rgb), v.a);"
        << endl << "}"
        ;
    }
    else
    {
        ost     << "float OSGSRGBToLinear(in float v)"
        << endl << "{"
        << endl << "    float t = step(0.04045, v);"
        << endl << "    return mix(v / 12.92, pow((v + 0.055)/1.055, 2.4), t);"
        << endl << "}"
        << endl << ""
        << endl << "vec3 OSGSRGBToLinear(in vec3 v)"
        << endl << "{"
        << endl << "    vec3 t = step(vec3(0.04045), v.rgb);"
        << endl << "    return mix(v.rgb / 12.92, pow((v.rgb + vec3(0.055))/1.055, vec3(2.4)), t);"
        << endl << "}"
        << endl << ""
        << endl << "vec4 OSGSRGBToLinear(in vec4 v)"
        << endl << "{"
        << endl << "    return vec4(OSGSRGBToLinear(v.rgb), v.a);"
        << endl << "}"
        << endl << ""
        << endl << "float OSGLinearToSRGB(in float v)"
        << endl << "{"
        << endl << "    float t = step(0.00313067, v);"
        << endl << "    return mix(v * 12.92, 1.055 * pow(v, 1.0/2.4) - 0.055, t);"
        << endl << "}"
        << endl << ""
        << endl << "vec3 OSGLinearToSRGB(in vec3 v)"
        << endl << "{"
        << endl << "    vec3 t = step(vec3(0.00313067), v.rgb);"
        << endl << "    return mix(v.rgb * 12.92, 1.055 * pow(v.rgb, vec3(1.0/2.4)) - 0.055, t);"
        << endl << "}"
        << endl << ""
        << endl << "vec4 OSGLinearToSRGB(in vec4 v)"
        << endl << "{"
        << endl << "    return vec4(OSGLinearToSRGB(v.rgb), v.a);"
        << endl << "}"
        ;
    }

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getColorConversionDeclSnippet()
{
    using namespace std;

    stringstream ost;

    ost     << "vec3 OSGGetXYZFromNTSC_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetNTSC_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromCIE_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetCIE_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromWideGamut_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetWideGamut_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromSMPTE_C_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetSMPTE_C_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromPAL_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetPAL_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromECI_RGB(in vec3 rgb);"
    << endl << "vec3 OSGGetECI_RGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromBest_RGB(in vec3 rgb)"
    << endl << "vec3 OSGGetBest_RGBFromXYZ(in vec3 xyz)"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromSRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetSRGBFromXYZ(in vec3 xyz);"
    << endl << ""
    << endl << "vec3 OSGGetYUV_BT601FromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromYUV_BT601(in vec3 yuv);"
    << endl << ""
    << endl << "vec3 OSGGetYUV_BT709FromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromYUV_BT709(in vec3 yuv);"
    << endl << ""
    << endl << "vec3 OSGGetYUVFromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromYUV(in vec3 yuv);"
    << endl << ""
    << endl << "vec3 OSGGetYPbPrFromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromYPbPr(in vec3 ypbpr);"
    << endl << ""
    << endl << "vec3 OSGGetYxyFromXYZ(in vec3 xyz);"
    << endl << "vec3 OSGGetXYZFromYxy(in vec3 Yxy);"
    << endl << ""
    << endl << "float OSGCalcAvgLuminance(in vec3 color);"
    << endl << ""
    << endl << getSRGBConversionDeclSnippet()
    << endl << ""
    << endl << "vec3 OSGGetRGBFromHUE(in float hue);"
    << endl << "vec3 OSGGetHCVFromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetHSVFromRGB(in vec3 rgb);"
    << endl << "vec3 OSGGetRGBFromHSV(in vec3 hsv);"
    ;

    return ost.str();
}

OSG_SYSTEM_DLLMAPPING std::string getColorConversionSnippet(bool sRGBApprox)
{
    using namespace std;

    stringstream ost;

    ost     << "//"
    << endl << "// See http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html"
    << endl << "//"
    << endl << "vec3 OSGGetXYZFromNTSC_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.6068909, 0.1735011, 0.2003480,"
    << endl << "         0.2989164, 0.5865990, 0.1144845,"
    << endl << "         0.0000000, 0.0660957, 1.1162243);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetNTSC_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         1.9099961,-0.5324542,-0.2882091,"
    << endl << "        -0.9846663, 1.9991710,-0.0283082,"
    << endl << "         0.0583056,-0.1183781, 0.8975535);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromCIE_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.4887180, 0.3106803, 0.2006017,"
    << endl << "         0.1762044, 0.8129847, 0.0108109,"
    << endl << "         0.0000000, 0.0102048, 0.9897952);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetCIE_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         2.3706743,-0.9000405,-0.4706338,"
    << endl << "        -0.5138850, 1.4253036, 0.0885814,"
    << endl << "         0.0052982,-0.0146949, 1.0093968);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromWideGamut_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.7161046, 0.1009296, 0.1471858,"
    << endl << "         0.2581874, 0.7249378, 0.0168748,"
    << endl << "         0.0000000, 0.0517813, 0.7734287);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetWideGamut_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         1.4628067,-0.1840623,-0.2743606,"
    << endl << "        -0.5217933, 1.4472381, 0.0677227,"
    << endl << "         0.0349342,-0.0968930, 1.2884099);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromSMPTE_C_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.3935891, 0.3652497, 0.1916313,"
    << endl << "         0.2124132, 0.7010437, 0.0865432,"
    << endl << "         0.0187423, 0.1119313, 0.9581563);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetSMPTE_C_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         3.5053960,-1.7394894,-0.5439640,"
    << endl << "        -1.0690722, 1.9778245, 0.0351722,"
    << endl << "         0.0563200,-0.1970226, 1.0502026);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromPAL_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.4306190, 0.3415419, 0.1783091,"
    << endl << "         0.2220379, 0.7066384, 0.0713236,"
    << endl << "         0.0201853, 0.1295504, 0.9390944);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetPAL_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         3.0628971,-1.3931791,-0.4757517,"
    << endl << "        -0.9692660, 1.8760108, 0.0415560,"
    << endl << "         0.0678775,-0.2288548, 1.0693490);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromECI_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.6502043, 0.1780774, 0.1359384,"
    << endl << "         0.3202499, 0.6020711, 0.0776791,"
    << endl << "         0.0000000, 0.0678390, 0.7573710);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetECI_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         1.7827618,-0.4969847,-0.2690101,"
    << endl << "        -0.9593623, 1.9477962,-0.0275807,"
    << endl << "         0.0859317,-0.1744674, 1.3228273);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromBest_RGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.6326696, 0.2045558, 0.1269946,"
    << endl << "         0.2284569, 0.7373523, 0.0341908,"
    << endl << "         0.0000000, 0.0095142, 0.8156958);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetBest_RGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         1.7552599,-0.4836786,-0.2530000,"
    << endl << "        -0.5441336, 1.5068789, 0.0215528,"
    << endl << "         0.0063467,-0.0175761, 1.2256959);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    return OSGGetXYZFromNTSC_RGB(rgb);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    return OSGGetNTSC_RGBFromXYZ(xyz);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromSRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matXYZFromRGB = mat3("
    << endl << "         0.4124564, 0.3575761, 0.1804375,"
    << endl << "         0.2126729, 0.7151522, 0.0721750,"
    << endl << "         0.0193339, 0.1191920, 0.9503041);"
    << endl << ""
    << endl << "    return matXYZFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetSRGBFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromXYZ = mat3("
    << endl << "         3.2404542,-1.5371385,-0.4985314,"
    << endl << "        -0.9692660, 1.8760108, 0.0415560,"
    << endl << "         0.0556434,-0.2040259, 1.0572252);"
    << endl << ""
    << endl << "    return matRGBFromXYZ * xyz;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetYUV_BT601FromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matYUVFromRGB = mat3("
    << endl << "         0.299, 0.587, 0.114,"
    << endl << "        -0.147,-0.289, 0.436,"
    << endl << "         0.615,-0.515,-0.100);"
    << endl << ""
    << endl << "    return matYUVFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromYUV_BT601(in vec3 yuv)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromYUV = mat3("
    << endl << "         1.000, 0.000, 1.140,"
    << endl << "         1.000,-0.395,-0.581,"
    << endl << "         1.000, 2.032, 0.000);"
    << endl << ""
    << endl << "    return matRGBFromYUV * yuv;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetYUV_BT709FromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matYUVFromRGB = mat3("
    << endl << "         0.213, 0.715, 0.072,"
    << endl << "        -0.100,-0.336, 0.436,"
    << endl << "         0.615,-0.559,-0.056);"
    << endl << ""
    << endl << "    return matYUVFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromYUV_BT709(in vec3 yuv)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromYUV = mat3("
    << endl << "         1.000, 0.000, 1.280,"
    << endl << "         1.000,-0.215,-0.381,"
    << endl << "         1.000, 2.128, 0.000);"
    << endl << ""
    << endl << "    return matRGBFromYUV * yuv;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetYUVFromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    return OSGGetYUV_BT601FromRGB(rgb);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromYUV(in vec3 yuv)"
    << endl << "{"
    << endl << "    return OSGGetRGBFromYUV_BT601(yuv);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetYPbPrFromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    const mat3 matYPbPrFromRGB = mat3("
    << endl << "         0.299,    0.587,    0.144,"
    << endl << "        -0.168936,-0.331264, 0.500,"
    << endl << "         0.500,   -0.418688,-0.081312);"
    << endl << ""
    << endl << "    return matYPbPrFromRGB * rgb;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromYPbPr(in vec3 ypbpr)"
    << endl << "{"
    << endl << "    const mat3 matRGBFromYPbPr = mat3("
    << endl << "         1.000, 0.000, 1.402,"
    << endl << "         1.000,-0.344,-0.714,"
    << endl << "         1.000, 1.772, 0.000);"
    << endl << ""
    << endl << "    return matRGBFromYPbPr * ypbpr;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetYxyFromXYZ(in vec3 xyz)"
    << endl << "{"
    << endl << "    float w = (xyz.x + xyz.y + xyz.z);"
    << endl << ""
    << endl << "    return vec3(xyz.y, xyz.x/w, xyz.g/w);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetXYZFromYxy(in vec3 Yxy)"
    << endl << "{"
    << endl << "    return vec3(Yxy.r * Yxy.g / Yxy.b,"
    << endl << "                Yxy.r,"
    << endl << "                Yxy.r * (1.0 - Yxy.g - Yxy.b) / Yxy.b);"
    << endl << "}"
    << endl << ""
    << endl << "float OSGCalcAvgLuminance(in vec3 color)"
    << endl << "{"
    << endl << "    return sqrt(dot(color * color, vec3(0.212656, 0.715158, 0.072186)));"
    << endl << "}"
    << endl << ""
    << endl << getSRGBConversionSnippet(sRGBApprox)
    << endl << ""
    << endl << "vec3 OSGGetRGBFromHUE(in float hue)"
    << endl << "{"
    << endl << "    float r =       abs(hue * 6.0 - 3.0) - 1.0;"
    << endl << "    float g = 2.0 - abs(hue * 6.0 - 2.0);"
    << endl << "    float b = 2.0 - abs(hue * 6.0 - 4.0);"
    << endl << ""
    << endl << "    return clamp(vec3(r,g,b), 0.0, 1.0);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetHCVFromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    vec4 bg = vec4(rgb.bg,-1.0, 2.0 / 3.0);"
    << endl << "    vec4 gb = vec4(rgb.gb, 0.0,-1.0 / 3.0);"
    << endl << ""
    << endl << "    vec4 p = (rgb.g < rgb.b) ? bg : gb;"
    << endl << ""
    << endl << "    vec4 xy = vec4(p.xyw, rgb.r);"
    << endl << "    vec4 yz = vec4(rgb.r, p.yzx);"
    << endl << ""
    << endl << "    vec4 q = (rgb.r < p.x) ? xy : yz;"
    << endl << ""
    << endl << "    float c = q.x - min(q.w, q.y);"
    << endl << "    float h = abs((q.w - q.y) / (6.0 * c + 1e-10) + q.z);"
    << endl << ""
    << endl << "    return vec3(h, c, q.x);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetHSVFromRGB(in vec3 rgb)"
    << endl << "{"
    << endl << "    vec3 hcv = OSGGetHCVFromRGB(rgb);"
    << endl << "    float S = hcv.y / (hcv.z + 1e-10);"
    << endl << ""
    << endl << "    return vec3(hcv.x, S, hcv.z);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 OSGGetRGBFromHSV(in vec3 hsv)"
    << endl << "{"
    << endl << "    vec3 rgb = OSGGetRGBFromHUE(hsv.x);"
    << endl << "    return ((rgb - 1.0) * hsv.y + 1.0) * hsv.z;"
    << endl << "}"
    ;

    return ost.str();
}

} // namespace Shader

OSG_END_NAMESPACE
