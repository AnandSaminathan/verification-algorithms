cmake_minimum_required(VERSION 3.4)

project(verification-algorithms)

set(CMAKE_CXX_STANDARD 11)
set(FORMULA_TREE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/libs/formula-tree)

add_subdirectory(libs/formula-tree)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/formula-tree/include)

file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/common/*.cpp;
    )

if(WITH_TEST)
  add_subdirectory(tests)
endif(WITH_TEST)
