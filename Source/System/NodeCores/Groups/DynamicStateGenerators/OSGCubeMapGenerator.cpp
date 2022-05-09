/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <boost/filesystem.hpp>

#include "OSGConfig.h"

#include "OSGCubeMapGenerator.h"
#include "OSGCubeMapGeneratorStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGCubeTextureObjChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGRenderAction.h"
#include "OSGPerspectiveCamera.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCubeMapGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGCubeMapGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CubeMapGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            CubeMapGenerator::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &CubeMapGenerator::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            CubeMapGenerator::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &CubeMapGenerator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CubeMapGenerator::CubeMapGenerator(void) :
    Inherited()
,   requestImage(false)
{
}

CubeMapGenerator::CubeMapGenerator(const CubeMapGenerator &source) :
    Inherited(source)
,   requestImage(false)
{
}

CubeMapGenerator::~CubeMapGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CubeMapGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CubeMapGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CubeMapGenerator NI" << std::endl;
}

void CubeMapGenerator::createCubeMapImage(FrameBufferObject* renderTarget)
{
    if (requestImage)
    {
        static char* target_names[6] = 
        {
            "-z_",
            "+z_",
            "+y_",
            "-y_",
            "+x_",
            "-x_"
        };

        if (renderTarget)
        {
            namespace fs = ::boost::filesystem;

            fs::path base = getName();

            fs::path ext  = base.extension();
            fs::path pth  = base.parent_path();
            fs::path stem = base.stem();
    
            ImageUnrecPtr assembled = NULL;

            for(UInt32 i = 0; i < 6; ++i)
            {
                fs::path tmp = target_names[i]; tmp += stem;
                fs::path name = pth / tmp;

                name.replace_extension(ext);

                FrameBufferAttachment* fba = renderTarget->getColorAttachments(i);
                if (fba)
                {
                    TextureBuffer* tb = dynamic_cast<TextureBuffer*>(fba);
                    if (tb)
                    {
                        CubeTextureObjChunk* texObj = dynamic_cast<CubeTextureObjChunk*>(tb->getTexture());
                        if (texObj)
                        {
                            Image* img = NULL;
                            switch (i)
                            {
                                case 0:
                                    {
                                        img = texObj->getPosZImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(true, true);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        3 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        5 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }

                                        }
                                    }
                                    break;
                                case 1: 
                                    {
                                        img = texObj->getImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(true, true);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        4 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }
                                        }
                                    }
                                    break;
                                case 2: 
                                    {
                                        img = texObj->getPosYImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(false, false);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 3 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 3 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        2 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }
                                        }
                                    }
                                    break;
                                case 3: 
                                    {
                                        img = texObj->getNegYImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(false, false);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(false, false);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        3 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }
                                        }
                                    }
                                    break;
                                case 4: 
                                    {
                                        img = texObj->getPosXImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(true, true);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        2 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        2 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 5 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }
                                        }
                                    }
                                    break;
                                case 5: 
                                    {
                                        img = texObj->getNegXImage();
                                        if (img && img->getData())
                                        {
                                            switch(getImageType())
                                            {
                                                case INDIVIDUAL:
                                                    img->mirror(true, true);
                                                    img->write(name.string().c_str());
                                                    requestImage = false;
                                                    break;
                                                case VERTICAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                                        3 * img->getWidth(), 4 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_CROSS_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case VERTICAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        0 * img->getWidth(), 4 * img->getHeight(), 0, 
                                                                        1 * img->getWidth(), 6 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                                case HORIZONTAL_STRIP_CUBE_MAP:
                                                    img->mirror(true, true);
                                                    assembled = img->placeSubImage(
                                                                        0,0,0, 
                                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                                        1 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                                        6 * img->getWidth(), 1 * img->getHeight(), img->getDepth(),
                                                                        assembled);
                                                    break;
                                            }
                                        }
                                    }
                                    break;

                            }
                        }
                    }
                }
            }

            if (assembled && assembled->getData())
            {
                //assembled->mirror(false, true, false);
                assembled->write(base.string().c_str());
                requestImage = false;
            }
        }
    }
}

