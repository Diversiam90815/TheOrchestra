set(BUILDINFO_TEMPLATE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/buildinfo")
string(TIMESTAMP TIMESTAMP)

find_program(GIT_PATH git)

if(NOT GIT_PATH)
    message(WARNING "git not found - build info will not contain commit details.")
    set(COMMIT_SHA "unknown")
    set(COMMIT_SHA_SHORT "unknown")
    set(GIT_BRANCH "unknown")
else()

    # Full SHA
    execute_process(
        COMMAND ${GIT_PATH} rev-parse HEAD
        OUTPUT_VARIABLE COMMIT_SHA
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Short SHA
    execute_process(
        COMMAND ${GIT_PATH} rev-parse --short=7 HEAD
        OUTPUT_VARIABLE COMMIT_SHA_SHORT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Branch name
    execute_process(
        COMMAND ${GIT_PATH} rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

set(CMAKE_INFO        "${CMAKE_VERSION}")
set(GENERATOR         "${CMAKE_GENERATOR}")
set(BUILD_TYPE        "${CMAKE_BUILD_TYPE}")
set(CXX_STD           "${CMAKE_CXX_STANDARD}")
set(CXX_ID            "${CMAKE_CXX_COMPILER_ID}")
set(CXX_VER           "${CMAKE_CXX_COMPILER_VERSION}")
set(SYS_NAME          "${CMAKE_SYSTEM_NAME}")
set(SYS_VER           "${CMAKE_SYSTEM_VERSION}")
set(SYS_CPU           "${CMAKE_SYSTEM_PROCESSOR}")
set(HOST_SYS          "${CMAKE_HOST_SYSTEM_NAME}")
set(HOST_VER          "${CMAKE_HOST_SYSTEM_VERSION}")

configure_file("${BUILDINFO_TEMPLATE_DIR}/buildinfo.h.in" "${DESTINATION}/buildinfo.h" @ONLY)

function(BuildInfo target)
    target_include_directories(${target} PUBLIC ${DESTINATION})
endfunction()
