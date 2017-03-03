include_directories(../lib/gram/src/gram/include)
include_directories(../lib/pugixml/src/pugixml/src)

add_executable(gram-php
        ../include/CommandLine.h
        ../include/DiffCalculator.h
        ../include/PhpLiteral.h
        ../include/PhpType.h
        ../include/PhpUnitEvaluator.h
        CommandLine.cpp
        DiffCalculator.cpp
        PhpLiteral.cpp
        PhpType.cpp
        PhpUnitEvaluator.cpp
        main.cpp
        )

add_dependencies(gram-php gram pugixml)

target_link_libraries(gram-php
        ${gram-php_SOURCE_DIR}/lib/gram/src/gram-build/src/libgram.a
        ${gram-php_SOURCE_DIR}/lib/pugixml/src/pugixml-build/libpugixml.a
        )
