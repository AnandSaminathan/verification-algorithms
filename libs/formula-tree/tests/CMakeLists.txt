add_executable(test-sample-formula ${PROJECT_SOURCE_DIR}/tests/test-sample-formula.cpp
               ${ANTLR_GrammarLexer_CXX_OUTPUTS}
               ${ANTLR_GrammarParser_CXX_OUTPUTS}
               ${SOURCE})
add_executable(test-formula-tree ${PROJECT_SOURCE_DIR}/tests/test-formula-tree.cpp
               ${ANTLR_GrammarLexer_CXX_OUTPUTS}
               ${ANTLR_GrammarParser_CXX_OUTPUTS}
               ${SOURCE})

target_link_libraries(test-sample-formula antlr4_static)
target_link_libraries(test-formula-tree antlr4_static)