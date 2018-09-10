#include "RegManager.h"
#include <iostream>
#include <sstream>

string RegManager::getVarReg(int ID, vector<string> &context) {
    // if not in reg, allocate a reg
    if (!inRx(ID)) {
        char buf[100];
        sprintf(buf, "lw    $t8, %d($fp)", varMap[ID]);
        context.emplace_back(buf);
        sprintf(buf, "sw    $s%d, %d($fp)", sxAllocator, varMap[ID]);
        context.emplace_back(buf);
        sprintf(buf, "move  $s%d, $t8", sxAllocator);
        context.emplace_back(buf);
        // update reg info
        varMap[sx[sxAllocator]] = varMap[ID];   // swap out reg
        sx[sxAllocator] = ID;                   // sx allocation info
        varMap[ID] = sxAllocator;               // swap in reg

        sxAllocator = (sxAllocator + 1) % sxNum;
    }
    return "$s" + std::to_string(varMap[ID]);
}

string RegManager::getArgReg(int ID, vector<string> &context) {
    // if not in reg, allocate a reg
    if (!inAx(ID)) {
        char buf[100];
        // each arg has its own memory location
        sprintf(buf, "sw $a%d, %d($fp)", axAllocator, getArgMemLoc(ax[axAllocator]));
        context.emplace_back(buf);
        sprintf(buf, "lw $a%d, %d($fp)", axAllocator, getArgMemLoc(ID));
        context.emplace_back(buf);
        // update reg info
        ax[axAllocator] = ID;
        argMap[ID] = axAllocator;
        axAllocator = (axAllocator + 1) % axNum;
    }
    return "$a" + std::to_string(argMap[ID]);
}

string RegManager::getTmpReg(int ID, vector<string> &context) {
    // if not in reg, allocate a reg
    if (!inTx(ID)) {
        char buf[100];
        // each tmp has its own memory location
        sprintf(buf, "sw $t%d, %d($fp)", txAllocator, getArgMemLoc(tx[txAllocator]));
        context.emplace_back(buf);
        sprintf(buf, "lw $t%d, %d($fp)", txAllocator, getTmpMemLoc(ID));
        context.emplace_back(buf);
        // update reg info
        tx[txAllocator] = ID;
        tmpMap[ID] = txAllocator;
        txAllocator = (txAllocator + 1) % txNum;
    }
    return "$t" + std::to_string(tmpMap[ID]);
}

string RegManager::getReg(const string &strID, vector<string> &context) {
    if (strID[0] == '#') {
        return strID.substr(1);
    }
    if (strID[0] != '%') {
        std::cerr << "RegManager::getReg: invalid ID 0: " << strID << std::endl;
        exit(1);
    }
    std::istringstream s(strID.substr(7));
    int ID;
    if (!(s >> ID)) {
        std::cerr << "RegManager::getReg: invalid ID: " << strID << std::endl;
        exit(1);
    }
    if (strID[1] == 't') {
        return getTmpReg(ID, context);
    }
    else if (strID[1] == 'v') {
        return getVarReg(ID, context);
    }
    else if (strID[1] == 'a') { // arg is numbered from arg bias
        return getArgReg(ID, context);
    }
    else {
        std::cerr << "RegManager::getReg: invalid varID: " << strID << std::endl;
        exit(1);
    }
}

void RegManager::saveReg(vector<string> &context) {
    char buf[100];
    for (int i = 0; i < txNum; i++) {
        if (tx[i] != -1) {
            sprintf(buf, "sw $t%d %d($fp)", i, getTmpMemLoc(tx[i]));
            context.emplace_back(buf);
        }
    }
    for (int i = 0; i < axNum; i++) {
        if (ax[i] != -1) {
            sprintf(buf, "sw $a%d %d($fp)", i, getArgMemLoc(ax[i]));
            context.emplace_back(buf);
        }
    }
}

void RegManager::loadReg(vector<string> &context) {
    char buf[100];
    for (int i = 0; i < txNum; i++) {
        if (tx[i] != -1) {
            sprintf(buf, "lw $t%d %d($fp)", i, getTmpMemLoc(tx[i]));
            context.emplace_back(buf);
        }
    }
    for (int i = 0; i < axNum; i++) {
        if (ax[i] != -1) {
            sprintf(buf, "lw $a%d %d($fp)", i, getArgMemLoc(ax[i]));
            context.emplace_back(buf);
        }
    }
}

RegManager::RegManager(int argNum, int varNum, int tmpNum): varNum(varNum) {

    argMap = new int[argNum];
    varMap = new int[varNum];
    tmpMap = new int[tmpNum];

    // initialize
    for (int i = 0; i < argNum; i++) {
        argMap[i] = -1;
    }
    for (int i = 0; i < varNum; i++) {
        varMap[i] = -1;
    }
    for (int i = 0; i < tmpNum; i++) {
        tmpMap[i] = -1;
    }
    for (int &i : ax) {
        i = -1;
    }
    for (int &i : sx) {
        i = -1;
    }
    for (int &i : tx) {
        i = -1;
    }

    // allocate ax for arg
    for (axAllocator = 0; axAllocator < argNum && axAllocator < axNum; axAllocator++) {
        argMap[axAllocator] = axAllocator;
        ax[axAllocator] = axAllocator;
    }
    // allocate memory for arg
    for (int i = axNum; i < argNum; i++) {
        argMap[i] = getArgMemLoc(i);
    }
    axAllocator %= axNum;


    // allocate sx for var
    for (sxAllocator = 0; sxAllocator < varNum && sxAllocator < sxNum; sxAllocator++) {
        varMap[sxAllocator] = sxAllocator;
        sx[sxAllocator] = sxAllocator;
    }
    // allocate memory for var
    for (int i = sxNum; i < varNum; i++) {
        varMap[i] = -(i + 2) * 4;  // relative to fp
    }
    sxAllocator %= sxNum;

    // allocate tx for tmp
    for (txAllocator = 0; txAllocator < tmpNum && txAllocator < txNum; txAllocator++) {
        tmpMap[txAllocator] = txAllocator;
        tx[txAllocator] = txAllocator;
    }
    // allocate memory for tmp
    for (int i = txNum; i < tmpNum; i++) {
        tmpMap[i] = getTmpMemLoc(i);
    }
    txAllocator %= txNum;
}

RegManager::~RegManager() {
    delete[] argMap;
    delete[] varMap;
    delete[] tmpMap;
}