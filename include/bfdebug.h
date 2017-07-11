/*
 * Bareflank Hypervisor
 *
 * Copyright (C) 2015 Assured Information Security, Inc.
 * Author: Rian Quinn        <quinnr@ainfosec.com>
 * Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file bfdebug.h
 */

#ifndef BFDEBUG_H
#define BFDEBUG_H

#include <bfconstants.h>

/* -------------------------------------------------------------------------- */
/* C++ Debugging                                                              */
/* -------------------------------------------------------------------------- */

#ifdef __cplusplus

#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

/* @cond */

#define bfcolor_black "\033[1;30m"
#define bfcolor_red "\033[1;31m"
#define bfcolor_green "\033[1;32m"
#define bfcolor_yellow "\033[1;33m"
#define bfcolor_blue "\033[1;34m"
#define bfcolor_magenta "\033[1;35m"
#define bfcolor_cyan "\033[1;36m"
#define bfcolor_end "\033[0m"

#define bfcolor_debug bfcolor_green
#define bfcolor_warning bfcolor_yellow
#define bfcolor_error bfcolor_red

/* @endcond */

/**
 * Current Function Macro
 *
 * Clang Tidy does not like the built in macros that return character pointers
 * as they claim it breaks the Core Guidelines which is obnoxious, so this
 * macro redefines how this is done.
 */
#ifdef UNIX
#define __BFFUNC__ static_cast<const char *>(__PRETTY_FUNCTION__)
#else
#define __BFFUNC__ static_cast<const char *>(__FUNCTION__)
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4312)
#endif

/**
 * View As Pointer
 *
 * This is really just a wrapper around reinterpret_cast to provide a simple
 * means to convert a pointer or integer to a void * so that it prints as
 * hex based pointer. Since this only provides a read, it's safe as well.
 *
 * @param val a pointer or integer to convert to void * for printing
 * @return void * version of val
 */
template <
    typename T,
    typename = std::enable_if_t <
        std::is_pointer<T>::value ||
        std::is_integral<T>::value
        >
    >
const void *
view_as_pointer(const T val)
{ return reinterpret_cast<const void *>(val); }

#ifdef _MSC_VER
#pragma warning(pop)
#endif

/**
 * Output To Core
 *
 * All std::cout and std::cerr are sent to a specific debug_ring
 * based on the vcpuid that you provide, instead of being
 * sent to vcpuid=invalid and serial.
 *
 * @param vcpuid the vcpu to send the output to
 * @param func a lambda function containing the output to redirect
 */
template<
    typename V,
    typename T
    >
void
output_to_vcpu(V vcpuid, T func)
{
    auto flags = std::cout.flags();
    std::cout << "$vcpuid=" << std::setw(18) << std::hex << std::showbase << vcpuid;
    std::cout.flags(flags);

    try {
        func();
    }
    catch (std::exception &e) {
        std::cout << '\n';
        throw;
    }
}

/**
 * Newline macro
 */
#ifndef bfendl
#define bfendl '\n'
#endif

/**
 * This macro is a shortcut for std::cout that adds some text and color.
 * Use it like std::cout
 *
 * @code
 * bfdebug << "hello world" << bfend;
 * @endcode
 */
#ifndef bfdebug
#define bfdebug std::cout << bfcolor_debug << "DEBUG" << bfcolor_end << ": "
#endif

/**
 * This macro is a shortcut for std::cout that adds some text and color.
 * Use it like std::cout
 *
 * @code
 * bfwarning << "hello world" << bfend;
 * @endcode
 */
#ifndef bfwarning
#define bfwarning std::cout << bfcolor_warning << "WARNING" << bfcolor_end << ": "
#endif

/**
 * This macro is a shortcut for std::cout that adds some text and color.
 * Use it like std::cout
 *
 * @code
 * bferror << "hello world" << bfend;
 * @endcode
 */
#ifndef bferror
#define bferror std::cout << bfcolor_error << "ERROR" << bfcolor_end << ": "
#endif

/**
 * Print Line Number
 *
 * @note: this should only be used temporarily for debugging. Do not check code
 *     with this macro into the main repo.
 *
 * @code
 * bfline
 * @endcode
 */
#define bfline bfdebug                                                                             \
    << bfcolor_blue << __BFFUNC__<< " ["                                                           \
    << bfcolor_yellow << __LINE__                                                                  \
    << bfcolor_blue "]" << bfcolor_end << bfendl;

/**
 * Print Field Value
 *
 * @note: this should only be used temporarily for debugging. Do not check code
 *     with this macro into the main repo.
 *
 * @code
 * int num = 10;
 * bffield(num)
 * @endcode
 */
#define bffield(a) bfdebug                                                                         \
    << bfcolor_blue << __BFFUNC__                                                                  \
    << bfcolor_yellow << " " << #a                                                                 \
    << bfcolor_blue << ": "                                                                        \
    << bfcolor_magenta << (a) << bfcolor_end << bfendl;

/**
 * Print Header
 *
 * @code
 * bfdebug_header(0, "description")
 * @endcode
 */
