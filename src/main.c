#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main() {

	char* input = "if else elif for fun ret";
	tokenize(input);

	return 0;
}


