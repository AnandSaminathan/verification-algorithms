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

add_executable(test-z3-solver-3 test-z3-solver-3.cpp
                ${SOURCE}
                )
target_link_libraries(test-z3-solver-3 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-z3-solver-3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-z3-solver-3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)


add_executable(test-3bit-ring-counter test-3bit-ring-counter.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-3bit-ring-counter-ic3 test-3bit-ring-counter-ic3.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-ring-counter-ic3 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-ring-counter-ic3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-ring-counter-ic3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-producer-consumer test-producer-consumer.cpp
              ${SOURCE}
              )
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-producer-consumer ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-producer-consumer-pb test-producer-consumer-pb.cpp
              ${SOURCE}
              )
target_link_libraries(test-producer-consumer-pb ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-producer-consumer-pb ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-producer-consumer-pb ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-mutex test-mutex.cpp
              ${SOURCE}
              )
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-mutex ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-mutex-pb test-mutex-pb.cpp
              ${SOURCE}
              )
target_link_libraries(test-mutex-pb ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-mutex-pb ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-mutex-pb ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-3bit-shift-register test-3bit-shift-register.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-shift-register ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-mutex-2 test-mutex-2.cpp
              ${SOURCE}
              )
target_link_libraries(test-mutex-2 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-mutex-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-mutex-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-3bit-ring-counter-2 test-3bit-ring-counter-2.cpp
              ${SOURCE}
              )
target_link_libraries(test-3bit-ring-counter-2 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-3bit-ring-counter-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-3bit-ring-counter-2 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-1000bit-ring-counter test-1000bit-ring-counter.cpp
              ${SOURCE}
              )
target_link_libraries(test-1000bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-1000bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-1000bit-ring-counter ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-cnf test-cnf.cpp
              ${SOURCE}
              )
target_link_libraries(test-cnf ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-cnf ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-cnf ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)

add_executable(test-ic3 test-ic3.cpp
              ${SOURCE}
              )
target_link_libraries(test-ic3 ${PROJECT_SOURCE_DIR}/libs/z3/libz3.so)
target_link_libraries(test-ic3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libantlr4-runtime.so)
target_link_libraries(test-ic3 ${PROJECT_SOURCE_DIR}/libs/formula-tree/libformula-tree.so)
