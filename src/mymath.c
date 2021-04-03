#include <math.h>
#include "mymath.h"

// vec2
//-----------------------------------------------
void vec2_add(struct vec2* vec, struct vec2* input)
{
    vec->x += input->x;
    vec->y += input->y;
}

//-----------------------------------------------
void vec2_addf(struct vec2* vec, float input)
{
    vec->x += input;
    vec->y += input;
}

//-----------------------------------------------
void vec2_addv(struct vec2* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 2] += input[i];
    }
}

//-----------------------------------------------
void vec2_sub(struct vec2* vec, struct vec2* input)
{
    vec->x -= input->x;
    vec->y -= input->y;
}

//-----------------------------------------------
void vec2_subf(struct vec2* vec, float input)
{
    vec->x -= input;
    vec->y -= input;
}

//-----------------------------------------------
void vec2_subv(struct vec2* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 2] -= input[i];
    }
}

//-----------------------------------------------
void vec2_mul(struct vec2* vec, struct vec2* input)
{
    vec->x *= input->x;
    vec->y *= input->y;
}

//-----------------------------------------------
void vec2_mulf(struct vec2* vec, float input)
{
    vec->x *= input;
    vec->y *= input;
}

//-----------------------------------------------
void vec2_mulv(struct vec2* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 2] *= input[i];
    }
}

//-----------------------------------------------
void vec2_div(struct vec2* vec, struct vec2* input)
{
    vec->x /= input->x;
    vec->y /= input->y;
}

//-----------------------------------------------
void vec2_divf(struct vec2* vec, float input)
{
    vec->x /= input;
    vec->y /= input;
}

//-----------------------------------------------
void vec2_divv(struct vec2* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 2] /= input[i];
    }
}


// vec3
//-----------------------------------------------
void vec3_add(struct vec3* vec, struct vec3* input)
{
    vec->x += input->x;
    vec->y += input->y;
    vec->z += input->z;
}

//-----------------------------------------------
void vec3_addf(struct vec3* vec, float input)
{
    vec->x += input;
    vec->y += input;
    vec->z += input;
}

//-----------------------------------------------
void vec3_addv(struct vec3* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 3] += input[i];
    }
}

//-----------------------------------------------
void vec3_sub(struct vec3* vec, struct vec3* input)
{
    vec->x -= input->x;
    vec->y -= input->y;
    vec->z -= input->z;
}

//-----------------------------------------------
void vec3_subf(struct vec3* vec, float input)
{
    vec->x -= input;
    vec->y -= input;
    vec->z -= input;
}

//-----------------------------------------------
void vec3_subv(struct vec3* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 3] -= input[i];
    }
}

//-----------------------------------------------
void vec3_mul(struct vec3* vec, struct vec3* input)
{
    vec->x *= input->x;
    vec->y *= input->y;
    vec->z *= input->z;
}

//-----------------------------------------------
void vec3_mulf(struct vec3* vec, float input)
{
    vec->x *= input;
    vec->y *= input;
    vec->z *= input;
}

//-----------------------------------------------
void vec3_mulv(struct vec3* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 3] *= input[i];
    }
}

//-----------------------------------------------
void vec3_div(struct vec3* vec, struct vec3* input)
{
    vec->x /= input->x;
    vec->y /= input->y;
    vec->z /= input->z;
}

//-----------------------------------------------
void vec3_divf(struct vec3* vec, float input)
{
    vec->x /= input;
    vec->y /= input;
    vec->z /= input;
}

//-----------------------------------------------
void vec3_divv(struct vec3* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 3] /= input[i];
    }
}

//-----------------------------------------------
float vec3_length(struct vec3* vec)
{
    return sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

//-----------------------------------------------
void vec3_cross(struct vec3* result, struct vec3* u, struct vec3* v)
{
    result->x = (u->y * v->z) - (u->z * v->y);
    result->y = (u->z * v->x) - (u->x * v->z);
    result->z = (u->x * v->y) - (u->y * v->x);
}

//-----------------------------------------------
void vec3_normalize(struct vec3* vec)
{
    float length = vec3_length(vec);
    vec3_divf(vec, length);
}


// vec4
//-----------------------------------------------
void vec4_add(struct vec4* vec, struct vec4* input)
{
    vec->x += input->x;
    vec->y += input->y;
    vec->z += input->z;
    vec->w += input->w;
}

//-----------------------------------------------
void vec4_addf(struct vec4* vec, float input)
{
    vec->x += input;
    vec->y += input;
    vec->z += input;
    vec->w += input;
}

//-----------------------------------------------
void vec4_addv(struct vec4* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 4] += input[i];
    }
}

