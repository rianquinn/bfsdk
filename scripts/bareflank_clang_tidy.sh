#!/bin/bash -e
#
# Bareflank Hypervisor
#
# Copyright (C) 2015 Assured Information Security, Inc.
# Author: Rian Quinn        <quinnr@ainfosec.com>
# Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

# Note:
#
# To use this script, you need make sure you have a compilation database, and
# clang tidy set up properly.
#
#   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
#
# Once you have compiled Bareflank and created a compilation database,
# you should be able to run this script which will tell you if there are
# any issues with the code. The following describes what we turned off
# and why:
#
# - cppcoreguidelines-pro-type-reinterpret-cast: There are legit cases where we
#   need reinterpret_cast. As a result, we have disabled this. That being said,
#   each instance were it is used has been reviewed, and determined to be
#   needed. The remaining instances were removed in place of safer code.
#
# - cert-err58-cpp: This is triggered by catch.hpp which we need
#

#
# Output
#
OUTPUT=$PWD/.clang_tidy_results.txt

#
# Make sure we can run this script
#
if [[ ! -f "compile_commands.json" ]]; then
    echo "ERROR: database is missing. Did you run?"
    echo "    - cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .."
    exit 1
fi

#
# Ensure executable is in the PATH
#
if [[ ! -x "$(which run-clang-tidy-4.0.py)" ]]; then
    echo "ERROR: run-clang-tidy-4.0.py not in PATH"
    exit 1
fi

#
# Cleanup
#
rm -Rf $OUTPUT

#
# Run Clang Tidy
#
run_clang_tidy() {
    run-clang-tidy-4.0.py -clang-tidy-binary clang-tidy-4.0 -header-filter=.* -checks=$1 > $OUTPUT 2>&1

    if [[ -n $(grep "warning: " $OUTPUT) ]] || [[ -n $(grep "error: " $OUTPUT) ]]; then
        echo ""
        echo "############################"
        echo "# Clang-Tidy Checks Failed #"
        echo "############################"
        echo ""
        grep --color -E '^|warning: |error: ' $OUTPUT
        exit -1;
    else
        echo -e "\xE2\x9C\x93 passed: $1";
    fi

    rm -Rf $OUTPUT
}

#
# Perform Checks
#
run_clang_tidy "clan*$1"
run_clang_tidy "cert*,-clang-analyzer*,-cert-err58-cpp$1"
run_clang_tidy "misc*,-clang-analyzer*,-misc-noexcept-move-constructor$1"
run_clang_tidy "perf*,-clang-analyzer*$1"
run_clang_tidy "cppc*,-clang-analyzer*,-cppcoreguidelines-pro-type-reinterpret-cast$1"
run_clang_tidy "read*,-clang-analyzer*$1"
run_clang_tidy "mode*,-clang-analyzer*$1"
