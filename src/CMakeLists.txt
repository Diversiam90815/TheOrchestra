include(cpm)

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
