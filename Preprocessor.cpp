//
// Created by 15134 on 2018/6/21.
//

#include "Preprocessor.h"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;

extern string fileName;

void Preprocessor::preprocess() {
    string output = fileName.substr(0, fileName.find_last_of('.')) + ".i";
    string line;
    ifstream fin(fileName);
    ofstream fout(output);
    if (!fin) {
        cerr << "Fatal Error: Preprocessor: fail to open file: " << fileName << endl;
        exit(1);
    }
    if (!fout) {
        cerr << "Fatal Error: Preprocessor: fail to create file" << endl;
        exit(1);
    }
    while (getline(fin, line)) {
        auto pos = line.find_first_of("//");
        pos = pos == string::npos ? line.size() : pos;
        fout << line.substr(0, pos) << endl;
    }
}