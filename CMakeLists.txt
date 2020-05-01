cmake_minimum_required(VERSION 3.4)

project(verification-algorithms)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/z3)


file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/*.cpp
        ${PROJECT_SOURCE_DIR}/src/verification-algorithms/k-induction/*.cpp
	      ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ltl-bmc/*.cpp
        ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ic3/*.cpp
    )

add_library(verification-algorithms SHARED
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/cnf.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/common/z3-solver.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/k-induction/k-induction.cpp
	          ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ltl-bmc/ltl-bmc.cpp
            ${PROJECT_SOURCE_DIR}/src/verification-algorithms/ic3/ic3.cpp
          )
target_link_libraries(verification-algorithms ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)
target_link_libraries(verification-algorithms ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(verification-algorithms z3)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so.4.8"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/libs/z3/libz3.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

if(WITH_TEST)
  enable_testing()
  add_subdirectory(tests)
endif(WITH_TEST)


