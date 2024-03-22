#include "dynamic_array.h"

void check_address(void* p)

dArray* new_dArray() {
	dArray* array = (dArray*)malloc(sizeof(dArray));
	check_address(array);

	array->size = 0;
	array->capacity = 0;
	array->data = malloc(array->size * sizeof(Token*));
	check_address(array->data);

	array->push = &dArray_push;
	array->pop_back = &dArray_popback;
	array->foreach = &dArray_foreach;

	return array;
}

void dArray_push(dArray* arr, Token* input) {
	arr->size++;

	arr->data = realloc(arr->data, arr->size * sizeof(Token*));
	check_address(arr->data);

	arr->data[arr->size - 1] = (Token*)malloc((strlen(input) + 1) * sizeof(Token));
	check_address(arr->data[arr->size - 1]);
}

void dArray_popback(dArray* arr) {
	if (arr->size == 0) {
		exit(EXIT_FAILURE);
	}
	free(arr->data[arr->size - 1]);
    arr->data[arr->size - 1] = NULL;
    
    arr->size--;
    
    arr->data = realloc(arr->data, arr->size * sizeof(Token*));
    check_address(arr->data);
}

void dArray_foreach(dArray* arr, void (*f_ptr)(Token*)) {
	for (ui64 i = 0; i < arr->size; i++) {
		f_ptr(arr->data[i]);
	}
}

void check_address(void* p) {
	if (p == NULL) {
		printf("Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
}

