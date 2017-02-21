//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

///
/// @file bfstring.h
///

#ifndef BFSTRING_H
#define BFSTRING_H

#include <string>
#include <sstream>
#include <iomanip>
#include <type_traits>

/// std::string literal
///
/// @param str string to convert to std::string
/// @param len len of str
/// @return std::string(str, len)
///
inline auto operator""_s(const char *str, std::size_t len)
{
    return std::string(str, len);
}

namespace bfn
{
/// Convert to String (with base)
///
/// Same thing as std::to_string, but adds the ability to state the base for
/// conversion.
///
/// @param val the value to convert
/// @param base the base for conversion.
/// @return string version of val converted to the provided base
///
template<class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
std::string
to_string(const T val, const int base)
{
    std::stringstream stream;

    switch (base) {
        case 8:
            stream << "0";
            break;

        case 16:
            stream << "0x";
            break;

        default:
            break;
    };

    stream << std::setbase(base) << std::uppercase << val;
    return stream.str();
}
}

#endif
