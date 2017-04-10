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

#include <cstdlib>

#include <string>
#include <vector>
#include <fstream>

#include <bfgsl.h>
#include <bfpublish.h>
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

    using text_data = std::string;                      ///< File format for text data
    using binary_data = std::vector<char>;              ///< File format for binary data
    using filename_type = std::string;                  ///< File name type
    using extension_type = std::string;                 ///< Extension name type
    using path_list_type = std::vector<std::string>;    ///< Find files path type

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
    PUBLISH ~file() noexcept = default;

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
    PUBLISH text_data
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
    PUBLISH binary_data
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
    PUBLISH void
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
    PUBLISH void
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
    PUBLISH extension_type
    extension(const filename_type &filename)
    {
        if (filename.empty()) {
            return {};
        }

        auto index = filename.find_last_of('.');

        if (index != filename_type::npos) {
            return filename.substr(index);
        }

        return {};
    }

    /// File Exists
    ///
    /// @expects none
    /// @ensures none
    ///
    /// @param filename the file name to check
    /// @return true if the file exists, false otherwise
    ///
    PUBLISH bool
    exists(const filename_type &filename)
    {
        auto &&handle = std::ifstream(filename);
        return handle.good();
    }

    /// Find Files
    ///
    /// Loops through all of the provided files and file paths and
    /// returns a list of each filename combined with the path and the filename
    /// that was first found. If a filename cannot be found, an exception is
    /// thrown.
    ///
    /// @note we use the '/' separator on both Windows and POSIX. The reason
    ///     is both support '/' for the versions we support.
    ///
    /// @expects files.empty() == false
    /// @expects paths.empty() == false
    /// @ensures ret: path_list_type.size() == files.size()
    ///
    /// @param files list of files to locate in the list of provided paths
    /// @param paths list of paths to search for the provided list of files
    /// @return pull paths for each file located, throws otherwise
    ///
    PUBLISH path_list_type
    find_files(const path_list_type &files, const path_list_type &paths)
    {
        expects(!files.empty());
        expects(!paths.empty());

        path_list_type results;

        for (const auto &filename : files) {
            auto found = false;

            for (auto path : paths) {
                path += '/';
                path += filename;

                if (exists(path)) {
                    results.push_back(path);

                    found = true;
                    break;
                }
            }

            if (!found) {
                throw std::runtime_error("unable to locate file: " + filename);
            }
        }

        return results;
    }

    /// Get Home Directory
    ///
    /// @expects none
    /// @expects none
    ///
    /// @return returns home directory
    ///
    PUBLISH std::string
    home()
    {
        char *home;

        home = std::getenv("HOME");
        if (home != nullptr) {
            return {home};
        }

        home = std::getenv("HOMEPATH");
        if (home != nullptr) {
            return {home};
        }

        throw std::runtime_error("HOME or HOMEPATH not set");
    }

public:

    file(file &&) noexcept = default;               ///< Default copy construction
    file &operator=(file &&) noexcept = default;    ///< Default copy operator

    file(const file &) = default;                   ///< Default move construction
    file &operator=(const file &) = default;        ///< Default move operator
};

#endif
