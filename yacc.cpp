/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

    #include <iostream>
    #include "ASTNode.h"
    extern int line;
    extern int column;
    extern int yylex();
    void yyerror(char const *);
    std::vector<A_TreeNode *> externalDeclaration;
    A_TranslationUnit *unit;

#line 77 "yacc.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.hpp".  */
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
#line 12 "yacc.y" /* yacc.c:355  */

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

#line 197 "yacc.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 214 "yacc.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   844

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,    29,    38,     2,
      56,    57,    27,    25,    49,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    39,    59,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    37,    41,    42,
      44,    45,    46,    47,    48,    54,    55,    61,    62,    63,
      64
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   117,   120,   126,   129,   135,   143,   144,
     145,   146,   147,   153,   156,   159,   162,   165,   168,   174,
     177,   180,   183,   186,   189,   192,   195,   198,   201,   204,
     207,   210,   213,   216,   219,   222,   225,   228,   231,   234,
     237,   240,   243,   246,   252,   255,   261,   264,   270,   273,
     276,   279,   285,   288,   294,   299,   306,   309,   312,   315,
     321,   330,   335,   342,   348,   354,   357,   363,   368,   375,
     378,   383,   386,   392,   397,   406,   409,   415,   420,   427,
     433,   436,   439,   442,   445,   448,   451,   454,   457,   463,
     466,   472,   475,   481,   487,   493,   496,   502,   505,   511,
     514,   520,   523,   529,   532
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT_INT",
  "CONSTANT_DOUBLE", "STRING_LITERAL", "TRUE", "FALSE", "VOID", "CHAR",
  "INT", "DOUBLE", "BOOL", "IF", "ELSE", "FOR", "WHILE", "DO", "SWITCH",
  "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "'+'", "'-'", "'*'",
  "'/'", "'%'", "EQU_OP", "NEQ_OP", "GT_OP", "LT_OP", "NGT_OP", "NLT_OP",
  "LOGIC_AND", "LOGIC_OR", "'&'", "'|'", "'^'", "SHIFT_L", "SHIFT_R",
  "'='", "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MUL", "ASSIGN_DIV",
  "ASSIGN_MOD", "','", "'['", "']'", "'!'", "'~'", "INC", "DEC", "'('",
  "')'", "'{'", "'}'", "';'", "PREFIX", "POSTFIX", "NO_ELSE", "WITH_ELSE",
  "$accept", "Program", "translation_unit", "external_declaration",
  "function_definition", "type_specifier", "expression",
  "binary_expression", "prefix_expression", "postfix_expression",
  "unary_expression", "call_expression", "argument_list",
  "literal_expression", "variable_expression", "parameter_list",
  "simple_declarator", "array_declarator", "function_declarator",
  "init_declarator_list", "init_declarator", "initializers", "block_item",
  "block_item_list", "declaration", "statement", "expression_statement",
  "compound_statement", "selection_statement",
  "selection_statement_with_else", "iteration_statement", "for_statement",
  "for_statement_with_declaration", "jump_statement", "return_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    43,    45,    42,    47,    37,
     280,   281,   282,   283,   284,   285,   286,   287,    38,   124,
      94,   288,   289,    61,   290,   291,   292,   293,   294,    44,
      91,    93,    33,   126,   295,   296,    40,    41,   123,   125,
      59,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -111

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-111)))

