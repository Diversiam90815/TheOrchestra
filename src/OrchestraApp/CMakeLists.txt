set(TARGET_NAME TheOrchestraApp)

set(ASSETS_DIR             ${PROJECT_SOURCE_DIR}/Assets)

set(APP_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)

source_group("App"              FILES ${APP_FILES})


juce_add_gui_app(${TARGET_NAME}
    COMPANY_NAME "DiversiamProduction"
    PRODUCT_NAME ${TARGET_NAME}
    ICON_BIG ${ASSETS_DIR}/Logo/TheOrchestraLogo.png
)

juce_generate_juce_header(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${APP_FILES} )

if(ENABLE_CPPCHECK)
	AddCppCheck(${TARGET_NAME})
endif()

if(ENABLE_FORMAT)
	Format(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(ENABLE_DOXYGEN)
	Doxygen(TheOrchestraApp ${CMAKE_CURRENT_SOURCE_DIR})
endif()

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set_common_target_options(${TARGET_NAME})

set (PROJECT_LIBS   TheOrchestraCore 
                    TheOrchestraUI
)

target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_LIBS} )

include(Assets)
copy_assets_to_target(${TARGET_NAME})

include(GNUInstallDirs)

install(TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  
    BUNDLE  DESTINATION .                        
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  
)

install(DIRECTORY ${ASSETS_DIR}/
    DESTINATION ${CMAKE_INSTALL_BINDIR}/Assets
)
