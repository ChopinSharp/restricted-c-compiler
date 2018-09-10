cmake_minimum_required(VERSION 3.10)
project(MyCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyCompiler main.cpp ASTNode.h ASTNode.cpp SymbolTable.h SymbolTable.cpp lex.yy.cpp yacc.hpp yacc.cpp TargetCodeGenerator.cpp TargetCodeGenerator.h Preprocessor.cpp Preprocessor.h RegManager.cpp RegManager.h)