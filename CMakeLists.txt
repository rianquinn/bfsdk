# cmake ..

cmake_minimum_required(VERSION 3.6)
project(bfsdk C CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT WIN32 STREQUAL "1")
        set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/bfprefix" CACHE PATH "default install path" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "$ENV{HOMEPATH}/bfprefix" CACHE PATH "default install path" FORCE)
    endif()
endif()

include("cmake/CMakeGlobal_Project.txt")

# ------------------------------------------------------------------------------
# JSON
# ------------------------------------------------------------------------------

list(APPEND CATCH_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    json
    PREFIX ${CMAKE_BINARY_DIR}/json
    GIT_REPOSITORY https://github.com/Bareflank/json.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CMAKE_ARGS ${CATCH_CMAKE_ARGS}
)

# ------------------------------------------------------------------------------
# Catch
# ------------------------------------------------------------------------------

list(APPEND CATCH_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/Bareflank/Catch.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CMAKE_ARGS ${CATCH_CMAKE_ARGS}
)

# ------------------------------------------------------------------------------
# Hippomocks
# ------------------------------------------------------------------------------

list(APPEND HIPPOMOCKS_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    hippomocks
    PREFIX ${CMAKE_BINARY_DIR}/hippomocks
    GIT_REPOSITORY https://github.com/Bareflank/hippomocks.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CMAKE_ARGS ${HIPPOMOCKS_CMAKE_ARGS}
)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

list(APPEND GSL_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    gsl
    PREFIX ${CMAKE_BINARY_DIR}/gsl
    GIT_REPOSITORY https://github.com/Bareflank/GSL.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CMAKE_ARGS ${GSL_CMAKE_ARGS}
)

# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------

list(APPEND ASTYLE_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    astyle
    PREFIX ${CMAKE_BINARY_DIR}/astyle
    GIT_REPOSITORY https://github.com/Bareflank/astyle.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CMAKE_ARGS ${ASTYLE_CMAKE_ARGS}
)

# ------------------------------------------------------------------------------
# Download Newlib
# ------------------------------------------------------------------------------

ExternalProject_Add(
    newlib
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/newlib-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/newlib-build
    GIT_REPOSITORY https://github.com/Bareflank/newlib.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Download LLVM
# ------------------------------------------------------------------------------

ExternalProject_Add(
    llvm
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/llvm-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/llvm-build
    GIT_REPOSITORY https://github.com/Bareflank/llvm.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Download Libcxxabi
# ------------------------------------------------------------------------------

ExternalProject_Add(
    libcxxabi
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/libcxxabi-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/libcxxabi-build
    GIT_REPOSITORY https://github.com/Bareflank/libcxxabi.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Download Libcxx
# ------------------------------------------------------------------------------

ExternalProject_Add(
    libcxx
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/libcxx-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/libcxx-build
    GIT_REPOSITORY https://github.com/Bareflank/libcxx.git
    GIT_TAG v1.2
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Download Unwind
# ------------------------------------------------------------------------------

ExternalProject_Add(
    bfunwind
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/bfunwind-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/bfunwind-build
    GIT_REPOSITORY https://github.com/Bareflank/bfunwind.git
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Download Support
# ------------------------------------------------------------------------------

ExternalProject_Add(
    bfsupport
    PREFIX ${CMAKE_INSTALL_PREFIX}
    STAMP_DIR ${CMAKE_BINARY_DIR}/bfsupport-stamp
    BINARY_DIR ${CMAKE_BINARY_DIR}/bfsupport-build
    GIT_REPOSITORY https://github.com/Bareflank/bfsupport.git
    GIT_SHALLOW 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# ------------------------------------------------------------------------------
# Binutils
# ------------------------------------------------------------------------------

add_custom_command(
    OUTPUT ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-elf-ld
    COMMAND ../scripts/create_linker.sh "x86_64-vmm-elf" ${CMAKE_INSTALL_PREFIX}
    VERBATIM
)

if(NOT WIN32 STREQUAL "1")
    add_custom_target(binutils ALL DEPENDS ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-elf-ld)
endif()

# ------------------------------------------------------------------------------
# Subdirectories
# ------------------------------------------------------------------------------

add_subdirectory(test)

# ------------------------------------------------------------------------------
# Install
# ------------------------------------------------------------------------------

install(FILES cmake/CMakeFlags_Native_GCC.txt DESTINATION cmake)
install(FILES cmake/CMakeFlags_Native_VS.txt DESTINATION cmake)
install(FILES cmake/CMakeFlags_VMM.txt DESTINATION cmake)
install(FILES cmake/CMakeGlobal_Includes.txt DESTINATION cmake)
install(FILES cmake/CMakeGlobal_Project.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_ASan.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Coverage.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Coverage_LLVM.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Testing.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_USan.txt DESTINATION cmake)
install(FILES cmake/CMakeTarget_Coverage.txt DESTINATION cmake)
install(FILES cmake/CMakeTarget_Format.txt DESTINATION cmake)
install(FILES cmake/CMakeTarget_Tidy.txt DESTINATION cmake)
install(FILES cmake/CMakeToolchain_VMM.txt DESTINATION cmake)
install(FILES cmake/CMakeToolchain_VMM_38.txt DESTINATION cmake)
install(FILES cmake/CMakeToolchain_VMM_39.txt DESTINATION cmake)
install(FILES cmake/CMakeToolchain_VMM_40.txt DESTINATION cmake)

install(FILES include/bfbitmanip.h DESTINATION include)
install(FILES include/bfbuffer.h DESTINATION include)
install(FILES include/bfconstants.h DESTINATION include)
install(FILES include/bfdebug.h DESTINATION include)
install(FILES include/bfdebugringinterface.h DESTINATION include)
install(FILES include/bfdriverinterface.h DESTINATION include)
install(FILES include/bfehframelist.h DESTINATION include)
install(FILES include/bferrorcodes.h DESTINATION include)
install(FILES include/bfexception.h DESTINATION include)
install(FILES include/bfexports.h DESTINATION include)
install(FILES include/bffile.h DESTINATION include)
install(FILES include/bfgsl.h DESTINATION include)
install(FILES include/bfmemory.h DESTINATION include)
install(FILES include/bfnewdelete.h DESTINATION include)
install(FILES include/bfplatform.h DESTINATION include)
install(FILES include/bfpublish.h DESTINATION include)
install(FILES include/bfshuffle.h DESTINATION include)
install(FILES include/bfstd.h DESTINATION include)
install(FILES include/bfstring.h DESTINATION include)
install(FILES include/bfsupport.h DESTINATION include)
install(FILES include/bfthreadcontext.h DESTINATION include)
install(FILES include/bftypes.h DESTINATION include)
install(FILES include/bfupperlower.h DESTINATION include)
install(FILES include/bfvector.h DESTINATION include)
install(FILES include/bfvmcallinterface.h DESTINATION include)

install(FILES src/bfvmcall_intel_x64.asm DESTINATION src)

if(NOT WIN32 STREQUAL "1")
    install(PROGRAMS scripts/bareflank_astyle_format.sh DESTINATION bin)
    install(PROGRAMS scripts/bareflank_clang_tidy.sh DESTINATION bin)
    install(PROGRAMS scripts/bareflank_llvm_cov.sh DESTINATION bin)
    install(PROGRAMS scripts/compiler_wrapper.sh DESTINATION bin)
    install(PROGRAMS scripts/create_linker.sh DESTINATION bin)
    install(PROGRAMS scripts/link_newlib.sh DESTINATION bin)

    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang++)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-3.8)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang++-3.8)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-3.9)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang++-3.9)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-4.0)
    install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang++-4.0)
endif()
