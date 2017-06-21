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

# ------------------------------------------------------------------------------
# Setup
# ------------------------------------------------------------------------------

find . -name "*.profraw" -type f -delete

declare -A region_stats
declare -A function_stats
declare -A instantiation_stats
declare -A line_stats

# ------------------------------------------------------------------------------
# Functions
# ------------------------------------------------------------------------------

run_test() {
    echo "executing: $1"
    LLVM_PROFILE_FILE="$PWD/$1.profraw" eval $1 1>/dev/null 2>/dev/null
    llvm-profdata-4.0 merge -sparse $PWD/$1.profraw -o default.profdata
    rm -Rf $PWD/$1.profraw
}

collect_test_stats() {
    llvm-cov-4.0 report $1 -instr-profile=default.profdata > stats.txt
    stats=$(awk 'flag{ if (/---/){printf "%s", buf; flag=0; buf=""} else buf = buf $0 ORS}; /---/{flag=1}' stats.txt)
    rm -Rf stats.txt
    rm -Rf default.profdata

    while read -r line; do

        filename=$(awk '{print $1}' <<< $line)

        if [[ ! $filename == "/"* ]]; then
            filename=$(readlink -f $2/$filename)
        fi

        regions=$(awk '{print $3}' <<< $line)
        functions=$(awk '{print $6}' <<< $line)
        instantiations=$(awk '{print $9}' <<< $line)
        lines=$(awk '{print $12}' <<< $line)

        if [[ ! ${region_stats[$filename]+exists} ]]; then
            region_stats[$filename]="incomplete"
        fi

        if [[ ! ${function_stats[$filename]+exists} ]]; then
            function_stats[$filename]="incomplete"
        fi

        if [[ ! ${instantiation_stats[$filename]+exists} ]]; then
            instantiation_stats[$filename]="incomplete"
        fi

        if [[ ! ${line_stats[$filename]+exists} ]]; then
            line_stats[$filename]="incomplete"
        fi

        if [[ $regions == "0" ]]; then
            region_stats[$filename]="complete"
        fi

        if [[ $functions == "0" ]]; then
            function_stats[$filename]="complete"
        fi

        if [[ $instantiations == "0" ]]; then
            instantiation_stats[$filename]="complete"
        fi

        if [[ $lines == "0" ]]; then
            line_stats[$filename]="complete"
        fi

    done <<< "$stats"
}

# ------------------------------------------------------------------------------
# Process Profile Data
# ------------------------------------------------------------------------------

if [[ "$#" -lt 1 ]]; then
    echo "ERROR: missing arguments"
    exit 1
fi

if [[ ! -x "$(which llvm-profdata-4.0)" ]]; then
    echo "ERROR: llvm-profdata-4.0 not in PATH"
    exit 1
fi

if [[ ! -x "$(which llvm-cov-4.0)" ]]; then
    echo "ERROR: llvm-cov-4.0 not in PATH"
    exit 1
fi

if [[ ! "$1" == "all" ]] && [[ ! "$1" == "test" ]]; then
    echo "ERROR: invalid opcode '$1'. Expecting 'all' or 'diff'"
    exit 1
fi

if [[ "$1" == "all" ]]; then

    if [[ "$#" -lt 2 ]]; then
        echo "ERROR: missing arguments"
        exit 1
    fi

    for f in $(find . -path "./*tests/test_*"); do
        run_test $f
        collect_test_stats $f $2
    done

    for i in "${!region_stats[@]}"
    do
        if [[ ! ${region_stats[$i]} == "complete" ]]; then
            incomplete="true"
            echo -e "\033[1;31mERROR: $i region coverage incomplete\033[0m"
        fi
    done

    for i in "${!function_stats[@]}"
    do
        if [[ ! ${function_stats[$i]} == "complete" ]]; then
            incomplete="true"
            echo -e "\033[1;31mERROR: $i function coverage incomplete\033[0m"
        fi
    done

    for i in "${!instantiation_stats[@]}"
    do
        if [[ ! ${instantiation_stats[$i]} == "complete" ]]; then
            incomplete="true"
            echo -e "\033[1;31mERROR: $i instantiation coverage incomplete\033[0m"
        fi
    done

    for i in "${!line_stats[@]}"
    do
        if [[ ! ${line_stats[$i]} == "complete" ]]; then
            incomplete="true"
            echo -e "\033[1;31mERROR: $i line coverage incomplete\033[0m"
        fi
    done

    if [[ ! $incomplete == "true" ]]; then
        echo -e "\033[1;32m\xE2\x9C\x93 coverage complete\033[0m"
        exit 0
    else
        exit 1
    fi

else

    if [[ ! -f $LLVM_COVERAGE_TEST ]]; then
        echo "ERROR: LLVM_COVERAGE_TEST file not found: $LLVM_COVERAGE_TEST"
        exit 1
    fi

    run_test $LLVM_COVERAGE_TEST
    llvm-cov-4.0 show $LLVM_COVERAGE_TEST -instr-profile=default.profdata
    llvm-cov-4.0 report $LLVM_COVERAGE_TEST -instr-profile=default.profdata

fi
