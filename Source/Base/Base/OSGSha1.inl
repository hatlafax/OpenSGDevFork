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

OSG_BEGIN_NAMESPACE

inline
char Sha1::hex(std::uint8_t v)
{
    if (v < 10) return v + '0';
    if (v < 16) return v + 'a' - 10;
    throw std::invalid_argument("not a hex digit");
}

inline
std::uint8_t Sha1::unhex(char c)
{
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'a' && c <= 'f') return c - 'a' + 10;
    if(c >= 'A' && c <= 'F') return c - 'A' + 10;
    throw std::invalid_argument("not a hex digit");
}

inline
std::string Sha1::unhex(std::string const& in)
{
    std::string out;
    out.reserve(in.size() / 2);
    if(in.size() % 2)
        throw std::domain_error("invalid hex string");

    for(std::size_t i = 0; i < in.size(); i += 2)
        out.push_back( (unhex(in[i])<<4) + unhex(in[i+1]));

    return out;
}

inline
std::string Sha1::hex(std::string const& in)
{
    std::string out;
    out.reserve(in.size() * 2);

    for(std::size_t i = 0; i < in.size(); i++)
    {
        std::uint8_t v = in[i];
        out.push_back( hex(v >> 4) );
        out.push_back( hex(v & 0xF) );
    }
    return out;
}

inline
std::string Sha1::finish()
{
    std::string result;
    result.resize(DIGEST_BYTES);
    finish(&result[0]);
    return result;
}

inline
std::string Sha1::finish_hex()
{
    std::string result;
    result.resize(DIGEST_BYTES);
    finish(&result[0]);

    return hex(result);
}

inline
std::string Sha1::get_from_string(std::string const& message)
{
    reset();
    update(message.data(), message.size());
    return finish();
}

inline
std::string Sha1::get_from_string_hex(std::string const& message)
{
    reset();
    update(message.data(), message.size());
    return finish_hex();
}

inline
std::string Sha1::get_from_file(std::string const& filename)
{
    std::ifstream is(filename.c_str(), std::ios::binary);
    return get_from_stream(is);
}

inline
std::string Sha1::get_from_file_hex(std::string const& filename)
{
    std::ifstream is(filename.c_str(), std::ios::binary);
    return get_from_stream_hex(is);
}

inline
std::string Sha1::get_from_stream_hex(std::istream& is)
{
    return hex(get_from_stream(is));
}

OSG_END_NAMESPACE