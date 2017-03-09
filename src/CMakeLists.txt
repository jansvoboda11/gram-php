include_directories(../lib/gram/src/gram/include)
include_directories(../lib/pugixml/src/pugixml/src)

set(SOURCE_FILES
        CommandLine.cpp
        DiffCalculator.cpp
        PhpLiteral.cpp
        PhpType.cpp
        PhpUnitEvaluator.cpp
        PhpUnserializer.cpp
        ../include/gram-php/CommandLine.h
        ../include/gram-php/DiffCalculator.h
        ../include/gram-php/PhpLiteral.h
        ../include/gram-php/PhpType.h
        ../include/gram-php/PhpUnitEvaluator.h
        ../include/gram-php/PhpUnserializer.h
        )

add_library(gram-php STATIC ${SOURCE_FILES})

add_dependencies(gram-php gram pugixml)

target_link_libraries(gram-php
        ${gram-php_SOURCE_DIR}/lib/gram/src/gram-build/src/libgram.a
        ${gram-php_SOURCE_DIR}/lib/pugixml/src/pugixml-build/libpugixml.a
        )