#define bfdebug_header(a,b)                                                                        \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bfdebug << std::string(b) << ": " << bfendl;                                               \
    }

/**
 * Print Header
 *
 * @code
 * bferror_header(0, "description")
 * @endcode
 */
#define bferror_header(a,b)                                                                        \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bferror << std::string(b) << ": " << bfendl;                                               \
    }

/**
 * Print New Line
 *
 * @code
 * bfdebug_brline(0)
 * @endcode
 */
#define bfdebug_brline(a) if ((a) <= DEBUG_LEVEL) bfdebug                                          \
    << bfendl;

/**
 * Print New Line
 *
 * @code
 * bferror_brline(0)
 * @endcode
 */
#define bferror_brline(a) if ((a) <= DEBUG_LEVEL) bferror                                          \
    << bfendl;

/**
 * Print Line Break (level 1)
 *
 * @code
 * bfdebug_break(0)
 * @endcode
 */
#define bfdebug_break1(a) if ((a) <= DEBUG_LEVEL) bfdebug                                          \
    << "======================================================================\n";

/**
 * Print Line Break (level 2)
 *
 * @code
 * bfdebug_break(0)
 * @endcode
 */
#define bfdebug_break2(a) if ((a) <= DEBUG_LEVEL) bfdebug                                          \
    << "----------------------------------------------------------------------\n";

/**
 * Print Line Break (level 3)
 *
 * @code
 * bfdebug_break(0)
 * @endcode
 */
#define bfdebug_break3(a) if ((a) <= DEBUG_LEVEL) bfdebug                                          \
    << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";

/**
 * Print Line Break (level 1)
 *
 * @code
 * bferror_break(0)
 * @endcode
 */
#define bferror_break1(a) if ((a) <= DEBUG_LEVEL) bferror                                          \
    << "======================================================================\n";

/**
 * Print Line Break (level 2)
 *
 * @code
 * bferror_break(0)
 * @endcode
 */
#define bferror_break2(a) if ((a) <= DEBUG_LEVEL) bferror                                          \
    << "----------------------------------------------------------------------\n";

/**
 * Print Line Break (level 3)
 *
 * @code
 * bferror_break(0)
 * @endcode
 */
#define bferror_break3(a) if ((a) <= DEBUG_LEVEL) bferror                                          \
    << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";

/**
 * Print Number Base 16
 *
 * @code
 * bfdebug_nhex(0, "description", 42)
 * @endcode
 */
#define bfdebug_nhex(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill('0') << std::internal << view_as_pointer(c);    \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Base 16 (Subfield)
 *
 * @code
 * bfdebug_subnhex(0, "description", 42)
 * @endcode
 */
#define bfdebug_subnhex(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill('0') << std::internal << view_as_pointer(c);    \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Based 10
 *
 * @code
 * bfdebug_ndec(0, "description", 42)
 * @endcode
 */
#define bfdebug_ndec(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::internal << std::dec << (c);       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Based 10 (Subfield)
 *
 * @code
 * bfdebug_subndec(0, "description", 42)
 * @endcode
 */
#define bfdebug_subndec(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::internal << std::dec << (c);       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Bool
 *
 * @code
 * bfdebug_bool(0, "description", true)
 * @endcode
 */
#define bfdebug_bool(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::right << #c;                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Bool (Subfield)
 *
 * @code
 * bfdebug_subbool(0, "description", true)
 * @endcode
 */
#define bfdebug_subbool(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::right << #c;                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print String
 *
 * @code
 * bfdebug_text(0, "description", "value")
 * @endcode
 */
#define bfdebug_text(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(40) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(30) << std::setfill(' ') << std::right << std::string(c);           \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print String (Subfield)
 *
 * @code
 * bfdebug_subtext(0, "description", "value")
 * @endcode
 */
#define bfdebug_subtext(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(36) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(30) << std::setfill(' ') << std::right << std::string(c);           \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Info
 *
 * @code
 * bfdebug_info(0, "description")
 * @endcode
 */
#define bfdebug_info(a,b)                                                                          \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bfdebug << std::string(b) << bfendl;                                                       \
    }

/**
 * Print Info (Subfield)
 *
 * @code
 * bfdebug_subinfo(0, "description")
 * @endcode
 */
#define bfdebug_subinfo(a,b)                                                                       \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bfdebug << "  - " << std::string(b) << bfendl;                                             \
    }

/**
 * Print Number Base 16
 *
 * @code
 * bferror_nhex(0, "description", 42)
 * @endcode
 */
#define bferror_nhex(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill('0') << std::internal << view_as_pointer(c);    \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Base 16 (Subfield)
 *
 * @code
 * bferror_subnhex(0, "description", 42)
 * @endcode
 */
#define bferror_subnhex(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill('0') << std::internal << view_as_pointer(c);    \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Based 10
 *
 * @code
 * bferror_ndec(0, "description", 42)
 * @endcode
 */
#define bferror_ndec(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::internal << std::dec << (c);       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Number Based 10 (Subfield)
 *
 * @code
 * bferror_subndec(0, "description", 42)
 * @endcode
 */
