/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "vm.y"

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #define MAXLEN 15
    
    union Value {
        int num;
        char *var;
    };
    typedef struct Addr {
        char name[MAXLEN];
        int addr;
    }Addr;
    typedef struct Node {
        char kind[MAXLEN];
        union Value value;
        struct Node* bro;
        struct Node* child;
    }Node;
    void preOrder(Node*);
    Node* createNode(char* kind);
    Node *root;
    
    /** 코드생성부분 */
    int countVar(Node* root);
    void codeR(Node* root);
    void codeL(Node* root);
    void code(Node* root);
    void codeGen(Node* root);
    int p = 0, v = 0, l = 0;
    

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 33 "vm.y"
{
    double dval;
    char *sval;
    struct Node *nval;
}
/* Line 193 of yacc.c.  */
#line 205 "vm.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 218 "vm.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,     2,     2,    39,     2,    37,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    36,
       2,    42,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    12,    16,    17,    21,    23,    27,    31,
      33,    35,    37,    39,    42,    44,    45,    47,    49,    57,
      69,    71,    72,    74,    76,    78,    80,    82,    84,    86,
      90,    97,   106,   112,   122,   128,   133,   137,   141,   143,
     147,   151,   154,   156,   160,   164,   168,   172,   176,   180,
     184,   188,   190,   194,   198,   200,   202,   204,   206,   209,
     213,   218,   220,   221,   225,   227,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,     3,    35,    36,    51,     4,    45,    63,
      37,    -1,     8,    46,    36,    -1,    -1,    46,    36,    47,
      -1,    47,    -1,    48,    38,    49,    -1,    48,    39,    50,
      -1,    50,    -1,     9,    -1,    10,    -1,    73,    -1,    51,
      52,    -1,    52,    -1,    -1,    53,    -1,    54,    -1,     5,
      73,    40,    55,    41,    45,    63,    -1,     6,    73,    40,
      55,    41,     7,    40,    49,    41,    45,    63,    -1,    46,
      -1,    -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    50,    21,    67,    -1,
      11,    40,    65,    41,    12,    56,    -1,    11,    40,    65,
      41,    12,    56,    13,    56,    -1,    14,    40,    65,    41,
      56,    -1,    15,    40,    50,    42,    67,    16,    67,    41,
      56,    -1,    17,    73,    40,    71,    41,    -1,    18,    40,
      67,    41,    -1,    19,    64,    20,    -1,    64,    36,    56,
      -1,    56,    -1,    65,    22,    66,    -1,    65,    23,    66,
      -1,    24,    66,    -1,    66,    -1,    67,    25,    67,    -1,
      67,    26,    67,    -1,    67,    27,    67,    -1,    67,    28,
      67,    -1,    67,    21,    67,    -1,    67,    29,    67,    -1,
      67,    30,    68,    -1,    67,    31,    68,    -1,    68,    -1,
      68,    32,    69,    -1,    68,    33,    69,    -1,    69,    -1,
      50,    -1,    74,    -1,    70,    -1,    31,    69,    -1,    40,
      67,    41,    -1,    73,    40,    71,    41,    -1,    72,    -1,
      -1,    72,    39,    67,    -1,    67,    -1,    35,    -1,    34,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    54,    58,    60,    66,    68,    76,    82,
      84,    85,    87,    89,    95,    96,    98,    99,   101,   108,
     116,   120,   122,   123,   124,   125,   126,   127,   128,   130,
     136,   141,   148,   154,   162,   168,   173,   178,   184,   185,
     192,   199,   203,   205,   210,   215,   220,   225,   230,   236,
     241,   246,   248,   253,   258,   260,   261,   262,   263,   267,
     269,   274,   275,   276,   282,   284,   288
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TPROGRAM", "TMAIN", "TPROC", "TFUNC",
  "TRETURNS", "TVAR", "TINT", "TLONG", "TIF", "TTHEN", "TELSE", "TWHILE",
  "TFOR", "TTO", "TCALL", "TRETURN", "TBEGIN", "TEND", "TASS", "TAND",
  "TOR", "TNOT", "TLT", "TLE", "TGT", "TGE", "TNE", "TPLUS", "TMINUS",
  "TMUL", "TDIV", "TNUMBER", "TNAME", "';'", "'.'", "':'", "','", "'('",
  "')'", "'='", "$accept", "Program", "VarDecl", "DclList", "Decl",
  "VarList", "Type", "Var", "SubPgmList", "SubPgm", "ProcDecl", "FuncDecl",
  "FormParam", "Stmt", "AsgnStmt", "IfStmt", "WhileStmt", "ForStmt",
  "CallStmt", "RtrnStmt", "CompStmt", "StmtList", "Cond", "Rel", "Expr",
  "Term", "Fact", "FuncCall", "ParamList", "ExprList", "Name", "Number", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    59,    46,    58,    44,
      40,    41,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    47,    48,    48,
      49,    49,    50,    51,    51,    51,    52,    52,    53,    54,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    57,
      58,    58,    59,    60,    61,    62,    63,    64,    64,    65,
      65,    65,    65,    66,    66,    66,    66,    66,    66,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    69,    69,
      70,    71,    71,    72,    72,    73,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     3,     0,     3,     1,     3,     3,     1,
       1,     1,     1,     2,     1,     0,     1,     1,     7,    11,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     3,
       6,     8,     5,     9,     5,     4,     3,     3,     1,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     2,     3,
       4,     1,     0,     3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,    15,     0,     0,     0,    14,
      16,    17,    65,     0,     0,     4,    13,    21,    21,     0,
       0,    20,     6,     0,     9,     0,    12,     0,     0,     0,
       0,     0,     0,     0,     4,     0,     3,     0,     0,     0,
       0,     0,     0,    38,    22,    23,    24,    25,    26,    27,
      28,     0,     2,     5,    10,    11,     7,     8,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,    18,     0,
       0,     0,    66,     0,    55,     0,    42,     0,    51,    54,
      57,    12,    56,     0,     0,    62,     0,    29,    37,     0,
      41,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,    64,
       0,    61,    35,     4,    59,    39,    40,     0,    47,    43,
      44,    45,    46,    48,    49,    50,    52,    53,     0,    32,
       0,    34,     0,     0,    30,    60,     0,    63,    19,     0,
       0,    31,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    20,    21,    22,    23,    56,    74,     8,     9,
      10,    11,    25,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    75,    76,    77,    78,    79,    80,   110,   111,
      81,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const yytype_int16 yypact[] =
{
       4,   -18,    20,     1,   -63,    23,   -13,   -13,    45,   -63,
     -63,   -63,   -63,     0,    17,    47,   -63,   -13,   -13,   -13,
      53,    39,   -63,    57,   -63,    36,   -63,    38,    55,    71,
      56,   -13,   100,   -13,    47,    92,   -13,    65,    80,    85,
     -13,    86,    96,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -10,   -63,   -63,   -63,   -63,   -63,   -63,    53,    91,
      63,    63,   -13,    95,    81,    81,   -63,    71,   -63,   100,
      81,    81,   -63,    81,   -63,    13,   -63,   113,    90,   -63,
     -63,    97,   -63,    37,    88,    81,    32,    83,   -63,   104,
     -63,   -63,    40,    81,    81,   120,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    71,    81,    83,
     105,   108,   -63,    47,   -63,   -63,   -63,    71,    83,    83,
      83,    83,    83,    83,    90,    90,   -63,   -63,   107,   -63,
      15,   -63,    81,    53,   136,   -63,    81,    83,   -63,    71,
      77,   -63,    71,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   -29,   131,   -12,   -63,    82,   -15,   -63,   144,
     -63,   -63,   135,   -59,   -63,   -63,   -63,   -63,   -63,   -63,
     -14,   -63,    93,   -55,   -32,    26,   -62,   -63,    49,   -63,
      -6,   -63
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      13,    14,    24,    24,    24,    58,    30,     1,    88,    91,
      66,    26,    26,    26,    42,    90,    24,     3,    57,    53,
       4,    24,    12,    26,    53,    26,    67,    26,     6,     7,
      26,   136,    86,    87,    63,    93,    94,     5,   115,   116,
      17,    92,   126,   127,    68,   102,   103,    84,   129,    15,
       6,     7,    42,   109,    95,    19,    26,    18,   134,    93,
      94,    26,   102,   103,   118,   119,   120,   121,   122,   123,
     102,   103,    29,   112,   109,    31,   130,    34,   107,    35,
     141,   114,    37,   143,   133,    38,    39,    70,    40,    41,
      29,    36,    42,    52,    71,    32,    33,    72,    12,    59,
     137,    26,    42,    73,   140,    60,    12,   102,   103,    54,
      55,    26,    71,   102,   103,    72,    12,    65,   142,   138,
      61,    73,   104,   105,    42,    62,    64,    42,   124,   125,
     108,    69,   117,    26,    96,    85,    26,   106,    97,    98,
      99,   100,   101,   102,   103,   113,   131,   132,   135,   139,
      28,    89,    16,    27,    83,   128
};

