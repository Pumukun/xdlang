#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stdinc.h"
#include "token.h"
#include "dynamic_array.h"

const char* DATA_TYPES[] = {
	"i8", "i16", "i32","i64",
	"ui8", "ui16", "ui32", "ui64",
	"f32", "bool", "xd", "str"
};

#define KWDS_ARR_LEN 6
const char* KEYWORDS[KWDS_ARR_LEN] = {
	"if", "else", "elif",
	"for", "fun", "ret"
};

i16 find_keyword(const char* input_lex);

bool is_digit(char c);
bool is_alpha(char c);
bool is_operator(char c);
bool is_semicolon(char c);
bool is_brace(char c);
bool is_punctuation(char c);
bool is_quote(char c);

Token next_token(const char* input, ui64* pos, ui64* line);

Token* tokenize(const char* input);

#endif /* LEXER_H */
