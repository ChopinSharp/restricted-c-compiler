#include "ASTNode.h"
#include <typeinfo>

using namespace std;

/* ===================================== IR Generatiron ================================== */
bool isArrayRef(A_Expression *exp) {
    auto ptr = dynamic_cast<A_BinaryExpression *>(exp);
    if (ptr != nullptr) {
        return ptr->operatorType == A_BinaryExpression::ARRAY_REF;
    }
    return false;
}

bool isLValue(A_Expression *exp) {
    return typeid(*exp) == typeid(A_VariableExpression) || isArrayRef(exp);
}


/* ===================================== IR Generatiron ================================== */
static int varNum = 0;
static int labelNum = 0;
static int tempNum = 0;
extern vector<string> IRList;

string assignVarID(int type) {  // used in parse phase
    string t;
    switch (type) {
        case A_Type::CHAR: case A_Type::INT: case A_Type::BOOL: t = "i"; break;
        case A_Type::DOUBLE: t = "f"; break;
        default: t = "u";
    }
    return "%var_" + t + "_" + to_string(varNum++);
}

string assignTmpID(int type) { // used in IR generation phase
    string t;
    switch (type) {
        case A_Type::CHAR: case A_Type::INT: case A_Type::BOOL: t = "i"; break;
        case A_Type::DOUBLE: t = "f"; break;
        default: t = "u";
    }
    return "%tmp_" + t + "_" + to_string(tempNum++);
}

string assignArgID(int type, int num) {
    string t;
    switch (type) {
        case A_Type::CHAR: case A_Type::INT: case A_Type::BOOL: t = "i"; break;
        case A_Type::DOUBLE: t = "f"; break;
        default: t = "u";
    }
    return "%arg_" + t + "_" + to_string(num);
}

inline string formThreeAddressIR
        (const string &opname, const string &dst, const string &src1, const string &src2 = "") {
    return opname + " " + dst + " " + src1 + " " + src2;
}


/* ===================================== Expression ====================================== */
void A_NopExpression::parseRecursive() {
    // empty
}

void A_NopExpression::generateIRRecursive() {
    // as for condition
    this->ID = "#true";
}

void A_BinaryExpression::parseRecursive(){
	op1->parseRecursive();
	op2->parseRecursive();
	// set line
	this->setLine(op1->line);
	// type checking for arithmetic, relational, logic, bitwise and assignment operation
	if (operatorType <= 23 && op1->semanticType != op2->semanticType) {
		reportError(this->line, "Type mismatch: incompatible types for binary operation");
	}
	// check rhs of assignment operation to be rvalue: array reference or variable
    if (operatorType >= 18 && operatorType <=23 && !isLValue(op1)) {
	    reportError(this->line, "assign to a rvalue");
	}
	switch (operatorType) {
	    // arithmetic operation:
        case ADD: case SUB: case MUL: case DIV: case MOD: {
            if (!A_Type::isNumeric(op1->semanticType)) {
                reportError(this->line, "Type mismatch: non-numeric type in arithmetic expression.");
            }
            this->semanticType = op1->semanticType;
            break;
	    }
	    // relational operation:
        case EQU: case NEQ: case GT: case LT: case NGT: case NLT: {
            if (!A_Type::isNumeric(op1->semanticType)) {
                reportError(this->line, "Type mismatch: non-numeric type in relational expression");
            }
            this->semanticType = A_Type::BOOL;
            break;
        }
        // logic operation:
        case LOGIC_AND: case LOGIC_OR: {
            if (!A_Type::isBool(op1->semanticType)) {
                reportError(this->line, "Type mismatch: non-boolean type in logic expression");
            }
            this->semanticType = A_Type::BOOL;
	        break;
	    }
	    // bit-wise operation
	    case BIT_AND: case BIT_OR: case BIT_XOR: {
            if (!A_Type::isInteger(op1->semanticType)) {
                reportError(this->line, "BIT operation can't operate on types other than INT");
            }
		    this->semanticType = op1->semanticType;
            break;
	    }
	    // shift operation
        case SHIFT_L: case SHIFT_R: {
            if (!A_Type::isInteger(op1->semanticType)) {
                reportError(this->line, "shift operation can't operate on types other than INT");
            }
            this->semanticType = op1->semanticType;
            break;
        }
	    // simple assignment operation:
	    case ASSIGN: {
            this->semanticType = op1->semanticType;
            // assign to an array element, expression value opt for lhs
            auto *lhs = dynamic_cast<A_BinaryExpression *>(op1);
            if (lhs != nullptr) {
                if (lhs->operatorType == A_BinaryExpression::ARRAY_REF) {
                    lhs->useVal = false;
                }
            }
            break;
	    }
	    // compound assignment operation:
	    case ASSIGN_ADD: case ASSIGN_SUB:
        case ASSIGN_MUL: case ASSIGN_DIV: case ASSIGN_MOD: {
		    this->semanticType = op1->semanticType;
            break;
        }
        // array indexing
	    case ARRAY_REF: {
            this->semanticType = op1->semanticType;
	        // check index type
            if (!A_Type::isInteger(op2->semanticType)) {
                reportError(this->line, "Type Error: non-integer type as array index");
            }
            // indexing a variable
            if (typeid(*op1) == typeid(A_VariableExpression)) {
                const VarEntry *entryPtr = SymbolInfo::resolveVarName(op1->semanticValue);
                // check if variable is an array
                if (!entryPtr->isArray) {
                    reportError(this->line, "Type Error: indexing a non-array variable: " + op1->semanticValue);
                }
                // check index range
                if (std::stoi(op2->semanticValue) >= entryPtr->capacity) {
                    reportError(this->line, "Index Error: index out of range, array of size " + to_string(entryPtr->capacity));
                }
            }
            else {
                reportError(this->line, "Type Error: index in to a non-variable");
            }
            break;
	    }
        default: reportError(this->line, "Internal Error: A_BinaryExpression::parseRecursive");
	} // end of switch
}

