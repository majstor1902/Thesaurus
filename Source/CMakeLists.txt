cmake_minimum_required(VERSION 3.16)

add_library(ThesaurusLib)

target_sources(ThesaurusLib
  PRIVATE
    Thesaurus.cpp
  PUBLIC
    Thesaurus.h
  )

target_include_directories(ThesaurusLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ThesaurusLib
    PUBLIC
      "--coverage"
    )
  target_link_options(ThesaurusLib
    INTERFACE
      "--coverage"
    )
endif()
