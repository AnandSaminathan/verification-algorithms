cmake_minimum_required(VERSION 3.7)

include(ExternalProject)

ExternalProject_Add(
        git_formulatree
        PREFIX ${CMAKE_BINARY_DIR}/formulatree
        URL https://github.com/AnandSaminathan/formula-tree/releases/download/v1.0/formulatree-source.zip
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(git_formulatree source_dir)
set(FORMULATREE_INCLUDE ${source_dir}/include)
set(FORMULATREE_LIBRARY ${source_dir}/bin)

add_library(formula-tree STATIC ${PROJECT_SOURCE_DIR}/cmake/formulatree-main.cpp)

add_dependencies(formula-tree git_formulatree)
target_include_directories(formula-tree PUBLIC ${FORMULATREE_INCLUDE})
target_link_libraries(formula-tree ${FORMULATREE_LIBRARY}/libformula-tree.so)
target_link_libraries(formula-tree ${FORMULATREE_LIBRARY}/libantlr4-runtime.so)
target_link_libraries(formula-tree ${FORMULATREE_LIBRARY}/libantlr4-runtime.so.4.8)