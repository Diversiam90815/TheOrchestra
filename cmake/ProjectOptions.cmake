function(set_common_target_options target)
    target_compile_definitions(${target} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=1
        JUCE_LOAD_CURL_SYMBOLS_LAZILY=1
        JUCE_WASAPI=1
        JUCE_DIRECTSOUND=1
        JUCE_ASIO=$<BOOL:${ENABLE_ASIO}>

        "$<$<CONFIG:Debug>:_DEBUG>"
        "$<$<CONFIG:Release>:NDEBUG>"
    )

    # ASIO needs the SDK headers on the include path; JUCE picks them up from there.
    if(ENABLE_ASIO)
        if(NOT ASIO_SDK_PATH OR NOT EXISTS "${ASIO_SDK_PATH}/common/iasiodrv.h")
            message(FATAL_ERROR "ENABLE_ASIO is ON but ASIO_SDK_PATH does not point at an ASIO SDK: ${ASIO_SDK_PATH}")
        endif()

        target_include_directories(${target} PUBLIC "${ASIO_SDK_PATH}/common")
    endif()

    if(MSVC)
        target_compile_definitions(${target} PUBLIC _CRT_SECURE_NO_WARNINGS)

        target_compile_options(${target}
            PRIVATE
                $<$<CONFIG:Release>:/Oi;/Gy>
                $<$<CONFIG:Debug>:/Od;/Z7>
                /sdl        # additional security checks
                /MP         # parallel compilation
                /wd4146     # unary minus on unsigned type (JUCE / nlohmann)
                /wd4996     # deprecated CRT functions
        )
    else()
        target_compile_options(${target}
            PRIVATE
                $<$<CONFIG:Release>:-O2>
                $<$<CONFIG:Debug>:-O0;-g>
                -Wall
                -Wextra
                -Wno-unused-parameter
        )
    endif()
endfunction()
