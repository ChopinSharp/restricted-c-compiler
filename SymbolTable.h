//
// Created by 15134 on 2018/6/1.
//

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class VarEntry {
public:
    string ID;
    int type;   // variable type, array element type
    int capacity;
    bool isArray;

    VarEntry(string ID, int type, int capacity, bool isArray):
            ID(ID), type(type), capacity(capacity), isArray(isArray) {}

};


class FunEntry {
public:
    string name;
    int type;
    bool isDefinied = false;
    vector<pair<int, string>> paraList;	//记录形参列表
    FunEntry(string name, int rtype, bool isDefined, vector<pair<int, string>> paraList):
        name(name), type(rtype), isDefinied(isDefined), paraList(paraList) {}
    int getReturnType() { return this->type; }
};

class SymbolTable {
public:

    int rtype;
    string funName;
    string breakTag;
    string continueTag;
    map<string, VarEntry> varMap;

//    explicit SymbolTable() = default;
    // ctor for symbol table of function body
    SymbolTable(string funName, int rtype):
            funName(funName), rtype(rtype), breakTag(""), continueTag("") {}
    // ctor for symbol table of statement block
    SymbolTable(string funName, int rtype, string breakTag, string continueTag):
            funName(funName), rtype(rtype), breakTag(breakTag), continueTag(continueTag) {}

    const VarEntry *resolveName(const string &name) {
        auto iter = varMap.find(name);
        if (iter == varMap.end()) {
            return nullptr;
        }
        return &iter->second;
    }

    bool isFunction() const { return !funName.empty(); }
    bool canBreak() const { return !breakTag.empty(); }
    bool canContinue() const { return !continueTag.empty(); }

};

class SymbolInfo {
public:
    static map<string, FunEntry> funcPool;        //全局定义的函数池，<函数名，函数记录表入口>
    static vector<SymbolTable> tableStack;        //维护的栈

    static const VarEntry *resolveVarName(const string &name) {
        for (auto iter = tableStack.rbegin(); iter != tableStack.rend(); iter++) {
            const VarEntry *ptr = iter->resolveName(name);
            if (ptr != nullptr) {
                return ptr;
            }
        }
        return nullptr;
    }

    static const FunEntry *resolveFunName(const string &name) {
        auto iter = funcPool.find(name);
        if (iter == funcPool.end()) {
            return nullptr;
        }
        return &iter->second;
    }
};

#endif //COMPILER_SYMBOLTABLE_H
