#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mesh.h"
#include "array.h"


bool mesh_new(struct mesh* mesh)
{
    memset(mesh, 0, sizeof(*mesh));
    return false;
}

bool mesh_load(struct mesh* mesh, const char* filename)
{
    FILE* f = fopen(filename, "r");
    if (!f)
        return false;

    char buf[256];
    memset(buf, 0, sizeof(buf));

    struct dynarray vertexarray;
    unsigned int vertexarraylimit = mesh->numvertices ? (mesh->numvertices * 3 * sizeof(float)) : 256;

    if (!mesh->vertices) {
        if (!array_new(&vertexarray, vertexarraylimit, 32)) return false;
        mesh->flags |= MESH_OWNVERTEXMEMORY;
    } else {
        vertexarray.buf = (unsigned char*)mesh->vertices;
        vertexarray.size = vertexarraylimit;
        vertexarray.index = 0;
        vertexarray.grow = 32;
    }

    struct dynarray facearray;
    unsigned int facearraylimit = mesh->numfaces ? (mesh->numfaces * 3 * sizeof(float)) : 256;

    if (!mesh->faces) {
        if (!array_new(&facearray, facearraylimit, 32)) return false;
        mesh->flags |= MESH_OWNFACEMEMORY;
    } else {
        facearray.buf = (unsigned char*)mesh->faces;
        facearray.size = facearraylimit;
        facearray.index = 0;
        facearray.grow = 32;
    }


    while (fgets(buf, sizeof(buf), f)) {
        if (buf[0] == '#')
            continue;
        
        if (buf[0] == 'v') {
            float tmp[3];
            sscanf(buf + 2, "%f %f %f", &tmp[0], &tmp[1], &tmp[2]);

            if (buf[1] == ' ')
                array_append(&vertexarray, tmp, sizeof(tmp));
            /*else if (buf[1] == 'n')
                normals.emplace_back(std::array<float, 3>({tmp[0], tmp[1], tmp[2]}));*/
        } else if (buf[0] == 'f') {
            int spaces = 0;
            int slashes = 0;
            bool notex = false;
            char* p = buf + 2;
            char ch;
            
            while (ch = *p++) {
                if (ch == ' ')
                    spaces++;
                else if (ch == '/') {
                    slashes++;
                    if(p[1] == '/')
                        notex = true;
                }
            }

            char a, b, c, d, e;
            if (spaces == 2) {
                if (!slashes) {
                    if (3 == sscanf(buf + 2, "%c %c %c", &a, &c, &d)) {
                        float face[] = {~0, a-'0', c-'0', d-'0', ~0};
                        array_append(&facearray, face, sizeof(face));
                    }
                } else {
                    if (6 == sscanf(buf + 2, notex ? "%c//%c %c//%c %c//%c" : "%c/%*d/%c %c/%*d/%c %c/%*d/%c", &a, &b, &c, &b, &d, &b)) {
                        float face[] = {b-'0', a-'0', c-'0', d-'0', ~0};
                        array_append(&facearray, face, sizeof(face));
                    }
                }
            } else if (spaces == 3) {
                if (!slashes)
                {
                    if (4 == sscanf(buf + 2, "%c %c %c %c", &a, &c, &d, &e)) {
                        float face[] = {a-'0', c-'0', d-'0', e-'0', ~0};
                        array_append(&facearray, face, sizeof(face));
                    }
                }
                else
                {
                    if (8 == sscanf(buf + 2, notex ? "%c//%c %c//%c %c//%c %c//%c" : "%c/%*d/%c %c/%*d/%c %c/%*d/%c %c/%*d/%c", &a, &b, &c, &b, &d, &b, &e, &b)) {
                        float face[] = {b-'0', a-'0', c-'0', d-'0', e-'0'};
                        array_append(&facearray, face, sizeof(face));
                    }
                }
            }
        }
    }

    mesh->vertices = (float*)vertexarray.buf;
    mesh->numvertices = vertexarray.index / sizeof(float) / 3;
    mesh->faces = (float*)facearray.buf;
    mesh->numfaces = facearray.index / sizeof(float) / 3;

    return true;
}


bool mesh_unload(struct mesh* mesh)
{
    if (mesh) {
        if (mesh->flags & MESH_OWNVERTEXMEMORY)
            free(mesh->vertices);
        if (mesh->flags & MESH_OWNFACEMEMORY)
            free(mesh->faces);
        return true;
    }
    return false;
}