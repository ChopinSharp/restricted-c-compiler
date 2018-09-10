%{
    #include <iostream>
    #include "ASTNode.h"
    extern int line;
    extern int column;
    extern int yylex();
    void yyerror(char const *);
    std::vector<A_TreeNode *> externalDeclaration;
    A_TranslationUnit *unit;
%}

%union {
    int pos;
    std::pair<int, int> *type;
    std::string *str;
    std::pair<std::string, int> *id;
    A_TreeNode *treeNode;
    A_FunctionDefinition *funcDef;
    A_Expression *exp;
    A_BinaryExpression *binExp;
    A_UnaryExpression *unExp;
    A_CallExpression *callExp;
    std::vector<A_Expression *> *arguments;
    A_LiteralExpression *literExp;
    A_VariableExpression *varExp;
    std::vector<std::pair<int, std::string> > *params;
    A_SimpleDeclarator *simpleDec;
    A_FunctionDeclarator *funcDec;
    std::vector<A_InitDeclarator *> *initDecList;
    A_InitDeclarator *initDec;
    std::vector<A_BlockItem *> *itemList;
    A_BlockItem *item;
    A_Declaration *declaration;
    A_Statement *statement;
    A_ExpressionStatement *expState;
    A_CompoundStatement *compState;
    A_SelectionStatement *selState;
    A_SelectionStatementWithElse *selStateWithElse;
    A_IterationStatement *iterState;
    A_ForStatement *forState;
    A_ForStatementWithDeclaration *forStateWithDec;
    A_JumpStatement *jumpState;
    A_ReturnStatement *retState;
}

%token <id> IDENTIFIER 
%token <str> CONSTANT_INT CONSTANT_DOUBLE STRING_LITERAL TRUE FALSE
%token <pos> VOID CHAR INT DOUBLE BOOL
%token <pos> IF ELSE FOR WHILE DO SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token <pos> '+' '-' '*' '/' '%'
%token <pos> EQU_OP NEQ_OP GT_OP LT_OP NGT_OP NLT_OP LOGIC_AND LOGIC_OR
%token <pos> '&' '|' '^'
%token <pos> SHIFT_L SHIFT_R
%token <pos> '=' ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%token <pos> ',' '[' ']' '!' '~' INC DEC
%token <pos> '(' ')' '{' '}' ';'

%type <treeNode> external_declaration
%type <funcDef> function_definition
%type <type> type_specifier
%type <exp> expression
%type <binExp> binary_expression
%type <unExp> unary_expression postfix_expression prefix_expression
%type <callExp> call_expression
%type <arguments> argument_list
%type <literExp> literal_expression
%type <varExp> variable_expression
%type <params> parameter_list
%type <simpleDec> simple_declarator
%type <simpleDec> array_declarator
%type <funcDec> function_declarator
%type <initDecList> init_declarator_list
%type <initDec> init_declarator
%type <arguments> initializers
%type <itemList> block_item_list
%type <item> block_item
%type <declaration> declaration
%type <statement> statement
%type <expState> expression_statement
%type <compState> compound_statement
%type <selState> selection_statement
%type <selStateWithElse> selection_statement_with_else
%type <iterState> iteration_statement
%type <forState> for_statement
%type <forStateWithDec> for_statement_with_declaration
%type <jumpState> jump_statement
%type <retState> return_statement

%left ','
%right '=' ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%left LOGIC_OR
%left LOGIC_AND
%left '|'
%left '^'
%left '&'
%left EQU_OP NEQ_OP
%left GT_OP LT_OP NGT_OP NLT_OP
%left SHIFT_L SHIFT_R
%left '+' '-'
%left '*' '/' '%'
%nonassoc '~'
%nonassoc '!'
%nonassoc PREFIX
%nonassoc POSTFIX
%nonassoc NO_ELSE
%nonassoc WITH_ELSE

%%

Program:
    translation_unit {
        unit = new A_TranslationUnit(externalDeclaration);
    }
    ;

translation_unit:
    external_declaration {
        externalDeclaration.emplace_back($1);
    }
    | translation_unit external_declaration{
        externalDeclaration.emplace_back($2);
    }
    ;

external_declaration:
    function_definition {
        $$ = $1;
    }
    | declaration {
        $$ = $1;
    }
    ;

function_definition:
    type_specifier function_declarator compound_statement {
        $$ = new A_FunctionDefinition($1->first, $2, $3, $1->second);
    }
    ;

 /* ==================== Type =========================================== */

type_specifier:
    VOID { $$ = new std::pair<int ,int>(0, $1); }
    | CHAR { $$ = new std::pair<int, int>(1, $1); }
    | INT { $$ = new std::pair<int, int>(2, $1); }
    | DOUBLE { $$ = new std::pair<int, int>(3, $1); }
    | BOOL { $$ = new std::pair<int, int>(4, $1); }
    ;

 /* ==================== Expression ====================================+ */

expression:
    binary_expression {
        $$ = $1;
    }
    | unary_expression {
        $$ = $1;
    }
    | call_expression {
        $$ = $1;
    }
    | literal_expression {
        $$ = $1;
    }
    | variable_expression {
        $$ = $1;
    }
    | '(' expression ')' {
    	$$ = $2;
    }
    ;

