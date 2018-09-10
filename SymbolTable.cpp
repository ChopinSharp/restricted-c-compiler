//
// Created by 15134 on 2018/6/4.
//
#include "SymbolTable.h"

map<string, FunEntry> SymbolInfo::funcPool;
vector<SymbolTable> SymbolInfo::tableStack;
