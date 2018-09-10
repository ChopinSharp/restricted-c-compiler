/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#include "ASTNode.h"

#ifndef YY_YY_YACC_HPP_INCLUDED
# define YY_YY_YACC_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONSTANT_INT = 259,
    CONSTANT_DOUBLE = 260,
    STRING_LITERAL = 261,
    TRUE = 262,
    FALSE = 263,
    VOID = 264,
    CHAR = 265,
    INT = 266,
    DOUBLE = 267,
    BOOL = 268,
    IF = 269,
    ELSE = 270,
    FOR = 271,
    WHILE = 272,
    DO = 273,
    SWITCH = 274,
    CASE = 275,
    DEFAULT = 276,
    BREAK = 277,
    CONTINUE = 278,
    RETURN = 279,
    EQU_OP = 280,
    NEQ_OP = 281,
    GT_OP = 282,
    LT_OP = 283,
    NGT_OP = 284,
    NLT_OP = 285,
    LOGIC_AND = 286,
    LOGIC_OR = 287,
    SHIFT_L = 288,
    SHIFT_R = 289,
    ASSIGN_ADD = 290,
    ASSIGN_SUB = 291,
    ASSIGN_MUL = 292,
    ASSIGN_DIV = 293,
    ASSIGN_MOD = 294,
    INC = 295,
    DEC = 296,
    PREFIX = 297,
    POSTFIX = 298,
    NO_ELSE = 299,
    WITH_ELSE = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "yacc.y" /* yacc.c:1909  */

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

#line 134 "yacc.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_HPP_INCLUDED  */
