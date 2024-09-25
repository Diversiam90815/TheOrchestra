cmake_minimum_required(VERSION 3.25)

project(InstrumentsOfTheOrchestra VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

# Allow folders in Visual Studio solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set (SOURCE_FILES_DIR ${PROJECT_SOURCE_DIR}/Source/)
set (SUBMODULES_DIR ${PROJECT_SOURCE_DIR}/submodules/)
set(ASSETS_DIR ${PROJECT_SOURCE_DIR}/Assets)
set(ASSETS_DEST_DIR "$<TARGET_FILE_DIR:InstrumentsOfTheOrchestra>/Assets")

# Project info
#configure_file(Project.h.in Project.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(Header_Files
        ${SOURCE_FILES_DIR}/CustomLookAndFeel.h
        ${SOURCE_FILES_DIR}/CustomPianoRoll.h
        ${SOURCE_FILES_DIR}/InstrumentData.h
        ${SOURCE_FILES_DIR}/InstrumentInfo.h
        ${SOURCE_FILES_DIR}/InstrumentInfoModel.h
        ${SOURCE_FILES_DIR}/InstrumentInfoView.h
        ${SOURCE_FILES_DIR}/Parameters.h
        ${SOURCE_FILES_DIR}/PianoRoll.h
        ${SOURCE_FILES_DIR}/PluginEditor.h
        ${SOURCE_FILES_DIR}/PluginProcessor.h
        ${SOURCE_FILES_DIR}/Sampler.h
        ${SOURCE_FILES_DIR}/SamplesManagement.h
)

set(Source_Files
        ${SOURCE_FILES_DIR}/CustomLookAndFeel.cpp
        ${SOURCE_FILES_DIR}/CustomPianoRoll.cpp

        ${SOURCE_FILES_DIR}/InstrumentInfo.cpp
        ${SOURCE_FILES_DIR}/InstrumentInfoModel.cpp
        ${SOURCE_FILES_DIR}/InstrumentInfoView.cpp

        ${SOURCE_FILES_DIR}/PianoRoll.cpp
        ${SOURCE_FILES_DIR}/PluginEditor.cpp
        ${SOURCE_FILES_DIR}/PluginProcessor.cpp
        ${SOURCE_FILES_DIR}/Sampler.cpp
        ${SOURCE_FILES_DIR}/SamplesManagement.cpp
)

source_group("Source Files" FILES ${Source_Files})


#-----------------------------------------------------------------------------------------
# Juce API
#-----------------------------------------------------------------------------------------

add_subdirectory(submodules/JUCE)

# Add the plugin target
juce_add_plugin(InstrumentsOfTheOrchestra
    COMPANY_NAME "DiversiamProduction"
    PLUGIN_MANUFACTURER_CODE 3160
    PLUGIN_CODE IOTO
    FORMATS Standalone
    PRODUCT_NAME "Instruments Of The Orchestra"
)

# Generate the JuceHeader.h
juce_generate_juce_header(InstrumentsOfTheOrchestra)



set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

target_sources(${PROJECT_NAME} PRIVATE  
        ${ALL_FILES} 
)


target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "Instruments Of The Orchestra"
)


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
        -DENV_DEVELOPMENT
        _CRT_SECURE_NO_WARNINGS
)


# Suppress specific compiler warnings
target_compile_options(InstrumentsOfTheOrchestra PRIVATE
    /wd4146  # Suppress warning C4146
    /wd4996  # Suppress warning C4996
)


set (PROJECT_LIBS juce::juce_audio_utils
                  juce::juce_audio_plugin_client
                  juce::juce_core
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBS} )


target_compile_options(${PROJECT_NAME} PRIVATE
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
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)

add_custom_command(TARGET InstrumentsOfTheOrchestra POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_DIR}"
        "${ASSETS_DEST_DIR}"
    COMMENT "Copying Assets directory to output directory"
)