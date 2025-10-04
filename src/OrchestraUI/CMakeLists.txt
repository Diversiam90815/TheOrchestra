set(TARGET_NAME TheOrchestraUI)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (CustomComponent_Dir        ${CMAKE_CURRENT_SOURCE_DIR}/CustomComponent )
set (PianoRoll_Dir              ${CMAKE_CURRENT_SOURCE_DIR}/PianoRoll )
set (CustomLookAndFeel_Dir      ${CMAKE_CURRENT_SOURCE_DIR}/CustomLookAndFeel )
set (CustomMenuBar_Dir          ${CMAKE_CURRENT_SOURCE_DIR}/CustomMenuBar )
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
    ${CustomComponent_Dir}
    ${PianoRoll_Dir}
    ${CustomLookAndFeel_Dir}
    ${CustomMenuBar_Dir}
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

set(CustomComponent_Files
    ${CustomComponent_Dir}/CustomComponent.h         ${CustomComponent_Dir}/CustomComponent.cpp
)

set(PianoRoll_Files
    ${PianoRoll_Dir}/PianoRoll.h            ${PianoRoll_Dir}/PianoRoll.cpp
    ${PianoRoll_Dir}/CustomPianoRoll.h            ${PianoRoll_Dir}/CustomPianoRoll.cpp
)

set(CustomLookAndFeel_Files
    ${CustomLookAndFeel_Dir}/CustomLookAndFeel.h       ${CustomLookAndFeel_Dir}/CustomLookAndFeel.cpp
)

set(CustomMenuBar_Dir
    ${CustomMenuBar_Dir}/CustomMenuBar.h            ${CustomMenuBar_Dir}/CustomMenuBar.cpp
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
    ${CustomComponent_Files}
    ${PianoRoll_Files}
    ${CustomLookAndFeel_Files}
    ${CustomMenuBar_Dir}
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
	Format(${TARGET_NAME} .)
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

target_compile_definitions(${TARGET_NAME} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
	    JUCE_USE_WINDOWS_MEDIA_FORMAT=1
        JUCE_LOAD_CURL_SYMBOLS_LAZILY=1
        JUCE_WASAPI=1
        JUCE_DIRECTSOUND=1
        JUCE_ASIO=0
        JUCE_USE_ANDROID_OBOE=1
        JUCE_USE_OBOE_STABILIZED_CALLBACK=1
        JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1

        -DENV_DEVELOPMENT
        _CRT_SECURE_NO_WARNINGS

        "$<$<CONFIG:Debug>:"
                "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
                "NDEBUG"
        ">"
)

target_compile_options(${TARGET_NAME} 
    PRIVATE
        $<$<CONFIG:Release>:
                /Oi;
                /Gy
        >
        $<$<CONFIG:Debug>:
                /Od;
                /Z7
        >
        /sdl
        /MP
        /WX-        # Don't treat warnings as errors
        /wd4146     # Suppress warning C4146
        /wd4996     # Suppress warning C4996
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)

set (PROJECT_LIBS       TheOrchestraCore 
                        FontBinaryData
                        juce::juce_gui_basics
                        juce::juce_gui_extra
                        juce::juce_audio_utils
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )
