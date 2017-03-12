include_directories(lib/catch/src/catch/single_include)
include_directories(lib/fakeit/src/fakeit/single_header/catch)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(catch
        PREFIX ${gram-php_SOURCE_DIR}/test/lib/catch
        GIT_REPOSITORY https://github.com/philsquared/Catch
        GIT_TAG master
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        )

ExternalProject_Add(fakeit
        PREFIX ${gram-php_SOURCE_DIR}/test/lib/fakeit
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt
        GIT_TAG master
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        )

add_executable(gram-php-tests
        test.cpp
        diff_calculator_test.cpp
        php_serializer_test.cpp
        )

add_dependencies(gram-php-tests catch fakeit)

target_link_libraries(gram-php-tests gram-php)