#define YYTABLE_NINF -50

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     189,  -111,  -111,  -111,  -111,  -111,    11,   189,  -111,  -111,
      21,  -111,  -111,  -111,   -14,    -3,    -2,    -8,   -46,  -111,
      40,    36,   301,    -5,   151,  -111,    58,  -111,    12,  -111,
      88,   -27,    38,  -111,  -111,  -111,  -111,   301,   301,   301,
     301,   301,   634,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
     301,    55,    61,    63,   231,    60,    62,     2,  -111,  -111,
      58,   333,  -111,   173,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,    46,  -111,  -111,  -111,   189,
    -111,   272,   634,   -28,    81,   634,   634,   405,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,  -111,  -111,   634,   -47,   301,   209,   301,
     106,  -111,  -111,  -111,   369,  -111,  -111,  -111,   123,  -111,
     634,   -24,  -111,    10,    10,    89,    89,    89,   769,   769,
     789,   789,   789,   789,   665,    74,   758,   696,   727,   285,
     285,   634,   634,   634,   634,   634,   634,   603,   301,  -111,
     438,   263,   263,   471,    78,  -111,  -111,   301,  -111,  -111,
     634,   231,   289,   295,   231,   301,   634,   122,   231,   504,
     231,   537,  -111,   570,   231,  -111,   231,  -111,   231,  -111,
    -111,  -111,  -111
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     9,    10,    11,    12,     0,     2,     3,     5,
       0,     6,     1,     4,    63,    69,    71,     0,     0,    67,
       0,     0,     0,     0,     0,     7,     0,    79,     0,    66,
       0,     0,    60,    57,    56,    58,    59,     0,     0,     0,
       0,     0,    70,    13,    51,    50,    14,    15,    16,    17,
       0,     0,     0,     0,     0,     0,     0,     0,    92,    89,
       0,     0,    77,     0,    75,    76,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    63,    68,    64,    61,     0,
      65,     0,     0,    14,    14,    44,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    47,    73,     0,     0,     0,     0,
       0,   101,   102,   103,     0,    90,    91,    78,     0,    52,
      54,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,     0,    72,
       0,     0,     0,     0,     0,   104,    62,     0,    53,    43,
      74,     0,     0,     0,     0,     0,    55,    93,     0,     0,
       0,     0,    95,     0,     0,    99,     0,    97,     0,    96,
      94,   100,    98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,   135,  -111,    13,   -22,  -111,  -111,  -111,
     -11,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
     120,  -111,    84,  -111,   -20,   -53,  -110,   131,  -111,  -111,
    -111,  -111,  -111,  -111,  -111
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    60,    61,    43,    44,    45,
      46,    47,   131,    48,    49,    31,    15,    16,    17,    18,
      19,   116,    62,    63,    11,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,   120,   158,    26,    64,    32,    33,    34,   162,    35,
      36,    12,   159,    10,    27,    82,    82,    85,    86,    87,
      10,   -48,    79,   -48,    14,   167,    83,    84,   115,   -48,
      80,   -48,   -48,   168,    30,   124,    20,    90,    91,    92,
      22,    23,    21,    64,    28,     1,     2,     3,     4,     5,
      24,   172,   173,    50,    37,    38,    39,    40,    41,   130,
     112,    75,   123,    77,   113,   114,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,    78,   128,    29,    81,   160,    20,   163,   161,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   117,   101,   102,   103,   104,   105,   118,   177,   119,
     121,   182,   122,   164,   112,   185,   166,   187,   113,   114,
     -49,   190,   -49,   191,   175,   192,   170,   184,   -49,   112,
     -49,   -49,    13,   113,   114,   176,    76,   127,    25,     0,
     179,   181,     0,   183,    32,    33,    34,     0,    35,    36,
       1,     2,     3,     4,     5,    51,     0,    52,    53,    54,
       0,     0,     0,    55,    56,    57,    32,    33,    34,     0,
      35,    36,     1,     2,     3,     4,     5,    51,     0,    52,
      53,    54,     0,     0,     0,    55,    56,    57,     1,     2,
       3,     4,     5,    37,    38,    39,    40,    41,     0,    24,
      58,    59,    32,    33,    34,     0,    35,    36,     1,     2,
       3,     4,     5,     0,     0,    37,    38,    39,    40,    41,
       0,    24,   126,    59,    32,    33,    34,     0,    35,    36,
       0,     0,     0,     0,     0,    51,     0,    52,    53,    54,
       0,     0,     0,    55,    56,    57,     0,     0,     0,     0,
       0,    37,    38,    39,    40,    41,    32,    33,    34,    59,
      35,    36,     0,     0,     0,    32,    33,    34,     0,    35,
      36,     0,     0,    37,    38,    39,    40,    41,     0,    24,
       0,    59,    32,    33,    34,     0,    35,    36,    32,    33,
      34,     0,    35,    36,    32,    33,    34,     0,    35,    36,
      88,    89,    90,    91,    92,    37,    38,    39,    40,    41,
       0,     0,     0,    59,    37,    38,    39,    40,    41,   129,
       0,     0,     0,     0,     0,   112,     0,     0,     0,   113,
     114,    37,    38,    39,    40,    41,   178,    37,    38,    39,
      40,    41,   180,    37,    38,    39,    40,    41,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,   112,     0,     0,     0,   113,   114,     0,
       0,     0,     0,   125,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
       0,     0,     0,   113,   114,     0,     0,     0,     0,   165,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,   112,     0,     0,     0,   113,
     114,     0,   132,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   112,     0,
       0,     0,   113,   114,     0,   171,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   112,     0,     0,     0,   113,   114,     0,   174,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,     0,     0,     0,   113,   114,
       0,   186,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     0,   112,     0,     0,
       0,   113,   114,     0,   188,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
     112,     0,     0,     0,   113,   114,     0,   189,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,   112,   169,     0,     0,   113,   114,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,     0,     0,     0,   113,   114,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,   112,     0,     0,     0,   113,
     114,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,     0,   101,     0,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,   112,     0,     0,     0,
     113,   114,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,     0,   101,     0,     0,   104,   105,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
       0,   113,   114,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    88,    89,    90,    91,    92,   104,
     105,    95,    96,    97,    98,     0,     0,     0,   112,     0,
     104,   105,   113,   114,    88,    89,    90,    91,    92,   112,
       0,     0,     0,   113,   114,     0,     0,     0,     0,     0,
     104,   105,     0,     0,     0,     0,     0,     0,     0,   112,
       0,     0,     0,   113,   114
};

