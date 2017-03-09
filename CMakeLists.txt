cmake_minimum_required(VERSION 3.6.0)

include_directories(lib/gram/src/gram/include)
include_directories(include)

project(gram-php)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(gram
        PREFIX ${gram-php_SOURCE_DIR}/lib/gram
        GIT_REPOSITORY https://github.com/jansvoboda11/gram
        GIT_TAG master
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_ALWAYS 1
        )

ExternalProject_Add(pugixml
        PREFIX ${gram-php_SOURCE_DIR}/lib/pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml
        GIT_TAG master
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_ALWAYS 1
        )

add_subdirectory(src)
add_subdirectory(test)

add_executable(gram-php-gen main.cpp)

add_dependencies(gram-php-gen gram)

target_link_libraries(gram-php-gen gram-php)
