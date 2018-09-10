//
// Created by 15134 on 2018/6/2.
//

#ifndef MYCOMPILER_TreeNode_H
#define MYCOMPILER_TreeNode_H

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "SymbolTable.h"

using std::string;
using std::vector;
using std::map;
using std::pair;


/* ======================================= Base Class ==================================== */
class A_TreeNode {
public:
    int line;           // for error reporting
    A_TreeNode(): line(-1) {}

    void setLine(int line) { this->line = line; }
    virtual void print(int level) = 0;
    virtual void parseRecursive() = 0;
    virtual void generateIRRecursive() = 0;
};


/* ======================================= Type ========================================== */
class A_Type {
    // USED AS A NAMESPACE
public:
    static const int NONE   = -1;
    static const int VOID   = 0;
    static const int CHAR   = 1;
    static const int INT    = 2;
    static const int DOUBLE = 3;
    static const int BOOL   = 4;

    static bool isNumeric(int type) { return type == INT || type == DOUBLE || type == CHAR; }
    static bool isBool(int type) { return type == BOOL; }
    static bool isInteger(int type) { return type == CHAR || type == INT; }
};


/* ===================================== Expression ====================================== */
class A_Expression: public A_TreeNode {
    // INTERFACE WITH NO INSTANCE
public:
    // name in IR
    string ID = "\"@None@\"";
    // semantic type and value in parsing phase
    int semanticType;
    string semanticValue;
    // side effect expression opt flag
    bool useVal = true;

    A_Expression(): semanticType(A_Type::NONE), semanticValue("@None@") {}
    A_Expression(int semanticType, string semanticValue):
            semanticType(semanticType), semanticValue(semanticValue) {}
};

class A_NopExpression: public A_Expression {
    void print(int level) override ;
    void parseRecursive() override ;
    void generateIRRecursive() override ;
};

class A_BinaryExpression: public A_Expression {
public:
    // operation type
    static const int ADD        = 0;  // +
    static const int SUB        = 1;  // -
    static const int MUL        = 2;  // *
    static const int DIV        = 3;  // /
    static const int MOD        = 4;  // %
    static const int EQU        = 5;  // ==
    static const int NEQ        = 6;  // !=
    static const int GT         = 7;  // >
    static const int LT         = 8;  // <
    static const int NGT        = 9;  // <=
    static const int NLT        = 10; // >=
    static const int LOGIC_AND  = 11; // &&
    static const int LOGIC_OR   = 12; // ||
    static const int BIT_AND    = 13; // &
    static const int BIT_OR     = 14; // |
    static const int BIT_XOR    = 15; // ^
    static const int SHIFT_L    = 16; // <<
    static const int SHIFT_R    = 17; // >>
    static const int ASSIGN     = 18; // =
    static const int ASSIGN_ADD = 19; // +=
    static const int ASSIGN_SUB = 20; // -=
    static const int ASSIGN_MUL = 21; // *=
    static const int ASSIGN_DIV = 22; // /=
    static const int ASSIGN_MOD = 23; // %=
    static const int ARRAY_REF  = 24; // []   : op1 --> array name, op2 --> index

    int operatorType;
    A_Expression *op1, *op2;
    bool assignToMem = false;

    A_BinaryExpression(int operatorType, A_Expression *op1, A_Expression *op2):
            operatorType(operatorType), op1(op1), op2(op2) {}

    bool isArithmetic() { return operatorType <= SHIFT_R; }
    bool isAssign() { return operatorType >= ASSIGN && operatorType <= ASSIGN_MOD; }
    bool isCompoundAssign() { return operatorType >= ASSIGN_ADD && operatorType <= ASSIGN_MOD; }

    void print(int level) override ;
    void parseRecursive() override ;
    void generateIRRecursive() override ;
};

class A_UnaryExpression: public A_Expression {
public:
    // operation type
    static const int LOGIC_NOT   = 0;   // !
    static const int BIT_NOT     = 1;   // ~
    static const int POSTFIX_INC = 2;   // a++
    static const int PREFIX_INC  = 3;   // ++a
    static const int POSTFIX_DEC = 4;   // a--
    static const int PREFIX_DEC  = 5;   // --a

    int operatorType;
    A_Expression *op;

