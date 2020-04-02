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

#ifndef _OSGBASEHASH_H_
#define _OSGBASEHASH_H_
#ifdef __sgi
#pragma once
#endif

#include <cstdint>
#include <string>
#include <istream>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"

struct XXH32_state_s;
struct XXH64_state_s;

OSG_BEGIN_NAMESPACE

//
// The implementation is based on the xxHash hashing library:
//      https://github.com/Cyan4973/xxHash
//
// "xxHash is an Extremely fast Hash algorithm, running at RAM speed limits. 
// It successfully completes the SMHasher test suite which evaluates collision, 
// dispersion and randomness qualities of hash functions. Code is highly portable, 
// and hashes are identical on all platforms (little / big endian).
//

class OSG_BASE_DLLMAPPING Hash32
{
public:
    static UInt32 hash              (const void*        input, std::size_t length,  UInt32 seed = 0);
    static UInt32 hash_from_string  (const std::string& message,                    UInt32 seed = 0);
    static UInt32 hash_from_file    (const char*        file,                       UInt32 seed = 0);
    static UInt32 hash_from_stream  (std::istream&      is,                         UInt32 seed = 0);

    static std::string  to_hex_string   (UInt32 value, bool showbase = false);
    static UInt32       from_hex_string (const std::string& str);

public:
            Hash32(UInt32 seed = 0);
           ~Hash32();

    void        reset               (UInt32 seed = 0);

    template <class T>
    void        update              (T value);
    void        update              (void const* message, std::size_t size);
    void        update_from_string  (const std::string& message);
    void        update_from_file    (const char* filename);
    void        update_from_stream  (std::istream& is);

    UInt32      finish              ();

private:
    XXH32_state_s* _state;
};

class OSG_BASE_DLLMAPPING Hash64
{
public:
    static UInt64 hash              (const void*        input, std::size_t length,  UInt64 seed = 0L);
    static UInt64 hash_from_string  (const std::string& message,                    UInt64 seed = 0L);
    static UInt64 hash_from_file    (const char*        file,                       UInt64 seed = 0L);
    static UInt64 hash_from_stream  (std::istream&      is,                         UInt64 seed = 0L);

    static std::string  to_hex_string   (UInt64 value, bool showbase = false);
    static UInt64       from_hex_string (const std::string& str);

public:
            Hash64(UInt64 seed = 0L);
           ~Hash64();

    void        reset               (UInt64 seed = 0);

    template <class T>
    void        update              (T value);
    void        update              (void const* message, std::size_t size);
    void        update_from_string  (const std::string& message);
    void        update_from_file    (const char* filename);
    void        update_from_stream  (std::istream& is);

    UInt64      finish              ();

private:
    XXH64_state_s* _state;
};

OSG_END_NAMESPACE

#include "OSGBaseHash.inl"

#endif // _OSGBASEHASH_H_
