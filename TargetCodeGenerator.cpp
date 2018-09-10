#include "TargetCodeGenerator.h"
#include <cstdio>
#include <fstream>

using std::to_string;
using std::ofstream;

extern string fileName;

inline int min2(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void FunctionUnit::generateCode(vector<string> &context) {
    context.push_back(funName + ":");

    char buf[100];

    /* Set Array Displacement */
    int arraySize = 0;
    int base = 2 + varNum + tmpNum;
    for (auto &item : arrayInfo) {
        arraySize += item.second;
        item.second = 4 * (base + arraySize - 1);
    }

    /* Initialize Register Manager */
    RegManager regManager(argNum, varNum, tmpNum);

    /* Function Prologue */
    int frameSize = 2 + varNum + arraySize + tmpNum;
//    std::cout << "frame size: " << frameSize << std::endl;
    // save fp
    context.emplace_back("sw    $fp,  -4($sp)");
    // set fp
    context.emplace_back("addi  $fp,  $sp,  -4");
    // set sp
    context.emplace_back("addi  $sp,  $sp,  -" + to_string(4 * frameSize));
    // save ra
    context.emplace_back("sw    $ra,  -4($fp)");
    // save sx
    for (int i = 0; i < min2(varNum, 8); i++) {
        sprintf(buf, "sw    $s%d,  -%d($fp)", i, (i + 2)*4);
        context.emplace_back(buf);
    }

    /* Function Body */
    for (const auto &inst : body) {
        if (inst.opname == "add" || inst.opname == "sub" || inst.opname == "mul" ||
            inst.opname == "div" || inst.opname == "rem" || inst.opname == "and" ||
            inst.opname == "or"  || inst.opname == "xor" || inst.opname == "srlv"||
            inst.opname == "sllv"|| inst.opname == "slt" || inst.opname == "sgt" ||
            inst.opname == "sle" || inst.opname == "sge" || inst.opname == "seq" ||
            inst.opname == "sne" || inst.opname == "addi") {
            string line = inst.opname + " ";
            line += regManager.getReg(inst.dst, context);
            line += ", ";
            line += regManager.getReg(inst.src1, context);
            line += ", ";
            line += regManager.getReg(inst.src2, context);
            context.push_back(line);
        }
        else if (inst.opname == "assign") {
            string line = "move ";
            line += regManager.getReg(inst.dst, context);
            line += ", ";
            line += regManager.getReg(inst.src1, context);
            context.push_back(line);
        }
        else if (inst.opname == "li") {
            string line = "li ";
            line += regManager.getReg(inst.dst, context);
            line += ", ";
            line += inst.src1.substr(1); // slice off #
            context.push_back(line);
        }
        else if (inst.opname == "lw" || inst.opname == "sw") {
            string line = inst.opname + " ";
            line += regManager.getReg(inst.dst, context);
            line += ", ";
            line += inst.src2 + "(" + regManager.getReg(inst.src1, context) + ")";
            context.push_back(line);
        }
        else if (inst.opname == "Label") {
            context.push_back(inst.dst + ":");
        }
        else if (inst.opname == "goto") {
            context.push_back("j " + inst.dst);
        }
        else if (inst.opname == "bnez" || inst.opname == "beqz") {
            string line = inst.opname + " ";
            line += regManager.getReg(inst.dst, context);
            line += ", ";
            line += inst.src2;
            context.push_back(line);
        }
        else if (inst.opname == "arg") {
            // move sp
            context.emplace_back("addi $sp, $sp, -4");
            std::istringstream s(inst.dst);
            int num;
            if (!(s >> num)) {
                std::cerr << "FunctionUnit::generateCode: invalid arg inst" << std::endl;
                exit(1);
            }
            if (num == 0) {
                regManager.saveReg(context);
            }
            string line;
            if (num < 4) {
                line = "move $a" + inst.dst + ", ";
                line += regManager.getReg(inst.src1, context);
            }
            else {
                line = "sw ";
                line += regManager.getReg(inst.src1, context);
                line += ", ($sp)";
            }
            context.push_back(line);
        }
        else if (inst.opname == "call") {
//            regManager.saveReg(context);
            context.push_back("jal " + inst.src1);
            regManager.loadReg(context);
            if (inst.dst != "*") {
                string line = "move " + regManager.getReg(inst.dst, context) + ", $v0";
                context.push_back(line);
            }
        }
        else if (inst.opname == "return") {
            string line = "move $v0, ";
            line += regManager.getReg(inst.dst, context);
            context.push_back(line);
            context.push_back("j exit_" + funName);
        }
        else {
            std::cerr << "FunctionUnit::generateCode: unknown opname: " + inst.opname << std::endl;
            exit(1);
        }
    }

    /* Function Epilogue */
    context.push_back("exit_" + funName + ":");
    // restore sx
    for (int i = 0; i < min2(varNum, 8); i++) {
        sprintf(buf, "lw    $s%d,  -%d($fp)", i, (i + 2)*4);
        context.emplace_back(buf);
    }
    // restore ra
    context.emplace_back("lw    $ra,  -4($fp)");
    // restore sp
    context.emplace_back("addi  $sp,  $fp,  4");
    // restore fp
    context.emplace_back("lw    $fp,  ($fp)");

    /* Return */
    context.emplace_back("jr    $ra");
}

TargetCodeGenerator::TargetCodeGenerator(const vector<string> &IRList) {
    FunctionUnit function;
    for (auto &line: IRList) {
        if (line == "$") {
            continue ;
        }
        std::istringstream lineStream(line);
        string token;
        if (!(lineStream >> token)) {
            std::cerr << "Internal Error: TargetCodeGenerator: 0" << std::endl;
        }
        if (token == "Function") {
            if (!(lineStream >> function.funName)) {
                std::cerr << "Internal Error: TargetCodeGenerator: 1" << std::endl;
            }
        }
        else if (token == "End") {
            if (!(lineStream >> function.argNum >> function.varNum >> function.tmpNum)) {
                std::cerr << "Internal Error: TargetCodeGenerator: 2" << std::endl;
            }
            FunctionList.push_back(function);
            function.body.clear();
        }
        else if (token == "array") {
            string varID;
            int ID;
            int length;
            if (!(lineStream >> varID >> length)) {
                std::cerr << "Internal Error: TargetCodeGenerator: 3" << std::endl;
            }
            std::istringstream s(varID.substr(7));
            if (!(s >> ID)) {
                std::cerr << "Internal Error: TargetCodeGenerator: 4" << std::endl;
            }
            function.arrayInfo.insert({ID, length});
        }
        else {
            Instruction inst;
            if (token == "mod") {
                inst.opname = "rem";
            }
            else if (token == "shr") {
                inst.opname = "srlv";
            }
            else if (token == "shl") {
                inst.opname = "sllv";
            }
            else if (token == "lt") {
                inst.opname = "slt";
            }
            else if (token == "gt") {
                inst.opname = "sgt";
            }
            else if (token == "nlt") {
                inst.opname = "sge";
            }
            else if (token == "ngt") {
                inst.opname = "sle";
            }
            else if (token == "equ") {
                inst.opname = "seq";
            }
            else if (token == "neq") {
                inst.opname = "sne";
            }
            else if (token == "mem2reg") {
                inst.opname = "lw";
            }
            else if (token == "reg2mem") {
                inst.opname = "sw";
            }
            else if (token == "if") {
                inst.opname = "bnez";
            }
            else if (token == "ifn") {
                inst.opname = "beqz";
            }
            else {
                inst.opname = token;
            }
            if (lineStream >> token) {
                inst.dst = token;
            }
            if (lineStream >> token) {
                inst.src1 = token;
            }
            if (lineStream >> token) {
                inst.src2 = token;
            }
            function.body.push_back(inst);
        }
    }
}

void TargetCodeGenerator::print() {
    for (auto &item : FunctionList) {
        std::cout << "name: " << item.funName << std::endl;
        std::cout << "arg: " << item.argNum << std::endl;
        std::cout << "var: " << item.varNum << std::endl;
        std::cout << "tmp: " << item.tmpNum << std::endl;
        for (auto &array : item.arrayInfo) {
            std::cout << "ID: " << array.first << "\t" << "length: " << array.second << std::endl;
        }
        for (auto &inst : item.body) {
            std::cout << "opname: " << inst.opname << "\t";
            std::cout << "dst: " << inst.dst << "\t";
            std::cout << "src1: " << inst.src1 << "\t";
            std::cout << "src2: " << inst.src2 << std::endl;
        }
    }
}

void TargetCodeGenerator::generateCode() {
    const char *header = ".globl main\n"
                         "\n"
                         ".data\n"
                         "_newline: .asciiz \"\\n\"\n"
                         "\n"
                         ".text\n"
                         "readInt:\n"
                         "    li $v0, 5\n"
                         "    syscall\n"
                         "    jr $ra\n"
                         "\n"
                         "printInt:\n"
                         "    li $v0, 1\n"
                         "    syscall\n"
                         "    li $v0, 4\n"
                         "    la $a0, _newline\n"
                         "    syscall\n"
                         "    jr $ra";
    CodeList.emplace_back(header);
    for (auto &function : FunctionList) {
        CodeList.emplace_back("");
        function.generateCode(CodeList);
    }
//    std::cout << std::endl << "[MIPS Assembly]" << std::endl;
    ofstream fout(fileName.substr(0, fileName.find_last_of('.')) + ".asm");
    if (!fout) {
        std::cerr << "Fatal Error: TargetCodeGenerator: fail to create file" << std::endl;
        exit(1);
    }
    for (auto &line : CodeList) {
        fout << line << std::endl;
    }
}