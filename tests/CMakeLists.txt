add_library(catch2_main STATIC catch-main.cpp)
target_include_directories(catch2_main PUBLIC ${PROJECT_SOURCE_DIR}/tests/catch2) 

set(TEST_LIST 
    3bit-ring-counter
    3bit-shift-register
    mutex
    producer-consumer
    ic3
    common
   )

foreach(NAME IN LISTS TEST_LIST)
  list(APPEND TEST_SOURCE_LIST test-${NAME}.cpp)
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
              ${TEST_SOURCE_LIST}
              ${SOURCE}
              )
target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/tests/catch2)
target_link_libraries(${TARGET_NAME} catch2_main)
target_link_libraries(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_test(NAME ${TARGET_NAME}
         COMMAND ${TARGET_NAME} 
        )

