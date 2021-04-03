#ifndef __MYMATH_H__
#define __MYMATH_H__

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct vec4
{
    float x, y, z, w;
};


void vec2_add(struct vec2* vec, struct vec2* input);
void vec2_addf(struct vec2* vec, float input);
void vec2_addv(struct vec2* vec, float* input, unsigned int len);
void vec2_sub(struct vec2* vec, struct vec2* input);
void vec2_subf(struct vec2* vec, float input);
void vec2_subv(struct vec2* vec, float* input, unsigned int len);
void vec2_mul(struct vec2* vec, struct vec2* input);
void vec2_mulf(struct vec2* vec, float input);
void vec2_mulv(struct vec2* vec, float* input, unsigned int len);
void vec2_div(struct vec2* vec, struct vec2* input);
void vec2_divf(struct vec2* vec, float input);
void vec2_divv(struct vec2* vec, float* input, unsigned int len);

void vec3_add(struct vec3* vec, struct vec3* input);
void vec3_addf(struct vec3* vec, float input);
void vec3_addv(struct vec3* vec, float* input, unsigned int len);
void vec3_sub(struct vec3* vec, struct vec3* input);
void vec3_subf(struct vec3* vec, float input);
void vec3_subv(struct vec3* vec, float* input, unsigned int len);
void vec3_mul(struct vec3* vec, struct vec3* input);
void vec3_mulf(struct vec3* vec, float input);
void vec3_mulv(struct vec3* vec, float* input, unsigned int len);
void vec3_div(struct vec3* vec, struct vec3* input);
void vec3_divf(struct vec3* vec, float input);
void vec3_divv(struct vec3* vec, float* input, unsigned int len);

float vec3_length(struct vec3* vec);
void vec3_cross(struct vec3* result, struct vec3* u, struct vec3* v);
void vec3_normalize(struct vec3* vec);

void vec4_add(struct vec4* vec, struct vec4* input);
void vec4_addf(struct vec4* vec, float input);
void vec4_addv(struct vec4* vec, float* input, unsigned int len);
void vec4_sub(struct vec4* vec, struct vec4* input);
void vec4_subf(struct vec4* vec, float input);
void vec4_subv(struct vec4* vec, float* input, unsigned int len);
void vec4_mul(struct vec4* vec, struct vec4* input);
void vec4_mulf(struct vec4* vec, float input);
void vec4_mulv(struct vec4* vec, float* input, unsigned int len);
void vec4_div(struct vec4* vec, struct vec4* input);
void vec4_divf(struct vec4* vec, float input);
void vec4_divv(struct vec4* vec, float* input, unsigned int len);

void mat4_ident(float matrix[4][4]);
void mat4_fill(float matrix[4][4], float val);
void mat4_translate(float matrix[4][4], struct vec3* translate);
void mat4_rotate(float matrix[4][4], float angle);
void mat4_mul(float result[4][4], float a[4][4], float b[4][4]);
void mat4_perspective(float matrix[4][4], float angle, float ratio, float near, float far);
void mat4_lookat(float matrix[4][4], struct vec3* eye, struct vec3* center, struct vec3* worldup);

float vec_dot(int vec_size, float* u, float* v);
float deg2rad(float degrees);

#endif