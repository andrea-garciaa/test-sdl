#ifndef __MESH_H__
#define __MESH_H__

#include <stdbool.h>

#define MESH_OWNVERTEXMEMORY    0x1     // mesh vertex buffer is owned by the mesh manager 
#define MESH_OWNFACEMEMORY      0x2     // mesh face buffer is owned by the mesh manager

struct mesh
{
    float* vertices;
    float* faces;
    unsigned short numvertices;
    unsigned short numfaces;
    unsigned int vao;
    unsigned int vbo;
    unsigned short refs;
    unsigned short flags;
};

bool mesh_new(struct mesh* mesh);
bool mesh_load(struct mesh* mesh, const char* filename);
bool mesh_unload(struct mesh* mesh);

#endif