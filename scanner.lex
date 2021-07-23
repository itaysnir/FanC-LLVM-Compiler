%{
  #include <iostream>
  #include <string>
  #include <vector>
  #include <stdlib.h>
  #include <stdio.h>
  #include "output.hpp"
  #include "symbol_table.hpp"
  #include "parser.hpp"
  #include "parser.tab.hpp"
  #define YYSTYPE Node*
%}

%option noyywrap
%option yylineno
digit    ([0-9])
letter    ([a-zA-Z])
whitespace ([\t\n\r ])

%%
void                                {
										yylval = new Node("VOID");
										return VOID;
									}	

int                                 {
										yylval = new Node("INT");
										return INT;
									}

byte                                {
										yylval = new Node("BYTE");
										return BYTE;
									}

b                                   return B;

bool                                {
										yylval = new Node("BOOL");
										return BOOL;
									}

and                                  return AND;
or                                   return OR;
not                                  return NOT;

true                                {
										yylval = new Node("BOOL");
										return TRUE;
									}

false                               {
										yylval = new Node("BOOL");
										return FALSE;
									}

return                               return RETURN;
if                                   return IF;
else                                 return ELSE;
while                                return WHILE;
break                                return BREAK;
continue                             return CONTINUE;
switch                               return SWITCH;
case                                 return CASE;
default                              return DEFAULT;
\:                                   return COLON;
\;                                   return SC;
\,                                   return COMMA;
\(                                   return LPAREN;
\)                                   return RPAREN;
\{                                   return LBRACE;
\}                                   return RBRACE;
=                                    return ASSIGN;
(\<|\>|\<\=|\>\=)					{ // check
									 	yylval = new String(yytext);
										return RELOPFIRST;
									}
==|!=								{
									 	yylval = new String(yytext);
										return RELOPSECOND;
									}
\*|\/                          		{
									 	yylval = new String(yytext);
										return BINOPFIRST;
									}
\+|\-								{
									 	yylval = new String(yytext);
										return BINOPSECOND;
									}

[a-zA-Z][a-zA-Z0-9]*                {
										yylval = new String(yytext); 
										return ID;
									}

0|[1-9][0-9]*                       {
										yylval = new Num(atoi(yytext));
										return NUM;
									}

\"([^\n\r\"\\]|\\[rnt"\\])+\"		{
										yylval = new String(yytext);
										return STRING;
									}

\/\/[^\r\n]*(\r|\n|\r\n)?            {}
{whitespace}                         {}
.                                    {									output::errorLex(yylineno);exit(1);}
%%
