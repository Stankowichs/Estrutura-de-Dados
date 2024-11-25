#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

struct float_vector {
    int size;
    int capacity;
    float *data;
};

FloatVector *createVector(int capacity) {
    FloatVector *vec = malloc(sizeof(FloatVector));
    
    vec->size = 0;
    vec->capacity = capacity;
    vec->data = calloc(capacity, sizeof(float));

    return vec;
}

void destroyVec(FloatVector **vec_ref) {
    FloatVector *vector = vec_ref;
    
    free(vector->data);
    free(vector);
    vec_ref = NULL;
}

int size(FloatVector *vec) {
    return vec->size; 
}

int capacity(FloatVector *vec) {
    return vec->capacity;
}

void append(FloatVector *vec, float val) {
    if(vec->size == vec->capacity) {
        fprintf(stderr, "Error in 'append\n");
        fprintf(stderr, "Vector is full\n");
        exit(EXIT_FAILURE);
    }

    vec->data[vec->size++] = val;
}

float at(FloatVector *vec, int index) {
     if(index < 0 || index >= vec->size) {
        fprintf(stderr, "Error in 'set\n");
        fprintf(stderr, "Index [%d] is out of bounds: [0, %d]\n", index, vec->capacity);

        exit(EXIT_FAILURE);
    }
    
    return vec->data[index];
}

float get(FloatVector *vec, int index) {
    return vec->data[index];
}

void set(FloatVector *vec, int index, float val) {
    if(index < 0 || index >= vec->size) {
        fprintf(stderr, "Error in 'set\n");
        fprintf(stderr, "Index is not valid\n");

        exit(EXIT_FAILURE);
    }

    vec->data[index] = val;
}


void print(FloatVector *vec) {
    printf("Size: %d\n", vec->size);
    printf("Total capacity: %d\n", vec->capacity);
    printf("Data: %.2f\n\n", vec->data);   
}
