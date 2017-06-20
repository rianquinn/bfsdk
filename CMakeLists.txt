# cmake ..

cmake_minimum_required(VERSION 3.6)
project(bfsdk C CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT WIN32 STREQUAL "1")
        set(CMAKE_INSTALL_PREFIX $ENV{HOME}/bfprefix CACHE PATH "" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX $ENV{HOMEPATH}/bfprefix CACHE PATH "" FORCE)
    endif()
endif()

include(cmake/CMakeGlobal_Project.txt)

# ------------------------------------------------------------------------------
# Source Directory
# ------------------------------------------------------------------------------

if(NOT BFSOURCE_DIR)
    set(BFSOURCE_DIR ${CMAKE_INSTALL_PREFIX}/src)
else()
    if(NOT IS_ABSOLUTE ${BFSOURCE_DIR})
        set(BFSOURCE_DIR ${CMAKE_BINARY_DIR}/${BFSOURCE_DIR})
    endif()
endif()

message(STATUS "Source Directory: ${BFSOURCE_DIR}")

# ------------------------------------------------------------------------------
# JSON
# ------------------------------------------------------------------------------

list(APPEND JSON_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
    json
    GIT_REPOSITORY      https://github.com/Bareflank/json.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${JSON_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/json/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/json/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/json/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/json/download
    SOURCE_DIR          ${BFSOURCE_DIR}/json
    BINARY_DIR          ${CMAKE_BINARY_DIR}/json/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Catch
# ------------------------------------------------------------------------------

list(APPEND CATCH_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
    catch
    GIT_REPOSITORY      https://github.com/Bareflank/Catch.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/catch/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/catch/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/catch/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/catch/download
    SOURCE_DIR          ${BFSOURCE_DIR}/catch
    BINARY_DIR          ${CMAKE_BINARY_DIR}/catch/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Hippomocks
# ------------------------------------------------------------------------------

list(APPEND HIPPOMOCKS_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
    hippomocks
    GIT_REPOSITORY      https://github.com/Bareflank/hippomocks.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${HIPPOMOCKS_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/hippomocks/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/hippomocks/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/hippomocks/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/hippomocks/download
    SOURCE_DIR          ${BFSOURCE_DIR}/hippomocks
    BINARY_DIR          ${CMAKE_BINARY_DIR}/hippomocks/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

list(APPEND GSL_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
    gsl
    GIT_REPOSITORY      https://github.com/Bareflank/GSL.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${GSL_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/gsl/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/gsl/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/gsl/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/gsl/download
    SOURCE_DIR          ${BFSOURCE_DIR}/gsl
    BINARY_DIR          ${CMAKE_BINARY_DIR}/gsl/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------

list(APPEND ASTYLE_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
    astyle
    GIT_REPOSITORY      https://github.com/Bareflank/astyle.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${ASTYLE_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/astyle/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/astyle/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/astyle/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/astyle/download
    SOURCE_DIR          ${BFSOURCE_DIR}/astyle
    BINARY_DIR          ${CMAKE_BINARY_DIR}/astyle/build
    UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
)

# ------------------------------------------------------------------------------
# Download Newlib
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        newlib
        GIT_REPOSITORY      https://github.com/Bareflank/newlib.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/newlib/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/newlib/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/newlib/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/newlib/download
        SOURCE_DIR          ${BFSOURCE_DIR}/newlib
        BINARY_DIR          ${CMAKE_BINARY_DIR}/newlib/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Download LLVM
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        llvm
        GIT_REPOSITORY      https://github.com/Bareflank/llvm.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/llvm/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/llvm/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/llvm/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/llvm/download
        SOURCE_DIR          ${BFSOURCE_DIR}/llvm
        BINARY_DIR          ${CMAKE_BINARY_DIR}/llvm/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Download Libcxxabi
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        libcxxabi
        GIT_REPOSITORY      https://github.com/Bareflank/libcxxabi.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/libcxxabi/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/libcxxabi/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/libcxxabi/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/libcxxabi/download
        SOURCE_DIR          ${BFSOURCE_DIR}/libcxxabi
        BINARY_DIR          ${CMAKE_BINARY_DIR}/libcxxabi/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Download Libcxx
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        libcxx
        GIT_REPOSITORY      https://github.com/Bareflank/libcxx.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/libcxx/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/libcxx/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/libcxx/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/libcxx/download
        SOURCE_DIR          ${BFSOURCE_DIR}/libcxx
        BINARY_DIR          ${CMAKE_BINARY_DIR}/libcxx/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Download Unwind
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        bfunwind
        GIT_REPOSITORY      https://github.com/Bareflank/bfunwind.git
        #GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/bfunwind/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/bfunwind/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/bfunwind/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/bfunwind/download
        SOURCE_DIR          ${BFSOURCE_DIR}/bfunwind
        BINARY_DIR          ${CMAKE_BINARY_DIR}/bfunwind/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Download Support
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    ExternalProject_Add(
        bfsupport
        GIT_REPOSITORY      https://github.com/Bareflank/bfsupport.git
        #GIT_TAG             v1.2
        GIT_SHALLOW         1
        PREFIX              ${CMAKE_BINARY_DIR}/bfsupport/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/bfsupport/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/bfsupport/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/bfsupport/download
        SOURCE_DIR          ${BFSOURCE_DIR}/bfsupport
        BINARY_DIR          ${CMAKE_BINARY_DIR}/bfsupport/build
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
        UPDATE_DISCONNECTED ${UPDATE_DISCONNECTED}
    )

endif()

# ------------------------------------------------------------------------------
# Binutils
# ------------------------------------------------------------------------------

if(NOT WIN32 STREQUAL "1")

    list(APPEND BINUTILS_ARGS
        --prefix=${CMAKE_BINARY_DIR}/binutils/prefix
        --target=${BAREFLANK_TARGET}
        --disable-nls
        --disable-werror
        --with-sysroot
    )

    ExternalProject_Add(
        binutils
        URL                 http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz
        URL_MD5             d5d270fd0b698ed59ca5ade8e1b5059c
        PREFIX              ${CMAKE_BINARY_DIR}/binutils/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/binutils/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/binutils/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/binutils/download
        SOURCE_DIR          ${BFSOURCE_DIR}/binutils
        BINARY_DIR          ${CMAKE_BINARY_DIR}/binutils/build
        CONFIGURE_COMMAND   ${BFSOURCE_DIR}/binutils/configure ${BINUTILS_ARGS}
        BUILD_COMMAND       make
        INSTALL_COMMAND     make install
        LOG_DOWNLOAD        1
        LOG_CONFIGURE       1
        LOG_BUILD           1
        LOG_INSTALL         1
    )

    ExternalProject_Add_Step(
        binutils
        prefix_install
        COMMAND             ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/binutils/prefix/bin/ ${CMAKE_INSTALL_PREFIX}/bin/
        DEPENDEES           install
    )

endif()

# ------------------------------------------------------------------------------
# Subdirectories
# ------------------------------------------------------------------------------

if(ENABLE_UNITTESTING)
    add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------

add_custom_target(super-clean
    COMMAND cmake --build . --target clean
    COMMAND cmake --build ${CMAKE_BINARY_DIR}/astyle/build --target clean
)

add_custom_target(dist-clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/astyle
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/bfsupport
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/bfunwind
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/binutils
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/catch
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/gsl
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/hippomocks
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/json
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/libcxx
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/libcxxabi
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/llvm
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BFSOURCE_DIR}/newlib
)

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
install(FILES include/bfjson.h DESTINATION include)
install(FILES include/bfmemory.h DESTINATION include)
install(FILES include/bfnewdelete.h DESTINATION include)
install(FILES include/bfplatform.h DESTINATION include)
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

install(PROGRAMS scripts/bareflank_astyle_format.sh DESTINATION bin)
install(PROGRAMS scripts/bareflank_clang_tidy.sh DESTINATION bin)
install(PROGRAMS scripts/bareflank_llvm_cov.sh DESTINATION bin)
install(PROGRAMS scripts/compiler_wrapper.sh DESTINATION bin)

install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang)
install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-3.8)
install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-3.9)
install_symlink(compiler_wrapper.sh ${CMAKE_INSTALL_PREFIX}/bin/x86_64-vmm-clang-4.0)
