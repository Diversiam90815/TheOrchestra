include(cpm)

find_package(Doxygen REQUIRED)

CPMAddPackage(
        GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
        GIT_TAG        v2.3.1
        )

function(Doxygen target input)
  set(NAME "doxygen-${target}")
  set(DOXYGEN_GENERATE_HTML       YES)
  set(DOXYGEN_OUTPUT_DIRECTORY    "${PROJECT_BINARY_DIR}/doxygen")
  set(DOXYGEN_HTML_OUTPUT         "html") 
  set(DOXYGEN_SEARCH_INCLUDES     NO)
  set(DOXYGEN_FULL_PATH_NAMES     YES)
  set(DOXYGEN_SHOW_DIRECTORIES    YES)
  set(DOXYGEN_DISABLE_INDEX       NO)
  set(DOXYGEN_EXCLUDE
      "${PROJECT_SOURCE_DIR}/submodule"
      "${PROJECT_SOURCE_DIR}/libs"
      "${PROJECT_BINARY_DIR}"
  )
  set(DOXYGEN_EXCLUDE_PATTERNS
      "**/_deps/**"
      "**/libs/**"
      "**/submodule/**"
      "**/external/**"
      "**/third_party/**"
      "**/build/**"
  )

  UseDoxygenAwesomeCss()
  UseDoxygenAwesomeExtensions()

  doxygen_add_docs("doxygen-${target}"
      ${input}
      COMMENT "Generate HTML documentation for ${target}"
  )

  message(STATUS "Doxygen: ${DOXYGEN_OUTPUT_DIRECTORY}/html/index.html")
endfunction()

macro(UseDoxygenAwesomeCss)

  set(DOXYGEN_GENERATE_TREEVIEW     YES)
  set(DOXYGEN_HAVE_DOT              NO)
  set(DOXYGEN_DOT_IMAGE_FORMAT      svg)
  set(DOXYGEN_DOT_TRANSPARENT       YES)
  set(DOXYGEN_HTML_EXTRA_STYLESHEET
      ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css)
endmacro()

macro(UseDoxygenAwesomeExtensions)
  set(DOXYGEN_HTML_EXTRA_FILES
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-paragraph-link.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-interactive-toc.js
  )

  execute_process(COMMAND doxygen -w html header.html footer.html style.css
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
  execute_process(COMMAND sed -i "/<\\/head>/r ${PROJECT_SOURCE_DIR}/cmake/doxygen_extra_headers" header.html
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
  set(DOXYGEN_HTML_HEADER ${PROJECT_BINARY_DIR}/header.html)
endmacro()
