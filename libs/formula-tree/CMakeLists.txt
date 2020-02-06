cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(formula-tree)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DANTLR4CPP_STATIC)

set(ANTLR4_WITH_STATIC_CRT OFF)
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.2-complete.jar)

include(ExternalAntlr4Cpp)

include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(ANTLR REQUIRED)

antlr_target(GrammarLexer ${PROJECT_SOURCE_DIR}/src/FormulaLexer.g4 LEXER)
antlr_target(GrammarParser ${PROJECT_SOURCE_DIR}/src/FormulaParser.g4 PARSER
	     VISITOR
             DEPENDS_ANTLR GrammarLexer
             COMPILE_FLAGS -lib ${ANTLR_GrammarLexer_OUTPUT_DIR})

include_directories(${ANTLR_GrammarLexer_OUTPUT_DIR})
include_directories(${ANTLR_GrammarParser_OUTPUT_DIR})


file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/src/*.h 
		 ${PROJECT_SOURCE_DIR}/src/*.cpp
    )

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
