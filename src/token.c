#include "token.h"

Token* new_Token(i16 atype, char* alexeme, i64 apos, i64 aline) {
	Token* token = (Token*)malloc(sizeof(Token));
	token->type = atype;
	if (alexeme == NULL) {
		token->lexeme = (char*)malloc(1);
		token->lexeme[0] = '\0';
	} else {
		token->lexeme = (char*)malloc(sizeof(char) * (strlen(alexeme) + 1));
		strcpy(token->lexeme, alexeme);
	}
	token->pos = apos;
	token->line = aline;
	return token;
}