static const yytype_int16 yycheck[] =
{
      22,    54,    49,    49,    24,     3,     4,     5,   118,     7,
       8,     0,    59,     0,    60,    37,    38,    39,    40,    41,
       7,    49,    49,    51,     3,    49,    37,    38,    50,    57,
      57,    59,    60,    57,    21,    57,    50,    27,    28,    29,
      43,    43,    56,    63,     4,     9,    10,    11,    12,    13,
      58,   161,   162,    58,    52,    53,    54,    55,    56,    81,
      50,     3,    60,    51,    54,    55,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,     3,    79,    57,    56,   117,    50,   119,   118,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    56,    38,    39,    40,    41,    42,    56,   171,    56,
      60,   174,    60,    17,    50,   178,     3,   180,    54,    55,
      49,   184,    51,   186,    56,   188,   158,    15,    57,    50,
      59,    60,     7,    54,    55,   167,    26,    63,    17,    -1,
     172,   173,    -1,   175,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    16,    17,    18,
      -1,    -1,    -1,    22,    23,    24,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    16,
      17,    18,    -1,    -1,    -1,    22,    23,    24,     9,    10,
      11,    12,    13,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    17,    18,
      -1,    -1,    -1,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,     3,     4,     5,    60,
       7,     8,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
       8,    -1,    -1,    52,    53,    54,    55,    56,    -1,    58,
      -1,    60,     3,     4,     5,    -1,     7,     8,     3,     4,
       5,    -1,     7,     8,     3,     4,     5,    -1,     7,     8,
      25,    26,    27,    28,    29,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    60,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      55,    52,    53,    54,    55,    56,    57,    52,    53,    54,
      55,    56,    57,    52,    53,    54,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    60,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    60,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    54,
      55,    -1,    57,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    50,    -1,
      -1,    -1,    54,    55,    -1,    57,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    54,    55,    -1,    57,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    -1,    -1,    -1,    54,    55,
      -1,    57,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    54,    55,    -1,    57,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      50,    -1,    -1,    -1,    54,    55,    -1,    57,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    50,    51,    -1,    -1,    54,    55,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    -1,    -1,    -1,    54,    55,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      55,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      54,    55,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    55,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    25,    26,    27,    28,    29,    41,
      42,    32,    33,    34,    35,    -1,    -1,    -1,    50,    -1,
      41,    42,    54,    55,    25,    26,    27,    28,    29,    50,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    66,    67,    68,    69,
      70,    89,     0,    68,     3,    81,    82,    83,    84,    85,
      50,    56,    43,    43,    58,    92,    49,    60,     4,    57,
      70,    80,     3,     4,     5,     7,     8,    52,    53,    54,
      55,    56,    71,    72,    73,    74,    75,    76,    78,    79,
      58,    14,    16,    17,    18,    22,    23,    24,    59,    60,
      70,    71,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,     3,    85,    51,     3,    49,
      57,    56,    71,    75,    75,    71,    71,    71,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    50,    54,    55,    71,    86,    56,    56,    56,
      90,    60,    60,    60,    71,    60,    59,    87,    70,    57,
      71,    77,    57,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    49,    59,
      71,    89,    91,    71,    17,    60,     3,    49,    57,    51,
      71,    57,    91,    91,    57,    56,    71,    90,    57,    71,
      57,    71,    90,    71,    15,    90,    57,    90,    57,    57,
      90,    90,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    68,    69,    70,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    76,    76,    77,    77,    78,    78,    78,    78,
      79,    80,    80,    81,    82,    83,    83,    84,    84,    85,
      85,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    92,    92,    93,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     2,     2,     2,     2,     2,     2,
       1,     1,     3,     4,     1,     3,     1,     1,     1,     1,
       1,     2,     4,     1,     4,     4,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     1,     1,     1,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     2,     5,     7,     5,     6,     6,     7,     6,
       7,     2,     2,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 111 "yacc.y" /* yacc.c:1646  */
    {
        unit = new A_TranslationUnit(externalDeclaration);
    }
#line 1571 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 117 "yacc.y" /* yacc.c:1646  */
    {
        externalDeclaration.emplace_back((yyvsp[0].treeNode));
    }
#line 1579 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "yacc.y" /* yacc.c:1646  */
    {
        externalDeclaration.emplace_back((yyvsp[0].treeNode));
    }
#line 1587 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 126 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.treeNode) = (yyvsp[0].funcDef);
    }
