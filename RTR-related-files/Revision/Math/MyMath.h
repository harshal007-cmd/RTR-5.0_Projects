#pragma once

// 2D 3D and 4D

typedef struct{
    float data[2];
} vec2;

typedef struct{
    float data[3];
} vec3;

typedef struct{
    float data[4];
} vec4;

void vec2_create(vec2* result, float x, float y);

void vec2_add(vec2* result,const vec2* v0,const vec2* v1);
void vec2_substract(vec2* result, const vec2* v0,const vec2* v1);
void vec2_multiple(vec2* result, const vec2* v0, float scalar);
void vec2_divide(vec2* result, const vec2* v0, float scalar);

void vec2_normalize(vec2 *result, const vec2* v0);

float vec2_dot(const vec2* v0, const vec2* v1);
float vec2_length(const vec2* v0);
float vec2_distance(const vec2* v0,const vec2* v1);
