set(TARGET_NAME TheOrchestraUI)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (VIEW_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/Views )
set (PIANOROLL_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/PianoRoll )

set(ALL_PROJECT_DIRS
    ${VIEW_DIR}
    ${PIANOROLL_DIR}
)

set(VIEW_FILES
    ${VIEW_DIR}/CreateEditor.cpp
    ${VIEW_DIR}/PluginEditor.h            ${VIEW_DIR}/PluginEditor.cpp
    ${VIEW_DIR}/CustomLookAndFeel.h       ${VIEW_DIR}/CustomLookAndFeel.cpp
    ${VIEW_DIR}/CustomComponent.h         ${VIEW_DIR}/CustomComponent.cpp
    ${VIEW_DIR}/InstrumentView.h          ${VIEW_DIR}/InstrumentView.cpp
    ${VIEW_DIR}/FamousWorksView.h         ${VIEW_DIR}/FamousWorksView.cpp
    ${VIEW_DIR}/InformationView.h         ${VIEW_DIR}/InformationView.cpp
    ${VIEW_DIR}/InstrumentRangesView.h    ${VIEW_DIR}/InstrumentRangesView.cpp
    ${VIEW_DIR}/QualitiesView.h           ${VIEW_DIR}/QualitiesView.cpp
    ${VIEW_DIR}/TechniquesView.h          ${VIEW_DIR}/TechniquesView.cpp
    ${VIEW_DIR}/SamplerView.h             ${VIEW_DIR}/SamplerView.cpp
    ${VIEW_DIR}/CustomMenuBar.h           ${VIEW_DIR}/CustomMenuBar.cpp
)

set(PIANOROLL_FILES
    ${PIANOROLL_DIR}/PianoRoll.h            ${PIANOROLL_DIR}/PianoRoll.cpp
    ${PIANOROLL_DIR}/CustomPianoRoll.h      ${PIANOROLL_DIR}/CustomPianoRoll.cpp
)

set(UI_PROJECT_FILES
    ${VIEW_FILES}
    ${PIANOROLL_FILES}
)

source_group("Views"            FILES ${VIEW_FILES})
source_group("Piano Roll"       FILES ${PIANOROLL_FILES})


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
