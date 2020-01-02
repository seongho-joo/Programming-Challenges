/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TPROGRAM = 258,
     TMAIN = 259,
     TPROC = 260,
     TFUNC = 261,
     TRETURNS = 262,
     TVAR = 263,
     TINT = 264,
     TLONG = 265,
     TIF = 266,
     TTHEN = 267,
     TELSE = 268,
     TWHILE = 269,
     TFOR = 270,
     TTO = 271,
     TCALL = 272,
     TRETURN = 273,
     TBEGIN = 274,
     TEND = 275,
     TASS = 276,
     TAND = 277,
     TOR = 278,
     TNOT = 279,
     TLT = 280,
     TLE = 281,
     TGT = 282,
     TGE = 283,
     TNE = 284,
     TPLUS = 285,
     TMINUS = 286,
     TMUL = 287,
     TDIV = 288,
     TNUMBER = 289,
     TNAME = 290
   };
#endif
/* Tokens.  */
#define TPROGRAM 258
#define TMAIN 259
#define TPROC 260
#define TFUNC 261
#define TRETURNS 262
#define TVAR 263
#define TINT 264
#define TLONG 265
#define TIF 266
#define TTHEN 267
#define TELSE 268
#define TWHILE 269
#define TFOR 270
#define TTO 271
#define TCALL 272
#define TRETURN 273
#define TBEGIN 274
#define TEND 275
#define TASS 276
#define TAND 277
#define TOR 278
#define TNOT 279
#define TLT 280
#define TLE 281
#define TGT 282
#define TGE 283
#define TNE 284
#define TPLUS 285
#define TMINUS 286
#define TMUL 287
#define TDIV 288
#define TNUMBER 289
#define TNAME 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 33 "vm.y"
{
    double dval;
    char *sval;
    struct Node *nval;
}
/* Line 1529 of yacc.c.  */
#line 125 "vm.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

