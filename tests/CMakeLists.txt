add_executable(test-symbol test-symbol.cpp)

add_executable(test-z3-solver test-z3-solver.cpp
                ${SOURCE}
                )
target_link_libraries(test-z3-solver ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-z3-solver ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-z3-solver ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-z3-solver-2 test-z3-solver-2.cpp
                ${SOURCE}
                )
target_link_libraries(test-z3-solver-2 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-z3-solver-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-z3-solver-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)


add_executable(test-3bit-ring-counter test-3bit-ring-counter.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-producer-consumer test-producer-consumer.cpp
              ${SOURCE}
              )
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-mutex test-mutex.cpp
              ${SOURCE}
              )
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)


add_executable(test-3bit-shift-register test-3bit-shift-register.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)