binary_expression:
    expression '+' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ADD, $1, $3);
    }
    | expression '-' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::SUB, $1, $3);
    }
    | expression '*' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::MUL, $1, $3);
    }
    | expression '/' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::DIV, $1, $3);
    }
    | expression '%' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::MOD, $1, $3);
    }
    | expression EQU_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::EQU, $1, $3);
    }
    | expression NEQ_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::NEQ, $1, $3);
    }
    | expression GT_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::GT, $1, $3);
    }
    | expression LT_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::LT, $1, $3);
    }
    | expression NGT_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::NGT, $1, $3);
    }
    | expression NLT_OP expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::NLT, $1, $3);
    }
    | expression LOGIC_AND expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::LOGIC_AND, $1, $3);
    }
    | expression LOGIC_OR expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::LOGIC_OR, $1, $3);
    }
    | expression '&' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::BIT_AND, $1, $3);
    }
    | expression '|' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::BIT_OR, $1, $3);
    }
    | expression '^' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::BIT_XOR, $1, $3);
    }
    | expression SHIFT_L expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::SHIFT_L, $1, $3);
    }
    | expression SHIFT_R expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::SHIFT_R, $1, $3);
    }
    | expression '=' expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN, $1, $3);
    }
    | expression ASSIGN_ADD expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN_ADD, $1, $3);
    }
    | expression ASSIGN_SUB expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN_SUB, $1, $3);
    }
    | expression ASSIGN_MUL expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN_MUL, $1, $3);
    }
    | expression ASSIGN_DIV expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN_DIV, $1, $3);
    }
    | expression ASSIGN_MOD expression {
        $$ = new A_BinaryExpression(A_BinaryExpression::ASSIGN_MOD, $1, $3);
    }
    | expression '[' expression ']' {
        $$ = new A_BinaryExpression(A_BinaryExpression::ARRAY_REF, $1, $3);
    }
    ;

prefix_expression:
    INC expression {
        $$ = new A_UnaryExpression(A_UnaryExpression::PREFIX_INC, $2);
    }
    | DEC expression {
        $$ = new A_UnaryExpression(A_UnaryExpression::PREFIX_DEC, $2);
    }
    ;

postfix_expression:
    expression INC {
        $$ = new A_UnaryExpression(A_UnaryExpression::POSTFIX_INC, $1);
    }
    | expression DEC {
        $$ = new A_UnaryExpression(A_UnaryExpression::POSTFIX_DEC, $1);
    }
    ;

unary_expression:
    '!' unary_expression {
        $$ = new A_UnaryExpression(A_UnaryExpression::LOGIC_NOT, $2);
    }
    | '~' unary_expression {
        $$ = new A_UnaryExpression(A_UnaryExpression::BIT_NOT, $2);
    }
    | postfix_expression %prec POSTFIX {
    	$$ = $1;
    }
    | prefix_expression %prec PREFIX {
    	$$ = $1;
    }
    ;

call_expression:
    IDENTIFIER '(' ')' {
        $$ = new A_CallExpression($1->first, std::vector<A_Expression *>(), $1->second);
    }
    | IDENTIFIER '(' argument_list ')' {
        $$ = new A_CallExpression($1->first, *($3), $1->second);
    }
    ;

argument_list:
    expression {
        std::vector<A_Expression *> *arguments = new std::vector<A_Expression *>();
        arguments->emplace_back($1);
        $$ = arguments;
    }
    | argument_list ',' expression {
        ($1)->emplace_back($3);
        $$ = $1;
    }
    ;

literal_expression:
    CONSTANT_DOUBLE {
        $$ = new A_LiteralExpression(A_Type::DOUBLE, *($1), line);
    }
    | CONSTANT_INT {
        $$ = new A_LiteralExpression(A_Type::INT, *($1), line);
    }
    | TRUE {
        $$ = new A_LiteralExpression(A_Type::BOOL, *($1), line);
    }
    | FALSE {
        $$ = new A_LiteralExpression(A_Type::BOOL, *($1), line);
    }
    ;

variable_expression:
    IDENTIFIER {
        $$ = new A_VariableExpression($1->first, $1->second);
    }
    ;


 /* ==================== Declarator & Initializer ======================= */

parameter_list:
    type_specifier IDENTIFIER { 
        std::vector<std::pair<int, std::string> > *parameters = new std::vector<std::pair<int, std::string> >();
        parameters->emplace_back(std::make_pair($1->first, $2->first));
        $$ = parameters;
    }
    | parameter_list ',' type_specifier IDENTIFIER {
        ($1)->emplace_back(std::make_pair($3->first, $4->first));
        $$ = $1;
    }
    ;

simple_declarator:
    IDENTIFIER {
        $$ = new A_SimpleDeclarator($1->first, 1, false, $1->second);
    }
    ;

array_declarator:
    IDENTIFIER '[' CONSTANT_INT ']' {
        $$ = new A_SimpleDeclarator($1->first, std::stoi(*($3)), true, $1->second);
    }
    ;

