set(TARGET_NAME TheOrchestraCore)

set (ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)

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
    ${SAMPLER_DIR}/SamplerStructs.h 
    ${SAMPLER_DIR}/SamplerEngine.h          ${SAMPLER_DIR}/SamplerEngine.cpp
    ${SAMPLER_DIR}/SampleCatalog.h          ${SAMPLER_DIR}/SampleCatalog.cpp
    ${SAMPLER_DIR}/SampleSound.h            ${SAMPLER_DIR}/SampleSound.cpp
    ${SAMPLER_DIR}/ArticulationVoice.h      ${SAMPLER_DIR}/ArticulationVoice.cpp
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
    VERSION 2.0.86
)

CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.12.0
    OPTIONS
        "JSON_Install OFF"
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
	Doxygen(TheOrchestraCore ${CMAKE_CURRENT_SOURCE_DIR})
endif()


target_include_directories(${TARGET_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${ALL_PROJECT_DIRS}
)

set_common_target_options(${TARGET_NAME})

juce_add_binary_data(InstrumentData
    NAMESPACE InstrumentData
    HEADER_NAME InstrumentData
    SOURCES ${ASSETS_DIR}/InstrumentData/Instruments.json
)

set (PROJECT_LIBS   juce::juce_audio_utils
                    juce::juce_core
                    Logger
                    nlohmann_json::nlohmann_json
                    InstrumentData
)

target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_LIBS} )
