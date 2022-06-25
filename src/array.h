#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdint.h>
#include <stdbool.h>

struct dynarray
{
    unsigned char* buf;
    unsigned int index;
    unsigned int size;
    unsigned int grow; // grow factor (growing array by 4 bytes => growing by 4*grow bytes)
};

bool array_grow(struct dynarray* array, unsigned int bytes);
bool array_resize(struct dynarray* array, unsigned int size);
bool array_new(struct dynarray* array, unsigned int size, unsigned int grow);
bool array_free(struct dynarray* array);

// returns length of copied data
unsigned int array_append(struct dynarray* array, void* data, unsigned int datalen);

// returns remaining size of the array
unsigned int array_pushbyte(struct dynarray* array, uint8_t data);
unsigned int array_pushword(struct dynarray* array, uint16_t data);
unsigned int array_pushdword(struct dynarray* array, uint32_t data);
unsigned int array_pushqword(struct dynarray* array, uint64_t data);

#endif