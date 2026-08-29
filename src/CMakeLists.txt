CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 8.0.3
    VERSION 8.0.3
)

if(ENABLE_FORMAT)
    include(Format)
endif()

if(ENABLE_CPPCHECK)
    include(CppCheck)
endif()

if(ENABLE_DOXYGEN)
    include(Doxygen)
endif()

add_subdirectory(OrchestraCore)
add_subdirectory(OrchestraUI)
add_subdirectory(OrchestraApp)
add_subdirectory(OrchestraPlugin)
