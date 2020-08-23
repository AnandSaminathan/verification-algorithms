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

add_library(formula-tree INTERFACE)
target_include_directories(formula-tree INTERFACE ${source_dir}/include)
target_link_libraries(formula-tree INTERFACE ${source_dir}/bin/libformula-tree.so)