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

#ifndef _OSGSHA1_H_
#define _OSGSHA1_H_
#ifdef __sgi
#pragma once
#endif

#include <cstdint>
#include <string>
#include <istream>

#include "OSGBaseDef.h"

// Based on https://github.com/vog/sha1
/*
    Original authors:
        Steve Reid (Original C Code)
        Bruce Guenter (Small changes to fit into bglibs)
        Volker Grabsch (Translation to simpler C++ Code)
        Eugene Hopkinson (Safety improvements)
        Vincent Falco (beast adaptation)
*/

OSG_BEGIN_NAMESPACE

class OSG_BASE_DLLMAPPING Sha1
{
public:
    static const std::size_t BLOCK_INTS   = 16;
    static const std::size_t BLOCK_BYTES  = 64;
    static const std::size_t DIGEST_BYTES = 20;

public:
            Sha1();

    void        reset               ();

    void        update              (void const* message, std::size_t size);
    void        finish              (void* digest);
    std::string finish              ();
    std::string finish_hex          ();

    std::string get_from_string     (std::string const& message);
    std::string get_from_string_hex (std::string const& message);

    std::string get_from_file       (std::string const& filename);
    std::string get_from_file_hex   (std::string const& filename);

    std::string get_from_stream     (std::istream& is);
    std::string get_from_stream_hex (std::istream& is);

    bool        check               (std::string const& message, std::string const& answer);
    
    std::string unhex               (std::string const& in);
    std::string hex                 (std::string const& in);

private:
    std::uint8_t    unhex   (char c);
    char            hex     (std::uint8_t v);

private:
    std::size_t   _buflen;
    std::size_t   _blocks;
    std::uint32_t _digest[5];
    std::uint8_t  _buf[BLOCK_BYTES];
};

OSG_END_NAMESPACE

#include "OSGSha1.inl"

#endif // _OSGSHA1_H_