static const yytype_uint8 yycheck[] =
{
       6,     7,    17,    18,    19,    34,    20,     3,    67,    71,
      20,    17,    18,    19,    29,    70,    31,    35,    33,    31,
       0,    36,    35,    29,    36,    31,    36,    33,     5,     6,
      36,    16,    64,    65,    40,    22,    23,    36,    93,    94,
      40,    73,   104,   105,    58,    30,    31,    62,   107,     4,
       5,     6,    67,    85,    41,     8,    62,    40,   117,    22,
      23,    67,    30,    31,    96,    97,    98,    99,   100,   101,
      30,    31,    19,    41,   106,    36,   108,    41,    41,    41,
     139,    41,    11,   142,   113,    14,    15,    24,    17,    18,
      19,    36,   107,    37,    31,    38,    39,    34,    35,     7,
     132,   107,   117,    40,   136,    40,    35,    30,    31,     9,
      10,   117,    31,    30,    31,    34,    35,    21,    41,   133,
      40,    40,    32,    33,   139,    40,    40,   142,   102,   103,
      42,    40,    12,   139,    21,    40,   142,    40,    25,    26,
      27,    28,    29,    30,    31,    41,    41,    39,    41,    13,
      19,    69,     8,    18,    61,   106
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    44,    35,     0,    36,     5,     6,    51,    52,
      53,    54,    35,    73,    73,     4,    52,    40,    40,     8,
      45,    46,    47,    48,    50,    55,    73,    55,    46,    19,
      63,    36,    38,    39,    41,    41,    36,    11,    14,    15,
      17,    18,    50,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    37,    47,     9,    10,    49,    50,    45,     7,
      40,    40,    40,    73,    40,    21,    20,    36,    63,    40,
      24,    31,    34,    40,    50,    65,    66,    67,    68,    69,
      70,    73,    74,    65,    50,    40,    67,    67,    56,    49,
      66,    69,    67,    22,    23,    41,    21,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    40,    41,    42,    67,
      71,    72,    41,    41,    41,    66,    66,    12,    67,    67,
      67,    67,    67,    67,    68,    68,    69,    69,    71,    56,
      67,    41,    39,    45,    56,    41,    16,    67,    63,    13,
      67,    56,    41,    56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 44 "vm.y"
    {
    (yyval.nval) = createNode("MAIN");
    (yyval.nval)->bro = (yyvsp[(4) - (8)].nval); // SUBPGM
    (yyval.nval)->child = (yyvsp[(6) - (8)].nval); // VARDECL
    (yyvsp[(6) - (8)].nval)->bro = (yyvsp[(7) - (8)].nval); // COMP
    
    // preOrder($$);
    codeGen((yyval.nval));
    // code($$);
;}
    break;

  case 3:
#line 54 "vm.y"
    {
    (yyval.nval) = createNode("VARDECL");
    (yyval.nval)->child = (yyvsp[(2) - (3)].nval);
;}
    break;

  case 4:
#line 58 "vm.y"
    { (yyval.nval) = createNode("VARDECL"); ;}
    break;

  case 5:
#line 60 "vm.y"
    {
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
    (yyval.nval) = (yyvsp[(1) - (3)].nval);
;}
    break;

  case 6:
#line 66 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 7:
#line 68 "vm.y"
    {
    (yyval.nval) = createNode("DECL");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 8:
#line 76 "vm.y"
    {
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
    (yyval.nval) = (yyvsp[(1) - (3)].nval);
;}
    break;

  case 9:
#line 82 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 10:
#line 84 "vm.y"
    { (yyval.nval) = createNode("INT"); ;}
    break;

  case 11:
#line 85 "vm.y"
    { (yyval.nval) = createNode("LONG"); ;}
    break;

  case 12:
#line 87 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 13:
#line 89 "vm.y"
    {
    root = (yyvsp[(1) - (2)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(2) - (2)].nval);
    (yyval.nval) = (yyvsp[(1) - (2)].nval);
;}
    break;

  case 14:
#line 95 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 15:
#line 96 "vm.y"
    {(yyval.nval) = NULL; ;}
    break;

  case 16:
#line 98 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 17:
#line 99 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 18:
#line 101 "vm.y"
    {
    (yyval.nval) = createNode("PROC");
    (yyval.nval)->child = (yyvsp[(2) - (7)].nval); // NAME
    (yyvsp[(2) - (7)].nval)->bro = (yyvsp[(4) - (7)].nval); // VARDECL
    (yyvsp[(4) - (7)].nval)->bro = (yyvsp[(6) - (7)].nval); // VARDECL
    (yyvsp[(6) - (7)].nval)->bro = (yyvsp[(7) - (7)].nval); // COMP
;}
    break;

  case 19:
#line 108 "vm.y"
    {
    (yyval.nval) = createNode("FUNC") ;
    (yyval.nval)->child = (yyvsp[(2) - (11)].nval); // NAME
    (yyvsp[(2) - (11)].nval)->bro = (yyvsp[(8) - (11)].nval); // TYPE
    (yyvsp[(8) - (11)].nval)->bro = (yyvsp[(4) - (11)].nval); // VARDECL
    (yyvsp[(4) - (11)].nval)->bro = (yyvsp[(10) - (11)].nval); // VARDECL
    (yyvsp[(10) - (11)].nval)->bro = (yyvsp[(11) - (11)].nval); // COMP
;}
    break;

  case 20:
#line 116 "vm.y"
    {
    (yyval.nval) = createNode("VARDECL");
    (yyval.nval)->child = (yyvsp[(1) - (1)].nval);
;}
    break;

  case 21:
#line 120 "vm.y"
    {(yyval.nval) = createNode("VARDECL");;}
    break;

  case 22:
#line 122 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 23:
#line 123 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 24:
#line 124 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 25:
#line 125 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 26:
#line 126 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 27:
#line 127 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 28:
#line 128 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 29:
#line 130 "vm.y"
    {
    (yyval.nval) = createNode("ASSIGN");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 30:
#line 136 "vm.y"
    {
    (yyval.nval) = createNode("IF");
    (yyval.nval)->child = (yyvsp[(3) - (6)].nval);
    (yyvsp[(3) - (6)].nval)->bro = (yyvsp[(6) - (6)].nval);
;}
    break;

  case 31:
#line 141 "vm.y"
    {
    (yyval.nval) = createNode("IF");
    (yyval.nval)->child = (yyvsp[(3) - (8)].nval);
    (yyvsp[(3) - (8)].nval)->bro = (yyvsp[(6) - (8)].nval);
    (yyvsp[(6) - (8)].nval)->bro = (yyvsp[(8) - (8)].nval);
;}
    break;

  case 32:
#line 148 "vm.y"
    {
    (yyval.nval) = createNode("WHILE");
    (yyval.nval)->child = (yyvsp[(3) - (5)].nval);
    (yyvsp[(3) - (5)].nval)->bro = (yyvsp[(5) - (5)].nval);
;}
    break;

  case 33:
#line 154 "vm.y"
    {
    (yyval.nval) = createNode("FOR");
    (yyval.nval)->child = (yyvsp[(3) - (9)].nval);
    (yyvsp[(3) - (9)].nval)->bro = (yyvsp[(5) - (9)].nval);
    (yyvsp[(5) - (9)].nval)->bro = (yyvsp[(7) - (9)].nval);
    (yyvsp[(7) - (9)].nval)->bro = (yyvsp[(9) - (9)].nval);
;}
    break;

  case 34:
#line 162 "vm.y"
    {
    (yyval.nval) = createNode("PCALL");
    (yyval.nval)->child = (yyvsp[(2) - (5)].nval);
    (yyvsp[(2) - (5)].nval)->bro = (yyvsp[(4) - (5)].nval);
;}
    break;

  case 35:
#line 168 "vm.y"
    {
    (yyval.nval) = createNode("RETURN");
    (yyval.nval)->child = (yyvsp[(3) - (4)].nval);
;}
    break;

  case 36:
#line 173 "vm.y"
    {
    (yyval.nval) = createNode("COMP");
    (yyval.nval)->child = (yyvsp[(2) - (3)].nval);
;}
    break;

  case 37:
#line 178 "vm.y"
    {
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
    (yyval.nval) = (yyvsp[(1) - (3)].nval);
;}
    break;

  case 38:
#line 184 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 39:
#line 185 "vm.y"
    {
    (yyval.nval) = createNode("AND");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 40:
#line 192 "vm.y"
    {
    (yyval.nval) = createNode("OR");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 41:
#line 199 "vm.y"
    {
    (yyval.nval) = createNode("NOT");
    (yyval.nval)->child = (yyvsp[(2) - (2)].nval);
;}
    break;

  case 42:
#line 203 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 43:
#line 205 "vm.y"
    {
    (yyval.nval) = createNode("LT");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 44:
#line 210 "vm.y"
    {
    (yyval.nval) = createNode("LE");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 45:
#line 215 "vm.y"
    {
    (yyval.nval) = createNode("GT");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 46:
#line 220 "vm.y"
    {
    (yyval.nval) = createNode("GE");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 47:
#line 225 "vm.y"
    {
    (yyval.nval) = createNode("EQ");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 48:
#line 230 "vm.y"
    {
    (yyval.nval) = createNode("LE");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 49:
#line 236 "vm.y"
    {
    (yyval.nval) = createNode("PLUS");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 50:
#line 241 "vm.y"
    {
    (yyval.nval) = createNode("MINUS");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 51:
#line 246 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 52:
#line 248 "vm.y"
    {
    (yyval.nval) = createNode("TIMES");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 53:
#line 253 "vm.y"
    {
    (yyval.nval) = createNode("DIVIDE");
    (yyval.nval)->child = (yyvsp[(1) - (3)].nval);
    (yyvsp[(1) - (3)].nval)->bro = (yyvsp[(3) - (3)].nval);
;}
    break;

  case 54:
#line 258 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 55:
#line 260 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 56:
#line 261 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 57:
#line 262 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 58:
#line 263 "vm.y"
    {
    (yyval.nval) = createNode("NEG");
    (yyval.nval)->child = (yyvsp[(2) - (2)].nval);
;}
    break;

  case 59:
#line 267 "vm.y"
    { (yyval.nval) = (yyvsp[(2) - (3)].nval); ;}
    break;

  case 60:
#line 269 "vm.y"
    {
    (yyval.nval) = createNode("FCALL");
    (yyval.nval)->child = (yyvsp[(1) - (4)].nval);
    (yyvsp[(1) - (4)].nval)->bro = (yyvsp[(3) - (4)].nval);
;}
    break;

  case 61:
#line 274 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 62:
#line 275 "vm.y"
    { (yyval.nval) = NULL; ;}
    break;

  case 63:
#line 276 "vm.y"
    {
    root = (yyvsp[(1) - (3)].nval);
    while(root->bro != NULL) root = root->bro;
    root->bro = (yyvsp[(3) - (3)].nval);
    (yyval.nval) = (yyvsp[(1) - (3)].nval);
;}
    break;

  case 64:
#line 282 "vm.y"
    { (yyval.nval) = (yyvsp[(1) - (1)].nval); ;}
    break;

  case 65:
#line 284 "vm.y"
    {
    (yyval.nval) = createNode("NAME");
    (yyval.nval)->value.var = yylval.sval;
;}
    break;

  case 66:
#line 288 "vm.y"
    {
    (yyval.nval) = createNode("NUMBER");
    (yyval.nval)->value.num = yylval.dval;
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2023 "vm.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 292 "vm.y"

Node* createNode(char* kind) {
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->kind, kind);
    new->bro = NULL;
    new->child = NULL;
    return new;
}
int countVar(Node* root){
    int cnt = 0;
    Node *t_node1, *t_node2;
    
    if(root->child != NULL) {
        t_node1 = root->child;
        while(t_node1 != NULL) {
            t_node2 = t_node1->child;
            while(t_node2->bro != NULL) {
                t_node2 = t_node2->bro;
                cnt++;
            }
            t_node1 = t_node1->bro;
        }
    }
    return cnt;
}

void codeL(Node* root) {
    printf("lda p(%s); ", root->value.var);
}
void codeR(Node* root) {
    if(strcmp(root->kind, "NUMBER") == 0) {
        printf("ldc %d; ", root->value.num);
    } else if(strcmp(root->kind, "NAME") == 0) {
        codeL(root);
        printf("ind; ");
    } else if(strcmp(root->kind, "PLUS") == 0 ||
    strcmp(root->kind, "MINUS") == 0 ||
    strcmp(root->kind, "TIMES") == 0 ||
    strcmp(root->kind, "DVIDE") == 0) {
        codeR(root->child);
        codeR(root->child->bro);
        if(strcmp(root->kind, "PLUS") == 0) printf("add; ");
        else if(strcmp(root->kind, "MINUS") == 0) printf("sub; ");
        else if(strcmp(root->kind, "TIMES") == 0) printf("mul; ");
        else if(strcmp(root->kind, "DVIDE") == 0) printf("div; ");
    } else if(strcmp(root->kind, "NEG") == 0) {
        codeR(root->child);
        printf("neg; ");
    } else if(strcmp(root->kind, "EQ") == 0 ||
    strcmp(root->kind, "NE") == 0 ||
    strcmp(root->kind, "GT") == 0 ||
    strcmp(root->kind, "GE") == 0 ||
    strcmp(root->kind, "LT") == 0 ||
    strcmp(root->kind, "LE") == 0 ) {
        codeR(root->child);
        codeR(root->child->bro);
        if(strcmp(root->kind, "EQ") == 0) printf("equ; ");
        else if(strcmp(root->kind, "NE") == 0) printf("neq; ");
        else if(strcmp(root->kind, "GT") == 0) printf("grt; ");
        else if(strcmp(root->kind, "GE") == 0) printf("geq; ");
        else if(strcmp(root->kind, "LT") == 0) printf("les; ");
        else if(strcmp(root->kind, "LE") == 0) printf("leq; ");
    } else if(strcmp(root->kind, "FCALL") == 0) {
        printf("mst; ");
        Node* t_node = root->child->bro;
        p = 0;
        while(t_node != NULL) {
            codeR(t_node);
            p++;
            t_node = t_node->bro;
        }
        printf("cup %d l%s ",p, root->child->value.var);
    }
}
void code(Node* root) {
    Node* tmp;
    int temp;
    if(strcmp(root->kind, "MAIN") == 0) {
        v = 0;
        v = countVar(root->child);
        printf("ssp %d; ", v + 2);
        code(root->child->bro);
        printf("stp ");
    } else if(strcmp(root->kind, "ASSIGN") == 0) {
        codeL(root->child);
        codeR(root->child->bro);
        printf("sto; ");
    } else if(strcmp(root->kind, "IF") == 0) {
        codeR(root->child);
        printf("fjp l%d", l);
        code(root->child->bro);
        temp = l;
        /** if then else 문 */
        if(root->child->bro->bro != NULL) {
            temp++;
            printf("ujp l%d; l%d: ", l + 1, l);
            l += 2;
            code(root->child->bro->bro);
        } else {
            l++;
            printf("l%d;", temp);
        }
    } else if(strcmp(root->kind, "WHILE") == 0) {
        printf("l%d: ", l);
        codeR(root->child);
        temp = l++;
        printf("fjp l%d; ", l);
        code(root->child->bro);
        printf("ujp l%d; l%d:", temp, l);
        l++;
    } else if(strcmp(root->kind, "FOR") == 0) {
        codeL(root->child);
        codeR(root->child->bro);
        printf("sto; l%d: ", l);
        temp = l++;
        codeR(root->child);
        codeR(root->child->bro->bro);
        printf("leq; fjp l%d; ", l);
        
        code(root->child->bro->bro->bro);
        codeL(root->child);
        codeR(root->child->bro);
        printf("ldc 1; add; sto; ujp l%d; l%d: ", temp, l);
        l++;
    } else if(strcmp(root->kind, "PCALL") == 0) {
        printf("mst; ");
        tmp = root->child->bro;
        p = 0;
        while(tmp != NULL) {
            codeR(tmp);
            p++;
            tmp = tmp->bro;
        }
        printf("cup %d l%s ", p, root->child->value.var);
    } else if(strcmp(root->kind, "PROC") == 0) {
        v = p = 0;
        p = countVar(root->child->bro);
        v = countVar(root->child->bro->bro);
        printf("l%s: ssp %d; ", root->child->value.var, p + v + 2);
        code(root->child->bro->bro->bro);
        printf("retp; ");
    } else if(strcmp(root->kind, "FUNC") == 0) {
        v = p = 0;
        v = countVar(root->child->bro->bro->bro);
        p = countVar(root->child->bro->bro);
        printf("l%s: ssp %d; ", root->child->value.var, p + v + 2);
        code(root->child->bro->bro->bro->bro);
        printf("reft; ");
    } else if(strcmp(root->kind, "RETURN") == 0) {
        codeR(root->child);
        printf("str 0; reft ");
    } else if(strcmp(root->kind, "COMP") == 0) {
        tmp = root->child;
        while(tmp != NULL) {
            code(tmp);
            tmp = tmp->bro;
        }
    }
}
void codeGen(Node* root) {
    Node* tmp = root->bro;
    while(tmp != NULL) {
        code(tmp);
        tmp = tmp->bro;
        if(tmp == NULL) break;
    }
    code(root);
}
void preOrder(Node *root) {
    printf("%s ", root->kind);
    if(root->child != NULL) preOrder(root->child);
    if(root->bro != NULL) preOrder(root->bro);
}
int main() {
    yyparse();
    return(0);
}

