#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main() {

	char* input = "x = 10 - 3;\ny = x + 5;\nif x == y { print x; } else { print y; }\n";
	tokenize(input);

	return 0;
}


