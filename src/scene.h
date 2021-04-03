#ifndef __SCENE_H__
#define __SCENE_H__

#include "model.h"

struct scene
{
    struct model* models;
    unsigned int nummodels;
    struct vec3* bounds;
    unsigned int numbounds;
};

void scene_new(struct scene* scene, unsigned int models);
void scene_free(struct scene* scene);
void scene_addmodel(struct model* model);

#endif