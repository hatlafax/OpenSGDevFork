// OpenSG Math Examples
//
// This example shows some math stuff. If glm / vmath is available 
// the example also shows how to express matters in the different
// toolkits.
//

#include <boost/random.hpp>

#ifdef OSG_WITH_QHULL
#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/RboxPoints.h>
#endif // OSG_WITH_QHULL

#ifdef OSG_WITH_GLM 
#pragma warning(push)
#pragma warning(disable : 4305)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/random.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/compatibility.hpp>
#pragma warning(pop)
#endif // OSG_WITH_GLM

#ifdef OSG_WITH_VMATH
#include <VectorMathTypes.h>

#include <Line.h>
#include <Plane.h>
#include <BoundingBox.h>
#include <Frustum.h>
#include <Polygon3d.h>
#include <PolygonBody.h>
#include <View.h>
#include <Projection.h>
#include <LiSP.h>
#include <vmath_impl.h>
#endif // OSG_WITH_VMATH

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGBaseInterpolators.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGMathUtils.h>
#include <OSGPlane.h>
#include <OSGBoxVolume.h>
#include <OSGFrustumVolume.h>
#include <OSGPolygon.h>
#include <OSGPolygonBody.h>
#include <OSGLiSPSMTechnique.h>
#include <OSGPerspectiveProjection.h>
#include <OSGOrthographicProjection.h>
#include <OSGView.h>

#include <OSGPoissonDiskGenerator.h>
#include <OSGPoissonDistribution.h>

#include <OSGSha1.h>
#include <OSGBaseHash.h>

typedef boost::mt19937 RNGType;
RNGType rng(time(0));

int myRandom(int i)
{
    return rng()%i;
}

void glm_math_library()
{
#ifdef OSG_WITH_GLM
    //
    //      glm: glm::
    //
    //           vec2,  vec3,  vec4
    //          dvec2, dvec3, dvec4
    //          ivec2, ivec3, ivec4
    //          uvec2, uvec3, uvec4
    //          bvec2, bvec3, bvec4
    //           mat2,  mat3,  mat4,  mat2x2,  mat2x3,  mat2x4,  mat3x2,  mat3x3,  mat3x4,  mat4x2,  mat4x3,  mat4x4
    //          dmat2, dmat3, dmat4, dmat2x2, dmat2x3, dmat2x4, dmat3x2, dmat3x3, dmat3x4, dmat4x2, dmat4x3, dmat4x4

    float epsilon                    = glm::epsilon<float>();
    float zero                       = glm::zero<float>();
    float one                        = glm::one<float>();
    float pi                         = glm::pi<float>();
    float two_pi                     = glm::two_pi<float>();
    float half_pi                    = glm::half_pi<float>();
    float root_pi                    = glm::root_pi<float>();
    float three_over_two_pi          = glm::three_over_two_pi<float>();
    float quarter_pi                 = glm::quarter_pi<float>();
    float one_over_pi                = glm::one_over_pi<float>();
    float one_over_two_pi            = glm::one_over_two_pi<float>();
    float two_over_pi                = glm::two_over_pi<float>();
    float four_over_pi               = glm::four_over_pi<float>();
    float two_over_root_pi           = glm::two_over_root_pi<float>();
    float one_over_root_two          = glm::one_over_root_two<float>();
    float root_half_pi               = glm::root_half_pi<float>();
    float root_two_pi                = glm::root_two_pi<float>();
    float root_ln_four               = glm::root_ln_four<float>();
    float e                          = glm::e<float>();
    float euler                      = glm::euler<float>();
    float root_two                   = glm::root_two<float>();
    float root_three                 = glm::root_three<float>();
    float root_five                  = glm::root_five<float>();
    float ln_two                     = glm::ln_two<float>();
    float ln_ten                     = glm::ln_ten<float>();
    float ln_ln_two                  = glm::ln_ln_two<float>();
    float third                      = glm::third<float>();
    float two_thirds                 = glm::two_thirds<float>();
    float golden_ratio               = glm::golden_ratio<float>();

    glm::vec3 vec3_zero              = glm::zero<glm::vec3>();
    glm::vec3 vec3_one               = glm::one<glm::vec3>();
    glm::vec3 vec3_pi                = glm::vec3(glm::pi<float>()); // glm::pi<glm::vec3>();
    glm::vec3 vec3_two_pi            = glm::two_pi<glm::vec3>();
    glm::vec3 vec3_half_pi           = glm::half_pi<glm::vec3>();
    glm::vec3 vec3_root_pi           = glm::root_pi<glm::vec3>();
    glm::vec3 vec3_three_over_two_pi = glm::three_over_two_pi<glm::vec3>();
    glm::vec3 vec3_quarter_pi        = glm::quarter_pi<glm::vec3>();
    glm::vec3 vec3_one_over_pi       = glm::one_over_pi<glm::vec3>();
    glm::vec3 vec3_one_over_two_pi   = glm::one_over_two_pi<glm::vec3>();
    glm::vec3 vec3_two_over_pi       = glm::two_over_pi<glm::vec3>();
    glm::vec3 vec3_four_over_pi      = glm::four_over_pi<glm::vec3>();
    glm::vec3 vec3_two_over_root_pi  = glm::two_over_root_pi<glm::vec3>();
    glm::vec3 vec3_one_over_root_two = glm::one_over_root_two<glm::vec3>();
    glm::vec3 vec3_root_half_pi      = glm::root_half_pi<glm::vec3>();
    glm::vec3 vec3_root_two_pi       = glm::root_two_pi<glm::vec3>();
    glm::vec3 vec3_root_ln_four      = glm::root_ln_four<glm::vec3>();
    glm::vec3 vec3_e                 = glm::e<glm::vec3>();
    glm::vec3 vec3_euler             = glm::euler<glm::vec3>();
    glm::vec3 vec3_root_two          = glm::root_two<glm::vec3>();
    glm::vec3 vec3_root_three        = glm::root_three<glm::vec3>();
    glm::vec3 vec3_root_five         = glm::root_five<glm::vec3>();
    glm::vec3 vec3_ln_two            = glm::ln_two<glm::vec3>();
    glm::vec3 vec3_ln_ten            = glm::ln_ten<glm::vec3>();
    glm::vec3 vec3_ln_ln_two         = glm::ln_ln_two<glm::vec3>();
    glm::vec3 vec3_third             = glm::third<glm::vec3>();
    glm::vec3 vec3_two_thirds        = glm::two_thirds<glm::vec3>();
    glm::vec3 vec3_golden_ratio      = glm::golden_ratio<glm::vec3>();

    glm::mat4 mat4_zero              = glm::zero<glm::mat4>();
    glm::mat4 mat4_one               = glm::one<glm::mat4>();
    glm::mat4 mat4_pi                = glm::mat4(glm::pi<float>()); //glm::pi<glm::mat4>();
    glm::mat4 mat4_two_pi            = glm::two_pi<glm::mat4>();
    glm::mat4 mat4_half_pi           = glm::half_pi<glm::mat4>();
    glm::mat4 mat4_root_pi           = glm::root_pi<glm::mat4>();
    glm::mat4 mat4_three_over_two_pi = glm::three_over_two_pi<glm::mat4>();
    glm::mat4 mat4_quarter_pi        = glm::quarter_pi<glm::mat4>();
    glm::mat4 mat4_one_over_pi       = glm::one_over_pi<glm::mat4>();
    glm::mat4 mat4_one_over_two_pi   = glm::one_over_two_pi<glm::mat4>();
    glm::mat4 mat4_two_over_pi       = glm::two_over_pi<glm::mat4>();
    glm::mat4 mat4_four_over_pi      = glm::four_over_pi<glm::mat4>();
    glm::mat4 mat4_two_over_root_pi  = glm::two_over_root_pi<glm::mat4>();
    glm::mat4 mat4_one_over_root_two = glm::one_over_root_two<glm::mat4>();
    glm::mat4 mat4_root_half_pi      = glm::root_half_pi<glm::mat4>();
    glm::mat4 mat4_root_two_pi       = glm::root_two_pi<glm::mat4>();
    glm::mat4 mat4_root_ln_four      = glm::root_ln_four<glm::mat4>();
    glm::mat4 mat4_e                 = glm::e<glm::mat4>();
    glm::mat4 mat4_euler             = glm::euler<glm::mat4>();
    glm::mat4 mat4_root_two          = glm::root_two<glm::mat4>();
    glm::mat4 mat4_root_three        = glm::root_three<glm::mat4>();
    glm::mat4 mat4_root_five         = glm::root_five<glm::mat4>();
    glm::mat4 mat4_ln_two            = glm::ln_two<glm::mat4>();
    glm::mat4 mat4_ln_ten            = glm::ln_ten<glm::mat4>();
    glm::mat4 mat4_ln_ln_two         = glm::ln_ln_two<glm::mat4>();
    glm::mat4 mat4_third             = glm::third<glm::mat4>();
    glm::mat4 mat4_two_thirds        = glm::two_thirds<glm::mat4>();
    glm::mat4 mat4_golden_ratio      = glm::golden_ratio<glm::mat4>();

    float inf                        =  std::numeric_limits<float>::infinity();
    float neg_inf                    = -std::numeric_limits<float>::infinity();

    float max_val                    =  std::numeric_limits<float>::max();
    float min_val                    =  std::numeric_limits<float>::min();

    float rad = glm::radians(45.0f);
    float deg = glm::degrees(glm::pi<float>());

    //
    // vector API
    //
    {
        float s1,s2,s3, d, m;
        bool flag;

        glm::vec3  v1(1.2f, 2.4f, 5.6f);

        glm::vec2  v2(v1);
        glm::vec3  v3(v1);
        glm::vec4  v4(v1, 2.6f);
        glm::vec4  v5(2.6f, v1);
        glm::vec4  v6(v2, v2);
        
        float* pValues = glm::value_ptr(v1);
                                        
        s1 = v1[0];    s2 = v1[1];    s3 = v1[2];
        v1[0] = s1;    v1[1] = s2;    v1[2] = s3;

        v3 = v1;

        flag = v3 == v1;
        flag = v3 != v1;

        v3 += 2.3f;             v3 += v1;
        v3 -= 2.3f;             v3 -= v1;
        v3 *= 2.3f;             v3 *= v1;
        v3 /= 2.3f;             v3 /= v1;

        v3 = v1 + 2.3f;         v3 = 2.3f + v1;             v3 = v1 + v1;
        v3 = v1 - 2.3f;         v3 = 2.3f - v1;             v3 = v1 - v1;
        v3 = v1 * 2.3f;         v3 = 2.3f * v1;             v3 = v1 * v1;
        v3 = v1 / 2.3f;         v3 = 2.3f / v1;             v3 = v1 / v1;

        d = glm::distance(v1, v3);  // distance(v3, v1)
        d = d * d;                  // square distance

        d = glm::length(v3);
        d = d * d;                  // square length

        v3 = glm::normalize(v3);

        v3 = glm::cross(v1, v3);

        m = glm::dot(v1, v3);

        v1 = glm::vec3(1.5f, 0.9f, 6.3f);
        v3 = glm::vec3(2.4f,-1.4f, 0.3f);  v3 = glm::normalize(v3);
        glm::vec3 vr;

        vr = glm::reflect(v1, v3);
        vr = glm::refract(v1, v3, 0.7f);

        vr = glm::mix(v1, v3, 0.8f);        // lerp availbale in #include <glm/gtx/compatibility.hpp>, but is the same
        m  = glm::mix(0.5f, 1.3f, 0.8f);


        glm::vec3 N    = glm::vec3(1.5f, 0.9f, 6.3f);
        glm::vec3 I    = glm::vec3(2.4f,-1.4f, 0.3f);
        glm::vec3 Nref = glm::vec3(3.4f,-2.4f,-1.4);

        vr = glm::faceforward(N, I, Nref); // If dot(Nref, I) < 0.0, return N, otherwise, return -N. 

        int ijk = 234;
    }

    //
    // matrix API
    //
    {
        // Mathematically: m(row x col)
        // --------------
        // columns: c0  c1  c2  c3       c0 c1 c2 c3
        //        -----------------     -------------
        //        (m00 m01 m02 m03)     ( 1  2  3  4) |r0
        //  mat = (m10 m11 m12 m13)  =  ( 5  6  7  8) |r1
        //        (m20 m21 m22 m23)     ( 9 10 11 12) |r2
        //        (m30 m31 m32 m33)     (13 14 15 16) |r3
        //
        //      col 0    col 1    col 2    col 3
        float m00 = 1, m01 = 2, m02 = 3, m03 = 4,     // row 0
              m10 = 5, m11 = 6, m12 = 7, m13 = 8,     // row 1
              m20 = 9, m21 =10, m22 =11, m23 =12,     // row 2
              m30 =13, m31 =14, m32 =15, m33 =16;     // row 3
        //
        // Element wise constructor takes elements in column-major order,
        // i.e. it takes the four columns of the matrix.
        //             r0   r1   r2   r3
        glm::mat4 mat(m00, m10, m20, m30,  // col 0    mat( 1, 5,  9, 13,   // element wise ctor is column-major
                      m01, m11, m21, m31,  // col 1         2, 6, 10, 14,
                      m02, m12, m22, m32,  // col 2         3, 7, 11, 15,
                      m03, m13, m23, m33); // col 3         4, 8, 12, 16)

        // Debugger and Math
        //
        //  mat.
        //      value[0] = { 1, 5,  9, 13}
        //      value[1] = { 2, 6, 10, 14}
        //      value[2] = { 3, 7, 11, 15}
        //      value[3] = { 4, 8, 12, 16}
        //
        // Memory: mat = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16}
        //
        // Debugger and Math       columns              // memory is column-major
        //                      ( 1  2  3  4)
        //              rows    ( 5  6  7  8)
        //                      ( 9 10 11 12)
        //                      (13 14 15 16)

        glm::vec4 v(100, 200, 300, 400);
        glm::vec4 r = mat * v;                          // math is column-major x' = M*x
        //  [ 3000]    ( 1  2  3  4)   [100]
        //  [ 7000] =  ( 5  6  7  8) * [200]
        //  [11000]    ( 9 10 11 12)   [300]
        //  [15000]    (13 14 15 16)   [400]

        int ijk = 234;
    }

    //
    // some glm example code
    //
    {
        glm::vec3 pos1 = glm::vec3(5.f);
        glm::vec3 pos2 = glm::vec3(3.f, 2.f, 1.f);
        glm::vec3 dir  = glm::vec3(1.f, 2.f, 3.f);

        float l1 = glm::length(dir);
        float l2 = l1 * l1;                         // square length

        glm::vec3 n = glm::normalize(dir);

        float dist1 = glm::distance(pos1, pos2);    // length(pos2 - pos1)
        float dist2 = dist1 * dist1;                // square distance

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 ortho = glm::ortho(-3.f, 2.f, -6.f, 1.3f, 0.1f, 100.f);
        //                  columns
        //        ( 0.4          0.           0.           0.2        )
        //   rows ( 0.           0.273972601  0.           0.64383555 )
        //        ( 0.           0.          -0.020020019 -1.002002   )
        //        ( 0.           0.           0.           1.         )

        glm::mat4 ortho2D = glm::ortho(-3.f, 2.f, -6.f, 1.3f);
        //                  columns
        //        ( 0.4          0.           0.           0.2        )
        //   rows ( 0.           0.273972601  0.           0.64383555 )
        //        ( 0.           0.          -1.           0.         )
        //        ( 0.           0.           0.           1.         )

        glm::mat4 frustum = glm::frustum(-3.f, 2.f, -6.f, 1.3f, 0.1f, 100.f);
        //                  columns
        //        ( 0.039999999  0.          -0.2         0.     )
        //   rows ( 0.           0.02739726  -0.64383555  0.     )
        //        ( 0.           0.          -1.002002   -0.2002 )
        //        ( 0.           0.          -1.          0.     )

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        //                  columns
        //        ( 1.81066012  0.          0.          0.        )
        //   rows ( 0.          2.41421342  0.          0.        )
        //        ( 0.          0.         -1.002002   -0.2002002 )
        //        ( 0.          0.         -1.          0.        )

        glm::mat4 projectionfov = glm::perspectiveFov(glm::radians(45.0f), 300.f, 200.f, 0.1f, 100.0f);
        //                  columns
        //        ( 1.60947561  0.          0.          0.        )
        //   rows ( 0.          2.41421342  0.          0.        )
        //        ( 0.          0.         -1.002002   -0.2002002 )
        //        ( 0.          0.         -1.          0.        )

        glm::mat4 inf_projection = glm::infinitePerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f);
        //                  columns
        //        ( 1.81066     0.          0.          0.  )
        //   rows ( 0.          2.41421342  0.          0.  )
        //        ( 0.          0.         -1.         -0.2 )
        //        ( 0.          0.         -1.          0.  )

        glm::mat4 eps_inf_projection = glm::tweakedInfinitePerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 3.0E-7f);
        //                  columns
        //        ( 1.81066     0.          0.           0.          )
        //   rows ( 0.          2.41421342  0.           0.          )
        //        ( 0.          0.         -0.999999702 -0.199999973 )
        //        ( 0.          0.         -1.           0.          )

        glm::mat4 view = glm::lookAt(
                                    glm::vec3(4,3,3),   // Camera is at (4,3,-3), in World Space
                                    glm::vec3(0,0,0),   // and looks at the origin
                                    glm::vec3(0,1,0)    // Head is up (set to 0,-1,0 to look upside-down)
                                );
        //                  columns
        //        ( 0.599999964  0.          -0.799999952  0.         )
        //   rows (-0.411596596  0.857492924 -0.308697462  0.         )
        //        ( 0.685994387  0.51449579   0.51449579  -5.83095264 )
        //        ( 0.           0.           0.           1.         )

        glm::mat4 inv_view = glm::inverse(view);
        //                  columns
        //        ( 0.600000024 -0.411596596  0.685994327  4.00000048 )
        //   rows ( 0.           0.857492924  0.51449573   3.00000048 )
        //        (-0.800000072 -0.308697462  0.51449573   3.         )
        //        ( 0.           0.           0.           1.         )

        glm::mat4 mvp = projection * view * model;
        //                  columns
        //        ( 1.08639598   0.          -1.44852805   0.         )
        //   rows (-0.993682027  2.07017088  -0.74526155   0.         )
        //        (-0.687367737 -0.515525818 -0.515525818  5.64242601 )
        //        (-0.685994387 -0.51449579  -0.51449579   5.83095264 )

        glm::mat4 inv_mat = glm::inverse(mvp);
        //                  columns
        //        ( 0.331370682 -0.170488641 -19.9799862   19.3339901 )
        //   rows ( 5.4487e-7    0.3551853   -14.9849892   14.5004930 )
        //        (-0.441827208 -0.12786676  -14.9849892   14.500494  )
        //        ( 0.           0.           -4.99499607   5.0049963 )

        glm::mat4 trsp_mat     = glm::transpose(mvp);
        //                  columns
        //        (  1.08639598 -0.993682027 -0.687367737 -0.685994387 )
        //   rows (  0           2.07017088  -0.515525818 -0.51449579  )
        //        ( -1.44852805 -0.74526155  -0.515525818 -0.51449579  )
        //        (  0           0            5.64242601   5.83095264  )

        glm::mat4 inv_trsp_mat = glm::inverseTranspose(mvp);
        //                  columns
        //        (   0.331370533   5.44869465e-007  -0.441826999   0          )
        //   rows (  -0.170488566   0.355185151      -0.127866715   0          )
        //        ( -19.9799767   -14.9849825       -14.9849825    -4.99499369 )
        //        (  19.3339825    14.5004864        14.5004873     5.00499439 )

        float* pMat = glm::value_ptr(mvp);
        //   [ 1.08639598,  -0.993682027, -0.687367737, -0.685994387,
        //     0,            2.07017088,  -0.515525818, -0.51449579,
        //    -1.44852805,  -0.74526155,  -0.515525818, -0.51449579,
        //     0,            0,            5.64242601,   5.83095264 ]

        glm::mat4 T  = glm::translate(glm::mat4(1), pos1);
        //          columns
        //        ( 1 0 0 5 )
        //   rows ( 0 1 0 5 )
        //        ( 0 0 1 5 )
        //        ( 0 0 0 1 )

        glm::mat4 Rx = glm::rotate(T,  glm::radians(10.f), glm::vec3(1.f, 0.f, 0.f));
        //                  columns
        //        (  1  0            0            5 )
        //   rows (  0  0.98480773  -0.173648179  5 )
        //        (  0  0.173648179  0.98480773   5 )
        //        (  0  0            0            1 )

        glm::mat4 Ry = glm::rotate(Rx, glm::radians(12.f), glm::vec3(0.f, 1.f, 0.f));
        //                  columns
        //        ( 0.978147626  0            0.2079117    5 )
        //   rows ( 0.036103487  0.98480773  -0.169853553  5 )
        //        (-0.204753056  0.173648179  0.963287354  5 )
        //        ( 0            0            0            1 )

        glm::mat4 S  = glm::scale(glm::mat4(1), glm::vec3(1000.f));
        //                  columns
        //        ( 1000    0    0    0 )
        //   rows (    0 1000    0    0 )
        //        (    0    0 1000    0 )
        //        (    0    0    0    1 )

        glm::vec4 r;
        glm::vec4 px(17.3f, 12.6f, 13.2f, 1.f);
        r = mvp * px;
        //      [-0.325920105, -0.943996429, -19.5496025, -19.3107414]

        glm::vec4 py(17.3f, 12.6f, 13.2f, 9.6f);
        r = mvp * py;
        //      [-0.325920105, -0.943996429, 28.9752674, 30.8354530]

        glm::vec4 vx(17.3f, 12.6f, 13.2f, 0.f);
        r = mvp * vx;
        //      [-0.325920105, -0.943996429, -25.1920280, -25.1416931]

        glm::vec3 v1(12.4f, 1.4f, 17.6f);
        glm::vec3 v2( 7.4f, 0.2f, 12.1f);
        float val = glm::dot(v1, v2);

        // glm::vec3 objPt = glm::unProject(glm::vec3(x, h-y, winZ), _model_view, _projection, glm::vec4(0,0, w, h));

        float rand = glm::linearRand<float>(-5.0f, 5.0f);

        int ijk = 234;
    }
#endif // OSG_WITH_GLM
}

void vmath_math_library()
{
#ifdef OSG_WITH_VMATH
    //      vmath:  typedef vmath::vec2<int> tVec2i;
    //
    //          tVec2f, tVec3f, tVec4f
    //          tVec2d, tVec3d, tVec4d
    //          tVec2i, tVec3i, tVec4i
    //          tVec2u, tVec3u, tVec4u
    //          tVec2b, tVec3b, tVec4b
    //
    //          tMat2f, tMat3f, tMat4f
    //          tMat2d, tMat3d, tMat4d
    //          tMat2i, tMat3i, tMat4i
    //          tMat2u, tMat3u, tMat4u
    //          tMat2b, tMat3b, tMat4b

    float pi      = static_cast<float>(M_PI);

    float inf     =  std::numeric_limits<float>::infinity();
    float neg_inf = -std::numeric_limits<float>::infinity();

    float max_val =  std::numeric_limits<float>::max();
    float min_val =  std::numeric_limits<float>::min();

    float rad = static_cast<float>(DEG2RAD(45.0f));             // #define DEG2RAD( a ) ( a * M_PI / 180.0 )
    float deg = static_cast<float>(RAD2DEG(pi));                // #define DEG2RAD( a ) ( a * M_PI / 180.0 )

    //
    // vector API
    //
    {
        float s1,s2,s3, d, m;
        bool flag;

        tVec3f  v1(1.2f, 2.4f, 5.6f);

        tVec2f  v2(v1);
        tVec3f  v3(v1);
        tVec4f  v4(v1, 2.6f);
        tVec4f  v5(2.6f, v1);
        tVec4f  v6(v2, v2);
        tVec3f  v7(1.3f);
        
        float pValues = *v1;
                                        
        s1 = v1[0];    s2 = v1[1];    s3 = v1[2];
        v1[0] = s1;    v1[1] = s2;    v1[2] = s3;

        v3 = v1;

        flag = v3 < v1;
        flag = v3 == v1;
        flag = v3 != v1;

        v3 += 2.3f;             v3 += v1;
        v3 -= 2.3f;             v3 -= v1;
        v3 *= 2.3f;             v3 *= v1;
        v3 /= 2.3f;             v3 /= v1;

        v3 = v1 + 2.3f;         v3 = 2.3f + v1;             v3 = v1 + v1;
        v3 = v1 - 2.3f;         v3 = 2.3f - v1;             v3 = v1 - v1;
        v3 = v1 * 2.3f;         v3 = 2.3f * v1;             v3 = v1 * v1;
        v3 = v1 / 2.3f;         v3 = 2.3f / v1;             v3 = v1 / v1;

        d = vmath::length(v1 - v3); // distance(v3, v1)
        d = d * d;                  // square distance

        d = vmath::length(v3);
        d = d * d;                  // square length

        v3 = vmath::normalize(v3);

        v3 = vmath::cross(v1, v3);

        m = vmath::dot(v1, v3);

        v1 = tVec3f(1.5f, 0.9f, 6.3f);
        v3 = tVec3f(2.4f,-1.4f, 0.3f);  v3 = vmath::normalize(v3);
        tVec3f vr;

        vr = vmath::reflect(v1, v3);
        vr = vmath::refract(v1, v3, 0.7f);

        vr = vmath::lerp(v1, v3, 0.8f);
        m  = vmath::lerp(0.5f, 1.3f, 0.8f);

        int ijk = 234;
    }

    //
    // matrix API
    //
    {
        // Mathematically: m(row x col)
        // --------------
        // columns: c0  c1  c2  c3       c0 c1 c2 c3
        //        -----------------     -------------
        //        (m00 m01 m02 m03)     ( 1  2  3  4) |r0
        //  mat = (m10 m11 m12 m13)  =  ( 5  6  7  8) |r1
        //        (m20 m21 m22 m23)     ( 9 10 11 12) |r2
        //        (m30 m31 m32 m33)     (13 14 15 16) |r3
        //
        //      col 0    col 1    col 2    col 3
        float m00 = 1, m01 = 2, m02 = 3, m03 = 4,     // row 0
              m10 = 5, m11 = 6, m12 = 7, m13 = 8,     // row 1
              m20 = 9, m21 =10, m22 =11, m23 =12,     // row 2
              m30 =13, m31 =14, m32 =15, m33 =16;     // row 3
        //
        // Element wise constructor takes elements in row-major order,
        // i.e. it takes the four rows of the matrix.
        //          c0   c1   c2   c3
        tMat4f mat(m00, m01, m02, m03,  // row 0    mat0( 1, 2, 3, 4,
                   m10, m11, m12, m13,  // row 1          5, 6, 7, 8,
                   m20, m21, m22, m23,  // row 2          9,10,11,12,
                   m30, m31, m32, m33); // row 3         13,14,15,16)

        //
        // In memory the matrix consists of a float elem[4][4] where 
        // elem[0],...,elem[3] are the rows of the matrix, i.e.
        //
        //      => elem[0][3] == m03 = 13, elem[2][1] == m21 = 7
        //
        //       (elem[0])   (m00 = 1, m01 =  2, m02 = 3, m03 = 4)   // row 0
        // mat = (elem[1]) = (m10 = 5, m11 =  6, m12 = 7, m13 = 8)   // row 1
        //       (elem[2])   (m20 = 9, m21 = 10, m22 =11, m23 =12)   // row 2
        //       (elem[3])   (m30 =13, m31 = 14, m32 =15, m33 =16)   // row 3

        //
        // The debugger shows elem[0],...,elem[3] i.e. 4 rows
        // => it 'shows' the transpose of the matrix
        //
        // Debugger:
        //                           rows
        //                elem[0] elem[1] elem[2] elem[3]
        //                  [1]     [5]    [ 9]    [13]
        //        columns   [2]     [6]    [10]    [14]
        //                  [3]     [7]    [11]    [15]
        //                  [4]     [8]    [12]    [16]
        //
        //                     ( elem[0] )   [  1,  2,  3,  4]   ( 1  2  3  4)
        //      that is: mat = ( elem[1] ) = [  5,  6,  7,  8] = ( 5  6  7  8)
        //                     ( elem[2] )   [  9, 10, 11, 12]   ( 9 10 11 12)
        //                     ( elem[3] )   [ 13, 14, 15, 16]   (13 14 15 16)
        //

        tVec4f r;
        tVec4f v(100, 200, 300, 400);

        r = mat * v;                           // math in column-major x' = M * x
        //
        //  [ 3000]    ( 1  2  3  4)   [100]
        //  [ 7000] =  ( 5  6  7  8) * [200]
        //  [11000]    ( 9 10 11 12)   [300]
        //  [15000]    (13 14 15 16)   [400]
        assert(r == tVec4f(3000, 7000, 11000, 15000));

        r = v * mat;                           // math in row-major x' = x * M
        //
        //                                                       ( 1  2  3  4)
        //  [9000, 10000, 11000, 12000] = [100, 200, 300, 400] * ( 5  6  7  8)
        //                                                       ( 9 10 11 12)
        //                                                       (13 14 15 16)
        assert(r == tVec4f(9000, 10000, 11000, 12000));
        //

        int ijk = 234;
    }

    //
    // transformation of a plane equation
    //
    {
        tVec3f n(-0.058649845f, -0.81474495f, -0.57684559f);
        float  d = -15.294896f;

        tMat4f lViewProj( 0.00968677550f, -0.00082531053f,  0.00018079198f,  0.01650621000f,
                         -0.00084303610f, -0.01011643400f, -0.00101164330f, -5.15137000000f,
                         -0.00026111995f, -0.00094563351f,  0.00967393440f,  0.01891266900f,
                          0.00000000000f,  0.00000000000f,  0.00000000000f,  1.00000000000f);
        //
        // elem[0] = [ 0.00968677550, -0.00082531053,  0.00018079198,  0.01650621000]
        // elem[1] = [-0.00084303610, -0.01011643400, -0.00101164330, -5.15137000000]
        // elem[2] = [-0.00026111995, -0.00094563351,  0.00967393440,  0.01891266900]
        // elem[3] = [ 0.00000000000,  0.00000000000,  0.00000000000,  1.00000000000]
        //

        tMat4f mat1 = vmath::transpose(vmath::inverse(lViewProj));
        //
        // elem[0] = [102.45413200   -8.72906208   1.91218197  0.0000000]
        // elem[1] = [ -8.10017014  -97.20203400  -9.72020435  0.0000000]
        // elem[2] = [ -2.76178932  -10.00168510 102.31834400  0.0000000]
        // elem[3] = [-43.36586760 -500.39041100  -52.0390396  1.0000000]
        //

        tVec4f eq(n[0], n[1], n[2], -d);        // [-0.058649845, -0.81474495, -0.57684559, +15.294896]
        tVec4f treq = mat1 * eq;                // [6.43730164e-006, 85.2770004, -50.7110825, 455.547333]
        n = tVec3f(treq[0], treq[1], treq[2]);  // [6.43730164e-006, 85.2770004, -50.7110825]
        d = -treq[3];                           // -455.54733
        float len = vmath::length(n);           // 99.2158279
        n = n / len;                            // [6.48818030e-008 0.859510064 -0.511118889]
        d = d / len;                            // -4.59147835

        int ijk = 234;
    }

    // Frustum transform and corner test
    {
        // Let M be the transformation that maps from the view frustum into the unit bounding box
        // Then,                                     -1
        //          q' = M * q                  q = M   * q'
        //
        //                 -1 T                      T
        //          L' = (M  ) * L              L = M   * L'
        //
        //                                                            -1
        // Now let S = invEyeViewProj be the inverse of M, i.e. S = M
        // Then,          -1
        //          q' = S  * q                 q = S * q'
        //
        //                T                           -1 T
        //          L' = S  * L                 L = (S  ) * L'
        //
        {
            tMat4f invEyeViewProj(
                -0.72110826f,      0.099096067f,    -9.0407127e-008f,  0.30503249f,
                -4.0614378e-007f,  0.50316292f,    -18.835268f,       19.509626f,
                 0.26943529f,      0.26521787f,      4.1242672e-007f,  0.81637925f,
                -1.1266424e-008f, -1.2139417e-008f, -0.94176346f,      1.0000008f);
            //
            // invEyeViewProj.elem[0] = [-0.721108258,      0.0990960672,    -9.04071271e-008,  0.305032492]
            // invEyeViewProj.elem[1] = [-4.06143783e-007,  0.503162920,    -18.8352680,       19.5096264  ]
            // invEyeViewProj.elem[2] = [ 0.269435287,      0.265217870,      4.12426715e-007,  0.816379249]
            // invEyeViewProj.elem[3] = [-1.12664242e-008, -1.21394166e-008, -0.941763461,      1.00000083 ]
            //
            vmath::BoundingBox unitBB(tVec3f(-1.f, -1.f, 0.f), tVec3f(1.f));
            vmath::Frustum frustum(invEyeViewProj, unitBB);
            //
            // eyeViewProj.elem[0] = [-1.21687031,        0.297288209,  0.323894948,  0.305032104]
            // eyeViewProj.elem[1] = [-5.86758198e-008,   1.50948918,  -0.520713866, -0.490388840]
            // eyeViewProj.elem[2] = [ 0.454672188,       0.795654655,  0.866861939,  0.816378236]
            // eyeViewProj.elem[3] = [ 8.54420534e-007, -30.1897831,    9.35243797,   9.80777550 ]
            //

            vmath::Plane plNear, plFar, plLeft, plRight, plTop, plBottom;

            tVec3f near_left_bottom, near_right_bottom, near_right_top, near_left_top, 
                    far_left_bottom,  far_right_bottom,  far_right_top,  far_left_top;

            plNear   = frustum.GetPlaneHessNorm(vmath::Frustum::Near);   // {-0.305032253  0.490389019 -0.816378534},  9.29278374
            plFar    = frustum.GetPlaneHessNorm(vmath::Frustum::Far);    // { 0.305033237 -0.490389496  0.816377819},  7.36331606
            plLeft   = frustum.GetPlaneHessNorm(vmath::Frustum::Left);   // { 0.556216121  0.299134463 -0.775333583},  5.98268795
            plRight  = frustum.GetPlaneHessNorm(vmath::Frustum::Right);  // {-0.928351879  0.299134374 -0.220638648},  5.98268700
            plTop    = frustum.GetPlaneHessNorm(vmath::Frustum::Top);    // {-0.003871947  0.999938786 -0.010361788}, 19.9987755
            plBottom = frustum.GetPlaneHessNorm(vmath::Frustum::Bottom); // {-0.301159978 -0.509549856 -0.806015968},-10.1909981

            near_left_bottom  = frustum.GetCorner(vmath::Frustum::NearBottomLeft);  // { 0.927043915 19.0064487   0.281725824 }
            near_right_bottom = frustum.GetCorner(vmath::Frustum::NearBottomRight); // {-0.515171409 19.0064468   0.820596039 }
            near_right_top    = frustum.GetCorner(vmath::Frustum::NearTopRight);    // {-0.316979438 20.0127716   1.35103142  }
            near_left_top     = frustum.GetCorner(vmath::Frustum::NearTopLeft);     // { 1.12523580  20.0127735   0.812161148 }
            far_left_bottom   = frustum.GetCorner(vmath::Frustum::FarBottomLeft);   // {15.9183788    2.93962407  4.83755445  }
            far_right_bottom  = frustum.GetCorner(vmath::Frustum::FarBottomRight);  // {-8.84607124   2.93959117 14.0905571   }
            far_right_top     = frustum.GetCorner(vmath::Frustum::FarTopRight);     // {-5.44289351  20.2193317  23.1987247   }
            far_left_top      = frustum.GetCorner(vmath::Frustum::FarTopLeft);      // {19.3215580   20.2193642  13.9457216   }

            int ijk = 234;
        }
        {
            tMat4f invEyeViewProj(
                -0.72110826f,     0.099096075f,   -5.4491289e-010f, 0.30503222f,
                 6.7199948e-009f, 0.50316292f,    -0.11352624f,    -0.13661544f,
                 0.26943535f,     0.26521760f,     2.4858289e-009f, 0.81637865f,
                 3.2070208e-011f,-4.2300885e-010f,-0.0056763124f,   0.017688671f);

            //
            // invEyeViewProj.elem[0] = [-0.721108258,      0.0990960747,    -5.44912893e-010,  0.305032223 ]
            // invEyeViewProj.elem[1] = [ 6.71999478e-009,  0.503162920,     -0.113526240,     -0.136615440 ]
            // invEyeViewProj.elem[2] = [ 0.269435346,      0.265217602,      2.48582888e-009,  0.816378653 ]
            // invEyeViewProj.elem[3] = [ 3.20702076e-011, -4.23008850e-010, -0.00567631237,    0.0176886711]
            //
            vmath::BoundingBox unitBB(tVec3f(-1.f, -1.f, 0.f), tVec3f(1.f));
            vmath::Frustum frustum(invEyeViewProj, unitBB);
            //
            // eyeViewProj.elem[0] = [-1.21687019,      0.297288209,   0.950549245, 0.305032194]
            // eyeViewProj.elem[1] = [1.42767878e-008,  1.50948858,   -1.52816236, -0.490388811]
            // eyeViewProj.elem[2] = [0.454672158,      0.795652688,   2.54401994,  0.816378593]
            // eyeViewProj.elem[3] = [0.000000000,    -30.1897697,  -145.607468,    9.80777550 ]
            //

            vmath::Plane plNear, plFar, plLeft, plRight, plTop, plBottom;

            tVec3f near_left_bottom, near_right_bottom, near_right_top, near_left_top, 
                    far_left_bottom,  far_right_bottom,  far_right_top,  far_left_top;

            plNear   = frustum.GetPlaneHessNorm(vmath::Frustum::Near);   // {-0.305032253    0.490388900 -0.816378713}, -32.9913177
            plFar    = frustum.GetPlaneHessNorm(vmath::Frustum::Far);    // { 0.305032253   -0.490388930  0.816378653},  73.4398270
            plLeft   = frustum.GetPlaneHessNorm(vmath::Frustum::Left);   // { 0.556216002    0.299134403 -0.775333762},   5.98268747
            plRight  = frustum.GetPlaneHessNorm(vmath::Frustum::Right);  // {-0.928351939    0.299134433 -0.220638901},   5.98268795
            plTop    = frustum.GetPlaneHessNorm(vmath::Frustum::Top);    // {-0.00387199270  0.999938846 -0.010362954},  19.9987736
            plBottom = frustum.GetPlaneHessNorm(vmath::Frustum::Bottom); // {-0.301160276   -0.509549975 -0.806015790}, -10.1909990

            near_left_bottom  = frustum.GetCorner(vmath::Frustum::NearBottomLeft);  // { 52.4089355 -36.1688194  15.9269009 }
            near_right_bottom = frustum.GetCorner(vmath::Frustum::NearBottomRight); // {-29.1244106 -36.1688194  46.3910713 }
            near_right_top    = frustum.GetCorner(vmath::Frustum::NearTopRight);    // {-17.9199429  20.7221603  76.3783493 }
            near_left_top     = frustum.GetCorner(vmath::Frustum::NearTopLeft);     // { 63.6133995  20.7221603  45.9141846 }
            far_left_bottom   = frustum.GetCorner(vmath::Frustum::FarBottomLeft);   // { 77.1742172 -62.7107964  23.4529877 }
            far_right_bottom  = frustum.GetCorner(vmath::Frustum::FarBottomRight);  // {-42.8868408 -62.7107964  68.3126755 }
            far_right_top     = frustum.GetCorner(vmath::Frustum::FarTopRight);     // {-26.3878212  21.0634098 112.470131  }
            far_left_top      = frustum.GetCorner(vmath::Frustum::FarTopLeft);      // { 93.6732330  21.0634098  67.6104431 }

            int ijk = 234;
        }
    }

    // PolygonBody test
    {
        {
            vmath::PolygonBody body;

            // near polygon ccw
            vmath::Polygon3d* p1 = new vmath::Polygon3d(
                tVec3f(-0.76980060f, 19.422653f, -1.0000001f), 
                tVec3f(0.76980060f, 19.422653f, -1.0000001f), 
                tVec3f(0.76980060f, 20.577354f, -1.0000001f), 
                tVec3f(-0.76980060f, 20.577354f, -1.0000001f));

            // far polygon ccw
            vmath::Polygon3d* p2 = new vmath::Polygon3d(
                tVec3f(-1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(1154.7845f, -846.08868f, -1500.1088f), 
                tVec3f(-1154.7845f, -846.08868f, -1500.1088f));

            // left polygon ccw
            vmath::Polygon3d* p3 = new vmath::Polygon3d(
                tVec3f(-0.76980060f, 19.422653f, -1.0000001f), 
                tVec3f(-0.76980060f, 20.577354f, -1.0000001f), 
                tVec3f(-1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(-1154.7845f, -846.08868f, -1500.1088f));

            // right polygon ccw
            vmath::Polygon3d* p4 = new vmath::Polygon3d(
                tVec3f(0.76980060f, 19.422653f, -1.0000001f), 
                tVec3f(1154.7845f, -846.08868f, -1500.1088f), 
                tVec3f(1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(0.76980060f, 20.577354f, -1.0000001f));

            // bottom polygon ccw
            vmath::Polygon3d* p5 = new vmath::Polygon3d(
                tVec3f(-1154.7845f, -846.08868f, -1500.1088f), 
                tVec3f(1154.7845f, -846.08868f, -1500.1088f), 
                tVec3f(0.76980060f, 19.422653f, -1.0000001f), 
                tVec3f(-0.76980060f, 19.422653f, -1.0000001f));

            // top polygon ccw
            vmath::Polygon3d* p6 = new vmath::Polygon3d(
                tVec3f(1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(-1154.7845f, 886.08868f, -1500.1088f), 
                tVec3f(-0.76980060f, 20.577354f, -1.0000001f), 
                tVec3f(0.76980060f, 20.577354f, -1.0000001f));

            body.Add(p1);
            body.Add(p2);
            body.Add(p3);
            body.Add(p4);
            body.Add(p5);
            body.Add(p6);

            vmath::BoundingBox aabb(tVec3f(-97.039207f, -0.10000066f, -97.039207f), tVec3f(97.039207f, 63.168030f, 97.039207f));
            body.Clip(aabb);

            body.CreateUniqueVertexArray();

            //   [0] {  0.76980060, 20.577354,    -1.0000001}
            //   [1] { -0.76980060, 20.577354,    -1.0000001}
            //   [2] { -0.76980060, 19.422653,    -1.0000001}
            //   [3] {  0.76980060, 19.422653,    -1.0000001}
            //   [4] {-57.557354,   63.168030,   -74.769173 }
            //   [5] {-74.700829,   63.168030,   -97.039207 }
            //   [6] {-74.700813,   -0.099998474,-97.039192 }
            //   [7] {-26.799988,   -0.099998474,-34.814201 }
            //   [8] { 74.700829,   -0.10000229, -97.039200 }
            //   [9] { 74.700813,   63.168030,   -97.039185 }
            //  [10] { 57.557343,   63.168030,   -74.769173 }
            //  [11] { 26.799997,   -0.10000038, -34.814209 }
            //  [12] {-26.799997,   -0.10000038, -34.814209 }
            //  [13] { 26.799988,   -0.099998474,-34.814201 }
            //  [14] {-57.557343,   63.168030,   -74.769173 }
            //  [15] { 57.557354,   63.168030,   -74.769173 }
            //  [16] { 57.557343,   63.168030,   -97.039185 }
            //  [17] {-26.799988,   -0.10000610, -97.039185 }
            //  [18] {-74.700813,   -0.10000229, -97.039192 }
            //  [19] {-74.700813,   63.168030,   -97.039185 }
            //  [20] {-74.700829,   -0.10000610, -97.039200 }

            int ijk = 234;
        }

        {
            vmath::PolygonBody body;

            // near polygon ccw
            vmath::Polygon3d* p1 = new vmath::Polygon3d(
                tVec3f(6.1652236f, 30.303381f, -38.134102f), 
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f));

            // far polygon ccw
            vmath::Polygon3d* p2 = new vmath::Polygon3d(
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(27.631605f, 6.0474062f, -22.481089f));

            // left polygon ccw
            vmath::Polygon3d* p3 = new vmath::Polygon3d(
                tVec3f(6.1652236f, 30.303381f, -38.134102f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f), 
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(27.631605f, 6.0474062f, -22.481089f));

            // right polygon ccw
            vmath::Polygon3d* p4 = new vmath::Polygon3d(
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f));

            // bottom polygon ccw
            vmath::Polygon3d* p5 = new vmath::Polygon3d(
                tVec3f(27.631605f, 6.0474062f, -22.481089f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(6.1652236f, 30.303381f, -38.134102f));

            // top polygon ccw
            vmath::Polygon3d* p6 = new vmath::Polygon3d(
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f));

            body.Add(p1);
            body.Add(p2);
            body.Add(p3);
            body.Add(p4);
            body.Add(p5);
            body.Add(p6);

            vmath::BoundingBox aabb(tVec3f(-97.039207f, -0.10000066f, -97.039207f), tVec3f(97.039207f, 63.168030f, 97.039207f));
            body.Clip(aabb);

            body.Extrude(tVec3f(tVec3f(-369.38138f, 448.11539f, -169.85291f) - tVec3f(0.f, 0.f, 0.f)), aabb);

            body.Clip(aabb);

            //  [0] {  4.67488718, 31.3571892, -37.5240936 }
            //  [1] {  6.20812082, 31.3571873, -37.6640015 }
            //  [2] {  6.16522360, 30.3033810, -38.1341019 }
            //  [3] {  4.63198996, 30.3033829, -37.9941940 }
            //  [4] {-13.6468077,   6.04745770,-18.7144184 }
            //  [5] { 27.6316051,   6.04740620,-22.4810886 }
            //  [6] { 28.7865047,  34.4184608, -9.82480812 }
            //  [7] {-12.4919071,  34.4185104, -6.05813837 }
            //  [8] {-21.5467796,  63.1680298, -49.5816231 }
            //  [9] {-20.0135460,  63.1680298, -49.7215309 }
            // [10] {-20.9250965,  63.1680298, -50.5910645 }
            // [11] {-22.4583302,  63.1680298, -50.4511566 }
            // [12] {-60.7312737,  63.1680260, -40.3653030 }
            // [13] {-19.4529057,  63.1680260, -44.1319923 }
            // [14] {  5.08824348, 63.1680298, -20.7219963 }
            // [15] {-36.1901245,  63.1680298, -16.9553089 }

            int ijk = 234;
        }

        {
            vmath::PolygonBody body;

            // near polygon ccw
            vmath::Polygon3d* p1 = new vmath::Polygon3d(
                tVec3f(6.1652236f, 30.303381f, -38.134102f), 
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f));

            // far polygon ccw
            vmath::Polygon3d* p2 = new vmath::Polygon3d(
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(27.631605f, 6.0474062f, -22.481089f));

            // left polygon ccw
            vmath::Polygon3d* p3 = new vmath::Polygon3d(
                tVec3f(6.1652236f, 30.303381f, -38.134102f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f), 
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(27.631605f, 6.0474062f, -22.481089f));

            // right polygon ccw
            vmath::Polygon3d* p4 = new vmath::Polygon3d(
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f));

            // bottom polygon ccw
            vmath::Polygon3d* p5 = new vmath::Polygon3d(
                tVec3f(27.631605f, 6.0474062f, -22.481089f), 
                tVec3f(-13.646808f, 6.0474577f, -18.714418f), 
                tVec3f(4.6319900f, 30.303383f, -37.994194f), 
                tVec3f(6.1652236f, 30.303381f, -38.134102f));

            // top polygon ccw
            vmath::Polygon3d* p6 = new vmath::Polygon3d(
                tVec3f(-12.491907f, 34.418510f, -6.0581384f), 
                tVec3f(28.786505f, 34.418461f, -9.8248081f), 
                tVec3f(6.2081208f, 31.357187f, -37.664001f), 
                tVec3f(4.6748872f, 31.357189f, -37.524094f));

            body.Add(p1);
            body.Add(p2);
            body.Add(p3);
            body.Add(p4);
            body.Add(p5);
            body.Add(p6);

            vmath::BoundingBox aabb(tVec3f(-97.039207f, -0.10000066f, -97.039207f), tVec3f(97.039207f, 63.168030f, 97.039207f));
            body.Clip(aabb);

            body.CreateConvexHull(tVec3f(-369.38138f, 448.11539f, -169.85291f));

            vmath::Plane plNear   (tVec3f(-0.61048514f,  0.74061066f, -0.28071985f), 247.05276f), 
                         plFar    (tVec3f( 0.61048520f, -0.74061060f,  0.28071988f),  86.555931f), 
                         plLeft   (tVec3f(-0.92862451f, -0.34693497f,  0.13150162f), 165.21375f), 
                         plRight  (tVec3f( 0.59523535f,  0.75138634f, -0.28480414f), 165.21371f), 
                         plBottom (tVec3f(-0.16669457f,  0.54318881f,  0.82289660f), 165.21373f), 
                         plTop    (tVec3f(-0.16669455f, -0.13873750f, -0.97619921f), 165.21376f);

            vmath::Frustum lFrust(plNear, plFar, plLeft, plRight, plTop, plBottom);

            body.Clip(lFrust);
            body.Clip(aabb);

            body.CreateUniqueVertexArray();

            //  [0] {-12.491889,  34.418598, -6.0580692 }
            //  [1] { 28.786419,  34.418446, -9.8247709 }
            //  [2] {  1.1160164, 63.168030, -20.945816 }
            //  [3] {-37.293556,  63.168030, -17.440823 }
            //  [4] {-13.646901,   6.0473685,-18.714413 }
            //  [5] {-37.293564,  63.168030, -17.440823 }
            //  [6] {-59.612213,  63.168030, -38.243382 }
            //  [7] { 27.631639,   6.0473080,-22.481112 }
            //  [8] {  6.2081275, 31.357132, -37.664093 }
            //  [9] {-22.460390,  63.168030, -47.753983 }
            // [10] {  1.1160278, 63.168030, -20.945816 }
            // [11] {  4.6319666, 30.303387, -37.994129 }
            // [12] {-59.612206,  63.168030, -38.243378 }
            // [13] {-24.787521,  63.168030, -48.365997 }
            // [14] {  6.1652594, 30.303417, -38.134014 }
            // [15] {-23.374817,  63.168030, -48.494873 }
            // [16] {-22.460388,  63.168022, -47.753983 }
            // [17] {-24.787525,  63.168030, -48.365997 }
            // [18] {-23.374825,  63.168030, -48.494869 }

            int ijk = 234;
        }
    }

    // Little transformation test
    {
        tMat4f lViewProjMat(
                -0.0073318263f, -0.0033760236f, -0.0025865268f,  0.067520469f,
                -0.0037693817f,  0.0027709638f,  0.0070680156f, -0.055419277f,
                 0.0012322352f, -0.0045445818f,  0.0024388228f, -2.4743109f,
                 0.00000000f,    0.00000000f,    0.00000000f,    1.0000000f);

        tVec3f center(-1.6575359f, 19.893993f, 1.4721632f);
        tVec3f nearCamPt(-1.2126635f, 20.219912f, 0.63797742f);

        tVec3f projViewDir_LS(
                    vmath::transform(lViewProjMat, center) - vmath::transform(lViewProjMat, nearCamPt));  
        // [0.00220439211, 0.00666982681, 0.00296735764]

        int ijk = 234;
    }
    
    // LiSP tests
    {
        // LiSP test I
        {
            vmath::LiSP liSP(1);

            liSP.SetMode(vmath::LiSP::NOpt);
            liSP.SetArbScaled(false);
            liSP.SetParamN(1.f, 0);
            liSP.SetSplitParam(0.5f);

            tMat4f matLightProj(
                0.0087762913f, 0.00000000f,   0.00000000f,    0.00000000f,
                0.00000000f,   0.0087762913f, 0.00000000f,    0.00000000f,
                0.00000000f,   0.00000000f,  -0.0052931984f, -2.5814035f,
                0.00000000f,   0.00000000f,   0.00000000f,    1.0000000f);
            liSP.SetLightProjMat(matLightProj, vmath::Projection::Ortho3d);

            tMat4f matLightView(
                -0.83052868f, -0.41207841f, -0.37471759f, 28.424620f,
                -0.55458331f,  0.54953837f,  0.62485582f, -2.4752662f,
                -0.051567912f, 0.72677296f, -0.68493932f,-13.445474f,
                 0.00000000f,  0.00000000f,  0.00000000f,  1.0000000f);

            vmath::View viewLightView(
                tVec3f(-31.201782f,      439.74268f,  -414.43073f),
                tVec3f(  0.00000000f,      0.00000000f,  0.00000000f),
                tVec3f(  5.9554767e-010f, -0.68585175f, -0.72774118f));

            liSP.SetLightView(matLightView, viewLightView);

            tMat4f matCamView(
                -0.74791080f, 0.00000000f, -0.66379929f, 18.094826f,
                -0.27553046f, 0.90978438f,  0.31044355f,-15.776711f,
                 0.60391420f, 0.41508099f, -0.68043751f,-20.458235f,
                 0.00000000f, 0.00000000f,  0.00000000f, 1.0000000f);

            vmath::View viewCamView(
                tVec3f(21.541370f,  22.845234f,  2.9885583f),
                tVec3f(20.937456f,  22.430153f,  3.6689959f),
                tVec3f (0.00000000f, 1.0000000f, 0.00000000f)
                );

            liSP.SetCamView(matCamView, viewCamView);

            tMat4f matCamProj(
                 1.2990381f,  0.00000000f,  0.00000000f,  0.00000000f,
                 0.00000000f, 1.7320508f,   0.00000000f,  0.00000000f,
                 0.00000000f, 0.00000000f, -1.0069381f,  -1.0069389f,
                 0.00000000f, 0.00000000f, -1.0000000f,   0.00000000f);

            liSP.SetCamProjMat(matCamProj);

            liSP.SetFieldOfView(60.000000f);
            liSP.SetGamma(42.558643f);
            liSP.SetSplitParam(0.50000000f);
            liSP.SetPseudoNear(0.00000000f);
            liSP.SetPseudoFar(0.00000000f);

            // Artificially construct a PolygonBody for the test
            vmath::PolygonBody bodyB;

            vmath::Polygon3d* p1 = new vmath::Polygon3d;
            p1->AddVertex(tVec3f( 20.202635f,  22.955418f,   3.3372376f));
            p1->AddVertex(tVec3f( 21.354120f,  22.955418f,   4.3592257f));
            p1->AddVertex(tVec3f( 21.672276f,  21.904886f,   4.0007563f));
            p1->AddVertex(tVec3f( 20.520790f,  21.904886f,   2.9787679f));
            p1->AddVertex(tVec3f( 17.349363f,  63.168030f, -34.560703f));
            p1->AddVertex(tVec3f( 18.500849f,  63.168030f, -33.538715f));
            p1->AddVertex(tVec3f( 18.744465f,  63.168030f, -34.887249f));
            p1->AddVertex(tVec3f( 17.592979f,  63.168030f, -35.909237f));

            vmath::Polygon3d* p2 = new vmath::Polygon3d;
            p2->AddVertex(tVec3f(-97.039207f, -0.10000610f,  97.038437f));
            p2->AddVertex(tVec3f(-97.038353f, -0.10000610f,  97.039200f));
            p2->AddVertex(tVec3f(-97.039207f, -0.098762877f, 97.039200f));
            p2->AddVertex(tVec3f(-97.039207f, -0.087963305f, 97.027847f));
            p2->AddVertex(tVec3f(-97.039207f, -0.098762877f, 97.039200f));

            vmath::Polygon3d* p3 = new vmath::Polygon3d;
            p3->AddVertex(tVec3f( 21.354120f,  22.955418f,     4.3592257f));
            p3->AddVertex(tVec3f(  8.6928453f, 30.405632f,    97.039207f));
            p3->AddVertex(tVec3f( 16.729954f,  -0.099998474f, 97.039207f));
            p3->AddVertex(tVec3f( 24.735554f,  -0.099998474f, 27.686996f));
            p3->AddVertex(tVec3f( 21.672276f,  21.904886f,     4.0007563f));
            p3->AddVertex(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            p3->AddVertex(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            p3->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            p3->AddVertex(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            p3->AddVertex(tVec3f( 18.744465f,  63.168030f,   -34.887249f));

            vmath::Polygon3d* p4 = new vmath::Polygon3d;
            p4->AddVertex(tVec3f(-97.039215f,  -0.10000455f, 25.074013f));
            p4->AddVertex(tVec3f(-97.039207f,  32.604870f,   33.873398f));
            p4->AddVertex(tVec3f( 20.202635f,  22.955418f,    3.3372376f));
            p4->AddVertex(tVec3f( 20.520790f,  21.904886f,    2.9787679f));
            p4->AddVertex(tVec3f( -3.3615990f, -0.10000229f,  2.7496789f));
            p4->AddVertex(tVec3f(-97.039207f,  32.604870f,   33.873398f));
            p4->AddVertex(tVec3f( 17.349363f,  63.168030f,  -34.560703f));
            p4->AddVertex(tVec3f( 17.592979f,  63.168030f,  -35.909237f));
            p4->AddVertex(tVec3f( -7.8507590f, 63.168030f,  -56.876591f));

            vmath::Polygon3d* p5 = new vmath::Polygon3d;
            p5->AddVertex(tVec3f( 24.735556f,  -0.10000038f,  27.686996f));
            p5->AddVertex(tVec3f( -3.3615875f, -0.099998474f,  2.7496789f));
            p5->AddVertex(tVec3f( 20.520790f,  21.904886f,     2.9787679f));
            p5->AddVertex(tVec3f( 21.672276f,  21.904886f,     4.0007563f));
            p5->AddVertex(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            p5->AddVertex(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            p5->AddVertex(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            p5->AddVertex(tVec3f( 18.744465f,  63.168030f,   -34.887249f));

            vmath::Polygon3d* p6 = new vmath::Polygon3d;
            p6->AddVertex(tVec3f(-97.039207f,  37.133457f,  97.039207f));
            p6->AddVertex(tVec3f(  8.6928444f, 30.405632f,  97.039207f));
            p6->AddVertex(tVec3f( 21.354120f,  22.955418f,   4.3592257f));
            p6->AddVertex(tVec3f( 20.202635f,  22.955418f,   3.3372376f));
            p6->AddVertex(tVec3f(-97.039207f,  32.604870f,  33.873394f));
            p6->AddVertex(tVec3f(-97.039207f,  37.133457f,  97.039207f));
            p6->AddVertex(tVec3f(  6.3682003f, 63.168030f,  66.162643f));
            p6->AddVertex(tVec3f( 18.500849f,  63.168030f, -33.538715f));
            p6->AddVertex(tVec3f( 17.349363f,  63.168030f, -34.560703f));
            p6->AddVertex(tVec3f(-97.039207f,  32.604870f,  33.873394f));

            vmath::Polygon3d* p7 = new vmath::Polygon3d;
            p7->AddVertex(tVec3f(-64.470268f,  -0.099998474f, 97.039207f));
            p7->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p7->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p7->AddVertex(tVec3f(-97.038361f,  -0.10000229f,  97.039200f));
            p7->AddVertex(tVec3f(  2.8259430f, -0.099998474f, 97.039207f));
            p7->AddVertex(tVec3f(  8.6928453f, 30.405632f,    97.039207f));
            p7->AddVertex(tVec3f( 16.729954f,  -0.099998474f, 97.039207f));
            p7->AddVertex(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            p7->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p7->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p7->AddVertex(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            p7->AddVertex(tVec3f( -1.6632171f, 63.168034f,    37.412937f));
            p7->AddVertex(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            p7->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));

            vmath::Polygon3d* p8 = new vmath::Polygon3d;
            p8->AddVertex(tVec3f( 24.735556f,  -0.10000038f,  27.686996f));
            p8->AddVertex(tVec3f( -3.3615875f, -0.099998474f,  2.7496789f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.10000301f,  25.074013f));
            p8->AddVertex(tVec3f(-97.039200f,  -0.10000455f,  25.074011f));
            p8->AddVertex(tVec3f( -3.3615990f, -0.10000229f,   2.7496789f));
            p8->AddVertex(tVec3f( 24.735554f,  -0.099998474f, 27.686996f));
            p8->AddVertex(tVec3f( 16.729954f,  -0.099998474f, 97.039207f));
            p8->AddVertex(tVec3f(-97.038353f,  -0.10000610f,  97.039200f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.10000610f,  97.038445f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.10000229f,  97.038452f));
            p8->AddVertex(tVec3f(-97.038361f,  -0.10000229f,  97.039200f));
            p8->AddVertex(tVec3f(-64.470268f,  -0.099998474f, 97.039207f));
            p8->AddVertex(tVec3f(  2.8259430f, -0.099998474f, 97.039207f));
            p8->AddVertex(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            p8->AddVertex(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            p8->AddVertex(tVec3f( -7.8507590f, 63.168030f,   -56.876591f));
            p8->AddVertex(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            p8->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.087963305f, 97.027847f));
            p8->AddVertex(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            p8->AddVertex(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            p8->AddVertex(tVec3f( -1.6632171f, 63.168034f,    37.412937f));

            vmath::Polygon3d* p9 = new vmath::Polygon3d;
            p9->AddVertex(tVec3f(-97.039207f,  -0.10000610f,  97.038445f));
            p9->AddVertex(tVec3f(-97.039200f,  -0.10000455f,  25.074011f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.10000301f,  25.074013f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p9->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p9->AddVertex(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            p9->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            p9->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            p9->AddVertex(tVec3f(-97.039215f,  -0.10000455f,  25.074013f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.10000610f,  97.038437f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.10000229f,  97.038452f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p9->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p9->AddVertex(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            p9->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            p9->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            p9->AddVertex(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));

            vmath::Polygon3d* p10 = new vmath::Polygon3d;
            p10->AddVertex(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->AddVertex(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->AddVertex(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->AddVertex(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.087963305f, 97.027847f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));
            p10->AddVertex(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->AddVertex(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            p10->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            p10->AddVertex(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            p10->AddVertex(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            p10->AddVertex(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->AddVertex(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->AddVertex(tVec3f( -7.8507590f, 63.168030f,   -56.876591f));
            p10->AddVertex(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            p10->AddVertex(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            p10->AddVertex(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->AddVertex(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->AddVertex(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            p10->AddVertex(tVec3f(  6.3682003f, 63.168030f,    66.162643f));
            p10->AddVertex(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->AddVertex(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            p10->AddVertex(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            p10->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            p10->AddVertex(tVec3f( -1.6632171f, 63.168034f,    37.412937f));
            p10->AddVertex(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            p10->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            p10->AddVertex(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            p10->AddVertex(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            p10->AddVertex(tVec3f( -7.8507590f, 63.168030f,   -56.876591f));
            p10->AddVertex(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            p10->AddVertex(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.087963305f, 97.027847f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            p10->AddVertex(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            p10->AddVertex(tVec3f( -1.6632171f, 63.168034f,    37.412937f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            p10->AddVertex(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            p10->AddVertex(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            p10->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            p10->AddVertex(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            p10->AddVertex(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));

            bodyB.Add(p1);
            bodyB.Add(p2);
            bodyB.Add(p3);
            bodyB.Add(p4);
            bodyB.Add(p5);
            bodyB.Add(p6);
            bodyB.Add(p7);
            bodyB.Add(p8);
            bodyB.Add(p9);
            bodyB.Add(p10);

            vmath::PolygonBody::tVertexArray uniqueVertices;
            uniqueVertices.push_back(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.087963305f, 97.027847f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));
            uniqueVertices.push_back(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            uniqueVertices.push_back(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            uniqueVertices.push_back(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(tVec3f( -7.8507590f, 63.168030f,   -56.876591f));
            uniqueVertices.push_back(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            uniqueVertices.push_back(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            uniqueVertices.push_back(tVec3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(tVec3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            uniqueVertices.push_back(tVec3f(  6.3682003f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(tVec3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(tVec3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            uniqueVertices.push_back(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            uniqueVertices.push_back(tVec3f( -1.6632171f, 63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f(  6.3682013f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f( 20.246395f,  63.168030f,   -31.939274f));
            uniqueVertices.push_back(tVec3f( -7.8507476f, 63.168034f,   -56.876591f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            uniqueVertices.push_back(tVec3f( -7.8507590f, 63.168030f,   -56.876591f));
            uniqueVertices.push_back(tVec3f( 20.246393f,  63.168034f,   -31.939274f));
            uniqueVertices.push_back(tVec3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.087963305f, 97.027847f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.088067017f, 97.027954f));
            uniqueVertices.push_back(tVec3f(-68.959427f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f( -1.6632171f, 63.168034f,    37.412937f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.099897027f, 25.073910f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.098770142f, 97.039200f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  21.274025f,    97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  37.133457f,    97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  32.604870f,    33.873394f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  32.604870f,    33.873398f));
            uniqueVertices.push_back(tVec3f(-97.039207f,  -0.098762877f, 97.039200f));
            bodyB.SetVertexArray(uniqueVertices);

            std::vector<tVec3f> corners;
            corners.push_back(tVec3f(  21.672276f,  21.904886f,   4.0007563f));
            corners.push_back(tVec3f(  20.520790f,  21.904886f,   2.9787679f));
            corners.push_back(tVec3f(  20.202635f,  22.955418f,   3.3372376f));
            corners.push_back(tVec3f(  21.354120f,  22.955418f,   4.3592257f));
            corners.push_back(tVec3f(  40.539791f,-113.62879f,  149.89030f  ));
            corners.push_back(tVec3f(-126.57689f, -113.62879f,    1.5677508f));
            corners.push_back(tVec3f(-172.75128f,   38.836262f,  53.592941f ));
            corners.push_back(tVec3f(  -5.6346021f, 38.836262f, 201.91550f  ));

            std::vector<vmath::Plane*> planes;
            vmath::Plane* pl1 = new vmath::Plane(tVec3f( 0.60391480f,  0.41508070f, -0.68043733f), 19.956511f );
            vmath::Plane* pl2 = new vmath::Plane(tVec3f(-0.60391575f, -0.41508308f,  0.68043506f),124.67360f  );
            vmath::Plane* pl3 = new vmath::Plane(tVec3f( 0.96103317f,  0.25319675f,  0.11093587f), 26.817856f );
            vmath::Plane* pl4 = new vmath::Plane(tVec3f(-0.22426482f,  0.25319672f, -0.94106156f), -1.8590580f);
            vmath::Plane* pl5 = new vmath::Plane(tVec3f( 0.54057401f, -0.58035570f, -0.60907066f), -3.4338706f);
            vmath::Plane* pl6 = new vmath::Plane(tVec3f( 0.063340642f, 0.99543709f, -0.071366511f), 23.892124f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum camFrust(corners, planes);

            vmath::BoundingBox sceneAABB(tVec3f(-97.039207f, -0.10000066f, -97.039207f), tVec3f(97.039207f, 63.168030f, 97.039207f));

            tVec2f zRange(1.0000008f, 145.13222f);

            tMat4f liSPMatrix = liSP.GetLiSPMtx(
                                        0,                  // unsigned int        split,
                                        bodyB,              // const PolygonBody&  bodyB,
                                        camFrust,           // const Frustum&      camFrust, 
                                        0x0,                // const Frustum*      lightFrust, 
                                        sceneAABB,          // const BoundingBox&  sceneAABB,
                                        zRange              // const tVec2f&       zRange
                                );
            //
            //              [0.110, -0.086,  0.000, -2.-09]
            // liSPMatrix = [0.688,  0.876,  0.000,  0.007]
            //              [0.000,  0.000,  0.140,  0.361]
            //              [0.617,  0.787,  0.000,  0.146]
            //

            int ijk = 234;
        }

        // LiSP test II
        {
            vmath::LiSP liSP(1);

            liSP.SetMode(vmath::LiSP::NOpt);
            liSP.SetArbScaled(false);
            liSP.SetParamN(1.f, 0);
            liSP.SetSplitParam(0.5f);

            tMat4f matLightProj(
                4.2034721f,  0.00000000f,  0.00000000f,    0.00000000f,
                0.00000000f, 4.2034721f,   0.00000000f,    0.00000000f,
                0.00000000f, 0.00000000f, -3.3012176f, -1595.2123f,
                0.00000000f, 0.00000000f, -1.0000000f,     0.00000000f);
            liSP.SetLightProjMat(matLightProj, vmath::Projection::Perspective);

            tMat4f matLightView(
                 0.37209886f,  0.66555393f, -0.64697784f,    1.1646205e-005f,
                -0.38898203f, -0.52105552f, -0.75973284f,   -6.9774319e-006f,
                -0.84275460f,  0.53435850f,  0.065004356f,-605.06195f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            vmath::View viewLightView(
                tVec3f(-509.91882f, 323.32004f, 39.331669f),
                tVec3f(0.00000000f, 0.00000000f, 0.00000000f),
                tVec3f(3.9999373e-010f, 0.12075910f, -0.99268186f));

            liSP.SetLightView(matLightView, viewLightView);

            tMat4f matCamView(
                  0.88472515f,  0.018609947f, -0.46574140f,    6.5359397f,
                 -0.036769699f, 0.99887520f,  -0.029935205f, -11.052643f,
                  0.46466044f,  0.043609601f,  0.88441432f, -105.78976f,
                  0.00000000f,  0.00000000f,   0.00000000f,    1.0000000f);

            vmath::View viewCamView(
                tVec3f(42.967415f, 15.532030f, 96.275192f),
                tVec3f(42.502754f, 15.488420f, 95.390778f),
                tVec3f (-0.016558312f, 0.99982685f, 0.0084964950f)
                );

            liSP.SetCamView(matCamView, viewCamView);

            tMat4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f, 0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f, 0.00000000f,
                0.00000000f, 0.00000000f, -1.0042425f, -1.0042425f,
                0.00000000f, 0.00000000f, -1.0000000f,  0.00000000f);

            liSP.SetCamProjMat(matCamProj);

            liSP.SetFieldOfView(60.000000f);
            liSP.SetGamma(71.892494f);
            liSP.SetSplitParam(0.50000000f);
            liSP.SetPseudoNear(0.00000000f);
            liSP.SetPseudoFar(0.00000000f);

            // Artificially construct a PolygonBody for the test
            vmath::PolygonBody bodyB;

            vmath::Polygon3d* p1 = new vmath::Polygon3d;
            p1->AddVertex(tVec3f(15.269290f, -0.099920020f, 83.747429f));
            p1->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));
            p1->AddVertex(tVec3f(-44.512161f, 63.168030f, 86.934151f));
            p1->AddVertex(tVec3f(-87.468880f, 63.168030f, 75.058762f));

            vmath::Polygon3d* p2 = new vmath::Polygon3d;
            p2->AddVertex(tVec3f(-79.515152f, -0.10000066f, 40.178802f));
            p2->AddVertex(tVec3f(15.269290f, -0.099920020f, 83.747429f));
            p2->AddVertex(tVec3f(-87.468903f, 63.168030f, 75.058762f));
            p2->AddVertex(tVec3f(-97.039207f, 63.168030f, 70.659676f));
            p2->AddVertex(tVec3f(-97.039207f, -0.10000610f, 32.123699f));

            vmath::Polygon3d* p3 = new vmath::Polygon3d;
            p3->AddVertex(tVec3f(41.800472f, 16.050735f, 95.731934f));
            p3->AddVertex(tVec3f(-42.801273f, 63.168030f, 87.083420f));
            p3->AddVertex(tVec3f(-44.512177f, 63.168030f, 86.934158f));
            p3->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));

            vmath::Polygon3d* p4 = new vmath::Polygon3d;
            p4->AddVertex(tVec3f(39.048035f, -0.10000066f, 70.328667f));
            p4->AddVertex(tVec3f(15.269290f, -0.099920020f, 83.747429f));
            p4->AddVertex(tVec3f(-79.515152f, -0.10000066f, 40.178799f));

            vmath::Polygon3d* p5 = new vmath::Polygon3d;
            p5->AddVertex(tVec3f(59.951366f, 63.168030f, -13.391017f));
            p5->AddVertex(tVec3f(49.097382f, -0.099998474f, 64.657608f));
            p5->AddVertex(tVec3f(77.088989f, -0.10000066f, -97.039063f));
            p5->AddVertex(tVec3f(59.951378f, 63.168026f, -13.391098f));

            vmath::Polygon3d* p6 = new vmath::Polygon3d;
            p6->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390985f));
            p6->AddVertex(tVec3f(43.205029f, 14.926052f, 95.049591f));
            p6->AddVertex(tVec3f(49.097359f, -0.10000038f, 64.657722f));
            p6->AddVertex(tVec3f(49.097382f, -0.10000066f, 64.657608f));
            p6->AddVertex(tVec3f(59.951363f, 63.168026f, -13.391014f));

            vmath::Polygon3d* p7 = new vmath::Polygon3d;
            p7->AddVertex(tVec3f(15.269290f, -0.099920020f, 83.747429f));
            p7->AddVertex(tVec3f(39.048035f, -0.10000066f, 70.328667f));
            p7->AddVertex(tVec3f(49.097359f, -0.10000066f, 64.657722f));
            p7->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));

            vmath::Polygon3d* p8 = new vmath::Polygon3d;
            p8->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));
            p8->AddVertex(tVec3f(49.097359f, -0.10000038f, 64.657722f));
            p8->AddVertex(tVec3f(49.097359f, -0.10000066f, 64.657722f));
            p8->AddVertex(tVec3f(43.205029f, 14.926052f, 95.049591f));

            vmath::Polygon3d* p9 = new vmath::Polygon3d;
            p9->AddVertex(tVec3f(77.088989f, -0.099998474f, -97.039063f));
            p9->AddVertex(tVec3f(77.089012f, -0.10000066f, -97.039177f));
            p9->AddVertex(tVec3f(74.431824f, 63.168026f, -97.039124f));
            p9->AddVertex(tVec3f(59.951378f, 63.168030f, -13.391094f));

            vmath::Polygon3d* p10 = new vmath::Polygon3d;
            p10->AddVertex(tVec3f(77.089012f, -0.10000066f, -97.039177f));
            p10->AddVertex(tVec3f(74.963264f, 50.514450f, -97.039207f));
            p10->AddVertex(tVec3f(74.431824f, 63.168030f, -97.039207f));
            p10->AddVertex(tVec3f(74.431824f, 63.168030f, -97.039124f));
            p10->AddVertex(tVec3f(77.089012f, -0.099998474f, -97.039177f));

            vmath::Polygon3d* p11 = new vmath::Polygon3d;
            p11->AddVertex(tVec3f(77.089012f, -0.10000229f, -97.039177f));
            p11->AddVertex(tVec3f(77.088982f, -0.10000066f, -97.039207f));
            p11->AddVertex(tVec3f(74.963264f, 50.514450f, -97.039207f));

            vmath::Polygon3d* p12 = new vmath::Polygon3d;
            p12->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390984f));
            p12->AddVertex(tVec3f(43.162521f, 16.079493f, 95.014954f));
            p12->AddVertex(tVec3f(43.205029f, 14.926052f, 95.049591f));
            p12->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390984f));

            vmath::Polygon3d* p13 = new vmath::Polygon3d;
            p13->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390976f));
            p13->AddVertex(tVec3f(-41.604263f, 63.168030f, 86.480789f));
            p13->AddVertex(tVec3f(43.162521f, 16.079493f, 95.014954f));

            vmath::Polygon3d* p14 = new vmath::Polygon3d;
            p14->AddVertex(tVec3f(43.162521f, 16.079493f, 95.014954f));
            p14->AddVertex(tVec3f(-41.604271f, 63.168030f, 86.480789f));
            p14->AddVertex(tVec3f(-42.801300f, 63.168030f, 87.083412f));
            p14->AddVertex(tVec3f(41.800472f, 16.050735f, 95.731934f));

            vmath::Polygon3d* p15 = new vmath::Polygon3d;
            p15->AddVertex(tVec3f(43.162521f, 16.079493f, 95.014954f));
            p15->AddVertex(tVec3f(41.800472f, 16.050735f, 95.731934f));
            p15->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));

            vmath::Polygon3d* p16 = new vmath::Polygon3d;
            p16->AddVertex(tVec3f(43.162521f, 16.079493f, 95.014954f));
            p16->AddVertex(tVec3f(41.842957f, 14.897432f, 95.766670f));
            p16->AddVertex(tVec3f(43.205029f, 14.926052f, 95.049591f));

            vmath::Polygon3d* p17 = new vmath::Polygon3d;
            p17->AddVertex(tVec3f(-97.039207f, -0.099906921f, -97.039207f));
            p17->AddVertex(tVec3f(-32.317986f, -0.10000066f, -97.039207f));
            p17->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039207f));
            p17->AddVertex(tVec3f(-97.039207f, 63.168026f, -97.039207f));
            p17->AddVertex(tVec3f(74.431717f, 63.168030f, -97.039207f));
            p17->AddVertex(tVec3f(7.4377823f, -0.099998474f, -97.039207f));
            p17->AddVertex(tVec3f(77.088982f, -0.10000066f, -97.039207f));
            p17->AddVertex(tVec3f(74.963264f, 50.514450f, -97.039207f));
            p17->AddVertex(tVec3f(-97.039207f, -0.099868774f, -97.039207f));

            vmath::Polygon3d* p18 = new vmath::Polygon3d;
            p18->AddVertex(tVec3f(-79.515152f, -0.10000066f, 40.178802f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039093f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.031891f));
            p18->AddVertex(tVec3f(39.048035f, -0.10000066f, 70.328667f));
            p18->AddVertex(tVec3f(-79.515152f, -0.10000066f, 40.178799f));
            p18->AddVertex(tVec3f(49.097382f, -0.099998474f, 64.657608f));
            p18->AddVertex(tVec3f(77.088989f, -0.10000066f, -97.039063f));
            p18->AddVertex(tVec3f(49.097359f, -0.10000038f, 64.657722f));
            p18->AddVertex(tVec3f(49.097382f, -0.10000066f, 64.657608f));
            p18->AddVertex(tVec3f(77.089012f, -0.10000066f, -97.039177f));
            p18->AddVertex(tVec3f(77.088989f, -0.099998474f, -97.039063f));
            p18->AddVertex(tVec3f(77.089012f, -0.099998474f, -97.039177f));
            p18->AddVertex(tVec3f(77.089012f, -0.10000229f, -97.039177f));
            p18->AddVertex(tVec3f(77.088982f, -0.10000066f, -97.039207f));
            p18->AddVertex(tVec3f(-32.317986f, -0.10000066f, -97.039207f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039207f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039207f));
            p18->AddVertex(tVec3f(7.4377823f, -0.099998474f, -97.039207f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000066f, 32.123543f));
            p18->AddVertex(tVec3f(-97.039207f, -0.10000610f, 32.123699f));

            vmath::Polygon3d* p19 = new vmath::Polygon3d;
            p19->AddVertex(tVec3f(-97.039207f, 63.168026f, -97.039078f));
            p19->AddVertex(tVec3f(-41.604271f, 63.168030f, 86.480789f));
            p19->AddVertex(tVec3f(-42.801300f, 63.168030f, 87.083412f));
            p19->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390976f));
            p19->AddVertex(tVec3f(-41.604263f, 63.168030f, 86.480789f));
            p19->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390984f));
            p19->AddVertex(tVec3f(74.431824f, 63.168030f, -97.039207f));
            p19->AddVertex(tVec3f(74.431824f, 63.168030f, -97.039124f));
            p19->AddVertex(tVec3f(59.951378f, 63.168030f, -13.391094f));
            p19->AddVertex(tVec3f(74.431824f, 63.168026f, -97.039124f));
            p19->AddVertex(tVec3f(59.951359f, 63.168030f, -13.390985f));
            p19->AddVertex(tVec3f(59.951363f, 63.168026f, -13.391014f));
            p19->AddVertex(tVec3f(59.951366f, 63.168030f, -13.391017f));
            p19->AddVertex(tVec3f(59.951378f, 63.168026f, -13.391098f));
            p19->AddVertex(tVec3f(-42.801273f, 63.168030f, 87.083420f));
            p19->AddVertex(tVec3f(-44.512177f, 63.168030f, 86.934158f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168030f, -97.038834f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168030f, 59.653152f));
            p19->AddVertex(tVec3f(-87.468903f, 63.168030f, 75.058762f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168030f, 70.659676f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168030f, 70.659668f));
            p19->AddVertex(tVec3f(-87.468880f, 63.168030f, 75.058762f));
            p19->AddVertex(tVec3f(-44.512161f, 63.168030f, 86.934151f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168030f, 24.951511f));
            p19->AddVertex(tVec3f(-97.039207f, 63.168026f, -8.2764320f));
            p19->AddVertex(tVec3f(74.431717f, 63.168030f, -97.039207f));
            p19->AddVertex(tVec3f(-97.039200f, 63.168026f, -97.039207f));

            vmath::Polygon3d* p20 = new vmath::Polygon3d;
            p20->AddVertex(tVec3f(-97.039207f, 63.168030f, 70.659676f));
            p20->AddVertex(tVec3f(-97.039207f, -0.099868774f, -97.039207f));
            p20->AddVertex(tVec3f(-97.039207f, -0.099906921f, -97.039207f));
            p20->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039207f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168026f, -97.039207f));
            p20->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.039093f));
            p20->AddVertex(tVec3f(-97.039207f, -0.10000066f, -97.031891f));
            p20->AddVertex(tVec3f(-97.039207f, -0.10000066f, 32.123543f));
            p20->AddVertex(tVec3f(-97.039200f, 63.168026f, -97.039207f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168026f, -97.039078f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168030f, -97.038834f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168030f, 59.653152f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168030f, 70.659668f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168030f, 24.951511f));
            p20->AddVertex(tVec3f(-97.039207f, 63.168026f, -8.2764320f));
            p20->AddVertex(tVec3f(-97.039207f, -0.10000610f, 32.123699f));


            bodyB.Add(p1);
            bodyB.Add(p2);
            bodyB.Add(p3);
            bodyB.Add(p4);
            bodyB.Add(p5);
            bodyB.Add(p6);
            bodyB.Add(p7);
            bodyB.Add(p8);
            bodyB.Add(p9);
            bodyB.Add(p10);
            bodyB.Add(p11);
            bodyB.Add(p12);
            bodyB.Add(p13);
            bodyB.Add(p14);
            bodyB.Add(p15);
            bodyB.Add(p16);
            bodyB.Add(p17);
            bodyB.Add(p18);
            bodyB.Add(p19);
            bodyB.Add(p20);

            vmath::PolygonBody::tVertexArray uniqueVertices;
            uniqueVertices.push_back(tVec3f(15.269290f, -0.099920020f, 83.747429f));
            uniqueVertices.push_back(tVec3f(41.842957f, 14.897432f, 95.766670f));
            uniqueVertices.push_back(tVec3f(-44.512161f, 63.168030f, 86.934151f));
            uniqueVertices.push_back(tVec3f(-87.468880f, 63.168030f, 75.058762f));
            uniqueVertices.push_back(tVec3f(-79.515152f, -0.10000066f, 40.178802f));
            uniqueVertices.push_back(tVec3f(-87.468903f, 63.168030f, 75.058762f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168030f, 70.659676f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.10000610f, 32.123699f));
            uniqueVertices.push_back(tVec3f(41.800472f, 16.050735f, 95.731934f));
            uniqueVertices.push_back(tVec3f(-42.801273f, 63.168030f, 87.083420f));
            uniqueVertices.push_back(tVec3f(-44.512177f, 63.168030f, 86.934158f));
            uniqueVertices.push_back(tVec3f(39.048035f, -0.10000066f, 70.328667f));
            uniqueVertices.push_back(tVec3f(-79.515152f, -0.10000066f, 40.178799f));
            uniqueVertices.push_back(tVec3f(59.951366f, 63.168030f, -13.391017f));
            uniqueVertices.push_back(tVec3f(49.097382f, -0.099998474f, 64.657608f));
            uniqueVertices.push_back(tVec3f(77.088989f, -0.10000066f, -97.039063f));
            uniqueVertices.push_back(tVec3f(59.951378f, 63.168026f, -13.391098f));
            uniqueVertices.push_back(tVec3f(59.951359f, 63.168030f, -13.390985f));
            uniqueVertices.push_back(tVec3f(43.205029f, 14.926052f, 95.049591f));
            uniqueVertices.push_back(tVec3f(49.097359f, -0.10000038f, 64.657722f));
            uniqueVertices.push_back(tVec3f(49.097382f, -0.10000066f, 64.657608f));
            uniqueVertices.push_back(tVec3f(59.951363f, 63.168026f, -13.391014f));
            uniqueVertices.push_back(tVec3f(77.088989f, -0.099998474f, -97.039063f));
            uniqueVertices.push_back(tVec3f(77.089012f, -0.10000066f, -97.039177f));
            uniqueVertices.push_back(tVec3f(74.431824f, 63.168026f, -97.039124f));
            uniqueVertices.push_back(tVec3f(59.951378f, 63.168030f, -13.391094f));
            uniqueVertices.push_back(tVec3f(74.963264f, 50.514450f, -97.039207f));
            uniqueVertices.push_back(tVec3f(74.431824f, 63.168030f, -97.039207f));
            uniqueVertices.push_back(tVec3f(74.431824f, 63.168030f, -97.039124f));
            uniqueVertices.push_back(tVec3f(77.089012f, -0.099998474f, -97.039177f));
            uniqueVertices.push_back(tVec3f(77.089012f, -0.10000229f, -97.039177f));
            uniqueVertices.push_back(tVec3f(77.088982f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(tVec3f(59.951359f, 63.168030f, -13.390984f));
            uniqueVertices.push_back(tVec3f(43.162521f, 16.079493f, 95.014954f));
            uniqueVertices.push_back(tVec3f(59.951359f, 63.168030f, -13.390976f));
            uniqueVertices.push_back(tVec3f(-41.604263f, 63.168030f, 86.480789f));
            uniqueVertices.push_back(tVec3f(-41.604271f, 63.168030f, 86.480789f));
            uniqueVertices.push_back(tVec3f(-42.801300f, 63.168030f, 87.083412f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.099906921f, -97.039207f));
            uniqueVertices.push_back(tVec3f(-32.317986f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168026f, -97.039207f));
            uniqueVertices.push_back(tVec3f(74.431717f, 63.168030f, -97.039207f));
            uniqueVertices.push_back(tVec3f(7.4377823f, -0.099998474f, -97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.099868774f, -97.039207f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.10000066f, -97.039093f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.10000066f, -97.031891f));
            uniqueVertices.push_back(tVec3f(-97.039207f, -0.10000066f, 32.123543f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168026f, -97.039078f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168030f, -97.038834f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168030f, 59.653152f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168030f, 70.659668f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168030f, 24.951511f));
            uniqueVertices.push_back(tVec3f(-97.039207f, 63.168026f, -8.2764320f));
            uniqueVertices.push_back(tVec3f(-97.039200f, 63.168026f, -97.039207f));
            bodyB.SetVertexArray(uniqueVertices);

            std::vector<tVec3f> corners;
            corners.push_back(tVec3f(41.842922f, 14.897396f, 95.766586f));
            corners.push_back(tVec3f(43.205051f, 14.926048f, 95.049522f));
            corners.push_back(tVec3f(43.162594f, 16.079441f, 95.014961f));
            corners.push_back(tVec3f(41.800465f, 16.050791f, 95.732025f));
            corners.push_back(tVec3f(-223.21036f, -134.69102f, -24.116596f));
            corners.push_back(tVec3f(99.215935f, -127.90880f, -193.85019f));
            corners.push_back(tVec3f(89.165848f, 145.10817f, -202.03113f));
            corners.push_back(tVec3f(-233.26044f, 138.32594f, -32.297531f));

            std::vector<vmath::Plane*> planes;
            vmath::Plane* pl1 = new vmath::Plane(tVec3f(0.46465811f, 0.043610103f, 0.88441563f), 105.28873f);
            vmath::Plane* pl2 = new vmath::Plane(tVec3f(-0.46466947f, -0.043610398f, -0.88440967f), 130.91943f);
            vmath::Plane* pl3 = new vmath::Plane(tVec3f(-0.41762245f, 0.011855224f, 0.90854329f), 69.710159f);
            vmath::Plane* pl4 = new vmath::Plane(tVec3f(0.98450172f, 0.041348580f, 0.17043072f), 59.351971f);
            vmath::Plane* pl5 = new vmath::Plane(tVec3f(0.26417196f, -0.84324867f, 0.46812919f), 43.322651f);
            vmath::Plane* pl6 = new vmath::Plane(tVec3f(0.20048171f, 0.88685942f, 0.41627806f), 62.466160f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum camFrust(corners, planes);

            corners.clear();
            planes.clear();

            corners.push_back(tVec3f(-100.74258f, 48.496494f, 169.63185f));
            corners.push_back(tVec3f(-15.191692f, 201.51694f, 20.882317f));
            corners.push_back(tVec3f(-104.62428f, 81.718758f, -153.79123f));
            corners.push_back(tVec3f(-190.17516f, -71.301689f, -5.0417075f));
            corners.push_back(tVec3f(77.065994f, -70.928787f, 226.25410f));
            corners.push_back(tVec3f(199.79324f, 148.58707f, 12.865096f));
            corners.push_back(tVec3f(71.497513f, -23.269722f, -237.71329f));
            corners.push_back(tVec3f(-51.229736f, -242.78558f, -24.324276f));

            pl1 = new vmath::Plane(tVec3f(-0.84275466f, 0.53435856f, 0.065004379f), 234.18739f);
            pl2 = new vmath::Plane(tVec3f(0.84275466f, -0.53435856f, -0.065004379f), 88.141632f);
            pl3 = new vmath::Plane(tVec3f(-0.55704284f, -0.52381212f, 0.64445645f), 140.03523f);
            pl4 = new vmath::Plane(tVec3f(0.16694947f, 0.77115542f, -0.61436731f), 140.03522f);
            pl5 = new vmath::Plane(tVec3f(0.18337426f, 0.63058019f, 0.75415015f), 140.03522f);
            pl6 = new vmath::Plane(tVec3f(-0.57346767f, -0.38323686f, -0.72406101f), 140.03525f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum lightFrust(corners, planes);

            vmath::BoundingBox sceneAABB(tVec3f(-97.039207f, -0.10000066f, -97.039207f), tVec3f(97.039207f, 63.168030f, 97.039207f));

            tVec2f zRange(1.0000000f, 236.70729f);

            tMat4f liSPMatrix = liSP.GetLiSPMtx(
                                        0,                  // unsigned int        split,
                                        bodyB,              // const PolygonBody&  bodyB,
                                        camFrust,           // const Frustum&      camFrust, 
                                        &lightFrust,        // const Frustum*      lightFrust, 
                                        sceneAABB,          // const BoundingBox&  sceneAABB,
                                        zRange              // const tVec2f&       zRange
                                );
            //
            //              [0.104373, -0.044428,  0.000000, -0.004013]
            // liSPMatrix = [0.419552,  0.985628,  0.000000,  0.745498]
            //              [0.000000,  0.000000,  0.113435, -0.085598]
            //              [0.391662,  0.920109,  0.000000,  0.809377]
            //

            int ijk = 234;
        }

        // LiSP test III
        {
            vmath::LiSP liSP(1);

            liSP.SetMode(vmath::LiSP::Reparametrized);
            liSP.SetArbScaled(false);
            liSP.SetParamN(140.98463f, 0);
            liSP.SetSplitParam(0.5f);

            tMat4f matLightProj(
                0.057911590f, 0.00000000f,  0.00000000f,  0.00000000f,
                0.00000000f,  0.057911590f, 0.00000000f,  0.00000000f,
                0.00000000f,  0.00000000f, -1.0347396f, -35.843311f,
                0.00000000f,  0.00000000f, -1.0000000f,   0.00000000f);
            liSP.SetLightProjMat(matLightProj, vmath::Projection::Perspective);

            tMat4f matLightView(
                 0.31544900f,  0.25865412f, -0.91301143f,   -4.5831375e-006f,
                -0.35206801f, -0.86156631f, -0.36572069f,    2.9790876e-006f,
                -0.88121516f,  0.43680838f, -0.18071641f, -605.06201f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            vmath::View viewLightView(
                tVec3f(-533.18976f, 264.29614f, -109.34463f),
                tVec3f(0.00000000f, 0.00000000f, 0.00000000f),
                tVec3f(9.0862562e-009f, -0.38229418f, -0.92404062f));

            liSP.SetLightView(matLightView, viewLightView);

            tMat4f matCamView(
                 0.69921154f, 0.017653238f, -0.71469688f,   -3.6979961f,
                -0.26234373f, 0.93628949f,  -0.23353288f,  -87.327797f,
                 0.66504055f, 0.35078511f,   0.65929562f, -172.59473f,
                 0.00000000f, 0.00000000f,   0.00000000f,    1.0000000f);

            vmath::View viewCamView(
                tVec3f(94.458290f, 142.37306f, 90.754105f),
                tVec3f(93.793251f, 142.02228f, 90.094810f),
                tVec3f (-0.016558312f, 0.99982685f, 0.0084964950f)
                );

            liSP.SetCamView(matCamView, viewCamView);

            tMat4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f,   0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f,   0.00000000f,
                0.00000000f, 0.00000000f, -1.2454509f, -175.58943f,
                0.00000000f, 0.00000000f, -1.0000000f,    0.00000000f);

            liSP.SetCamProjMat(matCamProj);

            liSP.SetFieldOfView(60.000000f);
            liSP.SetGamma(56.498173f);
            liSP.SetSplitParam(0.50000000f);
            liSP.SetPseudoNear(0.12000000f);
            liSP.SetPseudoFar(0.19000000f);

            // Artificially construct a PolygonBody for the test
            vmath::PolygonBody bodyB;

            vmath::Polygon3d* p1 = new vmath::Polygon3d;
            p1->AddVertex(tVec3f(40.567329f, -0.099960543f, -422.14844f));
            p1->AddVertex(tVec3f(69.083717f, -0.099999905f, -255.43610f));
            p1->AddVertex(tVec3f(-316.82861f, -0.099999905f, -422.14835f));
            p1->AddVertex(tVec3f(-147.22157f, -0.099981226f, -422.14844f));

            vmath::Polygon3d* p2 = new vmath::Polygon3d;
            p2->AddVertex(tVec3f(-147.22159f, -0.099981226f, -422.14844f));
            p2->AddVertex(tVec3f(-316.82861f, -0.099999905f, -422.14835f));
            p2->AddVertex(tVec3f(-397.60672f, -0.099999905f, -422.14835f));
            p2->AddVertex(tVec3f(-397.60672f, -0.099945091f, -422.14844f));

            vmath::Polygon3d* p3 = new vmath::Polygon3d;
            p3->AddVertex(tVec3f(-397.60669f, 206.36839f, 2.1476247f));
            p3->AddVertex(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            p3->AddVertex(tVec3f(-397.60672f, 234.15105f, -57.891682f));
            p3->AddVertex(tVec3f(-397.60672f, 206.36841f, 2.1475983f));

            vmath::Polygon3d* p4 = new vmath::Polygon3d;
            p4->AddVertex(tVec3f(69.083725f, -0.099999905f, -255.43610f));
            p4->AddVertex(tVec3f(40.567333f, -0.099960543f, -422.14844f));
            p4->AddVertex(tVec3f(1.3627319f, 164.95033f, -422.14844f));
            p4->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p4->AddVertex(tVec3f(98.463730f, -0.099990845f, -83.674805f));

            vmath::Polygon3d* p5 = new vmath::Polygon3d;
            p5->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p5->AddVertex(tVec3f(-397.60672f, 261.17880f, -422.14838f));
            p5->AddVertex(tVec3f(-397.60672f, 252.77078f, -190.67180f));

            vmath::Polygon3d* p6 = new vmath::Polygon3d;
            p6->AddVertex(tVec3f(-131.61452f, -0.099999905f, 85.536140f));
            p6->AddVertex(tVec3f(-97.820648f, -0.099999905f, 90.713882f));
            p6->AddVertex(tVec3f(-71.140770f, -0.099992089f, 94.801651f));

            vmath::Polygon3d* p7 = new vmath::Polygon3d;
            p7->AddVertex(tVec3f(-397.60672f, 206.36835f, 2.1476340f));
            p7->AddVertex(tVec3f(-397.60672f, 206.36818f, 2.1476779f));
            p7->AddVertex(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            p7->AddVertex(tVec3f(-397.60669f, 206.36839f, 2.1476247f));

            vmath::Polygon3d* p8 = new vmath::Polygon3d;
            p8->AddVertex(tVec3f(-397.60669f, 206.36839f, 2.1476247f));
            p8->AddVertex(tVec3f(-397.60672f, 206.36841f, 2.1475997f));
            p8->AddVertex(tVec3f(-397.60672f, 206.36835f, 2.1476340f));

            vmath::Polygon3d* p9 = new vmath::Polygon3d;
            p9->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p9->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p9->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p9->AddVertex(tVec3f(1.3627319f, 164.95032f, -422.14844f));

            vmath::Polygon3d* p10 = new vmath::Polygon3d;
            p10->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p10->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p10->AddVertex(tVec3f(-397.60672f, 261.17880f, -422.14838f));

            vmath::Polygon3d* p11 = new vmath::Polygon3d;
            p11->AddVertex(tVec3f(-397.60672f, 206.36815f, 2.1476860f));
            p11->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            p11->AddVertex(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            p11->AddVertex(tVec3f(-397.60672f, 206.36818f, 2.1476784f));

            vmath::Polygon3d* p12 = new vmath::Polygon3d;
            p12->AddVertex(tVec3f(97.937340f, 18.622017f, -60.753471f));
            p12->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            p12->AddVertex(tVec3f(98.463333f, -0.099999428f, -83.674263f));
            p12->AddVertex(tVec3f(98.463753f, -0.099999905f, -83.674698f));

            vmath::Polygon3d* p13 = new vmath::Polygon3d;
            p13->AddVertex(tVec3f(-71.140770f, -0.099992089f, 94.801651f));
            p13->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            p13->AddVertex(tVec3f(-397.60599f, -0.10000038f, 44.782143f));
            p13->AddVertex(tVec3f(-131.61453f, -0.099999905f, 85.536140f));

            vmath::Polygon3d* p14 = new vmath::Polygon3d;
            p14->AddVertex(tVec3f(-397.60672f, -0.10000563f, 44.782028f));
            p14->AddVertex(tVec3f(-397.60599f, -0.099999905f, 44.782143f));
            p14->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            p14->AddVertex(tVec3f(-397.60672f, 206.36815f, 2.1476822f));

            vmath::Polygon3d* p15 = new vmath::Polygon3d;
            p15->AddVertex(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            p15->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p15->AddVertex(tVec3f(-397.60672f, 242.80931f, -106.90833f));
            p15->AddVertex(tVec3f(-397.60672f, 234.15105f, -57.891685f));

            vmath::Polygon3d* p16 = new vmath::Polygon3d;
            p16->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p16->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p16->AddVertex(tVec3f(-397.60675f, 252.77078f, -190.67180f));
            p16->AddVertex(tVec3f(-397.60672f, 242.80930f, -106.90832f));

            vmath::Polygon3d* p17 = new vmath::Polygon3d;
            p17->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p17->AddVertex(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            p17->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));

            vmath::Polygon3d* p18 = new vmath::Polygon3d;
            p18->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p18->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            p18->AddVertex(tVec3f(97.937340f, 18.622017f, -60.753471f));

            vmath::Polygon3d* p19 = new vmath::Polygon3d;
            p19->AddVertex(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            p19->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p19->AddVertex(tVec3f(98.463745f, -0.099990845f, -83.674759f));
            p19->AddVertex(tVec3f(98.463730f, -0.099999905f, -83.674812f));

            vmath::Polygon3d* p20 = new vmath::Polygon3d;
            p20->AddVertex(tVec3f(98.463753f, -0.10000038f, -83.674698f));
            p20->AddVertex(tVec3f(98.463745f, -0.099999905f, -83.674751f));
            p20->AddVertex(tVec3f(55.229015f, 171.04536f, -98.771553f));
            p20->AddVertex(tVec3f(97.937340f, 18.622017f, -60.753471f));

            vmath::Polygon3d* p21 = new vmath::Polygon3d;
            p21->AddVertex(tVec3f(-71.140549f, -0.10000038f, 94.801521f));
            p21->AddVertex(tVec3f(98.463341f, -0.099999905f, -83.674263f));
            p21->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));

            vmath::Polygon3d* p22 = new vmath::Polygon3d;
            p22->AddVertex(tVec3f(-71.140770f, -0.099992089f, 94.801651f));
            p22->AddVertex(tVec3f(-71.140747f, -0.099999905f, 94.801636f));
            p22->AddVertex(tVec3f(-71.140549f, -0.099999905f, 94.801521f));
            p22->AddVertex(tVec3f(-53.833496f, 14.790224f, 94.378685f));

            vmath::Polygon3d* p23 = new vmath::Polygon3d;
            p23->AddVertex(tVec3f(-71.140747f, -0.099999905f, 94.801636f));
            p23->AddVertex(tVec3f(-71.140770f, -0.099992089f, 94.801651f));
            p23->AddVertex(tVec3f(-97.820633f, -0.099999905f, 90.713882f));

            vmath::Polygon3d* p24 = new vmath::Polygon3d;
            p24->AddVertex(tVec3f(-397.60672f, -0.099945091f, -422.14844f));
            p24->AddVertex(tVec3f(40.567333f, -0.099960543f, -422.14844f));
            p24->AddVertex(tVec3f(1.3627319f, 164.95033f, -422.14844f));
            p24->AddVertex(tVec3f(1.3627319f, 164.95032f, -422.14844f));
            p24->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p24->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p24->AddVertex(tVec3f(40.567329f, -0.099960543f, -422.14844f));
            p24->AddVertex(tVec3f(-147.22157f, -0.099981226f, -422.14844f));
            p24->AddVertex(tVec3f(-147.22159f, -0.099981226f, -422.14844f));
            p24->AddVertex(tVec3f(-397.60672f, -0.099945091f, -422.14844f));

            vmath::Polygon3d* p25 = new vmath::Polygon3d;
            p25->AddVertex(tVec3f(-71.140549f, -0.10000038f, 94.801521f));
            p25->AddVertex(tVec3f(98.463745f, -0.099999905f, -83.674751f));
            p25->AddVertex(tVec3f(98.463730f, -0.099999905f, -83.674812f));
            p25->AddVertex(tVec3f(98.463745f, -0.099990845f, -83.674759f));
            p25->AddVertex(tVec3f(-397.60672f, -0.10000610f, 44.782013f));
            p25->AddVertex(tVec3f(-397.60672f, -0.10000610f, 44.782028f));
            p25->AddVertex(tVec3f(-131.61453f, -0.099999905f, 85.536140f));
            p25->AddVertex(tVec3f(-397.60599f, -0.10000038f, 44.782143f));
            p25->AddVertex(tVec3f(98.463753f, -0.099999905f, -83.674698f));
            p25->AddVertex(tVec3f(98.463333f, -0.099999428f, -83.674263f));
            p25->AddVertex(tVec3f(-397.60669f, -0.099999905f, 44.781990f));
            p25->AddVertex(tVec3f(-397.60672f, -0.099999905f, 44.782024f));
            p25->AddVertex(tVec3f(-97.820648f, -0.099999905f, 90.713882f));
            p25->AddVertex(tVec3f(-131.61452f, -0.099999905f, 85.536140f));
            p25->AddVertex(tVec3f(69.083725f, -0.099999905f, -255.43610f));
            p25->AddVertex(tVec3f(98.463730f, -0.099990845f, -83.674805f));
            p25->AddVertex(tVec3f(-397.60669f, -0.099999905f, -422.14828f));
            p25->AddVertex(tVec3f(-397.60672f, -0.099999905f, -422.14835f));
            p25->AddVertex(tVec3f(-316.82861f, -0.099999905f, -422.14835f));
            p25->AddVertex(tVec3f(69.083717f, -0.099999905f, -255.43610f));
            p25->AddVertex(tVec3f(-97.820633f, -0.099999905f, 90.713882f));
            p25->AddVertex(tVec3f(-71.140747f, -0.099999905f, 94.801636f));
            p25->AddVertex(tVec3f(98.463341f, -0.099999905f, -83.674263f));

            vmath::Polygon3d* p26 = new vmath::Polygon3d;
            p26->AddVertex(tVec3f(-397.60672f, -0.099999905f, -422.14835f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36841f, 2.1475983f));
            p26->AddVertex(tVec3f(-397.60672f, 234.15105f, -57.891682f));
            p26->AddVertex(tVec3f(-397.60672f, 252.77078f, -190.67180f));
            p26->AddVertex(tVec3f(-397.60672f, 261.17880f, -422.14838f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36835f, 2.1476340f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36818f, 2.1476779f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36841f, 2.1475997f));
            p26->AddVertex(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36815f, 2.1476860f));
            p26->AddVertex(tVec3f(-397.60672f, 206.36815f, 2.1476822f));
            p26->AddVertex(tVec3f(-397.60672f, -0.10000563f, 44.782028f));
            p26->AddVertex(tVec3f(-397.60672f, 234.15105f, -57.891685f));
            p26->AddVertex(tVec3f(-397.60672f, 242.80931f, -106.90833f));
            p26->AddVertex(tVec3f(-397.60672f, 242.80930f, -106.90832f));
            p26->AddVertex(tVec3f(-397.60675f, 252.77078f, -190.67180f));
            p26->AddVertex(tVec3f(-397.60672f, -0.10000610f, 44.782013f));
            p26->AddVertex(tVec3f(-397.60669f, -0.099999905f, 44.781990f));
            p26->AddVertex(tVec3f(-397.60672f, -0.099999905f, 44.782024f));
            p26->AddVertex(tVec3f(-397.60669f, -0.099999905f, -422.14828f));
            p26->AddVertex(tVec3f(-397.60672f, -0.099945091f, -422.14844f));

            bodyB.Add(p1);
            bodyB.Add(p2);
            bodyB.Add(p3);
            bodyB.Add(p4);
            bodyB.Add(p5);
            bodyB.Add(p6);
            bodyB.Add(p7);
            bodyB.Add(p8);
            bodyB.Add(p9);
            bodyB.Add(p10);
            bodyB.Add(p11);
            bodyB.Add(p12);
            bodyB.Add(p13);
            bodyB.Add(p14);
            bodyB.Add(p15);
            bodyB.Add(p16);
            bodyB.Add(p17);
            bodyB.Add(p18);
            bodyB.Add(p19);
            bodyB.Add(p20);
            bodyB.Add(p21);
            bodyB.Add(p22);
            bodyB.Add(p23);
            bodyB.Add(p24);
            bodyB.Add(p25);
            bodyB.Add(p26);

            vmath::PolygonBody::tVertexArray uniqueVertices;
            uniqueVertices.push_back(tVec3f(40.567329f, -0.099960543f, -422.14844f));
            uniqueVertices.push_back(tVec3f(69.083717f, -0.099999905f, -255.43610f));
            uniqueVertices.push_back(tVec3f(-316.82861f, -0.099999905f, -422.14835f));
            uniqueVertices.push_back(tVec3f(-147.22157f, -0.099981226f, -422.14844f));
            uniqueVertices.push_back(tVec3f(-147.22159f, -0.099981226f, -422.14844f));
            uniqueVertices.push_back(tVec3f(-397.60672f, -0.099999905f, -422.14835f));
            uniqueVertices.push_back(tVec3f(-397.60672f, -0.099945091f, -422.14844f));
            uniqueVertices.push_back(tVec3f(-397.60669f, 206.36839f, 2.1476247f));
            uniqueVertices.push_back(tVec3f(-96.541801f, 167.21341f, 56.360508f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 234.15105f, -57.891682f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36841f, 2.1475983f));
            uniqueVertices.push_back(tVec3f(69.083725f, -0.099999905f, -255.43610f));
            uniqueVertices.push_back(tVec3f(40.567333f, -0.099960543f, -422.14844f));
            uniqueVertices.push_back(tVec3f(1.3627319f, 164.95033f, -422.14844f));
            uniqueVertices.push_back(tVec3f(-11.705462f, 219.96709f, -422.14841f));
            uniqueVertices.push_back(tVec3f(98.463730f, -0.099990845f, -83.674805f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 261.17880f, -422.14838f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 252.77078f, -190.67180f));
            uniqueVertices.push_back(tVec3f(-131.61452f, -0.099999905f, 85.536140f));
            uniqueVertices.push_back(tVec3f(-97.820648f, -0.099999905f, 90.713882f));
            uniqueVertices.push_back(tVec3f(-71.140770f, -0.099992089f, 94.801651f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36835f, 2.1476340f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36818f, 2.1476779f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36841f, 2.1475997f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 261.17877f, -422.14844f));
            uniqueVertices.push_back(tVec3f(1.3627319f, 164.95032f, -422.14844f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36815f, 2.1476860f));
            uniqueVertices.push_back(tVec3f(-53.833496f, 14.790224f, 94.378685f));
            uniqueVertices.push_back(tVec3f(97.937340f, 18.622017f, -60.753471f));
            uniqueVertices.push_back(tVec3f(98.463333f, -0.099999428f, -83.674263f));
            uniqueVertices.push_back(tVec3f(98.463753f, -0.099999905f, -83.674698f));
            uniqueVertices.push_back(tVec3f(-397.60599f, -0.10000038f, 44.782143f));
            uniqueVertices.push_back(tVec3f(-131.61453f, -0.099999905f, 85.536140f));
            uniqueVertices.push_back(tVec3f(-397.60672f, -0.10000563f, 44.782028f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 206.36815f, 2.1476822f));
            uniqueVertices.push_back(tVec3f(55.229015f, 171.04536f, -98.771553f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 242.80931f, -106.90833f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 234.15105f, -57.891685f));
            uniqueVertices.push_back(tVec3f(-397.60675f, 252.77078f, -190.67180f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 242.80930f, -106.90832f));
            uniqueVertices.push_back(tVec3f(98.463745f, -0.099990845f, -83.674759f));
            uniqueVertices.push_back(tVec3f(98.463730f, -0.099999905f, -83.674812f));
            uniqueVertices.push_back(tVec3f(98.463745f, -0.099999905f, -83.674751f));
            uniqueVertices.push_back(tVec3f(-71.140549f, -0.10000038f, 94.801521f));
            uniqueVertices.push_back(tVec3f(98.463341f, -0.099999905f, -83.674263f));
            uniqueVertices.push_back(tVec3f(-71.140747f, -0.099999905f, 94.801636f));
            uniqueVertices.push_back(tVec3f(-97.820633f, -0.099999905f, 90.713882f));
            uniqueVertices.push_back(tVec3f(-397.60672f, -0.10000610f, 44.782013f));
            uniqueVertices.push_back(tVec3f(-397.60669f, -0.099999905f, 44.781990f));
            uniqueVertices.push_back(tVec3f(-397.60672f, -0.099999905f, 44.782024f));
            uniqueVertices.push_back(tVec3f(-397.60669f, -0.099999905f, -422.14828f));
            bodyB.SetVertexArray(uniqueVertices);

            std::vector<tVec3f> corners;
            corners.push_back(tVec3f(-53.833530f, 14.790188f, 94.378601f));
            corners.push_back(tVec3f(97.937363f, 18.622013f, -60.753536f));
            corners.push_back(tVec3f(55.229088f, 171.04532f, -98.771545f));
            corners.push_back(tVec3f(-96.541809f, 167.21347f, 56.360600f));
            corners.push_back(tVec3f(-657.99438f, -504.99973f, 109.14530f));
            corners.push_back(tVec3f(112.11162f, -485.55685f, -678.01648f));
            corners.push_back(tVec3f(-104.59605f, 287.86002f, -870.92511f));
            corners.push_back(tVec3f(-874.70184f, 268.41663f, -83.763161f));

            std::vector<vmath::Plane*> planes;
            vmath::Plane* pl1 = new vmath::Plane(tVec3f(0.66504061f, 0.35078523f, 0.65929568f), 94.396889f);
            vmath::Plane* pl2 = new vmath::Plane(tVec3f(-0.66504079f, -0.35078505f, -0.65929550f), 542.78040f);
            vmath::Plane* pl3 = new vmath::Plane(tVec3f(-0.14838839f, 0.19998839f, 0.96849650f), 102.35148f);
            vmath::Plane* pl4 = new vmath::Plane(tVec3f(0.95973027f, 0.22796552f, -0.16416341f), 108.21213f);
            vmath::Plane* pl5 = new vmath::Plane(tVec3f(0.55971670f, -0.63545793f, 0.53189331f), 10.669267f);
            vmath::Plane* pl6 = new vmath::Plane(tVec3f(0.10532385f, 0.98624313f, 0.12740240f), 161.92548f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum camFrust(corners, planes);

            corners.clear();
            planes.clear();

            corners.push_back(tVec3f(-480.76080f, 609.79846f, 661.79242f));
            corners.push_back(tVec3f(-103.38708f, 919.22845f, -430.44873f));
            corners.push_back(tVec3f(-524.56805f, -111.46828f, -867.96173f));
            corners.push_back(tVec3f(-901.94165f, -420.89801f, 224.27936f));
            corners.push_back(tVec3f(1028.4377f, 10555.295f, 22859.447f));
            corners.push_back(tVec3f(12268.816f, 19771.967f, -9673.6797f));
            corners.push_back(tVec3f(-276.38898f, -10928.076f, -22705.219f));
            corners.push_back(tVec3f(-11516.631f, -20144.518f, 9827.7939f));

            pl1 = new vmath::Plane(tVec3f(-0.88121516f, 0.43680823f, -0.18071634f), 587.44617f);
            pl2 = new vmath::Plane(tVec3f(0.88121516f, -0.43680805f, 0.18071660f), 426.71161f);
            pl3 = new vmath::Plane(tVec3f(-0.89797878f, 0.42112353f, -0.12762856f), 604.04993f);
            pl4 = new vmath::Plane(tVec3f(-0.86150360f, 0.45103163f, -0.23319952f), 604.04993f);
            pl5 = new vmath::Plane(tVec3f(-0.85938650f, 0.48588881f, -0.15926999f), 604.04999f);
            pl6 = new vmath::Plane(tVec3f(-0.90009588f, 0.38626632f, -0.20155811f), 604.04987f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum lightFrust(corners, planes);

            vmath::BoundingBox sceneAABB(tVec3f(-397.60672f, -0.099999905f, -422.14844f), tVec3f(397.60669f, 329.10513f, 422.14844f));

            tVec2f zRange(140.98463f, 715.37512f);

            tMat4f liSPMatrix = liSP.GetLiSPMtx(
                                        0,                  // unsigned int        split,
                                        bodyB,              // const PolygonBody&  bodyB,
                                        camFrust,           // const Frustum&      camFrust, 
                                        &lightFrust,        // const Frustum*      lightFrust, 
                                        sceneAABB,          // const BoundingBox&  sceneAABB,
                                        zRange              // const tVec2f&       zRange
                                );
            //
            //              [0.109617, -0.054687,  0.000000, -0.000741]
            // liSPMatrix = [0.705244,  1.413626,  0.000000,  0.037487]
            //              [0.000000,  0.000000,  0.122501, -0.118981]
            //              [0.446419,  0.894824,  0.000000,  0.146230]
            //

            int ijk = 234;
        }

        // LiSP test IV
        {
            vmath::LiSP liSP(2);

            liSP.SetMode(vmath::LiSP::Arbitrary);
            liSP.SetArbScaled(false);
            liSP.SetParamN(324.27762f, 0);
            liSP.SetParamN(1.0000000f, 1);
            liSP.SetSplitParam(0.5f);

            tMat4f matLightProj(
                0.057911590f, 0.00000000f,  0.00000000f,  0.00000000f,
                0.00000000f,  0.057911590f, 0.00000000f,  0.00000000f,
                0.00000000f,  0.00000000f, -1.0347396f, -35.843311f,
                0.00000000f,  0.00000000f, -1.0000000f,   0.00000000f);
            liSP.SetLightProjMat(matLightProj, vmath::Projection::Perspective);

            tMat4f matLightView(
                0.33558467f,  0.30881563f, -0.88995260f,   -5.5088717e-006f,
                -0.33293071f, -0.84488535f, -0.41871920f,   -3.2874848e-006f,
                -0.88121516f,  0.43680838f, -0.18071641f, -605.06201f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            vmath::View viewLightView(
                tVec3f(-533.18976f, 264.29614f, -109.34463f),
                tVec3f(0.00000000f, 0.00000000f, 0.00000000f),
                tVec3f(9.0862562e-009f, -0.38229418f, -0.92404062f));

            liSP.SetLightView(matLightView, viewLightView);

            tMat4f matCamView(
                 0.76445252f, 0.018136535f, -0.64442474f,  -16.306841f,
                -0.23731807f, 0.93732780f,  -0.25513998f,  -87.878571f,
                 0.59941000f, 0.34797609f,   0.72084683f, -171.58147f,
                 0.00000000f, 0.00000000f,   0.00000000f,    1.0000000f);

            vmath::View viewCamView(
                tVec3f(94.458290f, 142.37306f, 90.754105f),
                tVec3f(93.858879f, 142.02509f, 90.033257f),
                tVec3f (-0.016558312f, 0.99982685f, 0.0084964950f)
                );

            liSP.SetCamView(matCamView, viewCamView);

            tMat4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f,   0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f,   0.00000000f,
                0.00000000f, 0.00000000f, -1.5293325f, -198.09848f,
                0.00000000f, 0.00000000f, -1.0000000f,    0.00000000f);

            liSP.SetCamProjMat(matCamProj);

            liSP.SetFieldOfView(60.000000f);
            liSP.SetGamma(59.570404f);
            liSP.SetSplitParam(0.50000000f);
            liSP.SetPseudoNear(0.12000000f);
            liSP.SetPseudoFar(0.19000000f);

            // Artificially construct a PolygonBody for the test
            vmath::PolygonBody bodyB;

            vmath::Polygon3d* p1 = new vmath::Polygon3d;
            p1->AddVertex(tVec3f(39.089149f, 219.89795f, -419.79834f));
            p1->AddVertex(tVec3f(94.789619f, -0.10000610f, -359.91510f));
            p1->AddVertex(tVec3f(94.789391f, -0.099999905f, -359.91498f));
            p1->AddVertex(tVec3f(-397.60672f, 207.21199f, -163.44366f));
            p1->AddVertex(tVec3f(-397.60672f, 253.77744f, -182.89661f));

            vmath::Polygon3d* p2 = new vmath::Polygon3d;
            p2->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));
            p2->AddVertex(tVec3f(105.87453f, -0.099999905f, -208.11368f));
            p2->AddVertex(tVec3f(94.789619f, -0.099999905f, -359.91510f));
            p2->AddVertex(tVec3f(39.089149f, 219.89795f, -419.79834f));

            vmath::Polygon3d* p3 = new vmath::Polygon3d;
            p3->AddVertex(tVec3f(94.789429f, -0.10000610f, -359.91498f));
            p3->AddVertex(tVec3f(-348.32108f, -0.099999905f, 8.5473785f));
            p3->AddVertex(tVec3f(-397.60672f, 70.387497f, -22.882376f));
            p3->AddVertex(tVec3f(-397.60672f, 207.21201f, -163.44366f));

            vmath::Polygon3d* p4 = new vmath::Polygon3d;
            p4->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));
            p4->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));
            p4->AddVertex(tVec3f(39.089149f, 219.89795f, -419.79834f));

            vmath::Polygon3d* p5 = new vmath::Polygon3d;
            p5->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));
            p5->AddVertex(tVec3f(39.089149f, 219.89795f, -419.79834f));
            p5->AddVertex(tVec3f(-397.60672f, 253.77744f, -182.89659f));
            p5->AddVertex(tVec3f(-397.60672f, 243.10803f, -104.13360f));

            vmath::Polygon3d* p6 = new vmath::Polygon3d;
            p6->AddVertex(tVec3f(-77.159714f, 165.58900f, 42.558334f));
            p6->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));
            p6->AddVertex(tVec3f(-397.60672f, 243.10805f, -104.13360f));
            p6->AddVertex(tVec3f(-397.60672f, 234.94934f, -64.182037f));

            vmath::Polygon3d* p7 = new vmath::Polygon3d;
            p7->AddVertex(tVec3f(-77.159714f, 165.58900f, 42.558334f));
            p7->AddVertex(tVec3f(-397.60669f, 234.94936f, -64.182045f));
            p7->AddVertex(tVec3f(-397.60672f, 208.93826f, -47.432968f));

            vmath::Polygon3d* p8 = new vmath::Polygon3d;
            p8->AddVertex(tVec3f(-348.32104f, -0.10000610f, 8.5473785f));
            p8->AddVertex(tVec3f(-348.32104f, -0.099999905f, 8.5473833f));
            p8->AddVertex(tVec3f(-397.60669f, 194.56253f, -44.439548f));
            p8->AddVertex(tVec3f(-397.60672f, 194.56255f, -44.439564f));
            p8->AddVertex(tVec3f(-397.60672f, 70.387527f, -22.882401f));

            vmath::Polygon3d* p9 = new vmath::Polygon3d;
            p9->AddVertex(tVec3f(-397.60669f, 194.56253f, -44.439548f));
            p9->AddVertex(tVec3f(-397.60672f, 199.35445f, -45.437359f));
            p9->AddVertex(tVec3f(-397.60672f, 194.56255f, -44.439564f));

            vmath::Polygon3d* p10 = new vmath::Polygon3d;
            p10->AddVertex(tVec3f(-397.60672f, 208.93802f, -47.432915f));
            p10->AddVertex(tVec3f(-397.60672f, 199.35445f, -45.437359f));
            p10->AddVertex(tVec3f(-397.60669f, 194.56253f, -44.439548f));
            p10->AddVertex(tVec3f(-348.32104f, -0.099990845f, 8.5473824f));
            p10->AddVertex(tVec3f(-348.32104f, -0.099999905f, 8.5473833f));

            vmath::Polygon3d* p11 = new vmath::Polygon3d;
            p11->AddVertex(tVec3f(-192.92177f, -0.099999905f, 47.810863f));
            p11->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            p11->AddVertex(tVec3f(-232.79909f, -0.099999905f, 37.735397f));

            vmath::Polygon3d* p12 = new vmath::Polygon3d;
            p12->AddVertex(tVec3f(-293.50140f, -0.099999905f, 22.398239f));
            p12->AddVertex(tVec3f(-232.79910f, -0.099999905f, 37.735397f));
            p12->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            p12->AddVertex(tVec3f(-71.326195f, -0.099907897f, 78.533524f));

            vmath::Polygon3d* p13 = new vmath::Polygon3d;
            p13->AddVertex(tVec3f(-32.678337f, -0.099999905f, -23.474182f));
            p13->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            p13->AddVertex(tVec3f(-192.92177f, -0.099999905f, 47.810863f));

            vmath::Polygon3d* p14 = new vmath::Polygon3d;
            p14->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));
            p14->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            p14->AddVertex(tVec3f(-32.678337f, -0.099999905f, -23.474197f));
            p14->AddVertex(tVec3f(105.87453f, -0.099999905f, -208.11369f));

            vmath::Polygon3d* p15 = new vmath::Polygon3d;
            p15->AddVertex(tVec3f(-397.60672f, 208.93802f, -47.432915f));
            p15->AddVertex(tVec3f(-348.32104f, -0.099990845f, 8.5473824f));
            p15->AddVertex(tVec3f(-348.32077f, -0.099999905f, 8.5474529f));
            p15->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p15->AddVertex(tVec3f(-397.60672f, 208.93825f, -47.432945f));

            vmath::Polygon3d* p16 = new vmath::Polygon3d;
            p16->AddVertex(tVec3f(-71.326195f, -0.099907897f, 78.533524f));
            p16->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p16->AddVertex(tVec3f(-348.32077f, -0.10000038f, 8.5474472f));
            p16->AddVertex(tVec3f(-293.50140f, -0.099999905f, 22.398243f));

            vmath::Polygon3d* p17 = new vmath::Polygon3d;
            p17->AddVertex(tVec3f(-397.60672f, 208.93825f, -47.432961f));
            p17->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p17->AddVertex(tVec3f(-77.159714f, 165.58900f, 42.558334f));
            p17->AddVertex(tVec3f(-397.60669f, 208.93826f, -47.432961f));

            vmath::Polygon3d* p18 = new vmath::Polygon3d;
            p18->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p18->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));
            p18->AddVertex(tVec3f(-77.159714f, 165.58900f, 42.558334f));

            vmath::Polygon3d* p19 = new vmath::Polygon3d;
            p19->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p19->AddVertex(tVec3f(-71.326195f, -0.099907897f, 78.533524f));
            p19->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));

            vmath::Polygon3d* p20 = new vmath::Polygon3d;
            p20->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p20->AddVertex(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            p20->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));

            vmath::Polygon3d* p21 = new vmath::Polygon3d;
            p21->AddVertex(tVec3f(110.78994f, 29.008524f, -47.796570f));
            p21->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));
            p21->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));

            vmath::Polygon3d* p22 = new vmath::Polygon3d;
            p22->AddVertex(tVec3f(110.78994f, 29.008524f, -47.796570f));
            p22->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            p22->AddVertex(tVec3f(114.98345f, -0.099913903f, -83.372223f));

            vmath::Polygon3d* p23 = new vmath::Polygon3d;
            p23->AddVertex(tVec3f(110.78994f, 29.008524f, -47.796570f));
            p23->AddVertex(tVec3f(75.293877f, 169.20604f, -85.958290f));
            p23->AddVertex(tVec3f(-41.663677f, 25.391619f, 80.720161f));

            vmath::Polygon3d* p24 = new vmath::Polygon3d;
            p24->AddVertex(tVec3f(94.789619f, -0.099999905f, -359.91510f));
            p24->AddVertex(tVec3f(-348.32108f, -0.099999905f, 8.5473785f));
            p24->AddVertex(tVec3f(94.789429f, -0.10000610f, -359.91498f));
            p24->AddVertex(tVec3f(-348.32104f, -0.10000610f, 8.5473785f));
            p24->AddVertex(tVec3f(-348.32104f, -0.099999905f, 8.5473833f));
            p24->AddVertex(tVec3f(-348.32104f, -0.099990845f, 8.5473824f));
            p24->AddVertex(tVec3f(-192.92177f, -0.099999905f, 47.810863f));
            p24->AddVertex(tVec3f(-232.79909f, -0.099999905f, 37.735397f));
            p24->AddVertex(tVec3f(-232.79910f, -0.099999905f, 37.735397f));
            p24->AddVertex(tVec3f(-293.50140f, -0.099999905f, 22.398239f));
            p24->AddVertex(tVec3f(-32.678337f, -0.099999905f, -23.474182f));
            p24->AddVertex(tVec3f(-32.678337f, -0.099999905f, -23.474197f));
            p24->AddVertex(tVec3f(105.87453f, -0.099999905f, -208.11369f));
            p24->AddVertex(tVec3f(-348.32077f, -0.099999905f, 8.5474529f));
            p24->AddVertex(tVec3f(-348.32077f, -0.10000038f, 8.5474472f));
            p24->AddVertex(tVec3f(-293.50140f, -0.099999905f, 22.398243f));
            p24->AddVertex(tVec3f(94.789391f, -0.099999905f, -359.91498f));
            p24->AddVertex(tVec3f(94.789619f, -0.10000610f, -359.91510f));
            p24->AddVertex(tVec3f(105.87453f, -0.099999905f, -208.11368f));

            vmath::Polygon3d* p25 = new vmath::Polygon3d;
            p25->AddVertex(tVec3f(-397.60672f, 207.21199f, -163.44366f));
            p25->AddVertex(tVec3f(-397.60672f, 207.21201f, -163.44366f));
            p25->AddVertex(tVec3f(-397.60672f, 70.387497f, -22.882376f));
            p25->AddVertex(tVec3f(-397.60672f, 243.10803f, -104.13360f));
            p25->AddVertex(tVec3f(-397.60672f, 253.77744f, -182.89659f));
            p25->AddVertex(tVec3f(-397.60672f, 234.94934f, -64.182037f));
            p25->AddVertex(tVec3f(-397.60672f, 243.10805f, -104.13360f));
            p25->AddVertex(tVec3f(-397.60672f, 208.93826f, -47.432968f));
            p25->AddVertex(tVec3f(-397.60669f, 234.94936f, -64.182045f));
            p25->AddVertex(tVec3f(-397.60672f, 70.387527f, -22.882401f));
            p25->AddVertex(tVec3f(-397.60672f, 194.56255f, -44.439564f));
            p25->AddVertex(tVec3f(-397.60672f, 199.35445f, -45.437359f));
            p25->AddVertex(tVec3f(-397.60672f, 208.93802f, -47.432915f));
            p25->AddVertex(tVec3f(-397.60672f, 208.93825f, -47.432945f));
            p25->AddVertex(tVec3f(-397.60669f, 208.93826f, -47.432961f));
            p25->AddVertex(tVec3f(-397.60672f, 208.93825f, -47.432961f));
            p25->AddVertex(tVec3f(-397.60672f, 253.77744f, -182.89661f));

            bodyB.Add(p1);
            bodyB.Add(p2);
            bodyB.Add(p3);
            bodyB.Add(p4);
            bodyB.Add(p5);
            bodyB.Add(p6);
            bodyB.Add(p7);
            bodyB.Add(p8);
            bodyB.Add(p9);
            bodyB.Add(p10);
            bodyB.Add(p11);
            bodyB.Add(p12);
            bodyB.Add(p13);
            bodyB.Add(p14);
            bodyB.Add(p15);
            bodyB.Add(p16);
            bodyB.Add(p17);
            bodyB.Add(p18);
            bodyB.Add(p19);
            bodyB.Add(p20);
            bodyB.Add(p21);
            bodyB.Add(p22);
            bodyB.Add(p23);
            bodyB.Add(p24);
            bodyB.Add(p25);

            vmath::PolygonBody::tVertexArray uniqueVertices;
            uniqueVertices.push_back(tVec3f(39.089149f, 219.89795f, -419.79834f));
            uniqueVertices.push_back(tVec3f(94.789619f, -0.10000610f, -359.91510f));
            uniqueVertices.push_back(tVec3f(94.789391f, -0.099999905f, -359.91498f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 207.21199f, -163.44366f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 253.77744f, -182.89661f));
            uniqueVertices.push_back(tVec3f(114.98345f, -0.099913903f, -83.372223f));
            uniqueVertices.push_back(tVec3f(105.87453f, -0.099999905f, -208.11368f));
            uniqueVertices.push_back(tVec3f(94.789619f, -0.099999905f, -359.91510f));
            uniqueVertices.push_back(tVec3f(94.789429f, -0.10000610f, -359.91498f));
            uniqueVertices.push_back(tVec3f(-348.32108f, -0.099999905f, 8.5473785f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 70.387497f, -22.882376f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 207.21201f, -163.44366f));
            uniqueVertices.push_back(tVec3f(75.293877f, 169.20604f, -85.958290f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 253.77744f, -182.89659f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 243.10803f, -104.13360f));
            uniqueVertices.push_back(tVec3f(-77.159714f, 165.58900f, 42.558334f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 243.10805f, -104.13360f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 234.94934f, -64.182037f));
            uniqueVertices.push_back(tVec3f(-397.60669f, 234.94936f, -64.182045f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 208.93826f, -47.432968f));
            uniqueVertices.push_back(tVec3f(-348.32104f, -0.10000610f, 8.5473785f));
            uniqueVertices.push_back(tVec3f(-348.32104f, -0.099999905f, 8.5473833f));
            uniqueVertices.push_back(tVec3f(-397.60669f, 194.56253f, -44.439548f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 194.56255f, -44.439564f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 70.387527f, -22.882401f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 199.35445f, -45.437359f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 208.93802f, -47.432915f));
            uniqueVertices.push_back(tVec3f(-348.32104f, -0.099990845f, 8.5473824f));
            uniqueVertices.push_back(tVec3f(-192.92177f, -0.099999905f, 47.810863f));
            uniqueVertices.push_back(tVec3f(-71.326172f, -0.099968173f, 78.533470f));
            uniqueVertices.push_back(tVec3f(-232.79909f, -0.099999905f, 37.735397f));
            uniqueVertices.push_back(tVec3f(-293.50140f, -0.099999905f, 22.398239f));
            uniqueVertices.push_back(tVec3f(-232.79910f, -0.099999905f, 37.735397f));
            uniqueVertices.push_back(tVec3f(-71.326195f, -0.099907897f, 78.533524f));
            uniqueVertices.push_back(tVec3f(-32.678337f, -0.099999905f, -23.474182f));
            uniqueVertices.push_back(tVec3f(-32.678337f, -0.099999905f, -23.474197f));
            uniqueVertices.push_back(tVec3f(105.87453f, -0.099999905f, -208.11369f));
            uniqueVertices.push_back(tVec3f(-348.32077f, -0.099999905f, 8.5474529f));
            uniqueVertices.push_back(tVec3f(-41.663677f, 25.391619f, 80.720161f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 208.93825f, -47.432945f));
            uniqueVertices.push_back(tVec3f(-348.32077f, -0.10000038f, 8.5474472f));
            uniqueVertices.push_back(tVec3f(-293.50140f, -0.099999905f, 22.398243f));
            uniqueVertices.push_back(tVec3f(-397.60672f, 208.93825f, -47.432961f));
            uniqueVertices.push_back(tVec3f(-397.60669f, 208.93826f, -47.432961f));
            uniqueVertices.push_back(tVec3f(110.78994f, 29.008524f, -47.796570f));
            bodyB.SetVertexArray(uniqueVertices);

            std::vector<tVec3f> corners;
            corners.push_back(tVec3f(-41.663712f, 25.391582f, 80.720078f));
            corners.push_back(tVec3f(110.78996f, 29.008520f, -47.796635f));
            corners.push_back(tVec3f(75.293953f, 169.20599f, -85.958282f));
            corners.push_back(tVec3f(-77.159721f, 165.58907f, 42.558426f));
            corners.push_back(tVec3f(-298.82150f, -195.60651f, 61.764080f));
            corners.push_back(tVec3f(141.64330f, -185.15656f, -309.54276f));
            corners.push_back(tVec3f(39.089241f, 219.89804f, -419.79834f));
            corners.push_back(tVec3f(-401.37555f, 209.44807f, -48.491474f));

            std::vector<vmath::Plane*> planes;
            vmath::Plane* pl1 = new vmath::Plane(tVec3f(0.59941006f, 0.34797609f, 0.72084683f), 93.261017f);
            vmath::Plane* pl2 = new vmath::Plane(tVec3f(-0.59941006f, -0.34797603f, -0.72084689f), 202.66058f);
            vmath::Plane* pl3 = new vmath::Plane(tVec3f(-0.24011993f, 0.19789197f, 0.95035857f), 91.742088f);
            vmath::Plane* pl4 = new vmath::Plane(tVec3f(0.97139335f, 0.22663496f, -0.070933454f), 117.58536f);
            vmath::Plane* pl5 = new vmath::Plane(tVec3f(0.50522858f, -0.63776171f, 0.58138120f), 9.6856546f);
            vmath::Plane* pl6 = new vmath::Plane(tVec3f(0.094181575f, 0.98573798f, 0.13946572f), 161.89584f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum camFrust(corners, planes);

            corners.clear();
            planes.clear();

            corners.push_back(tVec3f(-504.25223f, 569.81635f, 679.70142f));
            corners.push_back(tVec3f(-102.79053f, 939.25439f, -384.95416f));
            corners.push_back(tVec3f(-501.07675f, -71.486015f, -885.87030f));
            corners.push_back(tVec3f(-902.53833f, -440.92389f, 178.78485f));
            corners.push_back(tVec3f(328.73639f, 9364.4590f, 23393.018f));
            corners.push_back(tVec3f(12286.593f, 20368.463f, -8318.5938f));
            corners.push_back(tVec3f(423.30984f, -9737.1299f, -23238.521f));
            corners.push_back(tVec3f(-11534.408f, -20741.008f, 8472.7246f));

            pl1 = new vmath::Plane(tVec3f(-0.88121527f, 0.43680814f, -0.18071631f), 587.44641f);
            pl2 = new vmath::Plane(tVec3f(0.88121486f, -0.43680876f, 0.18071611f), 426.71146f);
            pl3 = new vmath::Plane(tVec3f(-0.89914292f, 0.41822335f, -0.12896173f), 604.04993f);
            pl4 = new vmath::Plane(tVec3f(-0.86033958f, 0.45393157f, -0.23186630f), 604.04993f);
            pl5 = new vmath::Plane(tVec3f(-0.86049294f, 0.48492423f, -0.15620588f), 604.04993f);
            pl6 = new vmath::Plane(tVec3f(-0.89898950f, 0.38723066f, -0.20462216f), 604.04993f);

            planes.push_back(pl1);
            planes.push_back(pl2);
            planes.push_back(pl3);
            planes.push_back(pl4);
            planes.push_back(pl5);
            planes.push_back(pl6);

            vmath::Frustum lightFrust(corners, planes);

            vmath::BoundingBox sceneAABB(tVec3f(-397.60672f, -0.099999905f, -422.14844f), tVec3f(397.60669f, 329.10513f, 422.14844f));

            tVec2f zRange(129.53264f, 714.25018f);

            tMat4f liSPMatrix = liSP.GetLiSPMtx(
                                        0,                  // unsigned int        split,
                                        bodyB,              // const PolygonBody&  bodyB,
                                        camFrust,           // const Frustum&      camFrust, 
                                        &lightFrust,        // const Frustum*      lightFrust, 
                                        sceneAABB,          // const BoundingBox&  sceneAABB,
                                        zRange              // const tVec2f&       zRange
                                );
            //
            //              [0.041494 -0.020267  0.000000 -0.000335]
            // liSPMatrix = [0.951689  1.948423  0.000000  0.033009]
            //              [0.000000  0.000000  0.046179 -0.044914]
            //              [0.438885  0.898543  0.000000  0.061402]
            //

            int ijk = 234;
        }
    }

    //
    // some vmath example code
    //
    {
        tVec3f pos1 = tVec3f(5.f);
        tVec3f pos2 = tVec3f(3.f, 2.f, 1.f);
        tVec3f dir  = tVec3f(1.f, 2.f, 3.f);

        float l1 = vmath::length(dir);
        float l2 = l1 * l1;                         // square length

        tVec3f n = vmath::normalize(dir);

        float dist1 = vmath::length(pos2 - pos1);   // distance(pos1, pos2)
        float dist2 = dist1 * dist1;                // square distance

    #ifdef OSG_WITH_QHULL
        // Test qhull library
        {
            std::vector<vmath::Polygon3d*> polygons;

            orgQhull::RboxPoints rPoints;
            rPoints.setDimension(3);

            std::vector<tVec3f> vertices;
            vertices.push_back(tVec3f(  -4.4842505f, 17.970732f,   21.593283f ));
            vertices.push_back(tVec3f(  18.277416f,  17.970732f,   12.341572f ));
            vertices.push_back(tVec3f(  14.167388f,   3.1237047f,   2.2298069f));
            vertices.push_back(tVec3f(  -8.5942793f,  3.1237037f,  11.481519f ));
            vertices.push_back(tVec3f( -13.735492f,  -0.10000038f, 34.172630f ));
            vertices.push_back(tVec3f(  33.681381f,  -0.10000134f, 14.899557f ));
            vertices.push_back(tVec3f(  38.075329f,  15.772653f,   25.709839f ));
            vertices.push_back(tVec3f(  -9.3415451f, 15.772651f,   44.982906f ));
            vertices.push_back(tVec3f(  16.873638f,  -0.10000134f,  2.6557446f));
            vertices.push_back(tVec3f( -10.235955f,  -0.10000062f, 13.674715f ));
            vertices.push_back(tVec3f(-466.05347f,  375.69608f,   -88.014847f ));

            for (std::size_t i = 0; i < vertices.size(); ++i)
            {
                rPoints.append(static_cast<double>(vertices[i].x));
                rPoints.append(static_cast<double>(vertices[i].y));
                rPoints.append(static_cast<double>(vertices[i].z));
            }

            orgQhull::Qhull convexHull(rPoints, "Qt");

            std::vector<orgQhull::QhullFacet> triangles = convexHull.facetList().toStdVector();

            for (std::size_t i = 0; i < triangles.size(); ++i)
            {
                orgQhull::QhullPoint first  = triangles[i].vertices()[0].point();
                orgQhull::QhullPoint second = triangles[i].vertices()[1].point();
                orgQhull::QhullPoint third  = triangles[i].vertices()[2].point();

                double* nCoords = triangles[i].hyperplane().coordinates();

                tVec3f normal = vmath::normalize(
                                        tVec3f(
                                            static_cast<float>(nCoords[0]), 
                                            static_cast<float>(nCoords[1]), 
                                            static_cast<float>(nCoords[2])
                                            )
                                        );
                tVec3f v0(
                            static_cast<float>(first[0]), 
                            static_cast<float>(first[1]), 
                            static_cast<float>(first[2])
                         );
                tVec3f v1(
                            static_cast<float>(second[0]), 
                            static_cast<float>(second[1]), 
                            static_cast<float>(second[2])
                         );
                tVec3f v2(
                            static_cast<float>(third[0]), 
                            static_cast<float>(third[1]), 
                            static_cast<float>(third[2])
                         );

                vmath::Plane plane(v0, v1, v2, vmath::Polygon3d::ccw);

                vmath::Polygon3d* polygon =  new vmath::Polygon3d();
                polygon->AddVertex(v0);

                if (vmath::dot(normal, plane.GetNormal()) > .0f)
                {
                    polygon->AddVertex(v1);
                    polygon->AddVertex(v2);
                }
                else
                {
                    polygon->AddVertex(v2);
                    polygon->AddVertex(v1);
                }
                polygon->SetNormal(normal);

                polygons.push_back(polygon);
            }

            for (std::size_t i = 0; i < polygons.size(); ++i)
                delete polygons[i];
        }
    #endif // OSG_WITH_QHULL
    }

#endif // OSG_WITH_VMATH
}

void osg_math_library()
{
    //      OpenSG: OSG:: typedef OSG::Vector< OSG::Real32, 3 > Vec3f;      typedef OSG::Vector< OSG::Real64, 3 > Vec3d;
    //                    typedef OSG::Point < OSG::Real32, 3 > Pnt3f;      typedef OSG::Point < OSG::Real64, 3 > Pnt3d;
    //
    //                    Int8, UInt8, Int16, UInt16, Int32, UInt32, Real32, Real64
    //
    //          Vec1f,  Vec2f,  Vec3f,  Vec4f
    //          Vec1d,  Vec2d,  Vec3d,  Vec4d
    //          Vec1b,  Vec2b,  Vec3b,  Vec4b
    //          Vec1ub, Vec2ub, Vec3ub, Vec4ub
    //          Vec1s,  Vec2s,  Vec3s,  Vec4s
    //          Vec1us, Vec2us, Vec3us, Vec4us
    //          Vec1i,  Vec2i,  Vec3i,  Vec4i
    //          Vec1u,  Vec2u,  Vec3u,  Vec4u
    //          
    //          Pnt1f,  Pnt2f,  Pnt3f,  Pnt4f
    //          Pnt1d,  Pnt2d,  Pnt3d,  Pnt4d
    //          Pnt1b,  Pnt2b,  Pnt3b,  Pnt4b
    //          Pnt1ub, Pnt2ub, Pnt3ub, Pnt4ub
    //          Pnt1s,  Pnt2s,  Pnt3s,  Pnt4s
    //          Pnt1us, Pnt2us, Pnt3us, Pnt4us
    //          Pnt1i,  Pnt2i,  Pnt3i,  Pnt4i
    //          Pnt1u,  Pnt2u,  Pnt3u,  Pnt4u
    //
    //                    typedef TransformationMatrix<Real32>  Matrix;
    //                    typedef TransformationMatrix<Real32>  Matrix4f;   typedef TransformationMatrix<Real64>  Matrix4d;
    //
    //                    typedef Matrix22<Real32> Matrix22f;               typedef Matrix22<Real64> Matrix22d;
    //
    //          Matrix22f, Matrix4f == Matrix
    //          Matrix22d, Matrix4d
    //          

    OSG::Real32 epsilon   = OSG::Eps;
    OSG::Real32 epsilon1  = OSG::TypeTraits<OSG::Real32>::getDefaultEps();
    OSG::Real32 pi        = OSG::Pi;
    OSG::Real32 two_pi    = OSG::TwoPi;
    OSG::Real32 half_pi   = OSG::PiHalf;
    OSG::Real32 root_two  = OSG::Sqrt2;

    OSG::Real32 inf       = OSG::Inf;
    OSG::Real32 neg_inf   = OSG::NegInf;

    OSG::Real32 inf2      =  std::numeric_limits<OSG::Real32>::infinity();
    OSG::Real32 neg_inf2  = -std::numeric_limits<OSG::Real32>::infinity();

    OSG::Real32 max_val   =  std::numeric_limits<OSG::Real32>::max();
    OSG::Real32 min_val    = std::numeric_limits<OSG::Real32>::min();

    OSG::Real32 rad = OSG::osgDegree2Rad(45.0f);
    OSG::Real32 deg = OSG::osgRad2Degree(pi);

    //
    // point and vector API
    //
    {
        OSG::Real32 aVals1[] = { 1.2f, 2.4f, 5.6f };
        const OSG::Real32* pValues = NULL;
        OSG::Real32 s1,s2,s3, d, m;
        bool flag;
        OSG::UInt32 i;

        OSG::Pnt3f  p1(aVals1);          p1.setValue(aVals1);
        OSG::Vec3f  v1(aVals1);          v1.setValue(aVals1);


        OSG::Pnt2f  p2(p1);              p2.setValue(p1);
        OSG::Pnt3f  p3(p1);              p3.setValue(p1);
        OSG::Pnt4f  p4(p1);              p4.setValue(p1);

        OSG::Pnt2f  p5(v1);              p5.setValue(v1);
        OSG::Pnt3f  p6(v1);              p6.setValue(v1);
        OSG::Pnt4f  p7(v1);              p7.setValue(v1);

        OSG::Pnt3f  p8(1.5f);
        OSG::Pnt3f  p9(1.5f,3.5f);
        OSG::Pnt3f p10(1.5f,3.5f,7.3f); p10.setValues(1.5f,3.5f,7.3f);

              OSG::Pnt3f& p11 = v1.addToZero();
        const OSG::Pnt3f& p12 = v1.addToZero();

                              pValues = p10.getValues();
                                        p10.getSeparateValues(s1, s2, s3);

        s1 = p10[0];    s2 = p10[1];    s3 = p10[2];
        p10[0] = s1;    p10[1] = s2;    p10[2] = s3;

        p6 = p1;
        // p6 = v1; not available!

        flag = p6 < p1;
        flag = p6 == p1;
        flag = p6 != p1;

        flag = p6.equals(p1, epsilon);

        p6.negate();

        p6.setNull();
        p6 = OSG::Pnt3f::Null;

        flag = p6.isZero();

        d = p1.dist (p10);
        d = p1.dist2(p10);

        m = p1.maxValue();
        i = p1.maxDim();
        i = p1.maxDimAbs();

        p10 *= 2.3f;
        p10 /= 2.3f;

        p6 = p1 + v1;
        p6 = p1 - v1;
        p6 = 2.3f * p1;
        p6 = p1 * 2.3f;
        p6 = p1 / 2.3f;
        p6 = -p1;

        p6 += v1;
        p6 -= v1;

        OSG::Vec2f  v2(v1);              v2.setValue(v1);
        OSG::Vec3f  v3(v1);              v3.setValue(v1);
        OSG::Vec4f  v4(v1);              v4.setValue(v1);

        v4[3] = 313.4f;
        OSG::Vec3f vt(v4);
        
        OSG::Vec2f  v5(p1);              v5.setValue(p1);
        OSG::Vec3f  v6(p1);              v6.setValue(p1);
        OSG::Vec4f  v7(p1);              v7.setValue(p1);

        OSG::Vec3f  v8(1.5f);
        OSG::Vec3f  v9(1.5f,3.5f);
        OSG::Vec3f v10(1.5f,3.5f,7.3f); v10.setValues(1.5f,3.5f,7.3f);

              OSG::Vec3f& v11 = p1.subZero();
        const OSG::Vec3f& v12 = p1.subZero();

              OSG::Vec3f& v13 = v1.subZero();
        const OSG::Vec3f& v14 = v1.subZero();

                              pValues = v10.getValues();
                                        v10.getSeparateValues(s1, s2, s3);
                                        
        s1 = v10[0];    s2 = v10[1];    s3 = v10[2];
        v10[0] = s1;    v10[1] = s2;    v10[2] = s3;

        v6 = v1;
        // v6 = p1; not available!

        flag = v6 < v1;
        flag = v6 == v1;
        flag = v6 != v1;

        flag = v6.equals(v1, epsilon);

        v6.negate();

        v6.setNull();
        v6 = OSG::Vec3f::Null;

        flag = v6.isZero();

        d = v1.dist (p10);   // works but makes no sense!
        d = v1.dist2(p10);   // works but makes no sense!

        m = v1.maxValue();
        i = v1.maxDim();
        i = v1.maxDimAbs();

        v10 *= 2.3f;
        v10 /= 2.3f;

        v6 = p10 - p1;
        v6 = v1 + v1;
        v6 = v1 - v1;
        v6 = 2.3f * v1;
        v6 = v1 * 2.3f;
        v6 = v1 / 2.3f;

        d = v1.length();
        d = v1.squareLength();

        v1.normalize();

        v6 = v1.cross(v10);
        v6 = v1 % v10;

        v1.crossThis(v10);

        m = v1.dot(v6);
        m = v1 * v6;

        m = v1.dot(p6);
        m = v1 * p6;

        m = v1.enclosedAngle(v10);
        m = v1.projectTo(v10);

        v1.setValues(1.5f, 0.9f, 6.3f);
        v3.setValues(2.4f,-1.4f, 0.3f);  v3.normalize();
        OSG::Vec3f vr;

        v3 = v1.reflect(v3);

             OSG::lerp(v1, v3, 0.8f, vr);  // Generic Lerp
        vr = OSG::lerp(v1, v3, 0.8f);      // Generic Lerp

             OSG::lerpNormal(v1, v3, 0.5f, vr);  // Generic Normal Lerp
        vr = OSG::lerpNormal(v1, v3, 0.5f);      // Generic Normal Lerp

        int ijk = 234;
    }

    //
    // matrix API
    //
    {
        // Mathematically: m(row x col)
        // --------------
        // columns: c0  c1  c2  c3       c0 c1 c2 c3
        //        -----------------     -------------
        //        (m00 m01 m02 m03)     ( 1  2  3  4) |r0
        //  mat = (m10 m11 m12 m13)  =  ( 5  6  7  8) |r1
        //        (m20 m21 m22 m23)     ( 9 10 11 12) |r2
        //        (m30 m31 m32 m33)     (13 14 15 16) |r3
        //
        //            col 0    col 1    col 2    col 3
        OSG::Real32 m00 = 1, m01 = 2, m02 = 3, m03 = 4,     // row 0
                    m10 = 5, m11 = 6, m12 = 7, m13 = 8,     // row 1
                    m20 = 9, m21 =10, m22 =11, m23 =12,     // row 2
                    m30 =13, m31 =14, m32 =15, m33 =16;     // row 3

        //
        // OpenSG stores internally the transposed of the matrix as 4 row vectors
        //
        //           ( _matrix[0] )   ( _matrix[0][0] _matrix[0][1] _matrix[0][2] _matrix[0][3] )
        //  Matrix = ( _matrix[1] ) = ( _matrix[1][0] _matrix[1][1] _matrix[1][2] _matrix[1][3] )
        //           ( _matrix[2] )   ( _matrix[2][0] _matrix[2][1] _matrix[2][2] _matrix[2][3] )
        //           ( _matrix[3] )   ( _matrix[3][0] _matrix[3][1] _matrix[3][2] _matrix[3][3] )
        //
        //           ( _matrix[0][0]=m00  _matrix[0][1]=m10  _matrix[0][2]=m20  _matrix[0][3]=m30 )
        //         = ( _matrix[1][0]=m01  _matrix[1][1]=m11  _matrix[1][2]=m21  _matrix[1][3]=m31 )
        //           ( _matrix[2][0]=m02  _matrix[2][1]=m12  _matrix[2][2]=m22  _matrix[2][3]=m32 )
        //           ( _matrix[3][0]=m03  _matrix[3][1]=m13  _matrix[3][2]=m23  _matrix[3][3]=m33 )
        //
        //           ( m00 m10 m20 m30 )    T
        //         = ( m01 m11 m21 m31 ) = M
        //           ( m02 m12 m22 m32 )
        //           ( m03 m13 m23 m33 )
        //
        // That is, the vectors _matrix[i] represent the column vectors of the original matrix M !!!
        //
        // Mulitplication: r = M * v
        //
        //      (m00 m01 m02 m03)   [v0]   [m00*v0 + m01*v1 + m02*v2 + m03*v3]
        //  r = (m10 m11 m12 m13) * [v1] = [m10*v0 + m11*v1 + m12*v2 + m13*v3]
        //      (m20 m21 m22 m23)   [v2]   [m20*v0 + m21*v1 + m22*v2 + m23*v3]
        //      (m30 m31 m32 m33)   [v3]   [m30*v0 + m31*v1 + m32*v2 + m33*v3]
        //
        //       T   T
        //    = v * M
        //                      (m00 m10 m20 m30)   [v0*m00 + v1*m01 + v2*m02 + v3*m03]
        //    = [v0 v1 v2 v3] * (m01 m11 m21 m31) = [v0*m10 + v1*m11 + v2*m12 + v3*m13]
        //                      (m02 m12 m22 m32)   [v0*m20 + v1*m21 + v2*m22 + v3*m23]
        //                      (m03 m13 m23 m33)   [v0*m30 + v1*m31 + v2*m32 + v3*m33]
        //
        //      [ v0*_matrix[0][0] + v1*_matrix[1][0] + v2*_matrix[2][0] + v3*_matrix[3][0] ]   // see TransformationMatrix<T>::mult
        //    = [ v0*_matrix[0][1] + v1*_matrix[1][1] + v2*_matrix[2][1] + v3*_matrix[3][1] ]   // in OSGMatrix.inl
        //      [ v0*_matrix[0][2] + v1*_matrix[1][2] + v2*_matrix[2][2] + v3*_matrix[3][2] ]
        //      [ v0*_matrix[0][3] + v1*_matrix[1][3] + v2*_matrix[2][3] + v3*_matrix[3][3] ]
        //

        //
        // In the following examples the mathematical matrix that we would like to 
        // setup is always:
        //
        // columns: c0  c1  c2  c3
        //        (m00 m01 m02 m03)   ( 1  2  3  4 )   // row 0
        //    M = (m10 m11 m12 m13) = ( 5  6  7  8 )   // row 1
        //        (m20 m21 m22 m23)   ( 9 10 11 12 )   // row 2
        //        (m30 m31 m32 m33)   (13 14 15 16 )   // row 3
        //
        // We show always the four _matrix[i] vectors of the Matrix object as shown in the debugger.
        // We show them as row vectors, i.e. the transposed of the mathematical matrix and as column 
        // vectors, i.e. the correct mathematical matrix.
        //

        //
        // Element wise constructor takes elements in row-major order,
        // i.e. it takes the four rows of the mathematical matrix and 
        // stores it internally transposed in the 4 _matrix[i] vectors!
        //                  c0   c1   c2   c3
        OSG::Matrix4f mat0(m00, m01, m02, m03,  // row 0    mat0( 1,  2,  3,  4,
                           m10, m11, m12, m13,  // row 1          5,  6,  7,  8, 
                           m20, m21, m22, m23,  // row 2          9, 10, 11, 12, 
                           m30, m31, m32, m33); // row 3         13, 14, 15, 16 );

        int ijfk = 234;
        //
        // The debugger shows _matrix[0],...,_matrix[3] i.e. 4 rows of the transposed of the original matrix
        // _m := _matrix in the following
        //
        //                           _m[0] _m[1] _m[2] _m[3]
        //          r0 r1 r2 r3        c0    c1    c2    c3             c0  c1  c2  c3
        // _m[0] = [ 1, 5, 9,13] c0   [ 1]  [ 2]  [ 3]  [ 4] r0       (m00 m01 m02 m03)   ( 1  2  3  4 ) row 0
        // _m[1] = [ 2, 6,10,14] c1   [ 5]  [ 6]  [ 7]  [ 8] r1   M = (m10 m11 m12 m13) = ( 5  6  7  8 ) row 1
        // _m[2] = [ 3, 7,11,15] c2   [ 9]  [10]  [11]  [12] r2       (m20 m21 m22 m23)   ( 9 10 11 12 ) row 2
        // _m[3] = [ 4, 8,12,16] c3   [13]  [14]  [15]  [16] r3       (m30 m31 m32 m33)   (13 14 15 16 ) row 3
        //
        //
        //        (_m[0])   ( _m[0][0] = m00= 1 _m[0][1] = m10= 5 _m[0][2] = m20= 9  _m[0][3] = m30=13 ) // col0
        // mat0 = (_m[1]) = ( _m[1][0] = m01= 2 _m[1][1] = m11= 6 _m[1][2] = m21=10  _m[1][3] = m31=14 ) // col1
        //        (_m[2])   ( _m[2][0] = m02= 3 _m[2][1] = m12= 7 _m[2][2] = m22=11  _m[2][3] = m32=15 ) // col2
        //        (_m[3])   ( _m[3][0] = m03= 4 _m[3][1] = m13= 8 _m[3][2] = m23=12  _m[3][3] = m33=16 ) // col3
        //

        //
        // Math is internally row-major: r = v * M' i.e. multiplication takes place on the left 
        // of the matrix.
        //
        //       T   
        //  r = v * M'  // where M' is the transposed of the original matrix M
        //
        //                      (m00 m10 m20 m30)   [v0*m00 + v1*m01 + v2*m02 + v3*m03]
        //    = [v0 v1 v2 v3] * (m01 m11 m21 m31) = [v0*m10 + v1*m11 + v2*m12 + v3*m13]
        //                      (m02 m12 m22 m32)   [v0*m20 + v1*m21 + v2*m22 + v3*m23]
        //                      (m03 m13 m23 m33)   [v0*m30 + v1*m31 + v2*m32 + v3*m33]
        //
        //      [ v0*_m[0][0] + v1*_m[1][0] + v2*_m[2][0] + v3*_m[3][0] ]   // see TransformationMatrix<T>::mult
        //    = [ v0*_m[0][1] + v1*_m[1][1] + v2*_m[2][1] + v3*_m[3][1] ]   // in OSGMatrix.inl
        //      [ v0*_m[0][2] + v1*_m[1][2] + v2*_m[2][2] + v3*_m[3][2] ]
        //      [ v0*_m[0][3] + v1*_m[1][3] + v2*_m[2][3] + v3*_m[3][3] ]
        //
        // But since M' is the transposed of the mathematical matrix M, we have actually 
        // column-major math, i.e. r = M * v
        //
        //              (m00 m01 m02 m03)   [v0]   [m00*v0 + m01*v1 + m02*v2 + m03*v3]
        //    = M * v = (m10 m11 m12 m13) * [v1] = [m10*v0 + m11*v1 + m12*v2 + m13*v3]
        //              (m20 m21 m22 m23)   [v2]   [m20*v0 + m21*v1 + m22*v2 + m23*v3]
        //              (m30 m31 m32 m33)   [v3]   [m30*v0 + m31*v1 + m32*v2 + m33*v3]
        //

        OSG::Vec4f r;
        OSG::Real32 v0 = 100, v1 = 200, v2 = 300, v3 = 400;
        OSG::Vec4f v(v0, v1, v2, v3);                       // = [100, 200, 300, 400]

        r = mat0 * v;
        //
        // [ 3000]   ( 1  2  3  4 )   [100]
        // [ 7000] = ( 5  6  7  8 ) * [200]
        // [11000]   ( 9 10 11 12 )   [300]
        // [15000]   (13 14 15 16 )   [400]
        //
        
        // r = v * mat0;    // does yet not exist in OpenSG

        //
        // The mathematically matrix that we would like to specify with the OpenSG API:
        //
        //            ( 1  2  3  4)            [ 1,  2,  3,  4]              [ 1] [ 2] [ 3] [ 4]
        //      mat = ( 5  6  7  8)  with rows [ 5,  6,  7,  8]  and columns [ 5] [ 6] [ 7] [ 8]
        //            ( 9 10 11 12)            [ 9, 10, 11, 12]              [ 9] [10] [11] [12]
        //            (13 14 15 16)            [13, 14, 15, 16]              [13] [14] [15] [16]
        //
        // We show always the four _matrix[i] =: _m[i] vectors of the Matrix object as shown in the debugger.
        // We show them as row vectors, i.e. the transposed of the mathematical matrix and as column 
        // vectors, i.e. the correct mathematical matrix.
        //

        //
        // The element wise construction: row-major, i.e. 4 row-vectors of the mathematical matrix
        //
        OSG::Matrix4f mat1( 1,2,3,4,  5,6,7,8,  9,10,11,12,  13,14,15,16 );
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //

        //
        // Initialize in row-major, i.e. from 4 row-vectors of the mathematical matrix
        //
        OSG::Matrix4f mat2; mat2.setValue( 1,2,3,4,  5,6,7,8,  9,10,11,12,  13,14,15,16 );
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2);

        //
        // Get values of the matrix: getValues() gives m00,m10,m20,m30, m01,m02,m03,...
        // i.e. it returns
        // 
        //  { _m[0][0] = m00 = 1, _m[0][1] = m10 = 5, _m[0][2] = m20 =  9, _m[0][3] = m30 = 13, 
        //    _m[1][0] = m01 = 2, _m[1][1] = m11 = 6, _m[1][2] = m21 = 10, _m[1][3] = m31 = 14,
        //    _m[2][0] = m02 = 3, _m[2][1] = m12 = 7, _m[2][2] = m22 = 11, _m[2][3] = m32 = 15, 
        //    _m[3][0] = m03 = 4, _m[3][1] = m13 = 8, _m[3][2] = m23 = 12, _m[3][3] = m33 = 16 }
        //
        OSG::Real32* pValues = mat2.getValues(); // 1,5,9,13, 2,6,10,14, 3,7,11,15, 4,8,12,16

        //
        // Construction from 4 column vectors of the mathematical matrix
        //
        OSG::Vec4f col0(1, 5,  9, 13);
        OSG::Vec4f col1(2, 6, 10, 14);
        OSG::Vec4f col2(3, 7, 11, 15);
        OSG::Vec4f col3(4, 8, 12, 16);

        OSG::Matrix4f mat3(col0, col1, col2, col3);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2 && mat2 == mat3);

        OSG::Matrix4f mat4; mat4.setValue(col0, col1, col2, col3);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2 && mat2 == mat3 && mat3 == mat4);

        //
        // Get the columns of the mathematical matrix
        //
        OSG::Vec4f c0 = mat4[0];    assert(c0 == col0);
        OSG::Vec4f c1 = mat4[1];    assert(c1 == col1);
        OSG::Vec4f c2 = mat4[2];    assert(c2 == col2);
        OSG::Vec4f c3 = mat4[3];    assert(c3 == col3);

        //
        // Initialize the matrix in column-major form, i.e. 4 column vectors of the mathematical matrix
        //
        OSG::Matrix4f mat5; mat5.setValueTransposed( 1,5,9,13,  2,6,10,14,  3,7,11,15,  4,8,12,16);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2 && mat2 == mat3 && mat3 == mat4 && mat4 == mat5);

        //
        // Initialize the matrix in row-major form from an array.
        //
        OSG::Real32 values_row_major[] = { 1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16 };
        OSG::Matrix4f mat6; mat6.setValue(values_row_major, false);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2 && mat2 == mat3 && mat3 == mat4 && mat4 == mat5 && mat5 == mat6);

        //
        // Initialize the matrix in column-major form from an array
        //
        OSG::Real32 values_column_major[] = { 1,5,9,13, 2,6,10,14, 3,7,11,15, 4,8,12,16 };
        OSG::Matrix4f mat7; mat7.setValue(values_column_major, true);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat1 == mat2 && mat2 == mat3 && mat3 == mat4 && mat4 == mat5 && mat5 == mat6 && mat6 == mat7);

        //
        // Where is the translational part?
        //
        OSG::Matrix4f mat8;

        OSG::Vec3f t(100, 200, 300);
        mat8.setTranslate(t);
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  0  0 100)      _m[0] = [  1,  0,  0,  0]       [1]   [0]   [0]  [100]
        // mat = ( 0  1  0 200)      _m[1] = [  0,  1,  0,  0]       [0]   [1]   [0]  [200]
        //       ( 0  0  1 300)      _m[2] = [  0,  0,  1,  0]       [0]   [0]   [1]  [300]
        //       ( 0  0  0  1 )      _m[3] = [100,200,300,  1]       [0]   [0]   [0]  [  1]
        //

        //
        // The default constructor initialize the identity.
        //
        OSG::Matrix4f test;
        //                                                    _m[0] _m[1] _m[2] _m[3]
        //       (1 0 0 0)      _m[0] = [1, 0, 0, 0]           [1]   [0]   [0]   [0]
        // mat = (0 1 0 0)      _m[1] = [0, 1, 0, 0]           [0]   [1]   [0]   [0]
        //       (0 0 1 0)      _m[2] = [0, 0, 0, 0]           [0]   [0]   [1]   [0]
        //       (0 0 0 1)      _m[3] = [0, 0, 0, 1]           [0]   [0]   [0]   [1]
        //

        //
        // Now, we will look at the matrix multiplication with vectors and points.
        // At first some inputs: mat, rhs, pnt4fIn, pnt3fIn, vec4fIn, vec3fIn
        // And some outputs: pnt4fOut, pnt3fOut, vec4fOut, vec3fOut
        //
        OSG::Matrix4f mat( 1,2,3,4,  5,6,7,8,  9,10,11,12,  13,14,15,16);   // row-major intialization
        //                                                          _m[0] _m[1] _m[2] _m[3]
        //       ( 1  2  3  4)      _m[0] = [1, 5,  9, 13]           [ 1]  [ 2]  [ 3]  [ 4]
        // mat = ( 5  6  7  8)      _m[1] = [2, 6, 10, 14]           [ 5]  [ 6]  [ 7]  [ 8]
        //       ( 9 10 11 12)      _m[2] = [3, 7, 11, 15]           [ 9]  [10]  [11]  [12]
        //       (13 14 15 16)      _m[3] = [4, 8, 12, 16]           [13]  [14]  [15]  [16]
        //
        assert(mat == mat1 && mat1 == mat2 && mat2 == mat3 && mat3 == mat4 && mat4 == mat5 && mat5 == mat6 && mat6 == mat7);

        OSG::Matrix4f rhs(101,201,301,401,  501,601,701,801,  901,1001,1101,1201,  1301,1401,1501,1601);   // row-major initialization
        //                                                                _m[0]   _m[1]   _m[2]   _m[3]
        //       ( 101  201  301  401)   _m[0] = [101, 501,  901, 1301]   [ 101]  [ 201]  [ 301]  [ 401]
        // mat = ( 501  601  701  801)   _m[1] = [201, 601, 1001, 1401]   [ 501]  [ 601]  [ 701]  [ 801]
        //       ( 901 1001 1101 1201)   _m[2] = [301, 701, 1101, 1501]   [ 901]  [1001]  [1101]  [1201]
        //       (1301 1401 1501 1601)   _m[3] = [401, 801, 1201, 1601]   [1301]  [1401]  [1501]  [1601]
        //
        OSG::Pnt4f pnt4fIn(100.f, 200.f, 300.f, 400.f);     OSG::Pnt4f pnt4fOut;
        OSG::Pnt3f pnt3fIn(100.f, 200.f, 300.f);            OSG::Pnt3f pnt3fOut;

        OSG::Vec4f vec4fIn(100.f, 200.f, 300.f, 400.f);     OSG::Vec4f vec4fOut;
        OSG::Vec3f vec3fIn(100.f, 200.f, 300.f);            OSG::Vec3f vec3fOut;

        //
        // If debugging into the matrix class, remember that the 4 vectors _matrix[0],...,_matrix[3]
        // store the transposed of the mathematical matrix M at hand, i.e. they represent the column 
        // vectors of the mathematical matrix. The multiplication implementation multiplies this 
        // transposed matrix, i.e. the matrix consiting of rows _matrix[i],
        //     T   ( _matrix[0] )
        //    M  = ( _matrix[1] )       M = (_matrix[0], _matrix[1], _matrix[2], _matrix[3])
        //         ( _matrix[2] )
        //         ( _matrix[3] )
        // from the left with the given vector type. That is, it actually performs a multiplication
        // of the mathematical matrix with the vector type from the right. See above for verbose
        // details.
        //               T   T
        // v' = M * v = v * M
        //
        // If you think of the _matrix[i] vectors as the columns of the mathematical matrix M
        // that you have at hand, than the multiplication is the ordinary multiplication with
        // the vector at the right side of the matrix!
        //

        //
        // void Matrix::mult(const PointType& pntIn, PointType& pntOut) const;
        //
        pnt4fOut.setNull();
        mat.mult(pnt4fIn, pnt4fOut);
        // [  3000 ]   [  1*100 +  2*200 +  3*300 +  4*400 ]   ( 1  2  3  4)   [ 100 ]
        // [  7000 ] = [  5*100 +  6*200 +  7*300 +  8*400 ] = ( 5  6  7  8) * [ 200 ]
        // [ 11000 ]   [  9*100 + 10*200 + 11*300 + 12*400 ]   ( 9 10 11 12)   [ 300 ]
        // [ 15000 ]   [ 13*100 + 14*200 + 15*300 + 16*400 ]   (13 14 15 16)   [ 400 ]
        assert(pnt4fOut == OSG::Pnt4f(3000, 7000, 11000, 15000));

        //
        // void Matrix::multFull(const PointType3f& pntIn, PointType3f& pntOut) const;
        //
        pnt3fOut.setNull();
        mat.multFull(pnt3fIn, pnt3fOut);
        // [ 0.162952647 ]   [  (1*100 +  2*200 +  3*300 +  4*1) / (13*100 + 14*200 + 15*300 + 16*1) ]   ( 1  2  3  4)   [ 100 ]
        // [ 0.441968411 ] = [  (5*100 +  6*200 +  7*300 +  8*1) / (13*100 + 14*200 + 15*300 + 16*1) ] = ( 5  6  7  8) * [ 200 ]
        // [ 0.720984221 ]   [  (9*100 + 10*200 + 11*300 + 12*1) / (13*100 + 14*200 + 15*300 + 16*1) ]   ( 9 10 11 12)   [ 300 ]
        //                                                                                               (13 14 15 16)   (   1 )
        assert(pnt3fOut.equals(OSG::Pnt3f(0.162952647f, 0.441968411f, 0.720984221f), OSG::Eps));

        //
        // void Matrix::mult(const PointType3f& pntIn, PointType3f& pntOut) const;
        //
        pnt3fOut.setNull();
        mat.mult(pnt3fIn, pnt3fOut);
        // [ 1404 ]   [  (1*100 +  2*200 +  3*300 +  4*1) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3808 ] = [  (5*100 +  6*200 +  7*300 +  8*1) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6212 ]   [  (9*100 + 10*200 + 11*300 + 12*1) ]   ( 9 10 11 12)   [ 300 ]
        //                                                    (13 14 15 16)   (   1 )
        assert(pnt3fOut == OSG::Pnt3f(1404, 3808, 6212));
    
        //
        // void Matrix::mult(const VectorType& vecIn, VectorType& vecOut) const;
        //
        vec4fOut.setNull();
        mat.mult(vec4fIn, vec4fOut);
        // [  3000 ]   [  1*100 +  2*200 +  3*300 +  4*400 ]   ( 1  2  3  4)   [ 100 ]
        // [  7000 ] = [  5*100 +  6*200 +  7*300 +  8*400 ] = ( 5  6  7  8) * [ 200 ]
        // [ 11000 ]   [  9*100 + 10*200 + 11*300 + 12*400 ]   ( 9 10 11 12)   [ 300 ]
        // [ 15000 ]   [ 13*100 + 14*200 + 15*300 + 16*400 ]   (13 14 15 16)   [ 400 ]
        assert(vec4fOut == OSG::Vec4f(3000, 7000, 11000, 15000));

        //
        // void Matrix::multFull(const VectorType3f& vecIn, VectorType3f& vecOut) const;
        //
        vec3fOut.setNull();
        mat.multFull(vec3fIn, vec3fOut);
        // [ 0.162790701 ]   [  (1*100 +  2*200 +  3*300 +  4*0) / (13*100 + 14*200 + 15*300 + 16*0) ]   ( 1  2  3  4)   [ 100 ]
        // [ 0.441860467 ] = [  (5*100 +  6*200 +  7*300 +  8*0) / (13*100 + 14*200 + 15*300 + 16*0) ] = ( 5  6  7  8) * [ 200 ]
        // [ 0.720930219 ]   [  (9*100 + 10*200 + 11*300 + 12*0) / (13*100 + 14*200 + 15*300 + 16*0) ]   ( 9 10 11 12)   [ 300 ]
        //                                                                                               (13 14 15 16)   (   0 )
        assert(vec3fOut.equals(OSG::Vec3f(0.162790701f, 0.441860467f, 0.720930219f), OSG::Eps));

        //
        // void Matrix::mult(const VectorType3f& vecIn, VectorType3f& vecOut) const;
        //
        vec3fOut.setNull();
        mat.mult(vec3fIn, vec3fOut);
        // [ 1400 ]   [  (1*100 +  2*200 +  3*300 +  4*0) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3800 ] = [  (5*100 +  6*200 +  7*300 +  8*0) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6200 ]   [  (9*100 + 10*200 + 11*300 + 12*0) ]   ( 9 10 11 12)   [ 300 ]
        //                                                    (13 14 15 16)   (   0 )
        assert(vec3fOut == OSG::Vec3f(1400, 3800, 6200));
    
        //
        // void Matrix::mult3x3(const PointType3f& pntIn, PointType3f& pntOut) const;
        //
        pnt3fOut.setNull();
        mat.mult3x3(pnt3fIn, pnt3fOut);
        // [ 1400 ]   [  (1*100 +  2*200 +  3*300) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3800 ] = [  (5*100 +  6*200 +  7*300) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6200 ]   [  (9*100 + 10*200 + 11*300) ]   ( 9 10 11 12)   [ 300 ]
        //                                             (13 14 15 16)
        assert(pnt3fOut == OSG::Pnt3f(1400, 3800, 6200));

        //
        // void Matrix::mult3x3(const VectorType3f& vecIn, VectorType3f& vecOut) const;
        //
        vec3fOut.setNull();
        mat.mult3x3(vec3fIn, vec3fOut);
        // [ 1400 ]   [  (1*100 +  2*200 +  3*300) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3800 ] = [  (5*100 +  6*200 +  7*300) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6200 ]   [  (9*100 + 10*200 + 11*300) ]   ( 9 10 11 12)   [ 300 ]
        //                                             (13 14 15 16)
        assert(vec3fOut == OSG::Vec3f(1400, 3800, 6200));


        //
        // void Matrix::multLeftFull(const PointType3f& pntIn, PointType3f& pntOut) const;
        //
        pnt3fOut.setNull();
        mat.multLeftFull(pnt3fIn, pnt3fOut);
        // [ 0.678952992 ]   [(100*1 + 200*5 + 300* 9 + 1*13)/(100*4 + 200*8 + 300*12 + 1*16)]                          ( 1  2  3  4)
        // [ 0.785968661 ] = [(100*2 + 200*6 + 300*10 + 1*14)/(100*4 + 200*8 + 300*12 + 1*16)] = [100, 200, 300, (1)] * ( 5  6  7  8)
        // [ 0.892984331 ]   [(100*3 + 200*7 + 300*11 + 1*15)/(100*4 + 200*8 + 300*12 + 1*16)]                          ( 9 10 11 12)
        //                                                                                                              (13 14 15 16)
        assert(pnt3fOut.equals(OSG::Pnt3f(0.678952992f, 0.785968661f, 0.892984331f), OSG::Eps));

        //
        // void Matrix::multLeft(const PointType3f& pntIn, PointType3f& pntOut) const;
        //
        pnt3fOut.setNull();
        mat.multLeft(pnt3fIn, pnt3fOut);
        // [ 3813 ]   [(100*1 + 200*5 + 300* 9 + 1*13)]                          ( 1  2  3  4)
        // [ 4414 ] = [(100*2 + 200*6 + 300*10 + 1*14)] = [100, 200, 300, (1)] * ( 5  6  7  8)
        // [ 5015 ]   [(100*3 + 200*7 + 300*11 + 1*15)]                          ( 9 10 11 12)
        //                                                                       (13 14 15 16)
        assert(pnt3fOut == OSG::Pnt3f(3813, 4414, 5015));

        //
        // void Matrix::multLeftFull(const VectorType3f& vecIn, VectorType3f& vecOut) const;
        //
        vec3fOut.setNull();
        mat.multLeftFull(vec3fIn, vec3fOut);
        // [ 0.678571403 ]   [(100*1 + 200*5 + 300* 9 + 0*13)/(100*4 + 200*8 + 300*12 + 0*16)]                          ( 1  2  3  4)
        // [ 0.785714269 ] = [(100*2 + 200*6 + 300*10 + 0*14)/(100*4 + 200*8 + 300*12 + 0*16)] = [100, 200, 300, (0)] * ( 5  6  7  8)
        // [ 0.892857134 ]   [(100*3 + 200*7 + 300*11 + 0*15)/(100*4 + 200*8 + 300*12 + 0*16)]                          ( 9 10 11 12)
        //                                                                                                              (13 14 15 16)
        assert(vec3fOut.equals(OSG::Vec3f(0.678571403f, 0.785714269f, 0.892857134f), OSG::Eps));

        //
        // void Matrix::multLeft(const VectorType3f& vecIn, VectorType3f& vecOut) const;
        //
        vec3fOut.setNull();
        mat.multLeft(vec3fIn, vec3fOut);
        // [ 3800 ]   [(100*1 + 200*5 + 300* 9 + 0*13)]                          ( 1  2  3  4)
        // [ 4400 ] = [(100*2 + 200*6 + 300*10 + 0*14)] = [100, 200, 300, (0)] * ( 5  6  7  8)
        // [ 5000 ]   [(100*3 + 200*7 + 300*11 + 0*15)]                          ( 9 10 11 12)
        //                                                                       (13 14 15 16)
        assert(vec3fOut == OSG::Vec3f(3800, 4400, 5000));
    
        //
        // PointType Matrix::operator*(const PointType& pntIn) const;
        //
        pnt4fOut.setNull();
        pnt4fOut = mat * pnt4fIn;
        // [  3000 ]   [  1*100 +  2*200 +  3*300 +  4*400 ]   ( 1  2  3  4)   [ 100 ]
        // [  7000 ] = [  5*100 +  6*200 +  7*300 +  8*400 ] = ( 5  6  7  8) * [ 200 ]
        // [ 11000 ]   [  9*100 + 10*200 + 11*300 + 12*400 ]   ( 9 10 11 12)   [ 300 ]
        // [ 15000 ]   [ 13*100 + 14*200 + 15*300 + 16*400 ]   (13 14 15 16)   [ 400 ]
        assert(pnt4fOut == OSG::Pnt4f(3000, 7000, 11000, 15000));

        //
        // PointType3f Matrix::operator*(const PointType3f& pntIn) const;
        //
        pnt3fOut.setNull();
        pnt3fOut = mat * pnt3fIn;
        // [ 1404 ]   [  (1*100 +  2*200 +  3*300 +  4*1) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3808 ] = [  (5*100 +  6*200 +  7*300 +  8*1) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6212 ]   [  (9*100 + 10*200 + 11*300 + 12*1) ]   ( 9 10 11 12)   [ 300 ]
        //                                                    (13 14 15 16)   (   1 )
        assert(pnt3fOut == OSG::Pnt3f(1404, 3808, 6212));
          
        //
        // VectorType Matrix::operator*(const VectorType& vecIn) const;
        //
        vec4fOut.setNull();
        vec4fOut = mat * vec4fIn;
        // [  3000 ]   [  1*100 +  2*200 +  3*300 +  4*400 ]   ( 1  2  3  4)   [ 100 ]
        // [  7000 ] = [  5*100 +  6*200 +  7*300 +  8*400 ] = ( 5  6  7  8) * [ 200 ]
        // [ 11000 ]   [  9*100 + 10*200 + 11*300 + 12*400 ]   ( 9 10 11 12)   [ 300 ]
        // [ 15000 ]   [ 13*100 + 14*200 + 15*300 + 16*400 ]   (13 14 15 16)   [ 400 ]
        assert(vec4fOut == OSG::Vec4f(3000, 7000, 11000, 15000));

        //
        // VectorType3f Matrix::operator*(const VectorType3f& vecIn) const;
        //
        vec3fOut.setNull();
        vec3fOut = mat * vec3fIn;
        // [ 1400 ]   [  (1*100 +  2*200 +  3*300 +  4*0) ]   ( 1  2  3  4)   [ 100 ]
        // [ 3800 ] = [  (5*100 +  6*200 +  7*300 +  8*0) ] = ( 5  6  7  8) * [ 200 ]
        // [ 6200 ]   [  (9*100 + 10*200 + 11*300 + 12*0) ]   ( 9 10 11 12)   [ 300 ]
        //                                                    (13 14 15 16)   (   0 )
        assert(vec3fOut == OSG::Vec3f(1400, 3800, 6200));

        //
        // template<class ValueTypeR>
        // void Matrix::mult(const Matrix& mat);
        //
        test = mat;
        test.mult(rhs);
        // ( 9010 10010 11010 12010)   ( 1  2  3  4)   ( 101  201  301  401)
        // (20226 22826 25426 28026)   ( 5  6  7  8)   ( 501  601  701  801)
        // (31442 35642 39842 44042) = ( 9 10 11 12) * ( 901 1001 1101 1201)
        // (42658 48458 54258 60058)   (13 14 15 16)   (1301 1401 1501 1601)
        assert(test == OSG::Matrix(  9010, 10010, 11010, 12010,
                                    20226, 22826, 25426, 28026,
                                    31442, 35642, 39842, 44042,
                                    42658, 48458, 54258, 60058 ));


        //
        // template<class ValueTypeR>
        // void Matrix::multLeft(const Matrix& mat);
        //
        test = mat;
        test.multLeft(rhs);
        // ( 9028 10032 11036 12040)   ( 101  201  301  401)   ( 1  2  3  4)
        // (20228 22832 25436 28040)   ( 501  601  701  801)   ( 5  6  7  8)
        // (31428 35632 39836 44040) = ( 901 1001 1101 1201) * ( 9 10 11 12)
        // (42628 48432 54236 60040)   (1301 1401 1501 1601)   (13 14 15 16)
        assert(test == OSG::Matrix(  9028, 10032, 11036, 12040,
                                    20228, 22832, 25436, 28040,
                                    31428, 35632, 39836, 44040,
                                    42628, 48432, 54236, 60040 ));

        int isdf = 234;
    }

    //
    // transformation of a plane equation
    //
    {
        OSG::Vec3f  n(-0.058649845f, -0.81474495f, -0.57684559f);
        OSG::Real32 d = -15.294896f;

        OSG::Matrix4f lViewProj( 0.00968677550f, -0.00082531053f,  0.00018079198f,  0.01650621000f,
                                -0.00084303610f, -0.01011643400f, -0.00101164330f, -5.15137000000f,
                                -0.00026111995f, -0.00094563351f,  0.00967393440f,  0.01891266900f,
                                 0.00000000000f,  0.00000000000f,  0.00000000000f,  1.00000000000f);
        //
        //             ( 0.00969 -0.00083  0.00018  0.01651)
        // lViewProj = (-0.00084 -0.01012 -0.00101 -5.15137)  
        //             (-0.00026 -0.00095  0.00967  0.01891)  
        //             ( 0.00000  0.00000  0.00000  1.00000)  
        //                                                  _m[0]      _m[1]      _m[2]     _m[3]
        // _m[0] = [ 0.00969,-0.00084,-0.00026, 0.00000]  [ 0.00969] [-0.00083] [ 0.00018] [ 0.01651]
        // _m[1] = [-0.00083,-0.01012,-0.00095, 0.00000]  [-0.00084] [-0.01012] [-0.00101] [-5.15137]
        // _m[2] = [ 0.00018,-0.00101, 0.00967, 0.00000]  [-0.00026] [-0.00095] [ 0.00967] [ 0.01891]
        // _m[3] = [ 0.01651,-5.15137, 0.01891, 1.00000]  [ 0.00000] [ 0.00000] [ 0.00000] [ 1.00000]
        //

        OSG::Matrix4f mat1;         // mat1 = vmath::transpose(vmath::inverse(lViewProj));
        lViewProj.inverse(mat1);    
        mat1.transpose();
        //
        //        (102.454   -8.729   1.912 0.000)
        // mat1 = ( -8.100  -97.202  -9.720 0.000)
        //        ( -2.762  -10.002 102.318 0.000)
        //        (-43.366 -500.390 -52.039 0.000)
        //                                                     _m[0]      _m[1]     _m[2]    _m[3]
        //_m[0] = [102.454,   -8.100,   -2.762,  -43.366]    [102.454] [  -8.729] [  1.912] [0.000]
        //_m[1] = [ -8.729,  -97.202,  -10.002, -500.390]    [ -8.100] [ -97.202] [ -9.720] [0.000]
        //_m[2] = [  1.912,   -9.720,  102.318,  -52.039]    [ -2.762] [ -10.002] [102.318] [0.000]
        //_m[3] = [  0.000,    0.000,    0.000,    1.000]    [-43.366] [-500.390] [-52.039] [0.000]
        //

        OSG::Vec4f eq(n[0], n[1], n[2], -d);    // [-0.058649845, -0.81474495, -0.57684559, +15.294896]
        OSG::Vec4f treq = mat1 * eq;            // [6.1795781e-006, 85.276993, -50.711086, 455.54733]
        n.setValues(treq[0], treq[1], treq[2]); // [6.1795781e-006, 85.276993, -50.711086]
        d = -treq[3];                           // -455.54733
        float len = n.length();                 // 99.21583
        n = n / len;                            // [6.2284194e-008 0.85950994 -0.51111889]
        d = d / len;                            // -4.5914783

        //
        // Now with OSG::Plane
        //
        n.setValues(-0.058649845f, -0.81474495f, -0.57684559f);
        d = -15.294896f;
        OSG::Plane plane1(n, d);
        OSG::Plane plane2(n, d);
        OSG::Plane plane3(n, d);
        OSG::Plane plane4(n, d);

        plane1.transform(lViewProj);                // [6.e-008, 0.8798, -0.4753], -4.6956 -> lViewProj not exactly orthogonal
        plane2.transform(lViewProj, true);          // [6.e-008, 0.8798, -0.4753], -4.6956 -> lViewProj not exactly orthogonal
        plane3.transform(lViewProj, false);         // [6.e-008, 0.8595, -0.5111], -4.5915 -> correct
        plane4.transformTransposedInverse(mat1);    // [6.e-008, 0.8595, -0.5111], -4.5915 -> correct

        int ijk = 234;
    }

    //
    // plane segment intersection test
    //
    {
        OSG::Vec3f normal(0.f, 1.f, 0.f);
        OSG::Real32 distance = 329.10513f;

        OSG::Plane plane(normal, distance);

        OSG::Pnt3f p0(-1.2984413f, 20.400978f, -0.28140914f);
        OSG::Pnt3f p1(-1947.4547f, 621.40247f, -422.06885f);

        OSG::LineSegment segment(p0, p1);

        OSG::Pnt3f intersectionPnt;

        plane.intersect(segment, intersectionPnt);
        // [-1000.94080, 329.105133, -216.932343]

        normal.setValues(0.f, 0.f, 1.f);
        distance = 97.039207f;
        plane.set(normal, distance);

        p0.setValues(-1642.5493f,  -912.82977f, 875.11597f);
        OSG::Vec3f dir(413.07971f, 0.00000000f, -2272.3274f);
        segment.setValue(p0, dir);

        OSG::Real32 param;
        plane.intersect(segment, param);
        // 0.342414021
        plane.intersect(segment, intersectionPnt);
        // [-1501.10498, -912.829773, 97.0391846]

        int ijk = 234;
    }

    //
    // Polygon plane clip test
    //
    {
        OSG::Pnt3f  v0,v1,v2,v3;

        OSG::Plane plane(OSG::Vec3f(0.f, 0.f, 1.f), 97.039207f);

        std::vector<OSG::Polygon> polygons;

        v0.setValues(   -0.94806147f,   19.105848f,    0.47707665f);
        v1.setValues(   -1.06623650f,   20.185675f,    0.86867100f);
        v2.setValues(   80.40770960f,   20.185675f,    1.31347730f);
        v3.setValues(    0.52588457f,   19.105848f,    0.92188287f);
        OSG::Polygon polygon0(v0, v1, v2, v3);
        polygons.push_back(polygon0);

        v0.setValues(    0.52588457f,   19.105848f,    0.92188287f);
        v1.setValues(    0.40770960f,   20.185675f,    1.3134773f);
        v2.setValues(  611.49957000f,  298.481660f, 1970.0073000f);
        v3.setValues(  788.74323000f,-1321.085700f, 1382.6780000f);
        OSG::Polygon polygon1(v0, v1, v2, v3);
        polygons.push_back(polygon1);

        v0.setValues(   -0.94806147f,   19.105848f,    0.47707665f);
        v1.setValues(-1421.94150000f,-1321.0857f,    715.53937000f);
        v2.setValues(-1599.18520000f,  298.48166f,  1302.86850000f);
        v3.setValues(   -1.06623650f,   20.185675f,    0.86867100f);
        OSG::Polygon polygon2(v0, v1, v2, v3);
        polygons.push_back(polygon2);

        v0.setValues(  788.74323000f,-1321.085700f, 1382.67800000f);
        v1.setValues(-1421.94150000f,-1321.085700f,  715.53937000f);
        v2.setValues(   -0.94806147f,   19.105848f,    0.47707665f);
        v3.setValues(    0.52588457f,   19.105848f,    0.92188287f);
        OSG::Polygon polygon3(v0, v1, v2, v3);
        polygons.push_back(polygon3);

        v0.setValues(-1599.18520000f,  298.48166f,  1302.86850000f);
        v1.setValues(  611.49957000f,  298.48166f,  1970.00730000f);
        v2.setValues(    0.40770960f,   20.185675f,    1.31347730f);
        v3.setValues(   -1.06623650f,   20.185675f,    0.86867100f);
        OSG::Polygon polygon4(v0, v1, v2, v3);
        polygons.push_back(polygon4);

        OSG::Polygon::VecVerticesT intersectPoints;

        std::vector<OSG::Polygon>::iterator iter = polygons.begin();
        std::vector<OSG::Polygon>::iterator end  = polygons.end();

        for (; iter != end; ++iter)
        {
            iter->clip(plane, intersectPoints);
        }

        // intersectPoints
        // [  30.121428,  33.717533, 97.039207 ]
        // [  55.355652, -74.120239, 97.039185 ]
        // [-192.839250,-161.873840, 97.039207 ]
        // [-119.109380,  40.741638, 97.039185 ]
        // [-192.839360,-161.873900, 97.039246 ]
        // [  55.355633, -74.120171, 97.039200 ]
        // [  30.121460,  33.717529, 97.039185 ]
        // [-119.109220,  40.741646, 97.039207 ]

        int ijk = 234;
    }

    //
    // BoundingBox test
    //
    {
        OSG::Plane plNear1,   plNear2,   plNear3,   plNear4;
        OSG::Plane plFar1,    plFar2,    plFar3,    plFar4;
        OSG::Plane plLeft1,   plLeft2,   plLeft3,   plLeft4;
        OSG::Plane plRight1,  plRight2,  plRight3,  plRight4;
        OSG::Plane plBottom1, plBottom2, plBottom3, plBottom4;
        OSG::Plane plTop1,    plTop2,    plTop3,    plTop4;

        OSG::BoxVolume box1(OSG::Pnt3f(1,2,3), OSG::Pnt3f(100,90,80));
        plNear1   = box1.getPlane(OSG::BoxVolume::PLANE_NEAR);            // [ 0, 0,-1],  -3
        plFar1    = box1.getPlane(OSG::BoxVolume::PLANE_FAR);             // [ 0, 0, 1],  80
        plLeft1   = box1.getPlane(OSG::BoxVolume::PLANE_LEFT);            // [-1, 0, 0],  -1
        plRight1  = box1.getPlane(OSG::BoxVolume::PLANE_RIGHT);           // [ 1, 0, 0], 100
        plBottom1 = box1.getPlane(OSG::BoxVolume::PLANE_BOTTOM);          // [ 0,-1, 0],  -2
        plTop1    = box1.getPlane(OSG::BoxVolume::PLANE_TOP);             // [ 0, 1, 0],  90

        OSG::BoxVolume box2(OSG::Pnt3f(-1,-2,-3), OSG::Pnt3f(100,90,80));
        plNear2   = box2.getPlane(OSG::BoxVolume::PLANE_NEAR);            // [ 0, 0,-1],   3
        plFar2    = box2.getPlane(OSG::BoxVolume::PLANE_FAR);             // [ 0, 0, 1],  80
        plLeft2   = box2.getPlane(OSG::BoxVolume::PLANE_LEFT);            // [-1, 0, 0],   1
        plRight2  = box2.getPlane(OSG::BoxVolume::PLANE_RIGHT);           // [ 1, 0, 0], 100
        plBottom2 = box2.getPlane(OSG::BoxVolume::PLANE_BOTTOM);          // [ 0,-1, 0],   2
        plTop2    = box2.getPlane(OSG::BoxVolume::PLANE_TOP);             // [ 0, 1, 0],  90

        OSG::BoxVolume box3(OSG::Pnt3f(12,-2.4f,-193), OSG::Pnt3f(-5,-90,80));
        plNear3   = box3.getPlane(OSG::BoxVolume::PLANE_NEAR);            // [ 0, 0,-1], 193
        plFar3    = box3.getPlane(OSG::BoxVolume::PLANE_FAR);             // [ 0, 0, 1],  80
        plLeft3   = box3.getPlane(OSG::BoxVolume::PLANE_LEFT);            // [-1, 0, 0],   5
        plRight3  = box3.getPlane(OSG::BoxVolume::PLANE_RIGHT);           // [ 1, 0, 0],  12
        plBottom3 = box3.getPlane(OSG::BoxVolume::PLANE_BOTTOM);          // [ 0,-1, 0],  90
        plTop3    = box3.getPlane(OSG::BoxVolume::PLANE_TOP);             // [ 0, 1, 0],  -2.4

        OSG::BoxVolume box4(OSG::Pnt3f(-100,-90,-80), OSG::Pnt3f(-1,-2,-3));
        plNear4   = box4.getPlane(OSG::BoxVolume::PLANE_NEAR);            // [ 0, 0,-1],  80
        plFar4    = box4.getPlane(OSG::BoxVolume::PLANE_FAR);             // [ 0, 0, 1],  -3
        plLeft4   = box4.getPlane(OSG::BoxVolume::PLANE_LEFT);            // [-1, 0, 0], 100
        plRight4  = box4.getPlane(OSG::BoxVolume::PLANE_RIGHT);           // [ 1, 0, 0],  -1
        plBottom4 = box4.getPlane(OSG::BoxVolume::PLANE_BOTTOM);          // [ 0,-1, 0],  90
        plTop4    = box4.getPlane(OSG::BoxVolume::PLANE_TOP);             // [ 0, 1, 0],  -2

        int ijk = 234;
    }

    // BoundingBox - Frustum test I
    {
        OSG::BoxVolume box[4];
        box[0] = OSG::BoxVolume(OSG::Pnt3f(   1,  2,      3), OSG::Pnt3f(100, 90,80));
        box[1] = OSG::BoxVolume(OSG::Pnt3f(  -1, -2,     -3), OSG::Pnt3f(100, 90,80));
        box[2] = OSG::BoxVolume(OSG::Pnt3f(  12, -2.4f,-193), OSG::Pnt3f( -5,-90,80));
        box[3] = OSG::BoxVolume(OSG::Pnt3f(-100,-90,    -80), OSG::Pnt3f( -1, -2,-3));

        for (int i = 0; i < 4; ++i)
        {
            OSG::Plane plNearBV, plFarBV, plLeftBV, plRightBV, plBottomBV, plTopBV;
            OSG::Plane plNearFV, plFarFV, plLeftFV, plRightFV, plBottomFV, plTopFV;

            plNearBV   = box[i].getPlane(OSG::BoxVolume::PLANE_NEAR);           // [ 0, 0,-1],  -3   [ 0, 0,-1],   3   [ 0, 0,-1], 193   [ 0, 0,-1],  80
            plFarBV    = box[i].getPlane(OSG::BoxVolume::PLANE_FAR);            // [ 0, 0, 1],  80   [ 0, 0, 1],  80   [ 0, 0, 1],  80   [ 0, 0, 1],  -3
            plLeftBV   = box[i].getPlane(OSG::BoxVolume::PLANE_LEFT);           // [-1, 0, 0],  -1   [-1, 0, 0],   1   [-1, 0, 0],   5   [-1, 0, 0], 100
            plRightBV  = box[i].getPlane(OSG::BoxVolume::PLANE_RIGHT);          // [ 1, 0, 0], 100   [ 1, 0, 0], 100   [ 1, 0, 0],  12   [ 1, 0, 0],  -1
            plBottomBV = box[i].getPlane(OSG::BoxVolume::PLANE_BOTTOM);         // [ 0,-1, 0],  -2   [ 0,-1, 0],   2   [ 0,-1, 0],  90   [ 0,-1, 0],  90
            plTopBV    = box[i].getPlane(OSG::BoxVolume::PLANE_TOP);            // [ 0, 1, 0],  90   [ 0, 1, 0],  90   [ 0, 1, 0],  -2.4 [ 0, 1, 0],  -2

            OSG::Pnt3f nltBV, nlbBV, nrtBV, nrbBV, fltBV, flbBV, frtBV, frbBV;
            box[i].getCorners(nltBV, nlbBV, nrtBV, nrbBV, fltBV, flbBV, frtBV, frbBV);

            // nlbBV = [  1,  2,  3]   [ -1, -2, -3]   [-5,  90,  -193]   [-100,-90,-80]
            // nrbBV = [100,  2,  3]   [100, -2, -3]   [12, -90,  -193]   [  -1,-90,-80]
            // nrtBV = [100, 90,  3]   [100, 90, -3]   [12,  -2.4,-193]   [  -1, -2,-80]
            // nltBV = [  1, 90,  3]   [ -1, 90, -3]   [-5,  -2.4,-193]   [-100, -2,-80]
            // flbBV = [  1,  2, 80]   [ -1, -2, 80]   [-5, -90,    80]   [-100,-90, -3]
            // frbBV = [100,  2, 80]   [100, -2, 80]   [12, -90,    80]   [  -1,-90, -3]
            // frtBV = [100, 90, 80]   [100, 90, 80]   [12,  -2.4,  80]   [  -1, -2, -3]
            // fltBV = [  1, 90, 80]   [ -1, 90, 80]   [-5,  -2.4,  80]   [-100, -2, -3]

            OSG::FrustumVolume frustum;
            frustum.setPlanes(nltBV, nlbBV, nrtBV, nrbBV, fltBV, flbBV, frtBV, frbBV);
            plNearFV   = frustum.getPlane(OSG::FrustumVolume::PLANE_NEAR);      // [ 0, 0,-1],  -3   [ 0, 0,-1],   3   [ 0, 0,-1], 193   [ 0, 0,-1],  80
            plFarFV    = frustum.getPlane(OSG::FrustumVolume::PLANE_FAR);       // [ 0, 0, 1],  80   [ 0, 0, 1],  80   [ 0, 0, 1],  80   [ 0, 0, 1],  -3
            plLeftFV   = frustum.getPlane(OSG::FrustumVolume::PLANE_LEFT);      // [-1, 0, 0],  -1   [-1, 0, 0],   1   [-1, 0, 0],   5   [-1, 0, 0], 100
            plRightFV  = frustum.getPlane(OSG::FrustumVolume::PLANE_RIGHT);     // [ 1, 0, 0], 100   [ 1, 0, 0], 100   [ 1, 0, 0],  12   [ 1, 0, 0],  -1
            plBottomFV = frustum.getPlane(OSG::FrustumVolume::PLANE_BOTTOM);    // [ 0,-1, 0],  -2   [ 0,-1, 0],   2   [ 0,-1, 0],  90   [ 0,-1, 0],  90
            plTopFV    = frustum.getPlane(OSG::FrustumVolume::PLANE_TOP);       // [ 0, 1, 0],  90   [ 0, 1, 0],  90   [ 0, 1, 0],  -2.4 [ 0, 1, 0],  -2

            OSG::Pnt3f nltFV, nlbFV, nrtFV, nrbFV, fltFV, flbFV, frtFV, frbFV;
            nlbFV = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);    // [  1,  2,  3]   [ -1, -2, -3]   [-5,-90,  -193]   [-100,-90, -80]
            nrbFV = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM);   // [100,  2,  3]   [100, -2, -3]   [12,-90,  -193]   [  -1,-90, -80]
            nrtFV = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);      // [100, 90,  3]   [100, 90, -3]   [12, -2.4,-193]   [  -1, -2, -80]
            nltFV = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);       // [  1, 90,  3]   [ -1, 90, -3]   [-5, -2.4,-193]   [-100, -2, -80]
            flbFV = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);     // [  1,  2, 80]   [ -1, -2, 80]   [-5,-90,    80]   [-100,-90,  -3]
            frbFV = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);    // [100,  2, 80]   [100, -2, 80]   [12,-90,    80]   [  -1,-90,  -3]
            frtFV = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);       // [100, 90, 80]   [100, 90, 80]   [12, -2.4,  80]   [  -1, -2,  -3]
            fltFV = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);        // [  1, 90, 80]   [ -1, 90, 80]   [-5, -2.4,  80]   [-100, -2,  -3]

            int ijk = 234;
        }
    }

    // BoundingBox - Frustum test II
    {
        OSG::Matrix4f mat(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );

        OSG::FrustumVolume frustum1, frustum2;
        OSG::BoxVolume box;

        frustum1.setPlanes(mat);
        frustum2.setPlanesOutwards(mat);

        OSG::Pnt3f nlbFV, nrbFV, nrtFV, nltFV, flbFV, frbFV, frtFV, fltFV;
        OSG::Pnt3f nlbBV, nrbBV, nrtBV, nltBV, flbBV, frbBV, frtBV, fltBV;

        OSG::Plane plNearFV, plFarFV, plLeftFV, plRightFV, plBottomFV, plTopFV;
        OSG::Plane plNearBV, plFarBV, plLeftBV, plRightBV, plBottomBV, plTopBV;

        {
            plNearFV   = frustum1.getPlane(OSG::FrustumVolume::PLANE_NEAR);    // [ 0, 0, 1], -1
            plFarFV    = frustum1.getPlane(OSG::FrustumVolume::PLANE_FAR);     // [ 0, 0,-1], -1
            plLeftFV   = frustum1.getPlane(OSG::FrustumVolume::PLANE_LEFT);    // [ 1, 0, 0], -1
            plRightFV  = frustum1.getPlane(OSG::FrustumVolume::PLANE_RIGHT);   // [-1, 0, 0], -1
            plBottomFV = frustum1.getPlane(OSG::FrustumVolume::PLANE_BOTTOM);  // [ 0, 1, 0], -1
            plTopFV    = frustum1.getPlane(OSG::FrustumVolume::PLANE_TOP);     // [ 0,-1, 0], -1

            nlbFV = frustum1.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);  // [-1,-1,-1]
            nrbFV = frustum1.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM); // [ 1,-1,-1]
            nrtFV = frustum1.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);    // [ 1, 1,-1]
            nltFV = frustum1.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);     // [-1, 1,-1]
            flbFV = frustum1.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);   // [-1,-1, 1]
            frbFV = frustum1.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);  // [ 1,-1, 1]
            frtFV = frustum1.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);     // [ 1, 1, 1]
            fltFV = frustum1.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);      // [-1, 1, 1]
        
            box.setBounds(nlbFV[0], frtFV[0], nlbFV[1], frtFV[1], nlbFV[2], frtFV[2]);

            nlbBV = box.getCorner(OSG::BoxVolume::NEAR_LEFT_BOTTOM);  // [-1,-1,-1]
            nrbBV = box.getCorner(OSG::BoxVolume::NEAR_RIGHT_BOTTOM); // [ 1,-1,-1]
            nrtBV = box.getCorner(OSG::BoxVolume::NEAR_RIGHT_TOP);    // [ 1, 1,-1]
            nltBV = box.getCorner(OSG::BoxVolume::NEAR_LEFT_TOP);     // [-1, 1,-1]
            flbBV = box.getCorner(OSG::BoxVolume::FAR_LEFT_BOTTOM);   // [-1,-1, 1]
            frbBV = box.getCorner(OSG::BoxVolume::FAR_RIGHT_BOTTOM);  // [ 1,-1, 1]
            frtBV = box.getCorner(OSG::BoxVolume::FAR_RIGHT_TOP);     // [ 1, 1, 1]
            fltBV = box.getCorner(OSG::BoxVolume::FAR_LEFT_TOP);      // [-1, 1, 1]

            plNearBV   = box.getPlane(OSG::BoxVolume::PLANE_NEAR);      // [ 0, 0,-1],  1
            plFarBV    = box.getPlane(OSG::BoxVolume::PLANE_FAR);       // [ 0, 0, 1],  1
            plLeftBV   = box.getPlane(OSG::BoxVolume::PLANE_LEFT);      // [-1, 0, 0],  1
            plRightBV  = box.getPlane(OSG::BoxVolume::PLANE_RIGHT);     // [ 1, 0, 0],  1 
            plBottomBV = box.getPlane(OSG::BoxVolume::PLANE_BOTTOM);    // [ 0,-1, 0],  1
            plTopBV    = box.getPlane(OSG::BoxVolume::PLANE_TOP);       // [ 0, 1, 0],  1

            int ijk = 234;
        }
        {
            plNearFV   = frustum2.getPlane(OSG::FrustumVolume::PLANE_NEAR);    // [ 0, 0,-1], 1
            plFarFV    = frustum2.getPlane(OSG::FrustumVolume::PLANE_FAR);     // [ 0, 0, 1], 1
            plLeftFV   = frustum2.getPlane(OSG::FrustumVolume::PLANE_LEFT);    // [-1, 0, 0], 1
            plRightFV  = frustum2.getPlane(OSG::FrustumVolume::PLANE_RIGHT);   // [ 1, 0, 0], 1
            plBottomFV = frustum2.getPlane(OSG::FrustumVolume::PLANE_BOTTOM);  // [ 0,-1, 0], 1
            plTopFV    = frustum2.getPlane(OSG::FrustumVolume::PLANE_TOP);     // [ 0, 1, 0], 1

            nlbFV = frustum2.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);  // [-1,-1,-1]
            nrbFV = frustum2.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM); // [ 1,-1,-1]
            nrtFV = frustum2.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);    // [ 1, 1,-1]
            nltFV = frustum2.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);     // [-1, 1,-1]
            flbFV = frustum2.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);   // [-1,-1, 1]
            frbFV = frustum2.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);  // [ 1,-1, 1]
            frtFV = frustum2.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);     // [ 1, 1, 1]
            fltFV = frustum2.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);      // [-1, 1, 1]
        
            box.setBounds(nlbFV[0], frtFV[0], nlbFV[1], frtFV[1], nlbFV[2], frtFV[2]);

            nlbBV = box.getCorner(OSG::BoxVolume::NEAR_LEFT_BOTTOM);  // [-1,-1,-1]
            nrbBV = box.getCorner(OSG::BoxVolume::NEAR_RIGHT_BOTTOM); // [ 1,-1,-1]
            nrtBV = box.getCorner(OSG::BoxVolume::NEAR_RIGHT_TOP);    // [ 1, 1,-1]
            nltBV = box.getCorner(OSG::BoxVolume::NEAR_LEFT_TOP);     // [-1, 1,-1]
            flbBV = box.getCorner(OSG::BoxVolume::FAR_LEFT_BOTTOM);   // [-1,-1, 1]
            frbBV = box.getCorner(OSG::BoxVolume::FAR_RIGHT_BOTTOM);  // [ 1,-1, 1]
            frtBV = box.getCorner(OSG::BoxVolume::FAR_RIGHT_TOP);     // [ 1, 1, 1]
            fltBV = box.getCorner(OSG::BoxVolume::FAR_LEFT_TOP);      // [-1, 1, 1]

            plNearBV   = box.getPlane(OSG::BoxVolume::PLANE_NEAR);      // [ 0, 0,-1],  1
            plFarBV    = box.getPlane(OSG::BoxVolume::PLANE_FAR);       // [ 0, 0, 1],  1
            plLeftBV   = box.getPlane(OSG::BoxVolume::PLANE_LEFT);      // [-1, 0, 0],  1
            plRightBV  = box.getPlane(OSG::BoxVolume::PLANE_RIGHT);     // [ 1, 0, 0],  1 
            plBottomBV = box.getPlane(OSG::BoxVolume::PLANE_BOTTOM);    // [ 0,-1, 0],  1
            plTopBV    = box.getPlane(OSG::BoxVolume::PLANE_TOP);       // [ 0, 1, 0],  1

            int ijk = 234;
        }
    }

    // Frustum transform and corner test
    {
        // Let M be the transformation that maps from the view frustum into the unit bounding box
        // Then,                                     -1
        //          q' = M * q                  q = M   * q'
        //
        //                 -1 T                      T
        //          L' = (M  ) * L              L = M   * L'
        //
        //                                                            -1
        // Now let S = invEyeViewProj be the inverse of M, i.e. S = M
        // Then,          -1
        //          q' = S  * q                 q = S * q'
        //
        //                T                           -1 T
        //          L' = S  * L                 L = (S  ) * L'
        //
        {
            OSG::Matrix4f invEyeViewProj(
                -0.72110826f,      0.099096067f,    -9.0407127e-008f,  0.30503249f,
                -4.0614378e-007f,  0.50316292f,    -18.835268f,       19.509626f,
                 0.26943529f,      0.26521787f,      4.1242672e-007f,  0.81637925f,
                -1.1266424e-008f, -1.2139417e-008f, -0.94176346f,      1.0000008f);
            //
            //                  (-0.72111  0.09910  -9.e-008  0.30503)
            // invEyeViewProj = (-4.e-007  0.50316 -18.83527 19.50963)
            //                  ( 0.26943  0.26522   4.e-007  0.81638)
            //                  (-1.e-008 -1.e-008  -0.94176  1.00000)
            //                                                        _m[0]      _m[1]      _m[2]     _m[3]
            //   _m[0] = [-0.72111, -4.e-007,   0.26943, -1.e-008]  [-0.72111][ 0.09910][ -9.e-008][ 0.30503]
            //   _m[1] = [ 0.09910,  0.50316,   0.26522, -1.e-008]  [-4.e-007][ 0.50316][-18.83527][19.50963]
            //   _m[2] = [-9.e-008, -18.83527,  4.e-007, -0.94176]  [ 0.26943][ 0.26522][  4.e-007][ 0.81638]
            //   _m[3] = [ 0.30503,  19.50963,  0.81638,  1.00000]  [-1.e-008][-1.e-008][ -0.94176][ 1.00000]
            //

            OSG::Matrix4f mat1;         // mat1 = vmath::transpose(vmath::inverse(invEyeViewProj));
            invEyeViewProj.inverse(mat1);
            //
            //        (-1.217 -0.000  0.455   0.000)
            // mat1 = ( 0.297  1.509  0.796 -30.190)
            //        ( 0.324 -0.521  0.867   9.352)
            //        ( 0.305 -0.490  0.816   9.808)
            //                                                    _m[0]     _m[1]     _m[2]     _m[3]
            //    _m[0] = [-1.217,   0.297,  0.324,  0.305]     [-1.217]  [-0.000]  [ 0.455]  [  0.000]
            //    _m[1] = [-0.000,   1.509, -0.521, -0.490]     [ 0.297]  [ 1.509]  [ 0.796]  [-30.190]
            //    _m[2] = [ 0.455,   0.796,  0.867,  0.816]     [ 0.324]  [-0.521]  [ 0.867]  [  9.352]
            //    _m[3] = [ 0.000, -30.190,  9.352,  9.808]     [ 0.305]  [-0.490]  [ 0.816]  [  9.808]
            //

            OSG::FrustumVolume frustum;
            frustum.setPlanesOutwards(mat1);

            OSG::Plane plNear, plFar, plLeft, plRight, plTop, plBottom;

            OSG::Pnt3f near_left_bottom, near_right_bottom, near_right_top, near_left_top, 
                        far_left_bottom,  far_right_bottom,  far_right_top,  far_left_top;

            plNear   = frustum.getPlane(OSG::FrustumVolume::PLANE_NEAR);     // {-0.305032223  0.490389019 -0.816378593},   9.29278278
            plFar    = frustum.getPlane(OSG::FrustumVolume::PLANE_FAR);      // { 0.305031657 -0.490389079  0.816378713},   7.36332417
            plLeft   = frustum.getPlane(OSG::FrustumVolume::PLANE_LEFT);     // { 0.556216419  0.299134374 -0.775333405},   5.98268747
            plRight  = frustum.getPlane(OSG::FrustumVolume::PLANE_RIGHT);    // {-0.928351939  0.299134284 -0.220638648},   5.98268414
            plTop    = frustum.getPlane(OSG::FrustumVolume::PLANE_TOP);      // {-0.003872351  0.999938786 -0.010363164},  19.99877360
            plBottom = frustum.getPlane(OSG::FrustumVolume::PLANE_BOTTOM);   // {-0.301159948 -0.509550393 -0.806015551}, -10.19100760

            near_left_bottom  = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);  // { 0.477426529  19.4883232   0.145087719}
            near_right_bottom = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM); // {-0.265309334  19.4883232   0.422603607}
            near_right_top    = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);    // {-0.163241878  20.0065765   0.695774674}
            near_left_top     = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);     // { 0.579492092  20.0065765   0.418259382}
            far_left_bottom   = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);   // {15.9183750     2.93962598  4.83755302 }
            far_right_bottom  = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);  // {-8.84605789    2.93963504 14.0905390  }
            far_right_top     = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);     // {-5.44288588   20.2193470  23.1986961  }
            far_left_top      = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);      // {19.3215542    20.2193527  13.9457188  }

            int ijk = 234;
        }

        {
            OSG::Matrix4f invEyeViewProj(
               -0.72110826f,     0.099096075f,   -5.4491289e-010f, 0.30503222f,
                6.7199948e-009f, 0.50316292f,    -0.11352624f,    -0.13661544f,
                0.26943535f,     0.26521760f,     2.4858289e-009f, 0.81637865f,
                3.2070208e-011f,-4.2300885e-010f,-0.0056763124f,   0.017688671f);
            //
            //                  (-0.72111  0.09910 -5.e-010  0.30503)
            // invEyeViewProj = ( 6.e-009  0.50316 -0.11353 -0.13662)
            //                  ( 0.26944  0.26522  2.e-009  0.81638)
            //                  ( 3.e-011 -4.e-010 -0.00568  0.01769)
            //                                                       _m[0]       _m[1]       _m[2]       _m[3]
            //  _m[0] = [-0.72111,  6.e-009, 0.26944,  3.e-011]    [-0.72111]  [ 0.09910]  [-5.e-010]  [ 0.30503]
            //  _m[1] = [ 0.09910,  0.50316, 0.26522, -4.e-010]    [ 6.e-009]  [ 0.50316]  [-0.11353]  [-0.13662]
            //  _m[2] = [-5.e-010, -0.11353, 2.e-009, -0.00568]    [ 0.26944]  [ 0.26522]  [ 2.e-009]  [ 0.81638]
            //  _m[3] = [ 0.30503, -0.13662, 0.81638,  0.01769]    [ 3.e-011]  [-4.e-010]  [-0.00568]  [ 0.01769]
            //

            OSG::Matrix4f mat1;         // mat1 = vmath::transpose(vmath::inverse(invEyeViewProj));
            invEyeViewProj.inverse(mat1);

            //
            //        (-1.21687  1.e-008 0.45467    3.e-007)
            // mat1 = ( 0.29729  1.50949 0.79565  -30.18977)
            //        ( 0.95055 -1.52816 2.54402 -145.60747)
            //        ( 0.30503 -0.49039 0.81638    9.80778)
            //                                                           _m[0]       _m[1]      _m[2]       _m[3]
            //   _m[0] = [-1.21687,  0.29729,   0.95055,  0.30503]    [-1.21687]  [ 1.e-008]  [0.45467]  [   3.e-007]
            //   _m[1] = [ 1.e-008,  1.50949,  -1.52816, -0.49039]    [ 0.29729]  [ 1.50949]  [0.79565]  [ -30.18977]
            //   _m[2] = [ 0.45467,  0.79565,   2.54402,  0.81638]    [ 0.95055]  [-1.52816]  [2.54402]  [-145.60747]
            //   _m[3] = [ 3.e-007,-30.18977,-145.60747,  9.80778]    [ 0.30503]  [-0.49039]  [0.81638]  [   9.80778]
            //

            OSG::FrustumVolume frustum;
            frustum.setPlanesOutwards(mat1);

            OSG::Plane plNear, plFar, plLeft, plRight, plTop, plBottom;

            OSG::Pnt3f near_left_bottom, near_right_bottom, near_right_top, near_left_top, 
                        far_left_bottom,  far_right_bottom,   far_right_top, far_left_top;

            plNear   = frustum.getPlane(OSG::FrustumVolume::PLANE_NEAR);   // {-0.305032253  0.490388900 -0.816378653}, -32.9913177
            plFar    = frustum.getPlane(OSG::FrustumVolume::PLANE_FAR);    // { 0.305032283 -0.490388960  0.816378653},  73.4398270
            plLeft   = frustum.getPlane(OSG::FrustumVolume::PLANE_LEFT);   // { 0.556216002  0.299134403 -0.775333703},   5.98268795
            plRight  = frustum.getPlane(OSG::FrustumVolume::PLANE_RIGHT);  // {-0.928351820  0.299134374 -0.220638856},   5.98268747
            plTop    = frustum.getPlane(OSG::FrustumVolume::PLANE_TOP);    // {-0.003872007  0.999938786 -0.010362924},  19.9987755
            plBottom = frustum.getPlane(OSG::FrustumVolume::PLANE_BOTTOM); // {-0.301160246 -0.509549916 -0.806015790}, -10.1909971

            near_left_bottom  = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);  // { 39.6766586, -22.5231190,  12.0576038}
            near_right_bottom = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM); // {-22.0489006, -22.5231209,  35.1207809}
            near_right_top    = frustum.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);    // {-13.5664539,  20.5467167,  57.8229256}
            near_left_top     = frustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);     // { 48.1591034,  20.5467186,  34.7597504}
            far_left_bottom   = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);   // { 77.1742249, -62.7108116,  23.4529877}
            far_right_bottom  = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);  // {-42.8868523, -62.7108269,  68.3126907}
            far_right_top     = frustum.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);     // {-26.3878231,  21.0634079, 112.470154 }
            far_left_top      = frustum.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);      // { 93.6732635,  21.0634117,  67.6104660}

            int ijk = 234;
        }
    }

    // PolygonBody test
    {
        {
            OSG::PolygonBody body;

            // near polygon ccw
            OSG::Polygon* p1 = new OSG::Polygon(
                OSG::Pnt3f(-0.76980060f, 19.422653f, -1.0000001f), 
                OSG::Pnt3f(0.76980060f, 19.422653f, -1.0000001f), 
                OSG::Pnt3f(0.76980060f, 20.577354f, -1.0000001f), 
                OSG::Pnt3f(-0.76980060f, 20.577354f, -1.0000001f));

            // far polygon ccw
            OSG::Polygon* p2 = new OSG::Polygon(
                OSG::Pnt3f(-1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(1154.7845f, -846.08868f, -1500.1088f), 
                OSG::Pnt3f(-1154.7845f, -846.08868f, -1500.1088f));

            // left polygon ccw
            OSG::Polygon* p3 = new OSG::Polygon(
                OSG::Pnt3f(-0.76980060f, 19.422653f, -1.0000001f), 
                OSG::Pnt3f(-0.76980060f, 20.577354f, -1.0000001f), 
                OSG::Pnt3f(-1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(-1154.7845f, -846.08868f, -1500.1088f));

            // right polygon ccw
            OSG::Polygon* p4 = new OSG::Polygon(
                OSG::Pnt3f(0.76980060f, 19.422653f, -1.0000001f), 
                OSG::Pnt3f(1154.7845f, -846.08868f, -1500.1088f), 
                OSG::Pnt3f(1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(0.76980060f, 20.577354f, -1.0000001f));

            // bottom polygon ccw
            OSG::Polygon* p5 = new OSG::Polygon(
                OSG::Pnt3f(-1154.7845f, -846.08868f, -1500.1088f), 
                OSG::Pnt3f(1154.7845f, -846.08868f, -1500.1088f), 
                OSG::Pnt3f(0.76980060f, 19.422653f, -1.0000001f), 
                OSG::Pnt3f(-0.76980060f, 19.422653f, -1.0000001f));

            // top polygon ccw
            OSG::Polygon* p6 = new OSG::Polygon(
                OSG::Pnt3f(1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(-1154.7845f, 886.08868f, -1500.1088f), 
                OSG::Pnt3f(-0.76980060f, 20.577354f, -1.0000001f), 
                OSG::Pnt3f(0.76980060f, 20.577354f, -1.0000001f));

            body.add(p1);
            body.add(p2);
            body.add(p3);
            body.add(p4);
            body.add(p5);
            body.add(p6);

            OSG::BoxVolume aabb(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f), OSG::Pnt3f(97.039207f, 63.168030f, 97.039207f));
            body.clip(aabb);

            body.createUniqueVertices();

            //   [0] {  0.76980060, 20.577354,    -1.0000001}
            //   [1] { -0.76980060, 20.577354,    -1.0000001}
            //   [2] { -0.76980060, 19.422653,    -1.0000001}
            //   [3] {  0.76980060, 19.422653,    -1.0000001}
            //   [4] {-57.557354,   63.168030,   -74.769173 }
            //   [5] {-74.700829,   63.168030,   -97.039207 }
            //   [6] {-74.700813,   -0.099998474,-97.039192 }
            //   [7] {-26.799988,   -0.099998474,-34.814201 }
            //   [8] { 74.700829,   -0.10000229, -97.039200 }
            //   [9] { 74.700813,   63.168030,   -97.039185 }
            //  [10] { 57.557343,   63.168030,   -74.769173 }
            //  [11] { 26.799997,   -0.10000038, -34.814209 }
            //  [12] {-26.799997,   -0.10000038, -34.814209 }
            //  [13] { 26.799988,   -0.099998474,-34.814201 }
            //  [14] {-57.557343,   63.168030,   -74.769173 }
            //  [15] { 57.557354,   63.168030,   -74.769173 }
            //  [16] { 57.557343,   63.168030,   -97.039185 }
            //  [17] {-26.799988,   -0.10000610, -97.039185 }
            //  [18] {-74.700813,   -0.10000229, -97.039192 }
            //  [19] {-74.700813,   63.168030,   -97.039185 }
            //  [20] {-74.700829,   -0.10000610, -97.039200 }

            int ijk = 234;
        }

        {
            OSG::PolygonBody body;

            // near polygon ccw
            OSG::Polygon* p1 = new OSG::Polygon(
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f), 
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f));

            // far polygon ccw
            OSG::Polygon* p2 = new OSG::Polygon(
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f));

            // left polygon ccw
            OSG::Polygon* p3 = new OSG::Polygon(
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f), 
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f));

            // right polygon ccw
            OSG::Polygon* p4 = new OSG::Polygon(
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f));

            // bottom polygon ccw
            OSG::Polygon* p5 = new OSG::Polygon(
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f));

            // top polygon ccw
            OSG::Polygon* p6 = new OSG::Polygon(
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f));

            body.add(p1);
            body.add(p2);
            body.add(p3);
            body.add(p4);
            body.add(p5);
            body.add(p6);

            OSG::BoxVolume aabb(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f), OSG::Pnt3f(97.039207f, 63.168030f, 97.039207f));
            body.clip(aabb);

            body.extrude(OSG::Vec3f(OSG::Pnt3f(-369.38138f, 448.11539f, -169.85291f) - OSG::Pnt3f(0.f, 0.f, 0.f)), aabb);

            body.clip(aabb);

            //  [0] {  4.67488718, 31.3571892, -37.5240936 }
            //  [1] {  6.20812082, 31.3571873, -37.6640015 }
            //  [2] {  6.16522360, 30.3033810, -38.1341019 }
            //  [3] {  4.63198996, 30.3033829, -37.9941940 }
            //  [4] {-13.6468077,   6.04745770,-18.7144184 }
            //  [5] { 27.6316051,   6.04740620,-22.4810886 }
            //  [6] { 28.7865047,  34.4184608, -9.82480812 }
            //  [7] {-12.4919071,  34.4185104, -6.05813837 }
            //  [8] {-21.5467796,  63.1680298, -49.5816231 }
            //  [9] {-20.0135460,  63.1680298, -49.7215309 }
            // [10] {-20.9250965,  63.1680298, -50.5910645 }
            // [11] {-22.4583302,  63.1680298, -50.4511566 }
            // [12] {-60.7312737,  63.1680260, -40.3653030 }
            // [13] {-19.4529057,  63.1680260, -44.1319923 }
            // [14] {  5.08824348, 63.1680298, -20.7219963 }
            // [15] {-36.1901245,  63.1680298, -16.9553089 }

            int ijk = 234;
        }

        {
            OSG::PolygonBody body;

            // near polygon ccw
            OSG::Polygon* p1 = new OSG::Polygon(
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f), 
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f));

            // far polygon ccw
            OSG::Polygon* p2 = new OSG::Polygon(
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f));

            // left polygon ccw
            OSG::Polygon* p3 = new OSG::Polygon(
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f), 
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f));

            // right polygon ccw
            OSG::Polygon* p4 = new OSG::Polygon(
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f));

            // bottom polygon ccw
            OSG::Polygon* p5 = new OSG::Polygon(
                OSG::Pnt3f(27.631605f, 6.0474062f, -22.481089f), 
                OSG::Pnt3f(-13.646808f, 6.0474577f, -18.714418f), 
                OSG::Pnt3f(4.6319900f, 30.303383f, -37.994194f), 
                OSG::Pnt3f(6.1652236f, 30.303381f, -38.134102f));

            // top polygon ccw
            OSG::Polygon* p6 = new OSG::Polygon(
                OSG::Pnt3f(-12.491907f, 34.418510f, -6.0581384f), 
                OSG::Pnt3f(28.786505f, 34.418461f, -9.8248081f), 
                OSG::Pnt3f(6.2081208f, 31.357187f, -37.664001f), 
                OSG::Pnt3f(4.6748872f, 31.357189f, -37.524094f));

            body.add(p1);
            body.add(p2);
            body.add(p3);
            body.add(p4);
            body.add(p5);
            body.add(p6);

            OSG::BoxVolume aabb(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f), OSG::Pnt3f(97.039207f, 63.168030f, 97.039207f));
            body.clip(aabb);

            body.createConvexHull(OSG::Pnt3f(-369.38138f, 448.11539f, -169.85291f));

            OSG::Plane plNear   (OSG::Vec3f(-0.61048514f,  0.74061066f, -0.28071985f), 247.05276f), 
                       plFar    (OSG::Vec3f( 0.61048520f, -0.74061060f,  0.28071988f),  86.555931f), 
                       plLeft   (OSG::Vec3f(-0.92862451f, -0.34693497f,  0.13150162f), 165.21375f), 
                       plRight  (OSG::Vec3f( 0.59523535f,  0.75138634f, -0.28480414f), 165.21371f), 
                       plBottom (OSG::Vec3f(-0.16669457f,  0.54318881f,  0.82289660f), 165.21373f), 
                       plTop    (OSG::Vec3f(-0.16669455f, -0.13873750f, -0.97619921f), 165.21376f);

            OSG::FrustumVolume lFrust(plNear, plFar, plLeft, plRight, plTop, plBottom);

            body.clip(lFrust);
            body.clip(aabb);

            body.createUniqueVertices();

            //  [0] {-12.491889,  34.418598, -6.0580692 }
            //  [1] { 28.786419,  34.418446, -9.8247709 }
            //  [2] {  1.1160164, 63.168030, -20.945816 }
            //  [3] {-37.293556,  63.168030, -17.440823 }
            //  [4] {-13.646901,   6.0473685,-18.714413 }
            //  [5] {-37.293564,  63.168030, -17.440823 }
            //  [6] {-59.612213,  63.168030, -38.243382 }
            //  [7] { 27.631639,   6.0473080,-22.481112 }
            //  [8] {  6.2081275, 31.357132, -37.664093 }
            //  [9] {-22.460390,  63.168030, -47.753983 }
            // [10] {  1.1160278, 63.168030, -20.945816 }
            // [11] {  4.6319666, 30.303387, -37.994129 }
            // [12] {-59.612206,  63.168030, -38.243378 }
            // [13] {-24.787521,  63.168030, -48.365997 }
            // [14] {  6.1652594, 30.303417, -38.134014 }
            // [15] {-23.374817,  63.168030, -48.494873 }
            // [16] {-22.460388,  63.168022, -47.753983 }
            // [17] {-24.787525,  63.168030, -48.365997 }
            // [18] {-23.374825,  63.168030, -48.494869 }

            int ijk = 234;
        }
    }

    // Little transformation test
    {
        OSG::Matrix4f lViewProjMat(
                -0.0073318263f, -0.0033760236f, -0.0025865268f,  0.067520469f,
                -0.0037693817f,  0.0027709638f,  0.0070680156f, -0.055419277f,
                 0.0012322352f, -0.0045445818f,  0.0024388228f, -2.4743109f,
                 0.00000000f,    0.00000000f,    0.00000000f,    1.0000000f);

        OSG::Pnt3f center(-1.6575359f, 19.893993f, 1.4721632f);
        OSG::Pnt3f nearCamPt(-1.2126635f, 20.219912f, 0.63797742f);

        OSG::Pnt3f trCenter, trNearCamPt;

        lViewProjMat.multFull(center,    trCenter);
        lViewProjMat.multFull(nearCamPt, trNearCamPt);

        OSG::Vec3f projViewDir_LS(trCenter - trNearCamPt);
        // [0.00220439211, 0.00666982681, 0.00296735764]

        int ijk = 234;
    }

    // LiSP tests
    {
        // LiSP test I
        {
            //
            // This test takes values from DirectX example
            //
            OSG::LiSPSMTechnique liSP(1);

            liSP.setMode(OSG::LiSPSMTechnique::NOPT);
            liSP.setArbScaled(false);
            liSP.setParamN(1.f, 0);
            liSP.setSplitParam(0.5f);

            OSG::Matrix4f matLightProj(
                0.0087762913f, 0.00000000f,   0.00000000f,    0.00000000f,
                0.00000000f,   0.0087762913f, 0.00000000f,    0.00000000f,
                0.00000000f,   0.00000000f,  -0.0052931984f, -2.5814035f,
                0.00000000f,   0.00000000f,   0.00000000f,    1.0000000f);
            liSP.setLightProjMat(matLightProj, OSG::Projection::ORTHOGRAPHIC);

            OSG::Matrix4f matLightView(
                -0.83052868f, -0.41207841f, -0.37471759f, 28.424620f,
                -0.55458331f,  0.54953837f,  0.62485582f, -2.4752662f,
                -0.051567912f, 0.72677296f, -0.68493932f,-13.445474f,
                 0.00000000f,  0.00000000f,  0.00000000f,  1.0000000f);

            OSG::View viewLightView(
                OSG::Pnt3f(-31.201782f,      439.74268f,  -414.43073f),
                OSG::Pnt3f(  0.00000000f,      0.00000000f,  0.00000000f),
                OSG::Vec3f(  5.9554767e-010f, -0.68585175f, -0.72774118f));

            liSP.setLightView(matLightView, viewLightView);

            OSG::Matrix4f matCamView(
                -0.74791080f, 0.00000000f, -0.66379929f, 18.094826f,
                -0.27553046f, 0.90978438f,  0.31044355f,-15.776711f,
                 0.60391420f, 0.41508099f, -0.68043751f,-20.458235f,
                 0.00000000f, 0.00000000f,  0.00000000f, 1.0000000f);

            OSG::View viewCamView(
                OSG::Pnt3f(21.541370f,  22.845234f,  2.9885583f),
                OSG::Pnt3f(20.937456f,  22.430153f,  3.6689959f),
                OSG::Vec3f (0.00000000f, 1.0000000f, 0.00000000f)
                );

            liSP.setCamView(matCamView, viewCamView);

            OSG::Matrix4f matCamProj(
                 1.2990381f,  0.00000000f,  0.00000000f,  0.00000000f,
                 0.00000000f, 1.7320508f,   0.00000000f,  0.00000000f,
                 0.00000000f, 0.00000000f, -1.0069381f,  -1.0069389f,
                 0.00000000f, 0.00000000f, -1.0000000f,   0.00000000f);

            liSP.setCamProjMat(matCamProj);

            liSP.setFieldOfView(60.000000f);
            liSP.setGamma(42.558643f);
            liSP.setSplitParam(0.50000000f);
            liSP.setPseudoNear(0.00000000f);
            liSP.setPseudoFar(0.00000000f);

            // Artificially construct a PolygonBody for the test
            OSG::PolygonBody bodyB;

            OSG::Polygon* p1 = new OSG::Polygon;
            p1->addVertex(OSG::Pnt3f( 20.202635f,  22.955418f,   3.3372376f));
            p1->addVertex(OSG::Pnt3f( 21.354120f,  22.955418f,   4.3592257f));
            p1->addVertex(OSG::Pnt3f( 21.672276f,  21.904886f,   4.0007563f));
            p1->addVertex(OSG::Pnt3f( 20.520790f,  21.904886f,   2.9787679f));
            p1->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f, -34.560703f));
            p1->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f, -33.538715f));
            p1->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f, -34.887249f));
            p1->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f, -35.909237f));

            OSG::Polygon* p2 = new OSG::Polygon;
            p2->addVertex(OSG::Pnt3f(-97.039207f, -0.10000610f,  97.038437f));
            p2->addVertex(OSG::Pnt3f(-97.038353f, -0.10000610f,  97.039200f));
            p2->addVertex(OSG::Pnt3f(-97.039207f, -0.098762877f, 97.039200f));
            p2->addVertex(OSG::Pnt3f(-97.039207f, -0.087963305f, 97.027847f));
            p2->addVertex(OSG::Pnt3f(-97.039207f, -0.098762877f, 97.039200f));

            OSG::Polygon* p3 = new OSG::Polygon;
            p3->addVertex(OSG::Pnt3f( 21.354120f,  22.955418f,     4.3592257f));
            p3->addVertex(OSG::Pnt3f(  8.6928453f, 30.405632f,    97.039207f));
            p3->addVertex(OSG::Pnt3f( 16.729954f,  -0.099998474f, 97.039207f));
            p3->addVertex(OSG::Pnt3f( 24.735554f,  -0.099998474f, 27.686996f));
            p3->addVertex(OSG::Pnt3f( 21.672276f,  21.904886f,     4.0007563f));
            p3->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            p3->addVertex(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            p3->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            p3->addVertex(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            p3->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));

            OSG::Polygon* p4 = new OSG::Polygon;
            p4->addVertex(OSG::Pnt3f(-97.039215f,  -0.10000455f, 25.074013f));
            p4->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,   33.873398f));
            p4->addVertex(OSG::Pnt3f( 20.202635f,  22.955418f,    3.3372376f));
            p4->addVertex(OSG::Pnt3f( 20.520790f,  21.904886f,    2.9787679f));
            p4->addVertex(OSG::Pnt3f( -3.3615990f, -0.10000229f,  2.7496789f));
            p4->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,   33.873398f));
            p4->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f,  -34.560703f));
            p4->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f,  -35.909237f));
            p4->addVertex(OSG::Pnt3f( -7.8507590f, 63.168030f,  -56.876591f));

            OSG::Polygon* p5 = new OSG::Polygon;
            p5->addVertex(OSG::Pnt3f( 24.735556f,  -0.10000038f,  27.686996f));
            p5->addVertex(OSG::Pnt3f( -3.3615875f, -0.099998474f,  2.7496789f));
            p5->addVertex(OSG::Pnt3f( 20.520790f,  21.904886f,     2.9787679f));
            p5->addVertex(OSG::Pnt3f( 21.672276f,  21.904886f,     4.0007563f));
            p5->addVertex(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            p5->addVertex(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            p5->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            p5->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));

            OSG::Polygon* p6 = new OSG::Polygon;
            p6->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,  97.039207f));
            p6->addVertex(OSG::Pnt3f(  8.6928444f, 30.405632f,  97.039207f));
            p6->addVertex(OSG::Pnt3f( 21.354120f,  22.955418f,   4.3592257f));
            p6->addVertex(OSG::Pnt3f( 20.202635f,  22.955418f,   3.3372376f));
            p6->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,  33.873394f));
            p6->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,  97.039207f));
            p6->addVertex(OSG::Pnt3f(  6.3682003f, 63.168030f,  66.162643f));
            p6->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f, -33.538715f));
            p6->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f, -34.560703f));
            p6->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,  33.873394f));

            OSG::Polygon* p7 = new OSG::Polygon;
            p7->addVertex(OSG::Pnt3f(-64.470268f,  -0.099998474f, 97.039207f));
            p7->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p7->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p7->addVertex(OSG::Pnt3f(-97.038361f,  -0.10000229f,  97.039200f));
            p7->addVertex(OSG::Pnt3f(  2.8259430f, -0.099998474f, 97.039207f));
            p7->addVertex(OSG::Pnt3f(  8.6928453f, 30.405632f,    97.039207f));
            p7->addVertex(OSG::Pnt3f( 16.729954f,  -0.099998474f, 97.039207f));
            p7->addVertex(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            p7->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p7->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p7->addVertex(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            p7->addVertex(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));
            p7->addVertex(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            p7->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));

            OSG::Polygon* p8 = new OSG::Polygon;
            p8->addVertex(OSG::Pnt3f( 24.735556f,  -0.10000038f,  27.686996f));
            p8->addVertex(OSG::Pnt3f( -3.3615875f, -0.099998474f,  2.7496789f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000301f,  25.074013f));
            p8->addVertex(OSG::Pnt3f(-97.039200f,  -0.10000455f,  25.074011f));
            p8->addVertex(OSG::Pnt3f( -3.3615990f, -0.10000229f,   2.7496789f));
            p8->addVertex(OSG::Pnt3f( 24.735554f,  -0.099998474f, 27.686996f));
            p8->addVertex(OSG::Pnt3f( 16.729954f,  -0.099998474f, 97.039207f));
            p8->addVertex(OSG::Pnt3f(-97.038353f,  -0.10000610f,  97.039200f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000610f,  97.038445f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000229f,  97.038452f));
            p8->addVertex(OSG::Pnt3f(-97.038361f,  -0.10000229f,  97.039200f));
            p8->addVertex(OSG::Pnt3f(-64.470268f,  -0.099998474f, 97.039207f));
            p8->addVertex(OSG::Pnt3f(  2.8259430f, -0.099998474f, 97.039207f));
            p8->addVertex(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            p8->addVertex(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            p8->addVertex(OSG::Pnt3f( -7.8507590f, 63.168030f,   -56.876591f));
            p8->addVertex(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            p8->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.087963305f, 97.027847f));
            p8->addVertex(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            p8->addVertex(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            p8->addVertex(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));

            OSG::Polygon* p9 = new OSG::Polygon;
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000610f,  97.038445f));
            p9->addVertex(OSG::Pnt3f(-97.039200f,  -0.10000455f,  25.074011f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000301f,  25.074013f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            p9->addVertex(OSG::Pnt3f(-97.039215f,  -0.10000455f,  25.074013f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000610f,  97.038437f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.10000229f,  97.038452f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            p9->addVertex(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));

            OSG::Polygon* p10 = new OSG::Polygon;
            p10->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.087963305f, 97.027847f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));
            p10->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->addVertex(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            p10->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            p10->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            p10->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->addVertex(OSG::Pnt3f( -7.8507590f, 63.168030f,   -56.876591f));
            p10->addVertex(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            p10->addVertex(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            p10->addVertex(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            p10->addVertex(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            p10->addVertex(OSG::Pnt3f(  6.3682003f, 63.168030f,    66.162643f));
            p10->addVertex(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            p10->addVertex(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            p10->addVertex(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            p10->addVertex(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            p10->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            p10->addVertex(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            p10->addVertex(OSG::Pnt3f( -7.8507590f, 63.168030f,   -56.876591f));
            p10->addVertex(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            p10->addVertex(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.087963305f, 97.027847f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            p10->addVertex(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            p10->addVertex(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));

            bodyB.add(p1);
            bodyB.add(p2);
            bodyB.add(p3);
            bodyB.add(p4);
            bodyB.add(p5);
            bodyB.add(p6);
            bodyB.add(p7);
            bodyB.add(p8);
            bodyB.add(p9);
            bodyB.add(p10);

            OSG::PolygonBody::VecVerticesT uniqueVertices;
            uniqueVertices.push_back(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.087963305f, 97.027847f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            uniqueVertices.push_back(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(OSG::Pnt3f( -7.8507590f, 63.168030f,   -56.876591f));
            uniqueVertices.push_back(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            uniqueVertices.push_back(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            uniqueVertices.push_back(OSG::Pnt3f( 17.592979f,  63.168030f,   -35.909237f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.744465f,  63.168030f,   -34.887249f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(  6.3682003f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(OSG::Pnt3f( 18.500849f,  63.168030f,   -33.538715f));
            uniqueVertices.push_back(OSG::Pnt3f( 17.349363f,  63.168030f,   -34.560703f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            uniqueVertices.push_back(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            uniqueVertices.push_back(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f(  6.3682013f, 63.168030f,    66.162643f));
            uniqueVertices.push_back(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f( 20.246395f,  63.168030f,   -31.939274f));
            uniqueVertices.push_back(OSG::Pnt3f( -7.8507476f, 63.168034f,   -56.876591f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            uniqueVertices.push_back(OSG::Pnt3f( -7.8507590f, 63.168030f,   -56.876591f));
            uniqueVertices.push_back(OSG::Pnt3f( 20.246393f,  63.168034f,   -31.939274f));
            uniqueVertices.push_back(OSG::Pnt3f( 12.240793f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.087963305f, 97.027847f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.088067017f, 97.027954f));
            uniqueVertices.push_back(OSG::Pnt3f(-68.959427f,  63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f( -1.6632171f, 63.168034f,    37.412937f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.099897027f, 25.073910f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.098770142f, 97.039200f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  21.274025f,    97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  37.133457f,    97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873394f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  32.604870f,    33.873398f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f,  -0.098762877f, 97.039200f));
            bodyB.setVertices(uniqueVertices);

            //
            // Following the correct planes from the directX example run
            //
            OSG::Plane plNear  (OSG::Vec3f( 0.60391480f,  0.41508070f, -0.68043733f), 19.956511f );
            OSG::Plane plFar   (OSG::Vec3f(-0.60391575f, -0.41508308f,  0.68043506f),124.67360f  );
            OSG::Plane plLeft  (OSG::Vec3f( 0.96103317f,  0.25319675f,  0.11093587f), 26.817856f );
            OSG::Plane plRight (OSG::Vec3f(-0.22426482f,  0.25319672f, -0.94106156f), -1.8590580f);
            OSG::Plane plBottom(OSG::Vec3f( 0.54057401f, -0.58035570f, -0.60907066f), -3.4338706f);
            OSG::Plane plTop   (OSG::Vec3f( 0.063340642f, 0.99543709f, -0.071366511f), 23.892124f);

            OSG::FrustumVolume camFrust(plNear, plFar, plLeft, plRight, plTop, plBottom);

            OSG::Real32 d;

            //
            // The example's Frustum class does store the 'frustum corners'. These are not the
            // correct plane intersection points but the back transformed of the DirectX NDC 
            // bounding box [(-1,-1,0),(1,1,1)]. In order to get the same result as in the directX
            // example we have to use the very same corner points.
            //
            std::vector<OSG::Pnt3f> camFrustCorners;
            camFrustCorners.push_back(OSG::Pnt3f(  21.672276f,  21.904886f,   4.0007563f));
            camFrustCorners.push_back(OSG::Pnt3f(  20.520790f,  21.904886f,   2.9787679f));
            camFrustCorners.push_back(OSG::Pnt3f(  20.202635f,  22.955418f,   3.3372376f));
            camFrustCorners.push_back(OSG::Pnt3f(  21.354120f,  22.955418f,   4.3592257f));
            camFrustCorners.push_back(OSG::Pnt3f(  40.539791f,-113.62879f,  149.89030f  ));
            camFrustCorners.push_back(OSG::Pnt3f(-126.57689f, -113.62879f,    1.5677508f));
            camFrustCorners.push_back(OSG::Pnt3f(-172.75128f,   38.836262f,  53.592941f ));
            camFrustCorners.push_back(OSG::Pnt3f(  -5.6346021f, 38.836262f, 201.91550f  ));

            //
            // Proof that the corner points are not the frustum plane intersection points
            //
            d = plNear  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_BOTTOM]);
            d = plLeft  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_BOTTOM]);
            d = plBottom.distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_BOTTOM]);

            d = plNear  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_BOTTOM]);
            d = plRight .distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_BOTTOM]);
            d = plBottom.distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_BOTTOM]);

            d = plNear  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_TOP]);
            d = plRight .distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_TOP]);
            d = plTop   .distance(camFrustCorners[OSG::FrustumVolume::NEAR_RIGHT_TOP]);

            d = plNear  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_TOP]);
            d = plLeft  .distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_TOP]);
            d = plTop   .distance(camFrustCorners[OSG::FrustumVolume::NEAR_LEFT_TOP]);

            d = plFar   .distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_BOTTOM]);
            d = plLeft  .distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_BOTTOM]);
            d = plBottom.distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_BOTTOM]);

            d = plFar   .distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_BOTTOM]);
            d = plRight .distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_BOTTOM]);
            d = plBottom.distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_BOTTOM]);

            d = plFar   .distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_TOP]);
            d = plRight .distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_TOP]);
            d = plTop   .distance(camFrustCorners[OSG::FrustumVolume::FAR_RIGHT_TOP]);

            d = plFar   .distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_TOP]);
            d = plLeft  .distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_TOP]);
            d = plTop   .distance(camFrustCorners[OSG::FrustumVolume::FAR_LEFT_TOP]);

            //
            // OpenSG returns the correct frustum plane intersection points
            //
            OSG::Pnt3f nlbFV, nrbFV, nrtFV, nltFV, flbFV, frbFV, frtFV, fltFV;
            nlbFV = camFrust.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);  // [  21.6070652,   22.3734035,   3.49640203]
            nrbFV = camFrust.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM); // [  21.0293331,   22.3734035,   2.98364210]
            nrtFV = camFrust.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);    // [  20.8697052,   22.9004860,   3.16349649]
            nltFV = camFrust.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);     // [  21.4474354,   22.9004879,   3.67625690]
            flbFV = camFrust.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);   // [  40.5398331, -113.629059,  149.890533  ]
            frbFV = camFrust.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);  // [-126.576553,  -113.628571,    1.56774294]
            frtFV = camFrust.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);     // [-172.751419,    38.8362656,  53.5930290 ]
            fltFV = camFrust.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);      // [  -5.63471031,  38.8363113, 201.916428  ]

            //
            // Proof that the corner points are actually the frustum plane intersection points
            //
            d = plNear  .distance(nlbFV);
            d = plLeft  .distance(nlbFV);
            d = plBottom.distance(nlbFV);

            d = plNear  .distance(nrbFV);
            d = plRight .distance(nrbFV);
            d = plBottom.distance(nrbFV);

            d = plNear  .distance(nrtFV);
            d = plRight .distance(nrtFV);
            d = plTop   .distance(nrtFV);

            d = plNear  .distance(nltFV);
            d = plLeft  .distance(nltFV);
            d = plTop   .distance(nltFV);

            d = plFar   .distance(flbFV);
            d = plLeft  .distance(flbFV);
            d = plBottom.distance(flbFV);

            d = plFar   .distance(frbFV);
            d = plRight .distance(frbFV);
            d = plBottom.distance(frbFV);

            d = plFar   .distance(frtFV);
            d = plRight .distance(frtFV);
            d = plTop   .distance(frtFV);

            d = plFar   .distance(fltFV);
            d = plLeft  .distance(fltFV);
            d = plTop   .distance(fltFV);

            OSG::BoxVolume sceneAABB(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f), OSG::Pnt3f(97.039207f, 63.168030f, 97.039207f));

            OSG::Vec2f zRange(1.0000008f, 145.13222f);

            //
            // The function that we normally would call
            // 
            // OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
            //                            0,                  // unsigned int         split,
            //                            bodyB,              // const PolygonBody&   bodyB,
            //                            camFrust,           // const Frustum&       camFrust, 
            //                            0x0,                // const FrustumVolume* lightFrust, 
            //                            sceneAABB,          // const BoxVolume&     sceneAABB,
            //                            zRange              // const tVec2f&        zRange
            //                    );
            //

            //
            // To get around of the 'false' frustum plane intersection points we call this function to get the same result
            //
            OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
                                        0,                  // unsigned int             split,
                                        bodyB,              // const PolygonBody&       bodyB,
                                        camFrustCorners,    // const std::vecor<Pnt3f>& camFrustCorners, 
                                        0x0,                // const FrustumVolume*     lightFrust, 
                                        sceneAABB,          // const BoxVolume&         sceneAABB,
                                        zRange              // const tVec2f&            zRange
                                );
            //
            //              [0.110, -0.086,  0.000, -2.-09]
            // liSPMatrix = [0.688,  0.876,  0.000,  0.007]
            //              [0.000,  0.000,  0.140,  0.361]
            //              [0.617,  0.787,  0.000,  0.146]
            //

            int ijk = 234;
        }

        // LiSP test II
        {
            //
            // This test takes values from DirectX example
            //
            OSG::LiSPSMTechnique liSP(1);

            liSP.setMode(OSG::LiSPSMTechnique::NOPT);
            liSP.setArbScaled(false);
            liSP.setParamN(1.f, 0);
            liSP.setSplitParam(0.5f);

            OSG::Matrix4f matLightProj(
                4.2034721f,  0.00000000f,  0.00000000f,    0.00000000f,
                0.00000000f, 4.2034721f,   0.00000000f,    0.00000000f,
                0.00000000f, 0.00000000f, -3.3012176f, -1595.2123f,
                0.00000000f, 0.00000000f, -1.0000000f,     0.00000000f);
            liSP.setLightProjMat(matLightProj, OSG::Projection::PERSPECTIVE);

            OSG::Matrix4f matLightView(
                 0.37209886f,  0.66555393f, -0.64697784f,    1.1646205e-005f,
                -0.38898203f, -0.52105552f, -0.75973284f,   -6.9774319e-006f,
                -0.84275460f,  0.53435850f,  0.065004356f,-605.06195f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            OSG::View viewLightView(
                OSG::Pnt3f(-509.91882f, 323.32004f, 39.331669f),
                OSG::Pnt3f(0.00000000f, 0.00000000f, 0.00000000f),
                OSG::Vec3f(3.9999373e-010f, 0.12075910f, -0.99268186f));

            liSP.setLightView(matLightView, viewLightView);

            OSG::Matrix4f matCamView(
                  0.88472515f,  0.018609947f, -0.46574140f,    6.5359397f,
                 -0.036769699f, 0.99887520f,  -0.029935205f, -11.052643f,
                  0.46466044f,  0.043609601f,  0.88441432f, -105.78976f,
                  0.00000000f,  0.00000000f,   0.00000000f,    1.0000000f);

            OSG::View viewCamView(
                OSG::Pnt3f(42.967415f, 15.532030f, 96.275192f),
                OSG::Pnt3f(42.502754f, 15.488420f, 95.390778f),
                OSG::Vec3f(-0.016558312f, 0.99982685f, 0.0084964950f));

            liSP.setCamView(matCamView, viewCamView);

            OSG::Matrix4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f, 0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f, 0.00000000f,
                0.00000000f, 0.00000000f, -1.0042425f, -1.0042425f,
                0.00000000f, 0.00000000f, -1.0000000f,  0.00000000f);

            liSP.setCamProjMat(matCamProj);

            liSP.setFieldOfView(60.000000f);
            liSP.setGamma(71.892494f);
            liSP.setSplitParam(0.50000000f);
            liSP.setPseudoNear(0.00000000f);
            liSP.setPseudoFar(0.00000000f);

            // Artificially construct a PolygonBody for the test
            OSG::PolygonBody bodyB;

            OSG::Polygon* p1 = new OSG::Polygon;
            p1->addVertex(OSG::Pnt3f(15.269290f, -0.099920020f, 83.747429f));
            p1->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));
            p1->addVertex(OSG::Pnt3f(-44.512161f, 63.168030f, 86.934151f));
            p1->addVertex(OSG::Pnt3f(-87.468880f, 63.168030f, 75.058762f));

            OSG::Polygon* p2 = new OSG::Polygon;
            p2->addVertex(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178802f));
            p2->addVertex(OSG::Pnt3f(15.269290f, -0.099920020f, 83.747429f));
            p2->addVertex(OSG::Pnt3f(-87.468903f, 63.168030f, 75.058762f));
            p2->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659676f));
            p2->addVertex(OSG::Pnt3f(-97.039207f, -0.10000610f, 32.123699f));

            OSG::Polygon* p3 = new OSG::Polygon;
            p3->addVertex(OSG::Pnt3f(41.800472f, 16.050735f, 95.731934f));
            p3->addVertex(OSG::Pnt3f(-42.801273f, 63.168030f, 87.083420f));
            p3->addVertex(OSG::Pnt3f(-44.512177f, 63.168030f, 86.934158f));
            p3->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));

            OSG::Polygon* p4 = new OSG::Polygon;
            p4->addVertex(OSG::Pnt3f(39.048035f, -0.10000066f, 70.328667f));
            p4->addVertex(OSG::Pnt3f(15.269290f, -0.099920020f, 83.747429f));
            p4->addVertex(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178799f));

            OSG::Polygon* p5 = new OSG::Polygon;
            p5->addVertex(OSG::Pnt3f(59.951366f, 63.168030f, -13.391017f));
            p5->addVertex(OSG::Pnt3f(49.097382f, -0.099998474f, 64.657608f));
            p5->addVertex(OSG::Pnt3f(77.088989f, -0.10000066f, -97.039063f));
            p5->addVertex(OSG::Pnt3f(59.951378f, 63.168026f, -13.391098f));

            OSG::Polygon* p6 = new OSG::Polygon;
            p6->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390985f));
            p6->addVertex(OSG::Pnt3f(43.205029f, 14.926052f, 95.049591f));
            p6->addVertex(OSG::Pnt3f(49.097359f, -0.10000038f, 64.657722f));
            p6->addVertex(OSG::Pnt3f(49.097382f, -0.10000066f, 64.657608f));
            p6->addVertex(OSG::Pnt3f(59.951363f, 63.168026f, -13.391014f));

            OSG::Polygon* p7 = new OSG::Polygon;
            p7->addVertex(OSG::Pnt3f(15.269290f, -0.099920020f, 83.747429f));
            p7->addVertex(OSG::Pnt3f(39.048035f, -0.10000066f, 70.328667f));
            p7->addVertex(OSG::Pnt3f(49.097359f, -0.10000066f, 64.657722f));
            p7->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));

            OSG::Polygon* p8 = new OSG::Polygon;
            p8->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));
            p8->addVertex(OSG::Pnt3f(49.097359f, -0.10000038f, 64.657722f));
            p8->addVertex(OSG::Pnt3f(49.097359f, -0.10000066f, 64.657722f));
            p8->addVertex(OSG::Pnt3f(43.205029f, 14.926052f, 95.049591f));

            OSG::Polygon* p9 = new OSG::Polygon;
            p9->addVertex(OSG::Pnt3f(77.088989f, -0.099998474f, -97.039063f));
            p9->addVertex(OSG::Pnt3f(77.089012f, -0.10000066f, -97.039177f));
            p9->addVertex(OSG::Pnt3f(74.431824f, 63.168026f, -97.039124f));
            p9->addVertex(OSG::Pnt3f(59.951378f, 63.168030f, -13.391094f));

            OSG::Polygon* p10 = new OSG::Polygon;
            p10->addVertex(OSG::Pnt3f(77.089012f, -0.10000066f, -97.039177f));
            p10->addVertex(OSG::Pnt3f(74.963264f, 50.514450f, -97.039207f));
            p10->addVertex(OSG::Pnt3f(74.431824f, 63.168030f, -97.039207f));
            p10->addVertex(OSG::Pnt3f(74.431824f, 63.168030f, -97.039124f));
            p10->addVertex(OSG::Pnt3f(77.089012f, -0.099998474f, -97.039177f));

            OSG::Polygon* p11 = new OSG::Polygon;
            p11->addVertex(OSG::Pnt3f(77.089012f, -0.10000229f, -97.039177f));
            p11->addVertex(OSG::Pnt3f(77.088982f, -0.10000066f, -97.039207f));
            p11->addVertex(OSG::Pnt3f(74.963264f, 50.514450f, -97.039207f));

            OSG::Polygon* p12 = new OSG::Polygon;
            p12->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390984f));
            p12->addVertex(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));
            p12->addVertex(OSG::Pnt3f(43.205029f, 14.926052f, 95.049591f));
            p12->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390984f));

            OSG::Polygon* p13 = new OSG::Polygon;
            p13->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390976f));
            p13->addVertex(OSG::Pnt3f(-41.604263f, 63.168030f, 86.480789f));
            p13->addVertex(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));

            OSG::Polygon* p14 = new OSG::Polygon;
            p14->addVertex(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));
            p14->addVertex(OSG::Pnt3f(-41.604271f, 63.168030f, 86.480789f));
            p14->addVertex(OSG::Pnt3f(-42.801300f, 63.168030f, 87.083412f));
            p14->addVertex(OSG::Pnt3f(41.800472f, 16.050735f, 95.731934f));

            OSG::Polygon* p15 = new OSG::Polygon;
            p15->addVertex(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));
            p15->addVertex(OSG::Pnt3f(41.800472f, 16.050735f, 95.731934f));
            p15->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));

            OSG::Polygon* p16 = new OSG::Polygon;
            p16->addVertex(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));
            p16->addVertex(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));
            p16->addVertex(OSG::Pnt3f(43.205029f, 14.926052f, 95.049591f));

            OSG::Polygon* p17 = new OSG::Polygon;
            p17->addVertex(OSG::Pnt3f(-97.039207f, -0.099906921f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(-32.317986f, -0.10000066f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(74.431717f, 63.168030f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(7.4377823f, -0.099998474f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(77.088982f, -0.10000066f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(74.963264f, 50.514450f, -97.039207f));
            p17->addVertex(OSG::Pnt3f(-97.039207f, -0.099868774f, -97.039207f));

            OSG::Polygon* p18 = new OSG::Polygon;
            p18->addVertex(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178802f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039093f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.031891f));
            p18->addVertex(OSG::Pnt3f(39.048035f, -0.10000066f, 70.328667f));
            p18->addVertex(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178799f));
            p18->addVertex(OSG::Pnt3f(49.097382f, -0.099998474f, 64.657608f));
            p18->addVertex(OSG::Pnt3f(77.088989f, -0.10000066f, -97.039063f));
            p18->addVertex(OSG::Pnt3f(49.097359f, -0.10000038f, 64.657722f));
            p18->addVertex(OSG::Pnt3f(49.097382f, -0.10000066f, 64.657608f));
            p18->addVertex(OSG::Pnt3f(77.089012f, -0.10000066f, -97.039177f));
            p18->addVertex(OSG::Pnt3f(77.088989f, -0.099998474f, -97.039063f));
            p18->addVertex(OSG::Pnt3f(77.089012f, -0.099998474f, -97.039177f));
            p18->addVertex(OSG::Pnt3f(77.089012f, -0.10000229f, -97.039177f));
            p18->addVertex(OSG::Pnt3f(77.088982f, -0.10000066f, -97.039207f));
            p18->addVertex(OSG::Pnt3f(-32.317986f, -0.10000066f, -97.039207f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f));
            p18->addVertex(OSG::Pnt3f(7.4377823f, -0.099998474f, -97.039207f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, 32.123543f));
            p18->addVertex(OSG::Pnt3f(-97.039207f, -0.10000610f, 32.123699f));

            OSG::Polygon* p19 = new OSG::Polygon;
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039078f));
            p19->addVertex(OSG::Pnt3f(-41.604271f, 63.168030f, 86.480789f));
            p19->addVertex(OSG::Pnt3f(-42.801300f, 63.168030f, 87.083412f));
            p19->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390976f));
            p19->addVertex(OSG::Pnt3f(-41.604263f, 63.168030f, 86.480789f));
            p19->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390984f));
            p19->addVertex(OSG::Pnt3f(74.431824f, 63.168030f, -97.039207f));
            p19->addVertex(OSG::Pnt3f(74.431824f, 63.168030f, -97.039124f));
            p19->addVertex(OSG::Pnt3f(59.951378f, 63.168030f, -13.391094f));
            p19->addVertex(OSG::Pnt3f(74.431824f, 63.168026f, -97.039124f));
            p19->addVertex(OSG::Pnt3f(59.951359f, 63.168030f, -13.390985f));
            p19->addVertex(OSG::Pnt3f(59.951363f, 63.168026f, -13.391014f));
            p19->addVertex(OSG::Pnt3f(59.951366f, 63.168030f, -13.391017f));
            p19->addVertex(OSG::Pnt3f(59.951378f, 63.168026f, -13.391098f));
            p19->addVertex(OSG::Pnt3f(-42.801273f, 63.168030f, 87.083420f));
            p19->addVertex(OSG::Pnt3f(-44.512177f, 63.168030f, 86.934158f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, -97.038834f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 59.653152f));
            p19->addVertex(OSG::Pnt3f(-87.468903f, 63.168030f, 75.058762f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659676f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659668f));
            p19->addVertex(OSG::Pnt3f(-87.468880f, 63.168030f, 75.058762f));
            p19->addVertex(OSG::Pnt3f(-44.512161f, 63.168030f, 86.934151f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 24.951511f));
            p19->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -8.2764320f));
            p19->addVertex(OSG::Pnt3f(74.431717f, 63.168030f, -97.039207f));
            p19->addVertex(OSG::Pnt3f(-97.039200f, 63.168026f, -97.039207f));

            OSG::Polygon* p20 = new OSG::Polygon;
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659676f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.099868774f, -97.039207f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.099906921f, -97.039207f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039207f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039093f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.031891f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.10000066f, 32.123543f));
            p20->addVertex(OSG::Pnt3f(-97.039200f, 63.168026f, -97.039207f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039078f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, -97.038834f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 59.653152f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659668f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168030f, 24.951511f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, 63.168026f, -8.2764320f));
            p20->addVertex(OSG::Pnt3f(-97.039207f, -0.10000610f, 32.123699f));

            bodyB.add(p1);
            bodyB.add(p2);
            bodyB.add(p3);
            bodyB.add(p4);
            bodyB.add(p5);
            bodyB.add(p6);
            bodyB.add(p7);
            bodyB.add(p8);
            bodyB.add(p9);
            bodyB.add(p10);
            bodyB.add(p11);
            bodyB.add(p12);
            bodyB.add(p13);
            bodyB.add(p14);
            bodyB.add(p15);
            bodyB.add(p16);
            bodyB.add(p17);
            bodyB.add(p18);
            bodyB.add(p19);
            bodyB.add(p20);

            OSG::PolygonBody::VecVerticesT uniqueVertices;
            uniqueVertices.push_back(OSG::Pnt3f(15.269290f, -0.099920020f, 83.747429f));
            uniqueVertices.push_back(OSG::Pnt3f(41.842957f, 14.897432f, 95.766670f));
            uniqueVertices.push_back(OSG::Pnt3f(-44.512161f, 63.168030f, 86.934151f));
            uniqueVertices.push_back(OSG::Pnt3f(-87.468880f, 63.168030f, 75.058762f));
            uniqueVertices.push_back(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178802f));
            uniqueVertices.push_back(OSG::Pnt3f(-87.468903f, 63.168030f, 75.058762f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659676f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.10000610f, 32.123699f));
            uniqueVertices.push_back(OSG::Pnt3f(41.800472f, 16.050735f, 95.731934f));
            uniqueVertices.push_back(OSG::Pnt3f(-42.801273f, 63.168030f, 87.083420f));
            uniqueVertices.push_back(OSG::Pnt3f(-44.512177f, 63.168030f, 86.934158f));
            uniqueVertices.push_back(OSG::Pnt3f(39.048035f, -0.10000066f, 70.328667f));
            uniqueVertices.push_back(OSG::Pnt3f(-79.515152f, -0.10000066f, 40.178799f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951366f, 63.168030f, -13.391017f));
            uniqueVertices.push_back(OSG::Pnt3f(49.097382f, -0.099998474f, 64.657608f));
            uniqueVertices.push_back(OSG::Pnt3f(77.088989f, -0.10000066f, -97.039063f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951378f, 63.168026f, -13.391098f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951359f, 63.168030f, -13.390985f));
            uniqueVertices.push_back(OSG::Pnt3f(43.205029f, 14.926052f, 95.049591f));
            uniqueVertices.push_back(OSG::Pnt3f(49.097359f, -0.10000038f, 64.657722f));
            uniqueVertices.push_back(OSG::Pnt3f(49.097382f, -0.10000066f, 64.657608f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951363f, 63.168026f, -13.391014f));
            uniqueVertices.push_back(OSG::Pnt3f(77.088989f, -0.099998474f, -97.039063f));
            uniqueVertices.push_back(OSG::Pnt3f(77.089012f, -0.10000066f, -97.039177f));
            uniqueVertices.push_back(OSG::Pnt3f(74.431824f, 63.168026f, -97.039124f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951378f, 63.168030f, -13.391094f));
            uniqueVertices.push_back(OSG::Pnt3f(74.963264f, 50.514450f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(74.431824f, 63.168030f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(74.431824f, 63.168030f, -97.039124f));
            uniqueVertices.push_back(OSG::Pnt3f(77.089012f, -0.099998474f, -97.039177f));
            uniqueVertices.push_back(OSG::Pnt3f(77.089012f, -0.10000229f, -97.039177f));
            uniqueVertices.push_back(OSG::Pnt3f(77.088982f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951359f, 63.168030f, -13.390984f));
            uniqueVertices.push_back(OSG::Pnt3f(43.162521f, 16.079493f, 95.014954f));
            uniqueVertices.push_back(OSG::Pnt3f(59.951359f, 63.168030f, -13.390976f));
            uniqueVertices.push_back(OSG::Pnt3f(-41.604263f, 63.168030f, 86.480789f));
            uniqueVertices.push_back(OSG::Pnt3f(-41.604271f, 63.168030f, 86.480789f));
            uniqueVertices.push_back(OSG::Pnt3f(-42.801300f, 63.168030f, 87.083412f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.099906921f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-32.317986f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(74.431717f, 63.168030f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(7.4377823f, -0.099998474f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.099868774f, -97.039207f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039093f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.031891f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, -0.10000066f, 32.123543f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168026f, -97.039078f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168030f, -97.038834f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168030f, 59.653152f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168030f, 70.659668f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168030f, 24.951511f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039207f, 63.168026f, -8.2764320f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.039200f, 63.168026f, -97.039207f));
            bodyB.setVertices(uniqueVertices);

            //
            // Following the correct planes from the directX example run
            //
            OSG::Plane plCamNear  (OSG::Vec3f(0.46465811f, 0.043610103f, 0.88441563f), 105.28873f);
            OSG::Plane plCamFar   (OSG::Vec3f(-0.46466947f, -0.043610398f, -0.88440967f), 130.91943f);
            OSG::Plane plCamLeft  (OSG::Vec3f(-0.41762245f, 0.011855224f, 0.90854329f), 69.710159f);
            OSG::Plane plCamRight (OSG::Vec3f(0.98450172f, 0.041348580f, 0.17043072f), 59.351971f);
            OSG::Plane plCamBottom(OSG::Vec3f(0.26417196f, -0.84324867f, 0.46812919f), 43.322651f);
            OSG::Plane plCamTop   (OSG::Vec3f(0.20048171f, 0.88685942f, 0.41627806f), 62.466160f);

            OSG::FrustumVolume camFrust(plCamNear, plCamFar, plCamLeft, plCamRight, plCamTop, plCamBottom);

            //
            // The example's Frustum class does store the 'frustum corners'. These are not the
            // correct plane intersection points but the back transformed of the DirectX NDC 
            // bounding box [(-1,-1,0),(1,1,1)]. In order to get the same result as in the directX
            // example we have to use the very same corner points.
            //
            std::vector<OSG::Pnt3f> camFrustCorners;
            camFrustCorners.push_back(OSG::Pnt3f(41.842922f, 14.897396f, 95.766586f));
            camFrustCorners.push_back(OSG::Pnt3f(43.205051f, 14.926048f, 95.049522f));
            camFrustCorners.push_back(OSG::Pnt3f(43.162594f, 16.079441f, 95.014961f));
            camFrustCorners.push_back(OSG::Pnt3f(41.800465f, 16.050791f, 95.732025f));
            camFrustCorners.push_back(OSG::Pnt3f(-223.21036f, -134.69102f, -24.116596f));
            camFrustCorners.push_back(OSG::Pnt3f(99.215935f, -127.90880f, -193.85019f));
            camFrustCorners.push_back(OSG::Pnt3f(89.165848f, 145.10817f, -202.03113f));
            camFrustCorners.push_back(OSG::Pnt3f(-233.26044f, 138.32594f, -32.297531f));

            OSG::Plane plLightNear  (OSG::Vec3f(-0.84275466f, 0.53435856f, 0.065004379f), 234.18739f);
            OSG::Plane plLightFar   (OSG::Vec3f(0.84275466f, -0.53435856f, -0.065004379f), 88.141632f);
            OSG::Plane plLightLeft  (OSG::Vec3f(-0.55704284f, -0.52381212f, 0.64445645f), 140.03523f);
            OSG::Plane plLightRight (OSG::Vec3f(0.16694947f, 0.77115542f, -0.61436731f), 140.03522f);
            OSG::Plane plLightBottom(OSG::Vec3f(0.18337426f, 0.63058019f, 0.75415015f), 140.03522f);
            OSG::Plane plLightTop   (OSG::Vec3f(-0.57346767f, -0.38323686f, -0.72406101f), 140.03525f);

            OSG::FrustumVolume lightFrust(plLightNear, plLightFar, plLightLeft, plLightRight, plLightTop, plLightBottom);

            OSG::BoxVolume sceneAABB(OSG::Pnt3f(-97.039207f, -0.10000066f, -97.039207f), OSG::Pnt3f(97.039207f, 63.168030f, 97.039207f));

            OSG::Vec2f zRange(1.0000000f, 236.70729f);

            //
            // The function that we normally would call
            // 
            // OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
            //                            0,                  // unsigned int         split,
            //                            bodyB,              // const PolygonBody&   bodyB,
            //                            camFrust,           // const Frustum&       camFrust, 
            //                            0x0,                // const FrustumVolume* lightFrust, 
            //                            sceneAABB,          // const BoxVolume&     sceneAABB,
            //                            zRange              // const tVec2f&        zRange
            //                    );
            //

            //
            // To get around of the 'false' frustum plane intersection points we call this function to get the same result
            //
            OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
                                        0,                  // unsigned int         split,
                                        bodyB,              // const PolygonBody&   bodyB,
                                        camFrustCorners,    // const VecVerticesT&  camFrustCorners, 
                                        &lightFrust,        // const FrustumVolume* lightFrust, 
                                        sceneAABB,          // const BoundingBox&   sceneAABB,
                                        zRange              // const tVec2f&        zRange
                                );
            //
            //              [0.104373, -0.044428,  0.000000, -0.004013]
            // liSPMatrix = [0.419552,  0.985628,  0.000000,  0.745498]
            //              [0.000000,  0.000000,  0.113435, -0.085598]
            //              [0.391662,  0.920109,  0.000000,  0.809377]
            //

            int ijk = 234;
        }

        // LiSP test III
        {
            //
            // This test takes values from DirectX example
            //
            OSG::LiSPSMTechnique liSP(1);

            liSP.setMode(OSG::LiSPSMTechnique::REPARAMETRIZED);
            liSP.setArbScaled(false);
            liSP.setParamN(140.98463f, 0);
            liSP.setSplitParam(0.5f);

            OSG::Matrix4f matLightProj(
                0.057911590f, 0.00000000f,  0.00000000f,  0.00000000f,
                0.00000000f,  0.057911590f, 0.00000000f,  0.00000000f,
                0.00000000f,  0.00000000f, -1.0347396f, -35.843311f,
                0.00000000f,  0.00000000f, -1.0000000f,   0.00000000f);
            liSP.setLightProjMat(matLightProj, OSG::Projection::PERSPECTIVE);

            OSG::Matrix4f matLightView(
                 0.31544900f,  0.25865412f, -0.91301143f,   -4.5831375e-006f,
                -0.35206801f, -0.86156631f, -0.36572069f,    2.9790876e-006f,
                -0.88121516f,  0.43680838f, -0.18071641f, -605.06201f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            OSG::View viewLightView(
                OSG::Pnt3f(-533.18976f, 264.29614f, -109.34463f),
                OSG::Pnt3f(0.00000000f, 0.00000000f, 0.00000000f),
                OSG::Vec3f(9.0862562e-009f, -0.38229418f, -0.92404062f));

            liSP.setLightView(matLightView, viewLightView);

            OSG::Matrix4f matCamView(
                 0.69921154f, 0.017653238f, -0.71469688f,   -3.6979961f,
                -0.26234373f, 0.93628949f,  -0.23353288f,  -87.327797f,
                 0.66504055f, 0.35078511f,   0.65929562f, -172.59473f,
                 0.00000000f, 0.00000000f,   0.00000000f,    1.0000000f);

            OSG::View viewCamView(
                OSG::Pnt3f(94.458290f, 142.37306f, 90.754105f),
                OSG::Pnt3f(93.793251f, 142.02228f, 90.094810f),
                OSG::Vec3f(-0.016558312f, 0.99982685f, 0.0084964950f));

            liSP.setCamView(matCamView, viewCamView);

            OSG::Matrix4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f,   0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f,   0.00000000f,
                0.00000000f, 0.00000000f, -1.2454509f, -175.58943f,
                0.00000000f, 0.00000000f, -1.0000000f,    0.00000000f);

            liSP.setCamProjMat(matCamProj);

            liSP.setFieldOfView(60.000000f);
            liSP.setGamma(56.498173f);
            liSP.setSplitParam(0.50000000f);
            liSP.setPseudoNear(0.12000000f);
            liSP.setPseudoFar(0.19000000f);

            // Artificially construct a PolygonBody for the test
            OSG::PolygonBody bodyB;

            OSG::Polygon* p1 = new OSG::Polygon;
            p1->addVertex(OSG::Pnt3f(40.567329f, -0.099960543f, -422.14844f));
            p1->addVertex(OSG::Pnt3f(69.083717f, -0.099999905f, -255.43610f));
            p1->addVertex(OSG::Pnt3f(-316.82861f, -0.099999905f, -422.14835f));
            p1->addVertex(OSG::Pnt3f(-147.22157f, -0.099981226f, -422.14844f));

            OSG::Polygon* p2 = new OSG::Polygon;
            p2->addVertex(OSG::Pnt3f(-147.22159f, -0.099981226f, -422.14844f));
            p2->addVertex(OSG::Pnt3f(-316.82861f, -0.099999905f, -422.14835f));
            p2->addVertex(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14835f));
            p2->addVertex(OSG::Pnt3f(-397.60672f, -0.099945091f, -422.14844f));

            OSG::Polygon* p3 = new OSG::Polygon;
            p3->addVertex(OSG::Pnt3f(-397.60669f, 206.36839f, 2.1476247f));
            p3->addVertex(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            p3->addVertex(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891682f));
            p3->addVertex(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475983f));

            OSG::Polygon* p4 = new OSG::Polygon;
            p4->addVertex(OSG::Pnt3f(69.083725f, -0.099999905f, -255.43610f));
            p4->addVertex(OSG::Pnt3f(40.567333f, -0.099960543f, -422.14844f));
            p4->addVertex(OSG::Pnt3f(1.3627319f, 164.95033f, -422.14844f));
            p4->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p4->addVertex(OSG::Pnt3f(98.463730f, -0.099990845f, -83.674805f));

            OSG::Polygon* p5 = new OSG::Polygon;
            p5->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p5->addVertex(OSG::Pnt3f(-397.60672f, 261.17880f, -422.14838f));
            p5->addVertex(OSG::Pnt3f(-397.60672f, 252.77078f, -190.67180f));

            OSG::Polygon* p6 = new OSG::Polygon;
            p6->addVertex(OSG::Pnt3f(-131.61452f, -0.099999905f, 85.536140f));
            p6->addVertex(OSG::Pnt3f(-97.820648f, -0.099999905f, 90.713882f));
            p6->addVertex(OSG::Pnt3f(-71.140770f, -0.099992089f, 94.801651f));

            OSG::Polygon* p7 = new OSG::Polygon;
            p7->addVertex(OSG::Pnt3f(-397.60672f, 206.36835f, 2.1476340f));
            p7->addVertex(OSG::Pnt3f(-397.60672f, 206.36818f, 2.1476779f));
            p7->addVertex(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            p7->addVertex(OSG::Pnt3f(-397.60669f, 206.36839f, 2.1476247f));

            OSG::Polygon* p8 = new OSG::Polygon;
            p8->addVertex(OSG::Pnt3f(-397.60669f, 206.36839f, 2.1476247f));
            p8->addVertex(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475997f));
            p8->addVertex(OSG::Pnt3f(-397.60672f, 206.36835f, 2.1476340f));

            OSG::Polygon* p9 = new OSG::Polygon;
            p9->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p9->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p9->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p9->addVertex(OSG::Pnt3f(1.3627319f, 164.95032f, -422.14844f));

            OSG::Polygon* p10 = new OSG::Polygon;
            p10->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p10->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p10->addVertex(OSG::Pnt3f(-397.60672f, 261.17880f, -422.14838f));

            OSG::Polygon* p11 = new OSG::Polygon;
            p11->addVertex(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476860f));
            p11->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            p11->addVertex(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            p11->addVertex(OSG::Pnt3f(-397.60672f, 206.36818f, 2.1476784f));

            OSG::Polygon* p12 = new OSG::Polygon;
            p12->addVertex(OSG::Pnt3f(97.937340f, 18.622017f, -60.753471f));
            p12->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            p12->addVertex(OSG::Pnt3f(98.463333f, -0.099999428f, -83.674263f));
            p12->addVertex(OSG::Pnt3f(98.463753f, -0.099999905f, -83.674698f));

            OSG::Polygon* p13 = new OSG::Polygon;
            p13->addVertex(OSG::Pnt3f(-71.140770f, -0.099992089f, 94.801651f));
            p13->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            p13->addVertex(OSG::Pnt3f(-397.60599f, -0.10000038f, 44.782143f));
            p13->addVertex(OSG::Pnt3f(-131.61453f, -0.099999905f, 85.536140f));

            OSG::Polygon* p14 = new OSG::Polygon;
            p14->addVertex(OSG::Pnt3f(-397.60672f, -0.10000563f, 44.782028f));
            p14->addVertex(OSG::Pnt3f(-397.60599f, -0.099999905f, 44.782143f));
            p14->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            p14->addVertex(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476822f));

            OSG::Polygon* p15 = new OSG::Polygon;
            p15->addVertex(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            p15->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p15->addVertex(OSG::Pnt3f(-397.60672f, 242.80931f, -106.90833f));
            p15->addVertex(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891685f));

            OSG::Polygon* p16 = new OSG::Polygon;
            p16->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p16->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p16->addVertex(OSG::Pnt3f(-397.60675f, 252.77078f, -190.67180f));
            p16->addVertex(OSG::Pnt3f(-397.60672f, 242.80930f, -106.90832f));

            OSG::Polygon* p17 = new OSG::Polygon;
            p17->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p17->addVertex(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            p17->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));

            OSG::Polygon* p18 = new OSG::Polygon;
            p18->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p18->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            p18->addVertex(OSG::Pnt3f(97.937340f, 18.622017f, -60.753471f));

            OSG::Polygon* p19 = new OSG::Polygon;
            p19->addVertex(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            p19->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p19->addVertex(OSG::Pnt3f(98.463745f, -0.099990845f, -83.674759f));
            p19->addVertex(OSG::Pnt3f(98.463730f, -0.099999905f, -83.674812f));

            OSG::Polygon* p20 = new OSG::Polygon;
            p20->addVertex(OSG::Pnt3f(98.463753f, -0.10000038f, -83.674698f));
            p20->addVertex(OSG::Pnt3f(98.463745f, -0.099999905f, -83.674751f));
            p20->addVertex(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            p20->addVertex(OSG::Pnt3f(97.937340f, 18.622017f, -60.753471f));

            OSG::Polygon* p21 = new OSG::Polygon;
            p21->addVertex(OSG::Pnt3f(-71.140549f, -0.10000038f, 94.801521f));
            p21->addVertex(OSG::Pnt3f(98.463341f, -0.099999905f, -83.674263f));
            p21->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));

            OSG::Polygon* p22 = new OSG::Polygon;
            p22->addVertex(OSG::Pnt3f(-71.140770f, -0.099992089f, 94.801651f));
            p22->addVertex(OSG::Pnt3f(-71.140747f, -0.099999905f, 94.801636f));
            p22->addVertex(OSG::Pnt3f(-71.140549f, -0.099999905f, 94.801521f));
            p22->addVertex(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));

            OSG::Polygon* p23 = new OSG::Polygon;
            p23->addVertex(OSG::Pnt3f(-71.140747f, -0.099999905f, 94.801636f));
            p23->addVertex(OSG::Pnt3f(-71.140770f, -0.099992089f, 94.801651f));
            p23->addVertex(OSG::Pnt3f(-97.820633f, -0.099999905f, 90.713882f));

            OSG::Polygon* p24 = new OSG::Polygon;
            p24->addVertex(OSG::Pnt3f(-397.60672f, -0.099945091f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(40.567333f, -0.099960543f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(1.3627319f, 164.95033f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(1.3627319f, 164.95032f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(40.567329f, -0.099960543f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(-147.22157f, -0.099981226f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(-147.22159f, -0.099981226f, -422.14844f));
            p24->addVertex(OSG::Pnt3f(-397.60672f, -0.099945091f, -422.14844f));

            OSG::Polygon* p25 = new OSG::Polygon;
            p25->addVertex(OSG::Pnt3f(-71.140549f, -0.10000038f, 94.801521f));
            p25->addVertex(OSG::Pnt3f(98.463745f, -0.099999905f, -83.674751f));
            p25->addVertex(OSG::Pnt3f(98.463730f, -0.099999905f, -83.674812f));
            p25->addVertex(OSG::Pnt3f(98.463745f, -0.099990845f, -83.674759f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, -0.10000610f, 44.782013f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, -0.10000610f, 44.782028f));
            p25->addVertex(OSG::Pnt3f(-131.61453f, -0.099999905f, 85.536140f));
            p25->addVertex(OSG::Pnt3f(-397.60599f, -0.10000038f, 44.782143f));
            p25->addVertex(OSG::Pnt3f(98.463753f, -0.099999905f, -83.674698f));
            p25->addVertex(OSG::Pnt3f(98.463333f, -0.099999428f, -83.674263f));
            p25->addVertex(OSG::Pnt3f(-397.60669f, -0.099999905f, 44.781990f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, -0.099999905f, 44.782024f));
            p25->addVertex(OSG::Pnt3f(-97.820648f, -0.099999905f, 90.713882f));
            p25->addVertex(OSG::Pnt3f(-131.61452f, -0.099999905f, 85.536140f));
            p25->addVertex(OSG::Pnt3f(69.083725f, -0.099999905f, -255.43610f));
            p25->addVertex(OSG::Pnt3f(98.463730f, -0.099990845f, -83.674805f));
            p25->addVertex(OSG::Pnt3f(-397.60669f, -0.099999905f, -422.14828f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14835f));
            p25->addVertex(OSG::Pnt3f(-316.82861f, -0.099999905f, -422.14835f));
            p25->addVertex(OSG::Pnt3f(69.083717f, -0.099999905f, -255.43610f));
            p25->addVertex(OSG::Pnt3f(-97.820633f, -0.099999905f, 90.713882f));
            p25->addVertex(OSG::Pnt3f(-71.140747f, -0.099999905f, 94.801636f));
            p25->addVertex(OSG::Pnt3f(98.463341f, -0.099999905f, -83.674263f));

            OSG::Polygon* p26 = new OSG::Polygon;
            p26->addVertex(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14835f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475983f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891682f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 252.77078f, -190.67180f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 261.17880f, -422.14838f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36835f, 2.1476340f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36818f, 2.1476779f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475997f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476860f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476822f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, -0.10000563f, 44.782028f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891685f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 242.80931f, -106.90833f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, 242.80930f, -106.90832f));
            p26->addVertex(OSG::Pnt3f(-397.60675f, 252.77078f, -190.67180f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, -0.10000610f, 44.782013f));
            p26->addVertex(OSG::Pnt3f(-397.60669f, -0.099999905f, 44.781990f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, -0.099999905f, 44.782024f));
            p26->addVertex(OSG::Pnt3f(-397.60669f, -0.099999905f, -422.14828f));
            p26->addVertex(OSG::Pnt3f(-397.60672f, -0.099945091f, -422.14844f));

            bodyB.add(p1);
            bodyB.add(p2);
            bodyB.add(p3);
            bodyB.add(p4);
            bodyB.add(p5);
            bodyB.add(p6);
            bodyB.add(p7);
            bodyB.add(p8);
            bodyB.add(p9);
            bodyB.add(p10);
            bodyB.add(p11);
            bodyB.add(p12);
            bodyB.add(p13);
            bodyB.add(p14);
            bodyB.add(p15);
            bodyB.add(p16);
            bodyB.add(p17);
            bodyB.add(p18);
            bodyB.add(p19);
            bodyB.add(p20);
            bodyB.add(p21);
            bodyB.add(p22);
            bodyB.add(p23);
            bodyB.add(p24);
            bodyB.add(p25);
            bodyB.add(p26);

            OSG::PolygonBody::VecVerticesT uniqueVertices;
            uniqueVertices.push_back(OSG::Pnt3f(40.567329f, -0.099960543f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(69.083717f, -0.099999905f, -255.43610f));
            uniqueVertices.push_back(OSG::Pnt3f(-316.82861f, -0.099999905f, -422.14835f));
            uniqueVertices.push_back(OSG::Pnt3f(-147.22157f, -0.099981226f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(-147.22159f, -0.099981226f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14835f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, -0.099945091f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, 206.36839f, 2.1476247f));
            uniqueVertices.push_back(OSG::Pnt3f(-96.541801f, 167.21341f, 56.360508f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891682f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475983f));
            uniqueVertices.push_back(OSG::Pnt3f(69.083725f, -0.099999905f, -255.43610f));
            uniqueVertices.push_back(OSG::Pnt3f(40.567333f, -0.099960543f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(1.3627319f, 164.95033f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(-11.705462f, 219.96709f, -422.14841f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463730f, -0.099990845f, -83.674805f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 261.17880f, -422.14838f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 252.77078f, -190.67180f));
            uniqueVertices.push_back(OSG::Pnt3f(-131.61452f, -0.099999905f, 85.536140f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.820648f, -0.099999905f, 90.713882f));
            uniqueVertices.push_back(OSG::Pnt3f(-71.140770f, -0.099992089f, 94.801651f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36835f, 2.1476340f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36818f, 2.1476779f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36841f, 2.1475997f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 261.17877f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(1.3627319f, 164.95032f, -422.14844f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476860f));
            uniqueVertices.push_back(OSG::Pnt3f(-53.833496f, 14.790224f, 94.378685f));
            uniqueVertices.push_back(OSG::Pnt3f(97.937340f, 18.622017f, -60.753471f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463333f, -0.099999428f, -83.674263f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463753f, -0.099999905f, -83.674698f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60599f, -0.10000038f, 44.782143f));
            uniqueVertices.push_back(OSG::Pnt3f(-131.61453f, -0.099999905f, 85.536140f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, -0.10000563f, 44.782028f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 206.36815f, 2.1476822f));
            uniqueVertices.push_back(OSG::Pnt3f(55.229015f, 171.04536f, -98.771553f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 242.80931f, -106.90833f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 234.15105f, -57.891685f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60675f, 252.77078f, -190.67180f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 242.80930f, -106.90832f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463745f, -0.099990845f, -83.674759f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463730f, -0.099999905f, -83.674812f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463745f, -0.099999905f, -83.674751f));
            uniqueVertices.push_back(OSG::Pnt3f(-71.140549f, -0.10000038f, 94.801521f));
            uniqueVertices.push_back(OSG::Pnt3f(98.463341f, -0.099999905f, -83.674263f));
            uniqueVertices.push_back(OSG::Pnt3f(-71.140747f, -0.099999905f, 94.801636f));
            uniqueVertices.push_back(OSG::Pnt3f(-97.820633f, -0.099999905f, 90.713882f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, -0.10000610f, 44.782013f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, -0.099999905f, 44.781990f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, -0.099999905f, 44.782024f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, -0.099999905f, -422.14828f));
            bodyB.setVertices(uniqueVertices);

            //
            // Following the correct planes from the directX example run
            //
            OSG::Plane plCamNear  (OSG::Vec3f(0.66504061f, 0.35078523f, 0.65929568f), 94.396889f);
            OSG::Plane plCamFar   (OSG::Vec3f(-0.66504079f, -0.35078505f, -0.65929550f), 542.78040f);
            OSG::Plane plCamLeft  (OSG::Vec3f(-0.14838839f, 0.19998839f, 0.96849650f), 102.35148f);
            OSG::Plane plCamRight (OSG::Vec3f(0.95973027f, 0.22796552f, -0.16416341f), 108.21213f);
            OSG::Plane plCamBottom(OSG::Vec3f(0.55971670f, -0.63545793f, 0.53189331f), 10.669267f);
            OSG::Plane plCamTop   (OSG::Vec3f(0.10532385f, 0.98624313f, 0.12740240f), 161.92548f);

            OSG::FrustumVolume camFrust(plCamNear, plCamFar, plCamLeft, plCamRight, plCamTop, plCamBottom);

            //
            // The example's Frustum class does store the 'frustum corners'. These are not the
            // correct plane intersection points but the back transformed of the DirectX NDC 
            // bounding box [(-1,-1,0),(1,1,1)]. In order to get the same result as in the directX
            // example we have to use the very same corner points.
            //
            std::vector<OSG::Pnt3f> camFrustCorners;
            camFrustCorners.push_back(OSG::Pnt3f(-53.833530f, 14.790188f, 94.378601f));
            camFrustCorners.push_back(OSG::Pnt3f(97.937363f, 18.622013f, -60.753536f));
            camFrustCorners.push_back(OSG::Pnt3f(55.229088f, 171.04532f, -98.771545f));
            camFrustCorners.push_back(OSG::Pnt3f(-96.541809f, 167.21347f, 56.360600f));
            camFrustCorners.push_back(OSG::Pnt3f(-657.99438f, -504.99973f, 109.14530f));
            camFrustCorners.push_back(OSG::Pnt3f(112.11162f, -485.55685f, -678.01648f));
            camFrustCorners.push_back(OSG::Pnt3f(-104.59605f, 287.86002f, -870.92511f));
            camFrustCorners.push_back(OSG::Pnt3f(-874.70184f, 268.41663f, -83.763161f));

            OSG::Plane plLightNear  (OSG::Vec3f(-0.88121516f, 0.43680823f, -0.18071634f), 587.44617f);
            OSG::Plane plLightFar   (OSG::Vec3f(0.88121516f, -0.43680805f, 0.18071660f), 426.71161f);
            OSG::Plane plLightLeft  (OSG::Vec3f(-0.89797878f, 0.42112353f, -0.12762856f), 604.04993f);
            OSG::Plane plLightRight (OSG::Vec3f(-0.86150360f, 0.45103163f, -0.23319952f), 604.04993f);
            OSG::Plane plLightBottom(OSG::Vec3f(-0.85938650f, 0.48588881f, -0.15926999f), 604.04999f);
            OSG::Plane plLightTop   (OSG::Vec3f(-0.90009588f, 0.38626632f, -0.20155811f), 604.04987f);

            OSG::FrustumVolume lightFrust(plLightNear, plLightFar, plLightLeft, plLightRight, plLightTop, plLightBottom);

            OSG::BoxVolume sceneAABB(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14844f), OSG::Pnt3f(397.60669f, 329.10513f, 422.14844f));

            OSG::Vec2f zRange(140.98463f, 715.37512f);

            //
            // The function that we normally would call
            // 
            // OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
            //                            0,                  // unsigned int         split,
            //                            bodyB,              // const PolygonBody&   bodyB,
            //                            camFrust,           // const Frustum&       camFrust, 
            //                            0x0,                // const FrustumVolume* lightFrust, 
            //                            sceneAABB,          // const BoxVolume&     sceneAABB,
            //                            zRange              // const tVec2f&        zRange
            //                    );
            //

            //
            // To get around of the 'false' frustum plane intersection points we call this function to get the same result
            //
            OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
                                        0,                  // unsigned int         split,
                                        bodyB,              // const PolygonBody&   bodyB,
                                        camFrustCorners,    // const VecVerticesT&  camFrustCorners, 
                                        &lightFrust,        // const FrustumVolume* lightFrust, 
                                        sceneAABB,          // const BoundingBox&   sceneAABB,
                                        zRange              // const tVec2f&        zRange
                                );
            //
            //              [0.109617, -0.054687,  0.000000, -0.000741]
            // liSPMatrix = [0.705244,  1.413626,  0.000000,  0.037487]
            //              [0.000000,  0.000000,  0.122501, -0.118981]
            //              [0.446419,  0.894824,  0.000000,  0.146230]
            //

            int ijk = 234;
        }

        // LiSP test IV
        {
            //
            // This test takes values from DirectX example
            //
            OSG::LiSPSMTechnique liSP(2);

            liSP.setMode(OSG::LiSPSMTechnique::ARBITRARY);
            liSP.setArbScaled(false);
            liSP.setParamN(324.27762f, 0);
            liSP.setParamN(1.0000000f, 1);
            liSP.setSplitParam(0.5f);

            OSG::Matrix4f matLightProj(
                0.057911590f, 0.00000000f,  0.00000000f,  0.00000000f,
                0.00000000f,  0.057911590f, 0.00000000f,  0.00000000f,
                0.00000000f,  0.00000000f, -1.0347396f, -35.843311f,
                0.00000000f,  0.00000000f, -1.0000000f,   0.00000000f);
            liSP.setLightProjMat(matLightProj, OSG::Projection::PERSPECTIVE);

            OSG::Matrix4f matLightView(
                0.33558467f,  0.30881563f, -0.88995260f,   -5.5088717e-006f,
                -0.33293071f, -0.84488535f, -0.41871920f,   -3.2874848e-006f,
                -0.88121516f,  0.43680838f, -0.18071641f, -605.06201f,
                 0.00000000f,  0.00000000f,  0.00000000f,    1.0000000f);

            OSG::View viewLightView(
                OSG::Pnt3f(-533.18976f, 264.29614f, -109.34463f),
                OSG::Pnt3f(0.00000000f, 0.00000000f, 0.00000000f),
                OSG::Vec3f(9.0862562e-009f, -0.38229418f, -0.92404062f));

            liSP.setLightView(matLightView, viewLightView);

            OSG::Matrix4f matCamView(
                 0.76445252f, 0.018136535f, -0.64442474f,  -16.306841f,
                -0.23731807f, 0.93732780f,  -0.25513998f,  -87.878571f,
                 0.59941000f, 0.34797609f,   0.72084683f, -171.58147f,
                 0.00000000f, 0.00000000f,   0.00000000f,    1.0000000f);

            OSG::View viewCamView(
                OSG::Pnt3f(94.458290f, 142.37306f, 90.754105f),
                OSG::Pnt3f(93.858879f, 142.02509f, 90.033257f),
                OSG::Vec3f(-0.016558312f, 0.99982685f, 0.0084964950f));

            liSP.setCamView(matCamView, viewCamView);

            OSG::Matrix4f matCamProj(
                1.2990381f,  0.00000000f,  0.00000000f,   0.00000000f,
                0.00000000f, 1.7320508f,   0.00000000f,   0.00000000f,
                0.00000000f, 0.00000000f, -1.5293325f, -198.09848f,
                0.00000000f, 0.00000000f, -1.0000000f,    0.00000000f);

            liSP.setCamProjMat(matCamProj);

            liSP.setFieldOfView(60.000000f);
            liSP.setGamma(59.570404f);
            liSP.setSplitParam(0.50000000f);
            liSP.setPseudoNear(0.12000000f);
            liSP.setPseudoFar(0.19000000f);

            // Artificially construct a PolygonBody for the test
            OSG::PolygonBody bodyB;

            OSG::Polygon* p1 = new OSG::Polygon;
            p1->addVertex(OSG::Pnt3f(39.089149f, 219.89795f, -419.79834f));
            p1->addVertex(OSG::Pnt3f(94.789619f, -0.10000610f, -359.91510f));
            p1->addVertex(OSG::Pnt3f(94.789391f, -0.099999905f, -359.91498f));
            p1->addVertex(OSG::Pnt3f(-397.60672f, 207.21199f, -163.44366f));
            p1->addVertex(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89661f));

            OSG::Polygon* p2 = new OSG::Polygon;
            p2->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));
            p2->addVertex(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11368f));
            p2->addVertex(OSG::Pnt3f(94.789619f, -0.099999905f, -359.91510f));
            p2->addVertex(OSG::Pnt3f(39.089149f, 219.89795f, -419.79834f));

            OSG::Polygon* p3 = new OSG::Polygon;
            p3->addVertex(OSG::Pnt3f(94.789429f, -0.10000610f, -359.91498f));
            p3->addVertex(OSG::Pnt3f(-348.32108f, -0.099999905f, 8.5473785f));
            p3->addVertex(OSG::Pnt3f(-397.60672f, 70.387497f, -22.882376f));
            p3->addVertex(OSG::Pnt3f(-397.60672f, 207.21201f, -163.44366f));

            OSG::Polygon* p4 = new OSG::Polygon;
            p4->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            p4->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));
            p4->addVertex(OSG::Pnt3f(39.089149f, 219.89795f, -419.79834f));

            OSG::Polygon* p5 = new OSG::Polygon;
            p5->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            p5->addVertex(OSG::Pnt3f(39.089149f, 219.89795f, -419.79834f));
            p5->addVertex(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89659f));
            p5->addVertex(OSG::Pnt3f(-397.60672f, 243.10803f, -104.13360f));

            OSG::Polygon* p6 = new OSG::Polygon;
            p6->addVertex(OSG::Pnt3f(-77.159714f, 165.58900f, 42.558334f));
            p6->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            p6->addVertex(OSG::Pnt3f(-397.60672f, 243.10805f, -104.13360f));
            p6->addVertex(OSG::Pnt3f(-397.60672f, 234.94934f, -64.182037f));

            OSG::Polygon* p7 = new OSG::Polygon;
            p7->addVertex(OSG::Pnt3f(-77.159714f, 165.58900f, 42.558334f));
            p7->addVertex(OSG::Pnt3f(-397.60669f, 234.94936f, -64.182045f));
            p7->addVertex(OSG::Pnt3f(-397.60672f, 208.93826f, -47.432968f));

            OSG::Polygon* p8 = new OSG::Polygon;
            p8->addVertex(OSG::Pnt3f(-348.32104f, -0.10000610f, 8.5473785f));
            p8->addVertex(OSG::Pnt3f(-348.32104f, -0.099999905f, 8.5473833f));
            p8->addVertex(OSG::Pnt3f(-397.60669f, 194.56253f, -44.439548f));
            p8->addVertex(OSG::Pnt3f(-397.60672f, 194.56255f, -44.439564f));
            p8->addVertex(OSG::Pnt3f(-397.60672f, 70.387527f, -22.882401f));

            OSG::Polygon* p9 = new OSG::Polygon;
            p9->addVertex(OSG::Pnt3f(-397.60669f, 194.56253f, -44.439548f));
            p9->addVertex(OSG::Pnt3f(-397.60672f, 199.35445f, -45.437359f));
            p9->addVertex(OSG::Pnt3f(-397.60672f, 194.56255f, -44.439564f));

            OSG::Polygon* p10 = new OSG::Polygon;
            p10->addVertex(OSG::Pnt3f(-397.60672f, 208.93802f, -47.432915f));
            p10->addVertex(OSG::Pnt3f(-397.60672f, 199.35445f, -45.437359f));
            p10->addVertex(OSG::Pnt3f(-397.60669f, 194.56253f, -44.439548f));
            p10->addVertex(OSG::Pnt3f(-348.32104f, -0.099990845f, 8.5473824f));
            p10->addVertex(OSG::Pnt3f(-348.32104f, -0.099999905f, 8.5473833f));

            OSG::Polygon* p11 = new OSG::Polygon;
            p11->addVertex(OSG::Pnt3f(-192.92177f, -0.099999905f, 47.810863f));
            p11->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            p11->addVertex(OSG::Pnt3f(-232.79909f, -0.099999905f, 37.735397f));

            OSG::Polygon* p12 = new OSG::Polygon;
            p12->addVertex(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398239f));
            p12->addVertex(OSG::Pnt3f(-232.79910f, -0.099999905f, 37.735397f));
            p12->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            p12->addVertex(OSG::Pnt3f(-71.326195f, -0.099907897f, 78.533524f));

            OSG::Polygon* p13 = new OSG::Polygon;
            p13->addVertex(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474182f));
            p13->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            p13->addVertex(OSG::Pnt3f(-192.92177f, -0.099999905f, 47.810863f));

            OSG::Polygon* p14 = new OSG::Polygon;
            p14->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));
            p14->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            p14->addVertex(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474197f));
            p14->addVertex(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11369f));

            OSG::Polygon* p15 = new OSG::Polygon;
            p15->addVertex(OSG::Pnt3f(-397.60672f, 208.93802f, -47.432915f));
            p15->addVertex(OSG::Pnt3f(-348.32104f, -0.099990845f, 8.5473824f));
            p15->addVertex(OSG::Pnt3f(-348.32077f, -0.099999905f, 8.5474529f));
            p15->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p15->addVertex(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432945f));

            OSG::Polygon* p16 = new OSG::Polygon;
            p16->addVertex(OSG::Pnt3f(-71.326195f, -0.099907897f, 78.533524f));
            p16->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p16->addVertex(OSG::Pnt3f(-348.32077f, -0.10000038f, 8.5474472f));
            p16->addVertex(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398243f));

            OSG::Polygon* p17 = new OSG::Polygon;
            p17->addVertex(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432961f));
            p17->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p17->addVertex(OSG::Pnt3f(-77.159714f, 165.58900f, 42.558334f));
            p17->addVertex(OSG::Pnt3f(-397.60669f, 208.93826f, -47.432961f));

            OSG::Polygon* p18 = new OSG::Polygon;
            p18->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p18->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            p18->addVertex(OSG::Pnt3f(-77.159714f, 165.58900f, 42.558334f));

            OSG::Polygon* p19 = new OSG::Polygon;
            p19->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p19->addVertex(OSG::Pnt3f(-71.326195f, -0.099907897f, 78.533524f));
            p19->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));

            OSG::Polygon* p20 = new OSG::Polygon;
            p20->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p20->addVertex(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            p20->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));

            OSG::Polygon* p21 = new OSG::Polygon;
            p21->addVertex(OSG::Pnt3f(110.78994f, 29.008524f, -47.796570f));
            p21->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));
            p21->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));

            OSG::Polygon* p22 = new OSG::Polygon;
            p22->addVertex(OSG::Pnt3f(110.78994f, 29.008524f, -47.796570f));
            p22->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            p22->addVertex(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));

            OSG::Polygon* p23 = new OSG::Polygon;
            p23->addVertex(OSG::Pnt3f(110.78994f, 29.008524f, -47.796570f));
            p23->addVertex(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            p23->addVertex(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));

            OSG::Polygon* p24 = new OSG::Polygon;
            p24->addVertex(OSG::Pnt3f(94.789619f, -0.099999905f, -359.91510f));
            p24->addVertex(OSG::Pnt3f(-348.32108f, -0.099999905f, 8.5473785f));
            p24->addVertex(OSG::Pnt3f(94.789429f, -0.10000610f, -359.91498f));
            p24->addVertex(OSG::Pnt3f(-348.32104f, -0.10000610f, 8.5473785f));
            p24->addVertex(OSG::Pnt3f(-348.32104f, -0.099999905f, 8.5473833f));
            p24->addVertex(OSG::Pnt3f(-348.32104f, -0.099990845f, 8.5473824f));
            p24->addVertex(OSG::Pnt3f(-192.92177f, -0.099999905f, 47.810863f));
            p24->addVertex(OSG::Pnt3f(-232.79909f, -0.099999905f, 37.735397f));
            p24->addVertex(OSG::Pnt3f(-232.79910f, -0.099999905f, 37.735397f));
            p24->addVertex(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398239f));
            p24->addVertex(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474182f));
            p24->addVertex(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474197f));
            p24->addVertex(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11369f));
            p24->addVertex(OSG::Pnt3f(-348.32077f, -0.099999905f, 8.5474529f));
            p24->addVertex(OSG::Pnt3f(-348.32077f, -0.10000038f, 8.5474472f));
            p24->addVertex(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398243f));
            p24->addVertex(OSG::Pnt3f(94.789391f, -0.099999905f, -359.91498f));
            p24->addVertex(OSG::Pnt3f(94.789619f, -0.10000610f, -359.91510f));
            p24->addVertex(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11368f));

            OSG::Polygon* p25 = new OSG::Polygon;
            p25->addVertex(OSG::Pnt3f(-397.60672f, 207.21199f, -163.44366f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 207.21201f, -163.44366f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 70.387497f, -22.882376f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 243.10803f, -104.13360f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89659f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 234.94934f, -64.182037f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 243.10805f, -104.13360f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 208.93826f, -47.432968f));
            p25->addVertex(OSG::Pnt3f(-397.60669f, 234.94936f, -64.182045f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 70.387527f, -22.882401f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 194.56255f, -44.439564f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 199.35445f, -45.437359f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 208.93802f, -47.432915f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432945f));
            p25->addVertex(OSG::Pnt3f(-397.60669f, 208.93826f, -47.432961f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432961f));
            p25->addVertex(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89661f));

            bodyB.add(p1);
            bodyB.add(p2);
            bodyB.add(p3);
            bodyB.add(p4);
            bodyB.add(p5);
            bodyB.add(p6);
            bodyB.add(p7);
            bodyB.add(p8);
            bodyB.add(p9);
            bodyB.add(p10);
            bodyB.add(p11);
            bodyB.add(p12);
            bodyB.add(p13);
            bodyB.add(p14);
            bodyB.add(p15);
            bodyB.add(p16);
            bodyB.add(p17);
            bodyB.add(p18);
            bodyB.add(p19);
            bodyB.add(p20);
            bodyB.add(p21);
            bodyB.add(p22);
            bodyB.add(p23);
            bodyB.add(p24);
            bodyB.add(p25);

            OSG::PolygonBody::VecVerticesT uniqueVertices;
            uniqueVertices.push_back(OSG::Pnt3f(39.089149f, 219.89795f, -419.79834f));
            uniqueVertices.push_back(OSG::Pnt3f(94.789619f, -0.10000610f, -359.91510f));
            uniqueVertices.push_back(OSG::Pnt3f(94.789391f, -0.099999905f, -359.91498f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 207.21199f, -163.44366f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89661f));
            uniqueVertices.push_back(OSG::Pnt3f(114.98345f, -0.099913903f, -83.372223f));
            uniqueVertices.push_back(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11368f));
            uniqueVertices.push_back(OSG::Pnt3f(94.789619f, -0.099999905f, -359.91510f));
            uniqueVertices.push_back(OSG::Pnt3f(94.789429f, -0.10000610f, -359.91498f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32108f, -0.099999905f, 8.5473785f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 70.387497f, -22.882376f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 207.21201f, -163.44366f));
            uniqueVertices.push_back(OSG::Pnt3f(75.293877f, 169.20604f, -85.958290f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 253.77744f, -182.89659f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 243.10803f, -104.13360f));
            uniqueVertices.push_back(OSG::Pnt3f(-77.159714f, 165.58900f, 42.558334f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 243.10805f, -104.13360f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 234.94934f, -64.182037f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, 234.94936f, -64.182045f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 208.93826f, -47.432968f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32104f, -0.10000610f, 8.5473785f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32104f, -0.099999905f, 8.5473833f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, 194.56253f, -44.439548f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 194.56255f, -44.439564f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 70.387527f, -22.882401f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 199.35445f, -45.437359f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 208.93802f, -47.432915f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32104f, -0.099990845f, 8.5473824f));
            uniqueVertices.push_back(OSG::Pnt3f(-192.92177f, -0.099999905f, 47.810863f));
            uniqueVertices.push_back(OSG::Pnt3f(-71.326172f, -0.099968173f, 78.533470f));
            uniqueVertices.push_back(OSG::Pnt3f(-232.79909f, -0.099999905f, 37.735397f));
            uniqueVertices.push_back(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398239f));
            uniqueVertices.push_back(OSG::Pnt3f(-232.79910f, -0.099999905f, 37.735397f));
            uniqueVertices.push_back(OSG::Pnt3f(-71.326195f, -0.099907897f, 78.533524f));
            uniqueVertices.push_back(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474182f));
            uniqueVertices.push_back(OSG::Pnt3f(-32.678337f, -0.099999905f, -23.474197f));
            uniqueVertices.push_back(OSG::Pnt3f(105.87453f, -0.099999905f, -208.11369f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32077f, -0.099999905f, 8.5474529f));
            uniqueVertices.push_back(OSG::Pnt3f(-41.663677f, 25.391619f, 80.720161f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432945f));
            uniqueVertices.push_back(OSG::Pnt3f(-348.32077f, -0.10000038f, 8.5474472f));
            uniqueVertices.push_back(OSG::Pnt3f(-293.50140f, -0.099999905f, 22.398243f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60672f, 208.93825f, -47.432961f));
            uniqueVertices.push_back(OSG::Pnt3f(-397.60669f, 208.93826f, -47.432961f));
            uniqueVertices.push_back(OSG::Pnt3f(110.78994f, 29.008524f, -47.796570f));
            bodyB.setVertices(uniqueVertices);

            //
            // Following the correct planes from the directX example run
            //
            OSG::Plane plCamNear  (OSG::Vec3f(0.59941006f, 0.34797609f, 0.72084683f), 93.261017f);
            OSG::Plane plCamFar   (OSG::Vec3f(-0.59941006f, -0.34797603f, -0.72084689f), 202.66058f);
            OSG::Plane plCamLeft  (OSG::Vec3f(-0.24011993f, 0.19789197f, 0.95035857f), 91.742088f);
            OSG::Plane plCamRight (OSG::Vec3f(0.97139335f, 0.22663496f, -0.070933454f), 117.58536f);
            OSG::Plane plCamBottom(OSG::Vec3f(0.50522858f, -0.63776171f, 0.58138120f), 9.6856546f);
            OSG::Plane plCamTop   (OSG::Vec3f(0.094181575f, 0.98573798f, 0.13946572f), 161.89584f);

            OSG::FrustumVolume camFrust(plCamNear, plCamFar, plCamLeft, plCamRight, plCamTop, plCamBottom);

            //
            // The example's Frustum class does store the 'frustum corners'. These are not the
            // correct plane intersection points but the back transformed of the DirectX NDC 
            // bounding box [(-1,-1,0),(1,1,1)]. In order to get the same result as in the directX
            // example we have to use the very same corner points.
            //
            std::vector<OSG::Pnt3f> camFrustCorners;
            camFrustCorners.push_back(OSG::Pnt3f(-41.663712f, 25.391582f, 80.720078f));
            camFrustCorners.push_back(OSG::Pnt3f(110.78996f, 29.008520f, -47.796635f));
            camFrustCorners.push_back(OSG::Pnt3f(75.293953f, 169.20599f, -85.958282f));
            camFrustCorners.push_back(OSG::Pnt3f(-77.159721f, 165.58907f, 42.558426f));
            camFrustCorners.push_back(OSG::Pnt3f(-298.82150f, -195.60651f, 61.764080f));
            camFrustCorners.push_back(OSG::Pnt3f(141.64330f, -185.15656f, -309.54276f));
            camFrustCorners.push_back(OSG::Pnt3f(39.089241f, 219.89804f, -419.79834f));
            camFrustCorners.push_back(OSG::Pnt3f(-401.37555f, 209.44807f, -48.491474f));

            OSG::Plane plLightNear  (OSG::Vec3f(-0.88121527f, 0.43680814f, -0.18071631f), 587.44641f);
            OSG::Plane plLightFar   (OSG::Vec3f(0.88121486f, -0.43680876f, 0.18071611f), 426.71146f);
            OSG::Plane plLightLeft  (OSG::Vec3f(-0.89914292f, 0.41822335f, -0.12896173f), 604.04993f);
            OSG::Plane plLightRight (OSG::Vec3f(-0.86033958f, 0.45393157f, -0.23186630f), 604.04993f);
            OSG::Plane plLightBottom(OSG::Vec3f(-0.86049294f, 0.48492423f, -0.15620588f), 604.04993f);
            OSG::Plane plLightTop   (OSG::Vec3f(-0.89898950f, 0.38723066f, -0.20462216f), 604.04993f);

            OSG::FrustumVolume lightFrust(plLightNear, plLightFar, plLightLeft, plLightRight, plLightTop, plLightBottom);

            OSG::BoxVolume sceneAABB(OSG::Pnt3f(-397.60672f, -0.099999905f, -422.14844f), OSG::Pnt3f(397.60669f, 329.10513f, 422.14844f));

            OSG::Vec2f zRange(129.53264f, 714.25018f);

            //
            // The function that we normally would call
            // 
            // OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
            //                            0,                  // unsigned int         split,
            //                            bodyB,              // const PolygonBody&   bodyB,
            //                            camFrust,           // const Frustum&       camFrust, 
            //                            0x0,                // const FrustumVolume* lightFrust, 
            //                            sceneAABB,          // const BoxVolume&     sceneAABB,
            //                            zRange              // const tVec2f&        zRange
            //                    );
            //

            //
            // To get around of the 'false' frustum plane intersection points we call this function to get the same result
            //
            OSG::Matrix4f liSPMatrix = liSP.getLiSPMtx(
                                        0,                  // unsigned int         split,
                                        bodyB,              // const PolygonBody&   bodyB,
                                        camFrustCorners,    // const VecVerticesT&  camFrustCorners, 
                                        &lightFrust,        // const FrustumVolume* lightFrust, 
                                        sceneAABB,          // const BoundingBox&   sceneAABB,
                                        zRange              // const tVec2f&        zRange
                                );
            //
            //              [0.041494 -0.020267  0.000000 -0.000335]
            // liSPMatrix = [0.951689  1.948423  0.000000  0.033009]
            //              [0.000000  0.000000  0.046179 -0.044914]
            //              [0.438885  0.898543  0.000000  0.061402]
            //

            int ijk = 234;
        }
    }

    //
    // some OpenSG example code
    //
    {
        OSG::Pnt3f pos  = OSG::Pnt3f(5.f);              // only x-coord is set to 5.f
        OSG::Pnt3f pos1 = OSG::Pnt3f(5.f, 5.f, 5.f);    // this is to be used instead!
        OSG::Pnt3f pos2 = OSG::Pnt3f(3.f, 2.f, 1.f);
        OSG::Vec3f dir  = OSG::Vec3f(1.f, 2.f, 3.f);

        OSG::Real32 l1 = dir.length();
        OSG::Real32 l2 = dir.squareLength();

        OSG::Vec3f n = dir; n.normalize();

        OSG::Real32 dist1 = pos1.dist (pos2);  // distance(pos1, pos2) = length(pos2 - pos1)
        OSG::Real32 dist2 = pos1.dist2(pos2);  // distance(pos1, pos2) * distance(pos2, pos1)


        OSG::Matrix4f model, ortho, ortho2D, frustum, projection, projectionfov, inf_projection;
        OSG::Matrix4f eps_inf_projection, inv_view, view, mvp, inv_mat;
        OSG::Matrix4f id;
    
        bool result;
   
        id.setIdentity();       // not really necessary, ctor does initialize to identity matrix
        model.setIdentity();

        result = OSG::MatrixOrthogonal(ortho, -3.f, 2.f, -6.f, 1.3f, 0.1f, 100.f);
        //                   columns
        //         (0.400  0.000  0.000  0.200)
        // ortho = (0.000  0.274  0.000  0.644)     rows
        //         (0.000  0.000 -0.020 -1.002)
        //         (0.000  0.000  0.000  1.000)
        //                                             _m[0]     _m[1]     _m[2]     _m[3]
        //   _m[0] = [0.400, 0.000, 0.000, 0.000]    [ 0.400]  [ 0.000]  [ 0.000]  [ 0.200]
        //   _m[1] = [0.000, 0.274, 0.000, 0.000]    [ 0.000]  [ 0.274]  [ 0.000]  [ 0.644]
        //   _m[2] = [0.000, 0.000,-0.020, 0.000]    [ 0.000]  [ 0.000]  [-0.020]  [-1.002]
        //   _m[3] = [0.200, 0.644,-1.002, 1.000]    [ 0.000]  [ 0.000]  [ 0.000]  [ 1.000]
        //

        result = OSG::MatrixOrthogonal2D(ortho2D, -3.f, 2.f, -6.f, 1.3f);
        //                    columns
        //        ( 0.400   0.000  0.000  0.200)
        //   rows ( 0.000   0.274  0.000  0.644)
        //        ( 0.000   0.000 -1.000  0.000)
        //        ( 0.000   0.000  0.000  1.000)
        //

        result = OSG::MatrixFrustum(frustum, -3.f, 2.f, -6.f, 1.3f, 0.1f, 100.f);
        //                     columns
        //        ( 0.0400  0.0000 -0.2000  0.0000)
        //   rows ( 0.0000  0.0274 -0.6440  0.0000)
        //        ( 0.0000  0.0000 -1.0020 -0.2000)
        //        ( 0.0000  0.0000 -1.0000  0.0000)
        //

        result = OSG::MatrixPerspective(projection, OSG::osgDegree2Rad(45.0f / 2.f), 4.0f / 3.0f, 0.1f, 100.0f);
        //                    columns
        //        ( 1.811  0.000  0.000  0.000)
        //   rows ( 0.000  2.414  0.000  0.000)
        //        ( 0.000  0.000 -1.002 -0.200)
        //        ( 0.000  0.000 -1.000  0.000)
        //

        result = OSG::MatrixPerspective(projectionfov, OSG::osgDegree2Rad(45.0f / 2.f), 300.f, 200.f, 0.1f, 100.0f);
        //                   columns
        //        ( 1.609  0.000  0.000  0.000)
        //   rows ( 0.000  2.414  0.000  0.000)
        //        ( 0.000  0.000 -1.002 -0.200)
        //        ( 0.000  0.000 -1.000  0.000)
        //

        result = OSG::MatrixInfinitePerspective(inf_projection, OSG::osgDegree2Rad(45.0f / 2.f), 4.0f / 3.0f, 0.1f);
        //                   columns
        //        ( 1.811  0.000  0.000  0.000)
        //   rows ( 0.000  2.414  0.000  0.000)
        //        ( 0.000  0.000 -1.000 -0.200)
        //        ( 0.000  0.000 -1.000  0.000)
        //

        result = OSG::MatrixEpsInfinitePerspective(eps_inf_projection, OSG::osgDegree2Rad(45.0f / 2.f), 4.0f / 3.0f, 0.1f, 3.0E-7f);
        //                  columns
        //        ( 1.811  0.000  0.000  0.000)
        //   rows ( 0.000  2.414  0.000  0.000)
        //        ( 0.000  0.000 -0.100 -0.200)
        //        ( 0.000  0.000 -1.000  0.000)
        //

        inv_view.setIdentity();
        result = MatrixLookAt(
                                inv_view, 
                                OSG::Pnt3f(4,3,3),  // Camera is at (4,3,-3), in World Space
                                OSG::Pnt3f(0,0,0),  // and looks at the origin
                                OSG::Vec3f(0,1,0)   // Head is up (set to 0,-1,0 to look upside-down)
                             );
        //                  columns
        //        ( 0.600 -0.412  0.686  4.000)
        //   rows ( 0.000  0.857  0.514  3.000)
        //        (-0.800 -0.309  0.514  3.000)
        //        ( 0.000  0.000  0.000  1.000)
        //

        view.setIdentity();
        result = MatrixLookAtGL(
                                view, 
                                OSG::Pnt3f(4,3,3),  // Camera is at (4,3,-3), in World Space
                                OSG::Pnt3f(0,0,0),  // and looks at the origin
                                OSG::Vec3f(0,1,0)   // Head is up (set to 0,-1,0 to look upside-down)
                             );
        //                   columns
        //        ( 0.600  0.000 -0.800  0.000)
        //   rows (-0.412  0.857 -0.309  0.000)
        //        ( 0.686  0.514  0.514 -5.831)
        //        ( 0.000  0.000  0.000  1.000)

        mvp.setIdentity();
        mvp.mult(projection);
        mvp.mult(view);
        mvp.mult(model);
        //                                columns
        //        ( 1.086395980  0.000000000 -1.448528050  0.000000000 )
        //   rows (-0.993682027  2.070170880 -0.745261550  0.000000000 )
        //        (-0.687367737 -0.515525818 -0.515525818  5.642426010 )
        //        (-0.685994387 -0.514495790 -0.514495790  5.830952640 )
        mvp.inverse(inv_mat);
        //                               columns
        //        ( 0.331370682 -0.170488641 -19.97998620  19.33399010 )
        //   rows ( 5.4487e-7    0.355185300 -14.98498920  14.50049300 )
        //        (-0.441827208 -0.127866760 -14.98498920  14.50049400 )
        //        ( 0.000000000  0.000000000  -4.99499607   5.00499630 )

        OSG::Matrix4f trsp_mat;
        mvp.transposed(trsp_mat);
        //                               columns
        //        (  1.08639598 -0.99368202 -0.687367737 -0.68599439 )
        //   rows (  0.00000000  2.07017088 -0.515525818 -0.51449579 )
        //        ( -1.44852805 -0.74526155 -0.515525818 -0.51449579 )
        //        (  0.00000000  0.00000000  5.64242601   5.83095264 )

        OSG::Matrix4f inv_trsp_mat;
        mvp.inverse(inv_trsp_mat);
        inv_trsp_mat.transpose();
        //                               columns
        //        (   0.331370533   5.44869465e-007  -0.441826999   0.00000000 )
        //   rows (  -0.170488566   0.355185151      -0.127866715   0.00000000 )
        //        ( -19.9799767   -14.9849825       -14.9849825    -4.99499369 )
        //        (  19.3339825    14.5004864        14.5004873     5.00499439 )

        OSG::Real32* pMat =  mvp.getValues();
        //   [ 1.08639598,  -0.993682027, -0.687367737, -0.685994387,
        //     0.00000000,   2.07017088,  -0.515525818, -0.51449579,
        //    -1.44852805,  -0.74526155,  -0.515525818, -0.51449579,
        //     0.00000000,   0.00000000,   5.64242601,   5.83095264 ]

        OSG::Matrix4f T;
        T.setTranslate(pos1);
        T.multLeft(id);
        //          columns
        //        ( 1 0 0 5 )
        //   rows ( 0 1 0 5 )
        //        ( 0 0 1 5 )
        //        ( 0 0 0 1 )

        OSG::Matrix4f Rx;
        OSG::Quaternion qx(OSG::Vec3f(1.f, 0.f, 0.f), OSG::osgDegree2Rad(10.f));
        Rx.setRotate(qx);
        Rx.multLeft(T);
        //                     columns
        //        (  1  0            0            5 )
        //   rows (  0  0.98480773  -0.173648179  5 )
        //        (  0  0.173648179  0.98480773   5 )
        //        (  0  0            0            1 )

        OSG::Matrix4f Ry;
        OSG::Quaternion qy(OSG::Vec3f(0.f, 1.f, 0.f), OSG::osgDegree2Rad(12.f));
        Ry.setRotate(qy);
        Ry.multLeft(Rx);
        //                        columns
        //        ( 0.978147626  0            0.2079117    5 )
        //   rows ( 0.036103487  0.98480773  -0.169853553  5 )
        //        (-0.204753056  0.173648179  0.963287354  5 )
        //        ( 0            0            0            1 )

        OSG::Matrix4f S;
        S.setScale(OSG::Vec3f(1000.f, 1000.f, 1000.f));
        S.multLeft(id);
        //                 columns
        //        ( 1000    0    0    0 )
        //   rows (    0 1000    0    0 )
        //        (    0    0 1000    0 )
        //        (    0    0    0    1 )

        OSG::Pnt4f pr;
        OSG::Pnt4f px(17.3f, 12.6f, 13.2f, 1.f);
        pr = mvp * px;
        mvp.mult(px, pr);
        //      [-0.325920105, -0.943996429, -19.5496025, -19.3107414]

        OSG::Pnt4f py(17.3f, 12.6f, 13.2f, 9.6f);
        pr = mvp * py;
        mvp.mult(py, pr);
        //      [-0.325920105, -0.943996429, 28.9752674, 30.8354530]

        OSG::Vec4f vr;
        OSG::Vec4f vx(17.3f, 12.6f, 13.2f, 0.f);
        vr = mvp * vx;
        mvp.mult(vx, vr);
        //      [-0.325920105, -0.943996429, -25.1920280, -25.1416931]

        OSG::Vec3f v1(12.4f, 1.4f, 17.6f);
        OSG::Vec3f v2( 7.4f, 0.2f, 12.1f);
        OSG::Real32 val = v1.dot(v2);

        int ijk = 234;
    }

    //
    // Determine View from matrix
    //
    {
        bool result;

        OSG::Pnt3f from(19.6f, 24.8f, 10.4f);
        OSG::Pnt3f   at( 3.0f,-21.2f,-11.7f);
        OSG::Vec3f   up( 0.f,   1.f,   0.f);

        OSG::Matrix matWSFromES;
        result = MatrixLookAt(matWSFromES, from, at, up);
        //    ( 0.799565554  -0.514794350   0.309324354  19.6000004)
        //    ( 0.000000000   0.515043736   0.857163846  24.7999992)
        //    (-0.600578725  -0.685358703   0.411811292  10.3999996)
        //    ( 0.000000000   0.000000000   0.000000000   1.0000000)

        OSG::Matrix matESFromWS;
        result = MatrixLookAtGL(matESFromWS, from, at, up);
        //    ( 0.799565554   0.000000000  -0.600578725  -9.42546654)
        //    (-0.514794350   0.515043736  -0.685358703   4.44461536)
        //    ( 0.309324354   0.857163846   0.411811292 -31.60325620)
        //    ( 0.000000000   0.000000000   0.000000000   1.00000000)

        //
        // Now that we have these matrices, we would like to get the view,
        // i.e. the from, at, up parameters back.
        //
        // Case 1: from a matESFromWS
        {
            OSG::Matrix tmp_matWSFromES;
            matESFromWS.inverse(tmp_matWSFromES);

            OSG::Pnt3f new_from(0,0,0);
            tmp_matWSFromES.mult(new_from, new_from);

            OSG::Vec3f new_up  (matESFromWS[0][1], matESFromWS[1][1],matESFromWS[2][1]);
            OSG::Vec3f new_look(matESFromWS[0][2], matESFromWS[1][2],matESFromWS[2][2]);

            OSG::Real32 L = new_from.subZero().length();
            OSG::Pnt3f new_at = new_from - L*new_look;

            //
            // Now, we test new_from, new_at and new_up parameters, by creating the two matrices
            // new_matWSFromES and new_matESFromWS from them. These should be equal to the original
            // matrices.
            //
            OSG::Matrix new_matWSFromES, new_matESFromWS;
            result = MatrixLookAt  (new_matWSFromES, new_from, new_at, new_up);
            result = MatrixLookAtGL(new_matESFromWS, new_from, new_at, new_up);

            OSG_ASSERT(new_matWSFromES.equals(matWSFromES, 1.E-4f));
            OSG_ASSERT(new_matESFromWS.equals(matESFromWS, 1.E-4f));

            //
            // Finally, create a View object from the new parameters.
            //
            OSG::View eView(new_from, new_at, new_up);
            eView.setValue(new_from, new_at, new_up);

            //
            // The steps above are already implemented in the View class, so we can
            // just use the setValue function of the View with the matESFromWS as
            // input. The flag determines whether to use eys space from world space
            // or wise versa.
            //
            eView.setValue(matESFromWS, false);

            //
            // Constructing a View from the matESFromWS works accordingly.
            //
            OSG::View test(matESFromWS, false);

            int ijk = 234;
        }

        // Case 2: from a matWSFromES
        {
            OSG::Pnt3f new_from(matWSFromES[3]);
            OSG::Vec3f new_up  (matWSFromES[1]);
            OSG::Vec3f new_look(matWSFromES[2]);

            OSG::Real32 L = new_from.subZero().length();
            OSG::Pnt3f new_at = new_from - L*new_look;

            //
            // Now, we test new_from, new_at and new_up parameters, by creating the two matrices
            // new_matWSFromES and new_matESFromWS from them. These should be equal to the original
            // matrices.
            //
            OSG::Matrix new_matWSFromES, new_matESFromWS;
            result = MatrixLookAt  (new_matWSFromES, new_from, new_at, new_up);
            result = MatrixLookAtGL(new_matESFromWS, new_from, new_at, new_up);

            OSG_ASSERT(new_matWSFromES.equals(matWSFromES, 1.E-4f));
            OSG_ASSERT(new_matESFromWS.equals(matESFromWS, 1.E-4f));

            //
            // Finally, create a View object from the new parameters.
            //
            OSG::View eView(new_from, new_at, new_up);
            eView.setValue(new_from, new_at, new_up);

            //
            // The steps above are already implemented in the View class, so we can
            // just use the setValue function of the View with the matWSFromES as
            // input. The flag determines whether to use eys space from world space
            // or wise versa.
            //
            eView.setValue(matWSFromES, true);

            //
            // Constructing a View from the matWSFromES works accordingly.
            //
            OSG::View test(matWSFromES, true);

            int ijk = 234;
        }

        OSG::FrustumVolume camFrust;
        camFrust.setPlanes(matESFromWS);
        OSG::Pnt3f center;
        camFrust.getCenter(center);

        int ijk = 234;
    }

    //
    // Determine Projection from matrix
    //
    {
        // Case 1: From a perspective projection matrix
        {
            OSG::Real32 fov    = OSG::osgDegree2Rad(45.0f / 2.f);
            OSG::Real32 aspect = 4.0f / 3.0f;
            OSG::Real32 zNear  = 0.1f;
            OSG::Real32 zFar   = 100.f;

            OSG::Matrix matPersProjection;
            bool result = OSG::MatrixPerspective(matPersProjection, fov, aspect, zNear, zFar);
            //                    columns
            //        ( 1.811  0.000  0.000  0.000)
            //   rows ( 0.000  2.414  0.000  0.000)
            //        ( 0.000  0.000 -1.002 -0.200)
            //        ( 0.000  0.000 -1.000  0.000)
            //

            //
            // Given that projection matrix, we would like to get back the fov, aspect, zNear
            // and zFar parameters.
            //
            OSG::Real32 m00 = matPersProjection[0][0];
            OSG::Real32 m02 = matPersProjection[2][0];
            OSG::Real32 m11 = matPersProjection[1][1];
            OSG::Real32 m12 = matPersProjection[2][1];
            OSG::Real32 m22 = matPersProjection[2][2];
            OSG::Real32 m23 = matPersProjection[3][2];

            OSG::Real32 N = m23 / (m22 - 1);
            OSG::Real32 F = m23 / (m22 + 1);

            OSG::Real32 L = m23/m00 * (m02 - 1)/(m22 - 1);
            OSG::Real32 R = m23/m00 * (m02 + 1)/(m22 - 1);

            OSG::Real32 B = m23/m11 * (m12 - 1)/(m22 - 1);
            OSG::Real32 T = m23/m11 * (m12 + 1)/(m22 - 1);

            OSG::Real32 ct;
            ct = -B/N;
            ct =  T/N;

            OSG::Real32 new_aspect, new_fov, new_zNear, new_zFar;

            new_aspect = -L /(N * ct);
            new_aspect =  R /(N * ct);

            new_fov = OSG::osgATan(ct);

            new_zNear = N;
            new_zFar  = F;

            OSG::Matrix new_matPersProjection;
            result = OSG::MatrixPerspective(new_matPersProjection, new_fov, new_aspect, new_zNear, new_zFar);

            OSG_ASSERT(new_matPersProjection.equals(matPersProjection, 1.E-4f));

            OSG::Real32 FOV = OSG::osgRad2Degree(OSG::osgATan(ct)) * 2.f;

            //
            // Alternative the helper PerspectiveProjection can be used
            //
            OSG::PerspectiveProjection projection(matPersProjection);

            new_matPersProjection.setIdentity();
            result = OSG::MatrixPerspective(new_matPersProjection, projection);
            OSG_ASSERT(new_matPersProjection.equals(matPersProjection, 1.E-4f));

            int ijk = 234;
        }

        // Case 2: From a orthographic projection matrix
        {
            OSG::Real32 left   =  -3.0f;
            OSG::Real32 right  =   2.0f;
            OSG::Real32 bottom =  -6.0f;
            OSG::Real32 top    =   1.3f;
            OSG::Real32 zNear  =   0.1f;
            OSG::Real32 zFar   = 100.0f;

            OSG::Matrix matOrthoProjection;
            bool result = OSG::MatrixOrthogonal(matOrthoProjection, left, right, bottom, top, zNear, zFar);
            //                   columns
            //         (0.400  0.000  0.000  0.200)
            // ortho = (0.000  0.274  0.000  0.644)     rows
            //         (0.000  0.000 -0.020 -1.002)
            //         (0.000  0.000  0.000  1.000)

            //
            // Given that projection matrix, we would like to get back the left, right, bottom, top, zNear
            // and zFar parameters.
            //
            OSG::Real32 m00 = matOrthoProjection[0][0];
            OSG::Real32 m03 = matOrthoProjection[3][0];
            OSG::Real32 m11 = matOrthoProjection[1][1];
            OSG::Real32 m13 = matOrthoProjection[3][1];
            OSG::Real32 m22 = matOrthoProjection[2][2];
            OSG::Real32 m23 = matOrthoProjection[3][2];

            OSG::Real32 new_left, new_right, new_bottom, new_top, new_zNear, new_zFar;

            new_left   = -(m03 + 1)/m00;
            new_right  =  (1 - m03)/m00;

            new_bottom = -(m13 + 1)/m11;
            new_top    =  (1 - m13)/m11;

            new_zNear  =  (m23 + 1)/m22;
            new_zFar   = -(1 - m23)/m22;

            OSG::Matrix new_matOrthoProjection;
            result = OSG::MatrixOrthogonal(new_matOrthoProjection, new_left, new_right, new_bottom, new_top, new_zNear, new_zFar);

            OSG_ASSERT(new_matOrthoProjection.equals(matOrthoProjection, 1.E-4f));

            //
            // Alternative the helper OrthographicProjection can be used
            //
            OSG::OrthographicProjection projection(matOrthoProjection);

            new_matOrthoProjection.setIdentity();
            result = OSG::MatrixOrthogonal(new_matOrthoProjection, projection);
            OSG_ASSERT(new_matOrthoProjection.equals(matOrthoProjection, 1.E-4f));

            int ijk = 234;
        }
    }

/*  Time consuming, use only if necessary
    //
    // Poisson Disk Generator
    //
    {
        std::ofstream out("d:\\PoissonDisk.txt");

        out << std::fixed << std::setw( 12 ) << std::setprecision( 7 );

        {
            OSG::PoissonDiskGenerator<OSG::Real32> generator(time(0));

            generator.setMaxIterations(100);
            generator.setSizeFactor(2.f);
            generator.setUseCircle(true);

            std::vector<OSG::Pnt2f> disk;

            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                generator.clear();

                OSG::UInt32 size = Ns[i];
                disk = generator.getDisk(size);

                out << "PoissonDisk size = " << size << std::endl;

                for (int j = 0; j < disk.size(); ++j)
                {
                    OSG::Real32 x,y;
                    x = disk[j].x(); y = disk[j].y();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    
                    out << j << "] = Vec2f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f);" << std::endl;
                }

                out << std::endl;

                for (int j = 0; j < disk.size(); ++j)
                {
                    OSG::Real32 x,y;
                    x = disk[j].x(); y = disk[j].y();

                    out << "    << endl << \"    vec2(";
                    if (x > 0.f) out << " ";
                    out << x << ",";
                    if (y > 0.f) out << " ";
                    out << y << ")";
                    if (j < disk.size() - 1)
                    out << ",";
                    out << "\"" << std::endl;
                }

                out << std::endl << std::endl;

                int isdf = 323;
            }
        }
        
        {
            OSG::PoissonDiskGenerator<OSG::Real32> generator(time(0));

            generator.setMaxIterations(100);
            generator.setSizeFactor(2.f);

            generator.setUseCircle(true);

            std::vector<OSG::Pnt3f> sphere;

            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                generator.clear();

                OSG::UInt32 size = Ns[i];
                sphere = generator.getSphere(size);

                out << "PoissonSphere size = " << size << std::endl;

                for (int j = 0; j < sphere.size(); ++j)
                {
                    OSG::Real32 x,y,z;
                    x = sphere[j].x(); y = sphere[j].y(); z = sphere[j].z();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    
                    out << j << "] = Vec3f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f,";
                    if (z > 0.f) out << " ";
                    out << z << "f);" << std::endl;
                }

                out << std::endl;

                for (int j = 0; j < sphere.size(); ++j)
                {
                    OSG::Real32 x,y,z;
                    x = sphere[j].x(); y = sphere[j].y(); z = sphere[j].z();

                    out << "    << endl << \"    vec3(";
                    if (x > 0.f) out << " ";
                    out << x << ",";
                    if (y > 0.f) out << " ";
                    out << y << ",";
                    if (z > 0.f) out << " ";
                    out << z << ")";
                    if (j < sphere.size() - 1)
                    out << ",";
                    out << "\"" << std::endl;
                }

                out << std::endl << std::endl;

                int isdf = 323;
            }
        }

        int ijk = 234;
    }

    {
        std::ofstream out("d:\\PoissonQuad.txt");

        out << std::fixed << std::setw( 12 ) << std::setprecision( 7 );

        {
            OSG::PoissonDiskGenerator<OSG::Real32> generator(time(0));

            generator.setMaxIterations(100);
            generator.setSizeFactor(2.f);
            generator.setUseCircle(false);

            std::vector<OSG::Pnt2f> disk;

            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                generator.clear();

                OSG::UInt32 size = Ns[i];
                disk = generator.getDisk(size);

                out << "PoissonQuad size = " << size << std::endl;

                for (int j = 0; j < disk.size(); ++j)
                {
                    OSG::Real32 x,y;
                    x = disk[j].x(); y = disk[j].y();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    
                    out << j << "] = Vec2f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f);" << std::endl;
                }

                out << std::endl << std::endl;

                int isdf = 323;
            }
        }
        
        {
            OSG::PoissonDiskGenerator<OSG::Real32> generator(time(0));

            generator.setMaxIterations(100);
            generator.setSizeFactor(2.f);

            generator.setUseCircle(false);

            std::vector<OSG::Pnt3f> sphere;

            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                generator.clear();

                OSG::UInt32 size = Ns[i];
                sphere = generator.getSphere(size);

                out << "PoissonBox size = " << size << std::endl;

                for (int j = 0; j < sphere.size(); ++j)
                {
                    OSG::Real32 x,y,z;
                    x = sphere[j].x(); y = sphere[j].y(); z = sphere[j].z();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    
                    out << j << "] = Vec3f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f,";
                    if (z > 0.f) out << " ";
                    out << z << "f);" << std::endl;
                }

                out << std::endl << std::endl;

                int isdf = 323;
            }
        }

        int ijk = 234;
    }

    //
    // Poisson Hemisphere calculation
    //
    {
        std::ofstream out("d:\\PoissonHemisphere.txt");

        out << std::fixed << std::setw( 12 ) << std::setprecision( 7 );

        {
            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                std::vector<OSG::Vec2f> disk = OSG::Distribution::getPoissonDisk(Ns[i]);

                std::vector<OSG::Vec3f> hemisphere = OSG::Distribution::calcHemisphereSurfaceFromDisk(disk);

                std::size_t size = hemisphere.size();

                out << "PoissonHemisphere size = " << size << std::endl;

                for (int j = 0; j < hemisphere.size(); ++j)
                {
                    OSG::Vec3f P = hemisphere[j];

                    OSG::Real32 x,y,z;
                    x = P.x(); y = P.y(); z = P.z();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    
                    out << j << "] = Vec3f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f,";
                    if (z > 0.f) out << " ";
                    out << z << "f);" << std::endl;
                }

                out << std::endl << std::endl;

                for (int j = 0; j < hemisphere.size(); ++j)
                {
                    OSG::Vec3f P = hemisphere[j];
                    OSG::Vec3f Q = P; Q.normalize();

                    OSG::Real32 x,y,z;
                    x = P.x(); y = P.y(); z = P.z();

                    OSG::Real32 x_,y_,z_;
                    x_ = Q.x(); y_ = Q.y(); z_ = Q.z();

                    out << "    result[";
                    if (j < 10) out << "  ";
                    else if (j < 100) out << " ";
                    out << j << "] = Vec3f(";
                    if (x > 0.f) out << " ";
                    out << x << "f,";
                    if (y > 0.f) out << " ";
                    out << y << "f,";
                    if (z > 0.f) out << " ";
                    out << z << "f) == Vec3f(";

                    if (x_ > 0.f) out << " ";
                    out << x_ << "f,";
                    if (y_ > 0.f) out << " ";
                    out << y_ << "f,";
                    if (z_ > 0.f) out << " ";
                    out << z_ << "f);" << std::endl;
                }

                out << std::endl;

                int isdf = 323;
            }
        }
        int ijk = 234;
    }

    {
        std::ofstream out("d:\\PoissonDistributions.txt");

        out << std::fixed << std::setw( 12 ) << std::setprecision( 7 );

        {
            std::vector<int> Ns;
            Ns.push_back(9);
            Ns.push_back(16);
            Ns.push_back(25);
            Ns.push_back(32);
            Ns.push_back(64);
            Ns.push_back(100);
            Ns.push_back(128);
            Ns.push_back(256);

            for (int i = 0; i < Ns.size(); ++i)
            {
                std::vector<OSG::Real32> line       = OSG::Distribution::getPoissonLine                (Ns[i]);
                std::vector<OSG::Vec2f>  disk       = OSG::Distribution::getPoissonDisk                (Ns[i]);
                std::vector<OSG::Vec2f>  quad       = OSG::Distribution::getPoissonQuad                (Ns[i]);
                std::vector<OSG::Vec3f>  sphere     = OSG::Distribution::getPoissonSphere              (Ns[i]);
                std::vector<OSG::Vec3f>  box        = OSG::Distribution::getPoissonBox                 (Ns[i]);
                std::vector<OSG::Vec3f>  hemisphere = OSG::Distribution::getPoissonHemisphere          (Ns[i]);
                std::vector<OSG::Vec3f>  surface    = OSG::Distribution::getPoissonHemisphereSurface   (Ns[i]);

                for (int j = 0; j < 3; ++j)
                {
                    std::random_shuffle(line      .begin(), line      .end(), myRandom);
                    std::random_shuffle(disk      .begin(), disk      .end(), myRandom);
                    std::random_shuffle(quad      .begin(), quad      .end(), myRandom);
                    std::random_shuffle(sphere    .begin(), sphere    .end(), myRandom);
                    std::random_shuffle(box       .begin(), box       .end(), myRandom);
                    std::random_shuffle(hemisphere.begin(), hemisphere.end(), myRandom);
                    std::random_shuffle(surface   .begin(), surface   .end(), myRandom);
                }

                std::size_t size;

                {
                    size = line.size();

                    out << "PoissonLine size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Real32 x = line[j];

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = ";
                        if (x > 0.f) out << " ";
                        out << x << "f;" << std::endl;
                    }

                    out << std::endl << std::endl;
                }

                {
                    size = disk.size();

                    out << "PoissonDisk size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec2f  P = disk[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec2f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }

                {
                    size = quad.size();

                    out << "PoissonQuad size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec2f  P = quad[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec2f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }


                {
                    size = sphere.size();

                    out << "PoissonSphere size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec3f  P = sphere[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();
                        OSG::Real32 z = P.z();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec3f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f,";
                        if (z > 0.f) out << " ";
                        out << z << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }

                {
                    size = box.size();

                    out << "PoissonBox size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec3f  P = box[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();
                        OSG::Real32 z = P.z();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec3f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f,";
                        if (z > 0.f) out << " ";
                        out << z << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }

                {
                    size = hemisphere.size();

                    out << "PoissonHemisphere size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec3f  P = hemisphere[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();
                        OSG::Real32 z = P.z();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec3f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f,";
                        if (z > 0.f) out << " ";
                        out << z << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }

                {
                    size = surface.size();

                    out << "PoissonHemisphereSuface size = " << size << std::endl;

                    for (int j = 0; j < size; ++j)
                    {
                        OSG::Vec3f  P = surface[j];
                        OSG::Real32 x = P.x();
                        OSG::Real32 y = P.y();
                        OSG::Real32 z = P.z();

                        out << "            result[";
                        if (j < 10) out << "  ";
                        else if (j < 100) out << " ";
                    
                        out << j << "] = Vec3f(";
                        if (x > 0.f) out << " ";
                        out << x << "f,";
                        if (y > 0.f) out << " ";
                        out << y << "f,";
                        if (z > 0.f) out << " ";
                        out << z << "f);" << std::endl;
                    }

                    out << std::endl << std::endl;
                }
            }
        }
    }
*/

    //
    // SHA-1 test
    //
    {
        OSG::Sha1 sha1;

        OSG_ASSERT(sha1.check("abc", "A9993e36" "4706816a" "Ba3e2571" "7850C26c" "9cd0d89d"));
        OSG_ASSERT(sha1.check("",    "da39a3ee" "5e6b4b0d" "3255bfef" "95601890" "afd80709"));
        OSG_ASSERT(sha1.check("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", "84983e44" "1c3bd26e" "baae4aa1" "f95129e5" "e54670f1"));
        OSG_ASSERT(sha1.check("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", "a49b2446" "a02c645b" "f419f995" "b6709125" "3a04a259"));

        std::string s1     = sha1.get_from_string("abc");
        std::string s1_hex = sha1.get_from_string_hex("abc");

        std::string s2     = sha1.get_from_string("");
        std::string s2_hex = sha1.get_from_string_hex("");

        std::string s3     = sha1.get_from_string("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
        std::string s3_hex = sha1.get_from_string_hex("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");

        std::string s4     = sha1.get_from_string("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");
        std::string s4_hex = sha1.get_from_string_hex("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");

        std::string test1 = "abcdbcdecdefdefgefghfghig";
        std::string test2 = "hijhijkijkljklmklmnlmnomnopnopq";

        sha1.reset();
        sha1.update(test1.data(), test1.size());
        sha1.update(test2.data(), test2.size());

        std::string result;
        result.resize(OSG::Sha1::DIGEST_BYTES);
        sha1.finish(&result[0]);

        result = sha1.hex(result);

        result = sha1.get_from_file_hex("Data/dinopet.3ds");
        result = sha1.get_from_file_hex("Data/MyNanoSuit.obj");
        result = sha1.get_from_file_hex("Data/dinopet.3ds");
        result = sha1.get_from_file_hex("Data/machine5.osb");
        

        int ijk = 237;
    }

    // Hashing test
    {
        std::vector<BYTE> vecBytes;
        {
            std::ifstream ifs ("Data/MyNanoSuit.obj", std::ifstream::binary);
            ifs.unsetf(std::ios::skipws);

            std::streampos fileSize;
            ifs.seekg(0, std::ios::end);
            fileSize = ifs.tellg();
            ifs.seekg(0, std::ios::beg);
            
            vecBytes.resize(fileSize);
            ifs.read((char*)&vecBytes[0], fileSize);
        }


        // Hash32 test
        {
            OSG::UInt32 result;

            result = OSG::Hash32::hash(&vecBytes[0], vecBytes.size(), 0);
            result = OSG::Hash32::hash_from_file("Data/machine5.osb", 0);

            std::string hex_string = OSG::Hash32::to_hex_string(result, true);
            result = OSG::Hash32::from_hex_string(hex_string);

            OSG::Hash32 hasher;

            int ijk = 2345;
        }

        // Hash64 test
        {
            OSG::UInt64 result;

            result = OSG::Hash64::hash(&vecBytes[0], vecBytes.size(), 0);
            result = OSG::Hash64::hash_from_file("Data/machine5.osb", 0);

            std::string hex_string = OSG::Hash64::to_hex_string(result, true);
            result = OSG::Hash64::from_hex_string(hex_string);

            OSG::Hash64 hasher;

            int ijk = 2345;
        }
    }
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    glm_math_library();
    vmath_math_library();
    osg_math_library();

    return 0;
}
