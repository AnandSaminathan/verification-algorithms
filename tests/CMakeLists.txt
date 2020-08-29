cmake_minimum_required(VERSION 3.7)

include(ExternalCatch2)

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
              )

target_link_libraries(${TARGET_NAME} catch2_main)
target_link_libraries(${TARGET_NAME} verification-algorithms)

add_test(NAME ${TARGET_NAME}
         COMMAND ${TARGET_NAME} 
        )

