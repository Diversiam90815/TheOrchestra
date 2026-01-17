include(Testing)

set(TARGET_NAME OrchestraCore.Tests)

set(SamplerTest_Files
    SamplerTest/SamplerTest.cpp
    SamplerTest/SampleManagementTest.cpp
    SamplerTest/OrchestraSoundTest.cpp
    SamplerTest/OrchestraVoiceTest.cpp
    SamplerTest/SamplerIntegrationTest.cpp
)


set(InstrumentTest_Files
    InstrumentTest/InstrumentControllerTest.cpp
    InstrumentTest/InstrumentInfoTest.cpp
    InstrumentTest/HelperTest.cpp
)

set(FileManagerTest_Files
    FileManagerTest/FileManagerTest.cpp
)

set(CoreManagerTest_Files
    CoreManagerTest/CoreManagerTest.cpp
)


set(Test_Files
    ${SamplerTest_Files}
    ${InstrumentTest_Files}
    ${FileManagerTest_Files}
    ${CoreManagerTest_Files}
)


source_group("Sampler Tests"        FILES ${SamplerTest_Files})
source_group("Instrument Tests"     FILES ${InstrumentTest_Files})
source_group("File Manager Tests"   FILES ${FileManagerTest_Files})
source_group("Core Manager Tests"   FILES ${CoreManagerTest_Files})


add_executable(${TARGET_NAME} ${Test_Files})


target_link_libraries(${TARGET_NAME} PRIVATE TheOrchestraCore)


target_compile_definitions(${TARGET_NAME}
    PUBLIC
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

AddTests(${TARGET_NAME})
