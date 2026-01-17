function(set_common_target_options target)
    target_compile_definitions(${target} PUBLIC
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

        ENV_DEVELOPMENT
        _CRT_SECURE_NO_WARNINGS

        "$<$<CONFIG:Debug>:_DEBUG>"
        "$<$<CONFIG:Release>:NDEBUG>"
    )

    target_compile_options(${target}
        PRIVATE
            $<$<CONFIG:Release>:/Oi;/Gy>
            $<$<CONFIG:Debug>:/Od;/Z7>
            /sdl
            /MP
            /WX-
            /wd4146
            /wd4996
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
endfunction()
