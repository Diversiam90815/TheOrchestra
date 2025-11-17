include(Testing)

set(TARGET_NAME OrchestraUI.Tests)

add_executable(${TARGET_NAME} ${Test_Files})

target_link_libraries(${TARGET_NAME} PRIVATE TheOrchestraUI)

target_compile_definitions(${TARGET_NAME} 
    PUBLIC
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

AddTests(${TARGET_NAME})
