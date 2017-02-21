# ------------------------------------------------------------------------------
# CMake Includes
# ------------------------------------------------------------------------------

include("../cmake/CMakeGlobal_Includes.txt")
include("../cmake/CMakeOption_Testing.txt")

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

macro(do_test str)
    add_executable(test_${str} test_${str}.cpp)
    add_test(bfelf_${str} test_${str})
endmacro(do_test)

do_test(bitmanip)
do_test(debug)
do_test(errorcodes)
do_test(exceptions)
do_test(string)
do_test(upperlower)
do_test(vector)
