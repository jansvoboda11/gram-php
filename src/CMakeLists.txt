include_directories(../lib/gram/src/gram/include)

add_executable(gram-php
        ../include/CommandLine.h
        ../include/PhpUnitEvaluator.h
        CommandLine.cpp
        PhpUnitEvaluator.cpp
        main.cpp
        )

add_dependencies(gram-php gram)

target_link_libraries(gram-php ${gram-php_SOURCE_DIR}/lib/gram/src/gram-build/src/libgram.a)
