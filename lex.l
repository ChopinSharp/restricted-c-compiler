%{
    #include "yacc.hpp"
    int line = 0;
    int column = 0;
    void count(char *yytext);
%}

%option yylineno
%option noyywrap

D           [0-9]                                      
L           [A-Za-z_]                                 
H           [A-Fa-f0-9]                              
E           ([Ee][+-]?{D}+)                         

%%

"/*"(([^\*]*(\*[^\/])?)*)"*/" { line = yylineno; }
"//"[^\n]*          { }                                 /* Line comment */

"void"              { line = yylineno; count(yytext); yylval.pos = yylineno; return(VOID); }
"int"               { line = yylineno; count(yytext); yylval.pos = yylineno; return(INT); }
"double"            { line = yylineno; count(yytext); yylval.pos = yylineno; return(DOUBLE); }
"bool"   	    { line = yylineno; count(yytext); yylval.pos = yylineno; return(BOOL); }

"if"                { line = yylineno; count(yytext); yylval.pos = yylineno; return(IF); }
"else"              { line = yylineno; count(yytext); yylval.pos = yylineno; return(ELSE); }
"for"               { line = yylineno; count(yytext); yylval.pos = yylineno; return(FOR); }
"while"             { line = yylineno; count(yytext); yylval.pos = yylineno; return(WHILE); }
"do"                { line = yylineno; count(yytext); yylval.pos = yylineno; return(DO); }
"switch"            { line = yylineno; count(yytext); yylval.pos = yylineno; return(SWITCH); }
"case"              { line = yylineno; count(yytext); yylval.pos = yylineno; return(CASE); }
"default"           { line = yylineno; count(yytext); yylval.pos = yylineno; return(DEFAULT); }
"break"             { line = yylineno; count(yytext); yylval.pos = yylineno; return(BREAK); }
"continue"          { line = yylineno; count(yytext); yylval.pos = yylineno; return(CONTINUE); }
"return"            { line = yylineno; count(yytext); yylval.pos = yylineno; return(RETURN); }
"true"              { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(TRUE); }
"false"             { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(FALSE); }

{L}({L}|{D})*       { line = yylineno; count(yytext); yylval.id = new std::pair<std::string, int>(std::string(yytext), yylineno); return(IDENTIFIER); }        /* Identifier */

0[Xx]{H}+           { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_INT); }
0|[1-9]{D}*         { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_INT); }
0[0-7]+             { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_INT); }

{D}+{E}                 { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_DOUBLE); }    /* Float number, eg. 2e3 */
{D}*"."{D}+{E}?         { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_DOUBLE); }    /* Float number, eg. .3e-1 */
{D}+"."{D}*{E}?         { line = yylineno; count(yytext); yylval.str = new std::string(yytext); return(CONSTANT_DOUBLE); }    /* Float number, eg. 2.e+2 */

"+"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('+'); }
"-"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('-'); }
"*"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('*'); }
"/"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('/'); }
"%"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('%'); }
"=="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(EQU_OP); }
"!="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(NEQ_OP); }
">"         { line = yylineno; count(yytext); yylval.pos = yylineno; return(GT_OP); }
"<"         { line = yylineno; count(yytext); yylval.pos = yylineno; return(LT_OP); }
"<="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(NGT_OP); }
">="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(NLT_OP); }
"&&"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(LOGIC_AND); }
"||"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(LOGIC_OR); }
"&"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('&'); }
"|"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('|'); }
"^"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('^'); }
"<<"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(SHIFT_L); }
">>"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(SHIFT_R); }
"="         { line = yylineno; count(yytext); yylval.pos = yylineno; return('='); }
"+="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(ASSIGN_ADD); }
"-="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(ASSIGN_SUB); }
"*="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(ASSIGN_MUL); }
"/="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(ASSIGN_DIV); }
"%="        { line = yylineno; count(yytext); yylval.pos = yylineno; return(ASSIGN_MOD); }
","         { line = yylineno; count(yytext); yylval.pos = yylineno; return(','); }
"["         { line = yylineno; count(yytext); yylval.pos = yylineno; return('['); }
"]"         { line = yylineno; count(yytext); yylval.pos = yylineno; return(']'); }
"!"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('!'); }
"~"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('~'); }
"++"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(INC); }
"--"        { line = yylineno; count(yytext); yylval.pos = yylineno; return(DEC); }
"("         { line = yylineno; count(yytext); yylval.pos = yylineno; return('('); }
")"         { line = yylineno; count(yytext); yylval.pos = yylineno; return(')'); }
"{"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('{'); }
"}"         { line = yylineno; count(yytext); yylval.pos = yylineno; return('}'); }
";"         { line = yylineno; count(yytext); yylval.pos = yylineno; return(';'); }

[\t\v\n\f ] { count(yytext);}

.           { }     /* Add code to complain about unmatched characters */

%%

void count(char *yytext) {
    for (int i = 0; yytext[i] != 0; ++i) {
        if (yytext[i] == '\n') { column = 0; }
        else if (yytext[i] == '\t') { column += 4 - column % 4; }
        else column++;
    }
}
