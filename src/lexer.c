#include "lexer.h"

const char* DATA_TYPES[DATA_TYPES_ARR_LEN] = {
	"i8", "i16", "i32","i64",
	"ui8", "ui16", "ui32", "ui64",
	"f32", "bool", "xd", "str"
};

const char* KEYWORDS[KWDS_ARR_LEN] = {
	"if", "else", "elif",
	"for", "fun", "ret"
};

i16 find_keyword(const char* input_lex) {
	if (strcmp(input_lex, "if")) {
		return IF;
	}
	if (strcmp(input_lex, "else")) {
		return ELSE;
	}
	if (strcmp(input_lex, "elif")) {
		return ELIF;
	}
	if (strcmp(input_lex, "for")) {
		return FOR;
	}
	if (strcmp(input_lex, "fun")) {
		return FUN;
	}
	if (strcmp(input_lex, "ret")) {
		return RETURN;
	}
	return -1;
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '=' || c == '^'
		|| c == '!' || c == '<' || c == '>'; 
}

bool is_semicolon(char c) { return c == ';'; }

bool is_brace(char c) {
	return c == '(' || c == ')' 
		|| c == '[' || c == ']' 
		|| c == '{' || c == '}';
}

bool is_punctuation(char c) { return c == '.' || c == ','; }
bool is_quote(char c) { return c == '\"' || c == '\''; }

Token* next_token(const char* input, ui64* pos, ui64* line) {
	Token* token = new_Token(END, NULL, *pos, *line);
	char* lexeme = (char*)malloc(1);
	lexeme[0] = '\0';

	while (*pos < strlen(input)) {
		char c = input[*pos];

		if (c == ' ' || c == '\t' || c == '\r') {
			++(*pos);
			continue;
		}

		if (c == '\n') {
			++(*line);
			++(*pos);
			continue;
		}

		if (is_quote(c)) {
			++(*pos);

			while (*pos < strlen(input) && input[*pos] != '\"') {
				strcat(token->lexeme, strcat(token->lexeme, &input[*pos]));
				++(*pos);
			}
				
			token->type = STRING_LIT;
			token->subtype = STRING_LIT;
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			++(*pos);
			return token;
		}

		if (is_digit(c)) {
			bool float_flag = false;
			strcat(lexeme, &c);
			++(*pos);

			while ((*pos < strlen(input) && is_digit(input[*pos])) || input[*pos] == '.') {
				input[*pos] == '.' ? float_flag = true : false;
				strcat(lexeme, &input[*pos]);
				++(*pos);
			}

			// check is float valid
			if (float_flag) {
				token->type = DIGIT;
				token->subtype = FLOAT32;
				token->pos = *pos - strlen(lexeme);
				token->line = *line;
				return token;
			}
			
			token->type = DIGIT;
			token->subtype = INT32;
			strcpy(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_alpha(c)) {
			strcat(lexeme, &c);
			++(*pos);

			while (*pos < strlen(input) && (is_alpha(input[*pos]) || is_digit(input[*pos]))) {
				strcat(lexeme, &input[*pos]);
				++(*pos);
			}

			i16 kwd = find_keyword(lexeme);
			if (kwd != -1) {
				token->type = KEYWORD;
				token->subtype = kwd;
			} else {
				token->type = VARIABLE;
				token->subtype = VARIABLE;
			}

			strcpy(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_operator(c)) {
			strcat(lexeme, &c);
			++(*pos);

			while (*pos < strlen(input) && is_operator(input[*pos])) {
				strcat(lexeme, &input[*pos]);
				++(*pos);
			}

			if (strlen(lexeme) == 1) {
				switch (lexeme[0]) {
					case '=':
						token->subtype = ASSIGN;
						break;
					case '+':
						token->subtype = PLUS;
						break;
					case '-':
						token->subtype = MINUS;
						break;
					case '*':
						token->subtype = MUL;
						break;
					case '/':
						token->subtype = DIV;
						break;
					case '^':
						token->subtype = POW;
						break;
					case '!':
						token->subtype = NOT;
						break;
					case '<':
						token->subtype = LOWER;
						break;
					case '>':
						token->subtype = GREATER;
						break;
				}
			} else {
				if (strcmp(lexeme, "==") == 0) {
					token->subtype = EQUAL;
				} else if (strcmp(lexeme, "!=") == 0) {
					token->subtype = NEQUAL;
				} else if (strcmp(lexeme, ">=") == 0) {
					token->subtype = GREQUAL;
				} else if (strcmp(lexeme, "<=") == 0) {
					token->subtype = LEQUAL;
				} else if (strcmp(lexeme, "->") == 0) {
					token->subtype = ARROW;
				}
				break;
			}
			token->type = OPERATOR;
			strcpy(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_punctuation(c)) {
			strcat(lexeme, &c);
			++(*pos);

			token->type = PUNCTUATION;
			strcpy(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_semicolon(c)) {
			strcat(lexeme, &c);
			++(*pos);

			token->type = PUNCTUATION;
			strcpy(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		++(*pos);
	}

	token = new_Token(END, NULL, *pos, *line);
	return token;
}

dArray* tokenize(const char* input) {
	dArray* out_arr = new_dArray(); 

	Token* token = new_Token(END, "", 0, 0);
	ui64 pos = 0;
	ui64 tmp_line = 1;

	do {
		token = next_token(input, &pos, &tmp_line);
		printf("%s, ", token->lexeme);
		out_arr->push(out_arr, token);
	} while (strcmp(token->lexeme, "") != 0);
	return out_arr;
}