#define bferror_subndec(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::internal << std::dec << (c);       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Bool
 *
 * @code
 * bferror_bool(0, "description", true)
 * @endcode
 */
#define bferror_bool(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << std::setw(52) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::right << #c;                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Bool (Subfield)
 *
 * @code
 * bferror_subbool(0, "description", true)
 * @endcode
 */
#define bferror_subbool(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(48) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(18) << std::setfill(' ') << std::right << #c;                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print String
 *
 * @code
 * bferror_text(0, "description", "value")
 * @endcode
 */
#define bferror_text(a,b,c)                                                                        \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << std::setw(40) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(30) << std::setfill(' ') << std::right << std::string(c);           \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print String (Subfield)
 *
 * @code
 * bferror_subtext(0, "description", "value")
 * @endcode
 */
#define bferror_subtext(a,b,c)                                                                     \
    if ((a) <= DEBUG_LEVEL) { bferror;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(36) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << std::setw(30) << std::setfill(' ') << std::right << std::string(c);           \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Info
 *
 * @code
 * bferror_info(0, "description")
 * @endcode
 */
#define bferror_info(a,b)                                                                          \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bferror << std::string(b) << bfendl;                                                       \
    }

/**
 * Print Info (Subfield)
 *
 * @code
 * bferror_subinfo(0, "description")
 * @endcode
 */
#define bferror_subinfo(a,b)                                                                       \
    if ((a) <= DEBUG_LEVEL) {                                                                      \
        bferror << "  - " << std::string(b) << bfendl;                                             \
    }

/**
 * Print Pass
 *
 * @code
 * bfdebug_pass(0, "description")
 * @endcode
 */
#define bfdebug_pass(a,b)                                                                          \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(66) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << bfcolor_green << "pass" << bfcolor_end;                                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Pass (Subfield)
 *
 * @code
 * bfdebug_subpass(0, "description")
 * @endcode
 */
#define bfdebug_subpass(a,b)                                                                       \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(62) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << bfcolor_green << "pass" << bfcolor_end;                                       \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Fail
 *
 * @code
 * bfdebug_fail(0, "description")
 * @endcode
 */
#define bfdebug_fail(a,b)                                                                          \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << std::setw(66) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << bfcolor_red << "fail <----" << bfcolor_end;                                   \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Fail (Subfield)
 *
 * @code
 * bfdebug_subfail(0, "description")
 * @endcode
 */
#define bfdebug_subfail(a,b)                                                                       \
    if ((a) <= DEBUG_LEVEL) { bfdebug;                                                             \
        std::cout << "  - ";                                                                       \
        std::cout << std::setw(62) << std::setfill(' ') << std::left << std::string(b);            \
        std::cout << bfcolor_red << "fail <----" << bfcolor_end;                                   \
        std::cout << bfendl;                                                                       \
    }

/**
 * Print Pass / Fail
 *
 * @code
 * bfdebug_test(0, "description", true)
 * @endcode
 */
#define bfdebug_test(a,b,c)                                                                        \
    if ((c)) { bfdebug_pass(a,b); } else { bfdebug_fail(a,b); }

/**
 * Print Pass / Fail (Subfield)
 *
 * @code
 * bfdebug_subtest(0, "description", true)
 * @endcode
 */
#define bfdebug_subtest(a,b,c)                                                                     \
    if ((c)) { bfdebug_subpass(a,b); } else { bfdebug_subfail(a,b); }

#endif

/**
 * \def BFDEBUG
 *
 * This macro is a shortcut for printf that adds some text.
 * Use like printf
 */

/**
 * \def BFALERT
 *
 * This macro is a shortcut for printf that adds some text.
 * Use like printf
 */

/* -------------------------------------------------------------------------- */
/* C Debugging                                                                */
/* -------------------------------------------------------------------------- */

#ifndef KERNEL
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif
#define BFDEBUG(...) printf("[BAREFLANK DEBUG]: " __VA_ARGS__)
#define BFALERT(...) printf("[BAREFLANK ERROR]: " __VA_ARGS__)
#endif

/* -------------------------------------------------------------------------- */
/* Linux Debugging                                                            */
/* -------------------------------------------------------------------------- */

#ifdef KERNEL
#if defined(__linux__)
#include <linux/module.h>
#define BFDEBUG(...) printk(KERN_INFO "[BAREFLANK DEBUG]: " __VA_ARGS__)
#define BFALERT(...) printk(KERN_ALERT "[BAREFLANK ERROR]: " __VA_ARGS__)
#endif
#endif

/* -------------------------------------------------------------------------- */
/* Windows Debugging                                                          */
/* -------------------------------------------------------------------------- */

#ifdef KERNEL
#ifdef _WIN32
#include <wdm.h>
#define BFDEBUG(...)                                                                               \
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[BAREFLANK DEBUG]: " __VA_ARGS__)
#define BFALERT(...)                                                                               \
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[BAREFLANK ERROR]: " __VA_ARGS__)
#endif
#endif

#endif
