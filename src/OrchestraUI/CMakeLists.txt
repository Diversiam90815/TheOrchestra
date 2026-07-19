set(TARGET_NAME TheOrchestraUI)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (Custom_Dir                 ${CMAKE_CURRENT_SOURCE_DIR}/Custom )
set (PianoRoll_Dir              ${CMAKE_CURRENT_SOURCE_DIR}/PianoRoll )
set (HeaderBar_Dir              ${CMAKE_CURRENT_SOURCE_DIR}/HeaderBar )
set (InstrumentSidebar_Dir      ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentSidebar )
set (InstrumentFamousWorks_Dir  ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentFamousWorks )
set (InstrumentInfo_Dir         ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentInfo )
set (InstrumentRegister_Dir     ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentRegisters)
set (InstrumentTechniques_Dir   ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentTechniques )
set (InstrumentHeading_Dir      ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentHeading )
set (InstrumentRanges_Dir       ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentRanges )
set (OrchestraEditor_Dir        ${CMAKE_CURRENT_SOURCE_DIR}/OrchestraEditor )
set (Sampler_Dir                ${CMAKE_CURRENT_SOURCE_DIR}/Sampler )
set (NotationRenderer_Dir       ${CMAKE_CURRENT_SOURCE_DIR}/NotationRenderer )
set (Helper_Dir                 ${CMAKE_CURRENT_SOURCE_DIR}/Helper)
set (FamilySwitcher_Dir         ${CMAKE_CURRENT_SOURCE_DIR}/FamilySwitcher )
set (InstrumentDetail_Dir       ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentDetail )
set (TabBar_Dir                 ${CMAKE_CURRENT_SOURCE_DIR}/TabBar )
set (Overview_Dir               ${CMAKE_CURRENT_SOURCE_DIR}/Overview )


set(ALL_PROJECT_DIRS
    ${Custom_Dir}
    ${PianoRoll_Dir}
    ${HeaderBar_Dir}
    ${InstrumentSidebar_Dir}
    ${InstrumentFamousWorks_Dir}
    ${InstrumentInfo_Dir}
    ${InstrumentRegister_Dir}
    ${InstrumentTechniques_Dir}
    ${InstrumentHeading_Dir}
    ${InstrumentRanges_Dir}
    ${OrchestraEditor_Dir}
    ${Sampler_Dir}
    ${NotationRenderer_Dir}
    ${Helper_Dir}
    ${FamilySwitcher_Dir}
    ${InstrumentDetail_Dir}
    ${TabBar_Dir}
    ${Overview_Dir}
)

set(Custom_Files
    ${Custom_Dir}/CustomComponent.h         ${Custom_Dir}/CustomComponent.cpp
    ${Custom_Dir}/CustomLookAndFeel.h       ${Custom_Dir}/CustomLookAndFeel.cpp
    ${Custom_Dir}/OrchestraPanel.h          ${Custom_Dir}/OrchestraPanel.cpp
)

set(PianoRoll_Files
    ${PianoRoll_Dir}/PianoRoll.h            ${PianoRoll_Dir}/PianoRoll.cpp
    ${PianoRoll_Dir}/CustomPianoRoll.h      ${PianoRoll_Dir}/CustomPianoRoll.cpp
    ${PianoRoll_Dir}/CcConfig.h
    ${PianoRoll_Dir}/MidiCcGutter.h         ${PianoRoll_Dir}/MidiCcGutter.cpp
    ${PianoRoll_Dir}/PianoRollWithCc.h      ${PianoRoll_Dir}/PianoRollWithCc.cpp
)

set(HeaderBar_Files
    ${HeaderBar_Dir}/HeaderBar.h            ${HeaderBar_Dir}/HeaderBar.cpp
)

set(InstrumentSidebar_Files
    ${InstrumentSidebar_Dir}/InstrumentSidebar.h    ${InstrumentSidebar_Dir}/InstrumentSidebar.cpp
)

set(InstrumentFamousWorks_Files
    ${InstrumentFamousWorks_Dir}/FamousWorksPanel.h        ${InstrumentFamousWorks_Dir}/FamousWorksPanel.cpp
)

set(InstrumentInfo_Files
    ${InstrumentInfo_Dir}/RolesPanel.h              ${InstrumentInfo_Dir}/RolesPanel.cpp
)

set(InstrumentRegisters_Files
    ${InstrumentRegister_Dir}/RegisterPanel.h          ${InstrumentRegister_Dir}/RegisterPanel.cpp
)

