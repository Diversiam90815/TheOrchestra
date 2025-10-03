###########################################
#   The Orchestra
#       by Jens W. Langenberg
###########################################

cmake_minimum_required(VERSION 3.25)

set(ORCHESTRA_VERSION 2.0.212)

project(TheOrchestra VERSION ${ORCHESTRA_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_FORMAT    "Run clang-format on sources during build"          ON)
option(ENABLE_CPPCHECK  "Run cppcheck static analysis on C++ targets"       ON)
option(ENABLE_DOXYGEN   "Add doxygen documentation target"                  OFF)
option(ENABLE_MEMCHECK  "Add memcheck target "                              OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CTest)

if(ENABLE_FORMAT) 
    include(Format)
endif()

if(ENABLE_CPPCHECK)
    include(CppCheck)
endif()

if(ENABLE_DOXYGEN)
    include(Doxygen)
endif()

# Include sub-projects.
add_subdirectory(src)
add_subdirectory(tests)
