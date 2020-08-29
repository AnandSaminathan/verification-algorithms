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

add_library(formula-tree STATIC ${PROJECT_SOURCE_DIR}/cmake/formulatree-main.cpp)

add_dependencies(formula-tree git_formulatree)
target_include_directories(formula-tree PUBLIC ${source_dir}/include)
target_link_libraries(formula-tree ${source_dir}/bin/libformula-tree.so)
target_link_libraries(formula-tree ${source_dir}/bin/libantlr4-runtime.so)
target_link_libraries(formula-tree ${source_dir}/bin/libantlr4-runtime.so.4.8)