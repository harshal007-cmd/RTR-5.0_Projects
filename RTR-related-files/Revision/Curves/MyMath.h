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

void vec2_set(vec2* result, float x, float y);
void vec2_add(vec2* result,const vec2* v0,const vec2* v1);
void vec2_substract(vec2* result, const vec2* v0,const vec2* v1);
void vec2_multiple(vec2* result, const vec2* v0, float scalar);
void vec2_divide(vec2* result, const vec2* v0, float scalar);
void vec2_normalize(vec2 *result, const vec2* v0);
float vec2_dot(const vec2* v0, const vec2* v1);
float vec2_length(const vec2* v0);
float vec2_distance(const vec2* v0,const vec2* v1);
void vec2_lerp(vec2* result, const vec2* v0, const vec2* v1, float t);

void    vec3_set(vec3* result, float x, float y,float z);
void    vec3_add(vec3* result,const vec3* v0,const vec3* v1);
void    vec3_substract(vec3* result, const vec3* v0,const vec3* v1);
void    vec3_multiple(vec3* result, const vec3* v0, float scalar);
void    vec3_divide(vec3* result, const vec3* v0, float scalar);
void    vec3_normalize(vec3 *result, const vec3* v0);
float   vec3_dot(const vec3* v0, const vec3* v1);
void    vec3_cross(vec3* result, const vec3* v0, const vec3* v1);
float   vec3_length(const vec3* v0);
float   vec3_distance(const vec3* v0,const vec3* v1);

void    vec4_set(vec4* result, float x, float y, float z, float w);
void    vec4_add(vec4* result,const vec4* v0,const vec4* v1);
void    vec4_substract(vec4* result, const vec4* v0,const vec4* v1);
void    vec4_multiple(vec4* result, const vec4* v0, float scalar);
void    vec4_divide(vec4* result, const vec4* v0, float scalar);
void    vec4_normalize(vec4 *result, const vec4* v0);
float   vec4_dot(const vec4* v0, const vec4* v1);
float   vec4_length(const vec4* v0);
float   vec4_distance(const vec4* v0,const vec4* v1);
