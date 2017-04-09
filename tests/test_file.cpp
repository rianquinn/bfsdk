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

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <bffile.h>
#include <bfstring.h>

TEST_CASE("read with bad filename")
{
    auto &&f = file{};
    auto &&filename = "/blah/bad_filename.txt"_s;

    CHECK_THROWS(f.read_text(""));
    CHECK_THROWS(f.read_binary(""));

    CHECK_THROWS(f.read_text(filename));
    CHECK_THROWS(f.read_binary(filename));
}

TEST_CASE("write with bad filename")
{
    auto &&f = file{};
    auto &&filename = "/blah/bad_filename.txt"_s;

    auto &&text_data = "hello"_s;
    auto &&binary_data = {'h', 'e', 'l', 'l', 'o'};

    CHECK_THROWS(f.write_text("", text_data));
    CHECK_THROWS(f.write_binary("", binary_data));

    CHECK_THROWS(f.write_text(filename, ""));
    CHECK_THROWS(f.write_binary(filename, {}));

    CHECK_THROWS(f.write_text(filename, text_data));
    CHECK_THROWS(f.write_binary(filename, binary_data));
}

TEST_CASE("read / write success")
{
    auto &&f = file{};
    auto &&filename = "test.txt"_s;

    auto &&text_data = "hello"_s;
    auto &&binary_data = {'h', 'e', 'l', 'l', 'o'};

    CHECK_NOTHROW(f.write_text(filename, text_data));
    CHECK(f.read_text(filename) == text_data);

    CHECK_NOTHROW(f.write_binary(filename, binary_data));
    CHECK(f.read_binary(filename) == file::binary_data(binary_data));

    auto &&ret = std::remove(filename.c_str());
    ignored(ret);
}

TEST_CASE("extension")
{
    auto &&f = file{};

    CHECK(f.extension("") == "");
    CHECK(f.extension("no_extension") == "");
    CHECK(f.extension("no_extension.") == ".");
    CHECK(f.extension(".nofilename") == ".nofilename");
    CHECK(f.extension("no_path.ext") == ".ext");
    CHECK(f.extension("/with/path.ext") == ".ext");
    CHECK(f.extension("more.than.one.ext") == ".ext");

    // #ifdef _WIN32
    // CHECK(f.extension(R"(c:\windows\path.ext)") == ".ext");
    // #endif
}

// TEST_CASE("basename")
// {
//     auto &&f = file{};

//     CHECK(f.basename("") == "");
//     CHECK(f.basename("no_path") == "no_path");
//     CHECK(f.basename("with.ext") == "with.ext");
//     CHECK(f.basename("/no_filename/") == ".");
//     CHECK(f.basename("no_filename/") == ".");
//     CHECK(f.basename("/no/filename/") == ".");
//     CHECK(f.basename("/absolute/file.ext") == "file.ext");
//     CHECK(f.basename("../relative/file.ext") == "file.ext");
//     CHECK(f.basename("/") == "/");

//     #ifdef _WIN32
//     CHECK(f.basename(R"(c:\windows\path.ext)") == "path.ext");
//     CHECK(f.basename(R"(c:\windows\no_filename\)") == ".");
//     #endif
// }

// TEST_CASE("dirname")
// {
//     auto &&f = file{};

//     CHECK(f.dirname("") == "");
//     CHECK(f.dirname("no_path") == "");
//     CHECK(f.dirname("with.ext") == "");
//     CHECK(f.dirname("/no_filename/") == "/no_filename");
//     CHECK(f.dirname("no_filename/") == "no_filename");
//     CHECK(f.dirname("/no/filename/") == "/no/filename");
//     CHECK(f.dirname("/absolute/file.ext") == "/absolute");
//     CHECK(f.dirname("../relative.ext") == "..");
//     CHECK(f.dirname("../relative/file.ext") == "../relative");
//     CHECK(f.dirname("/") == "");

//     #ifdef _WIN32
//     CHECK(f.dirname(R"(c:\windows\path.ext)") == R"(c:\windows)");
//     CHECK(f.dirname(R"(c:\windows\no_filename\)") == R"(c:\windows\no_filename)");
//     #endif
// }

// TEST_CASE("exists")
// {
//     auto &&f = file{};
//     auto &&filename = "test.txt"_s;

//     CHECK(!f.exists(""));
//     CHECK(!f.exists(filename));

//     CHECK_NOTHROW(f.write_text(filename, "hello world"));
//     CHECK(f.exists(filename));

//     auto &&ret = std::remove(filename.c_str());
//     ignored(ret);

//     CHECK(!f.exists(filename));
// }


// TEST_CASE("find files")
// {
//     auto &&f = file{};
//     auto &&files = {"test1.txt", "test2.txt"};
//     auto &&paths = {"../bad/path", ".."};

//     CHECK_NOTHROW(f.write_text(filename, "hello world"));

//     CHECK(!f.exists(""));
//     CHECK(!f.exists(filename));

//     CHECK(f.exists(filename));

//     auto &&ret = std::remove(filename.c_str());
//     ignored(ret);

//     CHECK(!f.exists(filename));
// }
