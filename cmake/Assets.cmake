set(ORCHESTRA_ASSETS_DIR ${PROJECT_SOURCE_DIR}/Assets)

function(copy_assets_to_target target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${ORCHESTRA_ASSETS_DIR}/Images
        "$<TARGET_FILE_DIR:${target}>/Assets/Images"
        COMMENT "Copying Images to ${target} build directory..."
    )
endfunction()
