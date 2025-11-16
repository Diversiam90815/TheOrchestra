###########################################
#   The Orchestra
#       by Jens W. Langenberg
###########################################

cmake_minimum_required(VERSION 3.25)

set(PROJECT_VERSION 2.1.262)

project(TheOrchestra VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_FORMAT    "Run clang-format on sources during build"          OFF)
option(ENABLE_CPPCHECK  "Run cppcheck static analysis on C++ targets"       ON)
option(ENABLE_DOXYGEN   "Add doxygen documentation target"                  OFF)
option(ENABLE_MEMCHECK  "Add memcheck target "                              OFF)

set(LIB_DIR "${CMAKE_SOURCE_DIR}/libs" CACHE PATH "Directory for external dependencies")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cpm)
include(CTest)

# Include sub-projects.
add_subdirectory(src)
add_subdirectory(tests)
