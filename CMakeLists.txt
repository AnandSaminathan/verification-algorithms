cmake_minimum_required(VERSION 3.4)

project(verification-algorithms)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

include(ExternalZ3)
include(ExternalFormulaTree)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(verification-algorithms SHARED
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/cnf.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/z3-solver.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/symbol.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/k-induction/k-induction.cpp
	          ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ltl-bmc/ltl-bmc.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ic3/ic3.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/pnet-coverability/pnet-coverability.cpp
          )

target_link_libraries(verification-algorithms formula-tree)
target_link_libraries(verification-algorithms z3_main)

if(WITH_TEST)
  enable_testing()
  add_subdirectory(tests)
endif(WITH_TEST)

set(POST_BUILD_INCLUDE_DIRECTORY $<TARGET_FILE_DIR:verification-algorithms>/include)
set(POST_BUILD_BIN_DIRECTORY $<TARGET_FILE_DIR:verification-algorithms>/bin)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${PROJECT_SOURCE_DIR}/include"
  ${POST_BUILD_INCLUDE_DIRECTORY})

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:verification-algorithms>
  ${POST_BUILD_BIN_DIRECTORY}/$<TARGET_FILE_NAME:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E tar "cfv" "verificationalgo-source.zip" --format=zip
  ${POST_BUILD_INCLUDE_DIRECTORY}
  ${POST_BUILD_BIN_DIRECTORY})