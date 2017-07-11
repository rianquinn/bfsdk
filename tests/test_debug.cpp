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

TEST_CASE("__BFFUNC__")
{
    bfdebug << __BFFUNC__ << '\n';
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
    CHECK_COUT(bfcolor_warning "WARNING" bfcolor_end ": hello\n", "", [] {
        bfwarning << "hello\n";
    });
}

TEST_CASE("bferror")
{
    CHECK_COUT(bfcolor_error "ERROR" bfcolor_end ": hello\n", "", [] {
        bferror << "hello\n";
    });
}

TEST_CASE("debug facilities")
{
    bfline;
    bffield(10);
}

TEST_CASE("debug macros")
{
    bfdebug_header(0, "debug macro tests");
    bfdebug_brline(0);
    bfdebug_break1(0);
    bfdebug_break2(0);
    bfdebug_break3(0);
    bfdebug_nhex(0, "test", 42);
    bfdebug_subnhex(0, "test", 42);
    bfdebug_ndec(0, "test", 42);
    bfdebug_subndec(0, "test", 42);
    bfdebug_bool(0, "test", true);
    bfdebug_subbool(0, "test", true);
    bfdebug_bool(0, "test", false);
    bfdebug_subbool(0, "test", false);
    bfdebug_text(0, "test", "value");
    bfdebug_subtext(0, "test", "value");
    bfdebug_info(0, "test");
    bfdebug_subinfo(0, "test");
    bfdebug_pass(0, "test");
    bfdebug_subpass(0, "test");
    bfdebug_fail(0, "test");
    bfdebug_subfail(0, "test");
    bfdebug_test(0, "test", true);
    bfdebug_subtest(0, "test", true);
    bfdebug_test(0, "test", false);
    bfdebug_subtest(0, "test", false);
}

TEST_CASE("debug macros: no print")
{
    bfdebug_header(1000, "debug macro tests");
    bfdebug_brline(1000);
    bfdebug_break1(1000);
    bfdebug_break2(1000);
    bfdebug_break3(1000);
    bfdebug_nhex(1000, "test", 42);
    bfdebug_subnhex(1000, "test", 42);
    bfdebug_ndec(1000, "test", 42);
    bfdebug_subndec(1000, "test", 42);
    bfdebug_bool(1000, "test", true);
    bfdebug_subbool(1000, "test", true);
    bfdebug_bool(1000, "test", false);
    bfdebug_subbool(1000, "test", false);
    bfdebug_text(1000, "test", "value");
    bfdebug_subtext(1000, "test", "value");
    bfdebug_info(1000, "test");
    bfdebug_subinfo(1000, "test");
    bfdebug_pass(1000, "test");
    bfdebug_subpass(1000, "test");
    bfdebug_fail(1000, "test");
    bfdebug_subfail(1000, "test");
    bfdebug_test(1000, "test", true);
    bfdebug_subtest(1000, "test", true);
    bfdebug_test(1000, "test", false);
    bfdebug_subtest(1000, "test", false);
}

TEST_CASE("error macros")
{
    bferror_header(0, "error macro tests");
    bferror_brline(0);
    bferror_break1(0);
    bferror_break2(0);
    bferror_break3(0);
    bferror_nhex(0, "test", 42);
    bferror_subnhex(0, "test", 42);
    bferror_ndec(0, "test", 42);
    bferror_subndec(0, "test", 42);
    bferror_bool(0, "test", true);
    bferror_subbool(0, "test", true);
    bferror_bool(0, "test", false);
    bferror_subbool(0, "test", false);
    bferror_text(0, "test", "value");
    bferror_subtext(0, "test", "value");
    bferror_info(0, "test");
    bferror_subinfo(0, "test");
}

TEST_CASE("error macros: no print")
{
    bferror_header(1000, "error macro tests");
    bferror_brline(1000);
    bferror_break1(1000);
    bferror_break2(1000);
    bferror_break3(1000);
    bferror_nhex(1000, "test", 42);
    bferror_subnhex(1000, "test", 42);
    bferror_ndec(1000, "test", 42);
    bferror_subndec(1000, "test", 42);
    bferror_bool(1000, "test", true);
    bferror_subbool(1000, "test", true);
    bferror_bool(1000, "test", false);
    bferror_subbool(1000, "test", false);
    bferror_text(1000, "test", "value");
    bferror_subtext(1000, "test", "value");
    bferror_info(1000, "test");
    bferror_subinfo(1000, "test");
}
