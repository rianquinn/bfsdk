[![GitHub version](https://badge.fury.io/gh/Bareflank%2Fbfsdk.svg)](https://badge.fury.io/gh/Bareflank%2Fbfsdk)
[![Build Status](https://travis-ci.org/Bareflank/bfsdk.svg?branch=master)](https://travis-ci.org/Bareflank/bfsdk)
[![Build status](https://ci.appveyor.com/api/projects/status/c00xbj5bdrsdt1m3?svg=true)](https://ci.appveyor.com/project/rianquinn/bfsdk)
[![codecov](https://codecov.io/gh/Bareflank/bfsdk/branch/master/graph/badge.svg)](https://codecov.io/gh/Bareflank/bfsdk)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d21cad7f7fd54ceb969c970f952f0e3d)](https://www.codacy.com/app/rianquinn/bfsdk?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bareflank/bfsdk&amp;utm_campaign=Badge_Grade)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/325/badge)](https://bestpractices.coreinfrastructure.org/projects/325)
[![Join the chat at https://gitter.im/Bareflank-hypervisor/Lobby](https://badges.gitter.im/Bareflank-hypervisor/Lobby.svg)](https://gitter.im/Bareflank-hypervisor/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Description

The Bareflank Software Development Kit (SDK) is the base repo for building the
various different Bareflank repos including the ELF loader, the VMM and the
sysroot. For this reason, it is the first repo that should be cloned, built and
installed prior to compiling any other repo.

## Dependencies

Although Bareflank can be made to run on most systems, the following are the
supported platforms and their dependencies:

#### Ubuntu 16.10 (or Higher):
```
sudo apt-get install build-essential linux-headers-$(uname -r) nasm cmake clang
```

#### Windows (Cygwin):
```
setup-x86_64.exe -q -P git,make,gcc-core,gcc-g++,nasm,clang,clang++,cmake,wget
```

#### Windows (Visual Studio):

Install the following packages:
- [Visual Studio SDK 10](https://go.microsoft.com/fwlink/?linkid=838916)
- [Visual Stidio WDK 10](https://go.microsoft.com/fwlink/p/?LinkId=526733)
- [Visual Studio 2017](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=Community&rel=15#)
  - Check "Desktop development with C++"
  - Check "C++ CLI / Support"
  - Check "Standard Library Modules"
- [CMake v3.8 rc3 or higher](https://cmake.org/files/v3.8/cmake-3.8.0-rc3-win64-x64.msi)
- [Git](https://github.com/git-for-windows/git/releases/download/v2.12.2.windows.1/Git-2.12.2-64-bit.exe)

## Compilation / Installation

To compile and install the Bareflank SDK, use the following instructions:

#### GCC / Clang
```
git clone https://github.com/Bareflank/bfsdk.git

mkdir bfsdk/build
cd bfsdk/build

cmake ..

make
make test
make install
```

#### Visual Studio 2017 (NMake)

From the x64 Native Tools Command Prompt for Visual Studio:
```
git clone https://github.com/Bareflank/bfsdk.git

mkdir bfsdk/build
cd bfsdk/build

cmake -G "NMake Makefiles" ..

nmake
nmake test
nmake install
```

#### Visual Studio 2017 (MSBuild)

From the Developer Command Prompt for Visual Studio:
```
git clone https://github.com/Bareflank/bfsdk.git

mkdir bfsdk/build
cd bfsdk/build

cmake -G "Visual Studio 15 2017 Win64" ..

msbuild bfsdk.sln
ctest
cmake --build . --target install
```

## Prefix Notes (Optional)

Once built and installed, the SDK will create the Bareflank "prefix" which is a
working directory where dependencies and various different scripts are
installed. By default, the prefix is set to:

#### Linux
```
$HOME/bfprefix
```

#### Windows
```
%HOMEPATH%\bfprefix
```

This can be changed by using the following (must be performed for all Bareflank
repos):

```
cmake -DCMAKE_INSTALL_PREFIX=path ..
```
## Path Notes (Optional)

Various applications will be installed into the Bareflank prefix which will be
needed for both development, and regular use. Although this step is optional,
it is highly recommended to add the prefix's bin directory to your path.

Note that on Linux, if your using sudo, you might have to add the prefix path
to your /etc/sudoers file in order to execute Bareflank applications and
scripts using sudo.

## License

The Bareflank Hypervisor is licensed under the GNU Lesser General Public License
v2.1 (LGPL).
