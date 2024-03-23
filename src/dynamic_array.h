#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>

#include "token.h"

typedef struct dArray {
	Token** data;
	ui64 capacity;
	ui64 size;

	void (*push)(struct dArray*, Token*);
	void (*pop_back)(struct dArray*);
	void (*foreach)(struct dArray*, void (*f_ptr)(Token*));
} dArray;

dArray* new_dArray();

void dArray_push(dArray* arr, Token* input);
void dArray_popback(dArray* arr);

void dArray_foreach(dArray* arr, void (*f_ptr)(Token*));

#endif /* DYNAMIC_ARRAY_H */
