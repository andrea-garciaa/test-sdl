#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

bool array_grow(struct dynarray* array, unsigned int bytes)
{
    if (!array->grow)
        return 0;

    void* reallocatedbuf = realloc(array->buf, array->size + (bytes * array->grow));
    if (reallocatedbuf) {
        array->buf = (unsigned char*)reallocatedbuf;
        array->size += (bytes * array->grow);
        return true;
    }

    return false;
}

bool array_resize(struct dynarray* array, unsigned int size)
{
    void* reallocatedbuf = realloc(array->buf, size);
    if (reallocatedbuf) {
        array->buf = (unsigned char*)reallocatedbuf;
        array->size = size;
        return true;
    }

    return false;
}

bool array_new(struct dynarray* array, unsigned int size, unsigned int grow)
{
    void* buf = malloc(size);
    if (buf) {
        array->buf = (unsigned char*)buf;
        array->size = size;
        array->index = 0;
        array->grow = grow;
        return true;
    }

    return false;
}

bool array_free(struct dynarray* array)
{
    if (array && array->buf) {
        free(array->buf);
        return true;
    }

    return false;
}

unsigned int array_append(struct dynarray* array, void* data, unsigned int datalen)
{
    if (array->size - array->index < datalen) {
        if (!array_grow(array, datalen))
            datalen = array->size - array->index;
    }

    memcpy(&array->buf[array->index], data, datalen);
    array->index += datalen;
    return datalen;
}

unsigned int array_pushbyte(struct dynarray* array, uint8_t data)
{
    if ((array->size - array->index) < sizeof(uint8_t) && !array_grow(array, sizeof(uint8_t)))
        return 0;

    array->buf[array->index++] = data;
    return array->size - array->index;
}

unsigned int array_pushword(struct dynarray* array, uint16_t data)
{
    if ((array->size - array->index) < sizeof(uint16_t) && !array_grow(array, sizeof(uint16_t)))
        return 0;

    array->buf[array->index] = data;
    array->index += sizeof(uint16_t);
    return array->size - array->index;
}

unsigned int array_pushdword(struct dynarray* array, uint32_t data)
{
    if ((array->size - array->index) < sizeof(uint32_t) && !array_grow(array, sizeof(uint32_t)))
        return 0;

    array->buf[array->index] = data;
    array->index += sizeof(uint32_t);
    return array->size - array->index;
}

unsigned int array_pushqword(struct dynarray* array, uint64_t data)
{
    if ((array->size - array->index) < sizeof(uint64_t) && !array_grow(array, sizeof(uint64_t)))
        return 0;

    array->buf[array->index] = data;
    array->index += sizeof(uint64_t);
    return array->size - array->index;
}