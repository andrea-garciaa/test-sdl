#ifndef __MODEL_H__
#define __MODEL_H__

#include "mesh.h"

struct model
{
    struct mesh* meshes;
    unsigned int nummeshes;
    const char name[52];
};

void model_new(struct model* model, struct mesh* meshes, unsigned int nummeshes, const char* name);
void model_free(struct model* model);
void model_addmesh(struct model* model, struct mesh* mesh, float* pos);
void model_removemesh(struct model* model, const char* meshname);

#endif