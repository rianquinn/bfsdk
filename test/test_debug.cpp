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

#include <gsl/gsl>
#include <bfdebug.h>

template<class T>
void
CHECK_COUT(const std::string &out, const std::string &err, T func)
{
    std::stringstream outbuf;
    std::stringstream errbuf;
    std::streambuf *outbuf_original = std::cout.rdbuf();
    std::streambuf *errbuf_original = std::cerr.rdbuf();

    auto _ = gsl::finally([&] {
        std::cout.rdbuf(outbuf_original);
        std::cerr.rdbuf(errbuf_original);

        CHECK(outbuf.str() == out);
        CHECK(errbuf.str() == err);
    });

    std::cout.rdbuf(outbuf.rdbuf());
    std::cerr.rdbuf(errbuf.rdbuf());

    func();
}

TEST_CASE("__FUNC__")
{
    bfdebug << __FUNC__ << '\n';
}

TEST_CASE("view_as_pointer: integer")
{
    int i = 1;
    CHECK(view_as_pointer(i) == reinterpret_cast<const void *>(0x1));
}

TEST_CASE("view_as_pointer: pointer")
{
    int i = 1;
    CHECK(view_as_pointer(&i) == reinterpret_cast<const void *>(&i));
}

TEST_CASE("output_to_vcpu: success")
{
    CHECK_COUT("$vcpuid=               0x1hello\n", "", [] {
        output_to_vcpu(1, [] { std::cout << "hello\n"; });
    });
}

TEST_CASE("output_to_vcpu: throw")
{
    auto caught = false;

    try {
        CHECK_COUT("$vcpuid=               0x1\n", "", [] {
            output_to_vcpu(1, [] { throw std::runtime_error("error"); });
        });
    }
    catch (...) {
        caught = true;
    }

    CHECK(caught);
}

TEST_CASE("bfendl")
{
    CHECK_COUT("\n", "", [] {
        std::cout << bfendl;
    });
}

TEST_CASE("bfdebug")
{
    CHECK_COUT(bfcolor_debug "DEBUG" bfcolor_end ": hello\n", "", [] {
        bfdebug << "hello\n";
    });
}

TEST_CASE("bfwarning")
{
    CHECK_COUT("", bfcolor_warning "WARNING" bfcolor_end ": hello\n", [] {
        bfwarning << "hello\n";
    });
}

TEST_CASE("bferror")
{
    CHECK_COUT("", bfcolor_error "ERROR" bfcolor_end ": hello\n", [] {
        bferror << "hello\n";
    });
}

TEST_CASE("bffatal")
{
    CHECK_COUT("", bfcolor_error "FATAL ERROR" bfcolor_end ": hello\n", [] {
        bffatal << "hello\n";
    });
}
