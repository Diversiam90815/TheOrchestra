set(ORCHESTRA_ASSETS_DIR ${PROJECT_SOURCE_DIR}/Assets)

# Copies the Samples and Images asset folders next to the given executable target's build output,
# so it can locate them at runtime via FileManager without needing an install step.
function(copy_assets_to_target target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ORCHESTRA_ASSETS_DIR}/Samples
        "$<TARGET_FILE_DIR:${target}>/Assets/Samples"
        COMMENT "Copying Samples to ${target} build directory..."
    )

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ORCHESTRA_ASSETS_DIR}/Images
        "$<TARGET_FILE_DIR:${target}>/Assets/Images"
        COMMENT "Copying Images to ${target} build directory..."
    )
endfunction()
