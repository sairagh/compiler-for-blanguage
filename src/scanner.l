%{
#include "parser.tab.h"
%}

%%
[0-9][0-9]*	{yylval.num = atoi(yytext);	return NUMBER; }
"declblock" {return DEC;}
"codeblock"	{return COD;}
"int"				{return INT;}
"if"				{return IF;}
"else"      {return ELSE;}
"for"       {return FOR;}
"goto"      {return GOTO;}
"while"     {return WHILE;}
"read"      {return READ;}
"print"     {return PRI;}
"println"   {return PR1;}
\"(\\.|[^"])*\" {yylval.an= strdup(yytext);return AD;}
[a-zA-Z][a-zA-Z0-9]* {yylval.identifier_val = strdup(yytext); return IDENTIFIER;}
\+		{return '+';}
\:    {return ':';}
\-		{return '-';}
\*		{yylval.ari= strdup(yytext);return ARI;}
"/"		{yylval.ari= strdup(yytext);return ARI;}
%   {yylval.ari= strdup(yytext);return ARI;}
\<  {yylval.rel= strdup(yytext);return REL;}
\>  {yylval.rel= strdup(yytext);return REL;}
\<= {yylval.rel= strdup(yytext);return REL;}
\>= {yylval.rel= strdup(yytext);return REL;}
\!	{yylval.ari= strdup(yytext);return NO;}
\&&     {yylval.ari= strdup(yytext);return AND;}
"||"    {yylval.ari= strdup(yytext);return OR;}
\== {yylval.ari= strdup(yytext);return EQ;}
\!= {yylval.ari= strdup(yytext);return NEQ;}
\{		{return '{';}
\}		{return '}';}
\[    {return '[';}
\]    {return ']';}
\(    {return '(';}
\)    {return ')';}
","   {return ',';}
\;   return  SEMI;
"="	{return '=';}

[ \t\n]+		{}
.		{ printf("Unexpected token encountered: %s\n", yytext); return ETOK; 	}