void A_BinaryExpression::generateIRRecursive(){
    // generate ID for children
    op1->generateIRRecursive();
    op2->generateIRRecursive();
    // assign temp ID
    if (useVal || isCompoundAssign() && isArrayRef(op1)) {   // expression value opt, compound assignment must use a temp variable
        this->ID = assignTmpID(this->semanticType);
    }
    // arithmetic, logic, bit-wise, relational
    if (isArithmetic()) {
        if (!useVal) {
            return ;
        }
        switch (operatorType) {
            case ADD        : IRList.push_back(formThreeAddressIR("add", this->ID, op1->ID, op2->ID)); break;
            case SUB        : IRList.push_back(formThreeAddressIR("sub", this->ID, op1->ID, op2->ID)); break;
            case MUL        : IRList.push_back(formThreeAddressIR("mul", this->ID, op1->ID, op2->ID)); break;
            case DIV        : IRList.push_back(formThreeAddressIR("div", this->ID, op1->ID, op2->ID)); break;
            case MOD        : IRList.push_back(formThreeAddressIR("mod", this->ID, op1->ID, op2->ID)); break;
            case EQU        : IRList.push_back(formThreeAddressIR("equ", this->ID, op1->ID, op2->ID)); break;
            case NEQ        : IRList.push_back(formThreeAddressIR("neq", this->ID, op1->ID, op2->ID)); break;
            case GT         : IRList.push_back(formThreeAddressIR("gt ", this->ID, op1->ID, op2->ID)); break;
            case LT         : IRList.push_back(formThreeAddressIR("lt ", this->ID, op1->ID, op2->ID)); break;
            case NGT        : IRList.push_back(formThreeAddressIR("ngt", this->ID, op1->ID, op2->ID)); break;
            case NLT        : IRList.push_back(formThreeAddressIR("nlt", this->ID, op1->ID, op2->ID)); break;
            case LOGIC_AND  : IRList.push_back(formThreeAddressIR("and", this->ID, op1->ID, op2->ID)); break;
            case LOGIC_OR   : IRList.push_back(formThreeAddressIR("or ", this->ID, op1->ID, op2->ID)); break;
            case BIT_AND    : IRList.push_back(formThreeAddressIR("and", this->ID, op1->ID, op2->ID)); break;
            case BIT_OR     : IRList.push_back(formThreeAddressIR("or ", this->ID, op1->ID, op2->ID)); break;
            case BIT_XOR    : IRList.push_back(formThreeAddressIR("xor", this->ID, op1->ID, op2->ID)); break;
            case SHIFT_L    : IRList.push_back(formThreeAddressIR("shl", this->ID, op1->ID, op2->ID)); break;
            case SHIFT_R    : IRList.push_back(formThreeAddressIR("shr", this->ID, op1->ID, op2->ID)); break;
            default: ;/* unreachable */
        }
    }
    // assignment expression
    else if (isAssign()) {
        // side effect
        auto lhs = dynamic_cast<A_BinaryExpression *>(this->op1);
        // assign to memory location
        if (lhs != nullptr && lhs->operatorType == A_BinaryExpression::ARRAY_REF) {
            const string &value = op2->ID;
            const string &base = lhs->op1->ID;
            const string &displacement = lhs->op2->ID;
            const string &element = lhs->ID;
            switch (operatorType) {
                case ASSIGN:
                    IRList.push_back(formThreeAddressIR("reg2mem", value, base, displacement));
                    break;
                case ASSIGN_ADD:
                    IRList.push_back(formThreeAddressIR("add", this->ID, element, value));
                    IRList.push_back(formThreeAddressIR("reg2mem", this->ID, base, displacement));
                    break;
                case ASSIGN_SUB:
                    IRList.push_back(formThreeAddressIR("sub", this->ID, element, value));
                    IRList.push_back(formThreeAddressIR("reg2mem", this->ID, base, displacement));
                    break;
                case ASSIGN_MUL:
                    IRList.push_back(formThreeAddressIR("mul", this->ID, element, value));
                    IRList.push_back(formThreeAddressIR("reg2mem", this->ID, base, displacement));
                    break;
                case ASSIGN_DIV:
                    IRList.push_back(formThreeAddressIR("div", this->ID, element, value));
                    IRList.push_back(formThreeAddressIR("reg2mem", this->ID, base, displacement));
                    break;
                case ASSIGN_MOD:
                    IRList.push_back(formThreeAddressIR("mod", this->ID, element, value));
                    IRList.push_back(formThreeAddressIR("reg2mem", this->ID, base, displacement));
                    break;
                default: /* unreachable */ ;
            }
        }
        // assign to variable
        else {
            switch (operatorType) {
                case 18 : IRList.push_back(formThreeAddressIR("assign", op1->ID, op2->ID)); break;
                case 19 : IRList.push_back(formThreeAddressIR("add", op1->ID, op1->ID , op2->ID)); break;
                case 20 : IRList.push_back(formThreeAddressIR("sub", op1->ID, op1->ID , op2->ID)); break;
                case 21 : IRList.push_back(formThreeAddressIR("mul", op1->ID, op1->ID , op2->ID)); break;
                case 22 : IRList.push_back(formThreeAddressIR("div", op1->ID, op1->ID , op2->ID)); break;
                case 23 : IRList.push_back(formThreeAddressIR("mod", op1->ID, op1->ID , op2->ID)); break;
                default: /* unreachable */ ;
            }
        }
        // expression value
        if (useVal) {
            IRList.push_back(formThreeAddressIR("assign", this->ID, op1->ID));
        }
    }
    // index expression
    else {
        if (useVal) {
            IRList.push_back(formThreeAddressIR("mem2reg", this->ID, op1->ID, op2->ID));
        }
    }
}

