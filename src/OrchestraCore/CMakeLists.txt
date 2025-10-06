set(TARGET_NAME TheOrchestraCore)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (INSTRUMENT_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentInfo )
set (PROCESSOR_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/AudioProcessor )
set (SAMPLER_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/Sampler )
set (MISC_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/Misc )
set (FILE_MANAGER_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/FileManager)
set (APP_DIR                ${CMAKE_CURRENT_SOURCE_DIR}/App)
set (LOGGER_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/Logger)

# TODO: Create CoreManager

set(ALL_PROJECT_DIRS
    ${INSTRUMENT_DIR}
    ${PROCESSOR_DIR}
    ${SAMPLER_DIR}
    ${VIEW_DIR}
    ${MISC_DIR}
    ${FILE_MANAGER_DIR}
    ${APP_DIR}
    ${LOGGER_DIR}
)

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

set(MISC_FILES
    ${MISC_DIR}/JuceIncludes.h
    ${MISC_DIR}/Parameters.h
    ${MISC_DIR}/Helper.h
)

set(FILE_MANAGER_FILES
    ${FILE_MANAGER_DIR}/FileManager.h    ${FILE_MANAGER_DIR}/FileManager.cpp
)

set(LOGGER_FILES
    ${LOGGER_DIR}/Logging.h      ${LOGGER_DIR}/Logging.cpp
)

set(CORE_PROJECT_FILES
    ${INSTRUMENT_FILES}
    ${SAMPLER_FILES}
    ${PROCESSOR_FILES}
    ${MISC_FILES}
    ${FILE_MANAGER_FILES}
    ${LOGGER_FILES}
)


source_group("Instruments"      FILES ${INSTRUMENT_FILES})
source_group("Sampler"          FILES ${SAMPLER_FILES})
source_group("Processor"        FILES ${PROCESSOR_FILES})
source_group("Misc"             FILES ${MISC_FILES})
source_group("File Manager"     FILES ${FILE_MANAGER_FILES})
source_group("Logger"           FILES ${LOGGER_FILES})


CPMAddPackage(
  NAME Logger
  GITHUB_REPOSITORY Diversiam90815/Logger
  VERSION 1.3.81
)

CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG 8.0.3
        VERSION 8.0.3
)

add_library(${TARGET_NAME} STATIC ${CORE_PROJECT_FILES})

include(BuildInfo)
BuildInfo(${TARGET_NAME})

if(ENABLE_CPPCHECK)
	AddCppCheck(${TARGET_NAME})
endif()

if(ENABLE_FORMAT)
	Format(${TARGET_NAME} .)
endif()

if(ENABLE_DOXYGEN)
	Doxygen(Chess_Engine ${SOURCE_DIR})
endif()


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

set (PROJECT_LIBS   juce::juce_audio_utils
                    juce::juce_audio_plugin_client
                    juce::juce_core
                    Logger
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )

# TODO: Only copy if different
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_DIR}"
        "${ASSETS_DEST_DIR}"
    COMMENT "Copying Assets directory to output directory"
)
