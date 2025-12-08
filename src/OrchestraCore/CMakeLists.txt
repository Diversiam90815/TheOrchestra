set(TARGET_NAME TheOrchestraCore)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)
set (ASSETS_DEST_DIR        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets")

set (INSTRUMENT_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/InstrumentInfo )
set (PROCESSOR_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/AudioProcessor )
set (SAMPLER_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/Sampler )
set (MISC_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/Misc )
set (FILE_MANAGER_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/FileManager)
set (LOGGER_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/Logger)
set (CORE_MANAGER_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/CoreManager)
set (USER_CONFIG_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/UserConfig)


set(ALL_PROJECT_DIRS
    ${INSTRUMENT_DIR}
    ${PROCESSOR_DIR}
    ${SAMPLER_DIR}
    ${MISC_DIR}
    ${FILE_MANAGER_DIR}
    ${LOGGER_DIR}
    ${CORE_MANAGER_DIR}
    ${USER_CONFIG_DIR}
)

set(INSTRUMENT_FILES
    ${INSTRUMENT_DIR}/InstrumentInfo.h
    ${INSTRUMENT_DIR}/InstrumentRange.h
    ${INSTRUMENT_DIR}/SignatureWork.h
    ${INSTRUMENT_DIR}/PlayingTechnique.h
    ${INSTRUMENT_DIR}/InstrumentRegister.h
    ${INSTRUMENT_DIR}/OrchestrationRole.h
    ${INSTRUMENT_DIR}/InstrumentController.h    ${INSTRUMENT_DIR}/InstrumentController.cpp
)

set(SAMPLER_FILES
    ${SAMPLER_DIR}/OrchestraSampler.h       ${SAMPLER_DIR}/OrchestraSampler.cpp
    ${SAMPLER_DIR}/SamplesManagement.h      ${SAMPLER_DIR}/SamplesManagement.cpp
    ${SAMPLER_DIR}/OrchestraSound.h         ${SAMPLER_DIR}/OrchestraSound.cpp
    ${SAMPLER_DIR}/OrchestraVoice.h         ${SAMPLER_DIR}/OrchestraVoice.cpp
)

set(PROCESSOR_FILES
    ${PROCESSOR_DIR}/PluginProcessor.h    ${PROCESSOR_DIR}/PluginProcessor.cpp
)

set(CORE_MANAGER_FILES
    ${CORE_MANAGER_DIR}/CoreManager.h    ${CORE_MANAGER_DIR}/CoreManager.cpp
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

set(USER_CONFIG_FILES
    ${USER_CONFIG_DIR}/UserConfig.h      ${USER_CONFIG_DIR}/UserConfig.cpp
)

set(CORE_PROJECT_FILES
    ${INSTRUMENT_FILES}
    ${SAMPLER_FILES}
    ${PROCESSOR_FILES}
    ${MISC_FILES}
    ${FILE_MANAGER_FILES}
    ${LOGGER_FILES}
    ${USER_CONFIG_FILES}
    ${CORE_MANAGER_FILES}
)


source_group("Instruments"      FILES ${INSTRUMENT_FILES})
source_group("Sampler"          FILES ${SAMPLER_FILES})
source_group("Processor"        FILES ${PROCESSOR_FILES})
source_group("Misc"             FILES ${MISC_FILES})
source_group("File Manager"     FILES ${FILE_MANAGER_FILES})
source_group("Logger"           FILES ${LOGGER_FILES})
source_group("Core Manager"     FILES ${CORE_MANAGER_FILES})
source_group("User Config"      FILES ${USER_CONFIG_FILES})


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
	Format(${TARGET_NAME} ${ALL_PROJECT_DIRS})
endif()

if(ENABLE_DOXYGEN)
	Doxygen(Chess_Engine ${SOURCE_DIR})
endif()


target_include_directories(${TARGET_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${ALL_PROJECT_DIRS}
)

include(ProjectOptions)
set_common_target_options(${TARGET_NAME})

juce_add_binary_data(InstrumentData
    NAMESPACE InstrumentData
    HEADER_NAME InstrumentData
    SOURCES ${ASSETS_DIR}/InstrumentData/Instruments.json
)

set (PROJECT_LIBS   juce::juce_audio_utils
                    juce::juce_audio_plugin_client
                    juce::juce_core
                    Logger
                    InstrumentData
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )


add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}/Samples
    "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets/Samples"
    COMMENT "Copying Samples to build directory..."
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}/Images
    "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets/Images"
    COMMENT "Copying Images to build directory..."
)