void A_UnaryExpression::parseRecursive() {
	op->parseRecursive();
	this->setLine(op->line);
	switch (operatorType) {
	    case LOGIC_NOT: {
            //type checking
            if (!A_Type::isBool(op->semanticType)) {
                reportError(this->line, "LOGIC_NOT can't operate on operand other than BOOL.");
            }
            this->semanticType = A_Type::BOOL;
            break;
	    }
        case BIT_NOT: {
            //type checking
            if (!A_Type::isInteger(op->semanticType)) {
                reportError(this->line, "BIT_NOT can't operate on operand other than INT.");
            }
            this->semanticType = op->semanticType;
            break;
        }
        case POSTFIX_INC: case PREFIX_INC: case POSTFIX_DEC: case PREFIX_DEC: {
            //type checking
            if (!A_Type::isInteger(op->semanticType)) {
                reportError(this->line, "self-in(de)crease on a non-integer type");
            }
            if (!isLValue(op)) {
                reportError(this->line, "self-in(de)crease on a rvalue");
            }
            this->semanticType = op->semanticType;
            break;
        }
        default: reportError(this->line, "Internal Error: A_UnaryExpression::parseRecursive");
	} // end of switch
}

void A_UnaryExpression::generateIRRecursive() {
    // generate ID for children
    op->generateIRRecursive();
    // assign temp ID
    if (useVal) {
        this->ID = assignTmpID(this->semanticType);
    }
    switch (this->operatorType) {
        case LOGIC_NOT:
            if (useVal) {
                IRList.push_back(formThreeAddressIR("xor", this->ID, op->ID, "#1"));
            }
            break;
        case BIT_NOT:
            if (useVal) {
                IRList.push_back(formThreeAddressIR("not", this->ID, op->ID));
            }
            break;
        case POSTFIX_INC:
            if (useVal) {
                IRList.push_back(formThreeAddressIR("assign", this->ID, op->ID));
            }
            IRList.push_back(formThreeAddressIR("addi", op->ID, op->ID, "#1"));
            break;
        case PREFIX_INC:
            IRList.push_back(formThreeAddressIR("addi", op->ID, op->ID, "#1"));
            if (useVal) {
                IRList.push_back(formThreeAddressIR("assign", this->ID, op->ID));
            }
            break;
        case POSTFIX_DEC:
            if (useVal) {
                IRList.push_back(formThreeAddressIR("assign", this->ID, op->ID));
            }
            IRList.push_back(formThreeAddressIR("addi", op->ID, op->ID, "#-1"));
            break;
        case PREFIX_DEC:
            IRList.push_back(formThreeAddressIR("addi", op->ID, op->ID, "#-1"));
            if (useVal) {
                IRList.push_back(formThreeAddressIR("assign", this->ID, op->ID));
            }
            break;
        default: reportError(this->line, "Internal Error: A_UnaryExpression::generateIRRecursive");
    }
}