#line 1595 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 129 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.treeNode) = (yyvsp[0].declaration);
    }
#line 1603 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 135 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.funcDef) = new A_FunctionDefinition((yyvsp[-2].type)->first, (yyvsp[-1].funcDec), (yyvsp[0].compState), (yyvsp[-2].type)->second);
    }
#line 1611 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 143 "yacc.y" /* yacc.c:1646  */
    { (yyval.type) = new std::pair<int ,int>(0, (yyvsp[0].pos)); }
#line 1617 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 144 "yacc.y" /* yacc.c:1646  */
    { (yyval.type) = new std::pair<int, int>(1, (yyvsp[0].pos)); }
#line 1623 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 145 "yacc.y" /* yacc.c:1646  */
    { (yyval.type) = new std::pair<int, int>(2, (yyvsp[0].pos)); }
#line 1629 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 146 "yacc.y" /* yacc.c:1646  */
    { (yyval.type) = new std::pair<int, int>(3, (yyvsp[0].pos)); }
#line 1635 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 147 "yacc.y" /* yacc.c:1646  */
    { (yyval.type) = new std::pair<int, int>(4, (yyvsp[0].pos)); }
#line 1641 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 153 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[0].binExp);
    }
#line 1649 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[0].unExp);
    }
#line 1657 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 159 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[0].callExp);
    }
#line 1665 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 162 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[0].literExp);
    }
#line 1673 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 165 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.exp) = (yyvsp[0].varExp);
    }
#line 1681 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.exp) = (yyvsp[-1].exp);
    }
#line 1689 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 174 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1697 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 177 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1705 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 180 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1713 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 183 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1721 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 186 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::MOD, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1729 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 189 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::EQU, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1737 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 192 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::NEQ, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1745 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 195 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::GT, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1753 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 198 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::LT, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1761 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 201 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::NGT, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1769 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 204 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::NLT, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1777 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 207 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::LOGIC_AND, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1785 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 210 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::LOGIC_OR, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1793 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 213 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::BIT_AND, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1801 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 216 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::BIT_OR, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1809 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 219 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::BIT_XOR, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1817 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 222 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::SHIFT_L, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1825 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 225 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::SHIFT_R, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1833 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 228 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1841 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 231 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN_ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1849 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 234 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN_SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1857 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 237 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN_MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1865 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 240 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN_DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1873 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 243 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ASSIGN_MOD, (yyvsp[-2].exp), (yyvsp[0].exp));
    }
#line 1881 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 246 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.binExp) = new A_BinaryExpression(A_BinaryExpression::ARRAY_REF, (yyvsp[-3].exp), (yyvsp[-1].exp));
    }
#line 1889 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 252 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::PREFIX_INC, (yyvsp[0].exp));
    }
#line 1897 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 255 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::PREFIX_DEC, (yyvsp[0].exp));
    }
#line 1905 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 261 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::POSTFIX_INC, (yyvsp[-1].exp));
    }
#line 1913 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 264 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::POSTFIX_DEC, (yyvsp[-1].exp));
    }
#line 1921 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 270 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::LOGIC_NOT, (yyvsp[0].unExp));
    }
#line 1929 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 273 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.unExp) = new A_UnaryExpression(A_UnaryExpression::BIT_NOT, (yyvsp[0].unExp));
    }
#line 1937 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 276 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.unExp) = (yyvsp[0].unExp);
    }
#line 1945 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 279 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.unExp) = (yyvsp[0].unExp);
    }
#line 1953 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 285 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.callExp) = new A_CallExpression((yyvsp[-2].id)->first, std::vector<A_Expression *>(), (yyvsp[-2].id)->second);
    }
