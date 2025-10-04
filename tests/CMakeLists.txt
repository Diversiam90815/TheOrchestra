include(Testing)

set(SamplerTest_Files
    SamplerTest/SamplerTest.cpp
    SamplerTest/SampleManagementTest.cpp
    SamplerTest/OrchestraSoundTest.cpp
    SamplerTest/OrchestraVoiceTest.cpp
    SamplerTest/SamplerIntegrationTest.cpp
)


set(InstrumentTest_Files
    InstrumentTest/InstrumentControllerTest.cpp
)

set(Test_Files
    ${SamplerTest_Files}
    ${InstrumentTest_Files}
)

source_group("Sampler Tests" FILES ${SamplerTest_Files})
source_group("InstrumentTests" FILES ${InstrumentTest_Files})


add_executable(TheOrchestra.Tests ${Test_Files})

target_link_libraries(TheOrchestra.Tests PRIVATE TheOrchestraCore)


target_compile_definitions(TheOrchestra.Tests 
    PUBLIC
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

AddTests(TheOrchestra.Tests)