void A_CallExpression::parseRecursive() {
    // resolve function name
    const FunEntry *entryPtr = SymbolInfo::resolveFunName(this->funcName);
    if (entryPtr == nullptr || !entryPtr->isDefinied) {
        reportError(this->line, "Name Error: function " + this->funcName + " undefined");
    }
    // check argument number
    int argNum = this->argumentList.size(), paraNum = entryPtr->paraList.size();
    if (argNum != paraNum) {
        reportError(this->line, "Call Error: expect " + to_string(paraNum) + " argument(s), "
            + to_string(argNum) + " found");
    }
    // parse and check arguments
    for (int i = 0; i < argNum; i++) {
        auto argPtr = this->argumentList[i];
        // parse argument
        argPtr->parseRecursive();
        // type checking
        if (argPtr->semanticType != entryPtr->paraList[i].first) {
            reportError(this->line, "Type Error: at call to " + this->funcName
                + ", argument " + to_string(i + 1));
        }
    }
	this->semanticType = entryPtr->type;
}

void A_CallExpression::generateIRRecursive(){
    // generate IR for arguments
    for (auto &arg : this->argumentList) {
        arg->generateIRRecursive();
    }
    int count = 0;
    for (auto &arg : this->argumentList) {
        IRList.push_back("arg " + to_string(count++) + " " + arg->ID);
    }
    // assign temp ID
    if (this->semanticType != A_Type::VOID) {
        this->ID = assignTmpID(this->semanticType);
    }
    else {
        this->ID = "*";
    }
    IRList.push_back(formThreeAddressIR("call", this->ID, this->funcName));
}

void A_LiteralExpression::parseRecursive() {
    // semanticValue is initialized in the constructor
    // BLANK
}

void A_LiteralExpression::generateIRRecursive() {
    // literal value as ID
    if (this->semanticValue == "true") {
        this->semanticValue = "1";
    }
    if (this->semanticValue == "false") {
        this->semanticValue = "0";
    }
    // assign temp ID
    this->ID = assignTmpID(this->semanticType);
    IRList.push_back(formThreeAddressIR("li", this->ID, "#" + this->semanticValue));
}

void A_VariableExpression::parseRecursive() {
	// resolve variable name
    // semanticValue stores identifier
    const VarEntry *varInfo = SymbolInfo::resolveVarName(this->semanticValue);
	// name not found, report error
    if (varInfo == nullptr) {
        reportError(this->line, "Name Error: " + this->semanticValue + " is not declared");
    }
    this->semanticType = varInfo->type;
    this->ID = varInfo->ID;
}

void A_VariableExpression::generateIRRecursive() {
    // ID has already be recorded in node, nothing to be done

}


/* =============================== Declarator & Initializer ============================== */
void A_SimpleDeclarator::parseRecursive() {
    // empty
}

void A_SimpleDeclarator::generateIRRecursive() {
    // allocate memory for array
    if (isArray) {
        IRList.push_back("array " + this->ID + " " + to_string(this->capacity));
    }
}

void A_FunctionDeclarator::parseRecursive() {
    // empty
}

void A_InitDeclarator::parseRecursive() {
    // parse children
    this->declarator->parseRecursive();
    for (auto child: this->initializerList) {
        child->parseRecursive();
    }
}

void A_InitDeclarator::generateIRRecursive() {
    // generate IR for children
    this->declarator->generateIRRecursive();
    for (auto &item : this->initializerList) {
        item->generateIRRecursive();
    }
    // no initial value provided, work done
    if (this->initializerList.empty()) {
        return ;
    }
    // array initialization
    if (this->declarator->isArray) {
        for (int i = 0; i < this->initializerList.size(); i++) {
            IRList.push_back(formThreeAddressIR("reg2mem ", this->initializerList[i]->ID, this->declarator->ID, to_string(i)));
        }


    }
    // variable initialization
    else if (typeid(*(this->declarator)) == typeid(A_SimpleDeclarator)) {
        IRList.push_back(formThreeAddressIR("assign ", this->declarator->ID, this->initializerList[0]->ID));
    }
    // else: function declarator, already checked in parsing phase
}


/* ====================================== Statement ====================================== */
void A_Declaration::parseRecursive() {
    for (auto child: this->initDeclaratorList) {
        // parse children
        child->parseRecursive();
        A_SimpleDeclarator *declarator = child->declarator;
        const vector<A_Expression *> &initializerList = child->initializerList;

        int lineNum = declarator->line;

        auto funDeclarator = dynamic_cast<A_FunctionDeclarator *>(declarator);
        // function declaration
        if (funDeclarator != nullptr) {
            // check syntax
            if (!initializerList.empty()) {
                reportError(lineNum, "Syntax Error: non-empty initializer list for a function");
            }
            // check for duplicate declaration
            if (SymbolInfo::funcPool.find(funDeclarator->identifier) != SymbolInfo::funcPool.end()) {
                reportError(lineNum, "Redefinition of function " + funDeclarator->identifier);
            }
            // update function pool
            FunEntry newEntry(funDeclarator->identifier, this->type, false, funDeclarator->parameterList);
            SymbolInfo::funcPool.insert(make_pair(funDeclarator->identifier, newEntry));
        }
        // variable declaration: scalar or array
        else {
            // check current symbol table for duplicate
            SymbolTable &tbl = *(SymbolInfo::tableStack.rbegin());
            if (tbl.resolveName(declarator->identifier) != nullptr) {
                reportError(lineNum, "Duplicate declaration for name " + declarator->identifier);
            }
            // parse initializer list
            if (initializerList.size() > declarator->capacity) {
                reportError(lineNum, "Syntax Error: size mismatch for initialization");
            }
            for (auto expr : initializerList) {
                expr->parseRecursive();
                if (expr->semanticType != this->type) {
                    reportError(lineNum, "Type Error: type mismatch in initializer list");
                }
            }
            // assign var id
            declarator->ID = assignVarID(this->type);
            VarEntry newEntry(declarator->ID, this->type, declarator->capacity, declarator->isArray);
            tbl.varMap.insert(make_pair(declarator->identifier, newEntry));
        }

    } // end of for
}

