# ------------------------------------------------------------------------------
# CMake Includes
# ------------------------------------------------------------------------------

include("../cmake/CMakeGlobal_Includes.txt")
include("../cmake/CMakeOption_Testing.txt")

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

add_library(test_catch STATIC test.cpp)

macro(do_test str)
    add_executable(test_${str} test_${str}.cpp)
    target_link_libraries(test_${str} test_catch)
    add_test(test_${str} test_${str})
endmacro(do_test)

do_test(bitmanip)
do_test(buffer)
do_test(debug)
do_test(errorcodes)
do_test(exceptions)
do_test(file)
do_test(shuffle)
do_test(string)
do_test(types)
do_test(upperlower)
do_test(vector)
