include(Testing)

set(TARGET_NAME OrchestraUI.Tests)

set(LayoutTest_Files
    LayoutTest/GridFlowTest.cpp
)

set(NotationTest_Files
    NotationTest/NotationGeometryTest.cpp
)

set(Test_Files
    ${LayoutTest_Files}
    ${NotationTest_Files}
)

source_group("Layout Tests"     FILES ${LayoutTest_Files})
source_group("Notation Tests"   FILES ${NotationTest_Files})


add_executable(${TARGET_NAME} ${Test_Files})

target_link_libraries(${TARGET_NAME} PRIVATE TheOrchestraUI)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

AddTests(${TARGET_NAME})