void A_Declaration::generateIRRecursive() {
    // generate IR for variable initialization
    for (A_InitDeclarator *initDec : this->initDeclaratorList) {
        // generate IR for child
        initDec->generateIRRecursive();
    }
}


void A_ExpressionStatement::parseRecursive() {
//    if (expression != nullptr) {
    // expression used for side effect, flag to disable temp variable generation
    expression->useVal = false;
    expression->parseRecursive();
//    }
}

void A_ExpressionStatement::generateIRRecursive() {
    // generate IR for child
    this->expression->generateIRRecursive();
}

void A_CompoundStatement::parseRecursive() {
    // parse children
    for (auto child: this->blockItemList) {
        child->parseRecursive();
    }
    // no type checking
}

void A_CompoundStatement::generateIRRecursive() {
    // generate IR for children
    for (auto &item : this->blockItemList) {
        item->generateIRRecursive();
    }
}

void A_SelectionStatement::parseTrueBranch() {
    // parse & type check first child
    this->condition->parseRecursive();
    if (!A_Type::isBool(this->condition->semanticType)) {
        reportError(this->line, "Type Error: Non-boolean type as the `if` condition");
    }

    // parse the true branch
    // a statement block is found, push a new table
    if (typeid(*(this->branchTrue)) == typeid(A_CompoundStatement)) {
        if (SymbolInfo::tableStack.empty()) {
            reportError(this->line, "Internal Error: A_SelectionStatement::parseTrueBranch");
        }
        SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
        // inherit continueTag and breakTag from outer scope
        SymbolTable emptySymbolTable(currentTable.funName, currentTable.rtype, currentTable.breakTag, currentTable.continueTag);
        SymbolInfo::tableStack.push_back(emptySymbolTable);
        this->branchTrue->parseRecursive();
        SymbolInfo::tableStack.pop_back();
    }
    // not a block
    else {
        this->branchTrue->parseRecursive();
    }
}

void A_SelectionStatement::parseRecursive() {
    // parse true branch (with type checking)
    this->parseTrueBranch();
}

void A_SelectionStatement::generateTrueBranch() {
    // generate IR for condition
    this->condition->generateIRRecursive();
    // assign label for true branch exit
    string skipLabel = "label_" + to_string(labelNum++);
    // generate branch logic
    IRList.push_back("ifn " + this->condition->ID + " goto " + skipLabel);
    // generate IR in true branch
    this->branchTrue->generateIRRecursive();
    // wirte out label
    IRList.push_back("Label " + skipLabel);
}

void A_SelectionStatement::generateIRRecursive() {
    this->generateTrueBranch();
}

void A_SelectionStatementWithElse::parseRecursive() {
    // parse true branch (with type checking)
    this->parseTrueBranch();
    // found a block push a table on the stack
    if (typeid(*(this->branchFalse)) == typeid(A_CompoundStatement)) {
        if (SymbolInfo::tableStack.empty()) {
            reportError(this->line, "Internal Error: A_SelectionStatementWithElse::parseRecursive");
        }
        SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
        // inherit continueTag and breakTag from outer scope
        SymbolTable emptySymbolTable(currentTable.funName, currentTable.rtype, currentTable.breakTag, currentTable.continueTag);
        SymbolInfo::tableStack.push_back(emptySymbolTable);
        this->branchFalse->parseRecursive();
        SymbolInfo::tableStack.pop_back();
    }
    // not a block
    else {
        this->branchFalse->parseRecursive();
    }
}

void A_SelectionStatementWithElse::generateIRRecursive() {
    /* generate IR for true branch */
    this->generateTrueBranch();
    /* assign label for false branch exit */
    string skipLabel = "label_" + to_string(labelNum++);
    // generate branch logic
    IRList.push_back("if " + this->condition->ID + " goto " + skipLabel);
    // generate IR in false branch
    this->branchFalse->generateIRRecursive();
    // wirte out label
    IRList.push_back("Label " + skipLabel);
}

