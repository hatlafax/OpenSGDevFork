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

#include <algorithm>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

// https://github.com/Cyan4973/xxHash
#define XXH_INLINE_ALL
#define XXH_ACCEPT_NULL_INPUT_POINTER   1

#include "xxHash/xxhash.h"

#include "OSGConfig.h"
#include "OSGBaseHash.h"

OSG_BEGIN_NAMESPACE

/*---- Hash32 ---------------------------------------------------------------*/

UInt32 Hash32::hash(const void* input, std::size_t length, UInt32 seed)
{
    return XXH32(input, length, seed);
}

UInt32 Hash32::hash_from_string(const std::string& message, UInt32 seed)
{
    return XXH32(&message[0], message.size(), seed);
}

UInt32 Hash32::hash_from_file(const char* file, UInt32 seed)
{
    std::ifstream ifs (file, std::ifstream::binary);
    ifs.unsetf(std::ios::skipws);

    std::streampos fileSize;
    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    ifs.read((char*)&vecBytes[0], fileSize);

    return XXH32(&vecBytes[0], fileSize, seed);
}

UInt32 Hash32::hash_from_stream(std::istream& is, UInt32 seed)
{
    std::streampos fileSize;
    is.seekg(0, std::ios::end);
    fileSize = is.tellg();
    is.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    is.read((char*)&vecBytes[0], fileSize);

    return XXH32(&vecBytes[0], fileSize, seed);
}

std::string Hash32::to_hex_string(UInt32 value, bool showbase)
{
    std::stringstream stream;
    if (showbase)
        stream << std::showbase 
               << std::setfill ('0') << std::setw(sizeof(UInt32)*2)
               << std::hex 
               << value;
    else
        stream << std::hex 
               << std::setfill ('0') << std::setw(sizeof(UInt32)*2)
               << value;
    return stream.str();
}

UInt32 Hash32::from_hex_string(const std::string& str)
{
    UInt32 value = 0;
    std::stringstream is(str);
    is >> std::hex >> value;
    return value;
}

Hash32::Hash32(UInt32 seed)
: _state(XXH32_createState())
{
    XXH32_reset(_state, seed);
}

Hash32::~Hash32()
{
    XXH32_freeState(_state);
    _state = NULL;
}

void Hash32::reset(UInt32 seed)
{
    XXH32_reset(_state, seed);
}

void Hash32::update(void const* message, std::size_t size)
{
    XXH32_update(_state, message, size);
}

void Hash32::update_from_string(const std::string& message)
{
    XXH32_update(_state, &message[0], message.size());
}

void Hash32::update_from_file(const char* filename)
{
    std::ifstream ifs (filename, std::ifstream::binary);
    ifs.unsetf(std::ios::skipws);

    std::streampos fileSize;
    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    ifs.read((char*)&vecBytes[0], fileSize);

    XXH32_update(_state, &vecBytes[0], fileSize);
}

void Hash32::update_from_stream(std::istream& is)
{
    if (is.good())
    {
        const int BUFFER_SIZE = 1024;
        std::vector<char> buffer(BUFFER_SIZE + 1, 0);

        while(true)
        {
            is.read(buffer.data(), BUFFER_SIZE);
            std::streamsize s = ((is) ? BUFFER_SIZE : is.gcount());

            buffer[s] = 0;

            XXH32_update(_state, &buffer[0], s);

            if(!is) break;
        }
    }
}

UInt32 Hash32::finish()
{
    return XXH32_digest(_state);
}

/*---- Hash64 ---------------------------------------------------------------*/

UInt64 Hash64::hash(const void* input, std::size_t length, UInt64 seed)
{
    return XXH64(input, length, seed);
}

UInt64 Hash64::hash_from_string(const std::string& message, UInt64 seed)
{
    return XXH64(&message[0], message.size(), seed);
}

UInt64 Hash64::hash_from_file(const char* file, UInt64 seed)
{
    std::ifstream ifs (file, std::ifstream::binary);
    ifs.unsetf(std::ios::skipws);

    std::streampos fileSize;
    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    ifs.read((char*)&vecBytes[0], fileSize);

    return XXH64(&vecBytes[0], fileSize, seed);
}

UInt64 Hash64::hash_from_stream(std::istream& is, UInt64 seed)
{
    std::streampos fileSize;
    is.seekg(0, std::ios::end);
    fileSize = is.tellg();
    is.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    is.read((char*)&vecBytes[0], fileSize);

    return XXH64(&vecBytes[0], fileSize, seed);
}

std::string Hash64::to_hex_string(UInt64 value, bool showbase)
{
    std::stringstream stream;
    if (showbase)
        stream << std::showbase 
               << std::setfill ('0') << std::setw(sizeof(UInt64)*2)
               << std::hex 
               << value;
    else
        stream << std::hex 
               << std::setfill ('0') << std::setw(sizeof(UInt64)*2)
               << value;
    return stream.str();
}

UInt64 Hash64::from_hex_string(const std::string& str)
{
    UInt64 value = 0;
    std::stringstream is(str);
    is >> std::hex >> value;
    return value;
}

Hash64::Hash64(UInt64 seed)
: _state(XXH64_createState())
{
    XXH64_reset(_state, seed);
}

Hash64::~Hash64()
{
    XXH64_freeState(_state);
    _state = NULL;
}

void Hash64::reset(UInt64 seed)
{
    XXH64_reset(_state, seed);
}

void Hash64::update(void const* message, std::size_t size)
{
    XXH64_update(_state, message, size);
}

void Hash64::update_from_string(const std::string& message)
{
    XXH64_update(_state, &message[0], message.size());
}

void Hash64::update_from_file(const char* filename)
{
    std::ifstream ifs (filename, std::ifstream::binary);
    ifs.unsetf(std::ios::skipws);

    std::streampos fileSize;
    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<BYTE> vecBytes(fileSize);
    ifs.read((char*)&vecBytes[0], fileSize);

    XXH64_update(_state, &vecBytes[0], fileSize);
}

void Hash64::update_from_stream(std::istream& is)
{
    if (is.good())
    {
        const int BUFFER_SIZE = 1024;
        std::vector<char> buffer(BUFFER_SIZE + 1, 0);

        while(true)
        {
            is.read(buffer.data(), BUFFER_SIZE);
            std::streamsize s = ((is) ? BUFFER_SIZE : is.gcount());

            buffer[s] = 0;

            XXH64_update(_state, &buffer[0], s);

            if(!is) break;
        }
    }
}

UInt64 Hash64::finish()
{
    return XXH64_digest(_state);
}

OSG_END_NAMESPACE