function_declarator:
    IDENTIFIER '(' parameter_list ')' {
    	$$ = new A_FunctionDeclarator($1->first, *($3), $1->second);
    }
    | IDENTIFIER '(' ')' {
        $$ = new A_FunctionDeclarator($1->first, std::vector<std::pair<int, std::string> >(), $1->second);
    }
    ;

init_declarator_list:
    init_declarator {
        std::vector<A_InitDeclarator *> *declarators = new std::vector<A_InitDeclarator *>();
        declarators->emplace_back($1);
        $$ = declarators;
    }
    | init_declarator_list ',' init_declarator {
        $1->emplace_back($3);
        $$ = $1;
    }
    ;

init_declarator:
    simple_declarator {
    	$$ = new A_InitDeclarator($1, std::vector<A_Expression *>());
    }
    | simple_declarator '=' expression {
        std::vector<A_Expression *> initializers;
        initializers.emplace_back($3);
        $$ = new A_InitDeclarator($1, initializers);
    }
    | array_declarator {
    	$$ = new A_InitDeclarator($1, std::vector<A_Expression *>());
    }
    | array_declarator '=' '{' initializers '}' {
        $$ = new A_InitDeclarator($1, *($4));
    }
    ;

initializers:
    expression {
        std::vector<A_Expression *> *initializers = new std::vector<A_Expression *>();
        initializers->emplace_back($1);
        $$ = initializers;
    }
    | initializers ',' expression {
        $1->emplace_back($3);
        $$ = $1;
    }
    ;

 /* ================== Statement ====================================== */

block_item:
    declaration {
        $$ = $1;
    }
    | statement {
        $$ = $1;
    }
    ;

block_item_list:
    block_item {
        std::vector<A_BlockItem *> *items = new std::vector<A_BlockItem *>();
        items->emplace_back($1);
        $$ = items;
    }
    | block_item_list block_item {
        $1->emplace_back($2);
        $$ = $1;
    }
    ;

declaration:
    type_specifier init_declarator_list ';'{
        $$ = new A_Declaration($1->first, *($2), $1->second);
    }
    ;

statement:
    expression_statement {
        $$ = $1;
    }
    | compound_statement {
        $$ = $1;
    }
    | selection_statement %prec NO_ELSE {
        $$ = $1;
    }
    | selection_statement_with_else %prec WITH_ELSE {
        $$ = $1;
    }
    | iteration_statement {
        $$ = $1;
    }
    | for_statement {
        $$ = $1;
    }
    | for_statement_with_declaration {
        $$ = $1;
    }
    | jump_statement {
        $$ = $1;
    }
    | return_statement {
        $$ = $1;
    }
    ;

expression_statement:
    ';' {
        $$ = new A_ExpressionStatement(new A_NopExpression);
    }
    | expression ';' {
        $$ = new A_ExpressionStatement($1);
    }
    ;

compound_statement:
    '{' block_item_list '}' {
        $$ = new A_CompoundStatement(*($2), $1);
    }
    | '{' '}' {
        $$ = new A_CompoundStatement(std::vector<A_BlockItem *>(), $1);
    }
    ;

selection_statement:
    IF '(' expression ')' statement {
        $$ = new A_SelectionStatement($3, $5, $1);
    }
    ;

selection_statement_with_else:
    IF '(' expression ')' statement ELSE statement {
        $$ = new A_SelectionStatementWithElse($3, $5, $7, $1);
    }
    ;

iteration_statement:
    WHILE '(' expression ')' statement {
        $$ = new A_IterationStatement($5, $3, false, $1);
    }
    | DO statement WHILE '(' expression ')' {
        $$ = new A_IterationStatement($2, $5, true, $1);
    }
    ;

for_statement:
    FOR '(' expression_statement expression_statement ')' statement {
        $$ = new A_ForStatement($3, new A_NopExpression(), $6, $4, $1);
    }
    | FOR '(' expression_statement expression_statement expression ')' statement {
        $$ = new A_ForStatement($3, $5, $7, $4, $1);
    }
    ;

for_statement_with_declaration:
    FOR '(' declaration expression_statement ')' statement {
        $$ = new A_ForStatementWithDeclaration($3, new A_NopExpression(), $6, $4, $1);
    }
    | FOR '(' declaration expression_statement expression ')' statement {
        $$ = new A_ForStatementWithDeclaration($3, $5, $7, $4, $1);
    }
    ;

jump_statement:
    BREAK ';' {
        $$ = new A_JumpStatement(A_JumpStatement::BREAK, $1);
    }
    | CONTINUE ';' {
        $$ = new A_JumpStatement(A_JumpStatement::CONTINUE, $1);
    }
    ;

return_statement:
    RETURN ';' {
        $$ = new A_ReturnStatement(new A_NopExpression(), $1);
    }
    | RETURN expression ';' {
        $$ = new A_ReturnStatement($2, $1);
    }
    ;

%%

void yyerror(char const *s) {
    fflush(stdout);
    std::cout << "Error at line " << line << " column " << column << std::endl;
}