#line 1961 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 288 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.callExp) = new A_CallExpression((yyvsp[-3].id)->first, *((yyvsp[-1].arguments)), (yyvsp[-3].id)->second);
    }
#line 1969 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 294 "yacc.y" /* yacc.c:1646  */
    {
        std::vector<A_Expression *> *arguments = new std::vector<A_Expression *>();
        arguments->emplace_back((yyvsp[0].exp));
        (yyval.arguments) = arguments;
    }
#line 1979 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 299 "yacc.y" /* yacc.c:1646  */
    {
        ((yyvsp[-2].arguments))->emplace_back((yyvsp[0].exp));
        (yyval.arguments) = (yyvsp[-2].arguments);
    }
#line 1988 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 306 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.literExp) = new A_LiteralExpression(A_Type::DOUBLE, *((yyvsp[0].str)), line);
    }
#line 1996 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 309 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.literExp) = new A_LiteralExpression(A_Type::INT, *((yyvsp[0].str)), line);
    }
#line 2004 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 312 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.literExp) = new A_LiteralExpression(A_Type::BOOL, *((yyvsp[0].str)), line);
    }
#line 2012 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 315 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.literExp) = new A_LiteralExpression(A_Type::BOOL, *((yyvsp[0].str)), line);
    }
#line 2020 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 321 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.varExp) = new A_VariableExpression((yyvsp[0].id)->first, (yyvsp[0].id)->second);
    }
#line 2028 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 330 "yacc.y" /* yacc.c:1646  */
    { 
        std::vector<std::pair<int, std::string> > *parameters = new std::vector<std::pair<int, std::string> >();
        parameters->emplace_back(std::make_pair((yyvsp[-1].type)->first, (yyvsp[0].id)->first));
        (yyval.params) = parameters;
    }
#line 2038 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 335 "yacc.y" /* yacc.c:1646  */
    {
        ((yyvsp[-3].params))->emplace_back(std::make_pair((yyvsp[-1].type)->first, (yyvsp[0].id)->first));
        (yyval.params) = (yyvsp[-3].params);
    }
#line 2047 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 342 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.simpleDec) = new A_SimpleDeclarator((yyvsp[0].id)->first, 1, false, (yyvsp[0].id)->second);
    }
#line 2055 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 348 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.simpleDec) = new A_SimpleDeclarator((yyvsp[-3].id)->first, std::stoi(*((yyvsp[-1].str))), true, (yyvsp[-3].id)->second);
    }
#line 2063 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 354 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.funcDec) = new A_FunctionDeclarator((yyvsp[-3].id)->first, *((yyvsp[-1].params)), (yyvsp[-3].id)->second);
    }
#line 2071 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 357 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.funcDec) = new A_FunctionDeclarator((yyvsp[-2].id)->first, std::vector<std::pair<int, std::string> >(), (yyvsp[-2].id)->second);
    }
#line 2079 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 363 "yacc.y" /* yacc.c:1646  */
    {
        std::vector<A_InitDeclarator *> *declarators = new std::vector<A_InitDeclarator *>();
        declarators->emplace_back((yyvsp[0].initDec));
        (yyval.initDecList) = declarators;
    }
#line 2089 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 368 "yacc.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].initDecList)->emplace_back((yyvsp[0].initDec));
        (yyval.initDecList) = (yyvsp[-2].initDecList);
    }
#line 2098 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 375 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.initDec) = new A_InitDeclarator((yyvsp[0].simpleDec), std::vector<A_Expression *>());
    }
#line 2106 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 378 "yacc.y" /* yacc.c:1646  */
    {
        std::vector<A_Expression *> initializers;
        initializers.emplace_back((yyvsp[0].exp));
        (yyval.initDec) = new A_InitDeclarator((yyvsp[-2].simpleDec), initializers);
    }
#line 2116 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 383 "yacc.y" /* yacc.c:1646  */
    {
    	(yyval.initDec) = new A_InitDeclarator((yyvsp[0].simpleDec), std::vector<A_Expression *>());
    }
#line 2124 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 386 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.initDec) = new A_InitDeclarator((yyvsp[-4].simpleDec), *((yyvsp[-1].arguments)));
    }
#line 2132 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 392 "yacc.y" /* yacc.c:1646  */
    {
        std::vector<A_Expression *> *initializers = new std::vector<A_Expression *>();
        initializers->emplace_back((yyvsp[0].exp));
        (yyval.arguments) = initializers;
    }
#line 2142 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 397 "yacc.y" /* yacc.c:1646  */
    {
        (yyvsp[-2].arguments)->emplace_back((yyvsp[0].exp));
        (yyval.arguments) = (yyvsp[-2].arguments);
    }
