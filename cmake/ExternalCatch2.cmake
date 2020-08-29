cmake_minimum_required(VERSION 3.7)

include(ExternalProject)

ExternalProject_Add(
        git_catch
        PREFIX ${CMAKE_BINARY_DIR}/catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(git_catch source_dir)

add_library(catch2_main STATIC ${PROJECT_SOURCE_DIR}/cmake/catch-main.cpp)
add_dependencies(catch2_main git_catch)
target_include_directories(catch2_main PUBLIC ${source_dir}/single_include)
