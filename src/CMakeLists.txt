include_directories(../lib/gram/src/gram/include)

add_executable(gram-php
        main.cpp
        )

add_dependencies(gram-php gram)

target_link_libraries(gram-php ${gram-math_SOURCE_DIR}/lib/gram/src/gram-build/src/libgram.a)