// @flag: set to disable symbol table creation,
//        used in for loop with declaration in which a symbol table is already created
void A_IterationStatement::parseSimpleLoop(bool flag) {
    // parse condition
    this->condition->parseRecursive();
    // type check condition
    if (!A_Type::isBool(this->condition->semanticType) &&
        typeid(*(this->condition)) != typeid(A_NopExpression)) {
        reportError(this->line, "Type Error: Non-boolean type as loop condition");
    }
    // parse loopBody
    // set jump label for IR generation
    if (flag) {
        this->breakLabel = "break_" + to_string(labelNum++);
        this->continueLabel = "continue_" + to_string(labelNum++);
    }
    // push new table
    if (typeid(*(this->loopBody)) == typeid(A_CompoundStatement) && flag) {
        if (SymbolInfo::tableStack.empty()) {
            reportError(this->line, "Internal Error: A_IterationStatement::parseSimpleLoop");
        }
        SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
        SymbolTable emptySymbolTable(currentTable.funName, currentTable.rtype, this->breakLabel, this->continueLabel);
        SymbolInfo::tableStack.push_back(emptySymbolTable);
        this->loopBody->parseRecursive();
        SymbolInfo::tableStack.pop_back();
    }
    else {
        this->loopBody->parseRecursive();
    }
}

void A_IterationStatement::parseRecursive() {
    // parse children
    this->parseSimpleLoop(true);
}

void A_IterationStatement::generateIRRecursive() {
    // write out continue label at the entrance of the loop
    IRList.push_back("Label " + this->continueLabel);
    // IR for condition
    this->condition->generateIRRecursive();
    // flow control logic at the entrance
    IRList.push_back("ifn " + this->condition->ID + " goto " + this->breakLabel);
    // IR for loop body
    this->loopBody->generateIRRecursive();
    // flow control logic at the exit
    IRList.push_back("goto " + this->continueLabel);
    // write out break label at the exit of the loop
    IRList.push_back("Label " + this->breakLabel);
}

void A_ForStatement::parseRecursive() {
    // expression value opt
    this->initCode->useVal = false;
    this->endCode->useVal = false;
    // parse initCode
    this->initCode->parseRecursive();
    // parse loopBody and condition
    this->parseSimpleLoop(true);
    // parse endCode
    if (endCode == nullptr) {
        this->endCode->parseRecursive();
    }
}

void A_ForStatement::generateIRRecursive() {
    // IR for init code
    this->initCode->generateIRRecursive();
    // write out continue label at the entrance of the loop
    IRList.push_back("Label " + this->continueLabel);
    // IR for condition
    this->condition->generateIRRecursive();
    // flow control logic at the entrance
    IRList.push_back("ifn " + this->condition->ID + " goto " + this->breakLabel);
    // IR for loop body
    this->loopBody->generateIRRecursive();
    // IR for end code
    this->endCode->generateIRRecursive();
    // flow control logic at the exit
    IRList.push_back("goto " + this->continueLabel);
    // write out break label at the exit of the loop
    IRList.push_back("Label " + this->breakLabel);
}

void A_ForStatementWithDeclaration::parseRecursive() {
    // expression value opt
    this->endCode->useVal = false;
    // push a new table and parse declaration
    this->breakLabel = "break_" + to_string(labelNum++);
    this->continueLabel = "continue_" + to_string(labelNum++);
    if (SymbolInfo::tableStack.empty()) {
        reportError(this->line, "Internal Error: A_ForStatementWithDeclaration::parseRecursive");
    }
    SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
    SymbolTable emptySymbolTable(currentTable.funName, currentTable.rtype, breakLabel, continueLabel);
    SymbolInfo::tableStack.push_back(emptySymbolTable);
    this->declaration->parseRecursive();
    // parse loopBody and conditon, DISABLE table creation
    this->parseSimpleLoop(false);
    // prase endCode
    this->endCode->parseRecursive();
}

void A_ForStatementWithDeclaration::generateIRRecursive() {
    // IR for init code
    this->declaration->generateIRRecursive();
    // write out continue label at the entrance of the loop
    IRList.push_back("Label " + this->continueLabel);
    // IR for condition
    this->condition->generateIRRecursive();
    // flow control logic at the entrance
    IRList.push_back("ifn " + this->condition->ID + " goto " + this->breakLabel);
    // IR for loop body
    this->loopBody->generateIRRecursive();
    // IR for end code
    this->endCode->generateIRRecursive();
    // flow control logic at the exit
    IRList.push_back("goto " + this->continueLabel);
    // write out break label at the exit of the loop
    IRList.push_back("Label " + this->breakLabel);
}

void A_JumpStatement::parseRecursive() {
    const SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
    switch (this->type) {
        case A_JumpStatement::BREAK:
            if (!currentTable.canBreak()) {
                reportError(this->line, "`break` inside a unbreakable block");
            }
            break;
        case A_JumpStatement::CONTINUE:
            if (!currentTable.canContinue()) {
                reportError(this->line, "`continue` inside a uncontinuable block");
            }
            break;
        default: reportError(this->line, "Internal Error: A_JumpStatement::parseRecursive");
    }
}

