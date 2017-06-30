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
{
    return reinterpret_cast<const void *>(val);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

/**
 * Output To Core
 *
 * All std::cout and std::cerr are sent to a specific debug_ring
 * based on the vcpuid that you provide, instead of being
 * sent to vcpuid=0 and serial.
 *
 * @param vcpuid the vcpu to send the output to
 * @param func a lambda function containing the output to redirect
 */
template<class V, class T>
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
 * This macro is a shortcut for std::cerr that adds some text and color.
 * Use it like std::cerr
 *
 * @code
 * bfwarning << "hello world" << bfend;
 * @endcode
 */
#ifndef bfwarning
#define bfwarning std::cerr << bfcolor_warning << "WARNING" << bfcolor_end << ": "
#endif

/**
 * This macro is a shortcut for std::cerr that adds some text and color.
 * Use it like std::cerr
 *
 * @code
 * bferror << "hello world" << bfend;
 * @endcode
 */
#ifndef bferror
#define bferror std::cerr << bfcolor_error << "ERROR" << bfcolor_end << ": "
#endif

/**
 * This macro is a shortcut for std::cerr that adds some text and color.
 * Use it like std::cerr
 *
 * @code
 * bffatal << "hello world" << bfend;
 * @endcode
 */
#ifndef bffatal
#define bffatal std::cerr << bfcolor_error << "FATAL ERROR" << bfcolor_end << ": "
#endif

/**
 * This macro is a shortcut for printing the current file and line
 *
 * @code
 * bfline;
 * @endcode
 */
#define bfline bfdebug << bfcolor_blue << __BFFUNC__<< " ["                                        \
                       << bfcolor_yellow << __LINE__                                               \
                       << bfcolor_blue "]" << bfcolor_end << bfendl;

/**
 * This macro prints the value of field
 *
 * @code
 * int num = 10;
 * bffield(num)   // 10
 * @endcode
 */
#define bffield(a) bfdebug << bfcolor_blue << #a << ": "                                           \
                           << bfcolor_magenta << (a) << bfcolor_end << bfendl;

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
