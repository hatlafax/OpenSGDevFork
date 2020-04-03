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

#include <boost/algorithm/string/case_conv.hpp>

#include "OSGConfig.h"
#include "OSGSHA1.h"

OSG_BEGIN_NAMESPACE

namespace detail {

inline
std::uint32_t rol(
    std::uint32_t value,
    std::size_t   bits)
{
    return (value << bits) | (value >> (32 - bits));
}

inline
std::uint32_t blk(
    std::uint32_t block[Sha1::BLOCK_INTS], 
    std::size_t   i)
{
    return rol(
        block[(i+13)&15] ^ block[(i+8)&15] ^
        block[(i+2) &15] ^ block[i], 1);
}

inline
void R0(
    std::uint32_t  block[Sha1::BLOCK_INTS], 
    std::uint32_t  v,
    std::uint32_t& w, 
    std::uint32_t  x, 
    std::uint32_t  y,
    std::uint32_t& z, 
    std::size_t    i)
{
    z += ((w&(x^y))^y) + block[i] + 0x5a827999 + rol(v, 5);
    w = rol(w, 30);
}


inline
void R1(
    std::uint32_t  block[Sha1::BLOCK_INTS],
    std::uint32_t  v,
    std::uint32_t& w,
    std::uint32_t  x,
    std::uint32_t  y,
    std::uint32_t& z,
    std::size_t    i)
{
    block[i] = blk(block, i);
    z += ((w&(x^y))^y) + block[i] + 0x5a827999 + rol(v, 5);
    w = rol(w, 30);
}

inline
void R2(
    std::uint32_t  block[Sha1::BLOCK_INTS],
    std::uint32_t  v,
    std::uint32_t& w,
    std::uint32_t  x,
    std::uint32_t  y,
    std::uint32_t& z,
    std::size_t    i)
{
    block[i] = blk(block, i);
    z += (w^x^y) + block[i] + 0x6ed9eba1 + rol(v, 5);
    w = rol(w, 30);
}

inline
void R3(
    std::uint32_t  block[Sha1::BLOCK_INTS],
    std::uint32_t  v,
    std::uint32_t& w,
    std::uint32_t  x,
    std::uint32_t  y,
    std::uint32_t& z,
    std::size_t    i)
{
    block[i] = blk(block, i);
    z += (((w|x)&y)|(w&x)) + block[i] + 0x8f1bbcdc + rol(v, 5);
    w = rol(w, 30);
}

inline
void R4(
    std::uint32_t  block[Sha1::BLOCK_INTS],
    std::uint32_t  v,
    std::uint32_t& w,
    std::uint32_t  x,
    std::uint32_t  y,
    std::uint32_t& z,
    std::size_t    i)
{
    block[i] = blk(block, i);
    z += (w^x^y) + block[i] + 0xca62c1d6 + rol(v, 5);
    w = rol(w, 30);
}

inline
void make_block(
    std::uint8_t const* p,
    std::uint32_t       block[Sha1::BLOCK_INTS])
{
    for(std::size_t i = 0; i < Sha1::BLOCK_INTS; i++)
        block[i] =
            (static_cast<std::uint32_t>(p[4*i+3]))     |
            (static_cast<std::uint32_t>(p[4*i+2]))<< 8 |
            (static_cast<std::uint32_t>(p[4*i+1]))<<16 |
            (static_cast<std::uint32_t>(p[4*i+0]))<<24;
}

void transform(
    std::uint32_t digest[], 
    std::uint32_t block[Sha1::BLOCK_INTS])
{
    std::uint32_t a = digest[0];
    std::uint32_t b = digest[1];
    std::uint32_t c = digest[2];
    std::uint32_t d = digest[3];
    std::uint32_t e = digest[4];

    R0(block, a, b, c, d, e,  0);
    R0(block, e, a, b, c, d,  1);
    R0(block, d, e, a, b, c,  2);
    R0(block, c, d, e, a, b,  3);
    R0(block, b, c, d, e, a,  4);
    R0(block, a, b, c, d, e,  5);
    R0(block, e, a, b, c, d,  6);
    R0(block, d, e, a, b, c,  7);
    R0(block, c, d, e, a, b,  8);
    R0(block, b, c, d, e, a,  9);
    R0(block, a, b, c, d, e, 10);
    R0(block, e, a, b, c, d, 11);
    R0(block, d, e, a, b, c, 12);
    R0(block, c, d, e, a, b, 13);
    R0(block, b, c, d, e, a, 14);
    R0(block, a, b, c, d, e, 15);
    R1(block, e, a, b, c, d,  0);
    R1(block, d, e, a, b, c,  1);
    R1(block, c, d, e, a, b,  2);
    R1(block, b, c, d, e, a,  3);
    R2(block, a, b, c, d, e,  4);
    R2(block, e, a, b, c, d,  5);
    R2(block, d, e, a, b, c,  6);
    R2(block, c, d, e, a, b,  7);
    R2(block, b, c, d, e, a,  8);
    R2(block, a, b, c, d, e,  9);
    R2(block, e, a, b, c, d, 10);
    R2(block, d, e, a, b, c, 11);
    R2(block, c, d, e, a, b, 12);
    R2(block, b, c, d, e, a, 13);
    R2(block, a, b, c, d, e, 14);
    R2(block, e, a, b, c, d, 15);
    R2(block, d, e, a, b, c,  0);
    R2(block, c, d, e, a, b,  1);
    R2(block, b, c, d, e, a,  2);
    R2(block, a, b, c, d, e,  3);
    R2(block, e, a, b, c, d,  4);
    R2(block, d, e, a, b, c,  5);
    R2(block, c, d, e, a, b,  6);
    R2(block, b, c, d, e, a,  7);
    R3(block, a, b, c, d, e,  8);
    R3(block, e, a, b, c, d,  9);
    R3(block, d, e, a, b, c, 10);
    R3(block, c, d, e, a, b, 11);
    R3(block, b, c, d, e, a, 12);
    R3(block, a, b, c, d, e, 13);
    R3(block, e, a, b, c, d, 14);
    R3(block, d, e, a, b, c, 15);
    R3(block, c, d, e, a, b,  0);
    R3(block, b, c, d, e, a,  1);
    R3(block, a, b, c, d, e,  2);
    R3(block, e, a, b, c, d,  3);
    R3(block, d, e, a, b, c,  4);
    R3(block, c, d, e, a, b,  5);
    R3(block, b, c, d, e, a,  6);
    R3(block, a, b, c, d, e,  7);
    R3(block, e, a, b, c, d,  8);
    R3(block, d, e, a, b, c,  9);
    R3(block, c, d, e, a, b, 10);
    R3(block, b, c, d, e, a, 11);
    R4(block, a, b, c, d, e, 12);
    R4(block, e, a, b, c, d, 13);
    R4(block, d, e, a, b, c, 14);
    R4(block, c, d, e, a, b, 15);
    R4(block, b, c, d, e, a,  0);
    R4(block, a, b, c, d, e,  1);
    R4(block, e, a, b, c, d,  2);
    R4(block, d, e, a, b, c,  3);
    R4(block, c, d, e, a, b,  4);
    R4(block, b, c, d, e, a,  5);
    R4(block, a, b, c, d, e,  6);
    R4(block, e, a, b, c, d,  7);
    R4(block, d, e, a, b, c,  8);
    R4(block, c, d, e, a, b,  9);
    R4(block, b, c, d, e, a, 10);
    R4(block, a, b, c, d, e, 11);
    R4(block, e, a, b, c, d, 12);
    R4(block, d, e, a, b, c, 13);
    R4(block, c, d, e, a, b, 14);
    R4(block, b, c, d, e, a, 15);

    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;
}

} // namespace SHA1