    A_UnaryExpression(int operatorType, A_Expression *op):
            operatorType(operatorType), op(op) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_CallExpression: public A_Expression {
public:
    string funcName;
    vector<A_Expression *> argumentList;

    A_CallExpression(string funcName, vector<A_Expression *> argumentList, int line):
            funcName(funcName), argumentList(argumentList) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_LiteralExpression: public A_Expression {
public:
    A_LiteralExpression(int type, string content, int line):
            A_Expression(type, content) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_VariableExpression: public A_Expression {
public:
//    const VarEntry *varInfo;
    explicit A_VariableExpression(string identifier, int line):
            A_Expression(A_Type::NONE, identifier) {
    setLine(line);
}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};


/* =============================== Declarator & Initializer ============================== */
class A_SimpleDeclarator: public A_TreeNode { // e.g. "a"
public:
    bool isArray;
    int capacity;
    string identifier;
    string ID;

    A_SimpleDeclarator(string identifier, int capacity, bool isArray, int line):
            identifier(identifier), capacity(capacity), isArray(isArray) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_FunctionDeclarator: public A_SimpleDeclarator { // "f(int a, double b)"
public:
    vector<pair<int, string>> parameterList;     // <para_type, para_name> pair

    A_FunctionDeclarator(string identifier, vector<pair<int, string>> parameterList, int line):
        A_SimpleDeclarator(identifier, 0, false, line), parameterList(parameterList) {}

    void parseRecursive() override ;
    void print(int level) override ;
};

class A_InitDeclarator: public A_TreeNode { // e.g. "a = 1" | "b[2][2] = {{1,2}, {3,4}}"
public:
    A_SimpleDeclarator *declarator;
    vector<A_Expression *> initializerList;

    A_InitDeclarator(A_SimpleDeclarator *declarator, vector<A_Expression *> initializerList):
        declarator(declarator), initializerList(initializerList) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};


/* ====================================== Statement ====================================== */

/*
 * interface for items that can appear in CompoundStatement
 * two concrete subclass: A_statement, A_Declaration
 */

class A_BlockItem: public A_TreeNode {
    // INTERFACE: DO NOT INSTANTIATE !!!
};

class A_Declaration: public A_BlockItem { // e.g. "int a = 0, b = 1, a[4] = {1,2,3}"
public:
    int type;
    vector<A_InitDeclarator *> initDeclaratorList;

    A_Declaration(int type, vector<A_InitDeclarator *> initDeclaratorList, int line):
            type(type), initDeclaratorList(initDeclaratorList) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_Statement: public A_BlockItem {
    // INTERFACE: DO NOT INSTANTIATE !!!
};

class A_ExpressionStatement: public A_Statement {
public:
    A_Expression *expression;     // CAUTION: CAN BE NULL !!!

    explicit A_ExpressionStatement(A_Expression *expression): expression(expression) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_CompoundStatement: public A_Statement {
public:
    vector<A_BlockItem *> blockItemList;

    explicit A_CompoundStatement(vector<A_BlockItem *> blockItemList, int line):
            blockItemList(blockItemList) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_SelectionStatement: public A_Statement {   // if without else
public:
    A_Expression *condition;
    A_Statement *branchTrue;

    A_SelectionStatement(A_Expression *condition, A_Statement *branchTrue, int line):
            condition(condition), branchTrue(branchTrue) {
        setLine(line);
    }

    void parseTrueBranch();
    void generateTrueBranch();

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_SelectionStatementWithElse: public A_SelectionStatement { // if with else
public:
    A_Statement *branchFalse;

    A_SelectionStatementWithElse(A_Expression *condition, A_Statement *branchTrue, A_Statement *branchFalse, int line):
            A_SelectionStatement(condition, branchTrue, line), branchFalse(branchFalse) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_IterationStatement: public A_Statement {
public:
    bool reverse;              // true only for do-while statement
    A_Statement *loopBody;
    A_Expression *condition;
    /* fields for IR generation */
    string breakLabel = "@None@";
    string continueLabel = "@None@";

    A_IterationStatement(A_Statement *loopBody, A_Expression *condition, bool reverse, int line):
            loopBody(loopBody), condition(condition), reverse(reverse) {
        setLine(line);
    }

    void parseSimpleLoop(bool flag);

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_ForStatement: public A_IterationStatement {
public:
    A_Expression *initCode;
    A_Expression *endCode;

    A_ForStatement(A_ExpressionStatement *initCode, A_Expression *endCode,
                   A_Statement *loopBody, A_ExpressionStatement *conditionStatement, int line):
            A_IterationStatement(loopBody, conditionStatement->expression, false, line),
            initCode(initCode->expression), endCode(endCode) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_ForStatementWithDeclaration: public A_IterationStatement {
public:
    A_Declaration *declaration;
    A_Expression *endCode;  // ALERT: NULLABLE

    A_ForStatementWithDeclaration(A_Declaration *declaration, A_Expression *endCode,
                                  A_Statement *loopBody, A_ExpressionStatement *conditionStatement, int line):
            A_IterationStatement(loopBody, conditionStatement->expression, false, line),
            declaration(declaration), endCode(endCode) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_JumpStatement: public A_Statement {
public:
    static const int BREAK    = 0;
    static const int CONTINUE = 1;

    int type;

    A_JumpStatement(int type, int line): type(type) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_ReturnStatement: public A_Statement {
public:
    A_Expression *expression;

    A_ReturnStatement(A_Expression *expression, int line): expression(expression) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};


class A_FunctionDefinition: public A_TreeNode {
public:
    int varCount = 0;
    int rtype;
    A_SimpleDeclarator *declarator;                          // "func_name(para ...)"
    A_CompoundStatement *funcBody;

    A_FunctionDefinition(int rtype, A_SimpleDeclarator *declarator, A_CompoundStatement *funcBody, int line):
            rtype(rtype), declarator(declarator), funcBody(funcBody) {
        setLine(line);
    }

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};

class A_TranslationUnit: public A_TreeNode {
public:
    vector<A_TreeNode *> externalDeclaration;

    A_TranslationUnit(vector<A_TreeNode *> externalDeclaration): externalDeclaration(externalDeclaration) {}

    void parseRecursive() override ;
    void print(int level) override ;
    void generateIRRecursive() override ;
};



void reportError(int line, string msg);

//static void parseBlock()

#endif //MYCOMPILER_TreeNode_H
