#include "model.h"


void model_new(struct model* model, struct mesh* meshes, unsigned int nummeshes, const char* name);
void model_free(struct model* model);
void model_addmesh(struct model* model, struct mesh* mesh, float* pos);
void model_removemesh(struct model* model, const char* meshname);