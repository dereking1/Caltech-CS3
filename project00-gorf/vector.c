#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

typedef struct vector {
    double x;
    double y;
} vector_t;

vector_t *vec_init(double x, double y) {
    vector_t *vec = malloc(sizeof(vector_t));
    assert(vec != NULL);
    vec->x = x;
    vec->y = y;
    return vec;
}

void vec_free(vector_t *vec) {
    free(vec);
}

vector_t *vec_add(vector_t *v1, vector_t *v2) {
    return vec_init(v1->x + v2->x, v1->y + v2->y);
}