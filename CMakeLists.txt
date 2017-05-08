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
include("cmake/CMakeOption_Tidy.txt")
include("cmake/CMakeOption_Astyle.txt")

# ------------------------------------------------------------------------------
# JSON
# ------------------------------------------------------------------------------

list(APPEND JSON_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    json
    GIT_REPOSITORY      https://github.com/Bareflank/json.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${JSON_CMAKE_ARGS}
    TMP_DIR             ${CMAKE_BINARY_DIR}/bfsdk/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/bfsdk/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/bfsdk/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/bfsdk/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/bfsdk/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Catch
# ------------------------------------------------------------------------------

list(APPEND CATCH_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    catch
    GIT_REPOSITORY      https://github.com/Bareflank/Catch.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
    TMP_DIR             ${CMAKE_BINARY_DIR}/catch/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/catch/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/catch/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/catch/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/catch/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Hippomocks
# ------------------------------------------------------------------------------

list(APPEND HIPPOMOCKS_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    hippomocks
    GIT_REPOSITORY      https://github.com/Bareflank/hippomocks.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${HIPPOMOCKS_CMAKE_ARGS}
    TMP_DIR             ${CMAKE_BINARY_DIR}/hippomocks/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/hippomocks/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/hippomocks/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/hippomocks/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/hippomocks/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

list(APPEND GSL_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    gsl
    GIT_REPOSITORY      https://github.com/Bareflank/GSL.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${GSL_CMAKE_ARGS}
    TMP_DIR             ${CMAKE_BINARY_DIR}/gsl/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/gsl/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/gsl/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/gsl/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/gsl/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------

list(APPEND ASTYLE_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(
    astyle
    GIT_REPOSITORY      https://github.com/Bareflank/astyle.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${ASTYLE_CMAKE_ARGS}
    TMP_DIR             ${CMAKE_BINARY_DIR}/astyle/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/astyle/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/astyle/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/astyle/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/astyle/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Newlib
# ------------------------------------------------------------------------------

ExternalProject_Add(
    newlib
    GIT_REPOSITORY      https://github.com/Bareflank/newlib.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/newlib/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/newlib/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/newlib/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/newlib
    BINARY_DIR          ${CMAKE_BINARY_DIR}/newlib/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download LLVM
# ------------------------------------------------------------------------------

ExternalProject_Add(
    llvm
    GIT_REPOSITORY      https://github.com/Bareflank/llvm.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/llvm/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/llvm/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/llvm/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/llvm
    BINARY_DIR          ${CMAKE_BINARY_DIR}/llvm/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Libcxxabi
# ------------------------------------------------------------------------------

ExternalProject_Add(
    libcxxabi
    GIT_REPOSITORY      https://github.com/Bareflank/libcxxabi.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/libcxxabi/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/libcxxabi/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/libcxxabi/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/libcxxabi
    BINARY_DIR          ${CMAKE_BINARY_DIR}/libcxxabi/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Libcxx
# ------------------------------------------------------------------------------

ExternalProject_Add(
    libcxx
    GIT_REPOSITORY      https://github.com/Bareflank/libcxx.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/libcxx/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/libcxx/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/libcxx/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/libcxx
    BINARY_DIR          ${CMAKE_BINARY_DIR}/libcxx/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Unwind
# ------------------------------------------------------------------------------

ExternalProject_Add(
    bfunwind
    GIT_REPOSITORY      https://github.com/Bareflank/bfunwind.git
    #GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/bfunwind/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/bfunwind/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/bfunwind/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/bfunwind
    BINARY_DIR          ${CMAKE_BINARY_DIR}/bfunwind/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Support
# ------------------------------------------------------------------------------

ExternalProject_Add(
    bfsupport
    GIT_REPOSITORY      https://github.com/Bareflank/bfsupport.git
    #GIT_TAG             v1.2
    GIT_SHALLOW         1
    TMP_DIR             ${CMAKE_BINARY_DIR}/bfsupport/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/bfsupport/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/bfsupport/download
    SOURCE_DIR          ${CMAKE_INSTALL_PREFIX}/src/bfsupport
    BINARY_DIR          ${CMAKE_BINARY_DIR}/bfsupport/build
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Binutils
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")
    add_custom_target(binutils ALL VERBATIM COMMAND ${CMAKE_SOURCE_DIR}/scripts/create_linker.sh x86_64-vmm-elf ${CMAKE_INSTALL_PREFIX})
endif()

# ------------------------------------------------------------------------------
# Subdirectories
# ------------------------------------------------------------------------------

if(ENABLE_UNITTESTING)
    add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------
# Install
# ------------------------------------------------------------------------------

install(FILES cmake/CMakeFlags_Native_GCC.txt DESTINATION cmake)
install(FILES cmake/CMakeFlags_Native_VS.txt DESTINATION cmake)
install(FILES cmake/CMakeFlags_VMM.txt DESTINATION cmake)
install(FILES cmake/CMakeGlobal_Includes.txt DESTINATION cmake)
install(FILES cmake/CMakeGlobal_Project.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_ASan.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Astyle.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Coverage.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Coverage_LLVM.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Testing.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_Tidy.txt DESTINATION cmake)
install(FILES cmake/CMakeOption_USan.txt DESTINATION cmake)
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
