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
/// @file bffile.h
///

#ifndef BFFILE_H
#define BFFILE_H

#include <string>
#include <vector>
#include <fstream>

#include <bfgsl.h>
#include <bfexception.h>

/// File
///
/// This class is responsible for working with a file. Specifically, this
/// class wraps calls to ifstream and fstream to simplify their interface
/// as well as provide an implementation for the rest of the Bareflank
/// Manager, such that testing is easier.
///
class file
{
public:

    using text_data = std::string;          ///< File format for text data
    using binary_data = std::vector<char>;  ///< File format for binary data
    using filename_type = std::string;      ///< File name type

    /// @endcond

    /// File Constructor
    ///
    /// @expects none
    /// @ensures none
    ///
    /// Creates a file class that can be used to working with files.
    ///
    file() noexcept = default;

    /// File Destructor
    ///
    /// @expects none
    /// @ensures none
    ///
    virtual ~file() = default;

    /// Read
    ///
    /// Reads the entire contents of a file, in text form
    ///
    /// @expects filename.empty() == false
    /// @ensures none
    ///
    /// @param filename name of the file to read.
    /// @return the contents of filename
    ///
    virtual text_data
    read_text(const filename_type &filename) const
    {
        expects(!filename.empty());

        if (auto && handle = std::fstream(filename, std::ios_base::in)) {
            return text_data(std::istreambuf_iterator<char>(handle),
                             std::istreambuf_iterator<char>());
        }

        throw std::runtime_error("invalid filename: " + filename);
    }

    /// Read
    ///
    /// Reads the entire contents of a file, in binary form
    ///
    /// @expects filename.empty() == false
    /// @ensures none
    ///
    /// @param filename name of the file to read.
    /// @return the contents of filename
    ///
    virtual binary_data
    read_binary(const filename_type &filename) const
    {
        expects(!filename.empty());

        if (auto && handle = std::fstream(filename, std::ios_base::in | std::ios_base::binary)) {
            return binary_data(std::istreambuf_iterator<char>(handle),
                               std::istreambuf_iterator<char>());
        }

        throw std::runtime_error("invalid filename: " + filename);
    }

    /// Write
    ///
    /// Writes text data to the file provided
    ///
    /// @expects filename.empty() == false
    /// @expects data.empty() == false
    /// @ensures none
    ///
    /// @param filename name of the file to write to.
    /// @param data data to write
    ///
    virtual void
    write_text(const filename_type &filename, const text_data &data) const
    {
        expects(!filename.empty());
        expects(!data.empty());

        if (auto && handle = std::fstream(filename, std::ios_base::out | std::ios_base::binary)) {
            std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(handle));
            return;
        }

        throw std::runtime_error("invalid filename: " + filename);
    }

    /// Write
    ///
    /// Writes binary data to the file provided
    ///
    /// @expects filename.empty() == false
    /// @expects data.empty() == false
    /// @ensures none
    ///
    /// @param filename name of the file to write to.
    /// @param data data to write
    ///
    virtual void
    write_binary(const filename_type &filename, const binary_data &data) const
    {
        expects(!filename.empty());
        expects(!data.empty());

        if (auto && handle = std::fstream(filename, std::ios_base::out | std::ios_base::binary)) {
            std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(handle));
            return;
        }

        throw std::runtime_error("invalid filename: " + filename);
    }

    /// Get File Extension
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param filename the file name to extract the extension
    /// @return the filename's extension
    ///
    virtual std::string
    extension(const std::string &filename)
    {
        if (filename.empty()) {
            return {};
        }

        auto len = filename.length();
        auto index = filename.find_last_of('.');

        if (index != std::string::npos && index + 1 < len) {
            return filename.substr(index + 1);
        }

        return {};
    }

    /// Get File Base Name
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param filename the file name to extract the basename
    /// @return the filename's basename (includes extension)
    ///
    virtual std::string
    basename(const std::string &filename)
    {
        if (filename.empty()) {
            return {};
        }

        auto len = filename.length();
        auto index = filename.find_last_of(R"(/\)");

        if (index == std::string::npos) {
            return filename;
        }

        if (index + 1 >= len) {

            len--;
            index = filename.substr(0, len).find_last_of(R"(/\)");

            if (len == 0) {
                return filename;
            }

            if (index == 0) {
                return filename.substr(1, len - 1);
            }

            if (index == std::string::npos) {
                return filename.substr(0, len);
            }

            return filename.substr(index + 1, len - index - 1);
        }

        return filename.substr(index + 1, len - index);
    }

    /// Get File Directory Name
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param filename the file name to extract the directory
    /// @return the filename's directory
    ///
    virtual std::string
    dirname(const std::string &filename)
    {
        if (filename.empty()) {
            return ".";
        }

        auto len = filename.length();
        auto index = filename.find_last_of(R"(/\)");

        if (index == std::string::npos) {
            return ".";
        }

        if (index + 1 >= len) {

            len--;
            index = filename.substr(0, len).find_last_of(R"(/\)");

            if (len == 0) {
                return filename;
            }

            if (index == 0) {
                return filename.substr(0, index + 1);
            }

            if (index == std::string::npos) {
                return ".";
            }

            return filename.substr(0, index);
        }

        return filename.substr(0, index);
    }

    /// File Exists
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param filename the file name to check
    /// @return true if the file exists, false otherwise
    ///
    virtual bool
    exists(const std::string &filename)
    {
        auto &&f = std::ifstream(filename);
        return f.good();
    }

public:

    file(file &&) noexcept = default;               ///< Default copy construction
    file &operator=(file &&) noexcept = default;    ///< Default copy operator

    file(const file &) = default;                   ///< Default move construction
    file &operator=(const file &) = default;        ///< Default move operator
};

#endif
