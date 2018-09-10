#include <iostream>
#include <cstring>
#include "ASTNode.h"
#include "yacc.hpp"
#include "TargetCodeGenerator.h"
#include "Preprocessor.h"
#include "SymbolTable.h"

using std::cerr;
using std::endl;

extern FILE *yyin;
extern A_TranslationUnit *unit;

vector<string> IRList;
string fileName;
char nameBuf[1000];

void setInputFileName(const char *name) {
    int pos = -1;
    for (int i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            pos = i;
        }
    }
    if (pos == -1) {
        cerr << "Input file name of invalid format: should be *.c" << endl;
        exit(1);
    }
    strcpy(nameBuf, name);
    nameBuf[pos + 1] = 'i';
    nameBuf[pos + 2] = 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Fatal Error: no input file or multiple input files" << endl;
    }
    fileName = argv[1];
//    cout << fileName << endl;
    setInputFileName(argv[1]);
    Preprocessor::preprocess();
    yyin = fopen(nameBuf, "r");
    if (yyin == nullptr) {
        cerr << "Fatal Error: main: file not found" << endl;
        exit(1);
    }

    yyparse();

    cout << "[AST]:" << endl;
    unit->print(0);

    /* initialize built in function */ // TODO alert number literal used as type identifier, TO HELL WITH CPP LINKAGE
    string fun1("printInt");
    vector<pair<int, string>> para;
    para.emplace_back(2, string("a"));
    SymbolInfo::funcPool.insert(make_pair(fun1, FunEntry(fun1, 0, true, para)));
    string fun2("readInt");
    SymbolInfo::funcPool.insert(make_pair(fun2, FunEntry(fun2, 2, true, vector<pair<int, string>>())));

    unit->parseRecursive();

    unit->generateIRRecursive();

    cout << endl << "[IR]: " << endl;
    bool indent = false;
    for (auto &line : IRList) {
        if (line == "$") {
            indent = !indent;
            continue ;
        }
        if (indent) {
            cout << "    ";
        }
        cout << line << endl;
    }

    TargetCodeGenerator gen(IRList);
//    cout << endl << "[Code generator]: " << endl;
//    gen.print();
    gen.generateCode();

    return 0;
}