void A_JumpStatement::generateIRRecursive() {
    const SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
    if (this->type == A_JumpStatement::BREAK) {
        IRList.push_back("goto " + currentTable.breakTag);
    }
    else if (this->type == A_JumpStatement::CONTINUE) {
        IRList.push_back("goto " + currentTable.continueTag);
    }
}

void A_ReturnStatement::parseRecursive() {
    const SymbolTable &currentTable = *(SymbolInfo::tableStack.rbegin());
    if (!currentTable.isFunction()) {
        reportError(this->line, "return outside a function definition block");
    }
    // parse child
    this->expression->parseRecursive();
    // type checking
    if (this->expression->semanticType != currentTable.rtype) {
        reportError(this->line, "Type Error: return type mismatch for function " + currentTable.funName);
    }
}

void A_ReturnStatement::generateIRRecursive() {
    // IR for return value
    this->expression->generateIRRecursive();
    IRList.push_back("return " + this->expression->ID);
}

/* ==================================== Function Definition ============================== */
void A_FunctionDefinition::parseRecursive() {
    int lineNum = declarator->line;
    // PHASE 1: parse declaration, update function pool
    auto funDeclarator = dynamic_cast<A_FunctionDeclarator *>(declarator);
    if (funDeclarator == nullptr) {
        reportError(lineNum, "Syntax Error: Non-function declarator within a function definition");
    }
    declarator->parseRecursive();
    // lookup function pool first
    auto iter = SymbolInfo::funcPool.find(funDeclarator->identifier);
    // found in function pool
    if (iter != SymbolInfo::funcPool.end()) {
        auto &entry = iter->second;
        // function redefinition
        if (entry.isDefinied) {
            reportError(lineNum, "Syntax Error: Redefinition of function " + declarator->identifier);
        }
        // declared but not defined, check consistency
        if (entry.type != this->rtype) {
            reportError(lineNum, "Syntax Error: return type mismatch between declaration and definition of function "
                              + funDeclarator->identifier);
        }
        if (entry.paraList != funDeclarator->parameterList) {   // -*- interesting -*-
            reportError(lineNum, "Syntax Error: parameter list  mismatch between declaration and definition of function "
                + funDeclarator->identifier);
        }
        // pass type checking, flag as defined
        entry.isDefinied = true;
    }
    // not found in function pool
    else {
        // create new entry, insert into function pool
        FunEntry newEntry(funDeclarator->identifier, this->rtype, true, funDeclarator->parameterList);
        SymbolInfo::funcPool.insert(make_pair(funDeclarator->identifier, newEntry));
    }

    // PHASE 2: parse function body
    // push a new table and parse funcBody
    int parameterNum = 0;
    SymbolTable newTable(funDeclarator->identifier, this->rtype);
    for (auto &item: funDeclarator->parameterList) {
        // item: pair<type: int, name: string>
        // assign ID for parameter
        VarEntry e(assignArgID(item.first, parameterNum++), item.first, 1, false);
        newTable.varMap.insert(make_pair(item.second, e));
    }
    SymbolInfo::tableStack.push_back(newTable);
    int oldVarNum = varNum, oldTmpNum = tempNum;
    funcBody->parseRecursive();
    this->varCount = varNum - oldVarNum;

    // pop symbol table
    SymbolInfo::tableStack.pop_back();
}

void A_FunctionDefinition::generateIRRecursive() {
    // write out function label (function name)
    IRList.push_back("Function " + this->declarator->identifier);
    IRList.emplace_back("$"); // for IR output format
    // IR for function body
    int oldTmpNum = tempNum;
    this->declarator->generateIRRecursive();
    this->funcBody->generateIRRecursive();
    IRList.emplace_back("$");
    auto funcDec = dynamic_cast<A_FunctionDeclarator *>(this->declarator);
    if (funcDec != nullptr) {
        IRList.push_back("End " + to_string(funcDec->parameterList.size())+ " "
                               + to_string(this->varCount) + " " + to_string(tempNum - oldTmpNum));
    }
    else {
        reportError(-1, "Internal Error: A_FunctionDefinition::generateIRRecursive");
    }
}


/* ==================================== Start Symbol ===================================== */
void A_TranslationUnit::parseRecursive() {
    // parse child
    for (auto child: this->externalDeclaration) {
        child->parseRecursive();
    }
}

void A_TranslationUnit::generateIRRecursive() {
    // generate IR for children
    for (auto &item : this->externalDeclaration) {
        item->generateIRRecursive();
    }
}


/* =================================== Print ============================================== */
const char *BinaryOpNameTable[] = {"add", "sub", "mul", "div", "mod",
                                    "equ", "neq", "gt", "lt", "ngt", "nlt",
                                    "logic_and", "logic_or",
                                    "bit_and", "bit_or", "bit_xor", "shift_l", "shift_r",
                                    "assign", "assign_add", "assign_sub", "assign_mul", "assign_div", "assign_mod",
                                    "array_ref"};

