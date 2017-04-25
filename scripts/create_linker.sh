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

SRC="$(mktemp -d)"
BLD="$(mktemp -d)"
TMP="$(mktemp -d)"

function cleanup {
    rm -Rf $SRC
    rm -Rf $BLD
    rm -Rf $TMP
}

trap cleanup EXIT

echo "Downloading... please wait!!!"
cd $TMP
wget -nv -O binutils.tar.gz http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz 1>/dev/null 2>/dev/null

echo "Extracting... please wait!!!"
tar xf binutils.tar.gz -C $SRC --strip-components=1

echo "Building... please wait!!!"
cd $BLD
$SRC/configure --target=$1 --prefix="$2" --disable-nls --disable-werror --with-sysroot 1>/dev/null 2>/dev/null
make -j2 1>/dev/null 2>/dev/null

echo "Installing... please wait!!!"
make -j2 install 1>/dev/null 2>/dev/null
