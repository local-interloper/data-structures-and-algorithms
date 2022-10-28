#ifndef STL_H
#define STL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct
{
    float n[3];
    float v1[3];
    float v2[3];
    float v3[3];
    unsigned short color;
} Tri;

typedef struct
{
    Tri *tris;
    unsigned int tri_count;
} Object3D;

Object3D *new_object(void);

void add_tri(Object3D *obj, Tri tri);

Object3D *object_from_binary(char *path);
void object_to_binary(Object3D *obj, char *path);

Object3D *object_from_stl(char *path);
void object_to_stl(Object3D *obj, char *solidName, char *path);

void print_tri(Tri *tri);
void print_object(Object3D *obj);

void free_object(Object3D *obj);

#endif