Sha1::Sha1()
{
    reset();
}

void Sha1::reset()
{
    _buflen    = 0;
    _blocks    = 0;
    _digest[0] = 0x67452301;
    _digest[1] = 0xefcdab89;
    _digest[2] = 0x98badcfe;
    _digest[3] = 0x10325476;
    _digest[4] = 0xc3d2e1f0;
}

void Sha1::update(
    void const* message, 
    std::size_t size)
{
    auto p = reinterpret_cast<std::uint8_t const*>(message);
    for(;;)
    {
        auto const n = (std::min)(size, sizeof(_buf) - _buflen);
        std::memcpy(_buf + _buflen, p, n);
        _buflen += n;
        if(_buflen != 64)
            return;
        p += n;
        size -= n;
        _buflen = 0;
        std::uint32_t block[BLOCK_INTS];
        detail::make_block(_buf, block);
        detail::transform(_digest, block);
        ++_blocks;
    }
}

void Sha1::finish(void* digest)
{
    std::uint64_t total_bits = (_blocks*64 + _buflen) * 8;
    // pad
    _buf[_buflen++] = 0x80;
    auto const buflen = _buflen;
    while(_buflen < BLOCK_BYTES)
        _buf[_buflen++] = 0x00;
    std::uint32_t block[BLOCK_INTS];
    detail::make_block(_buf, block);
    if(buflen > BLOCK_BYTES - 8)
    {
        detail::transform(_digest, block);
        for(size_t i = 0; i < BLOCK_INTS - 2; i++)
            block[i] = 0;
    }

    /* Append total_bits, split this uint64_t into two uint32_t */
    block[BLOCK_INTS - 1] = total_bits & 0xffffffff;
    block[BLOCK_INTS - 2] = (total_bits >> 32);
    detail::transform(_digest, block);
    for(std::size_t i = 0; i < DIGEST_BYTES/4; i++)
    {
        std::uint8_t* d =
            reinterpret_cast<std::uint8_t*>(digest) + 4 * i;
        d[3] =  _digest[i]        & 0xff;
        d[2] = (_digest[i] >>  8) & 0xff;
        d[1] = (_digest[i] >> 16) & 0xff;
        d[0] = (_digest[i] >> 24) & 0xff;
    }
}

bool Sha1::check(std::string const& message, std::string const& answer)
{
    std::string digest;
    digest = unhex(answer);

    reset();
    update(message.data(), message.size());

    std::string result;
    result.resize(DIGEST_BYTES);
    finish(&result[0]);

    std::string verbose;
    verbose = hex(result);

    return (result == digest) && (verbose == boost::to_lower_copy(answer));
}

std::string Sha1::get_from_stream(std::istream& is)
{
    std::string result;

    if (is.good())
    {
        reset();

        const int BUFFER_SIZE = 1024;
        std::vector<char> buffer(BUFFER_SIZE + 1, 0);

        while(true)
        {
            is.read(buffer.data(), BUFFER_SIZE);
            std::streamsize s = ((is) ? BUFFER_SIZE : is.gcount());

            buffer[s] = 0;

            update(&buffer[0], s);

            if(!is) break;
        }

        result.resize(DIGEST_BYTES);
        finish(&result[0]);
    }

    return result;
}

OSG_END_NAMESPACE