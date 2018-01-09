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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    NUMBER = 258,
    IDENTIFIER = 259,
    ETOK = 260,
    AD = 261,
    SEMI = 262,
    INT = 263,
    DEC = 264,
    COD = 265,
    PRI = 266,
    IF = 267,
    ELSE = 268,
    EQ = 269,
    NEQ = 270,
    FOR = 271,
    WHILE = 272,
    PR1 = 273,
    READ = 274,
    NO = 275,
    AND = 276,
    OR = 277,
    REL = 278,
    CON = 279,
    ARI = 280,
    GOTO = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "parser.y" /* yacc.c:1909  */

  int num;
  char *an;
	char *identifier_val;
  char *rel;
	char *con;
	char *ari;

  class Astprogram *pno;
  class declarlist *decllis;
  class decl *decla;
  class idlist *idlino;
  class id *idno;
  class statlist *stlino;
  class stat *stno;
  class ass *assno;
  class ifs *ifsno;
  class fors *forsno;
  class whiles *whileno;
  class lab *labno;
  class gotos *gono;
  class read *readno;
  class print *printno;
  class bl *blno;
  class expr *exprno;
  class numb *numno;
  class lf *lfno;
  class ab *abno;
  class id1 *id1no;
  

#line 113 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
