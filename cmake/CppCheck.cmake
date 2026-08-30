function(AddCppCheck target)
  find_program(CPPCHECK_PATH cppcheck)

  if(NOT CPPCHECK_PATH)
    message(WARNING "ENABLE_CPPCHECK is ON but cppcheck was not found on PATH - skipping static analysis for ${target}.")
    return()
  endif()

  set_target_properties(${target}
    PROPERTIES CXX_CPPCHECK
    "${CPPCHECK_PATH};--enable=warning;--error-exitcode=1;-D__GNUC__=13;-D__GNUC_MINOR__=3;--suppress=*:*/libs/cpm-cache/*"
  )
endfunction()
