set(TARGET_NAME TheOrchestraUI)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (Custom_Dir                 ${CMAKE_CURRENT_SOURCE_DIR}/Custom )
set (PianoRoll_Dir              ${CMAKE_CURRENT_SOURCE_DIR}/PianoRoll )
set (MenuBar_Dir                ${CMAKE_CURRENT_SOURCE_DIR}/MenuBar )
set (InstrumentFamousWorks_Dir  ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentFamousWorks )
set (InstrumentInfo_Dir         ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentInfo )
set (InstrumentQualities_Dir    ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentQualities )
set (InstrumentTechniques_Dir   ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentTechniques )
set (InstrumentHeading_Dir      ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentHeading )
set (InstrumentRanges_Dir       ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentRanges )
set (OrchestraEditor_Dir        ${CMAKE_CURRENT_SOURCE_DIR}/OrchestraEditor )
set (Sampler_Dir                ${CMAKE_CURRENT_SOURCE_DIR}/Sampler )
set (Helper_Dir                 ${CMAKE_CURRENT_SOURCE_DIR}/Helper)


set(ALL_PROJECT_DIRS
    ${Custom_Dir}
    ${PianoRoll_Dir}
    ${MenuBar_Dir}
    ${InstrumentFamousWorks_Dir}
    ${InstrumentInfo_Dir}
    ${InstrumentQualities_Dir}
    ${InstrumentTechniques_Dir}
    ${InstrumentHeading_Dir}
    ${InstrumentRanges_Dir}
    ${OrchestraEditor_Dir}
    ${Sampler_Dir}
    ${Helper_Dir}
)

set(Custom_Files
    ${Custom_Dir}/CustomComponent.h         ${Custom_Dir}/CustomComponent.cpp
    ${Custom_Dir}/CustomLookAndFeel.h       ${Custom_Dir}/CustomLookAndFeel.cpp
)

set(PianoRoll_Files
    ${PianoRoll_Dir}/PianoRoll.h            ${PianoRoll_Dir}/PianoRoll.cpp
    ${PianoRoll_Dir}/CustomPianoRoll.h      ${PianoRoll_Dir}/CustomPianoRoll.cpp
)

set(MenuBar_Dir
    ${MenuBar_Dir}/MenuBar.h            ${MenuBar_Dir}/MenuBar.cpp
)

set(InstrumentFamousWorks_Files
    ${InstrumentFamousWorks_Dir}/FamousWorksView.h         ${InstrumentFamousWorks_Dir}/FamousWorksView.cpp
)

set(InstrumentInfo_Files
    ${InstrumentInfo_Dir}/InformationView.h         ${InstrumentInfo_Dir}/InformationView.cpp
)

set(InstrumentQualities_Files
    ${InstrumentQualities_Dir}/QualitiesView.h           ${InstrumentQualities_Dir}/QualitiesView.cpp
)

set(InstrumentTechniques_Files
    ${InstrumentTechniques_Dir}/TechniquesView.h          ${InstrumentTechniques_Dir}/TechniquesView.cpp
)

set(InstrumentHeading_Files
    ${InstrumentHeading_Dir}/InstrumentView.h         ${InstrumentHeading_Dir}/InstrumentView.cpp
)

set(InstrumentRanges_Files
    ${InstrumentRanges_Dir}/InstrumentRangesView.h         ${InstrumentRanges_Dir}/InstrumentRangesView.cpp
)

set(OrchestraEditor_Files
    ${OrchestraEditor_Dir}/PluginEditor.h           ${OrchestraEditor_Dir}/PluginEditor.cpp
)

set(Sampler_Files
    ${Sampler_Dir}/SamplerView.h          ${Sampler_Dir}/SamplerView.cpp
)

set(Helper_Files
    ${Helper_Dir}/CreateEditor.cpp
)

set(UI_PROJECT_FILES
    ${Custom_Files}
    ${PianoRoll_Files}
    ${MenuBar_Dir}
    ${InstrumentFamousWorks_Files}
    ${InstrumentInfo_Files}
    ${InstrumentQualities_Files}
    ${InstrumentTechniques_Files}
    ${InstrumentHeading_Files}
    ${InstrumentRanges_Files}
    ${OrchestraEditor_Files}
    ${Sampler_Files}
    ${Helper_Files}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UI_PROJECT_FILES})


add_library(${TARGET_NAME} STATIC ${UI_PROJECT_FILES})


if(ENABLE_CPPCHECK)
	AddCppCheck(${TARGET_NAME})
endif()

if(ENABLE_FORMAT)
	Format(${TARGET_NAME} ${ALL_PROJECT_DIRS})
endif()

if(ENABLE_DOXYGEN)
	Doxygen(Chess_Engine ${SOURCE_DIR})
endif()


juce_add_binary_data(FontBinaryData
    SOURCES ${ASSETS_DIR}/Font/Instrument-Serif/InstrumentSerif-Regular.ttf
)


target_include_directories(${TARGET_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${ALL_PROJECT_DIRS}
)

include(ProjectOptions)
set_common_target_options(${TARGET_NAME})


set (PROJECT_LIBS       TheOrchestraCore 
                        FontBinaryData
                        juce::juce_gui_basics
                        juce::juce_gui_extra
                        juce::juce_audio_utils
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )
