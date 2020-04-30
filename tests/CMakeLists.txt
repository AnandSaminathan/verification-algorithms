cmake_minimum_required(VERSION 3.16)

add_library(catch2_main STATIC catch-main.cpp)
target_include_directories(catch2_main PUBLIC ${PROJECT_SOURCE_DIR}/tests/catch2) 

set(TEST_LIST 
    3bit-ring-counter
   )

foreach(NAME IN LISTS TEST_LIST)
  list(APPEND TEST_SOURCE_LIST test-${NAME}.cpp)
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
              test-3bit-ring-counter.cpp
              ${SOURCE}
              )
target_precompile_headers(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/tests/catch2/catch.hpp)
target_link_libraries(${TARGET_NAME} catch2_main)
target_link_libraries(${TARGET_NAME} -lz3)
target_link_libraries(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)