// Begin Test Joe
void dump_image(const char* name, const char* ext, FrameBufferObject* fbo)
{
    static bool once = false;
    if (once)
        return;

    if (fbo)
    {
        static char* target_names[6] = 
        {
            "+z",
            "-z",
            "+y",
            "-y",
            "+x",
            "-x"
        };

        std::string img_file = name;

        ImageUnrecPtr imgCross = NULL;

        for(UInt32 i = 0; i < 6; ++i)
        {
            std::stringstream ss;

            ss << name << "_" << target_names[i] << ext;
            
            FrameBufferAttachment* fba = fbo->getColorAttachments(i);
            if (fba)
            {
                TextureBuffer* tb = dynamic_cast<TextureBuffer*>(fba);
                if (tb)
                {
                    CubeTextureObjChunk* texObj = dynamic_cast<CubeTextureObjChunk*>(tb->getTexture());
                    if (texObj)
                    {
                        Image* img = NULL;
                        switch (i)
                        {
                            case 0:
                                {
                                    img = texObj->getPosZImage();
                                    if (img && img->getData())
                                    {
                                        img->mirror(true, true);
                                        imgCross = img->placeSubImage(
                                                            0,0,0, 
                                                            img->getWidth(), img->getHeight(), img->getDepth(),
                                                            1 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                            4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                            imgCross);

                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;
                            case 1: 
                                {
                                    img = texObj->getImage();
                                    if (img && img->getData())
                                    {
                                        img->mirror(true, true);
                                        imgCross = img->placeSubImage(
                                                            0,0,0, 
                                                            img->getWidth(), img->getHeight(), img->getDepth(),
                                                            3 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                            4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                            imgCross);
                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;
                            case 2: 
                                {
                                    img = texObj->getPosYImage();
                                    if (img && img->getData())
                                    {
                                        imgCross = img->placeSubImage(
                                                        0,0,0, 
                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                        1 * img->getWidth(), 2 * img->getHeight(), 0, 
                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                        imgCross);
                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;
                            case 3: 
                                {
                                    img = texObj->getNegYImage();
                                    if (img && img->getData())
                                    {
                                        imgCross = img->placeSubImage(
                                                        0,0,0, 
                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                        1 * img->getWidth(), 0 * img->getHeight(), 0, 
                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                        imgCross);
                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;
                            case 4: 
                                {
                                    img = texObj->getPosXImage();
                                    if (img && img->getData())
                                    {
                                        img->mirror(true, true);
                                        imgCross = img->placeSubImage(
                                                        0,0,0, 
                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                        2 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                        imgCross);
                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;
                            case 5: 
                                {
                                    img = texObj->getNegXImage();
                                    if (img && img->getData())
                                    {
                                        img->mirror(true, true);
                                        imgCross = img->placeSubImage(
                                                        0,0,0, 
                                                        img->getWidth(), img->getHeight(), img->getDepth(),
                                                        0 * img->getWidth(), 1 * img->getHeight(), 0, 
                                                        4 * img->getWidth(), 3 * img->getHeight(), img->getDepth(),
                                                        imgCross);
                                        img->write(ss.str().c_str());
                                    }
                                }
                                break;

                        }
                    }
                }
            }
        }

        if (imgCross && imgCross->getData())
        {
            std::stringstream ss;
            ss << name << "_cross" << ext;

            //imgCross->mirror(false, true, false);
            imgCross->write(ss.str().c_str());

            once = true;
        }
    }
}
// End Test Joe

Action::ResultE CubeMapGenerator::renderEnter(Action *action)
{
    static Matrix transforms[] = 
    { 
        Matrix( 1,  0,  0,  0,
                0, -1,  0,  0,
                0,  0, -1,  0,
                0,  0,  0,  1),
        
        Matrix(-1,  0,  0,  0,
                0, -1,  0,  0,
                0,  0,  1,  0,
                0,  0,  0,  1),
        
        Matrix( 1,  0,  0,  0,
                0,  0, -1,  0,
                0,  1,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 1,  0,  0,  0,
                0,  0,  1,  0,
                0, -1,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 0,  0, -1,  0,
                0, -1,  0,  0,
               -1,  0,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 0,  0,  1,  0,
                0, -1,  0,  0,
                1,  0,  0,  0,
                0,  0,  0,  1)
    };

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Action::ResultE  returnValue = Action::Continue;

    Background      *pBack    = a->getBackground();

    Node            *pActNode = a->getActNode();

    CubeMapGeneratorStageData *pData = 
        a->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = this->initData(a);
    }

    TraversalValidator::ValidationStatus eStatus = this->validateOnEnter(a);

    if(eStatus == TraversalValidator::Run)
    {
        this->beginPartitionGroup(a);
        {
            FrameBufferObject *pTarget  = this->getRenderTarget();
                
            if(pTarget == NULL)
            {
                pTarget  = pData->getRenderTarget();
            }

            Pnt3f oOrigin;

            if(this->getOriginMode() == CubeMapGenerator::UseStoredValue)
            {
                oOrigin = this->getOrigin();
            }
            else if(this->getOriginMode() == CubeMapGenerator::UseBeacon)
            {
                fprintf(stderr, "CubemapGen::UseBeacon NYI\n");
            }
            else if(this->getOriginMode() == 
                                       CubeMapGenerator::UseCurrentVolumeCenter)
            {
                BoxVolume oWorldVol;

                commitChanges();

                pActNode->updateVolume();
                
                pActNode->getWorldVolume(oWorldVol);
                
                oWorldVol.getCenter(oOrigin);
            }
            else if(this->getOriginMode() == 
                                       CubeMapGenerator::UseParentsVolumeCenter)
            {
                fprintf(stderr, "CubemapGen::UseParentsCenter NYI\n");
            }

            Camera *pCam = pData->getCamera();

            pActNode->setTravMask(0);

            for(UInt32 i = 0; i < 6; ++i)
            {
                this->pushPartition(a);
                {
                    RenderPartition   *pPart    = a->getActivePartition();
                
                    pPart->setVolumeDrawing(false);

                    pPart->setRenderTarget(pTarget       );
                    pPart->setWindow      (a->getWindow());

                    pPart->calcViewportDimension(0,
                                                 0,
                                                 1,
                                                 1,
                                                 this->getWidth (),
                                                 this->getHeight());
                
                    Matrix m, t;
            
                    // set the projection
                    pCam->getProjection          (m, 
                                                  pPart->getViewportWidth (), 
                                                  pPart->getViewportHeight());
                
                    pCam->getProjectionTranslation(t, 
                                                   pPart->getViewportWidth (), 
                                                   pPart->getViewportHeight());
                
                    pPart->setupProjection(m, t);
            
                    m = transforms[i];
            
                    m[3][0] = oOrigin[0];
                    m[3][1] = oOrigin[1];
                    m[3][2] = oOrigin[2];

                    m.invert();

                    pPart->setupViewing(m);
            
                    pPart->setNear     (pCam->getNear());
                    pPart->setFar      (pCam->getFar ());
                    
                    pPart->calcFrustum();
                
                    if(this->getBackground() == NULL)
                    {
                        pPart->setBackground(pBack);
                    }
                    else
                    {
                        pPart->setBackground(this->getBackground());
                    }
                
                    if(this->getRoot() != NULL)
                    {
                        this->recurse(a, this->getRoot());
                    }
                    else
                    {
                        this->recurse(a, a->getTraversalRoot());
                    }

                    pPart->setDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + i);

#ifdef OSG_DEBUGX
                    std::string szMessage("CubeX\n");
                    pPart->setDebugString(szMessage          );
#endif
                }
                this->popPartition(a);
            }

            pActNode->setTravMask(~0);
        }
        this->endPartitionGroup(a);
    }

    OSG_ASSERT(pActNode == a->getActNode());

    returnValue = Inherited::renderEnter(action);

    action->useNodeList(false);

    return returnValue;
}

Action::ResultE CubeMapGenerator::renderLeave(Action *action)
{
    Action::ResultE returnValue = Action::Continue;

    returnValue = Inherited::renderLeave(action);

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    this->validateOnLeave(a);

    CubeMapGeneratorStageDataUnrecPtr pData = 
        a->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if (pData && getStoreImage())
    {
        createCubeMapImage(pData->getRenderTarget());
        //dump_image(R"(d:\_xxx\test\a)", ".tiff", pData->getRenderTarget());
    }

    return returnValue;
}


CubeMapGeneratorStageDataTransitPtr CubeMapGenerator::setupStageData(
    RenderAction *pAction)
{
    CubeMapGeneratorStageDataTransitPtr returnValue = 
        CubeMapGeneratorStageData::createLocal();
    
    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectUnrecPtr pCubeTarget  = NULL;
    RenderBufferUnrecPtr      pDepthBuffer = NULL;

    if(this->getRenderTarget() == NULL)
    {
        pCubeTarget  = FrameBufferObject::createLocal();
        pDepthBuffer = RenderBuffer     ::createLocal();

        pDepthBuffer->setInternalFormat (GL_DEPTH_COMPONENT24);

        // Begin Test Joe
        pCubeTarget ->setPostProcessOnDeactivate(true);
        // End Test Joe

        pCubeTarget ->setDepthAttachment(pDepthBuffer        );

        returnValue ->setRenderTarget   (pCubeTarget         );
    }
    else
    {
        pCubeTarget = this->getRenderTarget();
    }

    CubeTextureObjChunkUnrecPtr pCubeTex = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexture))
    {
        pCubeTex = CubeTextureObjChunk::createLocal();

        ImageUnrecPtr pImgPX = Image::createLocal();
        ImageUnrecPtr pImgMX = Image::createLocal();
        ImageUnrecPtr pImgPY = Image::createLocal();
        ImageUnrecPtr pImgMY = Image::createLocal();
        ImageUnrecPtr pImgPZ = Image::createLocal();
        ImageUnrecPtr pImgMZ = Image::createLocal();

        UInt32 pixelFormat = Image::OSG_RGB_PF;
        Int32 width  = getWidth();
        Int32 height = getHeight();
        Int32 type   = Image::OSG_FLOAT32_IMAGEDATA; // Image::OSG_UINT8_IMAGEDATA;

        pImgPX->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);
        pImgMX->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);
        pImgPY->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);
        pImgMY->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);
        pImgPZ->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);
        pImgMZ->set(pixelFormat, width, height, 1, 1, 1, 0.f, NULL, type, false, 1);

        pCubeTex->setPosXImage(pImgPX);
        pCubeTex->setNegXImage(pImgMX);
        pCubeTex->setPosYImage(pImgPY);
        pCubeTex->setNegYImage(pImgMY);            
        pCubeTex->setPosZImage(pImgPZ);
        pCubeTex->setImage    (pImgMZ);

        pCubeTex->setTarget   (GL_TEXTURE_CUBE_MAP);

        pCubeTex->setMinFilter(GL_LINEAR);
        pCubeTex->setMagFilter(GL_LINEAR);
        pCubeTex->setWrapS    (GL_CLAMP_TO_EDGE);
        pCubeTex->setWrapT    (GL_CLAMP_TO_EDGE);
        pCubeTex->setWrapR    (GL_CLAMP_TO_EDGE);

        GLenum eTexTarget = this->getTextureFormat();

        if(eTexTarget == GL_NONE)
        {
            eTexTarget = pAction->getActivePartition()->
                getDrawEnv().getTargetBufferFormat();
        }

        pCubeTex->setInternalFormat(eTexTarget);
    }
    else
    {
        //pCubeTex = _sfTexture.getValue();
    }

    //TextureObjChunkUnrecPtr   pCubeTex     = NULL;

    //if(0x0000 != (_sfSetupMode.getValue() & SetupTexture))
    //{
    //    pCubeTex = TextureObjChunk::createLocal();

    //    ImageUnrecPtr pImg = Image::createLocal();
    //
    //    pImg->set(Image::OSG_RGB_PF, 
    //              getWidth (), 
    //              getHeight(),
    //              1,
    //              1,
    //              1,
    //              0.0,
    //              0,
    //              // Begin Test Joe
    //              //Image::OSG_UINT8_IMAGEDATA,
    //              Image::OSG_FLOAT16_IMAGEDATA,
    //              //Image::OSG_FLOAT32_IMAGEDATA,
    //              // End Test Joe
    //              false,
    //              6);
    //    
    //    pCubeTex   ->setImage         (pImg              ); 
    //    pCubeTex   ->setMinFilter     (GL_LINEAR         );
    //    pCubeTex   ->setMagFilter     (GL_LINEAR         );
    //    pCubeTex   ->setWrapS         (GL_CLAMP_TO_EDGE  );
    //    pCubeTex   ->setWrapT         (GL_CLAMP_TO_EDGE  );
    //    pCubeTex   ->setWrapR         (GL_CLAMP_TO_EDGE  );

    //    GLenum eTexTarget = this->getTextureFormat();

    //    if(eTexTarget == GL_NONE)
    //    {
    //        eTexTarget = pAction->getActivePartition()->
    //            getDrawEnv().getTargetBufferFormat();
    //    }

    //    pCubeTex->setInternalFormat(eTexTarget);
    //}
    //else
    //{
    //    pCubeTex = _sfTexture.getValue();
    //}

    TextureEnvChunkUnrecPtr pCubeTexEnv  = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        pCubeTexEnv = TextureEnvChunk::createLocal();
        
        pCubeTexEnv->setEnvMode       (GL_REPLACE       );
    }

    TexGenChunkUnrecPtr           pCubeTexGen   = NULL;
    TextureTransformChunkUnrecPtr pCubeTexTrans = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        pCubeTexGen = TexGenChunk::createLocal();

        pCubeTexGen->setGenFuncS(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncT(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncR(GL_REFLECTION_MAP);

        pCubeTexTrans = TextureTransformChunk::createLocal();

        pCubeTexTrans->setUseCameraBeacon(true);
    }


    static GLenum targets[6] = 
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
    };

    for(UInt32 i = 0; i < 6; ++i)
    {
        TextureBufferUnrecPtr pCubeTexBuffer = TextureBuffer::createLocal();
    
        // Begin Test Joe
        pCubeTexBuffer->setReadBack(true);
        pCubeTexBuffer->setLevel          (0);
        // End Test Joe

        pCubeTexBuffer->setTexture  (pCubeTex  );
        pCubeTexBuffer->setTexTarget(targets[i]);

        pCubeTarget->setColorAttachment(pCubeTexBuffer,    i);
    }

    pCubeTarget->setSize(getWidth (),
                         getHeight());

    if(0x0000 != (_sfSetupMode.getValue() & OverrideTex))
    {
        returnValue->addChunk(pCubeTex,
                              getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        returnValue->addChunk(pCubeTexEnv,
                              getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        returnValue->addChunk(pCubeTexGen,
                              getTexUnit());
        returnValue->addChunk(pCubeTexTrans,
                              getTexUnit());

        returnValue->setTexTransform(pCubeTexTrans);
    }

    if(this->getCamera() == NULL)
    {
        PerspectiveCameraUnrecPtr pCam = PerspectiveCamera::createLocal();

        pCam->setNear(pAction->getCamera()->getNear());
        pCam->setFar (pAction->getCamera()->getFar ());
        
        pCam->setFov (osgDegree2Rad(90.f));

        returnValue->setCamera(pCam);
    }

    return returnValue;
}

CubeMapGeneratorStageData *CubeMapGenerator::initData(RenderAction *pAction)
{
    CubeMapGeneratorStageDataUnrecPtr pData = 
        pAction->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction);
        
        this->setData(pData, _iDataSlotId, pAction);
    }

    return pData;
}


OSG_END_NAMESPACE
