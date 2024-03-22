#include "lexer.h"

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
	char* lexeme = "";

	while (*pos < strlen(input)) {
		char c = input[*pos];

		if (c == ' ' || c == '\t' || c == '\r') {
			pos++;
			continue;
		}

		if (c == '\n') {
			line++;
			pos++;
			continue;
		}

		if (is_quote(c)) {
			pos++;

			while (*pos < strlen(input) && input[*pos] != '\"') {
				strcat(token->lexeme, strcat(token->lexeme, (char*)input[*pos]));
				pos++;
			}
				
			token->type = STRING_LIT;
			token->subtype = STRING_LIT;
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			pos++;
			return token;
		}

		if (is_digit(c)) {
			strcat(lexeme, (char*)c);
			pos++;

			while (*pos < strlen(input) && is_digit(input[*pos])) {
				strcat(lexeme, input[*pos]);
				pos++;
			}
			
			token->type = DIGIT;
			token->subtype = INT16;
			strcat(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_alpha(c)) {
			strcat(lexeme, (char*)c);
			pos++;

			while (pos < strlen(input) && (is_alpha(input[pos]) || is_digit(input[pos]))) {
				strcat(lexeme, input[*pos]);
				pos++;
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
			token->pos = pos - strlen(lexeme);
			token->line = line;
			return token;
		}

		if (is_operator(c)) {
			lexeme += c;
			pos++;

			while (pos < (int)input.length() && is_operator(input[pos])) {
				lexeme += input[pos];
				pos++;
			}

			if (lexeme == "=") {
				token->type = OPERATOR;
			} else { token->type = OPERATOR; }

			strcat(token->lexeme, lexeme);
			token->pos = *pos - strlen(lexeme);
			token->line = *line;
			return token;
		}

		if (is_punctuation(c)) {
			lexeme += c;
			pos++;

			token.set_type(PUNCTUATION);
			token.set_lexeme(lexeme);
			token.set_pos(pos - (int)lexeme.size());
			token.set_line(line);
			return token;
		}

		if (is_semicolon(c)) {
			lexeme += c;
			pos++;

			token.set_type(SEMICOLON);
			token.set_lexeme(lexeme);
			token.set_pos(pos - (int)lexeme.size());
			token.set_line(line);
			return token;
		}

		pos++;

		if (!is_alpha(c) && !is_digit(c) && !is_operator(c) && !is_punctuation(c)) {
			string msg = "Error on line: " + to_string(line) + ", pos: " + to_string(pos) + ", unknown Token: " + input[pos-1] + "\n";
			syntax_errors.push_back(msg);
		}
	}

	token.set_type(END);
	token.set_lexeme("");
	token.set_pos(pos);
	token.set_line(line);
	return token;
}

Token* tokenize(const char* input) {
	dArray* out_arr = new_dArray(); 

	Token* token;
	ui64 pos = 0;
	ui64 tmp_line = 1;

	do {
		token = next_token(&input, &pos, &tmp_line);
		out_arr->push(&out_arr, &token);
	} while (token.get_lexeme() != "");
}
