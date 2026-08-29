set(TARGET_NAME TheOrchestraPlugin)

set(PLUGIN_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/PluginEntry.cpp)

source_group("Plugin" FILES ${PLUGIN_FILES})

juce_add_plugin(${TARGET_NAME}
    COMPANY_NAME                "DiversiamProduction"
    PLUGIN_MANUFACTURER_CODE    Dvsm
    PLUGIN_CODE                 Ioto
    FORMATS                     VST3
    IS_SYNTH                    TRUE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD     FALSE
    VST3_CATEGORIES             "Instrument" "Sampler"
    PRODUCT_NAME                "The Orchestra"
    ICON_BIG                    ${PROJECT_SOURCE_DIR}/Assets/Logo/TheOrchestraLogo.png
)

target_sources(${TARGET_NAME} PRIVATE ${PLUGIN_FILES})

target_link_libraries(${TARGET_NAME}
    PRIVATE
        TheOrchestraCore
        TheOrchestraUI
        juce::juce_audio_plugin_client
)

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set_common_target_options(${TARGET_NAME})

if(ENABLE_CPPCHECK)
	AddCppCheck(${TARGET_NAME})
endif()

if(ENABLE_FORMAT)
	Format(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
endif()

include(GNUInstallDirs)

if(TARGET ${TARGET_NAME}_VST3)
    install(DIRECTORY "$<GENEX_EVAL:$<TARGET_PROPERTY:${TARGET_NAME}_VST3,JUCE_PLUGIN_ARTEFACT_FILE>>"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/VST3
            COMPONENT   VST3)
endif()
