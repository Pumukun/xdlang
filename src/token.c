#include "token.h"

Token* new_Token(i16 atype, char* alexeme, i64 apos, i64 aline) {
	Token* token = (Token*)malloc(sizeof(Token));
	token->lexeme = (char*)malloc(strlen(alexeme) + 1);
	token->type = atype;
	strcpy(token->lexeme, alexeme);
	token->pos = apos;
	token->line = aline;
	return token;
}