const char *UnaryOpNameTable[] = {"logic_not", "bit_not", "postfix_inc", "prefix_inc", "postfix_dec", "prefix_dec"};
const char *TypeNameTable[] = {"void", "char", "int", "double", "bool"};

void printDot(int level) {
    for (int i = 0; i < level; i++)
    {
        cout << "|   ";
    }
}

void A_NopExpression::print(int level) {
    printDot(level);
    cout << "nop_expression" << endl;
}

void A_BinaryExpression::print(int level) {
    printDot(level);
    cout << "binary_expression -> op: " << BinaryOpNameTable[this->operatorType] << endl;
    op1->print(level + 1);
    op2->print(level + 1);
}

void A_UnaryExpression::print(int level) {
    printDot(level);
    cout << "unary_expression -> op: " << UnaryOpNameTable[this->operatorType] << endl;
    op->print(level + 1);
}

void A_CallExpression::print(int level) {
    printDot(level);
    cout << "call_expression -> name: " << this->funcName << endl;
    for (auto &child: argumentList) {
        child->print(level + 1);
    }
}

void A_LiteralExpression::print(int level) {
    printDot(level);
    cout << "literal_expression -> type: " << TypeNameTable[this->semanticType]
                       << ", value: " << this->semanticValue << endl;
}

void A_VariableExpression::print(int level) {
    printDot(level);
    cout << "variale expression -> identifier: " << this->semanticValue << endl;
}

void A_SimpleDeclarator::print(int level) {
    printDot(level);
    cout << "simple_declarator -> identifier: " << this->identifier;
    if (isArray) {
        cout << ", capacity: " << this->capacity;
    }
    cout << endl;
}

void A_FunctionDeclarator::print(int level) {
    printDot(level);
    cout << "function_declarator -> identifier: " << this->identifier;
    cout << ", parameter_list: [ ";
    if (this->parameterList.empty()) {
        cout << "empty ";
    }
    for (auto &item : this->parameterList) {
        cout << "type: " << TypeNameTable[item.first] << ", name: " << item.second << "; ";
    }
    cout << "]" << endl;
}

void A_InitDeclarator::print(int level) {
    printDot(level);
    cout << "init_declarator" << endl;
    declarator->print(level + 1);
    for (auto &item : initializerList) {
        item->print(level + 1);
    }
}

void A_Declaration::print(int level) {
    printDot(level);
    cout << "declaration -> type: " << TypeNameTable[this->type] << endl;
    for (auto &item : initDeclaratorList) {
        item->print(level + 1);
    }
}

void A_ExpressionStatement::print(int level) {
    printDot(level);
    cout << "expression_statement" << endl;
    if (expression != nullptr)
        expression->print(level + 1);
}

void A_CompoundStatement::print(int level) {
    printDot(level);
    cout << "compound_statement" << endl;
    for (auto &item : blockItemList) {
        item->print(level + 1);
    }
}

void A_SelectionStatement::print(int level) {
    printDot(level);
    cout << "selection_statement" << endl;
    condition->print(level + 1);
    branchTrue->print(level + 1);
}

void A_SelectionStatementWithElse::print(int level) {
    printDot(level);
    cout << "selection_statement_with_else" << endl;
    condition->print(level + 1);
    branchTrue->print(level + 1);
    branchFalse->print(level + 1);
}

void A_IterationStatement::print(int level) {
    printDot(level);
    cout << "iteration_statement -> reverse: " << reverse << endl;
    condition->print(level + 1);
    loopBody->print(level + 1);
}

void A_ForStatement::print(int level) {
    printDot(level);
    cout << "for_statement" << endl;
    initCode->print(level + 1);
    condition->print(level + 1);
    endCode->print(level + 1);
    loopBody->print(level + 1);
}

void A_ForStatementWithDeclaration::print(int level) {
    printDot(level);
    cout << "for_statement_with_dec" << endl;
    declaration->print(level + 1);
    condition->print(level + 1);
    endCode->print(level + 1);
    loopBody->print(level + 1);
}

void A_JumpStatement::print(int level) {
    printDot(level);
    cout << "jump_statement -> type: " << TypeNameTable[type] << endl;
}

void A_ReturnStatement::print(int level) {
    printDot(level);
    cout << "return_statement" << endl;
    expression->print(level + 1);
}

void A_FunctionDefinition::print(int level) {
    printDot(level);
    cout << "function_definition -> rtype: " << TypeNameTable[rtype] << endl;
    declarator->print(level + 1);
    funcBody->print(level + 1);
}

void A_TranslationUnit::print(int level) {
    printDot(level);
    cout << "translation_unit" << endl;
    for (auto &item : externalDeclaration) {
        item->print(level + 1);
    }
}
void reportError(int line, string msg) {
    std::cerr << "line " << line << ": " << msg << std::endl;
    exit(1);
}

