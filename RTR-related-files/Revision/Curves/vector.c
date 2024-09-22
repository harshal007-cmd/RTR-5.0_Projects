#include<stdio.h>
#include<math.h>
#include"MyMath.h"

void vec2_create(vec2* result, float x, float y)
{
	result->data[0] = x;
	result->data[1] = y;
	
}
void vec2_add(vec2* result, const vec2* v0, const vec2* v1)
{
	result->data[0] = v0->data[0] + v1->data[0];
	result->data[1] = v0->data[1] + v1->data[1];


}
void vec2_substract(vec2* result, const vec2* v0, const vec2* v1)
{
	result->data[0] = v0->data[0] - v1->data[0];
	result->data[1] = v0->data[1] - v1->data[1];

}
void vec2_multiply(vec2* result, const vec2* v0, float scaler)
{
	result->data[0] = v0->data[0] * scaler;
	result->data[1] = v0->data[1] * scaler;

}
void vec2_divide(vec2* result, const vec2* v0, float scaler)
{
	result->data[0] = v0->data[0] / scaler;
	result->data[1] = v0->data[1] / scaler;

}
void vec2_normalise(vec2* result, const vec2* v0)
{
	float len = vec2_length(v0);
	vec2_divide(result, v0, len);
}

float vec2_dot(const vec2* v0, const vec2* v1)
{
	return(v0->data[0] * v1->data[0] + v0->data[1] * v1->data[1]);

}

float vec2_length(const vec2* v0)
{
	return sqrt(v0->data[0] * v0->data[0] + v0->data[1] * v0->data[1]);
}

float vec2_dist(const vec2* v0, const vec2* v1)
{
	vec2 diff;
	vec2_substract(&diff,v0, v1);

	return vec2_length(&diff);

}

float vec2_lerp(vec2* result, const vec2* v0, const vec2* v1)
{

	return 0.0f;
}

//vector 3
void vec3_create(vec3* result, float x, float y,float z)
{
	result->data[0] = x;
	result->data[1] = y;
	result->data[2] = z;
}

void vec3_add(vec3* result, const vec3* v0, const vec3* v1)
{
	result->data[0] = v0->data[0] + v1->data[0];
	result->data[1] = v0->data[1] + v1->data[1];
	result->data[2] = v0->data[2] + v1->data[2];

}
void vec3_substract(vec3* result, const vec3* v0, const vec3* v1)
{
	result->data[0] = v0->data[0] - v1->data[0];
	result->data[1] = v0->data[1] - v1->data[1];
	result->data[2] = v0->data[2] - v1->data[2];

}
void vec3_multiply(vec3* result, const vec3* v0, float scaler)
{
	result->data[0] = v0->data[0] * scaler;
	result->data[1] = v0->data[1] * scaler;
	result->data[2] = v0->data[2] * scaler;

}
void vec3_divide(vec3* result, const vec3* v0, float scaler)
{
	result->data[0] = v0->data[0] / scaler;
	result->data[1] = v0->data[1] / scaler;
	result->data[2] = v0->data[2] / scaler;

}
void vec3_normalise(vec3* result, const vec3* v0)
{
	float len = vec3_length(v0);
	vec3_divide(result, v0, len);

}
float vec3_dot(const vec3* v0, const vec3* v1)
{
	return(v0->data[0] * v1->data[0] + v0->data[1] * v1->data[1] + v0->data[2] * v1->data[2]);


}

void vec3_cross(vec3* result, const vec3* v0, const vec3* v1)
{

	result->data[0] = v0->data[1] * v1->data[2] - v0->data[2] * v1->data[1];
	result->data[1] = v0->data[2] * v1->data[0] - v0->data[0] * v1->data[2];
	result->data[2] = v0->data[0] * v1->data[1] - v0->data[1] * v1->data[0];


}

float vec3_length(const vec3* v0)
{
	return sqrt(v0->data[0] * v0->data[0] + v0->data[1] * v0->data[1] + v0->data[2] * v0->data[2]);

}
float vec3_dist(const vec3* v0, const vec3* v1)
{
	vec3 diff;
	vec3_substract(&diff, v0, v1);

	return vec3_length(&diff);
}

//Vec4 Implementation

void vec4_create(vec4* result, float x, float y, float z, float w)
{
	result->data[0] = x;
	result->data[1] = y;
	result->data[2] = z;
	result->data[3] = w;
}

void vec4_add(vec4* result, const vec4* v0, const vec4* v1)
{
	result->data[0] = v0->data[0] + v1->data[0];
	result->data[1] = v0->data[1] + v1->data[1];
	result->data[2] = v0->data[2] + v1->data[2];
	result->data[3] = v0->data[3] + v1->data[3];
}

void vec4_substract(vec4* result, const vec4* v0, const vec4* v1)
{
	result->data[0] = v0->data[0] - v1->data[0];
	result->data[1] = v0->data[1] - v1->data[1];
	result->data[2] = v0->data[2] - v1->data[2];
	result->data[3] = v0->data[3] - v1->data[3];
}
void vec4_multiply(vec4* result, const vec4* v0, float scaler)
{
	result->data[0] = v0->data[0] * scaler;
	result->data[1] = v0->data[1] * scaler;
	result->data[2] = v0->data[2] * scaler;
	result->data[3] = v0->data[3] * scaler;

}
void vec4_divide(vec4* result, const vec4* v0, float scaler)
{
	result->data[0] = v0->data[0] / scaler;
	result->data[1] = v0->data[1] / scaler;
	result->data[2] = v0->data[2] / scaler;
	result->data[3] = v0->data[3] / scaler;

}

void vec4_normalise(vec4* result, const vec4* v0)
{
	float num = vec4_length(v0);

	vec4_divide(result, v0, num);

}

float vec4_dot(const vec4* v0, const vec4* v1)
{

}

float vec4_length(const vec4* v0)
{
	return sqrt(v0->data[0] * v0->data[0] + v0->data[1] * v0->data[1] + v0->data[2] * v0->data[2] + v0->data[3] * v0->data[3]);

}

float vec4_dist(const vec4* v0, const vec4* v1)
{
	vec4 diff;
	vec4_substract(&diff, v0, v1);

	return vec4_length(&diff);
}
