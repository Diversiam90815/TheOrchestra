include(cpm)

CPMAddPackage(
        NAME GOOGLETEST
        GITHUB_REPOSITORY google/googletest
        VERSION 1.15.2
        SOURCE_DIR ${LIB_DIR}/googletest
        OPTIONS
        "INSTALL_GTEST OFF"
        "INSTALL_GMOCK OFF"
        "gtest_force_shared_crt ON"
        )

include(GoogleTest)

macro(AddTests target)
    message("Adding tests to ${target}")
    target_link_libraries(${target} PRIVATE gtest_main gmock)
    gtest_discover_tests(${target})
endmacro()
