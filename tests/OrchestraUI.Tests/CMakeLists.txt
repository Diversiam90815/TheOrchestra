include(Testing)

set(TARGET_NAME OrchestraUI.Tests)

set(Test_Files
    # No test sources yet - add them here as they're written.
)

if(Test_Files)
    add_executable(${TARGET_NAME} ${Test_Files})

    target_link_libraries(${TARGET_NAME} PRIVATE TheOrchestraUI)

    target_compile_definitions(${TARGET_NAME}
        PUBLIC
            JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    )

    AddTests(${TARGET_NAME})
else()
    message(STATUS "Skipping ${TARGET_NAME}: no test sources defined yet")
endif()
