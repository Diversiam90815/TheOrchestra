###########################################
#   The Orchestra
#       by Jens W. Langenberg
###########################################

cmake_minimum_required(VERSION 4.0)

set(PROJECT_VERSION 2.1.379)

project(TheOrchestra VERSION ${PROJECT_VERSION} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_FORMAT    "Run clang-format on sources during build"          OFF)
option(ENABLE_CPPCHECK  "Run cppcheck static analysis on C++ targets"       OFF)
option(ENABLE_DOXYGEN   "Add doxygen documentation target"                  OFF)
option(ENABLE_MEMCHECK  "Add memcheck target"                               OFF)
option(ENABLE_ASIO      "Build with ASIO support (requires the ASIO SDK)"   OFF)

set(LIB_DIR "${CMAKE_SOURCE_DIR}/libs" CACHE PATH "Directory for external dependencies" FORCE)
set(CPM_SOURCE_CACHE "${LIB_DIR}/cpm-cache" CACHE PATH "Shared cache for CPM-fetched dependencies" FORCE)
set(ASIO_SDK_PATH "" CACHE PATH "Path to the Steinberg ASIO SDK (for ENABLE_ASIO)")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cpm)
include(CTest)
include(ProjectOptions)

# Include sub-projects.
add_subdirectory(src)
add_subdirectory(tests)
