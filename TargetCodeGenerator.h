#ifndef MYCOMPILER_TARGETCODEGENERATOR_H
#define MYCOMPILER_TARGETCODEGENERATOR_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include "RegManager.h"

using std::vector;
using std::string;
using std::map;

struct Instruction {
    string opname;
    string dst;
    string src1;
    string src2;
    Instruction() = default;
};

struct FunctionUnit {
    string funName;
    map<int, int> arrayInfo;
    int argNum;
    int varNum;
    int tmpNum;
    vector<Instruction> body;
    FunctionUnit(): argNum(-1), varNum(-1), tmpNum(-1) {}
    void generateCode(vector<string> &context);
};

class TargetCodeGenerator {

    vector<FunctionUnit> FunctionList;
    vector<string> CodeList;

public:
    explicit TargetCodeGenerator(const vector<string> &IRList);
    void print();
    void generateCode();
};


#endif //MYCOMPILER_TARGETCODEGENERATOR_H
