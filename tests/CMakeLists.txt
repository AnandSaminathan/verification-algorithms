add_executable(test-symbol test-symbol.cpp)

add_executable(test-z3-solver test-z3-solver.cpp
                ${SOURCE}
                )
add_dependencies(test-z3-solver formula-tree)
target_link_libraries(test-z3-solver ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-z3-solver ${FORMULA_TREE_ROOT}/libantlr4-runtime.so)
target_link_libraries(test-z3-solver ${FORMULA_TREE_ROOT}/libformula-tree.so)

add_executable(test-z3-solver-2 test-z3-solver-2.cpp
                ${SOURCE}
                )
add_dependencies(test-z3-solver-2 formula-tree)
target_link_libraries(test-z3-solver-2 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-z3-solver-2 ${FORMULA_TREE_ROOT}/libantlr4-runtime.so)
target_link_libraries(test-z3-solver-2 ${FORMULA_TREE_ROOT}/libformula-tree.so)


add_executable(test-3bit-ring-counter test-3bit-ring-counter.cpp
              ${SOURCE}
              )
add_dependencies(test-3bit-ring-counter formula-tree)
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-ring-counter ${FORMULA_TREE_ROOT}/libantlr4-runtime.so)
target_link_libraries(test-3bit-ring-counter ${FORMULA_TREE_ROOT}/libformula-tree.so)

add_executable(test-producer-consumer test-producer-consumer.cpp
              ${SOURCE}
              )
add_dependencies(test-producer-consumer formula-tree)
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-producer-consumer ${FORMULA_TREE_ROOT}/libantlr4-runtime.so)
target_link_libraries(test-producer-consumer ${FORMULA_TREE_ROOT}/libformula-tree.so)
