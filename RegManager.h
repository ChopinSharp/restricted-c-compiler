#ifndef MYCOMPILER_REGMANAGER_H
#define MYCOMPILER_REGMANAGER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class RegManager {
    // t8 and t9 is reserved
    static const int axNum = 4;
    static const int sxNum = 8;
    static const int txNum = 8;
    int ax[axNum];
    int tx[txNum];
    int sx[sxNum];
    int *argMap;
    int *varMap;
    int *tmpMap;
    int axAllocator;
    int sxAllocator;
    int txAllocator;
    int varNum;

    bool inAx(int argID) { return ax[argMap[argID] % axNum] == argID; }
    bool inRx(int varID) { return sx[varMap[varID] % sxNum] == varID; }
    bool inTx(int tmpID) { return tx[tmpMap[tmpID] % txNum] == tmpID; }
    int getArgMemLoc(int argID) { return (argID + 1) * 4; }  // relative to fp
    int getTmpMemLoc(int tmpID) { return -(tmpID + 2 + varNum) * 4; }

public:
    string getArgReg(int ID, vector<string> &context);
    string getVarReg(int ID, vector<string> &context);
    string getTmpReg(int ID, vector<string> &context);
    string getReg(const string &strID, vector<string> &context);
    void saveReg(vector<string> &context);
    void loadReg(vector<string> &context);
    RegManager(int argNum, int varNum, int tmpNum);
    ~RegManager();
};

#endif