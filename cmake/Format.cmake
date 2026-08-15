function(Format target directory)
  find_program(CLANG-FORMAT_PATH clang-format)

  if(NOT CLANG-FORMAT_PATH)
    message(WARNING "ENABLE_FORMAT is ON but clang-format was not found on PATH - skipping formatting for ${target}.")
    return()
  endif()

  set(EXPRESSION h hpp hh c cc cxx cpp)
  list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
  file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
       LIST_DIRECTORIES false ${EXPRESSION}
  )
  add_custom_command(TARGET ${target} PRE_BUILD COMMAND
    ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES}
  )
endfunction()