set(InstrumentTechniques_Files
    ${InstrumentTechniques_Dir}/TechniquesPanel.h         ${InstrumentTechniques_Dir}/TechniquesPanel.cpp
)

set(InstrumentHeading_Files
    ${InstrumentHeading_Dir}/InstrumentHeaderPanel.h   ${InstrumentHeading_Dir}/InstrumentHeaderPanel.cpp
)

set(InstrumentRanges_Files
    ${InstrumentRanges_Dir}/RangesPanel.h                  ${InstrumentRanges_Dir}/RangesPanel.cpp
)

set(OrchestraEditor_Files
    ${OrchestraEditor_Dir}/PluginEditor.h           ${OrchestraEditor_Dir}/PluginEditor.cpp
)

set(Sampler_Files
    ${Sampler_Dir}/SamplerPanel.h         ${Sampler_Dir}/SamplerPanel.cpp
)

set(NotationRenderer_Files
    ${NotationRenderer_Dir}/NotationRenderer.h          ${NotationRenderer_Dir}/NotationRenderer.cpp
    ${NotationRenderer_Dir}/NotationComponent.h         ${NotationRenderer_Dir}/NotationComponent.cpp
)

set(Helper_Files
    ${Helper_Dir}/CreateEditor.cpp
)

set(FamilySwitcher_Files
    ${FamilySwitcher_Dir}/FamilySwitcherView.h    ${FamilySwitcher_Dir}/FamilySwitcherView.cpp
    ${FamilySwitcher_Dir}/FamilyCard.h            ${FamilySwitcher_Dir}/FamilyCard.cpp
)

set(InstrumentDetail_Files
    ${InstrumentDetail_Dir}/InstrumentDetailView.h    ${InstrumentDetail_Dir}/InstrumentDetailView.cpp
)

set(TabBar_Files
    ${TabBar_Dir}/TabBar.h            ${TabBar_Dir}/TabBar.cpp
)

set(Overview_Files
    ${Overview_Dir}/OverviewPanel.h       ${Overview_Dir}/OverviewPanel.cpp
    ${Overview_Dir}/QualitiesPanel.h      ${Overview_Dir}/QualitiesPanel.cpp
)

set(UI_PROJECT_FILES
    ${Custom_Files}
    ${PianoRoll_Files}
    ${HeaderBar_Files}
    ${InstrumentSidebar_Files}
    ${InstrumentFamousWorks_Files}
    ${InstrumentInfo_Files}
    ${InstrumentRegisters_Files}
    ${InstrumentTechniques_Files}
    ${InstrumentHeading_Files}
    ${InstrumentRanges_Files}
    ${OrchestraEditor_Files}
    ${Sampler_Files}
    ${NotationRenderer_Files}
    ${Helper_Files}
    ${FamilySwitcher_Files}
    ${InstrumentDetail_Files}
    ${TabBar_Files}
    ${Overview_Files}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UI_PROJECT_FILES})


juce_add_binary_data(TextFontData
    NAMESPACE TextFontData
    HEADER_NAME  TextFontData
    SOURCES ${ASSETS_DIR}/Font/Source-Serif-4/SourceSerif4-Regular.ttf
)

juce_add_binary_data(NotationFontData
    NAMESPACE NotationFontData
    HEADER_NAME  NotationFontData
    SOURCES ${ASSETS_DIR}/Font/Bravura/Bravura.otf
)


add_library(${TARGET_NAME} STATIC ${UI_PROJECT_FILES})


if(ENABLE_CPPCHECK)
	AddCppCheck(${TARGET_NAME})
endif()

if(ENABLE_FORMAT)
	Format(${TARGET_NAME} ${ALL_PROJECT_DIRS})
endif()

if(ENABLE_DOXYGEN)
	Doxygen(The_Orchestra ${SOURCE_DIR})
endif()


target_include_directories(${TARGET_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${ALL_PROJECT_DIRS}
)

include(ProjectOptions)
set_common_target_options(${TARGET_NAME})


set (PROJECT_LIBS       TheOrchestraCore
                        TextFontData
                        NotationFontData
                        juce::juce_gui_basics
                        juce::juce_gui_extra
                        juce::juce_audio_utils
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )

target_include_directories(${TARGET_NAME} PRIVATE
    $<TARGET_PROPERTY:TextFontData,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:NotationFontData,INTERFACE_INCLUDE_DIRECTORIES>
)