#line 2151 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 406 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.item) = (yyvsp[0].declaration);
    }
#line 2159 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 409 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.item) = (yyvsp[0].statement);
    }
#line 2167 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 415 "yacc.y" /* yacc.c:1646  */
    {
        std::vector<A_BlockItem *> *items = new std::vector<A_BlockItem *>();
        items->emplace_back((yyvsp[0].item));
        (yyval.itemList) = items;
    }
#line 2177 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 420 "yacc.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].itemList)->emplace_back((yyvsp[0].item));
        (yyval.itemList) = (yyvsp[-1].itemList);
    }
#line 2186 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 427 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.declaration) = new A_Declaration((yyvsp[-2].type)->first, *((yyvsp[-1].initDecList)), (yyvsp[-2].type)->second);
    }
#line 2194 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 433 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].expState);
    }
#line 2202 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 436 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].compState);
    }
#line 2210 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 439 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].selState);
    }
#line 2218 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 442 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].selStateWithElse);
    }
#line 2226 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 445 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].iterState);
    }
#line 2234 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 448 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].forState);
    }
#line 2242 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 451 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].forStateWithDec);
    }
#line 2250 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 454 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].jumpState);
    }
#line 2258 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 457 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.statement) = (yyvsp[0].retState);
    }
#line 2266 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 463 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.expState) = new A_ExpressionStatement(new A_NopExpression);
    }
#line 2274 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 466 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.expState) = new A_ExpressionStatement((yyvsp[-1].exp));
    }
#line 2282 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 472 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.compState) = new A_CompoundStatement(*((yyvsp[-1].itemList)), (yyvsp[-2].pos));
    }
#line 2290 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 475 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.compState) = new A_CompoundStatement(std::vector<A_BlockItem *>(), (yyvsp[-1].pos));
    }
#line 2298 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 481 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.selState) = new A_SelectionStatement((yyvsp[-2].exp), (yyvsp[0].statement), (yyvsp[-4].pos));
    }
#line 2306 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 487 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.selStateWithElse) = new A_SelectionStatementWithElse((yyvsp[-4].exp), (yyvsp[-2].statement), (yyvsp[0].statement), (yyvsp[-6].pos));
    }
#line 2314 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 493 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.iterState) = new A_IterationStatement((yyvsp[0].statement), (yyvsp[-2].exp), false, (yyvsp[-4].pos));
    }
#line 2322 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 496 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.iterState) = new A_IterationStatement((yyvsp[-4].statement), (yyvsp[-1].exp), true, (yyvsp[-5].pos));
    }
#line 2330 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 502 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.forState) = new A_ForStatement((yyvsp[-3].expState), new A_NopExpression(), (yyvsp[0].statement), (yyvsp[-2].expState), (yyvsp[-5].pos));
    }
#line 2338 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 505 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.forState) = new A_ForStatement((yyvsp[-4].expState), (yyvsp[-2].exp), (yyvsp[0].statement), (yyvsp[-3].expState), (yyvsp[-6].pos));
    }
#line 2346 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 511 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.forStateWithDec) = new A_ForStatementWithDeclaration((yyvsp[-3].declaration), new A_NopExpression(), (yyvsp[0].statement), (yyvsp[-2].expState), (yyvsp[-5].pos));
    }
#line 2354 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 514 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.forStateWithDec) = new A_ForStatementWithDeclaration((yyvsp[-4].declaration), (yyvsp[-2].exp), (yyvsp[0].statement), (yyvsp[-3].expState), (yyvsp[-6].pos));
    }
#line 2362 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 520 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.jumpState) = new A_JumpStatement(A_JumpStatement::BREAK, (yyvsp[-1].pos));
    }
#line 2370 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 523 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.jumpState) = new A_JumpStatement(A_JumpStatement::CONTINUE, (yyvsp[-1].pos));
    }
#line 2378 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 529 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.retState) = new A_ReturnStatement(new A_NopExpression(), (yyvsp[-1].pos));
    }
#line 2386 "yacc.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 532 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.retState) = new A_ReturnStatement((yyvsp[-1].exp), (yyvsp[-2].pos));
    }
#line 2394 "yacc.cpp" /* yacc.c:1646  */
    break;


#line 2398 "yacc.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 537 "yacc.y" /* yacc.c:1906  */


void yyerror(char const *s) {
    fflush(stdout);
    std::cout << "Error at line " << line << " column " << column << std::endl;
}

