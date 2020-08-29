cmake_minimum_required(VERSION 3.7)

include(ExternalProject)

ExternalProject_Add(
        git_z3
        PREFIX ${CMAKE_BINARY_DIR}/z3
        URL https://github.com/Z3Prover/z3/releases/download/z3-4.8.7/z3-4.8.7-x64-ubuntu-16.04.zip
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(git_z3 source_dir)
set(Z3_INCLUDE ${source_dir}/include)
set(Z3_LIBRARY ${source_dir}/bin)

add_library(z3_main STATIC ${PROJECT_SOURCE_DIR}/cmake/z3-main.cpp)

add_dependencies(z3_main git_z3)
target_include_directories(z3_main PUBLIC ${Z3_INCLUDE})
target_link_libraries(z3_main ${Z3_LIBRARY}/libz3.so)