//-----------------------------------------------
void vec4_sub(struct vec4* vec, struct vec4* input)
{
    vec->x -= input->x;
    vec->y -= input->y;
    vec->z -= input->z;
    vec->w -= input->w;
}

//-----------------------------------------------
void vec4_subf(struct vec4* vec, float input)
{
    vec->x -= input;
    vec->y -= input;
    vec->z -= input;
    vec->w -= input;
}

//-----------------------------------------------
void vec4_subv(struct vec4* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 4] -= input[i];
    }
}

//-----------------------------------------------
void vec4_mul(struct vec4* vec, struct vec4* input)
{
    vec->x *= input->x;
    vec->y *= input->y;
    vec->z *= input->z;
    vec->w *= input->w;
}

//-----------------------------------------------
void vec4_mulf(struct vec4* vec, float input)
{
    vec->x *= input;
    vec->y *= input;
    vec->z *= input;
    vec->w *= input;
}

//-----------------------------------------------
void vec4_mulv(struct vec4* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 4] *= input[i];
    }
}

//-----------------------------------------------
void vec4_div(struct vec4* vec, struct vec4* input)
{
    vec->x /= input->x;
    vec->y /= input->y;
    vec->z /= input->z;
    vec->w /= input->w;
}

//-----------------------------------------------
void vec4_divf(struct vec4* vec, float input)
{
    vec->x /= input;
    vec->y /= input;
    vec->z /= input;
    vec->w /= input;
}

//-----------------------------------------------
void vec4_divv(struct vec4* vec, float* input, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((float*)vec)[i % 4] /= input[i];
    }
}


// 4x4 matrix
//-----------------------------------------------
void mat4_ident(float matrix[4][4])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = (i == j ? 1.0f : 0.0f);
        }
    }
}

//-----------------------------------------------
void mat4_fill(float matrix[4][4], float val)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = val;
        }
    }
}

//-----------------------------------------------
void mat4_translate(float matrix[4][4], struct vec3* translate)
{

}

//-----------------------------------------------
void mat4_rotate(float matrix[4][4], float angle)
{

}

//-----------------------------------------------
void mat4_mul(float result[4][4], float a[4][4], float b[4][4])
{
    // row-major or column-major order ?
    // atm: row-major

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

//-----------------------------------------------
void mat4_perspective(float matrix[4][4], float angle, float ratio, float near, float far)
{
    angle = tanf(angle / 2);
    mat4_fill(matrix, 0.0f);
    matrix[0][0] = 1 / (ratio * angle);
    matrix[1][1] = 1 / angle;
    matrix[2][2] = -(far + near) / (far - near);
    matrix[2][3] = -1;
    matrix[3][2] = -(2 * far * near) / (far - near);
}

//-----------------------------------------------
void mat4_lookat(float result[4][4], struct vec3* eye, struct vec3* center, struct vec3* worldup)
{
    struct vec3 zaxis = { center->x, center->y, center->z };
    vec3_sub(&zaxis, eye);
    vec3_normalize(&zaxis);

    struct vec3 xaxis;
    vec3_cross(&xaxis, &zaxis, worldup);
    vec3_normalize(&xaxis);

    struct vec3 yaxis;
    vec3_cross(&yaxis, &xaxis, &zaxis);

    /*float rotation[4][4];
    mat4_ident(rotation);

    rotation[0][0] = xaxis.x;
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x;
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = -zaxis.x;
    rotation[1][2] = -zaxis.y;
    rotation[2][2] = -zaxis.z;

    float translation[4][4];
    mat4_ident(translation);

    translation[3][0] = -(eye->x);
    translation[3][1] = -(eye->y);
    translation[3][2] = -(eye->z);

    mat4_mul(result, rotation, translation);*/

    mat4_ident(result);
    result[0][0] = xaxis.x;
    result[1][0] = xaxis.y;
    result[2][0] = xaxis.z;
    result[0][1] = yaxis.x;
    result[1][1] = yaxis.y;
    result[2][1] = yaxis.z;
    result[0][2] = -zaxis.x;
    result[1][2] = -zaxis.y;
    result[2][2] = -zaxis.z;
    result[3][0] = -vec_dot(3, &xaxis, eye);
    result[3][1] = -vec_dot(3, &yaxis, eye);
    result[3][2] = -vec_dot(3, &zaxis, eye);
}


// utils
//-----------------------------------------------
float vec_dot(int vec_size, float* u, float* v)
{
    float product = 0.0f;
    for (int i = 0; i < vec_size; ++i) {
        product += u[i] * v[i];
    }
    return product;
}

//-----------------------------------------------
float deg2rad(float degrees)
{
    return degrees * 0.01745329251994329576923690768489f;
}