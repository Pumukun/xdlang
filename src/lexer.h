#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "stdinc.h"
#include "token.h"
#include "dynamic_array.h"

#define DATA_TYPES_ARR_LEN 12
extern const char* DATA_TYPES[DATA_TYPES_ARR_LEN];

#define KWDS_ARR_LEN 6
extern const char* KEYWORDS[KWDS_ARR_LEN];

i16 find_keyword(const char* input_lex);

bool is_digit(char c);
bool is_alpha(char c);
bool is_operator(char c);
bool is_semicolon(char c);
bool is_brace(char c);
bool is_punctuation(char c);
bool is_quote(char c);

Token* next_token(const char* input, ui64* pos, ui64* line);

dArray* tokenize(const char* input);

#endif /* LEXER_H */
