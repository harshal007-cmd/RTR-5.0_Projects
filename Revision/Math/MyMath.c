#include "MyMath.h"
#include <math.h>

// Constructor for vec2 type
void vec2_create(vec2* result, float x, float y){
    result->data[0] = x;
    result->data[1] = y;
}

void vec2_add(vec2* result,const vec2* v0,const vec2* v1){
    result->data[0] = v0->data[0] + v1->data[0];
    result->data[1] = v0->data[1] + v1->data[1];
}

void vec2_substract(vec2* result, const vec2* v0,const vec2* v1){
    result->data[0] = v0->data[0] - v1->data[0];
    result->data[1] = v0->data[1] - v1->data[1];
}

void vec2_multiple(vec2* result, const vec2* v0, float scalar){
    result->data[0] = v0->data[0] * scalar;
    result->data[1] = v0->data[1] * scalar;
}

void vec2_divide(vec2* result, const vec2* v0, float scalar){
    result->data[0] = v0->data[0] / scalar;
    result->data[1] = v0->data[1] / scalar;
}

void vec2_normalize(vec2 *result, const vec2* v0){
    float len = vec2_length(v0);
    vec2_divide(result, v0, len);
}

float vec2_dot(const vec2* v0, const vec2* v1){
    return v0->data[0] * v1->data[0] + v0->data[1] * v1->data[1];    
}

float vec2_length(const vec2* v0){
    return sqrt(v0->data[0] * v0->data[0] + v0->data[1] * v0->data[1]);
}

float vec2_distance(const vec2* v0,const vec2* v1){
    vec2 diff;
    vec2_substract(&diff, v0, v1);
    return vec2_length(&diff);
}
