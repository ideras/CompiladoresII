cmake_minimum_required(VERSION 3.14)
project(FLexer)

find_package(FLEX)

FLEX_TARGET(MyScanner LexerImpl.l
            ${CMAKE_CURRENT_BINARY_DIR}/LexerImpl.cpp
            COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/LexerImpl.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    ${FLEX_MyScanner_OUTPUTS}
    Lexer.hpp
    Lexer.cpp
    main.cpp
 )
