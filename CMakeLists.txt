cmake_minimum_required(VERSION 3.4)

project(verification-algorithms)

set(CMAKE_CXX_STANDARD 11)
set(FORMULA_TREE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/libs/formula-tree)

add_subdirectory(libs/formula-tree)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/formula-tree/include)

file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/common/*.cpp
        ${PROJECT_SOURCE_DIR}/src/k-induction/*.cpp
    )

add_library(verification-algorithms SHARED
            ${PROJECT_SOURCE_DIR}/src/common/z3-solver.cpp
            ${PROJECT_SOURCE_DIR}/src/k-induction/k-induction.cpp
          )
target_link_libraries(verification-algorithms ${FORMULA_TREE_ROOT}/libformula-tree.so)
target_link_libraries(verification-algorithms ${FORMULA_TREE_ROOT}/libantlr4-runtime.so)
target_link_libraries(verification-algorithms ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${FORMULA_TREE_ROOT}/libantlr4-runtime.so.4.8"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${FORMULA_TREE_ROOT}/libantlr4-runtime.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${FORMULA_TREE_ROOT}/libformula-tree.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

add_custom_command(TARGET verification-algorithms POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/libs/z3/libz3.so"
  $<TARGET_FILE_DIR:verification-algorithms>)

if(WITH_TEST)
  add_subdirectory(tests)
endif(WITH_TEST)


