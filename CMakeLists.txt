###########################################
#   The Orchestra
#       by Jens W. Langenberg
###########################################

cmake_minimum_required(VERSION 3.25)

set(ORCHESTRA_VERSION 2.0.183)

project(TheOrchestra VERSION ${ORCHESTRA_VERSION} LANGUAGES CXX)



###########################################
#   PROJECT SETTINGS
###########################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")


###########################################
#   DIRECTORIES
###########################################

set (CMAKE_INSTALL_PREFIX   ${PROJECT_BINARY_DIR})

set (SOURCE_FILES_DIR       ${PROJECT_SOURCE_DIR}/src)
set (SUBMODULES_DIR         ${PROJECT_SOURCE_DIR}/submodules)
set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets")

set (INSTRUMENT_DIR         ${SOURCE_FILES_DIR}/InstrumentInfo )
set (PROCESSOR_DIR          ${SOURCE_FILES_DIR}/AudioProcessor )
set (VIEW_DIR               ${SOURCE_FILES_DIR}/Views )
set (PIANOROLL_DIR          ${SOURCE_FILES_DIR}/PianoRoll )
set (SAMPLER_DIR            ${SOURCE_FILES_DIR}/Sampler )
set (MISC_DIR               ${SOURCE_FILES_DIR}/Misc )
set (FILE_MANAGER_DIR       ${SOURCE_FILES_DIR}/FileManager)
set (APP_DIR                ${SOURCE_FILES_DIR}/App)
set (LOGGER_DIR             ${SOURCE_FILES_DIR}/Logger)

set(ALL_PROJECT_DIRS
    ${INSTRUMENT_DIR}
    ${PROCESSOR_DIR}
    ${VIEW_DIR}
    ${PIANOROLL_DIR}
    ${SAMPLER_DIR}
    ${MISC_DIR}
    ${FILE_MANAGER_DIR}
    ${APP_DIR}
    ${LOGGER_DIR}
)


###########################################
#   PROJECT FILES
###########################################

set(INSTRUMENT_FILES
    ${INSTRUMENT_DIR}/InstrumentInfo.h
    ${INSTRUMENT_DIR}/InstrumentController.h    ${INSTRUMENT_DIR}/InstrumentController.cpp
)

set(SAMPLER_FILES
    ${SAMPLER_DIR}/Sampler.h                ${SAMPLER_DIR}/Sampler.cpp
    ${SAMPLER_DIR}/SamplesManagement.h      ${SAMPLER_DIR}/SamplesManagement.cpp
    ${SAMPLER_DIR}/OrchestraSound.h         ${SAMPLER_DIR}/OrchestraSound.cpp
    ${SAMPLER_DIR}/OrchestraVoice.h         ${SAMPLER_DIR}/OrchestraVoice.cpp
)

set(PROCESSOR_FILES
    ${PROCESSOR_DIR}/PluginProcessor.h    ${PROCESSOR_DIR}/PluginProcessor.cpp
)

set(VIEW_FILES
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

set(MISC_FILES
    ${MISC_DIR}/Parameters.h
    ${MISC_DIR}/Helper.h
)

set(FILE_MANAGER_FILES
    ${FILE_MANAGER_DIR}/FileManager.h    ${FILE_MANAGER_DIR}/FileManager.cpp
)

set(APP_FILES
    ${APP_DIR}/Main.cpp
)

set(LOGGER_FILES
    ${LOGGER_DIR}/Logging.h      ${LOGGER_DIR}/Logging.cpp
)

set(ALL_PROJECT_FILES
    ${INSTRUMENT_FILES}
    ${SAMPLER_FILES}
    ${PROCESSOR_FILES}
    ${VIEW_FILES}
    ${PIANOROLL_FILES}
    ${MISC_FILES}
    ${FILE_MANAGER_FILES}
    ${APP_FILES}
    ${LOGGER_FILES}
)



###########################################
#   SOURCE GROUPS
###########################################

source_group("Instruments"      FILES ${INSTRUMENT_FILES})
source_group("Sampler"          FILES ${SAMPLER_FILES})
source_group("Processor"        FILES ${PROCESSOR_FILES})
source_group("Piano Roll"       FILES ${PIANOROLL_FILES})
source_group("Views"            FILES ${VIEW_FILES})
source_group("Misc"             FILES ${MISC_FILES})
source_group("File Manager"     FILES ${FILE_MANAGER_FILES})
source_group("App"              FILES ${APP_FILES})
source_group("Logger"           FILES ${LOGGER_FILES})



###########################################
#   SUBMODULES
###########################################


#   Juce API

add_subdirectory(submodules/JUCE)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "DiversiamProduction"
    PLUGIN_MANUFACTURER_CODE 3160
    PLUGIN_CODE IOTO
    FORMATS Standalone
    PRODUCT_NAME ${PROJECT_NAME}
    ICON_BIG ${ASSETS_DIR}/Logo/TheOrchestraLogo.png
)

juce_generate_juce_header(${PROJECT_NAME})



#   Logger

add_subdirectory(submodules/Logger)



target_sources(${PROJECT_NAME} PRIVATE ${ALL_PROJECT_FILES} )



###########################################
#   BINARY DATA
###########################################

juce_add_binary_data(FontBinaryData
    SOURCES ${ASSETS_DIR}/Font/Instrument-Serif/InstrumentSerif-Regular.ttf
)



###########################################
#   TARGET INCLUDE DIRECTORIES
###########################################

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${ALL_PROJECT_DIRS}
        ${SUBMODULES_DIR}/Logger/include
)



###########################################
#   TARGET PROPERTIES
###########################################

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
)



###########################################
#   TARGET COMPILE DEFINITIONS
###########################################


target_compile_definitions(${PROJECT_NAME} PUBLIC
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


target_compile_options(${PROJECT_NAME} 
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



###########################################
#   TARGET LINK LIBRARIES
###########################################

set (PROJECT_LIBS juce::juce_audio_utils
                  juce::juce_audio_plugin_client
                  juce::juce_core
                  FontBinaryData
                  Logger
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBS} )



###########################################
#   POST BUILD COMMAND
###########################################

 add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
         "${ASSETS_DIR}"
         "${ASSETS_DEST_DIR}"
     COMMENT "Copying Assets directory to output directory"
 )
