#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "stdinc.h"

typedef enum Token_type {
	KEYWORD			= 0,
	OPERATOR		= 1,
	VARIABLE		= 2,
	SEMICOLON		= 3,
	BRACE			= 4,
	PUNCTUATION		= 5,
	DIGIT			= 6,
	STRING_LIT		= 7,
	DATA_TYPE		= 8,
	END				= 9
} Token_type;

/**
 * Keyword prefix: 2
*/ 
enum Keyword_type {
	IF		= 20,		///< if
	ELSE	= 21,		///< else
	ELIF	= 22,		///< elif
	
	FOR		= 23,		///< for

	FUN		= 24,		///< fun
	RETURN	= 25,		///< ret
};

/**
 * Data type prefix: 3
 * int suffix: 1, float suffix: 2, string suffix: 3.
 * size suffix: 0 = 8bit, 1 = 16bit, 2 = 32bit, 3 = 64bit.
*/
enum Data_type {
	INT8	= 310,		///< i8
	INT16	= 311,		///< i16
	INT32	= 312,		///< i32
	INT64	= 313,		///< i64
	BOOL	= 314,		///< bool

	FLOAT32	= 322,		///< f32

	STRING	= 333,		///< str
	XD		= 999		///< xd
};

/**
 * Brace prefix: 1
 * Open suffix: 1
 * Close suffix: 0
 * Brace types suffix:
 * 	- '(', ')' : 0
 * 	- '[', ']' : 1
 * 	- '{'. '}' : 2
 *
 * Example: '(' will be 110. First - brace token bit, Second - Open/Close, Third - brace type.
 * PH - parentheses, SB - squre braces, CB - curly braces.
*/
enum Brace_type {
	PH_O = 110,		///< (
	PH_C = 100,		///< )
	SB_O = 111,		///< [
	SB_C = 101,		///< ]
	CB_O = 112,		///< {
	CB_C = 102		///< }
};

/**
 * Operator prefix: 4
 * Arifmetic operator suffix: 0
 * Conditional operators suffix: 1
*/ 
enum Operator_type {
	ASSIGN	= 400,		///< =
	POW		= 401,		///< ^
	MUL		= 402,		///< *
	DIV		= 403,		///< /
	PLUS	= 404,		///< +
	MINUS	= 405,		///< -
	ARROW	= 406,		///< ->

	EQUAL	= 411,		///< ==
	NEQUAL	= 412,		///< !=
	GREATER	= 413,		///< >
	LOWER	= 414,		///< <
	
	GREQUAL	= 415,		///< >=
	LEQUAL	= 416,		///< <=
	NOT		= 417		///< !
};

/**
 * Punctuation prefix: 5
*/
enum Punctuation_type {
	DOT		= 50,	///< .
	COMMA	= 51	///< ,
};

typedef struct Token {
	ui16 type;
	ui16 subtype;
	char* lexeme;
	ui64 pos;
	ui64 line;
} Token;

Token* new_Token(i16 atype, char* alexeme, i64 apos, i64 aline) {
	Token* token = (Token*)malloc(sizeof(Token));
	token->type = atype;
	strcpy(token->lexeme, alexeme);
	token->pos = apos;
	token->line = aline;
	return token;
}

#endif /* TOKEN_H */
