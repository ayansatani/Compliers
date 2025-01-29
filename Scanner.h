/*
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 26

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	COL_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	VID_T,		/* 13: Variable token*/
	EQU_T,		/* 14: Equal token*/
	LES_T,		/* 15: Less than token*/
	COM_T,		/* 16: Comma token*/
	LSB_T,		/* 17: Left square bracket*/
	RSB_T,		/* 18: Right square bracket*/
	LSQ_T,		/* 19: Right single qoute*/
	ADD_T,		/* 20: Add token*/
	MULL_T,		/* 21: Multiply token*/
	SUB_T,		/* 22: Subtraction token*/
	DIV_T,		/* 23: Division token*/
	MOD_T,		/* 24" Modulas token*/
};

/* TO_DO: Define the list of keywords */
static String tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"COL_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"VID_T",
	"EQU_T",
	"LES_T",
	"COM_T",
	"LSB_T",
	"RSB_T",
	"LSQ_T",
	"ADD_T",
	"MULL_T",
	"SUB_T",
	"DIV_T",
	"MOD_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int intValue;				/* integer literal attribute (value) */
	int keywordIndex;			/* keyword index in the keyword table */
	int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float floatValue;				/* floating-point literal attribute (value) */
	Char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	Char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	infinity_byte flags;			/* Flags information */
	union {
		int intValue;				/* Integer value */
		float floatValue;			/* Float value */
		String stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '\"'
#define CHRCOL4 '\n'
#define CHRCOL6 '#'
#define CHRCOL8 '\s'


/* These constants will be used on VID / MID function */
#define MNID_SUF 'def'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		13
#define CHAR_CLASSES	10

/* TO_DO: Transition table - type of states defined in separate table */
static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
 /* [A - z] ,[0 - 9],    _,    \",  \n',SEOF,      #,     (        \s       other
	L(0), D(1), U(2), M(3), Q(4), E(5),   C(6),  B(7),    W(8)     O(9) */
	{     1,    4, ESNR,    4,    4, ESWR,      6,     2,    ESNR,   ESNR},     // S0: NOAS
	{     1,    1,    1,    3,    3,    3,      3,    2,        3,      3},     // S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S2: ASNR (MVID)
	{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S3: ASWR (KW)
	{     4,    4,    4,    5,    9, ESWR,      4,    4,        4,      4},     // S4: NOAS
	{    FS,    5,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S5: ASNR (IL)
	{     6,    6,    6,    6,    7,    7,      7,    7,        6,      6},     // S6: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S7: ASNR (COM)
	{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S8: ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S9: ASWR (ER)
	{    FS,    FS,    FS,   FS,   FS,   FS,     FS,   FS,       FS,     FS},     // S10: NOAS (Variable Identifier)
	{    FS,   FS,   FS,   FS,   FS,   FS,    FS,    FS,      FS,      FS}      // S11: ASNR (Integer Literal)
};





/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) - String Literal */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) - Comment */
	FSNR, /* 08 (ES) - Error 1 (no retract) */
	FSWR, /* 09 (ER) - Error 2 (retract) */
	FSNR, /* 10 (Variable Identifier) */
	FSNR, /* 11 (Integer Literal) */
	FSNR  /* 12 (String Literal) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int			startScanner(BufferPointer psc_buf);
static int	nextClass(Char c);					/* character class function */
static int	nextState(int, Char);		/* state machine function */
void			printScannerData(ScannerData scData);
Token				tokenizer(void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(String lexeme);

/* Declare accepting states functions */
Token funcSL(String lexeme);
Token funcIL(String lexeme);
Token funcID(String lexeme);
Token funcCMT(String lexeme);
Token funcKEY(String lexeme);
Token funcErr(String lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] - Comment */
	funcErr,	/* ERR1 [08] - Error 1 (no retract) */
	funcIL,		/* ERR2 [09] - Error 2 (retract) */
	NULL,       /* -    [10] */
	NULL,
	funcIL
};


/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 15

/* TO_DO: Define the list of keywords */
static String keywordTable[KWT_SIZE] = {
	
	"int",			/* KW00 */
	"void",			/* KW01 */
	"return",		/* KW02 */
	"if",			/* KW03 */
	"def",			/* KW04 */
	"else",			/* KW05 */
	"while",		/* KW06 */
	"do",			/* KW07 */
	"break",		/* KW08 */
	"for",			/* KW09 */
	"NULL",			/* KW10 */
	"try",			/* KW11 */
	"except",		/* KW12 */
	"True",			/* KW13 */
	"False"			/* KW14 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	Char indentationCharType;
	int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
